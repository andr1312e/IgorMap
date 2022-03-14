#ifndef THREADFILEREADER_H
#define THREADFILEREADER_H

#include "filereader.h"

#include <QThread>
#include <QTimer>
#include <QList>
#include <QTimerEvent>
#include <QString>
#include <QStringList>
#include <queue>
#include <map>

struct TileData
{
    QString tile;
    QString azm;
    QString layer;
    TileData(const QString &_tile,const QString &_azm,const QString &_layer)
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
    explicit ThreadImageRotator(const QString &pathToSourceSvg, const QString &pathToRendedImage, const QString &fileType, const char slash, QObject *parent);
    ~ThreadImageRotator();
public Q_SLOTS:
    void GettingTilesToConvert(std::list<QString> &tiles, int &numOfTilesToConvert, QString &azm, QString &layer);
    void OnSeekAvailableThreads();
    void OnAddFreeThreadToQueue();
    void ReadFilesFromQueue();
protected:
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
private:
    void CreateDataStructs(const QString &pathToSourceSvg, const QString &pathToRendedImage, const QString &fileType, char slash);
private:
    std::map<QThread*, ImageRotator*> * const m_imageRotatorHash;
    std::queue<QThread*> * const m_freeThreadsQueue;
    std::queue<TileData> * const m_tilesQueue;
    const QString m_svgType;
    const int m_numOfThreads=9;
    const int m_timerInterval=100;
};

#endif // THREADFILEREADER_H
