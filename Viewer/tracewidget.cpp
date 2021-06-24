#include "tracewidget.h"
#include <QList>
#include <QListView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QBoxLayout>
#include <QGroupBox>
#include <QMenu>
#include <QComboBox>
#include <QCheckBox>
#include <QScrollBar>

TrackWidget::TrackWidget(QWidget *parent) : BaseWidget(WidgetTypes::Track, parent),
    ctCounter(0), plottingCounter(0), traceCounter(0), dspCounter(0),
    ctLimit(2), plottingLimit(2), traceLimit(10), dspLimit(10),
    forcedBanOnPlottingDSP(false)
{
    setTitle("Трассы");

    listView = new QListView();
    QStandardItemModel *modelForTable = new QStandardItemModel();

    listView->setModel(modelForTable);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    listView->setSelectionBehavior(QAbstractItemView::SelectItems);
    listView->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setUniformItemSizes(true);
    listView->setFixedHeight(200);

    QVBoxLayout *trackMainLayout = new QVBoxLayout();
    trackMainLayout->addWidget(listView);

    QGroupBox *trackGroupBox = new QGroupBox("Набор трасс");
    trackGroupBox->setLayout(trackMainLayout);

    //QLabel *specialSectorLabel = new QLabel("Потеря трассы");
    specialSectorSwitchingCheckBox = new QCheckBox("Поиск трассы после потери");
    //specialSectorSwitchingCheckBox->setLayoutDirection(Qt::RightToLeft);
    specialSectorPriorityCheckBox = new QCheckBox("Высокий приоритет поиска");
    //specialSectorPriorityCheckBox->setLayoutDirection(Qt::RightToLeft);
    QLabel *specialSectorTimeToResetLabel = new QLabel("Время поиска (сек)");
    specialSectorTimeLineEdit = new BaseLineEdit(0, 255, 0);
    specialSectorTimeLineEdit->setText("0");
    specialSectorGlobalButton = new QPushButton("Глобально");
    specialSectorTimeLineEdit->setEnabled(false);
    specialSectorPriorityCheckBox->setEnabled(false);

    QHBoxLayout *specialSectorTimeLayout = new QHBoxLayout();
    specialSectorTimeLayout->addWidget(specialSectorTimeToResetLabel);
    specialSectorTimeLayout->addWidget(specialSectorTimeLineEdit);
    specialSectorTimeLayout->addStretch(1);

    QVBoxLayout *specialSectorBodyLayout = new QVBoxLayout();
    specialSectorBodyLayout->setContentsMargins(margin);
    specialSectorBodyLayout->addWidget(specialSectorSwitchingCheckBox);
    specialSectorBodyLayout->addWidget(specialSectorPriorityCheckBox);
    specialSectorBodyLayout->addLayout(specialSectorTimeLayout);
    specialSectorBodyLayout->addWidget(specialSectorGlobalButton, 0, Qt::AlignRight);
    specialSectorBodyLayout->addStretch(1);

    /*QVBoxLayout *specialSectorLayout = new QVBoxLayout();
    specialSectorLayout->addWidget(specialSectorLabel);
    specialSectorLayout->addLayout(specialSectorBodyLayout);*/

    specialSectorGroupBox = new QGroupBox("Потеря трассы");
    specialSectorGroupBox->setStyleSheet(groupBoxCSS);
    specialSectorGroupBox->setLayout(specialSectorBodyLayout);

    QStringList list;
    //QLabel *priorityLabel = new QLabel("Приоритет");
    priorityCb = new QComboBox();
    list << TableAttributes::normalPriorityStr << TableAttributes::hightPriorityStr;
    priorityCb->addItems(list);
    list.clear();

    /*QHBoxLayout *priorityHeaderLayout = new QHBoxLayout();
    priorityHeaderLayout->addWidget(priorityLabel);
    priorityHeaderLayout->addStretch(1);*/

    QVBoxLayout *priorityBodyLayout = new QVBoxLayout();
    priorityBodyLayout->setContentsMargins(margin);
    priorityBodyLayout->addWidget(priorityCb);
    priorityBodyLayout->addStretch(1);

    /*QVBoxLayout *priorityLayout = new QVBoxLayout(); //####################
    priorityLayout->addWidget(priorityLabel);
    //priorityLayout->addLayout(priorityHeaderLayout);
    priorityLayout->addLayout(priorityBodyLayout);*/


    QGroupBox *priorityGroupBox = new QGroupBox("Приоритет");
    priorityGroupBox->setStyleSheet(groupBoxCSS);
    priorityGroupBox->setLayout(priorityBodyLayout);


    //QLabel *workModeLabel = new QLabel("Режим работы");
    workModeCb = new QComboBox();
    list << TableAttributes::reflSignal << TableAttributes::respSignal << TableAttributes::reflRespSignal;
    workModeCb->addItems(list);
    list.clear();

    QVBoxLayout *workModeBodyLayout = new QVBoxLayout();
    workModeBodyLayout->setContentsMargins(margin);
    workModeBodyLayout->addWidget(workModeCb);
    workModeBodyLayout->addStretch(1);

    /*QVBoxLayout *workModeLayout = new QVBoxLayout(); //####################
    workModeLayout->addWidget(workModeLabel);
    workModeLayout->addLayout(workModeBodyLayout);*/

    QGroupBox *workModeGroupBox = new QGroupBox("Режим работы");
    workModeGroupBox->setStyleSheet(groupBoxCSS);
    workModeGroupBox->setLayout(workModeBodyLayout);

    //QLabel *dspModeLabel = new QLabel("Режим ДСП");
    dspModeCb = new QComboBox();
    list << TableAttributes::offStr << TableAttributes::dsp2Str << TableAttributes::dsp20Str;
    dspModeCb->addItems(list);
    list.clear();
    plottingDSPCheckBox = new QCheckBox("Отображение ДСП");
    plottingDSPButton = new QPushButton("График");
    plottingDSPButton->setCheckable(true);
    plottingDSPButton->setEnabled(false);
    plottingDSPCheckBox->setEnabled(false);

    QVBoxLayout *dspModeBodyLayout = new QVBoxLayout();
    dspModeBodyLayout->setContentsMargins(margin);
    dspModeBodyLayout->addWidget(dspModeCb);
    dspModeBodyLayout->addWidget(plottingDSPCheckBox);
    //dspModeBodyLayout->addWidget(plottingDSPButton,0, Qt::AlignRight);
    dspModeBodyLayout->addStretch(1);

    /*QVBoxLayout *dspModeLayout = new QVBoxLayout(); //####################
    dspModeLayout->addWidget(dspModeLabel);
    dspModeLayout->addLayout(dspModeBodyLayout);*/

    dspModeGroupBox = new QGroupBox("Режим ДСП");
    dspModeGroupBox->setStyleSheet(groupBoxCSS);
    dspModeGroupBox->setLayout(dspModeBodyLayout);

    ctAddButton = new QPushButton("Добавить трассу");
    ctAddButton->setCheckable(true);
    //QLabel *ctLabel = new QLabel("Сближение целей");

    QVBoxLayout *ctBodyLayout = new QVBoxLayout();
    ctBodyLayout->setContentsMargins(margin);
    ctBodyLayout->addWidget(ctAddButton,0, Qt::AlignRight);
    ctBodyLayout->addStretch(1);

    /*QVBoxLayout *ctLayout = new QVBoxLayout(); //####################
    ctLayout->addWidget(ctLabel);
    ctLayout->addLayout(ctBodyLayout);*/

    QGroupBox *ctGroupBox = new QGroupBox("Сближение целей");
    ctGroupBox->setStyleSheet(groupBoxCSS);
    ctGroupBox->setLayout(ctBodyLayout);

    QSet<QString> requestSignal({"1","2"}),
            codeDistance({"53","85"}),
            responseSignal({"080", "105", "160", "190", "225", "250"});
    for (auto &firstItem : requestSignal) {
        for (auto &secondItem : codeDistance) {
            for (auto &thirdItem : responseSignal) {
                QString str = firstItem + secondItem + thirdItem;
                list << str;
            }
        }
    }
    list << QString::number(1111111); // test LFM
    //QLabel *letterLabel = new QLabel("Литера");
    letterCb = new QComboBox();
    letterCb->addItems(list);
    letterCb->setEnabled(false);
    list.clear();

    QVBoxLayout *letterBodyLayout = new QVBoxLayout();
    letterBodyLayout->setContentsMargins(margin);
    letterBodyLayout->addWidget(letterCb);
    letterBodyLayout->addStretch(1);

    /*QVBoxLayout *letterLayout = new QVBoxLayout(); //####################
    letterLayout->addWidget(letterLabel);
    letterLayout->addLayout(letterBodyLayout);*/

    QGroupBox *letterGroupBox = new QGroupBox("Литера");
    letterGroupBox->setStyleSheet(groupBoxCSS);
    letterGroupBox->setLayout(letterBodyLayout);

    acceptButton = new QPushButton("Применить");
    resetButton = new QPushButton("Сбросить");

    QHBoxLayout *controlButtonLayout = new QHBoxLayout();
    controlButtonLayout->addStretch(1);
    controlButtonLayout->addWidget(acceptButton);
    controlButtonLayout->addWidget(resetButton);

    QVBoxLayout *localOptionsLayout = new QVBoxLayout();
    localOptionsLayout->setContentsMargins(0,0,0,0);
    //optionsLayout->addLayout(priorityLayout);
    localOptionsLayout->addWidget(priorityGroupBox);
    localOptionsLayout->addWidget(workModeGroupBox);
    localOptionsLayout->addWidget(dspModeGroupBox);
    localOptionsLayout->addWidget(ctGroupBox);
    localOptionsLayout->addWidget(letterGroupBox);

    localOptionsWidget = new QWidget();
    localOptionsWidget->setLayout(localOptionsLayout);

    QVBoxLayout *optionsLayout = new  QVBoxLayout();
    optionsLayout->setContentsMargins(margin);
    optionsLayout->addWidget(localOptionsWidget);
    optionsLayout->addWidget(specialSectorGroupBox);
    optionsLayout->addLayout(controlButtonLayout);

    optionsGroupBox = new QGroupBox("Параметры");
    optionsGroupBox->setLayout(optionsLayout);

    localOptionsWidget->setEnabled(false);
    acceptButton->setEnabled(false);
    resetButton->setEnabled(false);

    QVBoxLayout *mainLayout = new  QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));    
    mainLayout->addWidget(trackGroupBox);
    mainLayout->addWidget(optionsGroupBox);    

    setLayout(mainLayout);

    connect(listView, &QListView::clicked, this, &TrackWidget::listViewItemClicked);
    connect(workModeCb, QOverload<int>::of(&QComboBox::activated), this, &TrackWidget::currentModeChanged);
    connect(dspModeCb, QOverload<int>::of(&QComboBox::activated), this, &TrackWidget::currentDSPChanged);
    connect(specialSectorSwitchingCheckBox, &QCheckBox::stateChanged, this, &TrackWidget::specialSectorSettingSwitching);
    connect(acceptButton, &QPushButton::released, this, &TrackWidget::acceptEffect);
    connect(resetButton, &QPushButton::released, this, &TrackWidget::clearEffect);
    connect(specialSectorGlobalButton, &QPushButton::released, this, &TrackWidget::specialSectorGlobalAccept);    
}

