#include "threadimageloaders.h"
ThreadImageLoader::ThreadImageLoader(QString &pathToSourceSvg, QString &pathToRenderedSvg, QString &fileType, int breite, int hohe)
    :m_timer(new QTimer(this))
    ,til_freeThreadsQueue(new QQueue<QThread*>())
    ,til_tilesQueue(new QQueue<TileAndData>())
    ,til_loadedHash(new QHash<QThread*, ImageLoader*>())
{
    m_timer->setInterval(100);
    m_timer->setTimerType(Qt::CoarseTimer);
    m_timer->setSingleShot(true);
    int numOfthreads=18;
    for (int i=0; i<numOfthreads; i++)
    {
        til_loadedHash->insert(new QThread(), new ImageLoader(pathToSourceSvg, pathToRenderedSvg, fileType, breite, hohe));
    }
    QList<QThread*>keys=til_loadedHash->keys();
    for (int i=0; i<numOfthreads; i++)
    {
        til_freeThreadsQueue->enqueue(keys[i]);
    }
    QHashIterator<QThread*, ImageLoader*> iterator(*til_loadedHash);
    while (iterator.hasNext()) {
        iterator.next();
        connect(iterator.key(), &QThread::started, iterator.value(), &ImageLoader::doing);
        connect(iterator.value(), &ImageLoader::finished, iterator.key(), &QThread::quit);
        connect(iterator.key(), &QThread::finished, this, &ThreadImageLoader::addThreadToQueue);
        iterator.value()->moveToThread(iterator.key());
    }
    connect(m_timer, &QTimer::timeout, this, &ThreadImageLoader::seekAvailableThreads);
}

ThreadImageLoader::~ThreadImageLoader()
{
    delete til_freeThreadsQueue;
    delete til_tilesQueue;
    delete m_timer;
}

void ThreadImageLoader::sendingNoText(QStringList &tilesToLoadImage, int numImages, QString &layer)
{
    til_tilesQueue->clear();
//    qInfo()<<"(((((((((((((((((";
//    qInfo()<<til_freeThreadsQueue->size();
    if(til_freeThreadsQueue->size()>=numImages)
    {
       for (int i=0; i<numImages; i++)
        {
            QThread *thread=til_freeThreadsQueue->dequeue();
            til_loadedHash->value(thread)->setParams(tilesToLoadImage[i], layer, false, noAzm);
            thread->start();
        }
    }
    else
    {
        int numImagesToQueue=numImages;
        for (int i=0; i<(numImages-til_freeThreadsQueue->size()); i++)
        {
            QThread *thread=til_freeThreadsQueue->dequeue();
            til_loadedHash->value(thread)->setParams(tilesToLoadImage[i], layer, false, noAzm);
            thread->start();
            numImagesToQueue--;
        }
        for (int i=numImages-1; i>numImages-numImagesToQueue; i--)
        {
            til_tilesQueue->enqueue(TileAndData(tilesToLoadImage[i], layer, false, noAzm));
        }
        m_timer->start(100);
    }
}
void ThreadImageLoader::sendingText(QString &tile, QString &layer, QString &azm)
{
    qInfo()<<"tile "+ tile;
    if(!til_freeThreadsQueue->isEmpty())
    {
        QThread *thread=til_freeThreadsQueue->dequeue();
        til_loadedHash->value(thread)->setParams(tile, layer, true, azm);
        thread->start();
    }
    else
    {
        til_tilesQueue->enqueue(TileAndData(tile, layer, true, azm));
        m_timer->start(100);
    }
}
void ThreadImageLoader::seekAvailableThreads()
{
    if (!til_tilesQueue->isEmpty())
    {
        loadImagesFromQueue();
    }
}

void ThreadImageLoader::addThreadToQueue()
{
    til_freeThreadsQueue->enqueue((QThread *) sender());
}
void ThreadImageLoader::loadImagesFromQueue()
{
    if (!til_tilesQueue->isEmpty()&&!til_freeThreadsQueue->isEmpty())
    {
        if(til_tilesQueue->size()<=til_freeThreadsQueue->size())
        {
            for (int i=0; i<til_tilesQueue->size(); i++)
            {
                QThread *thread=til_freeThreadsQueue->dequeue();
                TileAndData tile= til_tilesQueue->dequeue();
                til_loadedHash->operator [](thread)->setParams(tile.tile, tile.layer, tile.hasAzm, tile.azm);
                thread->start();
            }
        }
        else
        {
            for (int i=0; i<til_freeThreadsQueue->size(); i++)
            {
                QThread *thread=til_freeThreadsQueue->dequeue();
                TileAndData tile= til_tilesQueue->dequeue();
                til_loadedHash->operator [](thread)->setParams(tile.tile, tile.layer, tile.hasAzm, tile.azm);
                thread->start();
            }
            m_timer->start(100);
        }
    }
}



