#include "tilesanalyzer.h"

#include <QDebug>

TilesAnalyzer::TilesAnalyzer(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType)
    : m_pathToSourceSvg(pathToSourceSvg)
    , m_pathToRendedImage(pathToRendedImage)
    , m_fileType(fileType)
    , m_tilesToConvertAzm(new QStringList())
    , m_numTilesToConvertAzm(0)
    , m_qDir(new QDir())
    , m_latAndLong(new std::array<tileIndex, 9>())
    , m_total(m_latAndLong->end())
    , m_slash(new QString(QStringLiteral("/")))
    , m_whiteJpg(new QString(QStringLiteral("/noAzm/white")))
    , m_underscore(new QString(QStringLiteral("_")))
    , m_threadFileReader(new ThreadImageRotator(pathToSourceSvg, pathToRendedImage, fileType, m_slash, nullptr))
    , m_index(0)
{
}

TilesAnalyzer::~TilesAnalyzer()
{
    delete m_whiteJpg;
    delete m_slash;
    delete m_qDir;
    delete m_tilesToConvertAzm;
    delete m_latAndLong;
    delete m_threadFileReader;
}

void TilesAnalyzer::searchTilesIndexs(float &currentLatitude, float &currentLongitude,int &layer){
    //latitude - широта.  longtitude долгота; широта вверх. долгота вправо!!!!!
    //если currentLongitude <0 то отнимаем от 360 наше число. Так как 179.9|-180 а нам надо 179.9|181
    //    currentLongitude=currentLongitude<0 ? (360+currentLongitude) : currentLongitude;
    const QVector<float> *currentLayerLatitudes=&latitudes.at(layer);
    const QVector<float> *currentLayerLongtitudes=&longtitudes.at(layer);
    int startIndex=0, lastIndexLat=latitudesVectorSize.at(layer), centerIndexLat=centerLatitudesVector.at(layer), difference, lastIndexLongt=longtitudesVectorSize.at(layer), centerIndexLong=centerLongtitudesVector.at(layer);
    //По долготе. долгота ВПРАВО!!!!!
    if (currentLongitude>=currentLayerLongtitudes->at(startIndex+1)&&currentLongitude<=currentLayerLongtitudes->at(lastIndexLongt-2))
    {
        while (startIndex<lastIndexLongt)
        {
            difference=(lastIndexLongt-startIndex)/2;
            if(difference==0)
            {
                if (currentLongitude>(currentLayerLongtitudes->at(startIndex)))
                {
                    m_latAndLong->operator[](0).first=startIndex-1;
                    m_latAndLong->operator[](1).first=startIndex;
                    m_latAndLong->operator[](2).first=lastIndexLongt;
                    m_latAndLong->operator[](3).first=startIndex-1;
                    m_latAndLong->operator[](4).first=startIndex;
                    m_latAndLong->operator[](5).first=lastIndexLongt;
                    m_latAndLong->operator[](6).first=startIndex-1;
                    m_latAndLong->operator[](7).first=startIndex;
                    m_latAndLong->operator[](8).first=lastIndexLongt;
                }
                else
                {
                    m_latAndLong->operator[](0).first=startIndex;
                    m_latAndLong->operator[](1).first=lastIndexLongt;
                    m_latAndLong->operator[](2).first=startIndex+2;
                    m_latAndLong->operator[](3).first=startIndex;
                    m_latAndLong->operator[](4).first=lastIndexLongt;
                    m_latAndLong->operator[](5).first=startIndex+2;
                    m_latAndLong->operator[](6).first=startIndex;
                    m_latAndLong->operator[](7).first=lastIndexLongt;
                    m_latAndLong->operator[](8).first=startIndex+2;
                }
                break;
            }
            else
            {
                if(currentLongitude>currentLayerLongtitudes->at(centerIndexLong))
                {
                    startIndex=centerIndexLong;
                    centerIndexLong=centerIndexLong+(lastIndexLongt-startIndex)/2;
                }
                else
                {
                    lastIndexLongt=centerIndexLong;
                    centerIndexLong=centerIndexLong-(lastIndexLongt-startIndex)/2;
                }
            }
        }
    }
    else
    {
        if (currentLongitude<=leftBorderLongtitude ||currentLongitude>=rightBorderLongtitude)
        {
            m_latAndLong->operator[](0).first=-1;
            m_latAndLong->operator[](1).first=-1;
            m_latAndLong->operator[](2).first=-1;
            m_latAndLong->operator[](3).first=-1;
            m_latAndLong->operator[](4).first=-1;
            m_latAndLong->operator[](5).first=-1;
            m_latAndLong->operator[](6).first=-1;
            m_latAndLong->operator[](7).first=-1;
            m_latAndLong->operator[](8).first=-1;
            return;
        }
        else
            if (currentLongitude<=currentLayerLongtitudes->at(startIndex))
            {
                m_latAndLong->operator[](0).first=-1;
                m_latAndLong->operator[](1).first=-1;
                m_latAndLong->operator[](2).first=0;
                m_latAndLong->operator[](3).first=-1;
                m_latAndLong->operator[](4).first=-1;
                m_latAndLong->operator[](5).first=0;
                m_latAndLong->operator[](6).first=-1;
                m_latAndLong->operator[](7).first=-1;
                m_latAndLong->operator[](8).first=0;
            }
            else
                if(currentLongitude<=currentLayerLongtitudes->at(startIndex+1))
                {
                    m_latAndLong->operator[](0).first=-1;
                    m_latAndLong->operator[](1).first=0;
                    m_latAndLong->operator[](2).first=1;
                    m_latAndLong->operator[](3).first=-1;
                    m_latAndLong->operator[](4).first=0;
                    m_latAndLong->operator[](5).first=1;
                    m_latAndLong->operator[](6).first=-1;
                    m_latAndLong->operator[](7).first=0;
                    m_latAndLong->operator[](8).first=1;
                }
                else
                    if(currentLongitude>currentLayerLongtitudes->at(lastIndexLat-1))
                    {
                        m_latAndLong->operator[](0).first=lastIndexLat-1;
                        m_latAndLong->operator[](1).first=-1;
                        m_latAndLong->operator[](2).first=-1;
                        m_latAndLong->operator[](3).first=lastIndexLat-1;
                        m_latAndLong->operator[](4).first=-1;
                        m_latAndLong->operator[](5).first=-1;
                        m_latAndLong->operator[](6).first=lastIndexLat-1;
                        m_latAndLong->operator[](7).first=-1;
                        m_latAndLong->operator[](8).first=-1;
                    }
                    else
                    {
                        m_latAndLong->operator[](0).first=lastIndexLat-2;
                        m_latAndLong->operator[](1).first=lastIndexLat-1;
                        m_latAndLong->operator[](2).first=-1;
                        m_latAndLong->operator[](3).first=lastIndexLat-2;
                        m_latAndLong->operator[](4).first=lastIndexLat-1;
                        m_latAndLong->operator[](5).first=-1;
                        m_latAndLong->operator[](6).first=lastIndexLat-2;
                        m_latAndLong->operator[](7).first=lastIndexLat-1;
                        m_latAndLong->operator[](8).first=-1;
                    }
    }
    startIndex=0;
    //проверка границы по широте. ШИРОТА ВВЕРХ!!!!!!!!!!!
    if (currentLatitude>=currentLayerLatitudes->at(startIndex+1)&&currentLatitude<=currentLayerLatitudes->at(lastIndexLat-2))
    {
        while (startIndex<lastIndexLat)
        {
            difference=(lastIndexLat-startIndex)/2;
            if(difference==0)
            {
                if(currentLatitude>(currentLayerLatitudes->at(startIndex)))
                {
                    m_latAndLong->operator[](0).second=startIndex-1;
                    m_latAndLong->operator[](1).second=startIndex-1;
                    m_latAndLong->operator[](2).second=startIndex-1;
                    m_latAndLong->operator[](3).second=startIndex;
                    m_latAndLong->operator[](4).second=startIndex;
                    m_latAndLong->operator[](5).second=startIndex;
                    m_latAndLong->operator[](6).second=lastIndexLat;
                    m_latAndLong->operator[](7).second=lastIndexLat;
                    m_latAndLong->operator[](8).second=lastIndexLat;
                }
                else
                {
                    m_latAndLong->operator[](0).second=startIndex;
                    m_latAndLong->operator[](1).second=startIndex;
                    m_latAndLong->operator[](2).second=startIndex;
                    m_latAndLong->operator[](3).second=lastIndexLat;
                    m_latAndLong->operator[](4).second=lastIndexLat;
                    m_latAndLong->operator[](5).second=lastIndexLat;
                    m_latAndLong->operator[](6).second=startIndex+2;
                    m_latAndLong->operator[](7).second=startIndex+2;
                    m_latAndLong->operator[](8).second=startIndex+2;
                }
                return;
            }
            else
            {
                if(currentLatitude>currentLayerLatitudes->at(centerIndexLat))
                {
                    startIndex=centerIndexLat;
                    centerIndexLat=centerIndexLat+difference;
                }
                else
                {
                    lastIndexLat=centerIndexLat;
                    centerIndexLat=centerIndexLat-difference;
                }
            }

        }
    }
    else
    {
        if (currentLatitude<bottomBorderLatitude||currentLatitude>topBorderLatitude)
        {
            m_latAndLong->operator[](0).first=-1;
            m_latAndLong->operator[](1).first=-1;
            m_latAndLong->operator[](2).first=-1;
            m_latAndLong->operator[](3).first=-1;
            m_latAndLong->operator[](4).first=-1;
            m_latAndLong->operator[](5).first=-1;
            m_latAndLong->operator[](6).first=-1;
            m_latAndLong->operator[](7).first=-1;
            m_latAndLong->operator[](8).first=-1;
            return;
        }
        else
        {
            if (currentLatitude<=currentLayerLatitudes->at(startIndex))
            {
                m_latAndLong->operator[](0).second=-1;
                m_latAndLong->operator[](1).second=-1;
                m_latAndLong->operator[](2).second=-1;
                m_latAndLong->operator[](3).second=-1;
                m_latAndLong->operator[](4).second=-1;
                m_latAndLong->operator[](5).second=-1;
                m_latAndLong->operator[](6).second=0;
                m_latAndLong->operator[](7).second=0;
                m_latAndLong->operator[](8).second=0;
                return;
            }
            else
                if(currentLatitude<=currentLayerLatitudes->at(startIndex+1))
                {
                    m_latAndLong->operator[](0).second=-1;
                    m_latAndLong->operator[](1).second=-1;
                    m_latAndLong->operator[](2).second=-1;
                    m_latAndLong->operator[](3).second=0;
                    m_latAndLong->operator[](4).second=0;
                    m_latAndLong->operator[](5).second=0;
                    m_latAndLong->operator[](6).second=1;
                    m_latAndLong->operator[](7).second=1;
                    m_latAndLong->operator[](8).second=1;
                    return;
                }
                else
                    if(currentLatitude<currentLayerLatitudes->at(lastIndexLat-1))
                    {
                        m_latAndLong->operator[](0).second=lastIndexLat-2;
                        m_latAndLong->operator[](1).second=lastIndexLat-2;
                        m_latAndLong->operator[](2).second=lastIndexLat-2;
                        m_latAndLong->operator[](3).second=lastIndexLat-1;
                        m_latAndLong->operator[](4).second=lastIndexLat-1;
                        m_latAndLong->operator[](5).second=lastIndexLat-1;
                        m_latAndLong->operator[](6).second=-1;
                        m_latAndLong->operator[](7).second=-1;
                        m_latAndLong->operator[](8).second=-1;
                        return;
                    }
                    else
                    {
                        m_latAndLong->operator[](0).second=lastIndexLat-1;
                        m_latAndLong->operator[](1).second=lastIndexLat-1;
                        m_latAndLong->operator[](2).second=lastIndexLat-1;
                        m_latAndLong->operator[](3).second=-1;
                        m_latAndLong->operator[](4).second=-1;
                        m_latAndLong->operator[](5).second=-1;
                        m_latAndLong->operator[](6).second=-1;
                        m_latAndLong->operator[](7).second=-1;
                        m_latAndLong->operator[](8).second=-1;
                        return;
                    }
        }
    }
}

