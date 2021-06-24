#include "dspwidget.h"

#include <QListView>
#include <QStandardItemModel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QScrollBar>
#include <QComboBox>
#include <QCheckBox>
#include <QMenu>
#include <QAction>
#include <bMath.h>
#include <QThread>
#include <QSharedDataPointer>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DSPWidget::DSPWidget(QWidget *parent) : BaseWidget(WidgetTypes::DSPControl, parent),
    dspCounter(0), dspPlottingCounter(0),
    maxDSP(10), maxDSPPlotting(2),
    incorrectID(-111),
    dataPathStr(dspDataPath),
    replacementRow(-1)
{
    setTitle("ДСП");

    //plotterWidget = new CustomPlotterWidget(10);
    //plotterWidget->show();

    dspDataHandler = new DSPDataHandler();

    listView = new QListView();
    QStandardItemModel *model = new QStandardItemModel(0, 1);

    listView->setModel(model);
    listView->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setUniformItemSizes(true);
    listView->setFixedHeight(100);

    initMenu();
    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listView, &QListView::customContextMenuRequested, this, &DSPWidget::customMenuForList);

    QHBoxLayout *listBodyLayout = new QHBoxLayout();
    //listBodyLayout->setContentsMargins(margin);
    listBodyLayout->addWidget(listView);

    listDSPGroupBox = new QGroupBox("Набор ДСП");
    listDSPGroupBox->setLayout(listBodyLayout);

    QStringList list;
    dspModeCb = new QComboBox();
    list << TableAttributes::dsp2Str << TableAttributes::dsp20Str;
    dspModeCb->addItems(list);
    list.clear();
    plottingDSPCheckBox = new QCheckBox("Отображение ДСП");
    plottingDSPCheckBox->setEnabled(true);
    plottingDSPButton = new QPushButton("График");
    //plottingDSPButton->setCheckable(true);
    plottingDSPButton->setEnabled(false);

    QVBoxLayout *dspModeBodyLayout = new QVBoxLayout();
    dspModeBodyLayout->setContentsMargins(margin);
    dspModeBodyLayout->addWidget(dspModeCb);
    dspModeBodyLayout->addWidget(plottingDSPCheckBox);
    dspModeBodyLayout->addWidget(plottingDSPButton,0, Qt::AlignRight);
    dspModeBodyLayout->addStretch(1);

    QGroupBox *dspModeGroupBox = new QGroupBox("Режим работы");
    dspModeGroupBox->setStyleSheet(groupBoxCSS);
    dspModeGroupBox->setLayout(dspModeBodyLayout);

    numberOfTargetCb = new QComboBox();
    QVBoxLayout *numberTargetBodyLayout = new QVBoxLayout();
    numberTargetBodyLayout->setContentsMargins(margin);
    numberTargetBodyLayout->addWidget(numberOfTargetCb);
    numberTargetBodyLayout->addStretch(1);

    QGroupBox *numberTargetGroupBox = new QGroupBox("Номер цели");
    numberTargetGroupBox->setStyleSheet(groupBoxCSS);
    numberTargetGroupBox->setLayout(numberTargetBodyLayout);

    acceptDSPButton = new QPushButton("Применить");
    clearDSPButton = new QPushButton("Сбросить");

    QHBoxLayout *buttonDSPLayout = new QHBoxLayout();
    buttonDSPLayout->addStretch(1);
    buttonDSPLayout->addWidget(acceptDSPButton);
    buttonDSPLayout->addWidget(clearDSPButton);

    QVBoxLayout *parametersDSPBodyLayout = new QVBoxLayout();
    parametersDSPBodyLayout->setContentsMargins(margin);
    parametersDSPBodyLayout->addWidget(numberTargetGroupBox);
    parametersDSPBodyLayout->addWidget(dspModeGroupBox);
    parametersDSPBodyLayout->addLayout(buttonDSPLayout);

    parametersDSPGroupBox = new QGroupBox("Параметры ДСП");
    parametersDSPGroupBox->setLayout(parametersDSPBodyLayout);
    parametersDSPGroupBox->setEnabled(false);

    track1Cb = new QComboBox();
    track2Cb = new QComboBox();

    QHBoxLayout *targetSelectionBodyLayout = new QHBoxLayout();
    targetSelectionBodyLayout->setContentsMargins(margin);
    targetSelectionBodyLayout->addWidget(track1Cb);
    targetSelectionBodyLayout->addWidget(track2Cb);

    QGroupBox *targetSelectionGruopBox = new QGroupBox("Выбор целей");
    targetSelectionGruopBox->setStyleSheet(groupBoxCSS);
    targetSelectionGruopBox->setLayout(targetSelectionBodyLayout);

    autoCTCheckBox = new QCheckBox("Автоматический запуск");
    startCTButton = new QPushButton("Пуск");
    plottingCTButton = new QPushButton("График");

    QHBoxLayout *buttonLaunchLayout = new QHBoxLayout();
    buttonLaunchLayout->addStretch(1);
    buttonLaunchLayout->addWidget(startCTButton);
    buttonLaunchLayout->addWidget(plottingCTButton);

    QVBoxLayout *ctLaunchBodyLayout = new QVBoxLayout();
    ctLaunchBodyLayout->setContentsMargins(margin);
    ctLaunchBodyLayout->addWidget(autoCTCheckBox);
    //ctLaunchBodyLayout->addLayout(buttonLaunchLayout);
    //ctLaunchBodyLayout->addWidget(startCTButton,0, Qt::AlignRight);
    ctLaunchBodyLayout->addStretch(1);

    QGroupBox *launchCTGroupBox = new QGroupBox("Параметры запуска");
    launchCTGroupBox->setStyleSheet(groupBoxCSS);
    launchCTGroupBox->setLayout(ctLaunchBodyLayout);

    acceptCTButton = new QPushButton("Применить");
    clearCTButton = new QPushButton("Сбросить");

    QHBoxLayout *buttonCTLayout = new QHBoxLayout();
    buttonCTLayout->addStretch(1);
    buttonCTLayout->addWidget(acceptCTButton);
    //buttonCTLayout->addWidget(clearCTButton);

    QVBoxLayout *parametersCTBodyLayout = new QVBoxLayout();
    parametersCTBodyLayout->setContentsMargins(margin);
    parametersCTBodyLayout->addWidget(targetSelectionGruopBox);
    parametersCTBodyLayout->addWidget(launchCTGroupBox);
    parametersCTBodyLayout->addLayout(buttonCTLayout);

    ctGroupBox = new QGroupBox("Сближение целей");
    ctGroupBox->setLayout(parametersCTBodyLayout);

    dspListView = new QListView();
    QStandardItemModel *model2 = new QStandardItemModel(0, 1);
    /*QString str = QDateTime::currentDateTime().toString(QString("dd.MM.yy hh:mm:ss.z")) + QString(" Tr111 2ms");
    for (quint8 index = 0; index != 20; index++) {
        QStandardItem *item = new QStandardItem();
        item->setData(str, Qt::DisplayRole);
        model2->setItem(index, item);
    }*/

    dspListView->setModel(model2);
    dspListView->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    dspListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dspListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dspListView->setUniformItemSizes(true);
    dspListView->setFixedHeight(150);
    dspListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    initDSPList();

    QPushButton *openDSPFileButton = new QPushButton("Открыть запись");
    QHBoxLayout *pleerBodyLayout = new QHBoxLayout();
    pleerBodyLayout->addWidget(dspListView);
    //pleerBodyLayout->addStretch(1);
    //pleerBodyLayout->addWidget(openDSPFileButton);

    pleerDSPGroupBox = new QGroupBox("Воспроизведение");
    pleerDSPGroupBox->setLayout(pleerBodyLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(listDSPGroupBox);
    mainLayout->addWidget(parametersDSPGroupBox);
    mainLayout->addWidget(ctGroupBox);
    mainLayout->addWidget(pleerDSPGroupBox);

    setLayout(mainLayout);

    connect(listView, &QListView::clicked, this, &DSPWidget::listViewItemClicked);
    connect(this, &DSPWidget::updateComboBoxWithTargetsSignal, this, &DSPWidget::updateComboBoxWithTargetsSlot);
    connect(plottingDSPCheckBox, &QCheckBox::released, this, &DSPWidget::plottingToggled);

    connect(acceptDSPButton, &QPushButton::released, this, &DSPWidget::acceptEffectDSP);
    connect(clearDSPButton, &QPushButton::released, this, &DSPWidget::clearEffectDSP);
    connect(acceptCTButton, &QPushButton::released, this, &DSPWidget::acceptEffectCT);
    connect(clearCTButton, &QPushButton::released, this, &DSPWidget::clearEffectCT);

    connect(plottingDSPButton, &QPushButton::released, this, &DSPWidget::showHidePlotterWidget);
    connect(this, &DSPWidget::changeDSP, dspDataHandler, &DSPDataHandler::prepareDSPInfo);
    connect(this, &DSPWidget::showDSPPlot, dspDataHandler, &DSPDataHandler::showPlot);

    //connect(openDSPFileButton, &QPushButton::released, this, &DSPWidget::openDSPFile);
    connect(dspListView, &QListView::doubleClicked, this, &DSPWidget::openDSPFile);
}

