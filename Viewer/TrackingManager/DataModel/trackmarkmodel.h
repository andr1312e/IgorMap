#ifndef TRACKMARKMODEL_H
#define TRACKMARKMODEL_H

#include <TcpHandler/datamessage.h>
#include "unordered_map"
#include <list>
#include <vector>
#include <deque>
#include <GL/gl.h>

using namespace std;
using namespace __gnu_cxx;

enum DRAW_INFO_MODE {
    DRAW_MODE_ID_SIGN,
    DRAW_MODE_FULL_INFO,
    DRAW_MODE_CUSTOM_INFO,
    DRAW_MODE_NONE
};

enum DrawInfoFixedMode {
    None,
    Fixed,
    Deleted
};

enum DRAW_CUSTOM_INFO_ITEM {
//    DRAW_NONE,
    DRAW_ID,
    DRAW_AZ_DIST,
    DRAW_HEIGHT,
    DRAW_SPEED,
    DRAW_TRACK_HEADING,
    DRAW_FUEL_RATE,

    // size of enum
    LENGTH_OF_INFO_ITEM
};

enum INFO_ITEM_ORIENTATION {
    INFO_ITEM_AVOID_RIGHT_TOP,
    INFO_ITEM_AVOID_LEFT_TOP,
    INFO_ITEM_AVOID_RIGHT_BOTTOM,
    INFO_ITEM_AVOID_LEFT_BOTTOM
};

struct CustomInfoItemOrder {
    DRAW_CUSTOM_INFO_ITEM drawOrder[LENGTH_OF_INFO_ITEM];
    bool drawItem[LENGTH_OF_INFO_ITEM];
};

struct DisplayTrackInfoOrder {
    bool useDefaults = true;
    bool showInfoText = true;
    bool showTrack = false;
    bool showTrace = false;
    bool highlight = false;
    bool followToTrack = false;
    DrawInfoFixedMode fixedTrace = None;
    DRAW_INFO_MODE drawMode;
    DRAW_INFO_MODE backupDrawMode = DRAW_MODE_NONE;
    CustomInfoItemOrder drawOrder;
    INFO_ITEM_ORIENTATION avoidOrientation;
};

struct TrackMark {
    float xPos;
    float yPos;
    float heading;
    float xProjPos;
    float yProjPos;
    float zProjPos;
    float speed;
    float absXPos;
    float absYPos;
    float az;
    float dist;
    float h;
    timeval time;
};

typedef deque<TrackMark*> TrackList;  //list -> deque

class TrackMarkList {

public:
    TrackMarkList(int trackID);
    ~TrackMarkList();

    void addTrackMark(RLSOaimMessage *msg);
    TrackList* getTrackList() { return trackList; }
    DisplayTrackInfoOrder *getDisplayInfoOrder() { return &displayInfoOrder; }
    //TLTrackIDItem* getTrackIDTableWidgetItem() { return trackIDTableWidgetItem; }
    //TLTrackIDItem* getSelectedTrackIDTableWidgetItem() { return selectedTrackIDTableWidgetItem; }
    /*void reinitSelectedTrackIDTableWidgetItem() { delete selectedTrackIDTableWidgetItem;
                                                  selectedTrackIDTableWidgetItem = new TLTrackIDItem(trackID);
                                                }*/
    void resetDisplayInfoOrder();

    GLuint getTraceDisplayListID() { return traceDisplayListID; }
    void setTraceDisplayListID(GLuint id) { traceDisplayListID = id; }
    GLuint getProjTraceDisplayListID() { return projTraceDisplayListID; }
    void setProjTraceDisplayListID(GLuint id) { projTraceDisplayListID = id; }

    //AIM_ID_SIGN getTrackSign() { return trackSign; }
    int getTrackID() { return trackID; }
    float getSpeed() { return trackSpeed; }
    float getFuelRate() { return fuelRate; }
    float getXPos() { return scenePosX; } //scenePosX sceneAbsX
    float getYPos() { return scenePosY; } //scenePosY sceneAbsY
    float getAbsXPos() { return sceneAbsX; } //scenePosX sceneAbsX
    float getAbsYPos() { return sceneAbsY; }
    float getXProjPos() { return sceneProjPosX; }
    float getYProjPos() { return sceneProjPosY; }
    float getZProjPos() { return sceneProjPosZ; }
    float getHeading() { return trackHeading; }
    float getHeight() { return trackHeight; }
    float getAzimuth() { return az; }
    float getDistance() { return dist; }
    bool visible() { return isVisible; }
    void setVisible(bool visible) { isVisible = visible; }
    void setXPos(float value) { scenePosX = value; }
    void setYPos(float value) { scenePosY = value; }
    void setNewDataYes() { isNewData = true; }
    void setAz (float value) { az = value; }
    void setSpeed (float value) { trackSpeed = value; }
    void setAbsXPos(float value) { sceneAbsX = value; }
    void setAbsYPos(float value) { sceneAbsY = value; }
    void setDistance(float value) { dist = value; }
    void setHeading(float value) { trackHeading = value; }
    void setHeight(float value) { trackHeight = value; }

