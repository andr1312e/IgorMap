#ifndef INCOMINGDATAHANDLER_H
#define INCOMINGDATAHANDLER_H

#include <QTcpSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QTimer>

#include <CommonEntities/global.h>


class IncomingDataHandler : public QObject
{
    Q_OBJECT

public:
    IncomingDataHandler();
    ~IncomingDataHandler();


public slots:
    void doWork();
    void sendJsonDocument(QJsonDocument doc);

private:

    timeval lastMsgTime;

    QTcpSocket *pTcpSocketForMap;
    const QUrl localHost;

    QTimer *timeToConnectHost;

protected:


private slots:
    void readDataForMap();
    void connectionError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void slotConnected();

    void connectToHostOnTimeout();

signals:
    void mapUpdate(QJsonDocument doc);

};

#endif // INCOMINGDATAHANDLER_H