DSPDataHandler *DSPWidget::getDSPDataHandler() const
{
    return dspDataHandler;
}

void DSPWidget::dspAvailabilityRequest()
{    
    emit isExceedingUsageLimitSignal(dspCounter != maxDSP, dspPlottingCounter != maxDSPPlotting);
}

void DSPWidget::removeDSP(qint32 targetID)
{
    qDebug() << "DSPWidget::removeDSP - targetID " << targetID;
    auto itemOfMap = mapOfDSP.find(targetID);
    if (itemOfMap != mapOfDSP.end()) {
        if (itemOfMap.value().isPlotting)
            dspPlottingCounter--;
        dspCounter--;
        mapOfDSP.erase(itemOfMap);
    }

    emit changeDSP(targetID, DSPType::None, false);

    auto itemOfTargets = mapOfPossibleTargets.find(targetID);
    if (itemOfTargets != mapOfPossibleTargets.end()) {
        itemOfTargets.value() = false;
    }

    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
    QList<QStandardItem *> modelSearchingList;
    if (targetID >= 0) {
        modelSearchingList = model->findItems(QString("трассе №%1").arg(targetID), Qt::MatchContains);
    }
    else {
        targetID = abs(targetID);
        modelSearchingList = model->findItems(QString("ЦУ №%1").arg(targetID), Qt::MatchContains);
    }
    if (!modelSearchingList.isEmpty()) {
        model->removeRow(modelSearchingList.at(0)->row());
    }

    dspAvailabilityRequest();
}

void DSPWidget::newTarget(qint32 targetID)
{
    auto itemOfPossibleMap = mapOfPossibleTargets.find(targetID);
    if (itemOfPossibleMap == mapOfPossibleTargets.end()) {
        mapOfPossibleTargets.insert(targetID, false);
    }
    else {
        qDebug() << "DSPWidget::newTarget - target repeats";
    }

    updateComboBoxWithTargetsSlot();
}