    int getInfoTxtGridCol() { return infoTxtGridCol; }
    int getInfoTxtGridRow() { return infoTxtGridRow; }
    int getMarkGridCol() { return trackMarkGridCol; }
    int getMarkGridRow() { return trackMarkGridRow; }
    int getInfoTxt3DGridCol() { return infoTxt3DGridCol; }
    int getInfoTxt3DGridRow() { return infoTxt3DGridRow; }
    int getMark3DGridCol() { return trackMark3DGridCol; }
    int getMark3DGridRow() { return trackMark3DGridRow; }
    void setInfoTxtGridCol(int col) { infoTxtGridCol = col; }
    void setInfoTxtGridRow(int row) { infoTxtGridRow = row; }
    void set3DInfoTxtGridCol(int col) { infoTxt3DGridCol = col; }
    void set3DInfoTxtGridRow(int row) { infoTxt3DGridRow = row; }
    void setMarkGridCol(int col) { trackMarkGridCol = col; }
    void setMarkGridRow(int row) { trackMarkGridRow = row; }
    void setMark3DGridCol(int col) { trackMark3DGridCol = col; }
    void setMark3DGridRow(int row) { trackMark3DGridRow = row; }
    void setInfoTxt3DGridCol(int col) { infoTxt3DGridCol = col; }
    void setInfoTxt3DGridRow(int row) { infoTxt3DGridRow = row; }
    void getInfoTxtPos(float &x, float &y);
    void get3DInfoTxtPos(float &az, float &z);
    void setTrackInfoSelection(bool selected) { isTrackInfoSelected = selected; }
    bool getTrackInfoSelection() { return isTrackInfoSelected; }

    void findInfoTxtPosition();
    void moveInfoTxtPosition(bool &searching, const int &rowCount, const int &colCount);
    void moveInfoTxtPosition();

    void find3DInfoTxtPosition();
    void move3DInfoTxtPosition(bool &searching, const int &rowCount, const int &colCount);

    void setDeleted() { isDeleted = true; }
    bool isTrackDeleted() { return isDeleted; }
    int decCounterAlive() { if (--counterAlive < 0)  counterAlive = 0; return counterAlive; }

private:
    //TLTrackIDItem *trackIDTableWidgetItem;
    //TLTrackIDItem *selectedTrackIDTableWidgetItem;
    TrackList *trackList;
    //AIM_ID_SIGN trackSign;
    int trackID;
    GLuint traceDisplayListID;
    GLuint projTraceDisplayListID;
    float trackHeight;
    float trackHeading;
    float trackSpeed;
    float fuelRate;
    float az;
    float dist;
    float scenePosX;
    float scenePosY;
    float sceneAbsX;
    float sceneAbsY;
    float sceneProjPosX;
    float sceneProjPosY;
    float sceneProjPosZ;
    DisplayTrackInfoOrder displayInfoOrder;
    bool isTrackInfoSelected;
    bool isVisible;
    bool isDeleted = false;
    int counterAlive = 50;

    // NOTE: due to gl transformations to match 0 deg azimuth with north,
    //       column of grid is from bottom to the top and row is from left to right
    int infoTxtGridCol = -1;   // pos of info text
    int infoTxtGridRow = -1;   // pos of info text
    int trackMarkGridCol = -1; // pos of mark
    int trackMarkGridRow = -1; // pos of mark
    int trackMark3DGridCol = -1; // pos of mark
    int trackMark3DGridRow = -1; // pos of mark
    int infoTxt3DGridCol = -1;
    int infoTxt3DGridRow = -1;

    bool isNewData = true;
};

/*******************
*  TrackMarkModel  *
*******************/
typedef unordered_map<int, TrackMarkList*> TrackMarkMap;
typedef unordered_map<int, TrackMark*> IndicatorMarkMap;
typedef pair<int, TrackMarkList*> TrackMarkMapPair;
typedef pair<int, TrackMark*> IndicatorMarkMapPair;
typedef list<int> InfoGridTracksList;

