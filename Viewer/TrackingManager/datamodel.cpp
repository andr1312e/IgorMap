#include "datamodel.h"

DataModel::DataModel() {
    trackMarkModel = new TrackMarkModel();
    //newTrackMarkModel = new NewTrackMarkModel();
    //trackHistoryModel = new TrackHistoryModel();
    ktaMarkModel = new KTAMarkModel();
    //analogMarkModel = new AnalogMarkModel();
    //blankArea = new BlankArea();
}

DataModel::~DataModel() {
    //delete mNotifier;
    //delete trackHistoryModel;
    //delete analogMarkModel;
    delete trackMarkModel;
    //delete newTrackMarkModel;
    delete ktaMarkModel;
    //delete blankArea;
}

void DataModel::addTrackMessage(RLSOaimMessage *msg) {
    trackMarkModel->lockTrackModel();
    trackMarkModel->addTrackMark(msg);
    trackMarkModel->unlockTrackModel();

    /*trackMarkModel->lockIndicatorModel();
    trackMarkModel->addIndicatorMark(msg);
    trackMarkModel->unlockIndicatorModel();
    mNotifier->updateIndicator();*/
}

void DataModel::displayTrack(int id)
{
    trackMarkModel->lockTrackModel();
    trackMarkModel->displayTrackHistory(id);
    trackMarkModel->unlockTrackModel();
}

void DataModel::cleanTrack()
{
    trackMarkModel->lockTrackModel();
    trackMarkModel->cleanTrack();
    trackMarkModel->unlockTrackModel();
}

/*void DataModel::addTrackHistoryMessage(RLSOaimMessage *msg) {
    trackHistoryModel->lockTrackHistoryModel();
    trackHistoryModel->addTrackMark(msg);
    trackHistoryModel->unlockTrackHistoryModel();
}*/

void DataModel::redrawInfoGrid() {
    trackMarkModel->lockTrackModel();
    //CfgManager::Instance()->getSizeSettings()->initInfoTxtGrid();
    trackMarkModel->resetInfoTxtGrid();
    trackMarkModel->unlockTrackModel();
    /*newTrackMarkModel->lockTrackModel();
    newTrackMarkModel->resetModel();
    newTrackMarkModel->unlockTrackModel();*/
}

/*void DataModel::redrawTrackHistoryGrid() {
    trackHistoryModel->lockTrackHistoryModel();
    CfgManager::Instance()->getSizeSettings()->initInfoTxtGrid();
    trackHistoryModel->resetTrackInfoGrid();
    trackHistoryModel->initTrackInfoGrid();
    trackHistoryModel->unlockTrackHistoryModel();
}*/

void DataModel::deleteTrack(int id) {
    //trackMarkModel->lockTrackModel();
    mNotifier->deleteTrack(id);
    // do not delete track here, instead delete from track list widget!
    //trackMarkModel.deleteTrack(id);
    //trackMarkModel->unlockTrackModel();

    /*trackMarkModel->lockIndicatorModel();
    trackMarkModel->deleteIndicatorMark(id);
    trackMarkModel->unlockIndicatorModel();*/
    //mNotifier->updateIndicator();
}

void DataModel::addKTAMark(RLSOPlotMessage *msg, uint type) {

    ktaMarkModel->addKTAMark(msg, type);
}

/*void DataModel::addAnalogMark(RLSOAnalogSignalMessage *msg) {
    analogMarkModel->lockAnalogModel();
    analogMarkModel->addAnalogMark(msg);
    analogMarkModel->unlockAnalogModel();
}*/

void DataModel::cleanModel() {

    trackMarkModel->lockTrackModel();
    trackMarkModel->cleanModel();
    trackMarkModel->unlockTrackModel();
    // clean kta marks

    ktaMarkModel->cleanModel();
}

void DataModel::releaseModel()
{

    trackMarkModel->releaseModel();
}

void DataModel::addTrack(RLSOaimMessage *msg)
{
//    newTrackMarkModel->lockTrackModel();
//    newTrackMarkModel->addTrackMark(msg);
//    newTrackMarkModel->unlockTrackModel();
}

void DataModel::resetTrack(int id)
{
//    newTrackMarkModel->lockTrackModel();
//    newTrackMarkModel->deleteTrackMark(id);
//    newTrackMarkModel->unlockTrackModel();
}
