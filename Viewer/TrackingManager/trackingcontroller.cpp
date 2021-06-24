#include "trackingcontroller.h"
#include <ConfigurationManager/cfgmanager.h>
#include "datamodel.h"
#include "uiWidgets/raycontrolwidget.h"

#include <QTimer>

TrackingController::TrackingController(QObject *parent)
    : QObject(parent)
{
    radarAzimuth = 0.0f;
    radarElevation = 5.35f;
    incomingDataHandler = nullptr;
    dataModel = new DataModel();
    startDataHandler(true);
}

TrackingController::~TrackingController() {
    //dataModel->cleanModel();
    delete dataModel;
    tcpThread->quit();
    //tcpThread->wait(1000);
    //delete incomingDataHandler;
    //delete tcpThread;
    //qDebug() << "Object and Thread Delete";
}

void TrackingController::startDataHandler(bool locator)
{
    Q_UNUSED(locator);
    /*
    // start incoming data handler thread
    //if (incomingDataHandler == nullptr) {
        incomingDataHandler = new IncomingDataHandler(this);
    //}
    if (!locator) {
        incomingDataHandler->setWorkMode(DATA_HANDLER_READ_LOGS);
    }
    incomingDataHandler->start(QThread::HighPriority);
    //connect(incomingDataHandler, SIGNAL(finished()), incomingDataHandler, SLOT(deleteLater()));
    */

    tcpThread = new QThread();
    incomingDataHandler = new IncomingDataHandler;
    incomingDataHandler->moveToThread(tcpThread);
    connect(tcpThread, &QThread::finished, incomingDataHandler, &QObject::deleteLater);
    connect(tcpThread, &QThread::finished, tcpThread, &QThread::deleteLater);
    connect(tcpThread, &QThread::started, incomingDataHandler, &IncomingDataHandler::doWork);


    connect(CfgManager::Instance()->getUiController()->getRayControlWidget(),
            &RayControlWidget::Msg,
            incomingDataHandler,
            &IncomingDataHandler::sendMsg);

    connect(this, &TrackingController::sendMsg,
            incomingDataHandler, &IncomingDataHandler::sendMsg);

    connect(CfgManager::Instance()->getUiController()->getSettingsWidget()->getRotaryDriveSetting(), &RotaryDriveSetting::Msg, incomingDataHandler,
            &IncomingDataHandler::sendMsg);
    connect(CfgManager::Instance()->getUiController()->getSettingsWidget()->getRotaryDriveSetting2(), &RotaryDriveSetting2::Msg, incomingDataHandler,
            &IncomingDataHandler::sendMsg);
    connect(incomingDataHandler, &IncomingDataHandler::setCurrentWorkStatus,
            CfgManager::Instance()->getUiController()->getStateControlWidget(), &StateOfSystemsWidget::setLocatorWorkMode);

    connect(incomingDataHandler, &IncomingDataHandler::setPPMSignal,
            CfgManager::Instance()->getUiController()->getStateControlWidget()->getPPMWindow(),
            &PPMStateWindow::setStateMsgPPM);

    /*connect(incomingDataHandler, SIGNAL(setPPMSignal(RLSORtmMessage)),
            CfgManager::Instance()->getUiController()->getStateControlWidget()->getPPMWindow(),
            SLOT(setStateMsgPPM(RLSORtmMessage)));*/

    connect(incomingDataHandler, &IncomingDataHandler::setPCSignal,
            CfgManager::Instance()->getUiController()->getStateControlWidget()->getPPMWindow(),
            &PPMStateWindow::setStateMsgPC);

    connect(incomingDataHandler, &IncomingDataHandler::setSBASignal,
            CfgManager::Instance()->getUiController()->getStateControlWidget()->getSBAWindow(),
            &SBAStateWindow::setSBAMessage);

    connect(incomingDataHandler, &IncomingDataHandler::setTime,
            CfgManager::Instance()->getUiController()->getUserTimeWidget(),
            &UserTimeWidget::updateHistoryTime);

    connect(incomingDataHandler, &IncomingDataHandler::subsystemInfoSignal,
            CfgManager::Instance()->getUiController()->getStateControlWidget(),
            &StateOfSystemsWidget::subsystemInfoSlot);

    connect(incomingDataHandler, &IncomingDataHandler::connectionStatusChangedSignal,
            CfgManager::Instance()->getUiController()->getStateControlWidget(),
            &StateOfSystemsWidget::connectionStatusChangedSlot);

    connect(incomingDataHandler, &IncomingDataHandler::setDSPState,
            CfgManager::Instance()->getUiController()->getStateControlWidget()->getPPMWindow(),
            &PPMStateWindow::setDSPStateMsg);

    connect(incomingDataHandler, &IncomingDataHandler::stateRLSO,
            CfgManager::Instance()->getUiController()->getStateControlWidget()->getPPMWindow(),
            &PPMStateWindow::setStateRLSOMsg);

    connect(incomingDataHandler, &IncomingDataHandler::setLocalMapSignal,
            CfgManager::Instance()->getUiController()->getMainUIView()->getAmpGraphicModel(),
            &AmpGraphicModel::setLocalMapSlot);
    connect(incomingDataHandler, &IncomingDataHandler::noiseMessageSignal,
            CfgManager::Instance()->getUiController()->getMainUIView()->getAmpGraphicModel(),
            &AmpGraphicModel::noiseMessageHandler);

    connect(incomingDataHandler, &IncomingDataHandler::setAzSensorSignal,
            CfgManager::Instance()->getUiController()->getRayControlWidget(),
            &RayControlWidget::setAzAntenna);

    connect(incomingDataHandler, &IncomingDataHandler::setCurrentAzSensorSignal,
            CfgManager::Instance()->getUiController()->getRayControlWidget(),
            &RayControlWidget::setCurrentAzAntenna);

    connect(incomingDataHandler, &IncomingDataHandler::setBlindSectorsSignal,
            CfgManager::Instance()->getUiController()->getBlindSectorsWidget(),
            &BlindSectors::setBlindSecorsSlot);

    connect(incomingDataHandler, &IncomingDataHandler::eraseKTA,
            dataModel->getKTAMarkModel(),
            &KTAMarkModel::eraseAllKTA);

    tcpThread->start(QThread::HighPriority);
}

