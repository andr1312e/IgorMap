#include "filereader.h"

ImageRotator::ImageRotator(const QString &pathToSourceSvg, const QString &pathToRendedImage, const QString &fileType, const char slash, const QString &svgType, QObject *parent)
    : QObject(parent)
    , m_file(new QFile())
    , m_pathToSourceSvgFolder(pathToSourceSvg)
    , m_pathToRendedImageFolder(pathToRendedImage)
    , m_fileType(fileType)
    , m_slash(slash)
    , m_svgType(svgType)
    , m_image(new QImage(497, 279, QImage::Format_RGB32))
    , m_renderer(new QSvgRenderer())
    , m_painter(new QPainter(m_image))
    , index(40)
    , m_previousCharInArray(' ')
    , m_openBracket('(')
    , m_whiteSpace(' ')
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
void ImageRotator::SetParams(const QString &tile,  QString &azm, QString &layer, char firstNum, char secondNum, char thirdNum)
{
    m_pathToSource.append(m_pathToSourceSvgFolder).append(layer).append(m_slash).append(tile).append(m_svgType);
    m_pathToRender.append(m_pathToRendedImageFolder).append(layer).append(m_slash).append(azm).append(m_slash).append(tile).append(m_fileType);
    m_firstNum=firstNum;
    m_secondNum=secondNum;
    m_thirdNum=thirdNum;
}
void ImageRotator::OnMakingImage()
{
    m_file->setFileName(m_pathToSource);
    m_file->open(QIODevice::ReadOnly);
    m_array=m_file->readAll();
    m_file->close();
    for (index; index<m_array.size()-10; index=index+1)
    {
        if(m_openBracket==m_previousCharInArray&&m_array.at(index)==m_whiteSpace&&m_array.at(index+1)==m_whiteSpace)
        {
            m_array.operator[](index+2)=m_firstNum;
            m_array.operator[](index+3)=m_secondNum;
            m_array.operator[](index+4)=m_thirdNum;
            index=index+60;
        }
         m_previousCharInArray=m_array.at(index);
    }
    m_renderer->load(m_array);
    m_renderer->render(m_painter);
    m_image->save(m_pathToRender);
    index=40;
    m_pathToSource.clear();
    m_pathToRender.clear();
    m_previousCharInArray=' ';
    Q_EMIT ToFinished();
}
