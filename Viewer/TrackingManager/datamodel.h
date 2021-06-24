#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <TcpHandler/datamessage.h>
#include <TrackingManager/DataModel/ktamarkmodel.h>
#include <TrackingManager/DataModel/trackmarkmodel.h>
#include <deque>
#include <list>
#include "unordered_map"
#include "msgnotifier.h"

using namespace std;
using namespace __gnu_cxx;


class DataModel
{    
public:
    DataModel();
    ~DataModel();

    TrackMarkModel* getTrackMarkModel() { return trackMarkModel; }
    //NewTrackMarkModel* getNewTrackMarkModel() { return newTrackMarkModel; }
    //TrackHistoryModel* getTrackHistoryModel() { return trackHistoryModel; }
    KTAMarkModel* getKTAMarkModel() { return ktaMarkModel; }
    void redrawInfoGrid();
    //void redrawTrackHistoryGrid();
    void addTrackMessage(RLSOaimMessage *msg);
    void addTrackHistoryMessage(RLSOaimMessage *msg);
    void displayTrack(int id);
    void cleanTrack();
    void deleteTrack(int id);
    void addTrackMark(RLSOaimMessage *msg);
    void addKTAMark(RLSOPlotMessage *msg, uint type);
    //void addAnalogMark(RLSOAnalogSignalMessage *msg);


    void cleanModel();
    void releaseModel();
    //bool isTrackMsgMapEmpty() { return trackMsgMap.empty(); }

public slots:
    void addTrack(RLSOaimMessage *msg);
    void resetTrack(int id);

private:
    TrackMarkModel *trackMarkModel;
    //NewTrackMarkModel *newTrackMarkModel;
    //TrackHistoryModel *trackHistoryModel;
    KTAMarkModel *ktaMarkModel;
    //BlankArea *blankArea;    

};

#endif // DATAMODEL_H
