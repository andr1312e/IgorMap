#include "server.h"
#include <QDataStream>
#include <QThread>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <program.h>
#define QT_NO_INFO_OUTPUT
Server::Server(Program &program, QObject *parent)
    : QObject(parent)
    , m_jsonData(new QByteArray())
{
    m_parseError=new QJsonParseError();
    m_object=new QJsonObject();
    m_program=&program;
    m_tcpServer= new QTcpServer(this);
    connect(m_program, &Program::sendToServer,
            this, &Server::jsonSend);
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &Server::login);
    connect(m_tcpServer, &QTcpServer::acceptError,
            this, &Server::error);
    if(!m_tcpServer->listen(QHostAddress::LocalHost, 10000))
    {
        qInfo()<<"Сервер не может запуститься";//Can't load server
        qInfo()<<"Скорее всего, другой экземляр приложения запущен";//Other copy is started maybe
        m_tcpServer->close();
    }
    qInfo()<<m_tcpServer->serverAddress();
    qInfo()<<"Сервер запущен";//Server starts
}

Server::~Server()
{
    delete m_jsonData;
    delete m_parseError;
    delete m_object;
    delete m_tcpServer;
}

void Server::login()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        connect(m_tcpSocket, &QTcpSocket::disconnected,
                this, &Server::logout
                );
        connect(m_tcpSocket, &QTcpSocket::readyRead,
                this, &Server::jsonGet
                );
    }
}
void Server::jsonGet()
{
    const QJsonDocument jsonDoc=QJsonDocument::fromJson(m_tcpSocket->readAll(), m_parseError);
    *m_jsonData=jsonDoc.toJson();
    if (m_parseError->error == QJsonParseError::NoError)
        if (jsonDoc.isObject())
            emit Server::execute(jsonDoc.object());
}
void Server::logout()
{
    m_tcpSocket->close();
}
void Server::error()
{
    Q_UNUSED(m_tcpSocket);
    qInfo()<<"Connection Error";
}
void Server::execute(const QJsonObject &message)
{
//    qInfo()<<"Сервер принял сообщение";//Server get message
    QVector<float> *coords=new QVector<float>(2);
    coords->operator[](0)=message.operator[]("latitude").toDouble();
    coords->operator[](1)=message.operator[]("longtitude").toDouble();
    int azimut=message.operator[]("azimut").toInt();
    int layer=message.operator[]("layer").toInt();
    bool repaintNeed=message.operator[]("repaint").toBool();
    m_program->executing(*coords, layer, azimut, repaintNeed);
}
void Server::jsonSend(QStringList &data)
{
    const QByteArray jsonData = QJsonDocument(makeJson(data)).toJson();
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        m_tcpSocket->write(jsonData);
        m_tcpSocket->flush();
    }
//    qInfo()<<"Send to client";
}
QJsonObject Server::makeJson(QStringList &data)
{
    QJsonArray arr = QJsonArray::fromStringList(data);
    (*m_object)["filePaths"] = arr;
    (*m_object)["w1"] = data.at(0).toFloat();
    (*m_object)["h1"] = data.at(1).toFloat();
    (*m_object)["w2"] = data.at(2).toFloat();
    (*m_object)["h2"] = data.at(3).toFloat();
    (*m_object)["w3"] = data.at(4).toFloat();
    (*m_object)["h3"] = data.at(5).toFloat();
    (*m_object)["w4"] = data.at(6).toFloat();
    (*m_object)["lat"] = data.at(7).toFloat();
    (*m_object)["long"] = data.at(8).toFloat();
    qInfo()<<"Json Created";
    return *m_object;
}



