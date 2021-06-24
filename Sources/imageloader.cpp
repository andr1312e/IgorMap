#include "imageloader.h"
#include <QDebug>
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;


ImageLoader::ImageLoader(QString &pathToSourceSvg, QString &pathToRendedImage, QString &fileType, int width, int height)
    :m_pathToSourceSvg(&pathToSourceSvg)
    ,m_pathToRendedImage(&pathToRendedImage)
    ,m_fileType(&fileType)
    ,m_image(new QImage(width, height, QImage::Format_ARGB32))
    ,m_renderer(new QSvgRenderer())
    ,m_painter(new QPainter(m_image))
{
    m_painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    m_painter->setRenderHints(QPainter::HighQualityAntialiasing, true);
}

ImageLoader::~ImageLoader()
{
    delete m_renderer;
    delete m_painter;
    delete m_image;
}
void ImageLoader::setParams(QString &tile, QString &layer, bool hasAzm, QString &azm)
{
    //    qInfo()<<" установили параметры в лодере для: " +tile;
    il_layer=layer;
    il_tilename=tile;
    il_hasAzm=hasAzm;
    il_azm=azm;
}
void ImageLoader::doing()
{
    //    system_clock::time_point start = system_clock::now();
    //    qDebug()<<"Загрузка в QImage" +il_tilename;
    m_renderer->load(*m_pathToSourceSvg+ il_layer+ "/"+ il_tilename+".svg");
    m_renderer->render(m_painter);
    if (il_hasAzm)
        m_image->save(m_pathToRendedImage+ il_layer+ "/"+ il_azm+ "/"+ il_tilename + *m_fileType);
    else
        m_image->save(m_pathToRendedImage+ il_layer+ "/noAzm/"+ il_tilename + *m_fileType);
    //    system_clock::time_point end = system_clock::now();
    //    duration<double> sec = end - start;
    //    qDebug()<< "Время загрузки одной картинки в QImage" + QString::number(sec.count());
    emit finished();
}
