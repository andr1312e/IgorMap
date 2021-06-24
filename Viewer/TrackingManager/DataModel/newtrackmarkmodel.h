#ifndef NEWTRACKMARKMODEL_H
#define NEWTRACKMARKMODEL_H
#include "IncomingMessageHandler/trackmath.h"
#include "trackmarkmodel.h"


struct Rect {
    Rect(): point1(), point2() {}
    Rect(float x1, float y1, float x2, float y2): point1(x1, y1), point2(x2, y2) {}

    AdvancedVertex point1, point2;
};

struct IdInfo {
    Rect form;
    Rect closedZone;
    int direction = 15;

    AdvancedVertex scenePos;
    float trackHeading;
    float az;
    int trackId;
    float speed;
    float dist;
    float height;
};

struct Id_Y {
    float y;
    int id;
};

typedef multimap<float, Id_Y> MapOfClosedZone;
typedef map<float, Id_Y> MapOfForm;
typedef map<int, IdInfo> MapOfInfo;
typedef map<int, TrackList> MapOfTrack;

class NewTrackMarkModel
{
public:
    NewTrackMarkModel();
    ~NewTrackMarkModel();
    void addTrackMark(RLSOaimMessage *msg);
    void deleteTrackMark(int id);
    void resetModel();
    void lockTrackModel() { mLock.lock(); }
    void unlockTrackModel() { mLock.unlock(); }
    MapOfInfo* getInfoOfTracksMap() { return &mapOfInfo; }

private:
    void findInfoPositionOnZone();
    void deleteClosedZoneAndFormByID(int id);

private:
    boost::mutex mLock;
    MapOfClosedZone mapOfClosedZone;
    MapOfForm mapOfForm;
    MapOfInfo mapOfInfo;
    MapOfTrack mapOfTracks;

    IdInfo currentInfo;
    int currentId;

    const short magicNumber = 24;
    float magicNumberWithScale;
};

#endif // NEWTRACKMARKMODEL_H
