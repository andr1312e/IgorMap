#ifndef INCOMINGDATAHANDLER_H
#define INCOMINGDATAHANDLER_H

#include <QTcpSocket>
#include <TcpHandler/datamessage.h>
#include <QUrl>
#include <QJsonDocument>

#include <global.h>

enum DATA_HANDLER_MODE {
    DATA_HANDLER_LOCATOR,
    DATA_HANDLER_READ_LOGS
};

enum KTA_TYPE {
    KTA_POI,
    KTA_VOI,
    KTA_TM,
    KTA_VOI_EXTRA
};

class IncomingDataHandler : public QObject
{
    Q_OBJECT

public:
    IncomingDataHandler();
    ~IncomingDataHandler();
    void stop() { pTcpSocket->abort(); running = false; }//quit(); }
    void setWorkMode(DATA_HANDLER_MODE mode) { workMode = mode; }
    void resetSocket();
    bool isSocketValid() {
        return (pTcpSocket->state() == QTcpSocket::ConnectedState); }
    int getMessageSize(quint8 id);
    //const QString hostAddress = "192.168.115.212";


public slots:
    void doWork();
    void sendMsg(QByteArray arr) {
        if (isSocketValid()) {
            pTcpSocket->write(arr);
            pTcpSocket->flush(); }
        }
    void sendJsonDocument(QJsonDocument doc);

private:
    //QUdpSocket *pUdpSocket;
    QTcpSocket *pTcpSocket;
    //QHostAddress ipAddress;
    //QEventLoop *evLoop;
    DATA_HANDLER_MODE workMode;
    bool running;

    timeval lastMsgTime;

    QByteArray unhandledData, unhandledDataForMap;
    int seekValue;

    QTcpSocket *pTcpSocketForMap;
    const QUrl localHost;

    //float angCorrection;
    //bool oldData;
protected:


private slots:
    void readData();
    void readDataForMap();
    void connectionError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void slotConnected();

signals:
    void addVOIMarkSign(VOIMarkMessage msg);
    void addPOIMarkSign(POIKtaMessage msg);
    void addTraceMark(RLSOaimMessage msg);
    void resetTraceMark(quint32 trakId);
    void updateRaySet(RaySet vec);
    void updateInfoAboutTrace(qint32 trackId, bool isReset);
    void dspNewData(RLSODSPDataMessage msg);

    void mapUpdate(QJsonDocument doc);
};

#endif // INCOMINGDATAHANDLER_H