void DSPWidget::clearTarget(qint32 targetID)
{
    removeDSP(targetID);

    auto itemOfPossibleMap = mapOfPossibleTargets.find(targetID);
    if (itemOfPossibleMap != mapOfPossibleTargets.end()) {
        mapOfPossibleTargets.erase(itemOfPossibleMap);
    }
    else {
        qDebug() << "DSPWidget::clearTarget - target not found";
    }

    updateComboBoxWithTargetsSlot();
}

void DSPWidget::insertDSP(qint32 targetID, DSPType type, bool isPlotting)
{
    if (type == DSPType::None) {
        removeDSP(targetID);
        return;
    }

    auto itemOfMap = mapOfDSP.find(targetID);
    if (itemOfMap == mapOfDSP.end()) {
        if (dspCounter < maxDSP)
            dspCounter++;
        if (isPlotting) {
            if (dspPlottingCounter < maxDSPPlotting) {
                dspPlottingCounter++;
            }
        }
    }
    else {
        if (itemOfMap.value().isPlotting != isPlotting) {
            if (isPlotting) {
                if (dspPlottingCounter < maxDSPPlotting) {
                    dspPlottingCounter++;
                }
            }
            else {
                dspPlottingCounter--;
            }
        }
    }
    itemOfMap = mapOfDSP.insert(targetID, DSPInfo(type, isPlotting));
    emit changeDSP(targetID, type, isPlotting);

    auto possibleItem = mapOfPossibleTargets.find(targetID);
    if (possibleItem != mapOfPossibleTargets.end()) {
        possibleItem.value() = true;
    }

    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
    QString dataIntoTable, searchingStr;
    if (targetID >= 0) {
        dataIntoTable = QString("ДСП %1мс по трассе №%2 ").arg(type == DSPType::DSP2 ? 2 : 20).arg(targetID);
        searchingStr = QString("трассе №%1").arg(targetID);
    }
    else {
        targetID = abs(targetID);
        dataIntoTable = QString("ДСП %1мс по ЦУ №%2 ").arg(type == DSPType::DSP2 ? 2 : 20).arg(targetID);
        searchingStr = QString("ЦУ №%1").arg(targetID);
    }

    QList<QStandardItem *> modelSearchingList(model->findItems(searchingStr, Qt::MatchContains));
    if (modelSearchingList.isEmpty()) {
        QStandardItem *item = new QStandardItem;
        item->setData(dataIntoTable, Qt::DisplayRole);
        if (replacementRow != -1) {
            model->setItem(replacementRow, item);
            if (listView->currentIndex().row() == replacementRow){
                updateFields(itemOfMap);
            }
            replacementRow = -1;
        }
        else
            model->setItem(model->rowCount(), item);
    }
    else {
        modelSearchingList.at(0)->setData(dataIntoTable, Qt::DisplayRole);
        if (listView->currentIndex().row() == modelSearchingList.at(0)->row()) {
            updateFields(itemOfMap);
        }
    }

    dspAvailabilityRequest();
}

void DSPWidget::initMenu()
{
    tableMenu = new QMenu();
    QAction *action = new QAction("Добавить ДСП");
    connect(action, &QAction::triggered,
            [this] () {
        if (dspCounter < maxDSP) {

        }
    });
    tableMenu->addAction(action);

    action = new QAction("Удалить ДСП");
    connect(action, &QAction::triggered,
            [this] () {
        clearEffectDSP();
    });
    tableMenu->addAction(action);
}

void DSPWidget::initDSPList()
{
    QDir dspDataDir(dataPathStr);
    if (dspDataDir.exists()) {
        QStringList filters;
        filters << QString("*.dsp");
        QStringList listOfDSPRecording = dspDataDir.entryList(filters, QDir::Files, QDir::Time);

        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(dspListView->model());
        model->clear();

        quint32 index = 0;
        for(auto &itemOfList : listOfDSPRecording) {
            QStandardItem *item = new QStandardItem();
            item->setData(itemOfList, Qt::DisplayRole);
            model->setItem(index++, item);
        }
    }

}

void DSPWidget::updateFields(QMap<qint32, DSPInfo>::iterator &itemOfMap)
{
    dspModeCb->setCurrentIndex(dspModeCb->findText(itemOfMap.value().type == DSPType::DSP2 ?
                                                   TableAttributes::dsp2Str : TableAttributes::dsp20Str));
    plottingDSPCheckBox->setChecked(itemOfMap.value().isPlotting);
    plottingDSPButton->setEnabled(itemOfMap.value().isPlotting);
}

void DSPWidget::clearFields()
{
    listView->clearSelection();
    parametersDSPGroupBox->setEnabled(false);
    plottingDSPCheckBox->setChecked(false);
}

void DSPWidget::customMenuForList(QPoint pos)
{
    tableMenu->move(listView->viewport()->mapToGlobal(pos));
    tableMenu->show();
}

