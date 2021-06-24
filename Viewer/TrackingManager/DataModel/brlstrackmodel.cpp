#include "brlstrackmodel.h"
#include <ConfigurationManager/cfgmanager.h>

BRLSTrackModel::BRLSTrackModel()
{
    cleanModel();
}

void BRLSTrackModel::setBRLSPosition(BRLSPosition pos)
{
    float *gcenter = CfgManager::Instance()->getUiController()->getMainUIView()->getGlobalCenterPoint();
    double tempX,tempY;
    brlsGeographPoint = RectCoordinatesToGradus(AdvancedVertex(pos.x,pos.y));
    tempX = (pos.y - gcenter[0]) / CfgManager::GLOBAL_TO_LOCAL_RATIO;
    tempY = (pos.x - gcenter[1]) / CfgManager::GLOBAL_TO_LOCAL_RATIO;
    currentPosition = pos;
    currentPosition.x = tempX;
    currentPosition.y = tempY;
    newData = true;
    if (brlsTrack.size() > 2000)
        brlsTrack.pop_back();
    brlsTrack.push_front(Vertex(tempX,tempY)); //Отвязаны метки трассы БРЛС
    CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel()->checkGoingAbroad(AdvancedVertex(currentPosition.x,currentPosition.y));
}

void BRLSTrackModel::setStartPosition(float _x, float _y)
{
    float *gcenter = CfgManager::Instance()->getUiController()->getMainUIView()->getGlobalCenterPoint();
    double tempX,tempY;
    tempX = (_y - gcenter[0]) / CfgManager::GLOBAL_TO_LOCAL_RATIO;
    tempY = (_x - gcenter[1]) / CfgManager::GLOBAL_TO_LOCAL_RATIO;
    currentPosition.x = tempX;
    currentPosition.y = tempY;
}

void BRLSTrackModel::cleanModel() {
    brlsTrack.clear();
    newData = false;
    currentPosition = BRLSPosition();
    lastPosition = BRLSPosition();
    brlsGeographPoint = AdvancedVertex();
}


BRLSPosition BRLSTrackModel::getBRLSPosition() {
    if (newData) {
        lastPosition = currentPosition;
    }
    return currentPosition;
}