void TilesAnalyzer::findIndexsOfUnRenderedTiles(QJsonArray *jsonArray, QStringList *tilesToConvertAzm, int &layer, QString &pathToResultAzmTiles)
{
    const int &numOfTiles=numLatitudeTiles.at(layer);
    const QByteArray *hasMapWorldLayer=&hasMapWord.at(layer);
    for (std::array<tileIndex, 9>::iterator it=m_latAndLong->begin(); it!=m_total; ++it)
    {
        if (it->first<0||it->second<0)
        {
           jsonArray->replace(m_index, *m_pathToRendedImage+m_layer+*m_whiteJpg+*m_fileType);
        }
        else
        {
            m_tileIndex=QString::number(it->first)+*m_underscore+ QString::number(it->second);
            qDebug()<< m_tileIndex;
            if (hasMapWorldLayer->at(it->first*numOfTiles+it->second))
            {
                fullPathToTile=pathToResultAzmTiles+*m_slash+m_tileIndex+*m_fileType;
                if(!QFile::exists(fullPathToTile))
                {
                    tilesToConvertAzm->append(m_tileIndex);
                }
            }
            else
            {
                fullPathToTile=*m_pathToSourceSvg+m_layer+*m_slash+m_tileIndex+*m_fileType;
            }
            jsonArray->replace(m_index, fullPathToTile);

        }
        m_index++;
    }
    m_index=0;
    qDebug()<<*jsonArray;
}

