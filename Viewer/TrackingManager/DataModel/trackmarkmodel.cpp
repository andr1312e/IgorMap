#include "trackmarkmodel.h"
#include <assert.h>

TrackMarkList::TrackMarkList(int id) {
    traceDisplayListID = 0;
    projTraceDisplayListID = 0;
    //trackIDTableWidgetItem = new TLTrackIDItem(id);
    //selectedTrackIDTableWidgetItem = new TLTrackIDItem(id);
    trackList = new TrackList;
    trackID = id;
    isTrackInfoSelected = false;
    isVisible = true;
    // use default display info settings
    //memcpy(&displayInfoOrder, CfgManager::Instance()->getDefaultDisplayInfoOrder(), sizeof(DisplayTrackInfoOrder));
}

void TrackMarkList::resetDisplayInfoOrder() {
    //memcpy(&displayInfoOrder, CfgManager::Instance()->getDefaultDisplayInfoOrder(), sizeof(DisplayTrackInfoOrder));
}

TrackMarkList::~TrackMarkList() {
    // delete track from info text grid
    /*if (infoTxtGridRow >= 0 && infoTxtGridCol >= 0) {
        CfgManager::Instance()->getTrackingController()->getDataModel()->
                getTrackMarkModel()->setInfoTxtAt(-1, infoTxtGridRow, infoTxtGridCol);
    }*/
    /*CfgManager::Instance()->getTrackingController()->getDataModel()->
            getTrackMarkModel()->deleteTrackFromInfoGrid(trackID, trackMarkGridRow, trackMarkGridCol);*/

    // release list of pointers
    while(!trackList->empty()) {
        delete trackList->back(), trackList->pop_back();
    }
    trackList->clear();
    //delete trackIDTableWidgetItem; //segmentation fault
    //delete selectedTrackIDTableWidgetItem;
    delete trackList;
}

void TrackMarkList::getInfoTxtPos(float &x, float &y) {
    // due to gl transformations to match 0 azimuth with north, x - column, y - row
    x = (float) infoTxtGridCol * CfgManager::Instance()->getSizeSettings()->getInfoTxtColSize();// - (float) CfgManager::DISTANCE_GRID_MAX;
    y = (float) (infoTxtGridRow - 1) * CfgManager::Instance()->getSizeSettings()->getInfoTxtRowSize();// - (float) CfgManager::DISTANCE_GRID_MAX;
}

void TrackMarkList::moveInfoTxtPosition(bool &searching, const int &rowCount, const int &colCount) {
    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();
    // reset info text pos
    infoTxtGridRow = trackMarkGridRow;
    infoTxtGridCol = trackMarkGridCol;

    switch(displayInfoOrder.avoidOrientation) {

    case INFO_ITEM_AVOID_RIGHT_BOTTOM: {
        if ( trackHeading <= 135 ) {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        }

        break;
    }
    case INFO_ITEM_AVOID_RIGHT_TOP: {
        if ( trackHeading <= 45 ) {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        }

        break;
    }
    case INFO_ITEM_AVOID_LEFT_BOTTOM: {
        if ( trackHeading <= 225 ) {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        }

        break;
    }
    case INFO_ITEM_AVOID_LEFT_TOP: {
        if ( trackHeading <= 315 ) {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {


                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else {
            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                    // reset movement and move in another direction
                    infoTxtGridRow = trackMarkGridRow;
                    infoTxtGridCol = trackMarkGridCol;
                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                            // reset movement and move in another direction
                            infoTxtGridRow = trackMarkGridRow;
                            infoTxtGridCol = trackMarkGridCol;
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {

                                // not found a place in the nearest info grid cell, so look for a place
                                // 1 cell away
                                // reset movement and move in another direction
                                infoTxtGridRow = trackMarkGridRow;
                                infoTxtGridCol = trackMarkGridCol;
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_LEFT, rowCount, colCount);
                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxtGridRow = trackMarkGridRow;
                                        infoTxtGridCol = trackMarkGridCol;
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxtGridRow = trackMarkGridRow;
                                                infoTxtGridCol = trackMarkGridCol;
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                    !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                    Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_TOP, rowCount, colCount);
                                                    if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                        !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                        // reset movement and move in another direction
                                                        infoTxtGridRow = trackMarkGridRow;
                                                        infoTxtGridCol = trackMarkGridCol;
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_RIGHT, rowCount, colCount);
                                                        Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                        if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                            !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                            Utils::moveInGrid(infoTxtGridRow, infoTxtGridCol, MOVE_BOTTOM, rowCount, colCount);
                                                            if( model->getInfoTxtIDAt(infoTxtGridRow, infoTxtGridCol) != -1 ||
                                                                !model->isInfoGridTrackListEmptyAt(infoTxtGridRow, infoTxtGridCol) ) {
                                                                // if no place was found, set row and col to -2
                                                                // so info text will not be drawn
                                                                infoTxtGridRow = -2;
                                                                infoTxtGridCol = -2;
                                                                searching = false;
                                                            } else { searching = false; }
                                                        } else { searching = false; }
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }


                            } else { searching = false; }
                        } else { searching = false; }
                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        }

        break;
    }

    default:
        searching = false;
        // TODO: WTF?!
        assert(false);
        break;

    }
}

