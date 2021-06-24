#include "uicontroller.h"
#include "global.h"
#include <QSurfaceFormat>
#include <QApplication>
#include <QScreen>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlFileSelector>
#include <QUrl>
#include <QTimer>
#include <QLayout>


UIController::UIController(QObject *parent) : QObject(parent)
{
    //sectorsData = new SectorData;

    QList<QScreen *> listOfScreens = dynamic_cast<QApplication *>(parent)->screens();
    quint8 index = 0;

    QRect rect = listOfScreens.at(index)->availableGeometry();

    backgroundWidget = new Widget(listOfScreens.at(index));

    //backgroundWidget->setGeometry(listOfScreens.at(index)->availableGeometry());
    //backgroundWidget2 = new Widget(listOfScreens.at(index + 1));
    //backgroundWidget2->doNotRender(false);
    //backgroundWidget2->setGeometry(listOfScreens.at(index + 1)->availableVirtualGeometry());
    //QWidget *wgt2 = QWidget::createWindowContainer(backgroundWidget);
    //wgt2->setStyleSheet("QWidget { margin: 0px; padding: 0px; spacing: 0; }");
    //wgt2->setGeometry(listOfScreens.at(index)->availableGeometry());
    //wgt2->showFullScreen();
    //wgt2->show();

    //rect = wgt2->geometry();

    int x2 = 100, y2 = 100;
    /*settingWidget = new DetectionSectorWidget();
    settingWidget->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2,
                     listOfScreens.at(index)->availableGeometry().y() + y2,
                     x2, y2);*/
    //settingWidget->show();

    sectorsViewer = new SectorsViewerWidget();
    sectorsViewer->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2,
                     listOfScreens.at(index)->availableGeometry().y() + y2,
                     3*x2, 3*y2);

    ktaInfoWidget = new KTAInfoWidget();
    ktaInfoWidget->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2,
                     listOfScreens.at(index)->availableGeometry().y() + y2 + y2,
                     3*x2, 3*y2);
    //sectorsViewer->show();

//    int xMainWindget = 0, yMainWindget = 0,
//        widthMainWindget = 200, heightMainWindget = listOfScreens.at(index)->geometry().height();

//    mainWidgetController = new MainWidgetController();
//    mainWidgetController->setGeometry(listOfScreens.at(index)->availableGeometry().x() + xMainWindget,
//                     listOfScreens.at(index)->availableGeometry().y() + yMainWindget,
//                     widthMainWindget, heightMainWindget);
    /*mainWidget = new MainWidget();
    mainWidget->show();*/    


    sceneCustomazingWindow = new SceneCustomazingWindow();
    sceneCustomazingWindow->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2,
                     listOfScreens.at(index)->availableGeometry().y() + y2 + y2,
                     3*x2, 3*y2);


    controlPanel = new ControlPanelWidget;
    controlPanel->virtualOffset(listOfScreens.at(index)->geometry().topLeft());
    controlPanel->setVisible(false);
    trackWidget = new TrackWidget();
    trackWidget->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2 + 340,
                                     listOfScreens.at(index)->availableGeometry().y() + y2,
                                     300, 800);

    dspWidget = new DSPWidget();
    dspWidget->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2 + 325 * 2,
                                     listOfScreens.at(index)->availableGeometry().y() + y2,
                                     300, 500);
    //dspWidget->show();

    snrWidget = new SignalNoiseRatioWidget();
    snrWidget->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2 + 325 * 3,
                                     listOfScreens.at(index)->availableGeometry().y() + y2,
                                     600, 600);

    mapDebugger = new MapDebugger();
    mapDebugger->setGeometry(1643, 497,
                             255, 563);
    mapDebugger->show();

    //dspSettingWidget->show();
