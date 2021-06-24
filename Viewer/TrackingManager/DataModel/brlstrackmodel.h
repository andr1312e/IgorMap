#ifndef BRLSTRACKMODEL_H
#define BRLSTRACKMODEL_H

#include <math.h>
#include <uiWidgets/oglHelpers/gldrawhelper.h>

struct BRLSPosition
{
    BRLSPosition():x(0),y(0),course(0),h(0),az(0){}
    BRLSPosition(float _x, float _y, float _course, float _h, float _az):
        x(_x),y(_y),course(_course),h(_h),az(_az) {}
    BRLSPosition(const BRLSPosition &point):
        x(point.x),y(point.y),course(point.course),h(point.h),az(point.az) {}
    BRLSPosition& operator= (const BRLSPosition &point)
    {
        if (this == &point)
            return *this;
        x = point.x;
        y = point.y;
        course = point.course;
        h = point.h;
        az = point.az;
        return *this;
    }

    float x;
    float y;
    float course;
    float h;
    float az;
};

class BRLSTrackModel {

public:
    BRLSTrackModel();
    void setBRLSPosition(BRLSPosition pos);
    BRLSPosition getBRLSPosition();
    dequeVertex *getBRLSTrack() {return &brlsTrack;}
    void setStartPosition(float _x, float _y);
    float getCourse() { return currentPosition.course; }
    bool isDataUpdate() {return newData;}
    AdvancedVertex getBRLSGeo() { return brlsGeographPoint; }
    void cleanModel();
    float getDriftAngle() { return (currentPosition.az - currentPosition.course); }    

private:
    BRLSPosition currentPosition,lastPosition;
    bool newData;
    dequeVertex brlsTrack;
    AdvancedVertex brlsGeographPoint;    
};

#endif // BRLSTRACKMODEL_H
