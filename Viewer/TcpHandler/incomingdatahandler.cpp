#include "incomingdatahandler.h"
#include <QNetworkConfigurationManager>
#include <QEventLoop>
#include <QDataStream>
#include <QTime>

//const QUrl url = QUrl::fromUserInput(QLatin1String("192.168.1.36:4242"));// home
//const QUrl url = QUrl::fromUserInput(QLatin1String("192.168.115.212:4242"));// my
//const QUrl url = QUrl::fromUserInput(QLatin1String("192.168.115.219:4242"));//bochenev
const QUrl url = QUrl::fromUserInput(QLatin1String("127.0.0.1:4242"));
//const QUrl localHost = QUrl::fromUserInput(QLatin1String("127.0.0.1:4242"));

IncomingDataHandler::IncomingDataHandler() :
    localHost(QUrl::fromUserInput(QLatin1String("127.0.0.1:10000")))
{
    workMode = DATA_HANDLER_LOCATOR;
    running = true;
    seekValue = 0;    
}

IncomingDataHandler::~IncomingDataHandler()
{
    // TODO: release memory!
    //pUdpSocket->abort();
    //delete pUdpSocket;
    pTcpSocket->abort();
    //pTcpSocket->disconnectFromHost();
    delete pTcpSocket;
    //qDebug() << "Tcp Socket Delete";
}

void IncomingDataHandler::doWork()
{
    //qDebug() << "IncomingDataHandler thread started!";
    //qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");

    //evLoop = new QEventLoop;
    //evLoop->moveToThread(this);
    //pUdpSocket = new QUdpSocket;
    //pUdpSocket->moveToThread(this);
    pTcpSocket = new QTcpSocket();
    //pTcpSocket->moveToThread(this);

    connect(pTcpSocket, &QTcpSocket::connected, this, &IncomingDataHandler::slotConnected);
    pTcpSocket->connectToHost(url.host(), url.port(), QIODevice::ReadWrite);
    //pTcpSocket->connectToHost(urlLocalHost.host(), urlLocalHost.port(), QIODevice::ReadWrite);
    connect(pTcpSocket, &QTcpSocket::disconnected, this, &IncomingDataHandler::disconnected);
    //connect(pTcpSocket, &QTcpSocket::error, this, &IncomingDataHandler::connectionError);
    connect(pTcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &IncomingDataHandler::connectionError);

    pTcpSocketForMap = new QTcpSocket();
    connect(pTcpSocketForMap, &QTcpSocket::connected, this, &IncomingDataHandler::slotConnected);
    pTcpSocketForMap->connectToHost(localHost.host(), localHost.port(), QIODevice::ReadWrite);
    //pTcpSocket->connectToHost(urlLocalHost.host(), urlLocalHost.port(), QIODevice::ReadWrite);
    connect(pTcpSocketForMap, &QTcpSocket::disconnected, this, &IncomingDataHandler::disconnected);
    //connect(pTcpSocket, &QTcpSocket::error, this, &IncomingDataHandler::connectionError);
    connect(pTcpSocketForMap, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &IncomingDataHandler::connectionError);
}

void IncomingDataHandler::sendJsonDocument(QJsonDocument doc)
{
    if (pTcpSocketForMap->state() == QTcpSocket::ConnectedState) {
        pTcpSocketForMap->write(doc.toJson());
        pTcpSocketForMap->flush();
    }
}

