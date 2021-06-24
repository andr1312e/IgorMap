#include "msgnotifier.h"
#include <ConfigurationManager/cfgmanager.h>

DataModelNotifier::DataModelNotifier(QObject *parent) :
    QObject(parent)
{
    qDebug() << "create msg notifier";
    connect(this, SIGNAL(newTrack(int)), CfgManager::Instance()->getUiController()->getMainUIView(), SLOT(onNewTrack(int)), Qt::QueuedConnection);
    //connect(this, SIGNAL(newTrack(int)), CfgManager::Instance()->getUiController()->getTrackListWidget(), SLOT(onAddTrack(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(eraseTrack(int)), CfgManager::Instance()->getUiController()->getMainUIView(), SLOT(onDeleteTrack(int)), Qt::QueuedConnection);
    //connect(this, SIGNAL(eraseTrack(int)), CfgManager::Instance()->getUiController()->getTrackListWidget(), SLOT(onDeleteTrack(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(trackMarkUpdated(int)), CfgManager::Instance()->getUiController()->getMainUIView(), SLOT(onUpdateTrack(int)), Qt::QueuedConnection);
    //connect(this, SIGNAL(trackMarkUpdated(int)), CfgManager::Instance()->getUiController()->getTrackListWidget(), SLOT(onUpdateTrackInfo(int)), Qt::QueuedConnection);
    //connect(this, SIGNAL(modelCleaned()), CfgManager::Instance()->getUiController()->getTrackListWidget(), SLOT(onModelClean()), Qt::QueuedConnection);
    //connect(this, SIGNAL(onUpdateIndicator()), CfgManager::Instance()->getUiController()->getIndicator(), SLOT(update()), Qt::QueuedConnection);
}

void DataModelNotifier::addTrack(int id) {
    emit newTrack(id);
}

void DataModelNotifier::deleteTrack(int id) {
    emit eraseTrack(id);
}

void DataModelNotifier::updateTrackInfo(int id) {
    emit trackMarkUpdated(id);
}

void DataModelNotifier::cleanModel() {
    emit modelCleaned();
}

void DataModelNotifier::updateIndicator() {
    emit onUpdateIndicator();
}
