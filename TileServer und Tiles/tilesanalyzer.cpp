#include "tilesanalyzer.h"

#include <QDebug>

TilesAnalyzer::TilesAnalyzer(const QString &pathToSourceSvg, const QString &pathToRendedImage, const QString &fileType)
    : m_pathToSourceSvg(pathToSourceSvg)
    , m_pathToRendedImage(pathToRendedImage)
    , m_fileType(fileType)
    , m_tilesToConvertAzm(new std::list<QString>())
    , m_numTilesToConvertAzm(0)
    , m_qDir(new QDir())
    , m_latAndLong(new std::array<tileIndex, 9>())
    , m_total(m_latAndLong->end())
    , m_slash('/')
    , m_underscore('_')
    , m_threadFileReader(new ThreadImageRotator(pathToSourceSvg, pathToRendedImage, fileType, m_slash, nullptr))
    , m_index(0)
{
    m_whiteJpg.append(pathToRendedImage).append("/white").append(m_fileType);
}

TilesAnalyzer::~TilesAnalyzer()
{
    delete m_qDir;
    delete m_tilesToConvertAzm;
    delete m_latAndLong;
    delete m_threadFileReader;
}

void TilesAnalyzer::SearchTilesIndexs(const float &currentLatitude,const float &currentLongitude,const int &layer){
    //latitude - широта.  longtitude долгота; широта вверх. долгота вправо!!!!!
    //если currentLongitude <0 то отнимаем от 360 наше число. Так как 179.9|-180 а нам надо 179.9|181
    //    currentLongitude=currentLongitude<0 ? (360+currentLongitude) : currentLongitude;
    const std::vector<float> *currentLayerLatitudes=&latitudes.at(layer);
    const std::vector<float> *currentLayerLongtitudes=&longtitudes.at(layer);
    int startIndex=0;
    int lastIndexLat=latitudesVectorSize.at(layer);
    int centerIndexLat=centerLatitudesVector.at(layer);
    int difference=0;
    int lastIndexLongt=longtitudesVectorSize.at(layer);
    int centerIndexLong=centerLongtitudesVector.at(layer);
    //По долготе. долгота ВПРАВО!!!!!
    if (currentLongitude>=currentLayerLongtitudes->at(startIndex+1)
        &&currentLongitude<=currentLayerLongtitudes->at(lastIndexLongt-2))
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
    if (currentLatitude>=currentLayerLatitudes->at(startIndex+1)&&currentLatitude<=currentLayerLatitudes->at(lastIndexLat-4))
    {
        qInfo()<< "firstIf";
        while (startIndex<lastIndexLat)
        {
            difference=(lastIndexLat-startIndex)/2;
            if(difference==0)
            {
                if(currentLatitude>(currentLayerLatitudes->at(startIndex)))
                {
                    qInfo()<< "ret";
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
        qInfo()<< "no tiles if";
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
                {
                    qInfo()<< "smaller that last  index -1";
                    if(currentLatitude>currentLayerLatitudes->at(lastIndexLat-3))
                    {
                        m_latAndLong->operator[](0).second=lastIndexLat-3;
                        m_latAndLong->operator[](1).second=lastIndexLat-3;
                        m_latAndLong->operator[](2).second=lastIndexLat-3;
                        m_latAndLong->operator[](3).second=lastIndexLat-2;
                        m_latAndLong->operator[](4).second=lastIndexLat-2;
                        m_latAndLong->operator[](5).second=lastIndexLat-2;
                        m_latAndLong->operator[](6).second=-1;
                        m_latAndLong->operator[](7).second=-1;
                        m_latAndLong->operator[](8).second=-1;
                        qInfo()<< "fall";
                        return;
                    }
                    else
                    {
                        qInfo()<< "smaller that last  index -2";
                        m_latAndLong->operator[](0).second=lastIndexLat-2;
                        m_latAndLong->operator[](1).second=lastIndexLat-2;
                        m_latAndLong->operator[](2).second=lastIndexLat-2;
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
}

void TilesAnalyzer::FindIndexsOfUnRenderedTiles(QJsonArray *jsonArray, std::list<QString> *tilesToConvertAzm, int &layer, QString &pathToResultAzmTiles)
{
    const int &numOfTiles=numLatitudeTiles.at(layer);
    const QByteArray *hasMapWorldLayer=&hasMapWord.at(layer);
    for (std::array<tileIndex, 9>::iterator it=m_latAndLong->begin(); it!=m_total; ++it)
    {
        if (it->first<0||it->second<0)
        {
            jsonArray->replace(m_index, m_whiteJpg);
        }
        else
        {
            m_tileIndex.append(QString::number(it->first)).append(m_underscore).append(QString::number(it->second));
            //            qDebug()<< m_tileIndex;
            if (hasMapWorldLayer->at(it->first*numOfTiles+it->second))
            {
                fullPathToTile.append(pathToResultAzmTiles).append(m_tileIndex).append(m_fileType);
                if(!QFile::exists(fullPathToTile))
                {
                    tilesToConvertAzm->push_back(m_tileIndex);
                }
            }
            else
            {
                fullPathToTile.append(m_pathToSourceSvg).append(m_layer).append(m_slash).append(m_tileIndex).append(m_fileType);
            }
            jsonArray->replace(m_index, fullPathToTile);
            m_tileIndex.clear();
            fullPathToTile.clear();
        }
        m_index++;
    }
    m_index=0;
    //    qDebug()<<*jsonArray;
}

void TilesAnalyzer::AddWidthHeightAndLatLongToList(int &layer, float &w1, float &h1, float &w2, float &h2, float &w3, float &h3, float &w4, float &p1_lat, float &p1_long, float &p2_lat, float &p2_long)
{
    //check
    const std::vector<float> *width=&bottomAndTopDistance.at(layer);
    const std::vector<float> *height=&leftAndRightDistance.at(layer);
    const std::vector<float> *currentLayerLatitudes=&latitudes.at(layer);
    const std::vector<float> *currentLayerLongtitudes=&longtitudes.at(layer);
    //сначала смотрим по латитюду - широте, она вверх
    //потом делаем корректировку по лонгтитьюду
    //есть середина тайла не попадает ПОЛНОСТЬЮ то его координаты нулевые ( к Игорю)
    if (m_latAndLong->at(1).second==-1)
    {
        if (m_latAndLong->at(4).second==-1)
        {
            if (m_latAndLong->at(7).second==-1)//это если белый квардрат, вышли за пределы
            {
                h3=500.0f;
            }
            else//это если три верхних отрисовываются
            {
                h3=height->at(m_latAndLong->at(7).second);
            }
            p1_lat=0.0f;//то что белое инициализуем как у остального
            p2_lat=0.0f;
            h2=h3;

        }
        else//это если шесть верхних отрисовываются
        {
            h2=height->at(m_latAndLong->at(4).second);
            h3=height->at(m_latAndLong->at(7).second);
            p1_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
            p2_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second+1);
        }
        h1=h2;
    }
    else//это если первые отрисовывается
    {
        try {
            qDebug()<< "else1";
            h1=height->at(m_latAndLong->at(1).second);
            if (m_latAndLong->at(7).second==-1 )//последние за границей
            {
                qDebug()<< "if1";
                if (m_latAndLong->at(4).second==-1)//и середина тоже за границей массива
                {
                    h2=h1;
                    p1_lat=0.0f;
                    p2_lat=0.0f;
                }
                else//середина есть
                {
                    h2=height->at(m_latAndLong->at(4).second);
                    p1_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
                    p2_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second+1);
                }
                h3=h2;
            }
            else//есть все
            {
                h2=height->at(m_latAndLong->at(4).second);
                h3=height->at(m_latAndLong->at(7).second);
                p1_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second);
                p2_lat=currentLayerLatitudes->at(m_latAndLong->at(4).second+1);
            }
        }  catch (const std::out_of_range& e) {
            qDebug() << "Out of Range error. catched THIRD";
        }
    }
    qDebug()<< "lat";
    //делаем по лонгтитьюду->это вправо, у пары первая координата
    if (m_latAndLong->at(1).first==-1)
    {
        if (m_latAndLong->at(4).first==-1)
        {
            if (m_latAndLong->at(7).first==-1)//это если белый квардрат, вышли за пределы
            {
                w4=500.0f;
                w3=w4;
            }
            else//это если три правых отрисовываются
            {
                w3=width->at(m_latAndLong->at(7).first);
                w4=width->at(m_latAndLong->at(7).first+1);
            }
            w2=w3;//то что белое инициализуем как у остального
            p1_long=0.0f;
            p2_long=0.0f;

        }
        else//это если шесть правых отрисовываются
        {
            w2=width->at(m_latAndLong->at(4).first);
            w3=width->at(m_latAndLong->at(7).first);
            w4=width->at(m_latAndLong->at(7).first+1);
            p1_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
            p2_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first+1);
        }
        w1=w2;
    }
    else//это если первые отрисовывается
    {
        w1=width->at(m_latAndLong->at(1).first);
        w2=width->at(m_latAndLong->at(1).first+1);
        if (m_latAndLong->at(7).first==-1 )//последние за границей
        {
            if (m_latAndLong->at(4).first==-1)//и середина тоже за границей массива
            {
                w3=w2;
                p1_long=0.0f;
                p2_long=0.0f;
            }
            else//середина есть
            {
                w3=width->at(m_latAndLong->at(4).first+1);
                p1_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
                p2_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first+1);
            }
            w4=w3;
        }
        else//есть все
        {
            w3=width->at(m_latAndLong->at(4).first+1);
            w4=width->at(m_latAndLong->at(7).first+1);
            p1_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first);
            p2_long=currentLayerLongtitudes->at(m_latAndLong->at(4).first+1);
        }
    }
    qDebug()<<" p1(lat,lng)" << p1_lat << ";" << p1_long << " p2(lat,lng)" << p2_lat << ";" << p2_long;
//    qDebug()<<"w1: " << w1 << " h1: "<< h1 << " w2: " << w2 << " h2: " <<h2 << " w3: " << w3 << " h3: " << h3 << " w4: " << w4 << " p1(lat,lng)" << p1_lat << ";" << p1_long;
}

