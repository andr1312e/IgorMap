#include "threadfilereaders.h"
#include <QDebug>

ThreadFileReader::ThreadFileReader(QString &pathToSourceSvg, QObject *parent)
    :QObject(parent)
    ,m_pathToSourceSvg(pathToSourceSvg)
    ,m_timer(new QTimer(this))
    ,til_fileReaderMap(new QHash<QThread*, FileReader*>())
    ,til_freeThreadsQueue(new QQueue<QThread*>())
    ,til_tilesQueue(new QQueue<TileData>())
{
    m_timer->setInterval(100);
    m_timer->setTimerType(Qt::CoarseTimer);
    m_timer->setSingleShot(true);
    for (int i=0; i<9; i++)
    {
        til_fileReaderMap->insert(new QThread(), new FileReader(pathToSourceSvg));
    }
    QList<QThread*>keys=til_fileReaderMap->keys();
    for (int i=0; i<9; i++)
    {
        til_freeThreadsQueue->enqueue(keys[i]);
    }
    QHashIterator<QThread*, FileReader*> iterator(*til_fileReaderMap);
    while (iterator.hasNext()) {
        iterator.next();
        connect(iterator.key(), &QThread::started, iterator.value(), &FileReader::doing);
        connect(iterator.value(), &FileReader::finished, this, &ThreadFileReader::sending);
        connect(iterator.value(), &FileReader::finished, iterator.key(), &QThread::quit);
        connect(iterator.key(), &QThread::finished, this, &ThreadFileReader::addThreadToQueue);
        iterator.value()->moveToThread(iterator.key());
    }
    connect(m_timer, &QTimer::timeout, this, &ThreadFileReader::seekAvailableThreads);
}

ThreadFileReader::~ThreadFileReader()
{
    delete til_tilesQueue;
    delete til_fileReaderMap;
    delete til_freeThreadsQueue;
    delete m_timer;
}
void ThreadFileReader::getting(QStringList &tiles, int numOfImages, QString &azm, QString &layer)
{
    if(til_freeThreadsQueue->size()>=numOfImages)
    {
        for (int i=0; i<numOfImages; i++)
        {
            QThread *thread=til_freeThreadsQueue->dequeue();
            til_fileReaderMap->value(thread)->setParams(tiles[i], azm, layer);
            thread->start();
        }
    }
    else
    {
        int numImagesToQueue=numOfImages;
        for (int i=0; i<(numOfImages-til_freeThreadsQueue->size()); i++)
        {
            QThread *thread=til_freeThreadsQueue->dequeue();
            til_fileReaderMap->value(thread)->setParams(tiles[i], azm, layer);
            thread->start();
            numImagesToQueue--;
        }
        for (int i=numOfImages-1; i>numOfImages-numImagesToQueue; i--)
        {
            til_tilesQueue->enqueue(TileData(tiles[i], azm , layer));
        }
        m_timer->start(100);
    }

}
void ThreadFileReader::sending()
{
    emit sendToLoad(((FileReader *)sender())->m_tileName, ((FileReader *)sender())->m_layer, ((FileReader *)sender())->m_azm);
}

void ThreadFileReader::seekAvailableThreads()
{
    if (!til_tilesQueue->isEmpty())
    {
        loadImagesFromQueue();
    }
}

void ThreadFileReader::addThreadToQueue()
{
    til_freeThreadsQueue->enqueue((QThread *) sender());
}
void ThreadFileReader::loadImagesFromQueue()
{
    if (!til_tilesQueue->isEmpty()&&!til_freeThreadsQueue->isEmpty())
    {
        if(til_tilesQueue->size()<=til_freeThreadsQueue->size())
        {
            for (int i=0; i<til_tilesQueue->size(); i++)
            {
                QThread *thread=til_freeThreadsQueue->dequeue();
                TileData tile= til_tilesQueue->dequeue();
                til_fileReaderMap->operator [](thread)->setParams(tile.tile, tile.azm, tile.layer);
                thread->start();
            }
        }
        else
        {
            for (int i=0; i<til_freeThreadsQueue->size(); i++)
            {
                QThread *thread=til_freeThreadsQueue->dequeue();
                TileData tile= til_tilesQueue->dequeue();
                til_fileReaderMap->operator [](thread)->setParams(tile.tile, tile.azm, tile.layer);
                thread->start();
            }
            m_timer->start(100);
        }
    }
}
