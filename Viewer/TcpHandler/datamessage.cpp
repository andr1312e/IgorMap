#include "datamessage.h"

// возвращает размер сообщения в зависимости от ID сообщения
// возвращает -1 в случае неверного ID на входе
int getMessageSize(MESSAGE_ID id) {
    int retVal = -1;

    switch (id) {

        case CMD_START_RADIATION_MESSAGE:
            retVal = WORK_MODE_MESSAGE_SIZE;
            break;
        case CMD_CHANGE_RT_MESSAGE:
            retVal = IVO_AIM_MESSAGE_SIZE;
            break;
        case RLSO_STATE_MESSAGE:
            retVal = ASHP_MESSAGE_SIZE;
            break;
        case RLSO_PLOT_MESSAGE:
            retVal = PP_MESSAGE_SIZE;
            break;
        case RLSO_AIM_MESSAGE:
            retVal = SECTOR_VIEW_MESSAGE_SIZE;
            break;
        case CP_PRIORITY_TRACK_MESSAGE:
            retVal = RLSO_STATE_MESSAGE_SIZE;
            break;
        case GK_COORDS_MESSAGE:
            retVal = RLSO_AIM_MESSAGE_SIZE;
            break;
        case COORDS_RAY_MESSAGE:
            retVal = RLSO_ASHP_PING_MESSAGE_SIZE;
            break;
        case INS_MESSAGE:
            retVal = RLSS_STATE_MESSAGE_SIZE;
            break;
        case MYO_COORDINATES_TARGET_MESSAGE:
            retVal = RLSS_AIM_MESSAGE_SIZE;
            break;
        case MYO_CALIBRATION_MESSAGE:
            retVal = RLSS_ASHP_PING_MESSAGE_SIZE;
            break;
        case MYO_SETTINGS_MODE_MESSAGE:
            retVal = CP_AIM_POINTING_MESSAGE_SIZE;
            break;
        case MYO_MANUAL_MODE_MESSAGE:
            retVal = RLSS_AIM_POINTING_MESSAGE_SIZE;
            break;
        case MYO_RESET_MESSAGE:
            retVal = CP_RESET_TRACK_MESSAGE_SIZE;
            break;
        case MYO_QUERY_MESSAGE:
            retVal = RLSS_RESET_TRACK_MESSAGE_SIZE;
            break;
        case MYO_INIT_MESSAGE:
            retVal = RLSS_STATE_MESSAGE_SIZE;
            break;
        case MYO_CONFIG_TARGET_MESSAGE:
            retVal = RLSS_AIM_MESSAGE_SIZE;
            break;
        case MYO_PARKIN_MESSAGE:
            retVal = RLSS_ASHP_PING_MESSAGE_SIZE;
            break;
        case MYO_READY_MESSAGE:
            retVal = CP_AIM_POINTING_MESSAGE_SIZE;
            break;
        case RLSO_START_RAY_MESSAGE:
            retVal = RLSS_AIM_POINTING_MESSAGE_SIZE;
            break;
        case RLSO_FINISH_RAY_MESSAGE:
            retVal = CP_RESET_TRACK_MESSAGE_SIZE;
            break;
        case RLSO_AZIMUTH_SENSOR_MESSAGE:
            retVal = RLSS_RESET_TRACK_MESSAGE_SIZE;
            break;
        case RLSO_GENERATOR_MESSAGE:
            retVal = RLSS_STATE_MESSAGE_SIZE;
            break;
        case RLSO_RTM_MESSAGE:
            retVal = RLSS_AIM_MESSAGE_SIZE;
            break;
        case RLSO_DRIVE_CMD_MESSAGE:
            retVal = RLSS_ASHP_PING_MESSAGE_SIZE;
            break;
        case RLSO_DRIVE_ANS_MESSAGE:
            retVal = CP_AIM_POINTING_MESSAGE_SIZE;
            break;
        case RLSO_DSP_CONFIG_MESSAGE:
            retVal = RLSS_AIM_POINTING_MESSAGE_SIZE;
            break;
        case RLSO_DSP_STATE_MESSAGE:
            retVal = CP_RESET_TRACK_MESSAGE_SIZE;
            break;
        case RLSO_TIME_MESSAGE:
            retVal = RLSS_RESET_TRACK_MESSAGE_SIZE;
            break;
        case RLSO_DSP_PARAMS_MESSAGE:
            retVal = RLSS_STATE_MESSAGE_SIZE;
            break;
        case RLSO_IMITATOR_CONFIG_MESSAGE:
            retVal = RLSS_AIM_MESSAGE_SIZE;
            break;
        case RLSO_ESCORT_AIM_MESSAGE:
            retVal = RLSS_ASHP_PING_MESSAGE_SIZE;
            break;
        case RLSO_IMITATOR_PLOT_MESSAGE:
            retVal = CP_AIM_POINTING_MESSAGE_SIZE;
            break;
        case RLSO_ERASE_KTA_MESSAGE:
            retVal = RLSS_AIM_POINTING_MESSAGE_SIZE;
            break;
        case RMO_OUTSIDE_COORD_TARGET_MESSAGE:
            retVal = CP_RESET_TRACK_MESSAGE_SIZE;
            break;
        case RMO_OUTSIDE_CONFIG_TARGET_MESSAGE:
            retVal = RLSS_RESET_TRACK_MESSAGE_SIZE;
            break;
        case SIM_GK_COORDS_MESSAGE:
            retVal = RLSS_STATE_MESSAGE_SIZE;
            break;
        case SIM_PWD_START_MESSAGE:
            retVal = RLSS_AIM_MESSAGE_SIZE;
            break;
        case SIM_PWD_STATE_MESSAGE:
            retVal = RLSS_ASHP_PING_MESSAGE_SIZE;
            break;
        case SIM_PWD_ANSWER:
            retVal = CP_AIM_POINTING_MESSAGE_SIZE;
            break;
        case TM_MESSAGE:
            retVal = RLSS_AIM_POINTING_MESSAGE_SIZE;
            break;

        default:
            break;
    }

    return retVal;
}