void TrackWidget::listViewItemClicked(const QModelIndex &index) {    
    localOptionsWidget->setEnabled(true);
    acceptButton->setEnabled(true);
    resetButton->setEnabled(true);

    qint32 traceId = idFromString(index.data().toString());
    if (traceId == -1) {
        qDebug() << "TrackWidget::listViewItemClicked - Track not found in string";
        return;
    }

    auto itemOfTrackMap = mapOfTrack.find(traceId);
    if (itemOfTrackMap != mapOfTrack.end()) {
        if (itemOfTrackMap.value().isPriority) {
            priorityCb->setCurrentIndex(priorityCb->findText(TableAttributes::hightPriorityStr));
        }
        else {
            priorityCb->setCurrentIndex(priorityCb->findText(TableAttributes::normalPriorityStr));
        }

        if (itemOfTrackMap.value().workMode == TargetWorkMode::ReflectedSignal) {
            workModeCb->setCurrentIndex(workModeCb->findText(TableAttributes::reflSignal));
        }
        else if (itemOfTrackMap.value().workMode == TargetWorkMode::ResponseSignal) {
            workModeCb->setCurrentIndex(workModeCb->findText(TableAttributes::respSignal));
        }
        else if (itemOfTrackMap.value().workMode == TargetWorkMode::ReflectedAndResponse) {
            workModeCb->setCurrentIndex(workModeCb->findText(TableAttributes::reflRespSignal));
        }
        if (itemOfTrackMap.value().dspType == DSPType::DSP2) {
            dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::dsp2Str));
        }
        else if (itemOfTrackMap.value().dspType == DSPType::DSP20){
            dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::dsp20Str));
        }
        else {
            dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::offStr));
        }
        if (itemOfTrackMap.value().dspType != DSPType::None) {
            if (itemOfTrackMap.value().isPlotting) {
                plottingDSPCheckBox->setEnabled(true);
            }
            else {
                if (forcedBanOnPlottingDSP) {
                    plottingDSPCheckBox->setEnabled(false);
                }
            }
            plottingDSPCheckBox->setChecked(itemOfTrackMap.value().isPlotting);
        }
        else {
            plottingDSPCheckBox->setEnabled(false);
        }
        //plottingDSPCheckBox->setChecked(itemOfTrackMap.value().isPlotting);
        ctAddButton->setChecked(itemOfTrackMap.value().isConvergingTargets);
        letterCb->setCurrentIndex(letterCb->findText(QString::number(itemOfTrackMap.value().letter)));
        specialSectorSwitchingCheckBox->setChecked(itemOfTrackMap.value().becomeSpecialSector);
        specialSectorPriorityCheckBox->setChecked(itemOfTrackMap.value().isSpecialSectorPriority);
        specialSectorTimeLineEdit->setText(QString::number(itemOfTrackMap.value().timeToResetSpecialSector));

        emit isDSPAvailableSignal();
    }
    else {
        qDebug() << "TrackWidget::listViewItemClicked - Track not found in map";
    }
}

