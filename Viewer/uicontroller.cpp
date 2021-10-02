#include "uicontroller.h"

#include <QSurfaceFormat>
#include <QApplication>
#include <QScreen>
#include <QLayout>


UIController::UIController(QObject *parent)
    : QObject(parent)
{

    QList<QScreen *> listOfScreens = dynamic_cast<QApplication *>(parent)->screens();
    quint8 index = currentScreenIndex;


    backgroundWidget = new Widget(listOfScreens.at(index));

    mapDebugger = new MapDebugger();
    mapDebugger->setGeometry(1643, 700,
                             255, 255);
    mapDebugger->show();


    initWidgetsInteractions();

    initTcpHandler();
}

UIController::~UIController()
{
    tcpThread->quit();
    tcpThread->wait(1000);
}


void UIController::initTcpHandler()
{
    tcpThread = new QThread();
    incomingDataHandler = new IncomingDataHandler;
    incomingDataHandler->moveToThread(tcpThread);
    connect(tcpThread, &QThread::finished, incomingDataHandler, &QObject::deleteLater);
    connect(tcpThread, &QThread::finished, tcpThread, &QThread::deleteLater);
    connect(tcpThread, &QThread::started, incomingDataHandler, &IncomingDataHandler::doWork);

    connect(incomingDataHandler, &IncomingDataHandler::mapUpdate,
            mapDebugger, &MapDebugger::parseJSONDocument);
    connect(mapDebugger, &MapDebugger::requestForNewMap,
            incomingDataHandler, &IncomingDataHandler::sendJsonDocument);
    tcpThread->start();
}

void UIController::initWidgetsInteractions()
{
    connect(backgroundWidget->getSceneRef()->getCameraPtr(), &Camera::translateCamera,
            mapDebugger, &MapDebugger::updateViewCenter); // зацикливание
    connect(mapDebugger, &MapDebugger::moveCenterOnX,
            backgroundWidget->getSceneRef(), &Scene::setSideSpeedSlot);
    connect(mapDebugger, &MapDebugger::moveCenterOnY,
            backgroundWidget->getSceneRef(), &Scene::setForwardSpeedSlot);
    connect(mapDebugger, &MapDebugger::userCenterViewGeo,
            backgroundWidget->getSceneRef()->mapGLData(), &MapGL::updateViewCenterGeo);
    connect(mapDebugger, &MapDebugger::clearAllTilesOfMap,
            backgroundWidget->getSceneRef()->mapGLData(), &MapGL::clearAllTiles);
    connect(mapDebugger, &MapDebugger::getViewCenter,
            backgroundWidget->getSceneRef(), &Scene::viewCenterRequest);
    connect(mapDebugger, &MapDebugger::infoForRender,
            backgroundWidget->getSceneRef()->mapGLData(), &MapGL::updateMap);
    emit mapDebugger->getViewCenter();
}
