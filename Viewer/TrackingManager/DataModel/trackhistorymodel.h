#ifndef TRACKHISTORYMODEL_H
#define TRACKHISTORYMODEL_H

#include "trackmarkmodel.h"
#include "unordered_map"


struct TrackHistoryMark {
    float az;
    float dist;
    float speed;
    float height;
    float xpos;
    float ypos;
    float heading;
    float trackSpeed;
    float trackHeight;
    timeval timestamp;
    bool showInfo = false;
    int infoGridRow = -1;
    int infoGridCol = -1;
    int markGridRow = -1;
    int markGridCol = -1;
};

struct TrackInfoGridItem {
    InfoGridTracksList tracksList;      // list of tracks, which are in this cell
    bool isFree = true; // >= 0, if info txt is displayed in this cell
};

typedef list<TrackHistoryMark*> TrackHistoryList;

class TrackHistory {

public:
    TrackHistory() { trackHistory = new TrackHistoryList; }
    ~TrackHistory();
    TrackHistoryList* getHistory() { return trackHistory; }
    bool visible() { return isVisible; }
    void setVisible(bool visible) { isVisible = visible; }
    void setTrackID(int id) { trackID = id; }
    int getTrackID() { return trackID; }

private:
    TrackHistoryList *trackHistory;
    bool isVisible = false;
    int trackID = -1;

};


typedef unordered_map<int, TrackHistory*> TrackHistoryMap;
typedef pair<int, TrackHistory*> TrackHistoryMapPair;
typedef vector< vector<TrackInfoGridItem> > TrackInfoGrid;

class TrackHistoryModel {

public:
    TrackHistoryModel();
    ~TrackHistoryModel();
    TrackHistoryMap* getTrackHistoryMap() { return trackHistoryMap; }
    TrackHistoryList* getTrackById(int id);
    TrackHistory* getHistoryById(int id);
    void addTrackMark(RLSOaimMessage *msg);
    void deleteTrack(int id);
    void initTrackInfoGrid();
    void resetTrackInfoGrid();
    void cleanModel();
    void lockTrackHistoryModel() { mLock.lock(); }
    void unlockTrackHistoryModel() { mLock.unlock(); }
    bool isEmpty() { return trackHistoryMap->empty(); }

private:
    boost::mutex mLock;
    TrackHistoryMap *trackHistoryMap;
    TrackInfoGrid trackInfoGrid;

    void moveTrackInfoPosition(TrackHistoryMark *mark, bool &searching, const int &rowCount, const int &colCount);
    void addTrackToGrid(int id, int row, int col) { trackInfoGrid[row][col].tracksList.push_front(id); }
    //bool isTrackListEmptyAt(int row, int col) { return trackInfoGrid[row][col].tracksList.empty(); }
    //bool isTrackInfoEmptyAt(int row, int col) { return trackInfoGrid[row][col].isFree; }
    bool isGridEmptyAt(int row, int col) { return trackInfoGrid[row][col].isFree; }
    void occupyGridAt(int row, int col) { trackInfoGrid[row][col].isFree = false; }
    void deleteTrackFromGrid();

};

#endif // TRACKHISTORYMODEL_H
