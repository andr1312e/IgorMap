/*
 * data_messages.h
 *
 *  Created on: 5 июн. 2017 г.
 *      Автор: Алексей Тихомиров
 *      Главный редактор: Игорь Микеров
 *      АО "КБ "Кунцево"
 */

#ifndef DATA_MESSAGES_H_
#define DATA_MESSAGES_H_

#define DRIVE_COMMAND_LENGTH        512             // Максимальная длина сообщения от/на привод

#define TCP_PORT_RMO_SERVER         4242            // TCP-порт сервера РМО (на который вычислитель отправляет сообщения)
#define TCP_PORT_BOARD_SERVER       40005           // TCP-порт сервера вычислителя (на который РМО отправляет команды управления)

//#include <time.h>
#include <QtGlobal>

struct timeval64
{
    quint64 tv_sec;		/* Seconds.  */
    quint64 tv_usec;	/* Microseconds.  */
};

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

enum MESSAGE_ID    {  // не менять

    RLSO_AIM_MESSAGE                 = 10,          // Сообщение о трассе цели (ИРЛС-О -> ИКБУ, МЦУВК)
    RMO_VOI_TRACK_SETTING_MESSAGE    = 11,          // Сообщение с настройками трассы
    RMO_VOI_TRACK_DELETE_MESSAGE     = 18,          // Сообщение об удалении трассы от РМО
    VOI_RMO_TRACK_DELETE_MESSAGE     = 19,          // Сообщение об удалении трассы от вторички   

    RLSO_RMO_DSP_DATA_MESSAGE        = 30,          // Сообщение с данными ДСП

    POI_KTA_MESSAGE                  = 72,
    VOI_RMO_MARK_MESSAGE             = 109,         // Сообщение о КТА от ВОИ

    VOI_RMO_CREATE_SPECIAL_SECTOR_MESSAGE = 113,    // Сообщение о создании спец-сектора
    VOI_RMO_DELETE_SPECIAL_SECTOR_MESSAGE = 114,    // Сообщение об удалении спец-сектора
    RMO_VOI_TARGET_POSITION_MESSAGE  = 115,         // Сообщение с параметрами ЦУ
    RMO_VOI_TARGET_DELETE_MESSAGE    = 116,         // Сообщение с удалением ЦУ
    VOI_RMO_RAY_SET_MESSAGE          = 117,         // Сообщение с набором лучей на следующий такт

    SIM_CHANGE_FILE                  = 125,         // Сообщение об изменении файла для воспроизведения
    SIM_RREWIND_FILE                 = 126,         // Сообщение для перемотки файла воспроизведения
    SIM_PLAY_ON                      = 127,         // Сообщение для запуска/остановки воспроизведения
    SIM_CURRENT_PLAY_TIME            = 128,         // Сообщение о времени воспроизведения из файла    

    RARM_SYSTEM_CONTROL_MESSAGE      = 253,         // Сообщение с состоянием подсистем
    RMO_REGFILE_CLOSE                = 254,         // Закрытие файла регистрации
    ALL_SYSTEM_HANDSHAKE             = 255          // Сообщение о рукопожатии с ММИРом
};

enum SYSTEMS_ID    {
    POI_SYS_ID,
    VOI_SYS_ID,
    RMO_SYS_ID,
    RARM_SYS_ID,
    MUO_SYS_ID,
    SENDER_SYS_ID,
    NAVIGATION_SYS_ID,
    MODBUS_SYS_ID,
    POI_SYS_ID_INCOMMING_CONN,
    PROGRAM_SIMULATOR_SYS_ID,

    PPS_SYS_ID,
    ROTOR_SYS_ID,
};

enum SIM_PLAY_CONTROL {
    SIM_CMD_PLAY            = 1,
    SIM_CMD_PAUSE           = 0,
    SIM_CMD_HALF_SPEED      = 3,
    SIM_CMD_2x              = 2,
    SIM_CMD_4x              = 4,
    SIM_CMD_8x              = 8,
    SIM_CMD_STOP            = 255,
};

enum TRACK_STATE {                  // признак состояния трассы
    TRACK_STATE_BOUNDED_AGAIN,      // вновь завязанная
    TRACK_STATE_FOLLOWED,           // сопровождаемая
    TRACK_STATE_FOLLOWED_WO_SIGN,   // сопровождаемая без отметки пеленга
    TRACK_STATE_RESET,              // сброс трассы
    TRACK_STATE_PLOT,               // первая отметка
    TRACK_STATE_ASPT,               // вторая отметка
    TRACK_STATE_DELETED             // удаленная трасса
};

