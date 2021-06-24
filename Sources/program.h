#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <tilesanalyzer.h>
#include <threadfilereaders.h>
#include <threadimageloaders.h>
#include <QStringList>
#include <QVector>
class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    void setParams(QString &pathToSourceSvg, QString &pathToRendedImage, QString &fileType, int width, int height);
signals:
    void sendToAnalyze(QVector<float> &coords, int layer,int azm,  bool repaintNeed);
    void sendToServer(QStringList &data);
public slots:
    void executing(QVector<float> &coords,int layer, int azm,  bool repaintNeed);
    void sending(QStringList &data);
private:
    TilesAnalyzer *m_analyzer;
    ThreadFileReader *m_reader;
    ThreadImageLoader *m_loader;
};

#endif // PROGRAM_H
