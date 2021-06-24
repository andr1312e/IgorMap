#include <QApplication>
#include "server.h"
#include <QDir>
#include <QSettings>
#include <QVariant>
#include<QTextStream>
#include <threadfilereaders.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString pathToSettingsFile=QDir::currentPath()+"/settings.ini";
    QString pathToSourcesSvg, pathToRenderedImages, fileType;
    int width, height;
    if (QFile(pathToSettingsFile).exists())
    {
        qDebug()<< QDir::currentPath()+"/settings.ini "+" найден";
        QSettings setting(QDir::currentPath()+"/settings.ini", QSettings::IniFormat);
        pathToSourcesSvg = setting.value("pathToSource", "").toString();
        pathToRenderedImages = setting.value("pathToRendedImage", "").toString();
        width = setting.value("width", "").toString().toInt();
        height = setting.value("height", "").toString().toInt();
        fileType=setting.value("fileType", "").toString().toInt();

        if (width<1||height<1)
        {
            width=497;
            height=279;
        }
        if (!fileType.contains("."))
        {
            qInfo() <<"fileType должен содежать тип с точкой .png, .jpeg";
            qInfo() <<'fileType =.png';
            fileType=".png";
        }
    }
    else
    {
        width=497;
        height=279;
        pathToSourcesSvg=QDir::currentPath()+"/svg/";
        pathToRenderedImages=QDir::currentPath()+"/images/";
        fileType=".png";
    }
    if(!(QDir(pathToSourcesSvg).exists()))
    {
        qInfo()<<"ТАЙЛОВ НЕТ!!!!!!!!!!!!!!";
        qInfo()<<"pathToSourceSvg: " + pathToSourcesSvg;
        return 0;
    }
    else
    {
        qDebug()<<width;
        qDebug()<<height;
        if(!(QDir(pathToRenderedImages).exists()))
            QDir().mkdir(pathToRenderedImages);
        qInfo()<<"pathToSourceSvg: " + pathToSourcesSvg;
        qInfo()<<"pathToRendedImage: " +pathToRenderedImages;
        qInfo()<<"width: " + QString::number(width);
        qInfo()<<"height: " + QString::number(height);
        Program *program=new Program();
        qInfo()<<"Программа запущена";
        program->setParams(pathToSourcesSvg, pathToRenderedImages, fileType, width, height);
        Server renderServer(*program, nullptr);
        return app.exec();
    }
}

