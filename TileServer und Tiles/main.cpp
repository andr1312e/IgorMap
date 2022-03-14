#include <QApplication>
#include "server.h"

void CreateFoldersForRenderedImages(const QString &pathToRenderedImages)
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
        if(!(QDir(pathToRenderedImages+QString::number(i)+QStringLiteral("/noAzm")).exists()))
        {
            QDir().mkdir(pathToRenderedImages+QString::number(i)+QStringLiteral("/noAzm"));
        }
        QImage image(QSize(497, 279), QImage::Format_ARGB32);
        image.fill(Qt::white);
        image.save(pathToRenderedImages+QStringLiteral("white.jpg"));

    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    const QString m_programDirectory=QDir::currentPath()+QStringLiteral("/");
    const QString m_renderedImageType=QStringLiteral(".jpg");
    const QString pathToSourcesSvg=m_programDirectory+QStringLiteral("svg/");
    const QString pathToRenderedImages=m_programDirectory+QStringLiteral("jpg/");
    if(!(QDir(pathToSourcesSvg).exists()))
    {
        qInfo()<<QStringLiteral("ПАПКИ ТАЙЛОВ НЕТ!!!!!!!!!!!!!!").toUtf8().constData();
        qInfo()<<QStringLiteral("pathToSourceSvg: ") + pathToSourcesSvg;
        return 0;
    }
    else
    {
        qInfo()<<QStringLiteral("Путь к исходным изображениям: ") + pathToSourcesSvg;
        qInfo()<<QStringLiteral("Путь к полученным изображениям: ") +pathToRenderedImages;
        CreateFoldersForRenderedImages(pathToRenderedImages);
        qInfo()<<QStringLiteral("Программа запущена");
        Server renderServer(pathToSourcesSvg, pathToRenderedImages, m_renderedImageType, Q_NULLPTR);
        return app.exec();
    }
}