void DSPWidget::listViewItemClicked(const QModelIndex &index)
{
    parametersDSPGroupBox->setEnabled(true);

    qint32 targetId = idFromString(index.data().toString());
    if (targetId == incorrectID) {
        qDebug() << "DSPWidget::listViewItemClicked - Track not found in string";
        return;
    }

    auto itemOfTargetMap = mapOfDSP.find(targetId);
    if (itemOfTargetMap != mapOfDSP.end()) {
        /*if (targetId < 0)
            numberOfTargetCb->setCurrentIndex(numberOfTargetCb->findText(QString("ЦУ №%1 ").arg(abs(targetId))));
        else {
            numberOfTargetCb->setCurrentIndex(numberOfTargetCb->findText(QString("Трасса №%1 ").arg(targetId)));
        }*/
        updateComboBoxWithTargetsSlot();
        updateFields(itemOfTargetMap);
        /*dspModeCb->setCurrentIndex(dspModeCb->findText(itemOfTargetMap.value().type == DSPType::DSP2 ?
                                                       TableAttributes::dsp2Str : TableAttributes::dsp20Str));
        plottingDSPCheckBox->setChecked(itemOfTargetMap.value().isPlotting);
        //if (itemOfTargetMap.value().type == DSPType::DSP20)
            plottingDSPButton->setEnabled(itemOfTargetMap.value().isPlotting);*/
        //else
        //    plottingDSPButton->setEnabled(false);
    }
}

void DSPWidget::updateComboBoxWithTargetsSlot()
{
    qint32 targetId = idFromSelectedItemOfList();
    if (targetId != incorrectID) {
        numberOfTargetCb->clear();
        QStringList list;
        if (targetId < 0) {
            list << QString("ЦУ №%1 ").arg(abs(targetId));
        }
        else {
            list << QString("Трасса №%1 ").arg(targetId);
        }
        for (auto possibleItem = mapOfPossibleTargets.begin(); possibleItem != mapOfPossibleTargets.end(); possibleItem++) {
            if (!possibleItem.value()) {
                if (possibleItem.key() < 0) {
                    list << QString("ЦУ №%1 ").arg(abs(possibleItem.key()));
                }
                else {
                    list << QString("Трасса №%1 ").arg(possibleItem.key());
                }
            }
        }
        numberOfTargetCb->addItems(list);
        numberOfTargetCb->setCurrentIndex(0);
    }
}

void DSPWidget::plottingToggled()
{
    QCheckBox *chb = qobject_cast<QCheckBox*>(sender());

    qint32 targetId = idFromSelectedItemOfList();
    if (targetId != incorrectID) {
        auto itemOfTrackMap = mapOfDSP.find(targetId);
        if (itemOfTrackMap != mapOfDSP.end()) {
            if (itemOfTrackMap.value().isPlotting) {
                chb->setEnabled(true);
                //plottingCTButton->setEnabled(true);
            }
            else {
                if (dspPlottingCounter == maxDSPPlotting) {
                    chb->setChecked(false);
                    chb->setEnabled(false);
                    //plottingCTButton->setEnabled(false);
                }
            }
        }
    }
}

void DSPWidget::acceptEffectDSP()
{
    qint32 lastTargetId = idFromSelectedItemOfList(),
           currentTargetId = idFromSelectedItemOfComboBox();
    if (lastTargetId != incorrectID && currentTargetId != incorrectID) {
        DSPInfo info;
        info.type = (dspModeCb->currentText() == TableAttributes::dsp20Str) ? DSPType::DSP20 : DSPType::DSP2;
        info.isPlotting = plottingDSPCheckBox->checkState();

        if (lastTargetId != currentTargetId) {
            replacementRow = listView->currentIndex().row();
            removeDSP(lastTargetId);
            emit changeDSP(lastTargetId, DSPType::None, false);
        }
        else {
            auto itemOfMap = mapOfDSP.find(lastTargetId);
            if (itemOfMap == mapOfDSP.end()) {

                if (info.type == itemOfMap.value().type &&
                        info.isPlotting == itemOfMap.value().isPlotting ) {
                    return;
                }
            }
            else {
                qDebug() << "DSPWidget::acceptEffectDSP - TargetID not found in map";
            }

        }
//        DSPInfo info;
//        info.type = (dspModeCb->currentText() == TableAttributes::dsp20Str) ? DSPType::DSP20 : DSPType::DSP2;
//        info.isPlotting = plottingDSPCheckBox->checkState();
        /*if (info.isPlotting && info.type == DSPType::DSP20){
            plottingDSPButton->setEnabled(true);
        }
        else {
            plottingDSPButton->setEnabled(false);
        }*/
        plottingDSPButton->setEnabled(info.isPlotting);
        insertDSP(currentTargetId, info.type, info.isPlotting);
        //emit changeDSP(currentTargetId, info.type, info.isPlotting);
    }
}

void DSPWidget::clearEffectDSP()
{
    qint32 targetId = idFromSelectedItemOfList();
    if (targetId != incorrectID) {
        removeDSP(targetId);
        emit changeDSP(targetId, DSPType::None, false);

        clearFields();
    }
}

void DSPWidget::acceptEffectCT()
{

}

void DSPWidget::clearEffectCT()
{

}

void DSPWidget::showHidePlotterWidget()
{
    qint32 currentTargetId = idFromSelectedItemOfList();
    emit showDSPPlot(currentTargetId);
}

void DSPWidget::openDSPFile(const QModelIndex &index)
{
    QFile dataFile(QString(dspDataPath + index.data().toString()));
    if (dataFile.exists()) {
        dspDataHandler->parseDSPFile(dataFile);
    }
    else {
        qDebug() << "DSPWidget::openDSPFile - File doesn't exist";
    }
}