void TrackMarkList::moveInfoTxtPosition()
{
    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();

    int numbOfPassesOnFace = 4;
    int face = 0;
    int row = trackMarkGridRow + 2, col = trackMarkGridCol - 2;

    bool onGo = true;
    while (onGo) {

        if (++face == 5) {
            face = MOVE_RIGHT;
            numbOfPassesOnFace += 2;
            row += 1, col -= 1;
        }

        for (int _index = 0; _index != numbOfPassesOnFace; _index++) {
            if (_index != 0) {
                Utils::moveInGrid(row, col, (MOVE_DIRECTION)face, model->getRowCount(), model->getColCount());
            }
            if( model->isInfoGridTrackListEmptyAt(row,col) ) {
                onGo = false;
                break;
            }
        }
        if (onGo)
            Utils::moveInGrid(row, col, (MOVE_DIRECTION)face, model->getRowCount(), model->getColCount());
    }

    infoTxtGridRow = row, infoTxtGridCol = col;
}

void TrackMarkList::findInfoTxtPosition() {
    /*int colCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    float colSize = CfgManager::Instance()->getSizeSettings()->getInfoTxtColSize(),
          rowSize = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowSize();*/
    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();

    if (isNewData) {
        isNewData = false;

        float xpos = scenePosX, ypos = scenePosY;
        trackMarkGridRow = infoTxtGridRow = (int) ceil(ypos / model->getRowSize());
        trackMarkGridCol = infoTxtGridCol = (int) ceil(xpos / model->getColSize());

        model->setTrackAt(trackID, trackMarkGridRow, trackMarkGridCol);

        moveInfoTxtPosition();

        model->setInfoTxtAt(trackID, infoTxtGridRow, infoTxtGridCol);

    }
    else {
        float xpos = scenePosX, ypos = scenePosY;
        float newRow = (int) ceil(ypos / model->getRowSize()),
              newCol = (int) ceil(xpos / model->getColSize());

        if ( newRow != trackMarkGridRow || newCol != trackMarkGridCol ) {
            model->deleteTrackFromTrackGrid(trackID, trackMarkGridRow, trackMarkGridCol);
            trackMarkGridRow = newRow, trackMarkGridCol = newCol;

            model->setTrackAt(trackID, trackMarkGridRow, trackMarkGridCol);
        }

        //use different conditions, depending on mapScale
        float mapScale = CfgManager::Instance()->getUiController()->getMapScale();
        int moveFactor = 2;
        if (mapScale > 2.0f && mapScale <= 5.0f) {
            moveFactor = 3;
        } else if (mapScale > 5.0f && mapScale <= 10.0f) {
            moveFactor = 4;
        } else if ( mapScale > 10.0f) {
            moveFactor += 3 + mapScale / 10;
        }

        // move txt info block if track mark is to far from it or info text is hidden
        if ( abs(newRow - infoTxtGridRow) > moveFactor ||
             abs(newCol - infoTxtGridCol) > moveFactor ) {
            model->deleteTrackFromInfoGrid(infoTxtGridRow, infoTxtGridCol);

            moveInfoTxtPosition();

            model->setInfoTxtAt(trackID, infoTxtGridRow, infoTxtGridCol);
        }
    }
}

