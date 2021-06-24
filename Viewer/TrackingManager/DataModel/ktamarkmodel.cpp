#include "ktamarkmodel.h"
#include <QtMath>


KTAMarkModel::KTAMarkModel() {    
    for(int i = 0; i < NUM_RADIAL_SECTORS; i++) {
        ktaMarkMap.insert(i, KTAMarkVector());
    }    

    /*connect(this, &KTAMarkModel::returnDataToTableKTA,
            CfgManager::Instance()->getUiController()->getKTAInfoWidget(),
            &KTAInfoWidget::fillTable);
    connect(CfgManager::Instance()->getUiController()->getKTAInfoWidget(),
            &KTAInfoWidget::selectKTARequest,
            this,
            &KTAMarkModel::selectKTARequestHandler);
    connect(this, &KTAMarkModel::selectKTARequestAnswer,
            CfgManager::Instance()->getUiController()->getKTAInfoWidget(),
            &KTAInfoWidget::selectKTARequestAnswerHandler);*/
}

KTAMarkModel::~KTAMarkModel()
{
    ktaMarkMap.clear();
    markForTable.clear();
}

void KTAMarkModel::addKTAMark(RLSOPlotMessage *msg, uint type) {
    KTAMark mark;
    mark.az = msg->Azm;
    if(mark.az < 0)
    {
        mark.az += 360;
    }
    else if (mark.az >= 360) {
        mark.az -= 360;
    }

    int listInd = getListIndex(msg->Azm);    
    mark.dist = msg->D / 1000 ;
    mark.pointAngle = msg->Ugm;
    mark.sceneX = mark.dist * cosf(mark.az * M_PI / 180);
    mark.sceneY = mark.dist * sinf(mark.az * M_PI / 180);
    mark.amp = msg->Amp;    
    mark.rSpeed = msg->Vr;
    mark.type = type;
//    if (mark.rSpeed >= 20000)
//        mark.type = KTA_VOI_EXTRA;
//    mark.limit = timeAliveKTA;
    mark.absY = mark.dist * cosf((mark.az) * M_PI / 180);
    mark.absX = mark.dist * sinf((mark.az) * M_PI / 180);

    ktaMarkMap.find(listInd).value().push_back(SharedPointerKTAMark(new KTAMark(mark)));
}

void KTAMarkModel::cleanModel() {    
    ktaMarkMap.clear();
    for(int i = 0; i < NUM_RADIAL_SECTORS; i++) {
        ktaMarkMap.insert(i, KTAMarkVector());
    }
}

int KTAMarkModel::getKTACount()
{
    if (!ktaMarkMap.empty()) {
        int count = 0;
        for (auto item = ktaMarkMap.begin();
            item != ktaMarkMap.end();
            item++) {
            count += item.value().size();
        }
        return count;
    }
    else
        return 0;
}

void KTAMarkModel::eraseAllKTAMarksInCurrentAz()
{
    //float &azf = CfgManager::Instance()->getUiController()->getRayControlWidget()->getAzAntenna();
    //if (azf < 0)
    //    return;
    int az = getListIndex(20 + 4.5);

    for (int i = 0; i != 20; i++) {
        if(az < 0)
            az += 360;
        else if (az >= 360)
            az -= 360;
        ktaMarkMap.find(az).value().clear();
        az++;
    }
}

void KTAMarkModel::findKTAMarkAt(float az, float dist, float x, float y, float threshold)
{
    markForTable.clear();

    float deltaAZ = atan2(threshold / 2, dist) * 180.0 / M_PI;
    int tAz = az - deltaAZ;
    if (tAz < 0)
        tAz += 360;
    int startAz = qFloor(tAz),
        count = qCeil(deltaAZ * 2);

    int azInt = startAz;
    double minDist = 1;
    for (int i = 0; i != count; i++) {
        auto mapItem = ktaMarkMap.find(azInt + i);
        if (mapItem != ktaMarkMap.end()) {
            if (!mapItem.value().empty()) {
                for (auto iterKTA = mapItem->begin(); iterKTA != mapItem->end(); iterKTA++) {
                    double tx = fabs(iterKTA->data()->absX - x), ty = fabs(iterKTA->data()->absY - y);
                    double tdist = sqrt(tx * tx + ty * ty);
                    if (tdist < threshold) {
                        if (minDist > tdist) {
                            minDist = tdist;
                            if (!selectedMark.isNull()) {
                                selectedMark.data()->selected = false;
                            }
                            selectedMark = iterKTA->toWeakRef();
                            selectedMark.data()->selected = true;
                        }
                        markForTable.push_back(iterKTA->toWeakRef());
                    }
                }
            }
        }
    }

    //CfgManager::Instance()->getUiController()->getKTAInfoWidget()->fillTable(&markForTable);
}

int KTAMarkModel::getListIndex(float radarAz) {    
    if(radarAz < 0)
    {
        radarAz += 360;
    }
    else if (radarAz >= 360) {
        radarAz -= 360;
    }
    if (radarAz < 0) {
        int i = 0;
        i = 5;
        return 0;
    }
    else
        return qFloor(radarAz);
}

void KTAMarkModel::selectKTARequestHandler(int indexOnKTAVector)
{
    if (indexOnKTAVector >= markForTable.size()) {
        emit selectKTARequestAnswer(WeakPointerKTAMark());
    }
    else {
        if (!selectedMark.isNull()) {
            selectedMark.data()->selected = false;
        }
        if (!markForTable.at(indexOnKTAVector).isNull()) {
            selectedMark = markForTable.at(indexOnKTAVector);
            selectedMark.data()->selected = true;
            emit selectKTARequestAnswer(markForTable.at(indexOnKTAVector));
        }
    }
}

void KTAMarkModel::eraseAllKTA()
{

    eraseAllKTAMarksInCurrentAz();
}