struct InfoGridItem {
    InfoGridTracksList tracksList; // list of tracks, which are in this cell
    int trackID = -1;              // >= 0, if info txt is displayed in this cell
};

struct RowColStruct {
    RowColStruct():row(0),col(0){}
    RowColStruct(int _row, int _col):row(_row),col(_col) {}
    bool operator< (const RowColStruct &item) const
    {
        if (row < item.row)
            return true;
        else if (row == item.row) {
            if (col < item.col)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    int row;
    int col;
};

typedef vector< vector<InfoGridItem> > InfoGrid;
typedef map<int, int> NewInfoGrid;
typedef map<RowColStruct, int> AdvancedInfoGrid;
typedef multimap<RowColStruct, int> AdvancedTrackGrid;

class TrackMarkModel
{
public:
    TrackMarkModel();
    ~TrackMarkModel();
    void resetInfoTxtGrid();
    void reset3DInfoTxtGrid();
    TrackMarkMap* getTrackMarkMap() { return trackMarkMap; }
    IndicatorMarkMap* getIndicatorMarkMap() { return indicatorMarkMap; }
    TrackMarkList* getTrackById(int id);
    TrackMarkList* findTrackAt(float x, float y, float threshold);

    bool isEmpty() { return trackMarkMap->empty(); }
    void addTrackMark(RLSOaimMessage *msg);
    void addIndicatorMark(RLSOaimMessage *msg);
    void deleteTrack(int id);
    void deleteIndicatorMark(int id);
    void cleanModel();
    void cleanTrack();
    void releaseModel();
    void displayTrackHistory(int id);
    void swapTrackAndHistory(int id, TrackMark *track);
    float getColSize() { return colSize; }
    float getRowSize() { return rowSize; }
    int getColCount() { return colCount; }
    int getRowCount() { return rowCount; }

    // info grid methods
    int getInfoTxtIDAt(int row, int col);//{ return infoTxtGrid[row][col].trackID; }
    void setInfoTxtAt(int id, int row, int col); //{ infoTxtGrid[row][col].trackID = id; }
    void setTrackAt(int id, int row, int col);
    bool isInfoGridTrackListEmptyAt(int row, int col); //{ return infoTxtGrid[row][col].tracksList.empty(); }
    void deleteTrackFromInfoGrid(int row, int col);
    void deleteTrackFromTrackGrid(int id, int row, int col);    
    //void addTrackToInfoGrid(int id, int row, int col) { infoTxtGrid[row][col].tracksList.push_front(id); }
    //void deleteTrackFromInfoGrid(int id, int row, int col) { infoTxtGrid[row][col].tracksList.remove(id); }
    void moveInfoTxt(int oldRow, int oldCol, int newRow, int newCol); //{ infoTxtGrid[newRow][newCol].trackID = infoTxtGrid[oldRow][oldCol].trackID;
                                                                      // infoTxtGrid[oldRow][oldCol].trackID = -1; }

    // 3D info grid methods
    int get3DInfoTxtIDAt(int row, int col) { return infoTxt3DGrid[row][col].trackID; }
    void set3DInfoTxtAt(int id, int row, int col) { infoTxt3DGrid[row][col].trackID = id; }
    int is3DInfoGridTrackListEmptyAt(int row, int col) { return infoTxt3DGrid[row][col].tracksList.empty(); }
    void addTrackTo3DInfoGrid(int id, int row, int col) { infoTxt3DGrid[row][col].tracksList.push_front(id); }
    void deleteTrackFrom3DInfoGrid(int id, int row, int col) { infoTxt3DGrid[row][col].tracksList.remove(id); }
    void move3DInfoTxt(int oldRow, int oldCol, int newRow, int newCol) { infoTxt3DGrid[newRow][newCol].trackID = infoTxt3DGrid[oldRow][oldCol].trackID;
                                                                         infoTxt3DGrid[oldRow][oldCol].trackID = -1; }

private:
    TrackMarkMap *trackMarkMap;
    IndicatorMarkMap *indicatorMarkMap;
    AdvancedInfoGrid infoTxtGrid;
    AdvancedTrackGrid trackGrid;
    InfoGrid infoTxt3DGrid;    


    //bool newPosition = false;
    float colSize, rowSize;
    int colCount, rowCount;

private:
    void initTrackInfoTxtGrid();
    void initTrackInfoTxt3DGrid();    

};

#endif // TRACKMARKMODEL_H