void TrackMarkList::addTrackMark(RLSOaimMessage *msg) {
    TrackMark *mark = new TrackMark;

    BRLSPosition airplanPos = CfgManager::Instance()->getTrackingController()->getDataModel()->getBRLSTrackModel()->getBRLSPosition();
    az = mark->az = msg->Az;
    //az = msg->Az;
    dist = mark->dist = sqrt(pow(msg->D / CfgManager::GLOBAL_TO_LOCAL_RATIO, 2) - pow(abs(msg->sAimCoords.h - airplanPos.h)  / CfgManager::GLOBAL_TO_LOCAL_RATIO, 2));
    //dist = msg->D / CfgManager::GLOBAL_TO_LOCAL_RATIO;

    scenePosX = mark->xPos = dist * cosf(az * PI / 180);
    scenePosY = mark->yPos = dist * sinf(az * PI / 180);
    trackHeading = mark->heading = msg->sAimCoords.tack;
    sceneProjPosX = mark->xProjPos = cos(az * M_PI / 180) * (float) CfgManager::DISTANCE_GRID_MAX;
    sceneProjPosY = mark->yProjPos = sin(az * M_PI / 180) * (float) CfgManager::DISTANCE_GRID_MAX;
    sceneProjPosZ = mark->zProjPos = msg->sAimCoords.h / 100;
    mark->speed = trackSpeed = msg->sAimCoords.vp;
    //update code by SE

    //mark->absXPos = mark->xPos + airplanPos.y;
    //mark->absYPos = mark->yPos + airplanPos.x;
    sceneAbsY = mark->absYPos = airplanPos.y + dist * cosf((az + airplanPos.course) * PI / 180);
    sceneAbsX = mark->absXPos = airplanPos.x + dist * sinf((az + airplanPos.course) * PI / 180);
    scenePosX = sceneAbsX - CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel()->getCurrentPos().x;
    scenePosY = sceneAbsY - CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel()->getCurrentPos().y;

    mark->time = msg->sTimeMeasurement;

    counterAlive = 50;
    if (isDeleted)
        isDeleted = false;

    //mark->timestamp = msg->sTimeMeasurement;
    trackList->push_front(mark);

    // TODO: REMOVE THIS
    fuelRate = 0;
    // TODO: REMOVE THIS

    //scenePosX = mark->xPos;
    //scenePosY = mark->yPos;
    //trackHeading = mark->heading;
    trackHeight = mark->h = msg->sAimCoords.h;

    // set info bubble avoid orientation
    /*if(trackHeading >= 0 && trackHeading < 90) {
        displayInfoOrder.avoidOrientation = INFO_ITEM_AVOID_RIGHT_TOP;
    }
    if(trackHeading >= 90 && trackHeading < 180) {
        displayInfoOrder.avoidOrientation = INFO_ITEM_AVOID_RIGHT_BOTTOM;
    }
    if(trackHeading >= 180 && trackHeading < 270) {
        displayInfoOrder.avoidOrientation = INFO_ITEM_AVOID_LEFT_BOTTOM;
    }
    if(trackHeading >= 270 && trackHeading < 360) {
        displayInfoOrder.avoidOrientation = INFO_ITEM_AVOID_LEFT_TOP;
    }*/

    /*switch(msg->idSign) {
    case 0:
        trackSign = AIM_ID_SIGN_NOT_RESPONDING;
        break;
    case 1:
        trackSign = AIM_ID_SIGN_RESPONDING_OGP;
        break;
    case 2:
        trackSign = AIM_ID_SIGN_RESPONDING_MK_XA;
        break;
    default:
        assert(false);
        break;
    }*/

    findInfoTxtPosition();
    if (CfgManager::Instance()->getUiController()->getDisplayMode() == DISPLAY_LOCATOR_3D) {
        find3DInfoTxtPosition();
    }
}

TrackMarkModel::TrackMarkModel()
{
    trackMarkMap = new TrackMarkMap;
    indicatorMarkMap = new IndicatorMarkMap;
    historyTrackMarkMap = new HistoryTrackMarkMap;
    initTrackInfoTxtGrid();
}

TrackMarkModel::~TrackMarkModel()
{
    releaseModel();
    delete trackMarkMap;
    delete indicatorMarkMap;
    delete historyTrackMarkMap;
}

void TrackMarkModel::resetInfoTxtGrid() {
    /*float*/ colSize = CfgManager::Instance()->getSizeSettings()->getInfoTxtColSize(),
          rowSize = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowSize();
    /*int*/ colCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    // release memory
    /*for (InfoGrid::iterator it = infoTxtGrid.begin(); it != infoTxtGrid.end(); it++) {
        vector<InfoGridItem> *row = &*it;
        row->clear();
    }*/
    infoTxtGrid.clear();
    trackGrid.clear();
    // reinit grid
    initTrackInfoTxtGrid();
    for (TrackMarkMap::iterator it = trackMarkMap->begin(); it != trackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        //float xpos = list->getXPos(),// + (float) CfgManager::DISTANCE_GRID_MAX,
        //      ypos = list->getYPos();// + (float) CfgManager::DISTANCE_GRID_MAX;
        //float xpos, ypos;
        //if (newPosition) {
        //    newPosition = false;
        if (!list->isTrackDeleted()) {
            list->setXPos(list->getAbsXPos() - currentPosition.x);
            list->setYPos(list->getAbsYPos() - currentPosition.y);
        //}
        /*xpos = list->getXPos(), ypos = list->getYPos();
        int newRow = (int) ceil(ypos / rowSize),
            newCol = (int) ceil(xpos / colSize);*/

        //list->setMarkGridRow(newRow);
        //list->setMarkGridCol(newCol);
        //list->setInfoTxtGridRow(-1);
        //list->setInfoTxtGridCol(-1);
        list->setNewDataYes();
        list->findInfoTxtPosition();
        }
        //setInfoTxtAt(list->getTrackID(), list->getMarkGridRow(), list->getMarkGridCol());
        //addTrackToInfoGrid(list->getTrackID(), list->getMarkGridRow(), list->getMarkGridCol());
    }

    for (auto item = historyTrackMarkMap->begin(); item != historyTrackMarkMap->end(); item++) {
        TrackMarkList *list = item->second;

        list->setXPos(list->getAbsXPos() - currentPosition.x);
        list->setYPos(list->getAbsYPos() - currentPosition.y);

        list->setNewDataYes();
        list->findInfoTxtPosition();

    }
    /*for (TrackMarkMap::iterator it = trackMarkMap->begin(); it != trackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        // search for a proper place
        bool searching = true;
        do {
            list->moveInfoTxtPosition(searching, rowCount, colCount);
        } while(searching);

        if (list->getInfoTxtGridRow() >= 0 && list->getInfoTxtGridCol() >= 0) {
            setInfoTxtAt(list->getTrackID(), list->getInfoTxtGridRow(), list->getInfoTxtGridCol());
        }
        else {
            qDebug() << "TrackMarkList: Wrong Col or Row";
        }
    }*/
}

