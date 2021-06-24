#ifndef DATALOGGERMODEL_H
#define DATALOGGERMODEL_H

#include <boost/thread/mutex.hpp>
#include <list>
#include <deque>
#include "datamessage.h"


using namespace std;
//using namespace __gnu_cxx;

enum DisplayMode {    
    DISPLAY_LOCATOR,
    DISPLAY_LOCATOR_3D,
    DISPLAY_TRACK,
    DISPLAY_LOCAL_MAP
};

enum ZoomMode {
    ZOOM_RECT,
    ZOOM_SECTOR
};

enum WND_ID {
    INFO_WND,
    KTAINFO_WND,
    TRACKLIST_WND,
    LLFCONTROL_WND,
    OSCILLOSCOPE_WND,
    BLANKAREA_WND,
    BASICELEMENT_WND,
    RAYCONTROL_WND,
    STATECONTROL_WND,
    STATECONTROL_SUBWND
};

struct ResizeWindowMessage {
    timeval sTimeStamp;
    WND_ID windowID;
    int width;
    int height;
};

struct MoveWindowMessage {
    timeval sTimeStamp;
    WND_ID windowID;
    int xpos;
    int ypos;
};

struct ShowHideWindowMessage {
    timeval sTimeStamp;
    WND_ID windowID;
    bool visible;
};

struct ZoomMessage {
    timeval sTimeStamp;
    ZoomMode zoomMode;
    float mapScale;
    int zoomArea[4];
    bool reset;
};

struct MoveScaleMessage {
    timeval sTimeStamp;
    float mapScale;
    int mapCenterX;
    int mapCenterY;
};



struct EmittingChangedMessage {
    timeval sTimeStamp;
    bool on;
};

struct RotationSpeedChangedMessage {
    timeval sTimeStamp;
    char speed;
};

struct RotationStateChangedMessage {
    timeval sTimeStamp;
    bool on;
};

typedef list<MESSAGE_ID> DataLoggerProcessQueue;
//typedef list<RLSOstateMessage*> StateMessageList;
typedef list<RLSOPlotMessage*> KTAMessageList;
typedef list<RLSOaimMessage*> TrackMessageList;
//typedef list<RLSOAnalogSignalMessage*> AnalogSignalMessageList;
typedef list<ResetTrackMessage*> ResetTrackMessageList;
typedef list<FourRayCoordMessage*> FourRayCoordMessageList;
typedef list<GKCoordsRlsMessage*> GKCoordsRlsMessageList;
typedef list<ShowHideWindowMessage*> ShowHideWindowMessageList;
typedef list<MoveWindowMessage*> MoveWindowMessageList;
typedef list<ResizeWindowMessage*> ResizeWindowMessageList;
typedef list<ZoomMessage*> ZoomMessageList;
typedef list<MoveScaleMessage*> MoveScaleMessageList;
typedef list<EmittingChangedMessage*> EmittingChangedMessageList;
typedef list<RotationSpeedChangedMessage*> RotationSpeedChangedMessageList;
typedef list<RotationStateChangedMessage*> RotationStateChangedMessageList;

class DataLoggerModel
{
public:
    DataLoggerModel();
    ~DataLoggerModel();
    //void addStateMessage(RLSOstateMessage *msg);
    void addKTAMessage(RLSOPlotMessage *msg);
    void addTrackMessage(RLSOaimMessage *msg);
    //void addAnalogSignalMessage(RLSOAnalogSignalMessage *msg);
    void addResetTrackMessage(ResetTrackMessage *msg);
    void addFourRayCoordMessage(FourRayCoordMessage *msg);
    void addGKCoordsRlsMessage(GKCoordsRlsMessage *msg);
    void addShowHideWindowMessage(ShowHideWindowMessage *msg);
    void addMoveWindowMessage(MoveWindowMessage *msg);
    void addResizeWindowMessage(ResizeWindowMessage *msg);
    void addZoomMessage(ZoomMessage *msg);
    void addMoveScaleMessage(MoveScaleMessage *msg);
    void addEmittingChangedMessage(EmittingChangedMessage *msg);
    void addRotationSpeedChangedMessage(RotationSpeedChangedMessage *msg);
    void addRotationStateChangedMessage(RotationStateChangedMessage *msg);
    void lockDataLoggerModel() { mLock.lock(); }
    void unlockDataLoggerModel() { mLock.unlock(); }
    //StateMessageList* getStateMessageList() { return &stateMessageList; }
    KTAMessageList* getKTAMessageList() { return &ktaMessageList; }
    TrackMessageList* getTrackMessageList() { return &trackMessageList; }
    //AnalogSignalMessageList* getAnalogSignalMessageList() { return &analogSignalMessageList; }
    ResetTrackMessageList* getResetTrackMessageList() { return &resetTrackMessageList; }
    FourRayCoordMessageList* getFourRayCoordMessageList() { return &fourRayCoordMessageList; }
    GKCoordsRlsMessageList* getGKCoordsRlsMessageList() { return &gkCoordsRlsMessageList; }
    ShowHideWindowMessageList* getShowHideWindowMessageList() { return &showHideWindowMessageList; }
    MoveWindowMessageList* getMoveWindowMessageList() { return &moveWindowMessageList; }
    ResizeWindowMessageList* getResizeWindowMessageList() { return &resizeWindowMessageList; }
    ZoomMessageList* getZoomMessageList() { return &zoomMessageList; }
    MoveScaleMessageList* getMoveScaleMessageList() { return &moveScaleMessageList; }
    EmittingChangedMessageList* getEmittingChangedMessageList() { return &emittingChangedMessageList; }
    RotationSpeedChangedMessageList* getRotationSpeedChangedMessageList() { return &rotationSpeedChangedMessageList; }
    RotationStateChangedMessageList* getRotationStateChangedMessageList() { return &rotationStateChangedMessageList; }
    DataLoggerProcessQueue* getProcessQueue() { return &processQueue; }

    void setStopingDataLogger(bool stoping) { stopingDataLogger = stoping; }
    bool isStopingDataLogger() { return stopingDataLogger; }

private:
    boost::mutex mLock;
    bool stopingDataLogger;

    DataLoggerProcessQueue processQueue;
    //StateMessageList stateMessageList;
    KTAMessageList ktaMessageList;
    TrackMessageList trackMessageList;
    //AnalogSignalMessageList analogSignalMessageList;
    ResetTrackMessageList resetTrackMessageList;
    FourRayCoordMessageList fourRayCoordMessageList;
    GKCoordsRlsMessageList gkCoordsRlsMessageList;
    ShowHideWindowMessageList showHideWindowMessageList;
    MoveWindowMessageList moveWindowMessageList;
    ResizeWindowMessageList resizeWindowMessageList;
    ZoomMessageList zoomMessageList;
    MoveScaleMessageList moveScaleMessageList;
    EmittingChangedMessageList emittingChangedMessageList;
    RotationSpeedChangedMessageList rotationSpeedChangedMessageList;
    RotationStateChangedMessageList rotationStateChangedMessageList;
};

#endif // DATALOGGERMODEL_H
