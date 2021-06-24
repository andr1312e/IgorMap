#ifndef ANALOGMARKMODEL_H
#define ANALOGMARKMODEL_H

#include <DataHandler/datamessage.h>
#include <vector>
#include <list>
#include <boost/thread/mutex.hpp>


struct AnalogSignal {
    float az;
    float dist;
};

typedef std::list<AnalogSignal*> AnalogSignalList;
typedef std::vector<AnalogSignalList*> AnalogSignalMap;


class AnalogMarkModel
{
public:
    static constexpr float ANALOG_MARK_WIDTH = 1.4f;    // width (in degrees) of analog mark
    static constexpr int ANALOG_SECTOR_SIZE = 5;        // size of sector to store analog marks
    static constexpr int NUM_ANALOG_SECTORS = 360 / ANALOG_SECTOR_SIZE; // number of sectors in 360 deg circle

    AnalogMarkModel();
    ~AnalogMarkModel();
    //void addAnalogMark(RLSOAnalogSignalMessage *msg);
    AnalogSignalMap* getAnalogSignalMap() { return analogSignalMap; }
    AnalogSignalList* getAnalogSignalList(float az);
    void lockAnalogModel() { mLock.lock(); }
    void unlockAnalogModel() { mLock.unlock(); }
    void emptyAnalogMarkList(float radarAzimuth);
    void eraseAnalogMarks(float oldRadarAzimuth, float newRadarAzimuth);
    void eraseAllAnalogMarks();
    //void findKTAInfoAt(float scenePosX, float scenePosY, float threshold, float &markX, float &markY);
    void cleanModel();

private:
    boost::mutex mLock;
    AnalogSignalMap *analogSignalMap;

    int getAnalogListIndex(float radarAz);

};

#endif // KTAMARKMODEL_H