qint32 DSPWidget::idFromString(QString strOnCurrentIndex)
{
    bool trackFlag = false;
    if (strOnCurrentIndex.indexOf("ЦУ") == -1) {
        trackFlag = true;
    }

    int traceIdInitEnteryOfString = strOnCurrentIndex.indexOf("№"),
            traceIdFinishEnteryOfString;
    if (traceIdInitEnteryOfString == -1) {
        qDebug() << "DSPWidget::idFromString - Bad format of string";
        return incorrectID;
    }
    traceIdFinishEnteryOfString = strOnCurrentIndex.indexOf(" ", traceIdInitEnteryOfString++);
    if (traceIdFinishEnteryOfString == -1) {
        qDebug() << "DSPWidget::idFromString - Bad format of string";
        return incorrectID;
    }

    qint32 targetID = strOnCurrentIndex.mid(traceIdInitEnteryOfString, traceIdFinishEnteryOfString - traceIdInitEnteryOfString).toInt();
    if (!trackFlag) {
        targetID = -targetID;
    }
    return targetID;
}

qint32 DSPWidget::idFromSelectedItemOfList()
{
    auto selectedList = listView->selectionModel()->selectedRows();
    if (!selectedList.isEmpty()) {
        QString strID = selectedList.at(0).data().toString();
        qint32 targetId = idFromString(strID);
        if (targetId == incorrectID) {
            qDebug() << "DSPWidget::idFromSelectedItemOfList - Track not found in string";
            //return incorrectID;
        }
        return targetId;
    }
    return incorrectID;
}

qint32 DSPWidget::idFromSelectedItemOfComboBox()
{
    if (numberOfTargetCb->currentIndex() != -1) {
        QString strID = numberOfTargetCb->currentText();
        qint32 targetId = idFromString(strID);
        if (targetId == incorrectID) {
            qDebug() << "DSPWidget::idFromSelectedItemOfList - Track not found in string";
            //return incorrectID;
        }
        return targetId;
    }
    return incorrectID;
}

DSPDataHandler::DSPDataHandler(QObject *parent) : QObject(parent),
    maxPartOfData(10),
    dateFormat("dd.MM.yy_hh:mm:ss.z"), extensionOfFiles(".dsp")
{
    qRegisterMetaType<RLSODSPDataMessage>();    

    threadObject = new QThread();
    fftwProcessorObject = new FFTWProcessor();
    fftwProcessorObject->moveToThread(threadObject);
    connect(threadObject, &QThread::finished, fftwProcessorObject, &QObject::deleteLater);
    connect(threadObject, &QThread::finished, threadObject, &QThread::deleteLater);
    connect(threadObject, &QThread::started, fftwProcessorObject, &FFTWProcessor::doWork);

    threadObject->start(QThread::NormalPriority);

    connect(this, &DSPDataHandler::dataReadyForProcessing, fftwProcessorObject, &FFTWProcessor::newDataForWork);
    connect(this, &DSPDataHandler::dspChanged, fftwProcessorObject, &FFTWProcessor::dspChangedSlot);
    connect(this, &DSPDataHandler::prepareFFTWSignal, fftwProcessorObject, &FFTWProcessor::setPlane);
    connect(fftwProcessorObject, &FFTWProcessor::processedData, this, &DSPDataHandler::setData);

    //colorSchemeWidget = new ColorSchemeWidget();
    //colorSchemeWidget->show();
    //plotterWidget = new CustomPlotterWidget(101, false);
    //plotterWidget->show();
    //prepareDSPInfo(101, DSPType::DSP2, true);
}

DSPDataHandler::~DSPDataHandler()
{
    threadObject->quit();
    threadObject->wait(200);
}