void TrackWidget::currentModeChanged(int )
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    QString str = cb->currentText();
    if (str == TableAttributes::reflRespSignal) {
        dspModeGroupBox->setEnabled(false);
        letterCb->setEnabled(true);
    }
    else {
        if (str == TableAttributes::reflSignal) {
            letterCb->setEnabled(false);
        }
        else if (str == TableAttributes::respSignal) {
            letterCb->setEnabled(true);
        }
        dspModeGroupBox->setEnabled(true);
    }
}

void TrackWidget::currentDSPChanged(int )
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    QString str = cb->currentText();
    if (str == TableAttributes::offStr) {
        plottingDSPButton->setEnabled(false);
        plottingDSPButton->setChecked(false);
        plottingDSPCheckBox->setEnabled(false);
        plottingDSPCheckBox->setChecked(false);
    }
    else {
        if (!forcedBanOnPlottingDSP)
            plottingDSPCheckBox->setEnabled(true);
//        plottingDSPButton->setEnabled(true);
//        plottingDSPCheckBox->setEnabled(true);
    }
}

void TrackWidget::specialSectorSettingSwitching(int state)
{
    if (state == Qt::Checked) {
        specialSectorTimeLineEdit->setEnabled(true);
        specialSectorPriorityCheckBox->setEnabled(true);
    }
    else if (state == Qt::Unchecked) {
        specialSectorTimeLineEdit->setEnabled(false);
        specialSectorPriorityCheckBox->setEnabled(false);
    }
}

