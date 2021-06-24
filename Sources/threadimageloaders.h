#ifndef THREADIMAGELOADER_H
#define THREADIMAGELOADER_H

#include <QObject>
#include <QThread>
#include <imageloader.h>
#include <QMap>
#include <QPair>
#include <QMapIterator>
#include <QVector>
#include <QTimer>
#include <QQueue>
#include <QDebug>

struct TileAndData
{
    QString tile;
    QString azm;
    bool hasAzm;
    QString layer;
    TileAndData(QString _tile,QString _layer,bool _hasAzm, QString _azm)
    {
        tile=_tile;
        azm=_azm;
        hasAzm=_hasAzm;
        layer=_layer;
    }
};

class ThreadImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ThreadImageLoader(QString &pathToSourceSvg, QString &pathToRenderedSvg, QString &fileType, int breite, int hohe);
signals:
    void start();
    void cleared();
public slots:
    void sendingNoText(QStringList &tilesToLoadImage, int lenght, QString &layer);
    void sendingText(QString &tile,QString &layer, QString &azm);
    void seekAvailableThreads();
    void addThreadToQueue();
private:
    QString noAzm="000";
    QQueue<TileAndData> til_tilesQueue;
    QTimer *m_timer;
    QQueue<QThread*> til_freeThreadsQueue;
    QMap<QThread*, ImageLoader*> til_loadedMap;
    void loadImagesFromQueue();
};

#endif // THREADIMAGELOADER_H
