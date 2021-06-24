#include "datafilelogger.h"
#include <ConfigurationManager/cfgmanager.h>

//заменить абсолютный путь на относительный
const QString DataFileLogger::LOGS_DIR = QString("/usr/local/code/RMO/logs/");

DataFileLogger::DataFileLogger()
{
    char name[6];
    time_t rawtime;
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf(name, "%02d-%02d", timeinfo->tm_hour, timeinfo->tm_min);
    if( !QDir(LOGS_DIR).exists() ) {
        QDir().mkdir(LOGS_DIR);
    }
    QString yearDir(LOGS_DIR + QString::number(1900 + timeinfo->tm_year));
    if( !QDir(yearDir).exists() ) {
        QDir().mkdir(yearDir);
    }
    QString monthDir(yearDir + "/" + QString::number(timeinfo->tm_mon + 1));
    if( !QDir(monthDir).exists() ) {
        QDir().mkdir(monthDir);
    }
    QString dayDir(monthDir + "/" + QString::number(timeinfo->tm_mday));
    if( !QDir(dayDir).exists() ) {
        QDir().mkdir(dayDir);
    }
    QString fname(dayDir + "/" + name);

    logFile.open(fname.toLocal8Bit(), ios::out | ios::binary);
    dataLoggerModel = new DataLoggerModel();
    running = true;
    //connect( this, SIGNAL( finished() ), this, SLOT( deleteLater() ) );
    moveToThread(this);
}

DataFileLogger::~DataFileLogger()
{
    if( logFile.is_open() ) {
        logFile.close();
    }
    delete dataLoggerModel;
}

void DataFileLogger::run() {
    saveStartTimeStamp();
    timeval *skipBuf = new timeval;
    memset(skipBuf, 0, sizeof(timeval));
    logFile.write((char*) skipBuf, sizeof(timeval));
    delete skipBuf;

    while (running) {
        processData();
    }

    saveStopTimeStamp();
    logFile.close();
    quit();
    //exec();
}

void DataFileLogger::processData() {
    dataLoggerModel->lockDataLoggerModel();
    if(!dataLoggerModel->getProcessQueue()->empty()) {
        switch( dataLoggerModel->getProcessQueue()->front() ) {

        case RLSO_STATE_MESSAGE: {
            RLSOstateMessage *msg = dataLoggerModel->getStateMessageList()->front();
            char id = RLSO_STATE_MESSAGE;
            char size = sizeof(struct RLSOstateMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getStateMessageList()->pop_front();
            break;
        }
        case RLSO_PLOT_MESSAGE: {
            RLSOPlotMessage *msg = dataLoggerModel->getKTAMessageList()->front();
            char id = RLSO_PLOT_MESSAGE;
            char size = sizeof(struct RLSOPlotMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getKTAMessageList()->pop_front();
            break;
        }
        case RLSO_AIM_MESSAGE: {
            RLSOaimMessage *msg = dataLoggerModel->getTrackMessageList()->front();
            char id = RLSO_AIM_MESSAGE;
            char size = sizeof(struct RLSOaimMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getTrackMessageList()->pop_front();
            break;
        }
        /*case RLSO_ANALOG_SIGNAL_MESSAGE: {
            RLSOAnalogSignalMessage *msg = dataLoggerModel->getAnalogSignalMessageList()->front();
            char id = RLSO_ANALOG_SIGNAL_MESSAGE;
            char size = sizeof(struct RLSOAnalogSignalMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getAnalogSignalMessageList()->pop_front();
            break;
        }
        case CP_PRIORITY_TRACK_MESSAGE: {
            ResetTrackMessage *msg = dataLoggerModel->getResetTrackMessageList()->front();
            char id = CP_PRIORITY_TRACK_MESSAGE;
            char size = sizeof(struct ResetTrackMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getResetTrackMessageList()->pop_front();
            break;
        }
        case SHOW_HIDE_WINDOW_MESSAGE: {
            ShowHideWindowMessage *msg = dataLoggerModel->getShowHideWindowMessageList()->front();
            char id = SHOW_HIDE_WINDOW_MESSAGE;
            char size = sizeof(struct ShowHideWindowMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getShowHideWindowMessageList()->pop_front();
            break;
        }
        case MOVE_WINDOW_MESSAGE: {
            MoveWindowMessage *msg = dataLoggerModel->getMoveWindowMessageList()->front();
            char id = MOVE_WINDOW_MESSAGE;
            char size = sizeof(struct MoveWindowMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getMoveWindowMessageList()->pop_front();
            break;
        }
        case RESIZE_WINDOW_MESSAGE: {
            ResizeWindowMessage *msg = dataLoggerModel->getResizeWindowMessageList()->front();
            char id = RESIZE_WINDOW_MESSAGE;
            char size = sizeof(struct ResizeWindowMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getResizeWindowMessageList()->pop_front();
            break;
        }
        case ZOOM_MESSAGE: {
            ZoomMessage *msg = dataLoggerModel->getZoomMessageList()->front();
            char id = ZOOM_MESSAGE;
            char size = sizeof(struct ZoomMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getZoomMessageList()->pop_front();
            break;
        }
        case MOVE_SCALE_MESSAGE: {
            MoveScaleMessage *msg = dataLoggerModel->getMoveScaleMessageList()->front();
            char id = MOVE_SCALE_MESSAGE;
            char size = sizeof(struct MoveScaleMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getMoveScaleMessageList()->pop_front();
            break;
        }
        case EMMITING_CHANGED_MESSAGE: {
//            qDebug() << "writing EMMITING_CHANGED_MESSAGE";
            EmittingChangedMessage *msg = dataLoggerModel->getEmittingChangedMessageList()->front();
            char id = EMMITING_CHANGED_MESSAGE;
            char size = sizeof(struct EmittingChangedMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getEmittingChangedMessageList()->pop_front();
            break;
        }
        case ROT_SPEED_CHANGED_MESSAGE: {
//            qDebug() << "writing ROT_SPEED_CHANGED_MESSAGE";
            RotationSpeedChangedMessage *msg = dataLoggerModel->getRotationSpeedChangedMessageList()->front();
            char id = ROT_SPEED_CHANGED_MESSAGE;
            char size = sizeof(struct RotationSpeedChangedMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getRotationSpeedChangedMessageList()->pop_front();
            break;
        }
        case ROT_STATE_CHANGED_MESSAGE: {
//            qDebug() << "writing ROT_STATE_CHANGED_MESSAGE";
            RotationStateChangedMessage *msg = dataLoggerModel->getRotationStateChangedMessageList()->front();
            char id = ROT_STATE_CHANGED_MESSAGE;
            char size = sizeof(struct RotationStateChangedMessage);
            char buf[size + 1];
            memcpy(buf, &id, 1);
            memcpy(buf + 1, msg, size);
            logFile.write(buf, size + 1);
            delete msg, dataLoggerModel->getRotationStateChangedMessageList()->pop_front();
            break;
        }*/

        }

        dataLoggerModel->getProcessQueue()->pop_front();
    }
    dataLoggerModel->unlockDataLoggerModel();
}

void DataFileLogger::saveStartTimeStamp() {
    timeval startTimeStamp;
    gettimeofday(&startTimeStamp, NULL);
    logFile.write((char*) &startTimeStamp, sizeof(timeval));
}

void DataFileLogger::saveStopTimeStamp() {
    timeval endTimeStamp;
    gettimeofday(&endTimeStamp, NULL);
    logFile.seekp(sizeof(timeval));
    logFile.write((char*) &endTimeStamp, sizeof(timeval));
}