void TrackMarkModel::initTrackInfoTxtGrid() {
    if (CfgManager::Instance()->isInitialized()) {
        currentPosition.x = CfgManager::Instance()->getTrackingController()->getDataModel()->getBRLSTrackModel()->getBRLSPosition().x - static_cast<float>(CfgManager::DISTANCE_GRID_MAX * 3 / 2);
        currentPosition.y = CfgManager::Instance()->getTrackingController()->getDataModel()->getBRLSTrackModel()->getBRLSPosition().y - static_cast<float>(CfgManager::DISTANCE_GRID_MAX * 3 / 2);
    }
}

void TrackMarkModel::cleanModel() {
    /*TrackMarkMap::iterator it;
    for (it = trackMarkMap->begin(); it != trackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        delete list;
    }
    trackMarkMap->clear();*/
    IndicatorMarkMap::iterator it1;
    for (it1 = indicatorMarkMap->begin(); it1 != indicatorMarkMap->end(); it1++) {
        TrackMark *mark = it1->second;
        delete mark;
    }
    indicatorMarkMap->clear();
    infoTxtGrid.clear();
    trackGrid.clear();
    resetInfoTxtGrid();
}

void TrackMarkModel::cleanTrack()
{
    infoTxtGrid.clear();
    trackGrid.clear();
    for (auto it = historyTrackMarkMap->begin(); it != historyTrackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        delete list;
    }
    historyTrackMarkMap->clear();
}

void TrackMarkModel::displayTrackHistory(int id)
{
    TrackList *list;
    if (getTrackById(id) != nullptr)
        list = getTrackById(id)->getTrackList();
    else
        return;

    if (list != nullptr) {
        timeval time;
        for (auto item = list->rbegin(); item != list->rend(); item++) {
            timeval _time = (*item)->time;
            if (item == list->rbegin() ||
               _time.tv_sec > (time.tv_sec + 60) ) {
                time = (*item)->time;
                swapTrackAndHistory(id, *item);
            }
        }
        swapTrackAndHistory(id, *(list->begin()));
    }
}

void TrackMarkModel::swapTrackAndHistory(int id, TrackMark *track)
{
    TrackMarkList *list = new TrackMarkList(id);
    list->setAz(track->az);
    list->setDistance(track->dist);
    list->setXPos(track->absXPos - currentPosition.x);
    list->setYPos(track->absYPos - currentPosition.y);
    list->setAbsXPos(track->absXPos);
    list->setAbsYPos(track->absYPos);
    list->setHeading(track->heading);
    list->setHeight(track->h);
    list->setSpeed(track->speed);
    historyTrackMarkMap->insert({id, list});

    list->findInfoTxtPosition();
}

void TrackMarkModel::checkGoingAbroad(AdvancedVertex vertex)
{
    if (!( ((currentPosition.x + CfgManager::DISTANCE_GRID_MAX) < vertex.x && vertex.x <  (currentPosition.x + 2 * CfgManager::DISTANCE_GRID_MAX)) &&
           ((currentPosition.y + CfgManager::DISTANCE_GRID_MAX) < vertex.y && vertex.y <  (currentPosition.y + 2 * CfgManager::DISTANCE_GRID_MAX)) )  ) {
        //newPosition = true;
        resetInfoTxtGrid();
    }
}

int TrackMarkModel::getInfoTxtIDAt(int row, int col)
{
    //int rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    //int index = row * rowCount + col;
    auto item = infoTxtGrid.find(RowColStruct(row,col));
    if (item != infoTxtGrid.end()) {
        return item->second;
    }
    else {
        return -1;
    }
}

void TrackMarkModel::setInfoTxtAt(int id, int row, int col)
{
    //int rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    //int index = row * rowCount + col;
    auto item = infoTxtGrid.find(RowColStruct(row,col));
    if (item == infoTxtGrid.end()) /*{
        if (item->second != id ) {
            infoTxtGrid.erase(item);
            infoTxtGrid.insert({index, id});
        }
    }
    else*/
        infoTxtGrid.insert({RowColStruct(row,col), id});
    else {
        qDebug() << "Shit happens №2";
    }
}

void TrackMarkModel::setTrackAt(int id, int row, int col)
{
    std::vector<int> vectorRetiredEntriesID;
    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();
    const int passage = 2;
    for (int indexRow = -1; indexRow != passage; indexRow++) {
        for (int indexCol = -1; indexCol != passage; indexCol++) {
            if (!model->isInfoGridTrackListEmptyAt(row,col)) {
                auto itemInfo = infoTxtGrid.find(RowColStruct(row,col));
                if (itemInfo != infoTxtGrid.end()) {
                    vectorRetiredEntriesID.push_back(itemInfo->second);
                    infoTxtGrid.erase(itemInfo);
                }
                /*else {
                    qDebug() << "Shit happens №1";
                }*/
            }
            trackGrid.insert({RowColStruct(row + indexRow,col + indexCol), id});
        }
    }

    for (auto itemVector = vectorRetiredEntriesID.begin(); itemVector != vectorRetiredEntriesID.end(); itemVector++) {
        getTrackById(*itemVector)->moveInfoTxtPosition();
    }
}

