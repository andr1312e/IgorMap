#include "threadfilereaders.h"


ThreadImageRotator::ThreadImageRotator(const QString &pathToSourceSvg,const QString &pathToRendedImage,const QString &fileType, const char slash, QObject *parent)
    : QObject(parent)
    , m_imageRotatorHash(new std::map<QThread*, ImageRotator*>())
    , m_freeThreadsQueue(new std::queue<QThread*>())
    , m_tilesQueue(new std::queue<TileData>())
    , m_svgType(QStringLiteral(".svg"))
{
    qInfo()<<"ThreadFileReader constructor";
    CreateDataStructs(pathToSourceSvg, pathToRendedImage, fileType, slash);
}

ThreadImageRotator::~ThreadImageRotator()
{
    std::map<QThread*, ImageRotator*>::iterator it(m_imageRotatorHash->begin());
    while (it!=m_imageRotatorHash->end()) {
        delete it->second;
        delete it->first;
        ++it;
    }
    delete m_tilesQueue;
    delete m_imageRotatorHash;
    delete m_freeThreadsQueue;
}
void ThreadImageRotator::GettingTilesToConvert(std::list<QString> &tiles, int &numOfImages, QString &azm, QString &layer)
{
    char firstParam=azm.at(0).toLatin1();
    char secondParam=azm.at(1).toLatin1();
    char thirdParam=azm.at(2).toLatin1();
    std::list<QString>::const_iterator it=tiles.cbegin();
    if(m_freeThreadsQueue->size()>=numOfImages)
    {
        for (; it!=tiles.cend(); ++it)
        {
            QThread *thread=m_freeThreadsQueue->front();
            m_freeThreadsQueue->pop();
            m_imageRotatorHash->at(thread)->SetParams(*it, azm, layer, firstParam, secondParam, thirdParam);
            thread->start();
        }
    }
    else
    {
        int numImagesToQueue=numOfImages;
        for (int i=0; i<m_freeThreadsQueue->size(); ++i, ++it)
        {
            QThread *thread=m_freeThreadsQueue->front();
            m_freeThreadsQueue->pop();
            m_imageRotatorHash->at(thread)->SetParams(*it, azm, layer, firstParam, secondParam, thirdParam);
            thread->start();
            numImagesToQueue--;
        }
        for (int i=numOfImages-1; i>numOfImages-numImagesToQueue; --i )
        {
            m_tilesQueue->push(TileData(*it, azm , layer));
            ++it;
        }
        startTimer(m_timerInterval, Qt::VeryCoarseTimer);
    }

}

void ThreadImageRotator::OnSeekAvailableThreads()
{

}

void ThreadImageRotator::OnAddFreeThreadToQueue()
{
    m_freeThreadsQueue->push(qobject_cast<QThread *>(sender()));
}
void ThreadImageRotator::ReadFilesFromQueue()
{
    if (!m_tilesQueue->empty()&&!m_freeThreadsQueue->empty())
    {
        if(m_tilesQueue->size()<=m_freeThreadsQueue->size())
        {
            while(!m_tilesQueue->empty())
            {
                TileData tile= m_tilesQueue->front();
                m_tilesQueue->pop();
                char firstParam=tile.azm.at(0).toLatin1();
                char secondParam=tile.azm.at(1).toLatin1();
                char thirdParam=tile.azm.at(2).toLatin1();
                QThread * const thread=m_freeThreadsQueue->front();
                m_freeThreadsQueue->pop();
                m_imageRotatorHash->operator [](thread)->SetParams(tile.tile, tile.azm, tile.layer, firstParam, secondParam, thirdParam);
                thread->start(QThread::TimeCriticalPriority);
            }
        }
        else
        {
            while(!m_freeThreadsQueue->empty())
            {
                TileData tile= m_tilesQueue->front();
                m_tilesQueue->pop();
                char firstParam=tile.azm.at(0).toLatin1();
                char secondParam=tile.azm.at(1).toLatin1();
                char thirdParam=tile.azm.at(2).toLatin1();
                QThread * const thread=m_freeThreadsQueue->front();
                m_freeThreadsQueue->pop();
                m_imageRotatorHash->at(thread)->SetParams(tile.tile, tile.azm, tile.layer, firstParam, secondParam, thirdParam);
                thread->start(QThread::TimeCriticalPriority);
            }
            startTimer(m_timerInterval, Qt::VeryCoarseTimer);
        }
    }
}

void ThreadImageRotator::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    if (!m_tilesQueue->empty())
    {
        ReadFilesFromQueue();
    }
}

void ThreadImageRotator::CreateDataStructs(const QString &pathToSourceSvg,const QString &pathToRendedImage,const QString &fileType,  char slash)
{
    for (int i=0; i<m_numOfThreads; ++i)
    {
        QThread *const thread=new QThread();
        ImageRotator *const rotator=new ImageRotator(pathToSourceSvg, pathToRendedImage, fileType, slash, m_svgType, Q_NULLPTR);
        connect(thread, &QThread::started, rotator, &ImageRotator::OnMakingImage);
        connect(rotator, &ImageRotator::ToFinished, thread, &QThread::quit);
        connect(thread, &QThread::finished, this, &ThreadImageRotator::OnAddFreeThreadToQueue);
        rotator->moveToThread(thread);
        m_freeThreadsQueue->push(thread);
        m_imageRotatorHash->insert(std::make_pair(thread, rotator));
    }
}
