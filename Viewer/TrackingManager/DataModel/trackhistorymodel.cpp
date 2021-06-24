#include "trackhistorymodel.h"
#include <ConfigurationManager/cfgmanager.h>

TrackHistory::~TrackHistory() {
    while(!trackHistory->empty()) {
        delete trackHistory->back(), trackHistory->pop_back();
    }
    trackHistory->clear();
    delete trackHistory;
}

TrackHistoryModel::TrackHistoryModel() {
    trackHistoryMap = new TrackHistoryMap;
}

TrackHistoryModel::~TrackHistoryModel() {
    cleanModel();
    delete trackHistoryMap;
}

void TrackHistoryModel::cleanModel() {
    for (TrackHistoryMap::iterator it = trackHistoryMap->begin(); it != trackHistoryMap->end(); it++) {
        TrackHistory *hist = it->second;
        delete hist;
    }
    trackHistoryMap->clear();
}

TrackHistoryList* TrackHistoryModel::getTrackById(int id) {
    TrackHistoryMap::iterator it = trackHistoryMap->find(id);

    if ( it != trackHistoryMap->end() ) {
        return (it->second->getHistory());
    } else {
        //qDebug() << "TrackMarkModel::getTrackById. Track not found!!!";
    }

    return NULL;
}

TrackHistory* TrackHistoryModel::getHistoryById(int id) {
    TrackHistoryMap::iterator it = trackHistoryMap->find(id);

    if ( it != trackHistoryMap->end() ) {
        return (it->second);
    } else {
        //qDebug() << "TrackMarkModel::getTrackById. Track not found!!!";
    }

    return NULL;
}

void TrackHistoryModel::deleteTrack(int id) {
    if (id < 0) {
        qDebug() << "TrackMarkModel::deleteTrack ASSERT, track ID < 0!";
        assert(false);

        return;
    }

    TrackHistoryMap::iterator it = trackHistoryMap->find(id);
    if (it != trackHistoryMap->end()) {
        TrackHistoryList *list = it->second->getHistory();
        for (TrackHistoryList::iterator list_it = list->begin(); list_it != list->end(); list_it++) {
            //TrackHistoryMark *mark = *list_it;
            //removeTrackFromGrid(it->first, mark->, list->getMarkGridCol());
        }
        trackHistoryMap->erase(id);
        delete list;
    } else {
        //qDebug() << "TrackMarkModel::deleteTrack(), track ID: " << id << "  NOT FOUND!!!";
    }
}

void TrackHistoryModel::initTrackInfoGrid() {
    float colSize = CfgManager::Instance()->getSizeSettings()->getTrackInfoColSize(),
          rowSize = CfgManager::Instance()->getSizeSettings()->getTrackInfoRowSize();
    int colCount = CfgManager::Instance()->getSizeSettings()->getTrackInfoColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->getTrackInfoRowCount();

    for (TrackHistoryMap::iterator it = trackHistoryMap->begin(); it != trackHistoryMap->end(); it++) {
        TrackHistoryList *list = it->second->getHistory();
        if (it->second->visible()) {
            for(TrackHistoryList::iterator list_it = list->begin(); list_it != list->end(); list_it++) {
                TrackHistoryMark *mark = *list_it;
                float xpos = mark->xpos + (float) CfgManager::DISTANCE_GRID_MAX,
                      ypos = mark->ypos + (float) CfgManager::DISTANCE_GRID_MAX;
                mark->infoGridRow = mark->markGridRow = (int) ceil(ypos / rowSize) - 1;
                mark->infoGridCol = mark->markGridCol = (int) ceil(xpos / colSize);

                occupyGridAt(mark->infoGridRow, mark->infoGridCol);
            }
        }
    }

    for (TrackHistoryMap::iterator it = trackHistoryMap->begin(); it != trackHistoryMap->end(); it++) {
        TrackHistoryList *list = it->second->getHistory();
        if (it->second->visible()) { // calc only for visible tracks!
            int counter = 0;
            for(TrackHistoryList::iterator list_it = list->begin(); list_it != list->end(); list_it++) {
                if(counter % CfgManager::TRACK_HISTORY_INFO_SPACING == 0) {
                    TrackHistoryMark *mark = *list_it;
                    // find place for info text
                    bool searching = true;
                    do {
                        moveTrackInfoPosition(mark, searching, rowCount, colCount);
                    } while(searching);

                    if (mark->infoGridRow >= 0 && mark->infoGridCol >= 0) {
                        //setTrackInfoAt(mark->infoGridRow, mark->infoGridCol);
                        occupyGridAt(mark->infoGridRow, mark->infoGridCol);
                        mark->showInfo = true;
                    }
                }
                counter++;
            }
        }
        //addTrackToGrid(it->first, mark->infoGridRow, mark->infoGridCol);
    }
}