bool TrackMarkModel::isInfoGridTrackListEmptyAt(int row, int col)
{
    //int rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    //int index = row * rowCount + col;
    /*if (infoTxtGrid.find(RowColStruct(row,col)) != infoTxtGrid.end())
        return false;
    else
        return true;*/

    bool flag = true;
    if (trackGrid.find(RowColStruct(row,col)) != trackGrid.end()) {
        flag = false;
    }

    if (infoTxtGrid.find(RowColStruct(row,col)) != infoTxtGrid.end()) {
        flag = false;
    }
    return flag;
}

void TrackMarkModel::deleteTrackFromInfoGrid(int row, int col)
{
    //int rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    //int index = row * rowCount + col;
    auto item = infoTxtGrid.find(RowColStruct(row,col));
    if (item != infoTxtGrid.end()) {
        infoTxtGrid.erase(item);
    }
    else {
        qDebug() << "Shit happens №3";
    }
}

void TrackMarkModel::deleteTrackFromTrackGrid(int id, int row, int col)
{
    int counter = 0;
    const int passage = 2;
    for (int indexRow = -1; indexRow != passage; indexRow++) {
        for (int indexCol = -1; indexCol != passage; indexCol++) {
            for (auto items = trackGrid.equal_range(RowColStruct(row + indexRow,col + indexCol));items.first != items.second;) {
                if (items.first->second == id) {
                    items.first = trackGrid.erase(items.first);
                    counter++;
                }
                else
                    items.first++;
            }
        }
    }
    //qDebug() << "Удалено ячеек трасс " << QString::number(counter);
}

void TrackMarkModel::moveInfoTxt(int oldRow, int oldCol, int newRow, int newCol)
{
    //int rowCount = CfgManager::Instance()->getSizeSettings()->getInfoTxtRowCount();
    //int index1 = oldRow * rowCount + oldCol, index2 = newRow * rowCount + newCol;
    auto item = infoTxtGrid.find(RowColStruct(oldRow,oldCol));
    if (item != infoTxtGrid.end()) {
        infoTxtGrid.insert({RowColStruct(newRow,newCol), item->second});
        infoTxtGrid.erase(item);
    }
}

void TrackMarkModel::releaseModel() {    
    for (auto it = trackMarkMap->begin(); it != trackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        delete list;
    }
    trackMarkMap->clear();
    for (auto it1 = indicatorMarkMap->begin(); it1 != indicatorMarkMap->end(); it1++) {
        TrackMark *mark = it1->second;
        delete mark;
    }
    indicatorMarkMap->clear();
    infoTxtGrid.clear();
    trackGrid.clear();
}

void TrackMarkModel::deleteIndicatorMark(int id) {
    IndicatorMarkMap::iterator it = indicatorMarkMap->find(id);
    if (it != indicatorMarkMap->end()) {
        TrackMark *mark = it->second;
        indicatorMarkMap->erase(it);
        delete mark;
//        qDebug() << "TrackMarkModel::deleteIndicatorMark(), track ID: " << id << " deleted";
    } else {
//        qDebug() << "TrackMarkModel::deleteIndicatorMark(), track ID: " << id << "  NOT FOUND!!!";
    }
}

void TrackMarkModel::deleteTrack(int id) {
    if (id < 0) {
        qDebug() << "TrackMarkModel::deleteTrack ASSERT, track ID < 0!";
        assert(false);

        return;
    }

    auto it = trackMarkMap->find(id);
    if (it != trackMarkMap->end()) {
        TrackMarkList *list = it->second;
        deleteTrackFromTrackGrid(id, list->getMarkGridRow(), list->getMarkGridCol());
        deleteTrackFromInfoGrid(list->getInfoTxtGridRow(), list->getInfoTxtGridCol());
        /*int row, col;
        row = list->getInfoTxtGridRow();
        col = list->getInfoTxtGridCol();
        if (row >= 0 && col >= 0) {
            setInfoTxtAt(-1, row, col);
        }*/
        //trackMarkMap->erase(id);
        //delete list;

        list->setDeleted();

        //qDebug() << "TrackMarkModel::deleteTrack(), track ID: " << id;
    } else {
        //qDebug() << "TrackMarkModel::deleteTrack(), track ID: " << id << "  NOT FOUND!!!";
    }
/*
    TrackMarkMap::iterator it = trackMarkMap->find(msg->trackID);
    if ( it != trackMarkMap->end() ) { // if track exists, erase it
        TrackMarkList *list = it->second;
        list->addTrackMark(msg);
    } else {                         // handle case if track to be erased not found
*/
}

void TrackMarkModel::addIndicatorMark(RLSOaimMessage *msg) {
    if (msg->trackState != TRACK_STATE_RESET) {
        IndicatorMarkMap::iterator it = indicatorMarkMap->find(msg->trackID);
        if ( it != indicatorMarkMap->end() ) { // if mark exists, update pos
            TrackMark *mark = it->second;
            float dist = msg->D / 1000;
            mark->xPos = dist * cosf(msg->Az * PI / 180);
            mark->yPos = dist * sinf(msg->Az * PI / 180);
            mark->heading = msg->sAimCoords.tack;
        } else {                         // if not, add new indicator mark
            TrackMark *mark = new TrackMark;
            float dist = msg->D / 1000;
            mark->xPos = dist * cosf(msg->Az * PI / 180);
            mark->yPos = dist * sinf(msg->Az * PI / 180);
            mark->heading = msg->sAimCoords.tack;
            indicatorMarkMap->insert( IndicatorMarkMapPair(msg->trackID, mark) );
//            qDebug() << "TrackMarkModel::addIndicatorMark || added track id: " << msg->trackID;
        }
    }
}

