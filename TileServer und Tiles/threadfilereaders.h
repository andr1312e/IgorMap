#ifndef THREADFILEREADER_H
#define THREADFILEREADER_H

#include "filereader.h"

#include <QThread>
#include <QTimer>
#include <QList>
#include <QString>
#include <QStringList>
#include <queue>

struct TileData
{
    QString tile;
    QString azm;
    QString layer;
    TileData(QString &_tile,QString &_azm, QString &_layer)
    {
        tile=_tile;
        azm=_azm;
        layer=_layer;
    }
};

class ThreadImageRotator : public QObject
{
    Q_OBJECT
public:
    explicit ThreadImageRotator(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType, const QString *slash, QObject *parent);
    void operator=( const ThreadImageRotator& ) = delete;
    ~ThreadImageRotator();
public Q_SLOTS:
    void gettingTilesToConvert(QStringList &tiles, int &numOfTilesToConvert, QString &azm, QString &layer);
    void seekAvailableThreads();
    void addThreadToQueue();
    void readFilesFromQueue();
private:
    void initTimer();
    void createDataStructs(const QString *pathToSourceSvg, const QString *pathToRendedImage, const QString *fileType, const QString *slash);
    void createConnections();
private:
    QTimer *m_timer;
    QHash<QThread*, ImageRotator*> *m_imageRotatorHash;
    std::queue<QThread*> *m_freeThreadsQueue;
    std::queue<TileData> *m_tilesQueue;
    const QString *m_svgType;
    const int m_numOfThreads=9;
    const int m_timerInterval=100;
};

#endif // THREADFILEREADER_H
