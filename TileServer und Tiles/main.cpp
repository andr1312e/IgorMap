#include <QApplication>
#include "server.h"

void createFoldersForRenderedImages(const QString &pathToRenderedImages)
{
    if(!(QDir(pathToRenderedImages).exists()))
    {
        QDir().mkdir(pathToRenderedImages);
    }
    for (int i=5; i<12; i++){
        if(!(QDir(pathToRenderedImages+QString::number(i)).exists()))
        {
            QDir().mkdir(pathToRenderedImages+QString::number(i));
        }
        if(!(QDir(pathToRenderedImages+QString::number(i)+"/noAzm").exists()))
        {
            QDir().mkdir(pathToRenderedImages+QString::number(i)+"/noAzm");
            QImage image(QSize(497, 279), QImage::Format_ARGB32);
            image.fill(Qt::white);
            image.save(pathToRenderedImages+QString::number(i)+"/noAzm/"+"white.jpg");
        }

    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    const QString m_programDirectory=QDir::currentPath()+"/";
    QString m_renderedImageType=QStringLiteral(".jpg");
    const QString pathToSourcesSvg=m_programDirectory+"svg/";
    const QString pathToRenderedImages=m_programDirectory+"jpg/";
    if(!(QDir(pathToSourcesSvg).exists()))
    {
        qInfo()<<"ПАПКИ ТАЙЛОВ НЕТ!!!!!!!!!!!!!!";
        qInfo()<<"pathToSourceSvg: " + pathToSourcesSvg;
        return 0;
    }
    else
    {
        qInfo()<<"Путь к исходным изображениям: " + pathToSourcesSvg;
        qInfo()<<"Путь к полученным изображениям: " +pathToRenderedImages;
        createFoldersForRenderedImages(pathToRenderedImages);
        qInfo()<<"Программа запущена";
        Server renderServer(&pathToSourcesSvg, &pathToRenderedImages, &m_renderedImageType, nullptr);
        return app.exec();
    }
}

