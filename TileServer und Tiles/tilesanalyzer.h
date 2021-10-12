#ifndef TILEANALYZER_H
#define TILEANALYZER_H

#include <QStringList>
#include <QDir>
#include <QJsonArray>

#include "threadfilereaders.h"
#include "tilescoordinats.h"

#include <array>

struct tileIndex{
    int first;
    int second;
};

class TilesAnalyzer
{
public:
    explicit TilesAnalyzer(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType);
    ~TilesAnalyzer();
    void operator=( const TilesAnalyzer& ) = delete;
    void analyzing(float &latitude, float &longtutude, int &layer, int &azm, QJsonArray *jsonArray, float &w1, float &h1, float &w2, float &h2, float &w3, float &h3, float &w4, float &p1_lat, float &p1_long, float &p2_lat, float &p2_long);
private:
    void searchTilesIndexs(float &currentLatitude,  float &currentLongitude,  int &layer);
    void findIndexsOfUnRenderedTiles(QJsonArray *jsonArray, QStringList *tilesToConvertAzm, int &layer, QString &pathToResultAzmTiles);
    void addWidthHeightAndLatLongToList(int &layer, float &w1, float &h1, float &w2, float &h2, float &w3, float &h3, float &w4, float &p1_lat, float &p1_long, float &p2_lat, float &p2_long);
private:
    void createConnections();

private:
    const QString *m_pathToSourceSvg;
    const QString *m_pathToRendedImage;
    const QString *m_fileType;

    QStringList *m_tilesToConvertAzm;
    int m_numTilesToConvertAzm;
    QDir *m_qDir;
    std::array<tileIndex, 9> *m_latAndLong;
    std::array<tileIndex, 9>::iterator m_total;
    const QString *m_slash;
    const QString *m_underscore;
    QString m_whiteJpg;

    ThreadImageRotator *m_threadFileReader;


    QString m_azm;
    QString m_layer;
    QString m_tileIndex;
    QString fullPathToTile;
    QString pathToResultAzmTiles;
    int m_index;

};



#endif // TILEANALYZER_H