enum RLSOCommandId  {
    CmdRadiation = 1,
    CmdWorkPoint = 2,
    CmdSendPoiData = 3,
    CmdTurnOnFullPoiReg = 4,
    CmdStartSendFullPoiReg = 5,
    CmdRotationSpeed = 6,
    CmdGetBlindSectors = 7,
    CmdConfig4MainWork = 8,
    CmdRes_06 = 9,
    CmdRes_07 = 10,
    CmdRes_08 = 11,
    CmdRes_09 = 12,
    CmdRes_10 = 13,
    CmdRes_11 = 14,
    CmdRes_12 = 15,
};

// ID: RMO_BROADCAST
struct RMOBroadcastMessage {
    unsigned char id;   // Номер подсистемы
};

// ID: VOI_RMO_TRACK_DELETE_MESSAGE
struct ResetTrackMessage {
    timeval64 sTimeStamp;   // Время создания сообщение
    uint aimID;           // Номер цели в системе номеров ИРСЛ-С
};



// ID: VOI_RMO_MARK_MESSAGE
struct VOIMarkMessage {             // Сообщение с обнаруженной КТА
    timeval64 sTimeMeasurement;     // Время измерения координат
    float D;                        // Дальность КТА
    float Azm;                      // Азимут КТА
    float Ugm;                      // Угол места КТА
    float Vr;                       // Радиальная скорость КТА
    float Amp;                      // Амплитуда КТА
    int num_target;                 // Номер цели
    bool flag_target;               // Признак цели // true - цель, false - только отождествлённая кта
    bool flag_answer;               // Признак ответчика // true - по ответчику, false - по отражённому сигналу
};

// ID: POI_KTA_MESSAGE                  = 72,
// Сообщение о КТА
struct POIKtaMessage {              // Сообщение с обнаруженной КТА
    timeval64 sTimeMeasurement;     // Время измерения координат
    float Az_ant;                   // Азимут антенны
    float Um_ant;                   // Угол места антенны
    float D;                        // Дальность КТА
    float Az;                       // Азимут КТА
    float Um;                       // Угол места КТА
    float Vr;                       // Радиальная скорость КТА
    float Amp;                      // Амплитуда КТА
    uint8_t num_work_point;         // Номер рабочей точки
    uint8_t info;
};

// ID: RLSO_AIM_MESSAGE
//     Сообщение о цели (ИРЛС-О -> КП)
struct RLSOaimMessage {
    timeval64 sTimeMeasurement;     // Время измерения координат
    int trackID;           // Номер трассы в системе номеров ИРЛС-О

    float D;                // Дальность
    float Az;               // Азимут
    float h;                // высота h
    float vp;               // путевая скорость
    float tack;             // курс

    uint8_t typeSignal;     // 0 - Отраженный, 1 - Ответный, 3 - Отв+Отр
    uint8_t typeSignalNow;  // 0 - Отраженный, 1 - Ответный, 10 - Экстраполированный
    uint letter;            // литера
};


// ID: ALL_SYSTEM_HANDSHAKE
// Сообщение о рукопожатии с ММИРом
struct HandshakeMessage {
    SYSTEMS_ID sysId;
};


// ID: SIM_RREWIND_FILE
// Сообщение для перемотки файла воспроизведения
struct SimMessageRewind {
    timeval64 timeStart;      // Время начала воспроизведения
};

// ID: SIM_PLAY_ON                   = 127
// Сообщение для запуска/остановки воспроизведения
struct simPlayOn {
    uchar playOn;           // Воспроизведение (0 - остановить,
                            //                  1 - начать воспроизведение с реальной скоростью,
                            //                  2 - ускорение в 2 раза,
                            //                  3 - замедление в 2 раза
                            //                  255 - перезапуск
};

// ID: SIM_CURRENT_PLAY_TIME         = 128
// Сообщение о времени воспроизведения из файла
struct simTimeInFile {
    timeval64 timeStart;
};

// ID: RARM_SYSTEM_CONTROL_MESSAGE
// Сообщение с состоянием подсистем
struct RARMSysControlMessage {
    int sysControl;
};