void TrackMarkModel::addTrackMark(RLSOaimMessage *msg) {
    if (msg->trackID < 0) {
        qDebug() << "TrackMarkModel::addTrackMark ASSERT, track ID < 0!";
        assert(false);
        return;
    }

    /*if (!CfgManager::Instance()->getUiController()->getMainUIView()->isFillGlobalCenterPoint())
        return;*/

    auto it = trackMarkMap->find(msg->trackID);
    if ( it != trackMarkMap->end() ) { // if track exists, add new mark
        TrackMarkList *list = it->second;
        list->addTrackMark(msg);
        // notify UI
        CfgManager::Instance()->getTrackingController()->getDataModel()->getNotifier()->updateTrackInfo(msg->trackID);
    } else {                         // if not, add new track list
        TrackMarkList *list = new TrackMarkList(msg->trackID);
        list->addTrackMark(msg);
        trackMarkMap->insert( TrackMarkMapPair(msg->trackID, list) );
        // notify UI
        CfgManager::Instance()->getTrackingController()->getDataModel()->getNotifier()->addTrack(msg->trackID);
    }
}

TrackMarkList* TrackMarkModel::getTrackById(int id) {
    TrackMarkMap::iterator it = trackMarkMap->find(id);

    if ( it != trackMarkMap->end() ) {
        return (it->second);
    } else {
        qDebug() << "TrackMarkModel::getTrackById. Track not found!!!";
    }

    return nullptr;
}

TrackMarkList* TrackMarkModel::findTrackAt(float x, float y, float threshold) {
    /*TrackMarkList *retVal = nullptr;
    float minDist;
    for( TrackMarkMap::iterator it = trackMarkMap->begin(); it != trackMarkMap->end(); it++ ) {
        TrackMarkList *list = it->second;
        // due to gl transformations to match 0 deg to north direction x and y coords swaped
        if( y <= (list->getXPos() + threshold) && y >= (list->getXPos() - threshold) &&
            x <= (list->getYPos() + threshold) && x >= (list->getYPos() - threshold) ) {
            if (retVal != nullptr) {
                float dist = (list->getXPos() - y) * (list->getXPos() - y) + (list->getYPos() - x) * (list->getYPos() - x);
                if (dist < minDist) {
                    retVal = list;
                    minDist = dist;
                }
            } else {
                retVal = list;
                minDist = (list->getXPos() - y) * (list->getXPos() - y) + (list->getYPos() - x) * (list->getYPos() - x);
            }
        }
    }

    return retVal;*/

    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();

    float _x = x - model->getCurrentPos().x;
    float _y = y - model->getCurrentPos().y;

    int row = (int) ceil(_y / model->getRowSize());
    int col = (int) ceil(_x / model->getColSize());

    return model->getTrackById(model->getInfoTxtIDAt(row,col));
}

void TrackMarkList::get3DInfoTxtPos(float &az, float &z) {
    // due to gl transformations to match 0 azimuth with north, x - column, y - row
    az = (float) infoTxt3DGridCol * (360.0f / (float) CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount());
    z = (float) infoTxt3DGridRow * CfgManager::Instance()->getSizeSettings()->get3DInfoTxtRowSize();
}

void TrackMarkList::move3DInfoTxtPosition(bool &searching, const int &rowCount, const int &colCount) {
    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();
    infoTxt3DGridRow = trackMark3DGridRow;
    infoTxt3DGridCol = trackMark3DGridCol;

    Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
    if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
        !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
        Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
        if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
            !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
            // reset movement and move in another direction
            infoTxt3DGridRow = trackMark3DGridRow;
            infoTxt3DGridCol = trackMark3DGridCol;
            Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_RIGHT, rowCount, colCount);
            if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                    !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                    // reset movement and move in another direction
                    infoTxt3DGridRow = trackMark3DGridRow;
                    infoTxt3DGridCol = trackMark3DGridCol;
                    Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                    Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                    if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                        !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {


                        // not found a place in the nearest info grid cell, so look for a place
                        // 1 cell away
                        // reset movement and move in another direction
                        infoTxt3DGridRow = trackMark3DGridRow;
                        infoTxt3DGridCol = trackMark3DGridCol;
                        Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                        Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                        if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                            !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                            Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_BOTTOM, rowCount, colCount);
                            if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                // reset movement and move in another direction
                                infoTxt3DGridRow = trackMark3DGridRow;
                                infoTxt3DGridCol = trackMark3DGridCol;
                                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                                if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                    !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                    Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                                    if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                        !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                        // reset movement and move in another direction
                                        infoTxt3DGridRow = trackMark3DGridRow;
                                        infoTxt3DGridCol = trackMark3DGridCol;
                                        Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                                        Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                                        if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                            !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                            Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_RIGHT, rowCount, colCount);
                                            if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                                !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                                // reset movement and move in another direction
                                                infoTxt3DGridRow = trackMark3DGridRow;
                                                infoTxt3DGridCol = trackMark3DGridCol;
                                                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                                                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_TOP, rowCount, colCount);
                                                Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                                                if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                                    !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                                    Utils::moveIn3DGrid(infoTxt3DGridRow, infoTxt3DGridCol, MOVE_LEFT, rowCount, colCount);
                                                    if( model->get3DInfoTxtIDAt(infoTxt3DGridRow, infoTxt3DGridCol) != -1 ||
                                                        !model->is3DInfoGridTrackListEmptyAt(infoTxt3DGridRow, infoTxt3DGridCol) ) {
                                                        // if no place was found, set row and col to -2
                                                        // so info text will not be drawn
                                                        infoTxt3DGridRow = -2;
                                                        infoTxt3DGridCol = -2;
                                                        searching = false;
                                                    } else { searching = false; }
                                                } else { searching = false; }
                                            } else { searching = false; }
                                        } else { searching = false; }
                                    } else { searching = false; }
                                } else { searching = false; }
                            } else { searching = false; }
                        } else { searching = false; }


                    } else { searching = false; }
                } else { searching = false; }
            } else { searching = false; }
        } else { searching = false; }
    } else { searching = false; }
}