void IncomingDataHandler::slotConnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

    if (socket == pTcpSocket) {

        QVector<quint8> usedMessages {
            POI_KTA_MESSAGE,
                    VOI_RMO_MARK_MESSAGE,
                    RLSO_AIM_MESSAGE,
                    RLSO_RMO_DSP_DATA_MESSAGE,
                    VOI_RMO_TRACK_DELETE_MESSAGE,
                    SIM_CURRENT_PLAY_TIME,
                    RARM_SYSTEM_CONTROL_MESSAGE,
                    VOI_RMO_RAY_SET_MESSAGE,
        };

        qDebug() << "Connected to MMiP Server. Send HandShake Msg";
        QByteArray datagram;

        QDataStream out(&datagram, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(255);
        out << quint8(RMO_SYS_ID);
        for (const auto &item : usedMessages) {
            out << item;
        }
        out.device()->seek(0);
        out << quint16(datagram.size() - sizeof(quint16));

        pTcpSocket->write(datagram);
        pTcpSocket->flush();

        //oldData = false;
        unhandledData.clear();

        connect(pTcpSocket, &QTcpSocket::readyRead, this, &IncomingDataHandler::readData);

        //emit connectionStatusChangedSignal(true);

    }
    else if (socket == pTcpSocketForMap) {
        connect(pTcpSocketForMap, &QTcpSocket::readyRead, this, &IncomingDataHandler::readDataForMap);
    }
}

void IncomingDataHandler::readData()
{
    //qDebug() << "socket data recieved: " << pUdpSocket->size() << " bytes " << " datagramm: " << pUdpSocket->pendingDatagramSize();

    /*if (oldData)
        oldData = false;
    else
        unhandledData.clear();*/
    unhandledData.append(pTcpSocket->readAll());

    //QByteArray socketData(pTcpSocket->readAll());
    /*socketData.resize(pUdpSocket->pendingDatagramSize());
    pUdpSocket->readDatagram(socketData.data(), socketData.size());*/
    QDataStream in(&unhandledData, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_3);
    in.setByteOrder(QDataStream::LittleEndian);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);

    static quint8 lastID;
    static quint16 lastSize;
    static quint32 lastPos;
    quint8 msgID;
    quint16 size;
    bool headerHandling = false;
    in >> size;
    in >> msgID;
    while ((size - 1) <= (unhandledData.size() - in.device()->pos())) {
        headerHandling = true;
        lastPos = in.device()->pos();
        switch(msgID) {        

        case VOI_RMO_MARK_MESSAGE: {
            VOIMarkMessage *msg = new VOIMarkMessage;
            in.readRawData((char*) msg, size - 1);

            msg->flag_target = true; // Флаг вторичной отметки в неиспользуемом поле
            emit addVOIMarkSign(*msg);
            //qDebug() << "VOI_RMO_MARK_MESSAGE";

            delete msg;
            break;
        }
        case RLSO_AIM_MESSAGE: {
            RLSOaimMessage *msg = new RLSOaimMessage;
            in.readRawData((char*) msg, sizeof(RLSOaimMessage));

            emit addTraceMark(*msg);
            emit updateInfoAboutTrace(msg->trackID, false);
            //qDebug() << "RLSO_AIM_MESSAGE";

            delete msg;
            break;
        }
        case VOI_RMO_TRACK_DELETE_MESSAGE: {
            DeleteTrackMessage *msg = new DeleteTrackMessage;
            in.readRawData((char*) msg, sizeof(DeleteTrackMessage));

            //CfgManager::Instance()->getTrackingController()->getDataModel()->deleteTrack(msg->aimID);
            //emit resetTrackSignal(msg->aimID);
            //CfgManager::Instance()->getTrackingController()->getDataModel()->resetTrack(msg->aimID);

            emit resetTraceMark(msg->aimID);
            emit updateInfoAboutTrace(msg->aimID, true);

            delete msg;
            break;
        }

        case SIM_CURRENT_PLAY_TIME: {
            simTimeInFile *msg = new simTimeInFile;
            in.readRawData((char*) msg, sizeof(simTimeInFile));

            //emit setTime(msg->timeStart.tv_sec);

            delete msg;
            break;
        }
        case RARM_SYSTEM_CONTROL_MESSAGE: {
            RARMSysControlMessage *msg = new RARMSysControlMessage;
            in.readRawData((char*) msg, /*sizeof(RARMSysControlMessage)*/size - 1);
            lastPos = in.device()->pos();

            //emit subsystemInfoSignal(msg->sysControl);

            delete msg;
            break;
        }

        case VOI_RMO_RAY_SET_MESSAGE: {
            VOIRaySetMessage *msg = new VOIRaySetMessage;
            in.readRawData((char*) msg, size - 1);

            RaySet mapOfRays;
            for (quint16 index = 0; index < msg->count; index++) {
                auto iterOfMapOfRays = mapOfRays.find(msg->id[index]);
                if (iterOfMapOfRays != mapOfRays.end()) {
                    iterOfMapOfRays.value().push_back(RayInfo(msg->az[index],
                                                              msg->ugm[index]));
                }
                else {
                    mapOfRays.insert(msg->id[index], QVector<RayInfo>( { RayInfo(msg->az[index],
                                                                         msg->ugm[index]) } ));
                }
            }

            emit updateRaySet(mapOfRays);
            //qDebug() << "VOI_RMO_RAY_SET_MESSAGE";

            delete msg;
            break;
        }
        case POI_KTA_MESSAGE: {
            POIKtaMessage *msg = new POIKtaMessage;
            in.readRawData((char*) msg, size - 1);

            emit addPOIMarkSign(*msg);

            //qDebug() << "POI_KTA_MESSAGE";

            delete msg;
            break;
        }
        case RLSO_RMO_DSP_DATA_MESSAGE : {
            RLSODSPDataMessage msg;
            in.readRawData((char*) &msg, size - 1);

            emit dspNewData(msg);

            break;
        }



        default: {
            //qDebug() << "Error! Unknown message " << msgID << " recieved! Seeking " << size;
            //unhandledData.clear();
            //return;

            /* if ((unhandledData.size() - in.device()->pos()) >= size) {
                in.device()->seek(size);
                seekValue = 0;
            }
            else {
                in.device()->seek(unhandledData.size() - in.device()->pos());
                seekValue = size - (unhandledData.size() - in.device()->pos());
            }*/
            char *unknownMsg = new char;
            in.readRawData((char*) unknownMsg, size - 1);
            delete unknownMsg;

            break;
        }
        }
        if ((unhandledData.size() - in.device()->pos()) > 3) {
            lastPos = in.device()->pos();
            lastID = msgID;
            lastSize = size;
            in >> size;
            in >> msgID;
            headerHandling = false;
        }
    }


    if (!headerHandling) {
        in.device()->seek(in.device()->pos() - 3);        
    }
    unhandledData.remove(0, in.device()->pos());
}