//    for (quint16 k = 0; k < 10; k++) {
//        CustomPlotterWidget *customPlotterWidget1 = new CustomPlotterWidget();
//        customPlotterWidget1->setGeometry(listOfScreens.at(index)->availableGeometry().x() + x2 + x2 * k,
//                                         listOfScreens.at(index)->availableGeometry().y() + y2 + y2,
//                                         3*x2, 3*y2);
//        customPlotterWidget1->show();
//    }


    engine.load(QUrl("qrc:/SC/ControlUI2.qml"));
    if (engine.rootObjects().isEmpty())
        qDebug() << "Qml cant load";
    auto myElement = engine.rootObjects().at(0);
    connect(this, SIGNAL(openCloseQML(bool)), myElement, SIGNAL(qmlReceive(bool)));


    initControlPanel();

    /*connect(this, &UIController::changeProjection,
            backgroundWidget->getSceneRef(), &Scene::changeProjectionSlot);*/

    initWidgetsInteractions();

    initTcpHandler();

    initSceneCustomizationSignals();

    //initTestConnection();


     /*QQmlApplicationEngine engine2;
     engine2.load(QUrl("qrc:/SC/DSP.qml"));
     if (engine2.rootObjects().isEmpty())
         return -1;*/
}

UIController::~UIController()
{
    tcpThread->quit();
    tcpThread->wait(1000);
}

void UIController::initTestConnection()
{
    /*connect(this, &UIController::addMark,
            backgroundWidget->getSceneRef()->ktaGLData(), &KTAGLData::addKtaMark);
    connect(this, &UIController::addMark,
            ktaInfoWidget, &KTAInfoWidget::addKtaMark);
    testKTAMsg();

    connect(this, &UIController::addRaySet,
            backgroundWidget->getSceneRef()->rayGLData(), &RayGLData::updateRaySetSlot);
    testRayMsg();

    connect(this, &UIController::addTrace,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::addTraceMark);
    connect(this, &UIController::addTrace,
            backgroundWidget->getSceneRef()->test3DData(), &Test3D::addTraceMark);
    //testTraceMsg();
    QTimer::singleShot(1000, this, &UIController::testTraceMsg);*/
}

void UIController::initControlPanel()
{
    connect(backgroundWidget, &Widget::openSectorAddWidget, [this] () {
        if (sectorsViewer->isHidden()) {
            sectorsViewer->show();
            emit windowState(WidgetTypes::Targeting, !sectorsViewer->isHidden());
        }
    });
    connect(backgroundWidget, &Widget::openSectorAddWidget, sectorsViewer, &SectorsViewerWidget::openWidgetWithCurrentParams);
    connect(this, &UIController::windowState, controlPanel, &ControlPanelWidget::changeButtonState);

    connect(sectorsViewer, &SectorsViewerWidget::newSector,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::addSectorSlot);
    connect(sectorsViewer, &SectorsViewerWidget::excludeSector,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::excludeSectorSlot);
    connect(sectorsViewer, &SectorsViewerWidget::presetSector,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::presetSectorSlot);
    connect(sectorsViewer, &SectorsViewerWidget::setSectorInFocus,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::sectorInFocus);
    connect(sectorsViewer, &SectorsViewerWidget::setSectorOutFocus,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::sectorOutFocus);
    connect(sectorsViewer, &SectorsViewerWidget::deleteSector,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::deleteSectorSlot);
    connect(sectorsViewer->getSectorRemoverRef(), &SectorRemover::sectorBlinking,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::setBlinkingActions);

    connect(sectorsViewer, &BaseWidget::exit,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOff);
    connect(ktaInfoWidget, &BaseWidget::exit,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOff);
    connect(sceneCustomazingWindow, &BaseWidget::exit,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOff);
    connect(trackWidget, &BaseWidget::exit,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOff);
    connect(dspWidget, &BaseWidget::exit,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOff);
    connect(snrWidget, &BaseWidget::exit,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOff);


    connect(sectorsViewer, &BaseWidget::open,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOn);
    connect(ktaInfoWidget, &BaseWidget::open,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOn);
    connect(sceneCustomazingWindow, &BaseWidget::open,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOn);
    connect(trackWidget, &BaseWidget::open,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOn);
    connect(dspWidget, &BaseWidget::open,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOn);
    connect(snrWidget, &BaseWidget::open,
            controlPanel, &ControlPanelWidget::simpleChangeButtonStateOn);



    connect(controlPanel, &ControlPanelWidget::openWidgetSignal, [this] (WidgetTypes type) {
        static bool showb = false;
        static bool flag2d = true;
        switch (type) {
        case WidgetTypes::Targeting:
            if (sectorsViewer->isHidden())
                sectorsViewer->show();
            else {
                sectorsViewer->hide();
            }
            break;
        case WidgetTypes::FunctionalControl:
            showb = !showb;
            emit openCloseQML(showb);
            break;
        case WidgetTypes::Track : {
            if (trackWidget->isHidden()) {
                trackWidget->show();
            }
            else
                trackWidget->hide();

            break;
        }
        case WidgetTypes::DSPControl : {
            if (dspWidget->isHidden()) {
                dspWidget->show();
            }
            else
                dspWidget->hide();

            break;
        }
        case WidgetTypes::SignalNoiseRatio : {
            if (snrWidget->isHidden()) {
                snrWidget->show();
            }
            else
                snrWidget->hide();

            break;
        }
        /*case WidgetTypes::VisualControl:
            flag2d = !flag2d;
            emit changeProjection(flag2d);
            break;*/
        case WidgetTypes::KTAInfo:
            if (ktaInfoWidget->isHidden()){
                ktaInfoWidget->show();
            }
            else {
                ktaInfoWidget->hide();
            }
            break;
        case WidgetTypes::Customizing:
            if (sceneCustomazingWindow->isHidden())
                sceneCustomazingWindow->show();
            else {
                sceneCustomazingWindow->hide();
            }
            break;        
        default:
            break;
        }
    });
}