void TilesAnalyzer::addWidthHeightAndLatLongToList(int &layer, float &w1, float &h1, float &w2, float &h2, float &w3, float &h3, float &w4, float &p1_lat, float &p1_long, float &p2_lat, float &p2_long)
{
    //check
    const QVector<float> *width=&bottomAndTopDistance.at(layer);
    const QVector<float> *height=&leftAndRightDistance.at(layer);
    const QVector<float> *currentLayerLatitudes=&latitudes.at(layer);
    const QVector<float> *currentLayerLongtitudes=&longtitudes.at(layer);
    if (m_latAndLong->at(1).first==-1|| m_latAndLong->at(1).second==-1)
    {
        w1=900.0f;
        h1=530.0f;
        if (m_latAndLong->at(4).first==-1 || m_latAndLong->at(4).second==-1)
        {
            w2=900.0f;
            h2=900.0f;

            p1_lat=900.0f;
            p1_long=900.0f;

            p2_lat=900.0f;
            p2_long=900.0f;

            if (m_latAndLong->at(7).first==-1||m_latAndLong->at(7).second==-1 )
            {
                w3=900.0f;
                h3=900.0f;
                w4=900.0f;
            }
            else
            {
                w3=width->at(m_latAndLong->at(7).second);
                h3=height->at(m_latAndLong->at(7).second);
                w4=width->at(m_latAndLong->at(7).second+1);
            }
        }
        else
        {
            w2=width->at(m_latAndLong->at(4).second);
            h2=height->at(m_latAndLong->at(4).second);
            w3=width->at(m_latAndLong->at(7).second);
            h3=height->at(m_latAndLong->at(7).second);
            w4=width->at(m_latAndLong->at(7).second+1);
            p1_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
            p1_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
            p2_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second+1);
            p2_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first+1);
        }
    }
    else
    {
        w1=width->at(m_latAndLong->at(1).second);
        h1=height->at(m_latAndLong->at(1).second);
        w2=width->at(m_latAndLong->at(1).second+1);
        if (m_latAndLong->at(7).first==-1)
        {
            if (m_latAndLong->at(4).first==-1)
            {
                h2=900.0f;

                w3=900.0f;
                h3=900.0f;

                w4=900.0f;

                p1_lat=0.0f;
                p1_long=0.0f;

                p2_lat=0.0f;
                p2_long=0.0f;
            }
            else
            {
                h2=height->at(m_latAndLong->at(4).second);
                w3=width->at(m_latAndLong->at(4).second+1);
                h3=900.0f;
                w4=900.0f;
                p1_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
                p1_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
                //проверить
                p2_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
                p2_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
            }
        }
        else
        {
            h2=height->at(m_latAndLong->at(4).second);
            w3=width->at(m_latAndLong->at(7).second);
            h3=height->at(m_latAndLong->at(7).second);
            w4=width->at(m_latAndLong->at(7).second+1);
            p1_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
            p1_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
            p2_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second+1);
            p2_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first+1);
        }
    }
