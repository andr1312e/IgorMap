#ifndef DATAFILELOGGER_H
#define DATAFILELOGGER_H

#include <QThread>
#include <QEventLoop>
#include <fstream>
#include "dataloggermodel.h"


class DataFileLogger : public QThread
{
    Q_OBJECT

public:
    const static QString LOGS_DIR;

    DataFileLogger();
    ~DataFileLogger();

    DataLoggerModel* getDataLoggerModel() { return dataLoggerModel; }
    void stop() {
        dataLoggerModel->lockDataLoggerModel();
        running = false;
        dataLoggerModel->unlockDataLoggerModel();
    }

private:

    bool running;
    bool isFirstEntry = true;
    DataLoggerModel* dataLoggerModel;
    ofstream logFile;

    void processData();
    void saveStartTimeStamp();
    void saveStopTimeStamp();

protected:
    void run();

};

#endif // DATAFILELOGGER_H
