#include "threadfilereaders.h"


ThreadImageRotator::ThreadImageRotator(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType, const QString *slash, QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
    , m_imageRotatorHash(new QHash<QThread*, ImageRotator*>())
    , m_freeThreadsQueue(new std::queue<QThread*>())
    , m_tilesQueue(new std::queue<TileData>())
    , m_svgType(new QString(QStringLiteral(".svg")))
{
    qInfo()<<"ThreadFileReader constructor";
    initTimer();
    createDataStructs(pathToSourceSvg, pathToRendedImage, fileType, slash);
    createConnections();
}

ThreadImageRotator::~ThreadImageRotator()
{
    QHashIterator<QThread*, ImageRotator*> iterator(*m_imageRotatorHash);
    while (iterator.hasNext()) {
        iterator.next();
        delete iterator.value();
        delete iterator.key();
    }
    delete m_tilesQueue;
    delete m_imageRotatorHash;
    delete m_freeThreadsQueue;
    delete m_timer;
}
void ThreadImageRotator::gettingTilesToConvert(QStringList &tiles, int &numOfImages, QString &azm, QString &layer)
{
    char firstParam=azm.at(0).toLatin1();
    char secondParam=azm.at(1).toLatin1();
    char thirdParam=azm.at(2).toLatin1();
    QStringList::iterator it=tiles.begin();
    if(m_freeThreadsQueue->size()>=numOfImages)
    {
        for (; it!=tiles.end(); ++it)
        {
            QThread *thread=m_freeThreadsQueue->front();
            m_freeThreadsQueue->pop();
            m_imageRotatorHash->value(thread)->setParams(*it, azm, layer, firstParam, secondParam, thirdParam);
            thread->start();
        }
    }
    else
    {
        int numImagesToQueue=numOfImages;
        for (int i=0; i<m_freeThreadsQueue->size(); i++, ++it)
        {
            QThread *thread=m_freeThreadsQueue->front();
            m_freeThreadsQueue->pop();
            m_imageRotatorHash->value(thread)->setParams(*it, azm, layer, firstParam, secondParam, thirdParam);
            thread->start();
            numImagesToQueue--;
        }
        for (int i=numOfImages-1; i>numOfImages-numImagesToQueue; i--)
        {
            m_tilesQueue->push(TileData(tiles[i], azm , layer));
        }
        m_timer->start(m_timerInterval);
    }

}

void ThreadImageRotator::seekAvailableThreads()
{
    if (!m_tilesQueue->empty())
    {
        readFilesFromQueue();
    }
}

void ThreadImageRotator::addThreadToQueue()
{
    m_freeThreadsQueue->push(qobject_cast<QThread *>(sender()));
}
void ThreadImageRotator::readFilesFromQueue()
{
    if (!m_tilesQueue->empty()&&!m_freeThreadsQueue->empty())
    {
        if(m_tilesQueue->size()<=m_freeThreadsQueue->size())
        {
            for (int i=0; i<m_tilesQueue->size(); i++)
            {
                TileData tile= m_tilesQueue->front();
                m_tilesQueue->pop();
                char firstParam=tile.azm.at(0).toLatin1();
                char secondParam=tile.azm.at(1).toLatin1();
                char thirdParam=tile.azm.at(2).toLatin1();
                QThread *thread=m_freeThreadsQueue->front();
                m_freeThreadsQueue->pop();
                m_imageRotatorHash->operator [](thread)->setParams(tile.tile, tile.azm, tile.layer, firstParam, secondParam, thirdParam);
                thread->start(QThread::TimeCriticalPriority);
            }
        }
        else
        {
            for (int i=0; i<m_freeThreadsQueue->size(); i++)
            {
                TileData tile= m_tilesQueue->front();
                m_tilesQueue->pop();
                char firstParam=tile.azm.at(0).toLatin1();
                char secondParam=tile.azm.at(1).toLatin1();
                char thirdParam=tile.azm.at(2).toLatin1();
                QThread *thread=m_freeThreadsQueue->front();
                m_freeThreadsQueue->pop();
                m_imageRotatorHash->operator [](thread)->setParams(tile.tile, tile.azm, tile.layer, firstParam, secondParam, thirdParam);
                thread->start(QThread::TimeCriticalPriority);
            }
            m_timer->start(m_timerInterval);
        }
    }
}

void ThreadImageRotator::initTimer()
{
    m_timer->setInterval(m_timerInterval);
    m_timer->setTimerType(Qt::CoarseTimer);
    m_timer->setSingleShot(true);
}

void ThreadImageRotator::createDataStructs(const QString *pathToSourceSvg,const QString *pathToRendedImage,const QString *fileType, const QString *slash)
{
    for (int i=0; i<m_numOfThreads; i++)
    {
        m_imageRotatorHash->insert(new QThread(), new ImageRotator(pathToSourceSvg, pathToRendedImage, fileType, slash, m_svgType, nullptr));
    }
    QList<QThread*>keys=m_imageRotatorHash->keys();
    for (QList<QThread*>::const_iterator it=keys.cbegin(), total = keys.cend(); it!=total; ++it)
    {
        m_freeThreadsQueue->push(*it);
    }
}

void ThreadImageRotator::createConnections()
{
    QHashIterator<QThread*, ImageRotator*> iterator(*m_imageRotatorHash);
    while (iterator.hasNext()) {
        iterator.next();
        connect(iterator.key(), &QThread::started, iterator.value(), &ImageRotator::doing);
        connect(iterator.value(), &ImageRotator::finished, iterator.key(), &QThread::quit);
        connect(iterator.key(), &QThread::finished, this, &ThreadImageRotator::addThreadToQueue);
        iterator.value()->moveToThread(iterator.key());
    }
    connect(m_timer, &QTimer::timeout, this, &ThreadImageRotator::seekAvailableThreads);
}