void TrackWidget::acceptEffect()
{
    auto currentModelIndex = listView->currentIndex();
    qint32 traceId = idFromString(currentModelIndex.data().toString());
    if (traceId == -1) {
        qDebug() << "TrackWidget::acceptEffect - Track not found in string";
        return;
    }

    auto traceItem = mapOfTrack.find(traceId);
    if (traceItem != mapOfTrack.end()) {
        QString dataIntoTable = QString("Трасса №%1 ").arg(traceId);
        TrackInfo trackInfo;
        trackInfo.isPriority = priorityCb->currentText() == TableAttributes::normalPriorityStr ? false : true;
        if (trackInfo.isPriority)
            dataIntoTable += QString(" - Приор");
        if (workModeCb->currentText() == TableAttributes::reflSignal) {
            if (dspModeCb->currentText() == TableAttributes::offStr)
                trackInfo.workMode = TargetWorkMode::ReflectedSignal;
            else
                trackInfo.workMode = TargetWorkMode::ReflectedAndDSP;
            dataIntoTable += QString(" - ОТР");
        }
        else if (workModeCb->currentText() == TableAttributes::respSignal) {
            if (dspModeCb->currentText() == TableAttributes::offStr)
                trackInfo.workMode = TargetWorkMode::ResponseSignal;
            else
                trackInfo.workMode = TargetWorkMode::ResponseAndDSP;
            dataIntoTable += QString(" - ОТВ");
        }
        else if (workModeCb->currentText() == TableAttributes::reflRespSignal) {
            trackInfo.workMode = TargetWorkMode::ReflectedAndResponse;
            dataIntoTable += QString(" - ОТР и ОТВ");
        }
        if (dspModeCb->currentText() != TableAttributes::offStr) {
            trackInfo.dspType = dspModeCb->currentText() == TableAttributes::dsp20Str ? DSPType::DSP20 : DSPType::DSP2;
            trackInfo.isPlotting = plottingDSPCheckBox->isChecked();
            dataIntoTable += QString(" - ДСП");
        }
        else {
            trackInfo.dspType = DSPType::None;
        }

        trackInfo.isConvergingTargets = ctAddButton->isChecked();

        if (workModeCb->currentText() != TableAttributes::reflSignal) {
            trackInfo.letter = letterCb->currentText().toInt();
        }
        if (trackInfo.becomeSpecialSector) {
            trackInfo.becomeSpecialSector = specialSectorSwitchingCheckBox->isChecked();
            trackInfo.isSpecialSectorPriority = specialSectorPriorityCheckBox->isChecked();
            trackInfo.timeToResetSpecialSector = specialSectorTimeLineEdit->text().toInt();
            dataIntoTable += QString(" - СпецС");
        }

        traceItem.value() = trackInfo;

        QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(listView->model());
        sModel->item(currentModelIndex.row())->setData(dataIntoTable, Qt::DisplayRole);

        generateMessageToVOI(traceId, trackInfo);

        //if (trackInfo.dspType != DSPType::None) {
            emit insertDSP(traceId, trackInfo.dspType, trackInfo.isPlotting);
        //}

    }
    else {
        qDebug() << "TrackWidget::acceptEffect() - Cant find traceID in map";
    }
}

void TrackWidget::clearEffect()
{
    listView->clearSelection();
    priorityCb->setCurrentIndex(-1);
    workModeCb->setCurrentIndex(-1);
    dspModeCb->setCurrentIndex(-1);
    letterCb->setCurrentIndex(-1);

    plottingDSPCheckBox->setChecked(false);
    specialSectorSwitchingCheckBox->setChecked(false);
    specialSectorPriorityCheckBox->setChecked(false);

    plottingDSPButton->setChecked(false);
    ctAddButton->setChecked(false);
    specialSectorTimeLineEdit->setText("15");
}

void TrackWidget::specialSectorGlobalAccept()
{
    RMOTrackSetting msg;
    msg.aimID = -1;
    msg.spec_sectors_on = specialSectorSwitchingCheckBox->isChecked();
    msg.priority_spec_sectors = specialSectorPriorityCheckBox->isChecked();
    msg.time_searching_in_spec_sector = specialSectorTimeLineEdit->text().toInt();

    QByteArray arr;

    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << qint16(0);
    out << quint8(RMO_VOI_TRACK_SETTING_MESSAGE);
    out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));

    emit msgToVOI(arr);
    qDebug() << "TrackWidget::acceptEffect() - GLOBAL RMO_VOI_TRACK_SETTING_MESSAGE";
}

