#include "trackingobject.h"
#include <ConfigurationManager/cfgmanager.h>
#include <QDebug>
/*
TrackMark::TrackMark(float _azimuth, float _distance, uint _trackID)
{
    trackID = _trackID;
    setPosition(_azimuth, _distance);
    setNewPosition(_azimuth, _distance, 0);
    isSelected = false;
    heading = 0;
}

void TrackMark::setPosition(float _azimuth, float _distance)
{
    azimuth = _azimuth;
    distance = _distance;
}

void TrackMark::setNewPosition(float _azimuth, float _distance, float _aimAz)
{
    newAzimuth = _azimuth;
    newDistance = _distance;
    newHeading = _aimAz;
}

bool TrackMark::isUnderRadarRay(float radarAzimuth)
{
    float radarAzimuthFront = radarAzimuth;
    float radarAzimuthBack = radarAzimuth - (float) CfgManager::RADAR_RAY_WIDTH;
    if(radarAzimuthFront > 360) { // convert to 0..360 values
        radarAzimuthBack -= 360;
        radarAzimuthFront -= 360;
        float az = (azimuth > 180) ? (azimuth - 360) : azimuth;
        if(az >= radarAzimuthBack && az <= radarAzimuthFront) {
            return true;
        } else {
            return false;
        }
    } else {
        if(azimuth >= radarAzimuthBack && azimuth <= radarAzimuthFront) {
            return true;
        } else {
            return false;
        }
    }
}

float TrackMark::getAzimuth()
{
    return azimuth;
}

float TrackMark::getDistance()
{
    return distance;
}

float TrackMark::getNewAzimuth()
{
    return newAzimuth;
}

float TrackMark::getNewDistance()
{
    return newDistance;
}

void TrackMark::updatePosition()
{
    azimuth = newAzimuth;
    distance = newDistance;
    heading = newHeading;
}

void TrackMark::getXYScene(float &xScene, float &yScene) {
    float az = -azimuth * PI / 180;
    xScene = distance * cosf(az);
    yScene = distance * sinf(az);
}
*/
