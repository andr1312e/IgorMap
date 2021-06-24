#ifndef TRACKINGOBJECT_H
#define TRACKINGOBJECT_H
/*
typedef unsigned int uint;

class TrackMark
{
public:
    TrackMark() {};
    TrackMark(float _azimuth, float _distance, uint trackId);
    bool isUnderRadarRay(float radarAzimuth);
    void setPosition(float _azimuth, float _distance);
    float getAzimuth();
    float getNewAzimuth();
    float getDistance();
    float getNewDistance();
    float getTrackID() { return trackID; };
    float getHeading() { return heading; };
    void setNewPosition(float _azimuth, float _distance, float _aimAz);
    void updatePosition();
    void getXYScene(float &xScene, float &yScene);
    void setSelected(bool selected) { isSelected = selected; };
    bool selected() { return isSelected; };

private:
    bool isSelected;
    uint trackID;       // track id
    float azimuth;      // displayed coordinate currently displayed
    float distance;     // displayed coordinate currently displayed
    float heading;   // displayed aim heading
    float newAzimuth;   // actual coordinate
    float newDistance;  // actual coordinate
    float newHeading; // actual coordinate

};
*/
#endif // TRACKINGOBJECT_H