void TrackingController::stopDataHandler(bool cleanModel)
{
    // start incoming data handler thread
    /*if (incomingDataHandler->isRunning()) {
        incomingDataHandler->stop();
        incomingDataHandler->wait();
    }*/
    tcpThread->quit();
    tcpThread->wait(1000);
    delete incomingDataHandler;
    delete tcpThread;
    incomingDataHandler = nullptr;
    tcpThread = nullptr;
    //incomingDataHandler = nullptr;
    // clean model
    /*if (cleanModel) {
        dataModel->cleanModel();
    }*/
}

DataModel* TrackingController::getDataModel()
{
    return dataModel;
}

float TrackingController::getRadarAzimuth() {
    return radarAzimuth;
}

float TrackingController::getRadarElevation() {
    return radarElevation;
}

void TrackingController::setCoordsFour(FourRayCoordMessage *msg)
{
    CoordsFour[0] = msg->x1;
    CoordsFour[1] = msg->y1;
    CoordsFour[2] = msg->x2;
    CoordsFour[3] = msg->y2;
    CoordsFour[4] = msg->x3;
    CoordsFour[5] = msg->y3;
    CoordsFour[6] = msg->x4;
    CoordsFour[7] = msg->y4;

    /*qDebug() << QString::number(CoordsFour[0]) << QString::number(CoordsFour[1]);
    qDebug() << QString::number(CoordsFour[2]) << QString::number(CoordsFour[3]);
    qDebug() << QString::number(CoordsFour[4]) << QString::number(CoordsFour[5]);
    qDebug() << QString::number(CoordsFour[6]) << QString::number(CoordsFour[7]);*/
}

float* TrackingController::getCoordsFour()
{
    return CoordsFour;
}
