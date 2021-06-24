#ifndef TRACKINGCONTROLLER_H
#define TRACKINGCONTROLLER_H

#include "datamodel.h"
//#include "trackingobject.h"
#include <DataHandler/incomingdatahandler.h>
#include <boost/thread/mutex.hpp>
#include <QThread>
#include <QMetaType>

class TrackingController : public QObject
{
    Q_OBJECT

public:
    TrackingController(QObject *parent = 0);
    ~TrackingController();
    DataModel* getDataModel();
    void startDataHandler(bool locator);
    void stopDataHandler(bool cleanModel);
    void resetSocket() { incomingDataHandler->resetSocket(); }
    float getRadarAzimuth();
    float getRadarElevation();
    void setRadarParameters(float az, float el) { radarAzimuth = az; radarElevation = el; }
    void Lock() { mAzimuthLock.lock(); }
    void UnLock() { mAzimuthLock.unlock(); }
    float* getCoordsFour();
    void setCoordsFour(FourRayCoordMessage *msg);
    void SendMsg(QByteArray arr) { emit sendMsg(arr);}
    //void *getIncomingDataHandler () { return incomingDataHandler; }

private:
    DataModel *dataModel = nullptr;
    IncomingDataHandler *incomingDataHandler;
    QThread *tcpThread;
    boost::mutex mAzimuthLock;
    float radarAzimuth;
    float radarElevation;
    float CoordsFour[8] = {0};

public slots:
    //void updateLocationData(void *msg, MESSAGE_ID msgType);
    //void o();

private:
    // internal constraints for drawing (dependant on model definitions)
    //     rotation frequency in [rotations/min]
    const static int RADAR_ROTATION_FREQ = 30;
    //     rotation speed in [degree/sec]
    const static int RADAR_ANGULAR_VELOCITY = 360 * RADAR_ROTATION_FREQ / 60;

signals:
    void sendMsg(QByteArray arr);

};

#endif // TRACKINGCONTROLLER_H
