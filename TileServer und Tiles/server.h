#ifndef SERVER_H
#define SERVER_H

#include "tilesanalyzer.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(const QString &pathToSourceSvg, const QString &pathToRendedImage, const QString &fileType, QObject *parent);
    ~Server();
public Q_SLOTS:
    void OnLogin();
    void OnJsonGet();
    void OnLogout();
    void OnError();
    void OnJsonSend();
private:
    void ResizeJsonArray();
    void CreateConnections();
    void StartServer();
private:
    bool m_serverIsFree;
    TilesAnalyzer* const m_tileAnalyzer;
    float latitude;
    float longtitude;
    int m_azimut;
    int m_layer;
    QJsonParseError * const m_parseError;
    QTcpServer* const m_tcpServer;
    QTcpSocket* m_tcpSocket;
    QJsonObject* const m_jsonObject;
    const QJsonParseError::ParseError noError=QJsonParseError::NoError;
    QJsonArray * const m_jsonArray;
private:
    float bottomLineTileWidth;
    float bottomLineTileHeight;
    float centerLineTileWidth;
    float centerLineTileHeight;
    float topLineTileWidth;
    float topLineTileHeight;
    float topTileWidth;
    float centerTileBottomLatitude;
    float centerTileBottomLongtitude;
    float centerTileTopLatitude;
    float centerTileTopLongtitude;
private:
    const QString latitudeKey;
    const QString longtitudeKey;
    const QString azimutKey;
    const QString layerKey;

    const QString filePathsKey;
    const QString w1Key;
    const QString w2Key;
    const QString w3Key;
    const QString w4Key;
    const QString h1Key;
    const QString h2Key;
    const QString h3Key;

    const QString p1_latKey;
    const QString p1_longKey;
    const QString p2_latKey;
    const QString p2_longKey;
};

#endif // SERVER_H