void UIController::initTcpHandler()
{
    tcpThread = new QThread();
    incomingDataHandler = new IncomingDataHandler;
    incomingDataHandler->moveToThread(tcpThread);
    connect(tcpThread, &QThread::finished, incomingDataHandler, &QObject::deleteLater);
    connect(tcpThread, &QThread::finished, tcpThread, &QThread::deleteLater);
    connect(tcpThread, &QThread::started, incomingDataHandler, &IncomingDataHandler::doWork);

    connect(sectorsViewer,
            &SectorsViewerWidget::addSectorsToVOI,
            incomingDataHandler,
            &IncomingDataHandler::sendMsg);
    connect(sectorsViewer,
            &SectorsViewerWidget::deleteSectorToVOI,
            incomingDataHandler,
            &IncomingDataHandler::sendMsg);


    //KTA
        //scene
    connect(incomingDataHandler, &IncomingDataHandler::addPOIMarkSign,
            backgroundWidget->getSceneRef()->ktaGLData(), &KTAGLData::addPOIMarkSlot);
    connect(incomingDataHandler, &IncomingDataHandler::addVOIMarkSign,
            backgroundWidget->getSceneRef()->ktaGLData(), &KTAGLData::addVOIMarkSlot);
        //ktaInfo
    connect(incomingDataHandler, &IncomingDataHandler::addPOIMarkSign,
            ktaInfoWidget, &KTAInfoWidget::addPOIMarkSlot);
    connect(incomingDataHandler, &IncomingDataHandler::addVOIMarkSign,
            ktaInfoWidget, &KTAInfoWidget::addVOIMarkSlot);

    //Trace
    connect(incomingDataHandler, &IncomingDataHandler::addTraceMark,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::addTraceMark);
    /*connect(incomingDataHandler, &IncomingDataHandler::addTraceMark,
            backgroundWidget->getSceneRef()->test3DData(), &Test3D::addTraceMark);*/
    connect(incomingDataHandler, &IncomingDataHandler::resetTraceMark,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::eraseOldTrace);
    /*connect(backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::msgToVOI,
            incomingDataHandler, &IncomingDataHandler::sendMsg);*/
    connect(trackWidget, &TrackWidget::msgToVOI,
            incomingDataHandler, &IncomingDataHandler::sendMsg);

    connect(incomingDataHandler, &IncomingDataHandler::addTraceMark,
            trackWidget, &TrackWidget::addTraceMark);
    connect(incomingDataHandler, &IncomingDataHandler::resetTraceMark,
            trackWidget, &TrackWidget::eraseOldTrace);
    connect(incomingDataHandler, &IncomingDataHandler::resetTraceMark,
            dspWidget, &DSPWidget::removeDSP);


    //Ray
    connect(incomingDataHandler, &IncomingDataHandler::updateRaySet,
            backgroundWidget->getSceneRef()->rayGLData(), &RayGLData::updateRaySetSlot);

    //DSP
    connect(incomingDataHandler, &IncomingDataHandler::dspNewData,
            dspWidget->getDSPDataHandler(), &DSPDataHandler::dspMessageHandler);

    //Trace ID
    /*connect(incomingDataHandler, &IncomingDataHandler::updateInfoAboutTrace,
            dspSettingWidget, &DSPSettingWidget::updateTraceInfo);*/

    //Map
    connect(incomingDataHandler, &IncomingDataHandler::mapUpdate,
            backgroundWidget->getSceneRef()->mapGLData(), &MapGL::update);
    /*connect(backgroundWidget->getSceneRef()->mapGLData(), &MapGL::getNewMap,
            incomingDataHandler, &IncomingDataHandler::sendJsonDocument);*/
    connect(mapDebugger, &MapDebugger::requestForNewMap,
            incomingDataHandler, &IncomingDataHandler::sendJsonDocument);

    tcpThread->start();
}