void IncomingDataHandler::readDataForMap()
{
    //unhandledDataForMap.append(pTcpSocketForMap->readAll());

    //QJsonParseError *error;

    QJsonDocument document = QJsonDocument::fromJson(pTcpSocketForMap->readAll());

    emit mapUpdate(document);
}

void IncomingDataHandler::connectionError(QAbstractSocket::SocketError socketError)
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

    if (socket == pTcpSocket) {
        if (socketError ==  QAbstractSocket::ConnectionRefusedError ||
            socketError ==  QAbstractSocket::HostNotFoundError ||
            socketError ==  QAbstractSocket::SocketTimeoutError ||
            socketError ==  QAbstractSocket::NetworkError) {
            //qDebug() << "Try to connect again..."; //spam
            pTcpSocket->connectToHost(url.host(), url.port(), QIODevice::ReadWrite);
            //pTcpSocket->connectToHost(urlLocalHost.host(), urlLocalHost.port(), QIODevice::ReadWrite);
        }
        else
            qDebug() << "Unknown error";
    }
    else if (socket == pTcpSocketForMap) {
        if (socketError ==  QAbstractSocket::ConnectionRefusedError ||
            socketError ==  QAbstractSocket::HostNotFoundError ||
            socketError ==  QAbstractSocket::SocketTimeoutError ||
            socketError ==  QAbstractSocket::NetworkError) {
            //qDebug() << "Try to connect again..."; //spam
            pTcpSocketForMap->connectToHost(localHost.host(), localHost.port(), QIODevice::ReadWrite);
            //pTcpSocket->connectToHost(urlLocalHost.host(), urlLocalHost.port(), QIODevice::ReadWrite);
        }
        else
            qDebug() << "Unknown error";
    }
}

