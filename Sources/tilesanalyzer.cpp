#include "tilesanalyzer.h"

#include <QDebug>
TilesAnalyzer::TilesAnalyzer(QString &pathToSourceSvg, QString& pathToRendedImage, QString &fileType)
    :m_pathToSourceSvg(&pathToSourceSvg)
    ,m_pathToRendedImage(&pathToRendedImage)
    ,m_fileType(&fileType)
    ,m_azm(new QString())
    ,m_directory(new QDir())
    ,m_layer(new QString())
    ,m_tilesToReturn(new QStringList())
    ,m_tilesToConvertNoAzm(new QStringList())
    ,m_tilesToConvertAzm(new QStringList())
    ,m_numAzm(0)
{
    m_latAndLong=new QVector <QPair<int, int>>(9);
}

TilesAnalyzer::~TilesAnalyzer()
{
    delete m_tilesToConvertAzm;
    delete m_tilesToReturn;
    delete m_tilesToConvertNoAzm;
    delete m_directory;
    delete m_layer;
    delete m_azm;
}
void TilesAnalyzer::searchIndices(  float currentLatitude,   float currentLongitude,int &layer){
    //latitude - широта.  longtitude долгота; широта вверх. долгота вправо!!!!!
    //если currentLongitude <0 то отнимаем от 360 наше число. Так как 179.9|-180 а нам надо 179.9|181
    currentLongitude=currentLongitude<0 ? (360+currentLongitude) : currentLongitude;
    int startIndex=0, lastIndexLat=latitudesVectorSize[layer], centerIndexLat=centerLatitudesVector[layer], difference, lastIndexLongt=longtitudesVectorSize[layer], centerIndexLong=centerLongtitudesVector[layer];
    //По долготе. долгота ВПРАВО!!!!!
    if (currentLongitude>=longtitudes[layer][startIndex+1]&&currentLongitude<=longtitudes[layer][lastIndexLongt-2])
    {
        while (startIndex<lastIndexLongt)
        {
            difference=(lastIndexLongt-startIndex)/2;
            if(difference==0)
            {
                if (currentLongitude>(longtitudes[layer][startIndex]))
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
                if(currentLongitude>longtitudes[layer][centerIndexLong])
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
            if (currentLongitude<=longtitudes[layer][startIndex])
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
                if(currentLongitude<=longtitudes[layer][startIndex+1])
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
                    if(currentLongitude>longtitudes[layer][lastIndexLat-1])
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
                    }m_layer
    }
    startIndex=0;
    //проверка границы по широте. ШИРОТА ВВЕРХ!!!!!!!!!!!
    if (currentLatitude>=latitudes[layer][startIndex+1]&&currentLatitude<=latitudes[layer][lastIndexLat-2])
    {
        while (startIndex<lastIndexLat)
        {
            difference=(lastIndexLat-startIndex)/2;
            if(difference==0)
            {
                if(currentLatitude>(latitudes[layer][startIndex]))
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
                if(currentLatitude>latitudes[layer][centerIndexLat])
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
            if (currentLatitude<=latitudes[layer][startIndex])
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
                if(currentLatitude<=latitudes[layer][startIndex+1])
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
                    if(currentLatitude<latitudes[layer][lastIndexLat-1])
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
void TilesAnalyzer::findIndexsOfUnRenderedTiles(QStringList &tilesToReturn, QStringList &tilesToConvertNoAzm, QStringList &tilesToConvertAzm, int &layer)
{
    QStringList listOfRenderedNoAzmTiles, listOfRenderedAzmTiles;
    int numOfTiles=numLatitudeTiles[layer];
    QString tile, fullPath;
    for (int i=0; i<9; i++)
    {
        if (m_latAndLong->operator [](i).first<0||m_latAndLong->operator[](i).second<0)
        {
            tilesToReturn.append(*m_pathToRendedImage+m_layer+"/noAzm/white"+*m_fileType);
        }
        else
        {
            tile=QString::number(m_latAndLong->operator[](i).first)+"_"+ QString::number(m_latAndLong->operator[](i).second);
            if (hasMapWord[layer][m_latAndLong->operator[](i).first*numOfTiles+m_latAndLong->operator[](i).second])
            {
                fullPath=*m_pathToRendedImage+m_layer+"/"+m_azm+"/"+tile+*m_fileType;
                if(!QFileInfo::exists(fullPath))
                {
                    tilesToConvertAzm.append(tile);
                }
            }
            else
            {
                fullPath=*m_pathToRendedImage+m_layer+"/noAzm/"+tile+*m_fileType;
                if(!QFileInfo::exists(fullPath))
                {
                    tilesToConvertNoAzm.append(tile);
                }
            }
            tilesToReturn.append(fullPath);
        }
    }
}
void TilesAnalyzer::findIndexsOfTilesToRepaint(QStringList &tilesToReturn, QStringList &tilesToConvertNoAzm, QStringList &tilesToConvertAzm, int &layer)
{
    QStringList listOfRenderedNoAzmTiles, listOfRenderedAzmTiles;
    int numOfTiles=numLatitudeTiles[layer];
    QString tile, fullPath;
    for (int i=0; i<9; i++)
    {
        if (m_latAndLong->operator[](i).first<0||m_latAndLong->operator[](i).second<0)
        {
            tilesToReturn.append(*m_pathToRendedImage+m_layer+"/noAzm/white"+*m_fileType);
        }
        else
        {
            tile=QString::number(m_latAndLong->operator[](i).first)+"_"+ QString::number(m_latAndLong->operator[](i).second);
            if (hasMapWord[layer][m_latAndLong->operator[](i).first*numOfTiles+m_latAndLong->operator[](i).second])
            {
                fullPath=*m_pathToRendedImage+m_layer+"/"+m_azm+"/"+tile+*m_fileType;
                tilesToConvertAzm.append(tile);
            }
            else
            {
                fullPath=*m_pathToRendedImage+m_layer+"/noAzm/"+tile+*m_fileType;
                tilesToConvertNoAzm.append(tile);
            }
            tilesToReturn.append(fullPath);
        }
    }
}
void TilesAnalyzer::addWidthHeightAndLatLongToList(QStringList &tilesToReturn,  int &layer)
{
    //check
    const QVector<float> *width=&bottomAndTopDistance.operator[](layer);
    const QVector<float> *height=&leftAndRightDistance.operator[](layer);
    float distance;
    if (m_latAndLong->operator [](2).second==-1)
    {
        tilesToReturn.append(QString::number(0));
        tilesToReturn.append(QString::number(0));
        if (m_latAndLong->operator [](5).second==-1)
        {
            tilesToReturn.append(QString::number(0));
            tilesToReturn.append(QString::number(0));
            if (m_latAndLong->operator [](8).second==-1)
            {
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
            }
            else
            {
                distance=(width->operator [](m_latAndLong->operator [](8).second));
                        tilesToReturn.append(QString::number(distance, 'g' ));
                distance=(height->operator [](m_latAndLong->operator [](8).second));
                        tilesToReturn.append(QString::number(distance, 'g' ));
                distance=(width->operator [](m_latAndLong->operator [](8).second+1));
                        tilesToReturn.append(QString::number(distance, 'g' ));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
            }
        }
        else
        {
            distance=(width->operator [](m_latAndLong->operator [](5).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(height->operator [](m_latAndLong->operator [](5).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(width->operator [](m_latAndLong->operator [](8).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(height->operator [](m_latAndLong->operator [](8).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(width->operator [](m_latAndLong->operator [](8).second+1));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            tilesToReturn.append(QString::number(longtitudes[layer][m_latAndLong->operator [](4).first], 'g' ));
                    tilesToReturn.append(QString::number(latitudes[layer][m_latAndLong->operator [](4).second], 'g' ));
        }
    }
    else
    {
        distance=(width->operator [](m_latAndLong->operator [](1).second));
                tilesToReturn.append(QString::number(distance, 'g' ));
        distance=(height->operator [](m_latAndLong->operator [](1).second));
                tilesToReturn.append(QString::number(distance, 'g' ));
        distance=(width->operator [](m_latAndLong->operator [](1).second+1));
                tilesToReturn.append(QString::number(distance, 'g' ));
        if (m_latAndLong->operator [](8).second==-1)
        {
            if (m_latAndLong->operator [](5).second==-1)
            {
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
            }
            else
            {
                distance=(height->operator [](m_latAndLong->operator [](5).second));
                        tilesToReturn.append(QString::number(distance, 'g' ));
                distance=(width->operator [](m_latAndLong->operator [](1).second+1));
                        tilesToReturn.append(QString::number(distance, 'g' ));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(0));
                tilesToReturn.append(QString::number(longtitudes[layer][m_latAndLong->operator [](4).first], 'g' ));
                        tilesToReturn.append(QString::number(latitudes[layer][m_latAndLong->operator [](4).second], 'g' ));
            }
        }
        else
        {
            distance=(height->operator [](m_latAndLong->operator [](5).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(width->operator [](m_latAndLong->operator [](8).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(height->operator [](m_latAndLong->operator [](8).second));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            distance=(width->operator [](m_latAndLong->operator [](8).second+1));
                    tilesToReturn.append(QString::number(distance, 'g' ));
            tilesToReturn.append(QString::number(longtitudes[layer][m_latAndLong->operator [](4).first], 'g' ));
                    tilesToReturn.append(QString::number(latitudes[layer][m_latAndLong->operator [](4).second], 'g' ));
        }
    }
    qDebug()<<tilesToReturn;
    emit sendToProgram(tilesToReturn);
}
void TilesAnalyzer::analyzing(QVector<float> &coords,  int layer, int azm, bool repaintNeed)
{

    m_tilesToConvertAzm->clear();
    m_tilesToConvertNoAzm->clear();
    m_tilesToReturn->clear();
    qInfo()<<"Начало работы программы";
    searchIndices(coords.operator[](0), coords.operator[](1), layer);
            *m_layer=QString::number(layer);
    *m_azm=QString::number(azm).rightJustified(3, '0', true);
    if(!(QDir(*m_pathToRendedImage+m_layer).exists()))
    {
        QDir().mkdir(*m_pathToRendedImage+m_layer);
    }
    if(!(QDir(*m_pathToRendedImage+m_layer+"/"+m_azm).exists()))
    {
        QDir().mkdir(*m_pathToRendedImage+m_layer+"/"+m_azm);
    }
    if(!(QDir(*m_pathToRendedImage+m_layer+"/noAzm").exists()))
    {
        QDir().mkdir(*m_pathToRendedImage+m_layer+"/noAzm");
    }
    if (repaintNeed)
        findIndexsOfTilesToRepaint(*m_tilesToReturn, *m_tilesToConvertNoAzm, *m_tilesToConvertAzm, layer);
    else
        findIndexsOfUnRenderedTiles(*m_tilesToReturn, *m_tilesToConvertNoAzm, *m_tilesToConvertAzm, layer);
    qDebug()<<"Тайлы которые будут возвращены:";
    qDebug()<<*m_tilesToReturn;
    qDebug()<<"Тайлы которые будут конвертированы без азитмута:";
    qDebug()<<*m_tilesToConvertNoAzm;
    qDebug()<<"Тайлы которые будут конвертированы с азитмутом";
    qDebug()<<*m_tilesToConvertAzm;
    m_numAzm=m_tilesToConvertAzm->size();
    m_numNoAzm=m_tilesToConvertNoAzm->size();
    qDebug()<< "Длины массивов";
    qDebug()<<QString::number(m_numNoAzm) +" и второй  " +QString::number(m_numAzm) ;
    if (m_numAzm>0)
    {
        emit sendToRotate(*m_tilesToConvertAzm, m_numAzm, *m_azm, *m_layer);
    }
    if(m_numNoAzm>0)
    {
        qInfo()<<"emit sendToLoadNoAzm грузим тайлы в QImage без азимута";
        emit sendToLoadNoText(*m_tilesToConvertNoAzm, m_numNoAzm, *m_layer);
    }
    addWidthHeightAndLatLongToList(*m_tilesToReturn, layer);
}
