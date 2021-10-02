#include <QApplication>
//#include <QCoreApplication>
#include <QSurfaceFormat>
#include <QFile>
#include "uicontroller.h"


int main(int argc, char *argv[])
{
    //set Surface format
    QSurfaceFormat format;
    format.setDepthBufferSize(8);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(16);
    format.setProfile(QSurfaceFormat::CoreProfile );
    QSurfaceFormat::setDefaultFormat(format);    

    QApplication a(argc, argv);

    // set stylesheet
    QFile file(":/styles/Resources/style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(QString(file.readAll()));

    UIController uiController;



    return a.exec();
}
