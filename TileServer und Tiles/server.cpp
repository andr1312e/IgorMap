#include "server.h"

Server::Server(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType, QObject *parent)
    : QObject(parent)
    , m_serverIsFree(true)
    , m_tileAnalyzer(new TilesAnalyzer(pathToSourceSvg, pathToRendedImage, fileType))
    , m_parseError(new QJsonParseError())
    , m_tcpServer(new QTcpServer())
    , m_jsonObject(new QJsonObject)
    , m_jsonArray(new QJsonArray())
    , latitudeKey(QStringLiteral("latitude"))
    , longtitudeKey(QStringLiteral("longtitude"))
    , azimutKey(QStringLiteral("azimut"))
    , layerKey(QStringLiteral("layer"))
    , filePathsKey(QStringLiteral("filePaths"))
    , w1Key(QStringLiteral("w1"))
    , w2Key(QStringLiteral("w2"))
    , w3Key(QStringLiteral("w3"))
    , w4Key(QStringLiteral("w4"))
    , h1Key(QStringLiteral("h1"))
    , h2Key(QStringLiteral("h2"))
    , h3Key(QStringLiteral("h3"))
    , p1_latKey(QStringLiteral("p1_lat"))
    , p1_longKey(QStringLiteral("p1_long"))
    , p2_latKey(QStringLiteral("p2_lat"))
    , p2_longKey(QStringLiteral("p2_long"))
{
    resizeJsonArray();
    createConnections();
    startServer();
}

Server::~Server()
{
    delete m_tileAnalyzer;
    delete m_parseError;
    delete m_tcpServer;
    delete m_jsonObject;
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
    if (m_serverIsFree)
    {
        qInfo()<<"Сервер принял сообщение";
        const QJsonDocument jsonDoc=QJsonDocument::fromJson(m_tcpSocket->readAll(), m_parseError);
        if (m_parseError->error == noError)
        {
            if (jsonDoc.isObject())
            {
                m_serverIsFree=false;
                latitude=jsonDoc.operator[](latitudeKey).toDouble();
                longtitude=jsonDoc.operator[](longtitudeKey).toDouble();
                m_azimut=jsonDoc.operator[](azimutKey).toInt();
                m_layer=jsonDoc.operator[](layerKey).toInt();
                qInfo()<< "layer " << m_layer << " azimut " << m_azimut << " lat= " << latitude << " long " << longtitude;
                m_tileAnalyzer->analyzing(latitude, longtitude, m_layer, m_azimut, m_jsonArray, bottomLineTileWidth, bottomLineTileHeight, centerLineTileWidth, centerLineTileHeight, topLineTileWidth, topLineTileHeight, topTileWidth, centerTileBottomLatitude, centerTileBottomLongtitude, centerTileTopLatitude, centerTileTopLongtitude);
                jsonSend();
            }
        }
    }
}
void Server::logout()
{
    m_tcpSocket->close();
    m_serverIsFree=true;
}
void Server::error()
{
    Q_UNUSED(m_tcpSocket);
    m_serverIsFree=true;
    qInfo()<<"Connection Error";
}
void Server::jsonSend()
{
    m_jsonObject->insert(filePathsKey, *m_jsonArray);
    m_jsonObject->insert(w1Key, bottomLineTileWidth);
    m_jsonObject->insert(h1Key, bottomLineTileHeight);
    m_jsonObject->insert(w2Key, centerLineTileWidth);
    m_jsonObject->insert(h2Key, centerLineTileHeight);
    m_jsonObject->insert(w3Key, topLineTileWidth);
    m_jsonObject->insert(h3Key, topLineTileHeight);
    m_jsonObject->insert(w4Key, topTileWidth);

    m_jsonObject->insert(p1_latKey, centerTileBottomLatitude);
    m_jsonObject->insert(p1_longKey, centerTileBottomLongtitude);
    m_jsonObject->insert(p2_latKey, centerTileTopLatitude);
    m_jsonObject->insert(p2_longKey, centerTileTopLongtitude);

    const QByteArray jsonData = QJsonDocument(*m_jsonObject).toJson();
//    qDebug()<< jsonData;
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        m_tcpSocket->write(jsonData);
        m_tcpSocket->flush();
    }
    m_serverIsFree=true;
    //    qInfo()<<"Send to client";
}

void Server::resizeJsonArray()
{
    for (int i=0; i<9; i++)
    {
        m_jsonArray->insert(i, "");
    }
}

void Server::createConnections()
{
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &Server::login);
    connect(m_tcpServer, &QTcpServer::acceptError,
            this, &Server::error);
}

void Server::startServer()
{
    if(!m_tcpServer->listen(QHostAddress::LocalHost, 14000))
    {
        qInfo()<<"Сервер не может запуститься";//Can't load server
        qInfo()<<"Скорее всего, другой экземляр приложения запущен";//Other copy is started maybe
        m_tcpServer->close();
    }
    qInfo()<<m_tcpServer->serverAddress();
    qInfo()<<"Сервер запущен";//Server starts
}