void IncomingDataHandler::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

    if (socket == pTcpSocket) {
        qDebug() << "Disconnected from MMiP Server. Try to connect again...";
        disconnect(pTcpSocket,SIGNAL(readyRead()),this,SLOT(readData()));
        pTcpSocket->connectToHost(url.host(), url.port(), QIODevice::ReadWrite);

        //emit connectionStatusChangedSignal(false);
        //pTcpSocket->connectToHost(urlLocalHost.host(), urlLocalHost.port(), QIODevice::ReadWrite);
    }
    else if (socket == pTcpSocketForMap) {
        //qDebug() << "Disconnected from MMiP Server. Try to connect again...";
        disconnect(pTcpSocketForMap, SIGNAL(readyRead()),this,SLOT(readDataForMap()));
        pTcpSocketForMap->connectToHost(localHost.host(), localHost.port(), QIODevice::ReadWrite);
    }
}

void IncomingDataHandler::resetSocket() {
    /*pUdpSocket->abort();
    if(workMode == DATA_HANDLER_LOCATOR) {
        pUdpSocket->bind(QHostAddress::LocalHost, CfgManager::LOCATOR_LISTEN_PORT);
    } else {
        pUdpSocket->bind(QHostAddress::LocalHost, CfgManager::LLF_READ_LISTEN_PORT);
        //connect(this, SIGNAL(logReadDone(int)), CfgManager::Instance()->getUiController()->getLLFReaderControlWidget(), SLOT(readingDone(int)), Qt::QueuedConnection);
    }*/
    pTcpSocket->abort();
    pTcpSocket->connectToHost(url.host(), url.port(), QIODevice::ReadWrite);
    //pTcpSocket->connectToHost(urlLocalHost.host(), urlLocalHost.port(), QIODevice::ReadWrite);
}