void TrackWidget::addTraceMark(RLSOaimMessage msg)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
    int selectedRow = 0;

    QList<QStandardItem *> modelSearchingList(model->findItems(QString("№%1").arg(msg.trackID), Qt::MatchContains));

    if (modelSearchingList.isEmpty()) {
        selectedRow = model->rowCount();

        TrackInfo tInfo;
        auto itemOfMap = mapOfTrack.find(msg.trackID);
        if (itemOfMap != mapOfTrack.end()) {
            tInfo = itemOfMap.value();
        }
        else {
            tInfo.workMode = (TargetWorkMode)msg.typeSignal;
        }

        tInfo.workModeVOI = (TargetWorkMode)msg.typeSignalNow;
        tInfo.msg = msg;
        tInfo.letter = msg.letter;

        mapOfTrack.insert(msg.trackID, tInfo);

        QString workModeStr;
        if (tInfo.workMode == TargetWorkMode::ReflectedSignal){
            workModeStr = " - ОТР";
        }
        else if (tInfo.workMode == TargetWorkMode::ResponseSignal){
            workModeStr = " - ОТВ";
        }
        else {
            workModeStr = " - ОТР и ОТВ";
        }

        QString dataIntoTable = QString("Трасса №%1 ").arg(msg.trackID) + workModeStr;
        QStandardItem *item = new QStandardItem;
        item->setData(dataIntoTable, Qt::DisplayRole);
        model->setItem(selectedRow, item);

        emit newTrack(msg.trackID);
    }
}

void TrackWidget::eraseOldTrace(quint32 idTrack)
{
    auto itemOfMap = mapOfTrack.find(idTrack);
    if (itemOfMap != mapOfTrack.end()) {

//        if (itemOfMap.value().drawTrace)
//            traceCounter--;

        mapOfTrack.erase(itemOfMap);

        emit eraseTrack(idTrack);

        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
        QList<QStandardItem *> modelSearchingList(model->findItems(QString("№%1").arg(idTrack), Qt::MatchContains));

        if (!modelSearchingList.isEmpty()) {
            if (listView->currentIndex().row() == modelSearchingList.at(0)->row()) {
                //listView->clearSelection();
                clearEffect();
            }
            model->removeRow(modelSearchingList.at(0)->row());
        }
    }
}

void TrackWidget::interactiveActionsWithTrack(quint32 id, ActionsWithTrack action)
{
    auto iterOfMapOfTrack = mapOfTrack.find(id);

    if (iterOfMapOfTrack == mapOfTrack.end()) {
        return;
    }

    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
    QList<QStandardItem *> modelSearchingList(model->findItems(QString("№%1").arg(id), Qt::MatchContains));

    if (modelSearchingList.isEmpty()) {
        return;
    }

    if (action == ActionsWithTrack::Delete) {

        DeleteTrackMessage msg;
        msg.aimID = id;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_11);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(RMO_VOI_TRACK_DELETE_MESSAGE);
        out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        emit msgToVOI(arr);
        qDebug() << "TCP Handler - RMO_VOI_TRACK_DELETE_MESSAGE";
    }
    else if (action == ActionsWithTrack::Priority) {

        iterOfMapOfTrack.value().isPriority = !iterOfMapOfTrack.value().isPriority;

        generateMessageToVOI(id, iterOfMapOfTrack.value());

        /*RMOTrackSetting msg;
        msg.aimID = id;
        msg.priority = iterOfMapOfTrack.value().isPriority;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_11);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(RMO_VOI_TRACK_SETTING_MESSAGE);
        out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        emit msgToVOI(arr);
        qDebug() << "TCP Handler - RMO_VOI_TRACK_PRIORITY_MESSAGE";*/

//        QStandardItem *currentItem(model->item(modelSearchingList.at(0)->row(), TableAttributes::Priority));
//        currentItem->setData(iterOfMapOfTrack.value().isPriority ? TableAttributes::hightPriorityStr : TableAttributes::normalPriorityStr, Qt::DisplayRole);
    }
    else if (action == ActionsWithTrack::Trace) {
        if (!iterOfMapOfTrack.value().drawTrace) {
            if (traceCounter == traceLimit) {
                return;
            }
            else {
                traceCounter++;
            }
        }
        else {
            traceCounter--;
        }
        iterOfMapOfTrack.value().drawTrace = !iterOfMapOfTrack.value().drawTrace;
        emit activeTrackDrawing(id, iterOfMapOfTrack.value().drawTrace);

//        QStandardItem *currentItem(model->item(modelSearchingList.at(0)->row(), TableAttributes::Trace));
//        currentItem->setData(iterOfMapOfTrack.value().drawTrace ? TableAttributes::onStr : TableAttributes::offStr, Qt::DisplayRole);
    }
    else if (action == ActionsWithTrack::Extend) {

        iterOfMapOfTrack.value().extendCounter++;

    }
    else if (action == ActionsWithTrack::Correction) {



    }
}

