#include "dataloggermodel.h"
#include <ConfigurationManager/cfgmanager.h>

DataLoggerModel::DataLoggerModel()
{
}

DataLoggerModel::~DataLoggerModel()
{
}

void DataLoggerModel::addStateMessage(RLSOstateMessage* msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    stateMessageList.push_back(msg);
    processQueue.push_back(RLSO_STATE_MESSAGE);
    //qDebug() << "push:" << RLSO_STATE_MESSAGE;
    unlockDataLoggerModel();
}

void DataLoggerModel::addKTAMessage(RLSOPlotMessage* msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    ktaMessageList.push_back(msg);
    processQueue.push_back(RLSO_PLOT_MESSAGE);
    //qDebug() << "push:" << RLSO_PLOT_MESSAGE;
    unlockDataLoggerModel();
}

void DataLoggerModel::addTrackMessage(RLSOaimMessage* msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    trackMessageList.push_back(msg);
    processQueue.push_back(RLSO_AIM_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}

/*void DataLoggerModel::addAnalogSignalMessage(RLSOAnalogSignalMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    analogSignalMessageList.push_back(msg);
    processQueue.push_back(RLSO_ANALOG_SIGNAL_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}*/

void DataLoggerModel::addResetTrackMessage(ResetTrackMessage* msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    resetTrackMessageList.push_back(msg);
    processQueue.push_back(CP_PRIORITY_TRACK_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}

void DataLoggerModel::addFourRayCoordMessage(FourRayCoordMessage* msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    fourRayCoordMessageList.push_back(msg);
    processQueue.push_back(COORDS_RAY_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}

void DataLoggerModel::addGKCoordsRlsMessage(GKCoordsRlsMessage* msg) {
    if(stopingDataLogger) {
        return;
    }

    lockDataLoggerModel();
    gkCoordsRlsMessageList.push_back(msg);
    processQueue.push_back(GK_COORDS_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}

/*void DataLoggerModel::addShowHideWindowMessage(ShowHideWindowMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    showHideWindowMessageList.push_back(msg);
    processQueue.push_back(SHOW_HIDE_WINDOW_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addResizeWindowMessage(ResizeWindowMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    resizeWindowMessageList.push_back(msg);
    processQueue.push_back(RESIZE_WINDOW_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addZoomMessage(ZoomMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    zoomMessageList.push_back(msg);
    processQueue.push_back(ZOOM_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addMoveScaleMessage(MoveScaleMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    moveScaleMessageList.push_back(msg);
    processQueue.push_back(MOVE_SCALE_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addMoveWindowMessage(MoveWindowMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    moveWindowMessageList.push_back(msg);
    processQueue.push_back(MOVE_WINDOW_MESSAGE);
    //qDebug() << "push:" << RLSO_AIM_MESSAGE;
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addEmittingChangedMessage(EmittingChangedMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    emittingChangedMessageList.push_back(msg);
    processQueue.push_back(EMMITING_CHANGED_MESSAGE);
    //qDebug() << "addEmittingChangedMessage()";
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addRotationSpeedChangedMessage(RotationSpeedChangedMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    rotationSpeedChangedMessageList.push_back(msg);
    processQueue.push_back(ROT_SPEED_CHANGED_MESSAGE);
    //qDebug() << "addRotationSpeedChangedMessage()";
    unlockDataLoggerModel();
}*/

/*void DataLoggerModel::addRotationStateChangedMessage(RotationStateChangedMessage *msg) {
    if(stopingDataLogger) {
        return;
    }

    gettimeofday(&msg->sTimeStamp, NULL);
    lockDataLoggerModel();
    rotationStateChangedMessageList.push_back(msg);
    processQueue.push_back(ROT_STATE_CHANGED_MESSAGE);
    //qDebug() << "addRotationStateChangedMessage()";
    unlockDataLoggerModel();
}*/