void TilesAnalyzer::Analyzing( float &latitude, float &longtutude, int &layer, int &azm,QJsonArray *jsonArray, float &w1, float &h1, float &w2, float &h2, float &w3, float &h3, float &w4, float &p1_lat, float &p1_long, float &p2_lat, float &p2_long)
{
    if (m_numTilesToConvertAzm>0)
    {
        m_tilesToConvertAzm->clear();
    }
    SearchTilesIndexs(latitude, longtutude, layer);
    int index=0;
    for (auto iter=m_latAndLong->cbegin(); iter!=m_latAndLong->cend(); ++iter)
    {
        qDebug()<< index << " = " << iter->first << " , " << iter->second;
        ++index;
    }
    m_layer=QString::number(layer);
    m_azm=QString::number(azm).rightJustified(3, '0', true);
    pathToResultAzmTiles.append(m_pathToRendedImage).append(m_layer).append(m_slash).append(m_azm).append(m_slash);
    m_qDir->mkdir(pathToResultAzmTiles);
    FindIndexsOfUnRenderedTiles(jsonArray, m_tilesToConvertAzm, layer, pathToResultAzmTiles);
    m_numTilesToConvertAzm=m_tilesToConvertAzm->size();
    if (m_numTilesToConvertAzm>0)
    {
        m_threadFileReader->GettingTilesToConvert(*m_tilesToConvertAzm, m_numTilesToConvertAzm, m_azm, m_layer);
    }
    AddWidthHeightAndLatLongToList(layer, w1, h1, w2, h2, w3, h3, w4, p1_lat, p1_long, p2_lat, p2_long);
    pathToResultAzmTiles.clear();
}
