#include "incomingdatahandler.h"



IncomingDataHandler::IncomingDataHandler() :
    localHost(QUrl::fromUserInput(QLatin1String("127.0.0.1:14000")))
{
}

IncomingDataHandler::~IncomingDataHandler()
{

}

void IncomingDataHandler::doWork()
{

    pTcpSocketForMap = new QTcpSocket(this);
    connect(pTcpSocketForMap, &QTcpSocket::connected, this, &IncomingDataHandler::slotConnected);
    connect(pTcpSocketForMap, &QTcpSocket::disconnected, this, &IncomingDataHandler::disconnected);
    timeToConnectHost = new QTimer(this);
    connect(timeToConnectHost, &QTimer::timeout, this, &IncomingDataHandler::connectToHostOnTimeout);
    timeToConnectHost->start(1000);
}

void IncomingDataHandler::sendJsonDocument(QJsonDocument doc)
{
    if (pTcpSocketForMap->state() == QTcpSocket::ConnectedState) {
        pTcpSocketForMap->write(doc.toJson());
        pTcpSocketForMap->flush();
    }
}

void IncomingDataHandler::slotConnected()
{
    connect(pTcpSocketForMap, &QTcpSocket::readyRead, this, &IncomingDataHandler::readDataForMap);
}

void IncomingDataHandler::connectToHostOnTimeout()
{
    if (pTcpSocketForMap->state() != QTcpSocket::ConnectedState) {
        pTcpSocketForMap->connectToHost(localHost.host(), localHost.port(), QIODevice::ReadWrite);
    }
}


void IncomingDataHandler::readDataForMap()
{

    QJsonDocument document = QJsonDocument::fromJson(pTcpSocketForMap->readAll());

    emit mapUpdate(document);
}

void IncomingDataHandler::connectionError(QAbstractSocket::SocketError socketError)
{

    if (socketError ==  QAbstractSocket::ConnectionRefusedError ||
            socketError ==  QAbstractSocket::HostNotFoundError ||
            socketError ==  QAbstractSocket::SocketTimeoutError ||
            socketError ==  QAbstractSocket::NetworkError) {
        pTcpSocketForMap->connectToHost(localHost.host(), localHost.port(), QIODevice::ReadWrite);

    }
}

void IncomingDataHandler::disconnected()
{
    disconnect(pTcpSocketForMap, SIGNAL(readyRead()),this,SLOT(readDataForMap()));
}