void TrackWidget::isDSPExceedingUsageLimit(bool resolutionToSwitchingOn, bool resolutionToPlottingOn)
{
    if (resolutionToSwitchingOn) {
        dspModeGroupBox->setEnabled(true);
    }
    else {
        if (dspModeCb->currentText() == TableAttributes::offStr)
            dspModeGroupBox->setEnabled(false);
        else
            dspModeGroupBox->setEnabled(true);
    }

    if (resolutionToPlottingOn) {
        forcedBanOnPlottingDSP = false;
        plottingDSPCheckBox->setEnabled(true);
    }
    else {
        forcedBanOnPlottingDSP = true;

        qint32 traceId = idFromString(listView->currentIndex().data().toString());
        if (traceId == -1) {
            qDebug() << "TrackWidget::isDSPExceedingUsageLimit - Track not found in string";
            return;
        }

        auto itemOfTrackMap = mapOfTrack.find(traceId);
        if (itemOfTrackMap != mapOfTrack.end()) {
            if (!itemOfTrackMap.value().isPlotting) {
                plottingDSPCheckBox->setChecked(false);
                plottingDSPCheckBox->setEnabled(false);
            }
            else {
                plottingDSPCheckBox->setEnabled(true);
            }
        }
    }
}

void TrackWidget::changeDSPSlot(qint32 trackID, DSPType type, bool isPlotting)
{
    if (trackID >= 0) {
        auto itemOfTrackMap = mapOfTrack.find(trackID);
        if (itemOfTrackMap != mapOfTrack.end()) {
            TrackInfo &info = itemOfTrackMap.value();
            info.dspType = type;
            info.isPlotting = isPlotting;

            quint32 currentID = idFromString(listView->selectionModel()->selectedIndexes().at(0).data().toString());

            QStandardItemModel *model = qobject_cast<QStandardItemModel *>(listView->model());
            QList<QStandardItem *> modelSearchingList(model->findItems(QString("№%1").arg(trackID), Qt::MatchContains));

            if (modelSearchingList.isEmpty()) {
                qDebug() << "TrackWidget::changeDSPSlot() - Cant find trackID in listView";
                return;
            }

            if (currentID != -1 && trackID == currentID) {
                if (info.dspType == DSPType::DSP2) {
                    dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::dsp2Str));
                }
                else if (info.dspType == DSPType::DSP20) {
                    dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::dsp20Str));
                }
                else if (info.dspType == DSPType::None) {
                    dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::offStr));
                }
                plottingDSPCheckBox->setChecked(info.isPlotting);
            }

            QString dataIntoTable = QString("Трасса №%1 ").arg(trackID);
            if (info.isPriority)
                dataIntoTable += QString(" - Приор");
            if (info.workMode == TargetWorkMode::ReflectedSignal
                || info.workMode == TargetWorkMode::ReflectedAndDSP) {
                dataIntoTable += QString(" - ОТР");
            }
            else if (info.workMode == TargetWorkMode::ResponseSignal
                     || info.workMode == TargetWorkMode::ResponseAndDSP) {
                dataIntoTable += QString(" - ОТВ");
            }
            else if (info.workMode == TargetWorkMode::ReflectedAndResponse) {
                dataIntoTable += QString(" - ОТР и ОТВ");
            }
            if (info.dspType != DSPType::None) {
                dataIntoTable += QString(" - ДСП");
            }
            if (info.becomeSpecialSector) {
                dataIntoTable += QString(" - СпецС");
            }

            modelSearchingList.at(0)->setData(dataIntoTable, Qt::DisplayRole);

            generateMessageToVOI(trackID, info);
        }
        else {
            qDebug() << "TrackWidget::changeDSPSlot() - Cant find trackID in map";
        }
    }
}

