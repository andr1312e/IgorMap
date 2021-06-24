#include "tracewidget.h"
#include <QList>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QBoxLayout>
#include <QGroupBox>
#include <QMenu>
#include <QComboBox>
#include <QCheckBox>

TrackWidget::TrackWidget(QWidget *parent) : BaseWidget(WidgetTypes::Track, parent),
    ctCounter(0), plottingCounter(0), traceCounter(0), dspCounter(0),
    ctLimit(2), plottingLimit(2), traceLimit(10), dspLimit(10)
{
    setTitle("Трассы");
    QMargins margin(15,5,15,5);

    plotterWidget = new CustomPlotterWidget();
    plotterWidget->hide();

    tableView = new QTableView();
    QStringList hHeader;
    hHeader.append("Номер");
    hHeader.append("Приор");
    hHeader.append("Режим");
    hHeader.append("Литер");
    hHeader.append("ДСП");
    hHeader.append("СЦ");
    hHeader.append("Отрис");
    hHeader.append("Трек");

    QStandardItemModel *modelForTable = new QStandardItemModel();
    modelForTable->setHorizontalHeaderLabels(hHeader);

    tableView->setModel(modelForTable);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setMinimumWidth(40);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView->setTabKeyNavigation(true);
    //tableView->horizontalHeader()->setSectionsMovable(true);

    tableView->setItemDelegateForColumn(TableAttributes::TrackID,
                                        new ComboBoxItemDelegate(TableAttributes::TrackID));
    tableView->setItemDelegateForColumn(TableAttributes::Priority,
                                        new ComboBoxItemDelegate(TableAttributes::Priority));
    tableView->setItemDelegateForColumn(TableAttributes::WorkMode,
                                        new ComboBoxItemDelegate(TableAttributes::WorkMode));
    tableView->setItemDelegateForColumn(TableAttributes::DSP,
                                        new ComboBoxItemDelegate(TableAttributes::DSP));
    tableView->setItemDelegateForColumn(TableAttributes::CT,
                                        new ComboBoxItemDelegate(TableAttributes::CT));
    tableView->setItemDelegateForColumn(TableAttributes::Plotting,
                                        new ComboBoxItemDelegate(TableAttributes::Plotting));
    tableView->setItemDelegateForColumn(TableAttributes::Trace,
                                        new ComboBoxItemDelegate(TableAttributes::Trace));

    initMenu();
    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tableView, &QTableView::customContextMenuRequested, this, &TrackWidget::customMenuForTable);
    connect(qobject_cast<QStandardItemModel *>(tableView->model()),
            &QStandardItemModel::itemChanged,
            this,
            &TrackWidget::dataInModelChanged);

    QVBoxLayout *dspMainLayout = new QVBoxLayout();
    //dspMainLayout->addLayout(tableMainLayout);
    //dspMainLayout->addWidget(dspSettingGroupBox);
    dspMainLayout->addWidget(tableView);
    //dspMainLayout->addLayout(buttonLayout);

    QGroupBox *dspGroupBox = new QGroupBox("Управление работой по трассе");
    dspGroupBox->setLayout(dspMainLayout);

    QVBoxLayout *mainLayout = new  QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    //mainLayout->addLayout(comboBoxLayout);
    //mainLayout->addWidget(presetColorSchemeGroupBox);
    mainLayout->addWidget(dspGroupBox);
    //mainLayout->addWidget(plot);
    //mainLayout->addWidget(table);

    setLayout(mainLayout);
    addTraceMark(RLSOaimMessage());
}


void TrackWidget::customMenuForTable(QPoint pos)
{
    tableMenu->move(tableView->viewport()->mapToGlobal(pos));
    tableMenu->show();
}

void TrackWidget::addTraceMark(RLSOaimMessage msg)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(tableView->model());
    int selectedRow = 0;

    QList<QStandardItem *> modelSearchingList(model->findItems(QString("%1").arg(msg.trackID)));


    if (modelSearchingList.isEmpty()) {
        selectedRow = model->rowCount();

        QStandardItem *sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(QString("%1").arg(msg.trackID), Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::TrackID, sItem);

        sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(TableAttributes::normalPriorityStr, Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::Priority, sItem);

        sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(TableAttributes::reflSignal, Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::WorkMode, sItem);

        sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(TableAttributes::offStr, Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::DSP, sItem);

        sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(TableAttributes::offStr, Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::CT, sItem);

        sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(TableAttributes::offStr, Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::Plotting, sItem);

        sItem = new QStandardItem();
        sItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        sItem->setData(TableAttributes::offStr, Qt::DisplayRole);
        model->setItem(selectedRow, TableAttributes::Trace, sItem);

        TrackInfo tInfo;
        tInfo.msg = msg;

        mapOfTrack.insert(msg.trackID, tInfo);
    }
}

void TrackWidget::eraseOldTrace(quint32 idTrack)
{
    auto itemOfMap = mapOfTrack.find(idTrack);
    if (itemOfMap != mapOfTrack.end()) {
        if (itemOfMap.value().isConvergingTargets)
            ctCounter--;
        if (itemOfMap.value().isPlotting)
            plottingCounter--;
        mapOfTrack.erase(itemOfMap);


        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(tableView->model());
        QList<QStandardItem *> modelSearchingList(model->findItems(QString("%1").arg(idTrack)));

        if (!modelSearchingList.isEmpty()) {
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

    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(tableView->model());
    QList<QStandardItem *> modelSearchingList(model->findItems(QString("%1").arg(id)));

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

        RMOTrackSetting msg;
        msg.aimID = id;
        msg.priority = iterOfMapOfTrack.value().isPriority;
        //if (iterOfMapOfTrack.value().dspType)

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

        QStandardItem *currentItem(model->item(modelSearchingList.at(0)->row(), TableAttributes::Priority));
        currentItem->setData(iterOfMapOfTrack.value().isPriority ? TableAttributes::hightPriorityStr : TableAttributes::normalPriorityStr, Qt::DisplayRole);
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

        QStandardItem *currentItem(model->item(modelSearchingList.at(0)->row(), TableAttributes::Trace));
        currentItem->setData(iterOfMapOfTrack.value().drawTrace ? TableAttributes::onStr : TableAttributes::offStr, Qt::DisplayRole);
    }
    else if (action == ActionsWithTrack::Extend) {

        iterOfMapOfTrack.value().extendCounter++;

    }
    else if (action == ActionsWithTrack::Correction) {



    }
}


void TrackWidget::dataInModelChanged(QStandardItem *item)
{
    quint32 currentColumn = item->column();
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
    }
}


void TrackWidget::initMenu()
{
    tableMenu = new QMenu();

    QAction *action = new QAction("Удалить трассу");
    connect(action, &QAction::triggered,
            [this] () {
        auto selectedList = tableView->selectionModel()->selectedRows();
        if (!selectedList.isEmpty())
            tableView->model()->removeRow(selectedList.first().row());
    });
    tableMenu->addAction(action);
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