//    qDebug()<< "data " << " w1= " << w1 << " h1= " << h1 << " w2= " << w2 << " h2= " << h2 << " w3= " << w3 << " h3= " << h3 << " w4= " << w4;
//    qDebug()<< "2 points " << " 1 lat " << p1_lat << " 1 long " << p1_long << " 2 lat " << p2_lat  << " 2 long " << p2_long;
}

void TilesAnalyzer::analyzing(float &latitude, float &longtutude, int &layer, int &azm,QJsonArray *jsonArray, float &w1, float &h1, float &w2, float &h2, float &w3, float &h3, float &w4, float &p1_lat, float &p1_long, float &p2_lat, float &p2_long)
{
    if (m_numTilesToConvertAzm>0)
    {
        m_tilesToConvertAzm->clear();
    }
//    qInfo()<<"Начало работы программы";
    searchTilesIndexs(latitude, longtutude, layer);
    m_layer=QString::number(layer);
    m_azm=QString::number(azm).rightJustified(3, '0', true);
    pathToResultAzmTiles=*m_pathToRendedImage+m_layer+*m_slash+m_azm;
    m_qDir->mkdir(pathToResultAzmTiles);
    findIndexsOfUnRenderedTiles(jsonArray, m_tilesToConvertAzm, layer, pathToResultAzmTiles);
//    qDebug()<<"Тайлы которые будут возвращены" << *jsonArray;
//    qDebug()<<*m_tilesToConvertAzm;
    m_numTilesToConvertAzm=m_tilesToConvertAzm->size();
    if (m_numTilesToConvertAzm>0)
    {
        m_threadFileReader->gettingTilesToConvert(*m_tilesToConvertAzm, m_numTilesToConvertAzm, m_azm, m_layer);
    }
    addWidthHeightAndLatLongToList(layer, w1, h1, w2, h2, w3, h3, w4, p1_lat, p1_long, p2_lat, p2_long);
}