void TrackWidget::dataInModelChanged(QStandardItem *item)
{
    /*quint32 currentColumn = item->column();
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(tableView->model());
    quint32 idTrack = model->item(item->row(), TableAttributes::TrackID)->text().toInt();
    QString currentStr = item->data(Qt::DisplayRole).toString();
    //qDebug() << "TrackWidget::dataInModelChanged - " << currentStr;

    bool needToSend = false;

    auto mapItem = mapOfTrack.find(idTrack);
    if (mapItem != mapOfTrack.end()) {

        switch (currentColumn) {
        case TableAttributes::Priority : {
            if ((currentStr == TableAttributes::normalPriorityStr && mapItem.value().isPriority) ||
                    (currentStr == TableAttributes::hightPriorityStr && !mapItem.value().isPriority) ) {
                mapItem.value().isPriority = !mapItem.value().isPriority;
                needToSend = true;
            }
            break;
        }
        case TableAttributes::DSP : {
            if (currentStr == TableAttributes::offStr) {

                mapItem.value().dspType = DSPType::None;
            }
            else if (currentStr == TableAttributes::dsp2Str) {
                mapItem.value().dspType = DSPType::DSP2;
            }
            else if (currentStr == TableAttributes::dsp20Str) {
                mapItem.value().dspType = DSPType::DSP20;
            }
            needToSend = true;
            break;
        }
        case TableAttributes::CT : {
            if (currentStr == TableAttributes::onStr
                && !mapItem.value().isConvergingTargets) {

                if (ctCounter == ctLimit) {
                    item->setData(TableAttributes::offStr, Qt::DisplayRole);
                }
                else {
                    ctCounter++;
                    mapItem.value().isConvergingTargets = !mapItem.value().isConvergingTargets;
                    needToSend = true;
                }

            }
            else if (currentStr == TableAttributes::offStr
                     && mapItem.value().isConvergingTargets) {
                ctCounter--;
                mapItem.value().isConvergingTargets = !mapItem.value().isConvergingTargets;
                needToSend = true;

            }
            break;
        }
        case TableAttributes::Plotting : {
            if (currentStr == TableAttributes::onStr && !mapItem.value().isPlotting) {

                if (plottingCounter == plottingLimit) {
                    item->setData(TableAttributes::offStr, Qt::DisplayRole);
                }
                else {
                    plottingCounter++;
                    mapItem.value().isPlotting = !mapItem.value().isPlotting;
                    needToSend = true;
                }
            }
            else if (currentStr == TableAttributes::offStr && mapItem.value().isPlotting) {
                plottingCounter--;
                mapItem.value().isPlotting = !mapItem.value().isPlotting;
                needToSend = true;
            }
            break;
        }
        case TableAttributes::Trace : {
            if (currentStr == TableAttributes::onStr && !mapItem.value().drawTrace) {

                if (traceCounter == traceLimit) {
                    item->setData(TableAttributes::offStr, Qt::DisplayRole);
                    return;
                }
                else {
                    traceCounter++;
                    mapItem.value().drawTrace = !mapItem.value().drawTrace;
                    needToSend = true;
                }
            }
            else if (currentStr == TableAttributes::offStr && mapItem.value().drawTrace) {
                traceCounter--;
                mapItem.value().drawTrace = !mapItem.value().drawTrace;
                needToSend = true;
            }
            emit activeTrackDrawing(idTrack, mapItem.value().drawTrace);
            break;
        }
        }

        if (needToSend) {
            RMOTrackSetting msg;
            msg.aimID = mapItem.key();
            msg.priority = mapItem.value().isPriority;

            QByteArray arr;

            QDataStream out(&arr, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_11);
            out.setByteOrder(QDataStream::LittleEndian);
            out.setFloatingPointPrecision(QDataStream::SinglePrecision);

            out << qint16(0);
            out << quint8(RMO_VOI_TRACK_SETTING_MESSAGE);
            out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
            out.device()->seek(0);
            out << quint16(arr.size() - sizeof(quint16));

            emit msgToVOI(arr);
            qDebug() << "TCP Handler - RMO_VOI_TRACK_PRIORITY_MESSAGE";
        }
    }*/
}


void TrackWidget::initMenu()
{
    /*tableMenu = new QMenu();

    QAction *action = new QAction("Удалить трассу");
    connect(action, &QAction::triggered,
            [this] () {
        auto selectedList = tableView->selectionModel()->selectedRows();
        if (!selectedList.isEmpty())
            tableView->model()->removeRow(selectedList.first().row());
    });
    tableMenu->addAction(action);*/
}

qint32 TrackWidget::idFromString(QString strOnCurrentIndex)
{
    int traceIdInitEnteryOfString = strOnCurrentIndex.indexOf("№"),
            traceIdFinishEnteryOfString;
    if (traceIdInitEnteryOfString == -1) {
        qDebug() << "TrackWidget::idFromString - Bad format of string";
        return -1;
    }    
    traceIdFinishEnteryOfString = strOnCurrentIndex.indexOf(" ", traceIdInitEnteryOfString++);    
    if (traceIdFinishEnteryOfString == -1) {
        qDebug() << "TrackWidget::idFromString - Bad format of string";
        return -1;
    }
    return strOnCurrentIndex.mid(traceIdInitEnteryOfString, traceIdFinishEnteryOfString - traceIdInitEnteryOfString).toInt();
}

void TrackWidget::testGenAimMessage()
{
    static int id = 1;
    RLSOaimMessage msg;
    msg.trackID = id++;
    msg.typeSignal = 0;
    msg.typeSignalNow = 0;

    addTraceMark(msg);
}

void TrackWidget::generateMessageToVOI(quint32 trackID, TrackInfo &info)
{
    RMOTrackSetting msg;
    msg.aimID = trackID;
    msg.priority = info.isPriority;
    msg.work_mode = info.workMode;
    msg.DSP = info.dspType;
    msg.out_dsp = info.isPlotting;
    msg.type_answer = (info.letter > 1000000 ? 0 : 1);
    msg.letter = info.letter;
    msg.CT = info.isConvergingTargets;
    msg.spec_sectors_on = info.becomeSpecialSector;
    msg.priority_spec_sectors = info.isSpecialSectorPriority;
    msg.time_searching_in_spec_sector = info.timeToResetSpecialSector;

    QByteArray arr;

    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << qint16(0);
    out << quint8(RMO_VOI_TRACK_SETTING_MESSAGE);
    out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(msg));
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));

    emit msgToVOI(arr);
    qDebug() << "TrackWidget::generateMessageToVOI() - RMO_VOI_TRACK_SETTING_MESSAGE";
}