void UIController::initSceneCustomizationSignals()
{
    customData = new CustomData();

    connect(sceneCustomazingWindow, &SceneCustomazingWindow::themeChangedSignal,
            customData, &CustomData::themeChangeSlot);
    connect(customData, &CustomData::initCustomData,
            sceneCustomazingWindow, &SceneCustomazingWindow::initCustomDataSlot);
    connect(customData, &CustomData::initCustomData,
            backgroundWidget->getSceneRef(), &Scene::initSceneProperties);

    connect(sceneCustomazingWindow, &SceneCustomazingWindow::adChangeGrideColor,
            customData, &CustomData::grideColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::adChangeTextColor,
            customData, &CustomData::grideTextColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::adChangeBackGroundColor,
            customData, &CustomData::backgroundColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::adChangeTextSize,
            customData, &CustomData::grideTextSizeChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::adDistMarkChecked,
            customData, &CustomData::grideDistMarkOnSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::adAzMarkChecked,
            customData, &CustomData::grideAzMarkOnSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::ktaColorChangeSignal,
            customData, &CustomData::ktaColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::ktaSizeChangeSignal,
            customData, &CustomData::ktaSizeChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::sectorsColorChangeSignal,
            customData, &CustomData::sectorsColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::rayMaxDistChangeSignal,
            customData, &CustomData::rayMaxDistChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::traceColorChangeSignal,
            customData, &CustomData::traceColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::traceLBColorChangeSignal,
            customData, &CustomData::traceLBColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::traceLBTextColorChangeSignal,
            customData, &CustomData::traceLBTextColorChangeSlot);
    connect(sceneCustomazingWindow, &SceneCustomazingWindow::traceTextSizeChangeSignal,
            customData, &CustomData::traceTextSizeChangeSlot);

    connect(customData, &CustomData::grideColorChangeEcho,
            backgroundWidget->getSceneRef()->grideData(), &GrideGL::setGrideColor);
    connect(customData, &CustomData::grideTextColorChangeEcho,
            backgroundWidget->getSceneRef()->grideData(), &GrideGL::setTextColor);
    connect(customData, &CustomData::backgroundColorChangeEcho,
            backgroundWidget->getSceneRef(), &Scene::setBackground);
    connect(customData, &CustomData::grideTextSizeChangeEcho,
            backgroundWidget->getSceneRef()->grideData(), &GrideGL::setTextSize);
    connect(customData, &CustomData::grideAzMarkOnEcho,
            backgroundWidget->getSceneRef()->grideData(), &GrideGL::setAzMarkOnOff);
    connect(customData, &CustomData::grideDistMarkOnEcho,
            backgroundWidget->getSceneRef()->grideData(), &GrideGL::setDistMarkOnOff);
    connect(customData, &CustomData::ktaColorChangeEcho,
            backgroundWidget->getSceneRef()->ktaGLData(), &KTAGLData::setKTAColor);
    connect(customData, &CustomData::ktaSizeChangeEcho,
            backgroundWidget->getSceneRef()->ktaGLData(), &KTAGLData::setKTASize);
    connect(customData, &CustomData::sectorsColorChangeEcho,
            backgroundWidget->getSceneRef()->sectorsGLData(), &SectorsGLData::setColor);
    connect(customData, &CustomData::rayColorChangeEcho,
            backgroundWidget->getSceneRef()->rayGLData(), &RayGLData::setColor);
    connect(customData, &CustomData::rayMaxDistChangeEcho,
            backgroundWidget->getSceneRef()->rayGLData(), &RayGLData::setMaxDist);
    connect(customData, &CustomData::traceColorChangeEcho,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::setTraceColor);
    connect(customData, &CustomData::traceLBColorChangeEcho,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::setLogBookColor);
    connect(customData, &CustomData::traceLBTextColorChangeEcho,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::setLogBookColor);
    connect(customData, &CustomData::traceTextSizeChangeEcho,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::setTextSize);

    customData->initDefaultTheme();

}

