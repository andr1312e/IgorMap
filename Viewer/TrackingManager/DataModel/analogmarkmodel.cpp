#include "analogmarkmodel.h"
#include <ConfigurationManager/cfgmanager.h>

AnalogMarkModel::AnalogMarkModel()
{
    analogSignalMap = new AnalogSignalMap;
    for(int i = 0; i < NUM_ANALOG_SECTORS; i++) {
        AnalogSignalList *sig = new AnalogSignalList;
        analogSignalMap->push_back(sig);
    }
}

AnalogMarkModel::~AnalogMarkModel()
{
    for(int i = 0; i < NUM_ANALOG_SECTORS; i++) {
        AnalogSignalList *list = analogSignalMap->at(i);
        while(!list->empty()) {
            delete list->back(), list->pop_back();
        }
        list->clear();
        delete list;
    }
    analogSignalMap->clear();
    delete analogSignalMap;
}

/*void AnalogMarkModel::addAnalogMark(RLSOAnalogSignalMessage *msg) {
    int listInd = getAnalogListIndex(msg->az);
    AnalogSignal *sig = new AnalogSignal;
    sig->az = msg->az;
    sig->dist = msg->dist / 1000;
    analogSignalMap->at(listInd)->push_back(sig);
}*/

void AnalogMarkModel::cleanModel() {
    for(int i = 0; i < NUM_ANALOG_SECTORS; i++) {
        AnalogSignalList *list = analogSignalMap->at(i);
        while(!list->empty()) {
            delete list->back(), list->pop_back();
        }
        list->clear();
    }
}

void AnalogMarkModel::emptyAnalogMarkList(float radarAzimuth) {
    int listInd = getAnalogListIndex(radarAzimuth);
    AnalogSignalList *siglist = analogSignalMap->at(listInd);
    if (!siglist->empty()) {
        //AnalogSignal *sig;
        while(!siglist->empty()) {
            delete siglist->back(), siglist->pop_back();
        }
        siglist->clear();
    }
}

void AnalogMarkModel::eraseAnalogMarks(float oldRadarAzimuth, float newRadarAzimuth) {
    lockAnalogModel();
    int oldListInd = getAnalogListIndex(oldRadarAzimuth),
        newListInd = getAnalogListIndex(newRadarAzimuth);

    if(newRadarAzimuth > 360) { // in case when we go over 360deg/0deg pole...
        for (int i = oldListInd; i < NUM_ANALOG_SECTORS; i++) {
            AnalogSignalList *list = analogSignalMap->at(i);
            for(AnalogSignalList::iterator it = list->begin(); it != list->end(); it++) {
                AnalogSignal *sig = *it;
                if( sig->az >= oldRadarAzimuth ) {
                    AnalogSignalList::iterator tmp;
                    tmp = list->erase(it);
                    it = tmp;
                    delete sig;
                }
            }
        }
        for (int i = 0; i <= newListInd; i++) {
            AnalogSignalList *list = analogSignalMap->at(i);
            for(AnalogSignalList::iterator it = list->begin(); it != list->end(); it++) {
                AnalogSignal *sig = *it;
                if( sig->az <= newRadarAzimuth ) {
                    AnalogSignalList::iterator tmp;
                    tmp = list->erase(it);
                    it = tmp;
                    delete sig;
                }
            }
        }
    } else { // otherwise erase analog marks between 2 azimuth values
        for (int i = oldListInd; i <= newListInd; i++) {
            AnalogSignalList *list = analogSignalMap->at(i);
            for(AnalogSignalList::iterator it = list->begin(); it != list->end(); it++) {
                AnalogSignal *sig = *it;
                if( sig->az >= oldRadarAzimuth && sig->az <= newRadarAzimuth ) {
                    AnalogSignalList::iterator tmp;
                    tmp = list->erase(it);
                    it = tmp;
                    delete sig;
                }
            }
        }
    }
    unlockAnalogModel();
}

void AnalogMarkModel::eraseAllAnalogMarks()
{
    lockAnalogModel();

    auto iterMap = analogSignalMap->begin();
    while (iterMap != analogSignalMap->end())
    {
        auto iterList = (*iterMap)->begin();
        if (iterList != (*iterMap)->end())
        {
            for (;iterList != (*iterMap)->end();iterList++)
                delete *iterList;
            (*iterMap)->clear();
        }
        iterMap++;
    }

    unlockAnalogModel();
}

int AnalogMarkModel::getAnalogListIndex(float radarAz) {
    if (radarAz >= 360) {
        radarAz -= 360;
    }
    int retVal = (int) ((float) radarAz / ANALOG_SECTOR_SIZE);
    if (retVal < 0 || retVal >= NUM_ANALOG_SECTORS) {
        qDebug() << "KTAMarkModel: error! wrong list index!!! " << retVal;
        assert(false);
    }
    return retVal;
}