void TrackHistoryModel::resetTrackInfoGrid() {
    /*float colSize = CfgManager::Instance()->getSizeSettings()->getTrackInfoColSize(),
          rowSize = CfgManager::Instance()->getSizeSettings()->getTrackInfoRowSize();*/
    int colCount = CfgManager::Instance()->getSizeSettings()->getTrackInfoColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->getTrackInfoRowCount();

    // release memory
    for (TrackInfoGrid::iterator it = trackInfoGrid.begin(); it != trackInfoGrid.end(); it++) {
        vector<TrackInfoGridItem> *row = &*it;
        row->clear();
    }
    trackInfoGrid.clear();

    // reinit grid
    trackInfoGrid.resize(rowCount + 1);
    for (int i = 0; i <= rowCount; ++i) {
        trackInfoGrid[i].resize(colCount + 1);
    }

    for (TrackHistoryMap::iterator it = trackHistoryMap->begin(); it != trackHistoryMap->end(); it++) {
        TrackHistoryList *list = it->second->getHistory();
        for(TrackHistoryList::iterator list_it = list->begin(); list_it != list->end(); list_it++) {
            TrackHistoryMark *mark = *list_it;
            mark->showInfo = false;
        }
    }
}

void TrackHistoryModel::addTrackMark(RLSOaimMessage *msg) {
    TrackHistoryMark *mark = new TrackHistoryMark;
    mark->dist = msg->D / 1000;
    mark->az = msg->Az;
    mark->xpos = mark->dist * cosf(mark->az * PI / 180);
    mark->ypos = mark->dist * sinf(mark->az * PI / 180);
    mark->height = msg->sAimCoords.h;
    mark->speed = msg->sAimCoords.vp;
    mark->heading = msg->sAimCoords.tack;
    mark->timestamp = msg->sTimeMeasurement;
    mark->trackSpeed = msg->sAimCoords.vp;
    mark->trackHeight = msg->sAimCoords.h;
    mark->showInfo = false;

    // insert into model
    TrackHistoryList *list = getTrackById(msg->trackID);
    if (list == NULL) {
        TrackHistory *hist = new TrackHistory;
        hist->setTrackID(msg->trackID);
        list = hist->getHistory();
        trackHistoryMap->insert( TrackHistoryMapPair(msg->trackID, hist) );
    } else {
        list->push_front(mark);
    }
}

void TrackHistoryModel::moveTrackInfoPosition(TrackHistoryMark *mark, bool &searching, const int &rowCount, const int &colCount) {


    mark->infoGridRow = mark->markGridRow;
    mark->infoGridCol = mark->markGridCol;
    Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_LEFT, rowCount, colCount);
    if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
        mark->infoGridRow = mark->markGridRow;
        mark->infoGridCol = mark->markGridCol;
        Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_BOTTOM, rowCount, colCount);
        if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
            mark->infoGridRow = mark->markGridRow;
            mark->infoGridCol = mark->markGridCol;
            Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_TOP, rowCount, colCount);
            if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                mark->infoGridRow = mark->markGridRow;
                mark->infoGridCol = mark->markGridCol;
                Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_RIGHT, rowCount, colCount);
                if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                    mark->infoGridRow = mark->markGridRow;
                    mark->infoGridCol = mark->markGridCol;
                    Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_RIGHT, rowCount, colCount);
                    Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_TOP, rowCount, colCount);
                    if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                        mark->infoGridRow = mark->markGridRow;
                        mark->infoGridCol = mark->markGridCol;
                        Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_RIGHT, rowCount, colCount);
                        Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_BOTTOM, rowCount, colCount);
                        if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                            mark->infoGridRow = mark->markGridRow;
                            mark->infoGridCol = mark->markGridCol;
                            Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_LEFT, rowCount, colCount);
                            Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_TOP, rowCount, colCount);
                            if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                                mark->infoGridRow = mark->markGridRow;
                                mark->infoGridCol = mark->markGridCol;
                                Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_LEFT, rowCount, colCount);
                                Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_BOTTOM, rowCount, colCount);
                                if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                                    mark->infoGridRow = -1;
                                    mark->infoGridCol = -1;
                                    searching = false;
                                } else { searching = false; }
                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else { searching = false; }
    } else { searching = false; }



/*

    Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_LEFT, rowCount, colCount);
    if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
        Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_BOTTOM, rowCount, colCount);
        if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
            // reset movement and move in another direction
            mark->infoGridRow = mark->markGridRow;
            mark->infoGridCol = mark->markGridCol;
            Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_TOP, rowCount, colCount);
            if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_RIGHT, rowCount, colCount);
                if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {
                    // reset movement and move in another direction
                    mark->infoGridRow = mark->markGridRow;
                    mark->infoGridCol = mark->markGridCol;
                    Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_LEFT, rowCount, colCount);
                    Utils::moveInGrid(mark->infoGridRow, mark->infoGridCol, MOVE_TOP, rowCount, colCount);
                    if( !isGridEmptyAt(mark->infoGridRow, mark->infoGridCol) ) {


                        mark->infoGridRow = -1;
                        mark->infoGridCol = -1;
                        searching = false;



                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else { searching = false; }
    } else { searching = false; }
*/
}
