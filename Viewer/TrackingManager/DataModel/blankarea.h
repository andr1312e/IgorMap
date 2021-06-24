#ifndef BLANKAREA_H
#define BLANKAREA_H

//#include <vector>
//#include <list>
//#include "cfgmanager.h"
/*#include <map>
#include <boost/thread/mutex.hpp>

struct BlankAreaObject
{
    float x1;
    float y1;
    float x2;
    float y2;
};

//typedef std::vector<BlankAreaPoint*> BlankAreaObject;
//typedef std::list<BlankAreaObject*> BlankAreaObjectList;
typedef std::map<uint,BlankAreaObject*> BlankAreaObjectMap;

class BlankArea {

public:
    BlankArea();
    ~BlankArea();
    BlankAreaObjectMap* getBlankAreaMap() { return blankAreaObjectMap; }
    void lockBlankAreaModel() { mLock.lock(); }
    void unlockBlankAreaModel() { mLock.unlock(); }
    void createObject();
    void endObject();
    void deleteObject(float nx, float ny);
    void deleteObject(uint id);
    void addPoint(float nx, float ny);
    void addObject(BlankAreaObject* obj);
    void changeObject(uint id, BlankAreaObject* obj);
    uint getObjectId() { return objectId; }
    BlankAreaObject* getObjectInfo(uint id) { return blankAreaObjectMap->find(id)->second; }

private:
    boost::mutex mLock;
    BlankAreaObjectMap *blankAreaObjectMap;
    bool createObjectFlag;
    bool firstEnteryFlag;
    float tempAz;
    float tempDis;
    uint objectId;

private:
    void sendToCreate();
    void sendToRemove(uint id);

};*/

#endif // BLANKAREA_H