ComboBoxItemDelegate::ComboBoxItemDelegate(TableAttributes::ColumnName _type, QObject *parent)
    : QStyledItemDelegate(parent),
      type(_type)
{
}


ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}


QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (type == TableAttributes::TrackID) {
        QString str = index.data(Qt::DisplayRole).toString();
        QLabel *lbl = new QLabel((str.isEmpty() ? "" : str), parent);
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet("QLabel { background-color: rgba(50, 50, 50, 255);}");

        return lbl;
    }
    else if (type == TableAttributes::Priority ||
             type == TableAttributes::DSP ||
             type == TableAttributes::CT ||
             type == TableAttributes::Plotting ||
             type == TableAttributes::Trace ||
             type == TableAttributes::WorkMode){
        QComboBox *cb = new QComboBox(parent);
        cb->setStyleSheet("QComboBox { background-color: rgba(50, 50, 50, 255);}");
        QStringList list;
        if (type == TableAttributes::Priority)
            list << TableAttributes::normalPriorityStr << TableAttributes::hightPriorityStr;
        else if (type == TableAttributes::DSP)
            list << TableAttributes::offStr << TableAttributes::dsp20Str << TableAttributes::dsp2Str;
        else if (type == TableAttributes::WorkMode) {
            list << TableAttributes::reflSignal << TableAttributes::respSignal << TableAttributes::reflDSP
                 << TableAttributes::respDSP << TableAttributes::reflRespSignal;
        }
        else {
            list << TableAttributes::offStr << TableAttributes::onStr;
        }
        cb->addItems(list);
        connect(cb, QOverload<int>::of(&QComboBox::activated), this, &ComboBoxItemDelegate::cbResetData);
        connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ComboBoxItemDelegate::cbCommitData);
        return cb;
    }
}

void ComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (type == TableAttributes::TrackID) {
        QLabel *lbl = qobject_cast<QLabel *>(editor);
        Q_ASSERT(lbl);
        lbl->setText(index.data(Qt::DisplayRole).toString());
    }
    else /*if (type == TableAttributes::Priority ||
             type == TableAttributes::DSP ||
             type == TableAttributes::CT ||
             type == TableAttributes::Plotting ||
             type == TableAttributes::Trace)*/{
        QComboBox *cb = qobject_cast<QComboBox *>(editor);
        Q_ASSERT(cb);
        const QString currentText = index.data(Qt::DisplayRole).toString();
        const int cbIndex = cb->findText(currentText);
        if (cbIndex >= 0)
            cb->setCurrentIndex(cbIndex);
    }
    /*else if (type == TableAttributes::CT ||
             type == TableAttributes::Trace) {
        QCheckBox *chb = qobject_cast<QCheckBox *>(editor);
        Q_ASSERT(chb);
        const QString currentText = index.data(Qt::DisplayRole).toString();
        if (currentText == "Checked") {
            chb->setChecked(true);
        }
        else {
            chb->setChecked(false);
        }
    }*/
}

void ComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
    if (type == TableAttributes::TrackID) {
        /*QLabel *lbl = qobject_cast<QLabel *>(editor);
        Q_ASSERT(lbl);
        model->setData(index, lbl->text(), Qt::DisplayRole);*/
    }
    else /*if (type == TableAttributes::Priority ||
             type == TableAttributes::DSP ||
             type == TableAttributes::CT ||
             type == TableAttributes::Plotting ||
             type == TableAttributes::Trace)*/{
        QComboBox *cb = qobject_cast<QComboBox *>(editor);
        Q_ASSERT(cb);
//        if (type == TableAttributes::CT) {
//            static int counterCT = 0;
//            if (cb->currentText())
//        }
        model->setData(index, cb->currentText(), Qt::DisplayRole);
    }
    /*else if (type == TableAttributes::CT ||
             type == TableAttributes::Trace) {
        QCheckBox *chb = qobject_cast<QCheckBox *>(editor);
        Q_ASSERT(chb);
        model->setData(index, chb->isChecked() ? QString("Checked") : QString("Unchecked"), Qt::DisplayRole);
    }*/
}

void ComboBoxItemDelegate::cbCommitData(int index)
{
    Q_UNUSED(index)
    QComboBox *cb = qobject_cast<QComboBox *>(sender());
    Q_ASSERT(cb);
    emit commitData(cb);
    emit closeEditor(cb);
}

void ComboBoxItemDelegate::cbResetData(int index)
{
    Q_UNUSED(index)
    QComboBox *cb = qobject_cast<QComboBox *>(sender());
    Q_ASSERT(cb);
    emit closeEditor(cb);
}