void DSPDataHandler::parseDSPFile(QFile &fileWithData)
{
    if (!fileWithData.open(QIODevice::ReadOnly)) {
        qDebug() << "DSPDataHandler::parseDSPFile - Can't open dsp data file";
        return;
    }

    if (currentFile == fileWithData.fileName()) {
        auto &item = mapOfDSPDataForPleer.first();
        if (item.type == DSPType::DSP20) {
            if (item.plotterWidget->isHidden()) {
                item.plotterWidget->show();
            }
        }
        return;
    }
    else {
        currentFile = fileWithData.fileName();
    }

    if (!mapOfDSPDataForPleer.isEmpty()) {
        auto &item = mapOfDSPDataForPleer.first();
        item.plotterWidget->hide();
        delete item.plotterWidget;
        if (item.type == DSPType::DSP20)
            disconnect(item.plotterWidget, &CustomPlotterWidget::setPositionOnVectorOfDSP, this, &DSPDataHandler::setPositionOnVectorOfDSPSlot);
        mapOfDSPDataForPleer.clear();
    }

    QByteArray saveData = fileWithData.readAll();
    fileWithData.close();
    QJsonDocument settingDoc(QJsonDocument::fromJson(saveData));

    const QJsonObject &json = settingDoc.object();

    qint32 targetID;
    if (json.contains("target") && json["target"].isDouble()) {
        targetID = json["target"].toInt();
    }

    DSPDataInfo dspInfo;
    dspInfo.plotterWidget = new CustomPlotterWidget(targetID);

    auto itemOfPleer = mapOfDSPDataForPleer.insert(targetID, dspInfo);
    auto &valueOfItem = itemOfPleer.value();

    if (json.contains("type") && json["type"].isString()) {
        valueOfItem.type = json["type"].toString() == TableAttributes::dsp20Str ? DSPType::DSP20 : DSPType::DSP2;
    }

    if (json.contains("time") && json["time"].isString()) {
        valueOfItem.timeArrival.fromString(json["time"].toString(), dateFormat);
    }

    if (json.contains("data") && json["data"].isArray()) {
        const QJsonArray &dataArray = json["data"].toArray();

        if (dataArray.isEmpty()) {
            qDebug() << "DSPDataHandler::parseDSPFile - No data array in file";
            return;
        }

        for (quint16 dataIndex = 0; dataIndex != dataArray.size(); dataIndex++) {
            const QJsonObject &dataObject = dataArray[dataIndex].toObject();

            DSPData dataInfo;
            if (dataObject.contains("N") && dataObject["N"].isDouble()) {
                dataInfo.N = dataObject["N"].toInt();
            }
            if (dataObject.contains("M") && dataObject["M"].isDouble()) {
                dataInfo.M = dataObject["M"].toInt();
            }
            if (dataObject.contains("az") && dataObject["az"].isDouble()) {
                dataInfo.azm = dataObject["az"].toDouble();
            }
            if (dataObject.contains("ugm") && dataObject["ugm"].isDouble()) {
                dataInfo.ugm = dataObject["ugm"].toDouble();
            }

            valueOfItem.vectorOfData.push_back(dataInfo);
            auto &ampVector = valueOfItem.vectorOfData.last();

            if (dataObject.contains("amp") && dataObject["amp"].isArray()) {
                const QJsonArray &ampArray = dataObject["amp"].toArray();

                for (quint32 ampIndex = 0; ampIndex != ampArray.size(); ampIndex++) {
                    if (dataInfo.M == 1) {
                        ampVector.dataGL.push_back(ampArray.at(ampIndex).toDouble());
                    }
                    else if (dataInfo.M == 280) {
                        ampVector.data.push_back(ampArray.at(ampIndex).toDouble());
                    }
                }
            }
        }
    }

    if (valueOfItem.type == DSPType::DSP20) {
        connect(dspInfo.plotterWidget, &CustomPlotterWidget::setPositionOnVectorOfDSP, this, &DSPDataHandler::setPositionOnVectorOfDSPSlot);

        auto &itemOfDSP = valueOfItem.vectorOfData.first();
        valueOfItem.plotterWidget->updateData(itemOfDSP.N, itemOfDSP.M, 0, itemOfDSP.data);
        valueOfItem.plotterWidget->show();
    }
}

void DSPDataHandler::dspMessageHandler(RLSODSPDataMessage msg)
{
    auto itemOfMap = mapOfDSPData.find(msg.id);
    if (itemOfMap != mapOfDSPData.end()) {

        float az_ant = msg.azm_ray - 45.,
              ugm_ant = msg.ugm_ray - 45.;

        Coor3 coor = Polar2Coor3(Polar(1., msg.azm, msg.ugm));
        Coor3 Coor = ChangeSistemCoor_L2G_AzUm_Fast(coor, az_ant, ugm_ant);
        Polar realAngles = Coor2Polar(Coor);

        const quint32 matrixSize = 2 * msg.M * msg.N;

        if (msg.M == 1) {
            DSPData data(msg.N, msg.M,
                         realAngles.Az,
                         realAngles.Um);
            itemOfMap.value().vectorOfData.push_back(data);
            auto &vector = itemOfMap.value().vectorOfData.last().dataGL;
            for (quint32 index = 0; index != matrixSize; index += 2) {
                float result = moduleOfComplexValue(msg.data[index],
                                                    msg.data[index + 1]);
                result = 20 * log10(result);
                vector.push_back(result);
            }
            if (itemOfMap.value().vectorOfData.size() % 10 == 0 && !itemOfMap.value().vectorOfData.isEmpty()) {
                const auto iterOfPack = itemOfMap.value().vectorOfData.end() - 11;
                QSharedPointer< QVector<DSPData> > sharedDSPPack(QSharedPointer< QVector<DSPData> >::create());
                for (quint16 index = 0; index != 10; index++) {
                    sharedDSPPack.data()->push_back(*iterOfPack);
                }
                emit dspPackToScene(itemOfMap.key(), sharedDSPPack);
            }
        }
        else if (msg.M == 280) {
            auto itemOfIndexes = itemOfMap.value().mapOfIndexes.find(msg.counter);
            if (itemOfIndexes == itemOfMap.value().mapOfIndexes.end()) {
                itemOfIndexes = itemOfMap.value().mapOfIndexes.insert(msg.counter,
                                                                      IndexedData((quint8)msg.part, matrixSize));
                itemOfIndexes.value().dataFromMessage.azm = realAngles.Az;
                itemOfIndexes.value().dataFromMessage.ugm = realAngles.Um;
                itemOfIndexes.value().dataFromMessage.N = msg.N;
                itemOfIndexes.value().dataFromMessage.M = msg.M;
            }
            else {
                itemOfIndexes.value().setOfIndexes.insert(msg.part);
            }
            const quint32 partOfMatrixSize = 2 * msg.M * msg.N / maxPartOfData;
            const quint32 startIndex = partOfMatrixSize * msg.part;
            for (quint32 index = 0; index != partOfMatrixSize; index++) {
                itemOfIndexes.value().completeData.replace(startIndex + index, msg.data[index]);
            }

            if (itemOfIndexes.value().setOfIndexes.size() == maxPartOfData) {
                emit dataReadyForProcessing(itemOfMap.key(),
                                            itemOfIndexes.key(),
                                            itemOfIndexes.value().dataFromMessage.N,
                                            itemOfIndexes.value().completeData);
            }
        }
    }
    else {
        qDebug() << "DSPDataHandler::dspMessageHandler - Unknown targetID";
    }
}