void TrackMarkList::find3DInfoTxtPosition() {
    int colCount = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtRowCount();
    float colSize = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColSize(),
          rowSize = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtRowSize();
    Q_UNUSED( colSize );
    TrackMarkModel *model = CfgManager::Instance()->getTrackingController()->getDataModel()->getTrackMarkModel();

    if ( infoTxt3DGridCol == -1 && infoTxt3DGridRow == -1 ) { // calc info text pos for new track
        int newCol = (float) CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount() * (az / 360.0f),
            newRow = (int) (sceneProjPosZ / rowSize) + 1;
        trackMark3DGridRow = infoTxt3DGridRow = newRow;
        trackMark3DGridCol = infoTxt3DGridCol = newCol;
        model->addTrackTo3DInfoGrid(trackID, newRow, newCol);

        bool searching = true;
        // search for a proper place
        do {
            move3DInfoTxtPosition(searching, rowCount, colCount);
        } while(searching);

        if (infoTxt3DGridCol >= 0 && infoTxt3DGridRow >= 0) {
            model->set3DInfoTxtAt(trackID, infoTxt3DGridRow, infoTxt3DGridCol);
        }
    } else { // check if position of info text needs to be changed
        int newCol = (float) CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount() * (az / 360.0f),
            newRow = (int) (sceneProjPosZ / rowSize) + 1;

        if ( newRow != trackMark3DGridRow || newCol != trackMark3DGridCol ) { // if track mark moved to another grid cell
            model->deleteTrackFrom3DInfoGrid(trackID, trackMark3DGridRow, trackMark3DGridCol);
            //qDebug() << "[" << trackMarkGridRow << ";" << trackMarkGridCol << "]: deleted " << trackID;

            trackMark3DGridRow = newRow;
            trackMark3DGridCol = newCol;

            model->addTrackTo3DInfoGrid(trackID, newRow, newCol);

            if( model->get3DInfoTxtIDAt(newRow, newCol) != -1 ) {
                // if track mark moved to cell where info text is present, find proper place to this text
                // search for a proper place
                TrackMarkList *list = CfgManager::Instance()->getTrackingController()->getDataModel()->
                                        getTrackMarkModel()->getTrackById(model->get3DInfoTxtIDAt(newRow, newCol));
                if (list != nullptr) {
                    model->set3DInfoTxtAt(-1, newRow, newCol);
                    bool searching = true;
                    do {
                        list->move3DInfoTxtPosition(searching, rowCount, colCount);
                    } while(searching);

                    if (list->getInfoTxt3DGridRow() >= 0 && list->getInfoTxt3DGridCol() >= 0) {
                        model->set3DInfoTxtAt(list->getTrackID(), list->getInfoTxt3DGridRow(), list->getInfoTxt3DGridCol());
                    }
                } else {
                    //qDebug() << "move info text TRACK NOT FOUND! ID: " << model->getInfoTxtIDAt(newRow, newCol);
                    //assert(false);
                }
            }

            // use different conditions, depending on mapScale
            float mapScale = CfgManager::Instance()->getUiController()->getMapScale();
            int moveFactor = 1;
            if (mapScale > 2.0f && mapScale <= 5.0f) {
                moveFactor = 2;
            } else if (mapScale > 5.0f && mapScale <= 10.0f) {
                moveFactor = 3;
            } else if ( mapScale > 10.0f) {
                moveFactor += 1 + mapScale / 10;
            }
            //qDebug() << "moveFactor: " << moveFactor << "  mapScale: " << mapScale;

            // move txt info block if track mark is to far from it or info text is hidden
            if ( abs(newRow - infoTxt3DGridRow) > moveFactor ||
                 abs(newCol - infoTxt3DGridCol) > moveFactor ||
                 infoTxt3DGridCol < 0 || infoTxt3DGridRow < 0 ) {
                // remove old pos from grid
                if (infoTxt3DGridCol >= 0 && infoTxt3DGridRow >= 0) {
                    model->set3DInfoTxtAt(-1, infoTxt3DGridRow, infoTxt3DGridCol);
                } else {
//                    qDebug() << "";
                }

                infoTxt3DGridRow = newRow;
                infoTxt3DGridCol = newCol;

                // search for a proper place
                bool searching = true;
                do {
                    move3DInfoTxtPosition(searching, rowCount, colCount);
                } while(searching);

                // add new pos to grid
                if (infoTxt3DGridCol >= 0 && infoTxt3DGridRow >= 0) {
                    model->set3DInfoTxtAt(trackID, infoTxt3DGridRow, infoTxt3DGridCol);
                }
            }
        } else {
            // if info text pos was not found, try to find again
            if ( infoTxt3DGridCol == -2 && infoTxt3DGridRow == -2 ) {
                // search for a proper place
                bool searching = true;
                do {
                    move3DInfoTxtPosition(searching, rowCount, colCount);
                } while(searching);

                //model->addTrackToInfoGrid(trackID, trackMarkGridRow, trackMarkGridCol);
                if (infoTxt3DGridCol >= 0 && infoTxt3DGridRow >= 0) {
                    model->set3DInfoTxtAt(trackID, infoTxt3DGridRow, infoTxt3DGridCol);
                }
            }
            // check if current track is not on some other's track info text
            if( model->get3DInfoTxtIDAt(trackMark3DGridRow, trackMark3DGridCol) != -1 ) {
                // if track mark moved to cell where info text is present, find proper place to this text
                // search for a proper place
                TrackMarkList *list = CfgManager::Instance()->getTrackingController()->getDataModel()->
                                        getTrackMarkModel()->getTrackById(model->get3DInfoTxtIDAt(newRow, newCol));
                if (list != nullptr) {
                    model->set3DInfoTxtAt(-1, list->getInfoTxt3DGridRow(), list->getInfoTxt3DGridCol());
                    bool searching = true;
                    do {
                        list->move3DInfoTxtPosition(searching, rowCount, colCount);
                    } while(searching);

                    if (list->getInfoTxt3DGridRow() >= 0 && list->getInfoTxt3DGridCol() >= 0) {
                        model->set3DInfoTxtAt(list->getTrackID(), list->getInfoTxt3DGridRow(), list->getInfoTxt3DGridCol());
                    } else {
                        //qDebug() << "123";
                    }
                } else {
                    //assert(false);
//                    qDebug() << "TRACK NOT FOUND! ID: " << model->getInfoTxtIDAt(newRow, newCol);
                }
            }
        }
    }
}

