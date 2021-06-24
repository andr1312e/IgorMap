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
    //format.setOption( QSurfaceFormat::DebugContext );
    QSurfaceFormat::setDefaultFormat(format);    

    QApplication a(argc, argv);
    //QApplication::setAttribute(Qt::AA_ForceRasterWidgets, false);

    // set stylesheet
    QFile file(":/qss/style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(QString(file.readAll()));

    UIController uiController;

    /*QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/SC/ControlUI2.qml"));
    if (engine.rootObjects().isEmpty())
        qDebug() << "Qml cant load";*/

    return a.exec();
}