void UIController::initWidgetsInteractions()
{
    connect(backgroundWidget->getSceneRef(), &Scene::KTASamplingRequest,
            ktaInfoWidget, &KTAInfoWidget::sampledKTAMark);
    connect(ktaInfoWidget, &KTAInfoWidget::drawSampledKTAMarkSignal,
            backgroundWidget->getSceneRef()->ktaGLData(), &KTAGLData::drawSampledMarkSlot);

    connect(backgroundWidget->getSceneRef(), &Scene::targetingAddRequest,
            sectorsViewer, &SectorsViewerWidget::targetingAddSlot);
    connect(backgroundWidget->getSceneRef(), &Scene::targetingExcludeRequest,
            sectorsViewer, &SectorsViewerWidget::targetingExcludeSlot);

    /*connect(backgroundWidget, &Widget::activatedActionWithTrack,
            trackWidget, &TrackWidget::interactiveActionsWithTrack);
    connect(backgroundWidget, &Widget::activatedActionWithTrack,
            trackWidget, &TrackWidget::updateTableByAction);
    connect(trackWidget, &TrackWidget::activatedTableItem,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::interactiveActionsWithTrack);*/
    connect(backgroundWidget, &Widget::activatedActionWithTrack,
            trackWidget, &TrackWidget::interactiveActionsWithTrack);
    connect(trackWidget, &TrackWidget::activeTrackDrawing,
            backgroundWidget->getSceneRef()->traceGLData(), &TraceGLData::drawTrace);


    connect(trackWidget, &TrackWidget::isDSPAvailableSignal, dspWidget, &DSPWidget::dspAvailabilityRequest);
    connect(dspWidget, &DSPWidget::isExceedingUsageLimitSignal, trackWidget, &TrackWidget::isDSPExceedingUsageLimit);
    connect(sectorsViewer, &SectorsViewerWidget::isDSPAvailableSignal, dspWidget, &DSPWidget::dspAvailabilityRequest);
    connect(dspWidget, &DSPWidget::isExceedingUsageLimitSignal, sectorsViewer, &SectorsViewerWidget::isDSPExceedingUsageLimit);

    connect(dspWidget, &DSPWidget::changeDSP, trackWidget, &TrackWidget::changeDSPSlot);
    connect(dspWidget, &DSPWidget::changeDSP, sectorsViewer, &SectorsViewerWidget::changeDSPSlot);

    connect(trackWidget, &TrackWidget::insertDSP, dspWidget, &DSPWidget::insertDSP);
    connect(sectorsViewer, &SectorsViewerWidget::dspActivationOnSector, dspWidget, &DSPWidget::insertDSP);
    connect(sectorsViewer, &SectorsViewerWidget::newSectorToDSPWidget, dspWidget, &DSPWidget::newTarget);
    connect(trackWidget, &TrackWidget::newTrack, dspWidget, &DSPWidget::newTarget);
    connect(sectorsViewer, &SectorsViewerWidget::clearSectorToDSPWidget, dspWidget, &DSPWidget::clearTarget);
    connect(trackWidget, &TrackWidget::eraseTrack, dspWidget, &DSPWidget::clearTarget);

    connect(dspWidget->getDSPDataHandler(), &DSPDataHandler::dspPackToScene, backgroundWidget->getSceneRef()->dspGLData(), &DSPGLData::nextData);
    connect(dspWidget->getDSPDataHandler(), &DSPDataHandler::sendColorRangesOnSceneRepeaterSignal, backgroundWidget->getSceneRef()->dspGLData(), &DSPGLData::setColorRanges);
    connect(dspWidget->getDSPDataHandler(), &DSPDataHandler::deleteDSPFromScene, backgroundWidget->getSceneRef()->dspGLData(), &DSPGLData::eraseDSPData );

    connect(backgroundWidget->getSceneRef()->getCameraPtr(), &Camera::translateCamera,
            mapDebugger, &MapDebugger::updateViewCenter);
    connect(mapDebugger, &MapDebugger::moveCenterOnX,
            backgroundWidget->getSceneRef(), &Scene::setSideSpeedSlot);
    connect(mapDebugger, &MapDebugger::moveCenterOnY,
            backgroundWidget->getSceneRef(), &Scene::setForwardSpeedSlot);
}