void DSPDataHandler::prepareDSPInfo(qint32 targetID, DSPType type, bool isPlotting)
{
    auto itemOfMap = mapOfDSPData.find(targetID);
    DSPType lastType = DSPType::None;
    if (itemOfMap != mapOfDSPData.end()) {
        lastType = itemOfMap.value().type;
        if (!isPlotting || lastType != type) {
            itemOfMap.value().plotterWidget->hide();
            if (itemOfMap.value().type == DSPType::DSP20)
                disconnect(itemOfMap.value().plotterWidget, &CustomPlotterWidget::setPositionOnVectorOfDSP, this, &DSPDataHandler::setPositionOnVectorOfDSPSlot);
            else {
                disconnect(itemOfMap.value().plotterWidget, &CustomPlotterWidget::sendColorRangesToScene,
                           this, &DSPDataHandler::sendColorRangesOnSceneRepeaterSlot);
                emit deleteDSPFromScene(targetID);
            }
            delete itemOfMap.value().plotterWidget;
            saveDataOnDisk(itemOfMap);
            mapOfDSPData.erase(itemOfMap);
            emit dspChanged(targetID, isPlotting);
        }
    }

    if (isPlotting || (lastType != type && lastType != DSPType::None)) {
        DSPDataInfo info;
        info.timeArrival = QDateTime::currentDateTime();
        info.type = type;
        if (type == DSPType::DSP20) {
            info.plotterWidget = new CustomPlotterWidget(targetID, true);
            connect(info.plotterWidget, &CustomPlotterWidget::setPositionOnVectorOfDSP,
                    this,
                    &DSPDataHandler::setPositionOnVectorOfDSPSlot);
        }
        else {
            info.plotterWidget = new CustomPlotterWidget(targetID, false);
            connect(info.plotterWidget, &CustomPlotterWidget::sendColorRangesToScene,
                    this, &DSPDataHandler::sendColorRangesOnSceneRepeaterSlot);
            info.plotterWidget->forceSendColorRangesToScene();
        }
        mapOfDSPData.insert(targetID, info);
        emit dspChanged(targetID, isPlotting);
    }

}

void DSPDataHandler::setData(qint32 targetID, quint32 counter, VectorOfAmp vector)
{
    auto itemOfMap = mapOfDSPData.find(targetID);
    if (itemOfMap != mapOfDSPData.end()) {
        auto itemOfIndexMap = itemOfMap.value().mapOfIndexes.find(counter);
        if (itemOfIndexMap != itemOfMap.value().mapOfIndexes.end()) {
            DSPData data(itemOfIndexMap.value().dataFromMessage.N,
                         itemOfIndexMap.value().dataFromMessage.M,
                         itemOfIndexMap.value().dataFromMessage.azm,
                         itemOfIndexMap.value().dataFromMessage.ugm);
            itemOfMap.value().vectorOfData.push_back(data);
            auto &itemOfVector = itemOfMap.value().vectorOfData.last();
            itemOfVector.data.swap(vector);

            itemOfMap.value().mapOfIndexes.erase(itemOfIndexMap);

            itemOfMap.value().plotterWidget->updateData(itemOfVector.N,itemOfVector.M,
                                                        itemOfMap.value().vectorOfData.size(),
                                                        itemOfVector.data);
        }
        else {
            qDebug() << "DSPDataHandler::setData - Cant find index";
        }
    }
    else {
        qDebug() << "DSPDataHandler::setData - Cant find target in map";
    }
}

void DSPDataHandler::showPlot(qint32 targetID)
{
    auto itemOfMap = mapOfDSPData.find(targetID);
    if (itemOfMap != mapOfDSPData.end()) {
        if (itemOfMap.value().plotterWidget->isHidden()) {
            itemOfMap.value().plotterWidget->show();
        }
    }
    else {
        qDebug() << "DSPDataHandler::showPlot - Cant find target in map";
    }
}

void DSPDataHandler::setPositionOnVectorOfDSPSlot(const qint32 target, quint32 pos)
{
    auto itemOfMap = mapOfDSPData.find(target);
    if (itemOfMap != mapOfDSPData.end()) {
        if (pos < itemOfMap.value().vectorOfData.size()){
            auto &dspData = itemOfMap.value().vectorOfData.at(pos);
            itemOfMap.value().plotterWidget->updateData(dspData.N, dspData.M,
                                                        itemOfMap.value().vectorOfData.size(),
                                                        dspData.data);
        }
    }
    else {
        qDebug() << "DSPDataHandler::setPositionOnVectorOfDSPSlot - Cant find target in map";
    }
}

void DSPDataHandler::setPositionOnVectorOfDSPPleerSlot(const qint32 target, quint32 pos)
{
    auto itemOfMap = mapOfDSPDataForPleer.find(target);
    if (itemOfMap != mapOfDSPDataForPleer.end()) {
        if (pos < itemOfMap.value().vectorOfData.size()){
            auto &dspData = itemOfMap.value().vectorOfData.at(pos);
            itemOfMap.value().plotterWidget->updateData(dspData.N, dspData.M,
                                                        itemOfMap.value().vectorOfData.size(),
                                                        dspData.data);
        }
    }
    else {
        qDebug() << "DSPDataHandler::setPositionOnVectorOfDSPPleerSlot - Cant find target in map";
    }
}

void DSPDataHandler::sendColorRangesOnSceneRepeaterSlot(const qint32 target, const ColorRanges colorRanges)
{
    emit sendColorRangesOnSceneRepeaterSignal(target, colorRanges);
}

