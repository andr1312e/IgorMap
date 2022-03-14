#include "server.h"

Server::Server(const QString &pathToSourceSvg,const QString &pathToRendedImage,const QString &fileType, QObject *parent)
    : QObject(parent)
    , m_serverIsFree(true)
    , m_tileAnalyzer(new TilesAnalyzer(pathToSourceSvg, pathToRendedImage, fileType))
    , m_parseError(new QJsonParseError())
    , m_tcpServer(new QTcpServer())
    , m_jsonObject(new QJsonObject)
    , m_jsonArray(new QJsonArray())
    , latitudeKey(QLatin1String("latitude"))
    , longtitudeKey(QLatin1String("longtitude"))
    , azimutKey(QLatin1String("azimut"))
    , layerKey(QLatin1String("layer"))
    , filePathsKey(QLatin1String("filePaths"))
    , w1Key(QLatin1String("w1"))
    , w2Key(QLatin1String("w2"))
    , w3Key(QLatin1String("w3"))
    , w4Key(QLatin1String("w4"))
    , h1Key(QLatin1String("h1"))
    , h2Key(QLatin1String("h2"))
    , h3Key(QLatin1String("h3"))
    , p1_latKey(QLatin1String("p1_lat"))
    , p1_longKey(QLatin1String("p1_long"))
    , p2_latKey(QLatin1String("p2_lat"))
    , p2_longKey(QLatin1String("p2_long"))
{
    ResizeJsonArray();
    CreateConnections();
    StartServer();
}

Server::~Server()
{
    delete m_tileAnalyzer;
    delete m_parseError;
    delete m_tcpServer;
    delete m_jsonObject;
}

void Server::OnLogin()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    if (QAbstractSocket::ConnectedState == m_tcpSocket->state())
    {
        connect(m_tcpSocket, &QTcpSocket::disconnected,this, &Server::OnLogout);
        connect(m_tcpSocket, &QTcpSocket::readyRead,this, &Server::OnJsonGet);
    }
}
void Server::OnJsonGet()
{
    if (m_serverIsFree)
    {
//        qInfo()<<QStringLiteral("Сервер принял сообщение");
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
                m_tileAnalyzer->Analyzing(latitude, longtitude, m_layer, m_azimut, m_jsonArray, bottomLineTileWidth, bottomLineTileHeight, centerLineTileWidth, centerLineTileHeight, topLineTileWidth, topLineTileHeight, topTileWidth, centerTileBottomLatitude, centerTileBottomLongtitude, centerTileTopLatitude, centerTileTopLongtitude);
                OnJsonSend();
            }
        }
    }
}
void Server::OnLogout()
{
    m_tcpSocket->close();
    m_serverIsFree=true;
}
void Server::OnError()
{
    Q_UNUSED(m_tcpSocket);
    m_serverIsFree=true;
    qInfo()<<"Connection Error";
}
void Server::OnJsonSend()
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

    if (QAbstractSocket::ConnectedState == m_tcpSocket->state()) {
        m_tcpSocket->write(jsonData);
        m_tcpSocket->flush();
    }
    m_serverIsFree=true;

}

void Server::ResizeJsonArray()
{
    for (int i=0; i<9; i++)
    {
        m_jsonArray->insert(i, QLatin1String());
    }
}

void Server::CreateConnections()
{
    connect(m_tcpServer, &QTcpServer::newConnection,this, &Server::OnLogin);
    connect(m_tcpServer, &QTcpServer::acceptError,this, &Server::OnError);
}

void Server::StartServer()
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



