#ifndef THREADFILEREADER_H
#define THREADFILEREADER_H

#include <QObject>
#include <QThread>
#include <filereader.h>
#include <QTimer>
#include <QQueue>
#include <QList>
#include <QString>
#include <QStringList>
struct TileData
{
    QString tile;
    QString azm;
    QString layer;
    TileData(QString _tile,QString _azm, QString _layer)
    {
        tile=_tile;
        azm=_azm;
        layer=_layer;
    }
};
class ThreadFileReader : public QObject
{
    Q_OBJECT
public:
    explicit ThreadFileReader(QString &pathToSourceSvg, QObject *parent = nullptr);
    ~ThreadFileReader();
signals:
    void sendToLoad(QString &tile,QString &m_layer, QString &azm);
public slots:
    void getting(QStringList &tiles, int numOfThreads, QString &azm, QString &layer);
    void sending();
    void seekAvailableThreads();
    void addThreadToQueue();
    void loadImagesFromQueue();
private:
    QQueue<TileData> *til_tilesQueue;
    QHash<QThread*, FileReader*> *til_fileReaderMap;
    QQueue<QThread*> *til_freeThreadsQueue;
    QTimer *m_timer;
    QString m_pathToSourceSvg;
};

#endif // THREADFILEREADER_H