float DSPDataHandler::moduleOfComplexValue(qint16 &real, qint16 &imag)
{
    return sqrt(pow(real, 2) + pow(imag, 2));
}

void DSPDataHandler::saveDataOnDisk(QMap<qint32, DSPDataInfo>::iterator currentItem)
{
    QJsonObject saveState;

    saveState["time"] = currentItem.value().timeArrival.toString(dateFormat);
    saveState["type"] = currentItem.value().type == DSPType::DSP2 ? TableAttributes::dsp2Str : TableAttributes::dsp20Str;
    saveState["target"] = currentItem.key();

    QJsonArray dspDataArray;
    for (auto iterOfHeader = currentItem.value().vectorOfData.begin();
            iterOfHeader != currentItem.value().vectorOfData.end();
            iterOfHeader++) {
        QJsonObject dataHeaderObject;
        dataHeaderObject["N"] = static_cast<int>(iterOfHeader->N);
        dataHeaderObject["M"] = static_cast<int>(iterOfHeader->M);
        dataHeaderObject["az"] = iterOfHeader->azm;
        dataHeaderObject["ugm"] = iterOfHeader->ugm;

        QJsonArray dataMainArray;
        for (auto iterOfData = iterOfHeader->data.begin();
                iterOfData != iterOfHeader->data.end();
                iterOfData++) {
            dataMainArray.push_back(*iterOfData);
        }
        dataHeaderObject["amp"] = dataMainArray;

        dspDataArray.push_back(dataHeaderObject);
    }

    saveState["data"] = dspDataArray;

    QJsonDocument settingDoc(saveState);
    QFile dataFile(dspDataPath + currentItem.value().timeArrival.toString(dateFormat) + extensionOfFiles);
    if (!dataFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "DSPDataHandler::saveDataOnDisk - Can't open dsp setting file";
        return;
    }
    dataFile.write(settingDoc.toJson());
    dataFile.flush();
    dataFile.close();
}

float FFTWProcessor::moduleOfComplexValue(qreal &real, qreal &imag)
{
    return sqrt(pow(real, 2) + pow(imag, 2));
}

FFTWProcessor::FFTWProcessor(QObject *parent) : QObject(parent)
{

}

FFTWProcessor::~FFTWProcessor()
{
    for (auto &item : mapOfFFTWInfo) {
        fftw_destroy_plan(item.fftwPlan);
        fftw_free(item.complexMatrix);
    }
}

void FFTWProcessor::doWork()
{

}

void FFTWProcessor::dspChangedSlot(qint32 targetID, bool isPlotting)
{
    auto itemOfMap = mapOfFFTWInfo.find(targetID);
    if (itemOfMap != mapOfFFTWInfo.end()) {
        if (!isPlotting) {
            fftw_destroy_plan(itemOfMap.value().fftwPlan);
            fftw_free(itemOfMap.value().complexMatrix);
            mapOfFFTWInfo.erase(itemOfMap);
        }
    }
    else {
        if (isPlotting) {
            FFTWInfo info;
            mapOfFFTWInfo.insert(targetID, info);
        }
    }
}

void FFTWProcessor::setPlane(qint32 targetID, quint32 N, quint32 M)
{
    const quint32 matrixSize = N * M;
    auto itemOfMap = mapOfFFTWInfo.find(targetID);
    if (itemOfMap != mapOfFFTWInfo.end()) {
        const quint32 lastMatrixSize = itemOfMap.value().m * itemOfMap.value().n;
        if (N != itemOfMap.value().n && matrixSize != lastMatrixSize) {
            fftw_destroy_plan(itemOfMap.value().fftwPlan);
            fftw_free(itemOfMap.value().complexMatrix);

            itemOfMap.value().complexMatrix = fftw_alloc_complex(matrixSize);
            itemOfMap.value().fftwPlan = fftw_plan_dft_2d(N, M,
                                                          itemOfMap.value().complexMatrix, itemOfMap.value().complexMatrix,
                                                          FFTW_FORWARD, FFTW_ESTIMATE);
            itemOfMap.value().n = N;
            itemOfMap.value().m = M;
        }
    }

}

void FFTWProcessor::newDataForWork(qint32 targetID, quint32 counter, quint32 N, VectorRawData matrix)
{
    auto itemOfMap = mapOfFFTWInfo.find(targetID);
    if (itemOfMap != mapOfFFTWInfo.end()) {
        const quint32 lastMatrixSize = itemOfMap.value().m * itemOfMap.value().n;

        if (N != itemOfMap.value().n && matrix.size() != (2 * lastMatrixSize)) {
            setPlane(targetID, N, (matrix.size() / (2 * N)));
        }

        currentCounter = counter;

        for (quint32 index = 0; index != matrix.size(); index++) {
            quint32 fftMatrixIndex = index / 2;
            itemOfMap.value().complexMatrix[fftMatrixIndex][0] = matrix.at(index++);
            itemOfMap.value().complexMatrix[fftMatrixIndex][1] = matrix.at(index);
        }

        fftw_execute(itemOfMap.value().fftwPlan);

        resultMatrix.clear();
        const quint32 matrixSize = matrix.size() / 2;
        for (quint32 index = 0; index != matrixSize; index++) {
            float result = moduleOfComplexValue(itemOfMap.value().complexMatrix[index][0],
                                                itemOfMap.value().complexMatrix[index][1]);
            result = 20 * log10(result);
            resultMatrix.push_back(result);
        }

        emit processedData(targetID, currentCounter, resultMatrix);
    }
}