void TrackMarkModel::reset3DInfoTxtGrid() {
    float colSize = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColSize(),
          rowSize = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtRowSize();
    Q_UNUSED( colSize );
    int colCount = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtRowCount();
    // release memory
    for (InfoGrid::iterator it = infoTxt3DGrid.begin(); it != infoTxt3DGrid.end(); it++) {
        vector<InfoGridItem> *row = &*it;
        row->clear();
    }
    infoTxt3DGrid.clear();
    // reinit grid
    initTrackInfoTxt3DGrid();
    for (TrackMarkMap::iterator it = trackMarkMap->begin(); it != trackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        int newCol = (float) CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount() * (list->getAzimuth() / 360.0f),
            newRow = (int) (list->getZProjPos() / rowSize) + 1;
        list->setMark3DGridRow(newRow);
        list->setMark3DGridCol(newCol);
        list->setInfoTxt3DGridRow(-1);
        list->setInfoTxt3DGridCol(-1);
        addTrackTo3DInfoGrid(list->getTrackID(), newRow, newCol);
    }
    for (TrackMarkMap::iterator it = trackMarkMap->begin(); it != trackMarkMap->end(); it++) {
        TrackMarkList *list = it->second;
        // search for a proper place
        bool searching = true;
        do {
            list->move3DInfoTxtPosition(searching, rowCount, colCount);
        } while(searching);

        if (list->getInfoTxt3DGridRow() >= 0 && list->getInfoTxt3DGridCol() >= 0) {
            set3DInfoTxtAt(list->getTrackID(), list->getInfoTxt3DGridRow(), list->getInfoTxt3DGridCol());
        }
    }
}

void TrackMarkModel::initTrackInfoTxt3DGrid() {
    int colCount = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtColCount(),
        rowCount = CfgManager::Instance()->getSizeSettings()->get3DInfoTxtRowCount();
    //infoTxtGrid = new InfoGridItem*[rowCount];
    infoTxt3DGrid.resize(rowCount + 1);
    for (int i = 0; i <= rowCount; ++i) {
        infoTxt3DGrid[i].resize(colCount);
    }
/*    for(int i = 0; i <= rowCount; i++) {
        for(int j = 0; j <= colCount; j++) {
            infoTxtGrid[i][j];
            //qDebug() << "[" << i << "," << j << "]: " << infoTxtGrid[i][j].trackID << "  ||  empty? " << infoTxtGrid[i][j].tracksList.empty();
        }
    } */
}
