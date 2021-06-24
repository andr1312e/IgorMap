#include "program.h"
#include <QDebug>

Program::Program(QObject *parent)
    : QObject(parent)
    , m_loader(nullptr)
    , m_reader(nullptr)
{

}
void Program::setParams(QString &pathToSourceSvg, QString &pathToRendedImage, QString &fileType, int width, int height)
{
    m_reader=new ThreadFileReader(pathToSourceSvg);
    m_loader=new ThreadImageLoader(pathToSourceSvg, pathToRendedImage, fileType, width, height);
    m_analyzer=new TilesAnalyzer(pathToSourceSvg, pathToRendedImage, fileType);
    connect(this, &Program::sendToAnalyze, m_analyzer, &TilesAnalyzer::analyzing);
    connect(m_analyzer, &TilesAnalyzer::sendToRotate, m_reader, &ThreadFileReader::getting);
    connect(m_reader, &ThreadFileReader::sendToLoad, m_loader, &ThreadImageLoader::sendingText);
    connect(m_analyzer, &TilesAnalyzer::sendToLoadNoText, m_loader, &ThreadImageLoader::sendingNoText );
    connect(m_analyzer, &TilesAnalyzer::sendToProgram, this, &Program::sending);
}

void Program::executing(QVector<float> &coords, int layer,int azm,  bool repaintNeed)
{
    emit sendToAnalyze(coords,layer, azm, repaintNeed);
}
void Program::sending(QStringList &data)
{
    emit sendToServer(data);
}