int IncomingDataHandler::getMessageSize(quint8 id) {
    int retVal = 1;

    /*switch (id) {

        case RLSO_RESET_DSP_MESSAGE:
            retVal = 1;
            break;
        case RLSO_COMMAND_MESSAGE:
            retVal = sizeof(RLSOCommandMessage);
            break;
        case RLSO_ANSWER_COMMAND_MESSAGE:
            retVal = sizeof(RLSOCommandMessage);
            break;
        case RLSO_STATE_MESSAGE:
            retVal = sizeof(RLSOPoiStateMessage);
            break;
        case RLSO_PLOT_MESSAGE:
            retVal = sizeof(RLSOPlotMessage);
            break;
        case RLSO_AIM_MESSAGE:
            retVal = sizeof(RLSOaimMessage);
            break;
        case CP_PRIORITY_TRACK_MESSAGE:
            retVal = sizeof(ResetTrackMessage);
            break;
        case GK_COORDS_MESSAGE:
            retVal = sizeof(GKCoordsRlsMessage);
            break;
        case COORDS_RAY_MESSAGE:
            retVal = sizeof(FourRayCoordMessage);
            break;
        case MYO_TIME_SCANNING_MESSAGE:
            retVal = sizeof(MYOTimeScanningMessage);
            break;
        case VOI_WORK_ZONE_MESSAGE:
            retVal = sizeof(VOIWorkZoneMessage);
            break;
        case INS_MESSAGE:
            retVal = sizeof(ProtocolINS);
            break;
        case MYO_COORDINATES_TARGET_MESSAGE:
            retVal = sizeof(MYOCoodinatesTargetMessage);
            break;
        case MYO_CALIBRATION_MESSAGE:
            retVal = sizeof(MYOCalibrationMessage);
            break;
        case MYO_SETTINGS_MODE_MESSAGE:
            retVal = sizeof(MYOSettingsModeMessage);
            break;
        case MYO_MANUAL_MODE_MESSAGE:
            retVal = sizeof(MYOManualModeMessage);
            break;
        case MYO_INT_COMMAND_MESSAGE:
            retVal = sizeof(MYOIntCommandMessage);
            break;
        case MYO_QUERY_MESSAGE:
            retVal = sizeof(MYOQueryMessage);
            break;
        case MYO_INIT_MESSAGE:
            retVal = sizeof(MYOInitMessage);
            break;
        case MYO_CONFIG_TARGET_MESSAGE:
            retVal = sizeof(MYOConfigTargetMessage);
            break;
        case MYO_PARKIN_MESSAGE:
            retVal = sizeof(MYOParkingMessage);
            break;
        case MYO_READY_MESSAGE:
            retVal = sizeof(MYOReadyMessage);
            break;
        case RLSO_START_RAY_MESSAGE:
            retVal = sizeof(RLSOStartRayMessage);
            break;
        case RLSO_FINISH_RAY_MESSAGE:
            retVal = sizeof(RSLOFinishRayMessage);
            break;
        case RLSO_AZIMUTH_SENSOR_MESSAGE:
            retVal = sizeof(RSLOAzimuthSensorMessage);
            break;
        case RLSO_GENERATOR_MESSAGE:
            retVal = sizeof(RLSOGeneratorMessage);
            break;
        case RLSO_RTM_MESSAGE:
            retVal = sizeof(RLSORtmMessage);
            break;
        case RLSO_DRIVE_CMD_MESSAGE:
            retVal = sizeof(RLSODriveCmdMessage);
            break;
        case RLSO_DRIVE_ANS_MESSAGE:
            retVal = sizeof(RLSODriveAnsMessage);
            break;
        case RLSO_DSP_CONFIG_MESSAGE:
            retVal = sizeof(RLSODspConfigMessage);
            break;
        case RLSO_DSP_STATE_MESSAGE:
            retVal = sizeof(RLSODspStateMessage);
            break;
        case RLSO_TIME_MESSAGE:
            retVal = 1;
            break;

        case RLSO_ESCORT_AIM_MESSAGE:
            retVal = 1;
            break;
        case RLSO_IMITATOR_PLOT_MESSAGE:
            retVal = 1;
            break;
        case RLSO_ERASE_KTA_MESSAGE:
            retVal = 1;
            break;
        case RLSO_POI_DATA_MESSAGE:
            retVal = 1;
            break;
        case RLSO_AZ_ERROR_MESSAGE:
            retVal = sizeof(RLSOAZErrorMessage);
            break;
        case RLSO_FINISH_SEND_POI_MESSAGE:
            retVal = 1;
            break;
        case VOI_PLOT_MESSAGE:
            retVal = sizeof(RLSOPlotMessage);
            break;
        case RMO_OUTSIDE_COORD_TARGET_MESSAGE:
            retVal = sizeof(MYOCoodinatesTargetMessage);
            break;
        case RMO_OUTSIDE_CONFIG_TARGET_MESSAGE:
            retVal = sizeof(MYOConfigTargetMessage);
            break;
        case SIM_GK_COORDS_MESSAGE:
            retVal = sizeof(GKCoordsRlsMessage);
            break;
        case SIM_PWD_START_MESSAGE:
            retVal = sizeof(SIMStartPowerMessage);
            break;
        case SIM_PWD_STATE_MESSAGE:
            retVal = sizeof(SIMStatePowerMessage);
            break;
        case SIM_PWD_ANSWER:
            retVal = sizeof(SIMPowerModuleAnswerMessage);
            break;
        case SIM_MES_ON:
            retVal = sizeof(SimMessageOn);
            break;
        case SIM_CHANGE_FILE:
            retVal = 0;
            break;
        case TM_MESSAGE:
            retVal = sizeof(TmMessage);
            break;
        case ALL_SYSTEM_HANDSHAKE:
            retVal = sizeof(HandshakeMessage);
            break;

        default:
            break;
    }*/

    return retVal;
}