enum TargetWorkMode {
    ReflectedSignal = 0,
    ResponseSignal = 1,
    DSP = 2,
    ReflectedAndResponse = 3,
    ReflectedAndDSP = 4,
    ResponseAndDSP = 5,
    ReflectedAndResponseAndDSP = 6,
    Extrapolation = 10
};

struct SettingAnswerSector
{
    uint8_t set_mode;
    uint8_t freq_rays;
    uint8_t type_letter;
    uint letter;
};

// ID: RMO_VOI_TARGET_POSITION_MESSAGE
// Сообщение с параметрами ЦУ
struct RMOTargetPositionMessage      {
    timeval64 sTimeMeasurement;
    uint8_t id;
    uint8_t isUpdate;         //0 - новый сектор, 1 - обновление
    float azimuth[2];
    float ugm[2];
    float dist[2];
    float vr[2];
    uint8_t work_mode;        // 0,1,3,4,5,6
    uint8_t set_mode[2];      // набор режимов // 255 - нет набора //индексы режимов 0 - ОТР, 1 - ДСП
    uint8_t freq_rays[2];     // частота осмотра одного луча
    uint8_t DSP;              // 0 - 2 мсек, 1 - 20 мсек
    uint8_t out_dsp;          // 0 - не выводить дсп, 1 - выводить дсп
    uint8_t count_letter;     // количество литер
    SettingAnswerSector answer[10];
};

// ID: RMO_VOI_TARGET_DELETE_MESSAGE
// Сообщение с удалением ЦУ
struct RMOTargetDeleteMessage {
    timeval64 sTimeStamp;   // Время создания сообщение
    quint8 id;           // Номер сектора
};

// ID: RMO_VOI_TRACK_DELETE_MESSAGE
// Сообщение с удалением трассы
struct DeleteTrackMessage {
    timeval64 sTimeStamp;   // Время создания сообщение
    uint aimID;           // Номер цели в системе номеров ИРСЛ-С
};

// ID: VOI_RMO_RAY_SET_MESSAGE
// Сообщение с набором лучей на следующий такт
struct VOIRaySetMessage      {
    timeval64 sTimeMeasurement;
    uchar count;
    float az[100];
    float ugm[100];
    int id[100];
    quint8 mode[100];
};

// ID: RMO_VOI_TRACK_SETTING_MESSAGE
// Сообщение о проритетности трассы
struct RMOTrackSetting     {
    timeval64 sTimeStamp;       // Время создания сообщение
    int aimID;                  // Номер цели в системе номеров ИРСЛ-С
    uint8_t priority;           // 0 - нет приоритета, 1 - приоритет
    uint8_t work_mode;          // 0,1,3,4,5
    uint8_t DSP;                // 0 - 2 мсек (хвост), 1 - 20 мсек
    uint8_t out_dsp;            // 0 - не выводить дсп, 1 - выводить дсп
    uint8_t type_answer;        // тип ответчика // 0 - ЛЧМ, 1 - РИ
    uint letter;                // литера
    uint8_t CT;                 // 0 - нет, 1 - режим СЦ
    uint8_t spec_sectors_on;    // возможно ли создавать спец-сектора у удаляемых трасс // 0 - нет, 1 - можно,
    uint8_t priority_spec_sectors; // получает ли максимальный приоритет спец-сектор на поиск потерянной трассы // 0 - приоритет как у потерянной трассы, 1 - приоритет,
    uint8_t time_searching_in_spec_sector; // сек // время сброса спец-сектора
};

//ID: VOI_RMO_CREATE_SPECIAL_SECTOR_MESSAGE
// Сообщение о создании спец-сектора
struct VOICreateSpecialSectorMessage {
    timeval64 sTimeMeasurement;
    int id_trass;
    uint8_t work_mode; // TargetWorkMode // только ReflectedSignal = 0 и ResponseSignal = 1
    float azimuth[2];
    float ugm[2];
    float dist[2];
};

// ID: RLSO_RMO_DSP_DATA_MESSAGE
// Сообщение с данными ДСП
struct RLSODSPDataMessage {
    timeval64 sTimeMeasurement;
    int id;
    quint32 counter;
    quint32 N;
    quint32 M;
    quint32 part;
    int azm_ray;
    int ugm_ray;
    float azm;
    float ugm;
    short data[2 * 240 * 28];
};



#endif /* DATA_MESSAGES_H_ */
