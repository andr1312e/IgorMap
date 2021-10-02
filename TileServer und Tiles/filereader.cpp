#include "filereader.h"

ImageRotator::ImageRotator(const QString *pathToSourceSvg, const QString *pathToRendedImage, const QString *fileType, const QString *slash, const QString *svgType, QObject *parent)
    : QObject(parent)
    , m_file(new QFile())
    , m_pathToSourceSvg(pathToSourceSvg)
    , m_pathToRendedImage(pathToRendedImage)
    , m_fileType(fileType)
    , m_slash(slash)
    , m_svgType(svgType)
    , m_image(new QImage(497, 279, QImage::Format_ARGB32_Premultiplied))
    , m_renderer(new QSvgRenderer())
    , m_painter(new QPainter(m_image))
    , index(100)
    , m_previousCharInArray(' ')
    , m_array(Q_NULLPTR)
{
    m_painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    m_painter->setRenderHints(QPainter::Antialiasing, true);
    m_renderer->setFramesPerSecond(0);
}

ImageRotator::~ImageRotator()
{
    delete m_file;
    delete m_image;
    delete m_renderer;
    delete m_painter;
}
void ImageRotator::setParams(QString &tile,  QString &azm, QString &layer, char &firstNum, char &secondNum, char &thirdNum)
{
    m_tileName=tile;
    m_azm=azm;
    m_layer=layer;
    m_firstNum=firstNum;
    m_secondNum=secondNum;
    m_thirdNum=thirdNum;
}
void ImageRotator::doing()
{
    m_file->setFileName(*m_pathToSourceSvg+m_layer+*m_slash+m_tileName+*m_svgType);
    m_file->open(QIODevice::ReadOnly);
    m_array=m_file->readAll();
    m_file->close();
    for (index; index<m_array.size()-10; index++)
    {
        if(m_previousCharInArray=='('&&m_array.at(index)==' '&&m_array.at(index+1)==' ')
        {
            m_array.operator[](index+2)=m_firstNum;
            m_array.operator[](index+3)=m_secondNum;
            m_array.operator[](index+4)=m_thirdNum;
            index=index+60;
        }
        else
        {
            m_previousCharInArray=m_array.at(index);
        }
    }
    m_renderer->load(m_array);
    m_renderer->render(m_painter);
    m_image->save(*m_pathToRendedImage+ m_layer+ *m_slash+ m_azm+ *m_slash+ m_tileName + *m_fileType);
    index=100;
    m_previousCharInArray=' ';
    Q_EMIT finished();
}