/*void UIController::testKTAMsg()
{
    static quint32 counter = 0;
    static float dal = 0, az = 45;
    RLSOPlotMessage msg;
    msg.Azm = az;
    msg.D = dal;
    msg.Ugm = 10;

    dal += 100;
    az += 0.1;

    emit addMark(msg, true);
    counter++;
    //if (counter < 1000)
        QTimer::singleShot(20, this, &UIController::testKTAMsg);
    //else {
    //    counter = 0;
    //    QTimer::singleShot(6000, this, &UIController::testKTAMsg);
        //}
}

void UIController::testTraceMsg()
{
    static float az = 0, dist = 0, speed = 0;
    static float h = 3654;

    RLSOaimMessage msg;
    msg.trackID = 0;
    msg.Az = az;
    msg.D = dist;
    msg.tack = 0;
    msg.vp = speed;
    msg.h = h;

    if (speed < 1200)
        speed += 0.3;
    dist += 43;
    az += 0.33;

    h++;

    emit addTrace(msg);

    QTimer::singleShot(10, this, &UIController::testTraceMsg2);
}

void UIController::testTraceMsg2()
{
    static float az = 50, dist = 35000, speed = 0;
    static float h = 6554;

    RLSOaimMessage msg;
    msg.trackID = 1;
    msg.Az = az;
    msg.D = dist;
    msg.tack = 90;
    msg.vp = speed;
    msg.h = h;

    if (speed < 1200)
        speed += 0.3;
    dist += 43;
    az += 0.33;

    h += 3;

    emit addTrace(msg);

    QTimer::singleShot(10, this, &UIController::testTraceMsg3);
}

void UIController::testTraceMsg3()
{
    static float az = 100, dist = 85000, speed = 0;
    static float h = 9548;

    RLSOaimMessage msg;
    msg.trackID = 2;
    msg.Az = az;
    msg.D = dist;
    msg.tack = 180;
    msg.vp = speed;
    msg.h = h;

    if (speed < 1200)
        speed += 0.3;
    dist += 43;
    az += 0.33;

    h -= 4;

    emit addTrace(msg);

    QTimer::singleShot(10, this, &UIController::testTraceMsg4);
}

void UIController::testTraceMsg4()
{
    static float az = 150, dist = 115000, speed = 0;
    static float h = 11268;

    RLSOaimMessage msg;
    msg.trackID = 3;
    msg.Az = az;
    msg.D = dist;
    msg.tack = 270;
    msg.vp = speed;
    msg.h = h;

    if (speed < 1200)
        speed += 0.3;
    dist += 43;
    az += 0.33;

    h -= 15;

    emit addTrace(msg);

    QTimer::singleShot(10, this, &UIController::testTraceMsg);
}

void UIController::testRayMsg()
{
//    static float az = 0, ugm = 0;

//    RaySet set;
//    for (quint8 index = 0; index < 10; index++) {
//        set.push_back(qMakePair(az, ugm));

//        az += 0.8;
//        if (az > 360) {
//            az -= 360;
//            ugm += 2;
//            if (ugm > 80) {
//                ugm -= 80;
//            }
//        }
//    }

//    emit addRaySet(set);

//    QTimer::singleShot(200, this, &UIController::testRayMsg);
}*/
