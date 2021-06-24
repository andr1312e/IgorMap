#include "ktainfowindow.h"
#include <QBoxLayout>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QSharedPointer>
#include <QTimer>
#include <QTime>
#include "math.h"
#include <bMath.h>

KTAInfoWidget::KTAInfoWidget(QWidget *parent) : BaseWidget(WidgetTypes::KTAInfo, parent),
    timeAlive_msec(7000), timeErase(new QTimer())
{
    setTitle("Информация о КТА");
    resizeWidget(400, 300);

    Init();
}

void KTAInfoWidget::Init() {
    connect(timeErase, &QTimer::timeout, this, &KTAInfoWidget::eraseOldKTA);

    const int textLabelWidth = 40,
              outputTextWidth = 60;

    QLabel *radTextLabel = new QLabel("Радиус (км)");
    radSpallLine = new QLineEdit;
    radSpallLine->setValidator(new QRegExpValidator( QRegExp("^\\d*[.]?\\d*$"), radSpallLine ));
    radSpallLine->setText(QString::number(0.5, 'f', 2));
    radSpallLine->setFixedWidth(outputTextWidth);
    QHBoxLayout *radSpallLayout = new QHBoxLayout;
    radSpallLayout->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
    radSpallLayout->addWidget(radTextLabel);
    radSpallLayout->addWidget(radSpallLine);
    radSpallLayout->addStretch(1);

    QLabel *paramTextLabel = new QLabel("Параметры скола");
    QVBoxLayout *paramSpallLayout = new QVBoxLayout;
    paramSpallLayout->addWidget(paramTextLabel);
    paramSpallLayout->addLayout(radSpallLayout);
    paramSpallLayout->addStretch(1);

    QLabel *distLabel = new QLabel("D:");
    distLabel->setFixedWidth(textLabelWidth);
    distOutput = new QLabel(strNoValue);
    distOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *distLayout = new QHBoxLayout();
    distLayout->addWidget(distLabel);
    distLayout->addWidget(distOutput);

    QLabel *azLabel = new QLabel("Az:");
    azLabel->setFixedWidth(textLabelWidth);
    azimuthOutput = new QLabel(strNoValue);
    azimuthOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *azLayout = new QHBoxLayout();
    azLayout->addWidget(azLabel);
    azLayout->addWidget(azimuthOutput);

    QLabel *pointAngleLabel = new QLabel("Ugm:");
    pointAngleLabel->setFixedWidth(textLabelWidth);
    pointAngleOutput = new QLabel(strNoValue);
    pointAngleOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *pointAngleLayout = new QHBoxLayout();
    pointAngleLayout->addWidget(pointAngleLabel);
    pointAngleLayout->addWidget(pointAngleOutput);

    QHBoxLayout *firstInfoLayout = new QHBoxLayout;
    firstInfoLayout->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
    firstInfoLayout->addLayout(azLayout);
    firstInfoLayout->addLayout(pointAngleLayout);
    firstInfoLayout->addLayout(distLayout);
    firstInfoLayout->addStretch(1);

    QLabel *ampLabel = new QLabel("Amp:");
    ampLabel->setFixedWidth(textLabelWidth);
    ampOutput = new QLabel(strNoValue);
    ampOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *ampLayout = new QHBoxLayout();
    ampLayout->addWidget(ampLabel);
    ampLayout->addWidget(ampOutput);

    QLabel *rSpeedLabel = new QLabel("Vr:");
    rSpeedLabel->setFixedWidth(textLabelWidth);
    rSpeedOutput = new QLabel(strNoValue);
    rSpeedOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *rSpeedLayout = new QHBoxLayout();
    rSpeedLayout->addWidget(rSpeedLabel);
    rSpeedLayout->addWidget(rSpeedOutput);

    QHBoxLayout *secondInfoLayout = new QHBoxLayout;
    secondInfoLayout->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
    secondInfoLayout->addLayout(rSpeedLayout);
    secondInfoLayout->addLayout(ampLayout);
    secondInfoLayout->addStretch(1);

    QLabel *infoKTALabel = new QLabel("Информация о выбраной КТА");
    QVBoxLayout *infoKTALayout = new QVBoxLayout();
    infoKTALayout->addWidget(infoKTALabel);
    infoKTALayout->addLayout(firstInfoLayout);
    infoKTALayout->addLayout(secondInfoLayout);
    infoKTALayout->addStretch(1);

    QLabel *labelTable = new QLabel("Таблица КТА в выбранном сколе");
    showButton = new BasePushButton(":/icon/ic_table_show.png", ":/icon/ic_table_hide.png");
    tableView = new QTableView();
    tableView->setCornerButtonEnabled(false);
    tableView->hide();
    initTable();

    QHBoxLayout *headerTableLayout = new QHBoxLayout;
    headerTableLayout->addWidget(labelTable);
    headerTableLayout->addWidget(showButton);

    QVBoxLayout *tableLayout = new QVBoxLayout;
    tableLayout->addLayout(headerTableLayout);
    tableLayout->addWidget(tableView);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    //mainLayout->addLayout(paramSpallLayout);
    mainLayout->addLayout(infoKTALayout);
    mainLayout->addLayout(tableLayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);    

    connect(showButton, &QPushButton::clicked, this, &KTAInfoWidget::showTable);
    /*connect(radSpallLine,
            &QLineEdit::textChanged,
            CfgManager::Instance()->getUiController()->getMainUIView(),
            &MainUIView::setKTAClickThreshold);
    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &KTAInfoWidget::rowSelected);*/
}

void KTAInfoWidget::showTable()
{
    if (tableView->isHidden()) {
        tableView->show();
        resizeWidget(width(), height());
    }
    else {
        tableView->hide();
        QRect tableGeometry = tableView->geometry();
        int tHeight = tableGeometry.height();
        tableGeometry.setHeight(0);
        tableView->setGeometry(tableGeometry);
        int heightWindow = height();
        resizeWidget(width() - 1, heightWindow - tHeight);
//        QRect layoutGeometry = layout()->geometry();
//        layoutGeometry.setHeight(heightWindow - tHeight);
//        layout()->setGeometry(layoutGeometry);
//        QRect windowGeometry = geometry();
//        windowGeometry.setHeight(heightWindow - tHeight);
//        setGeometry(windowGeometry);
    }
}

void KTAInfoWidget::rowSelected()
{
    QModelIndexList rows = tableView->selectionModel()->selectedRows();
    if (rows.empty()) {
        displayKTAInfo(SharedPointerKTAMark());
    }
    else {
        emit selectKTARequest(rows.at(0).row());
    }
}

void KTAInfoWidget::resizeWidget(int w, int h) {

    resize(w, h);
    geometryCompensation();
}

void KTAInfoWidget::moveWidget(int x, int y) {

    move(x, y);
}

void KTAInfoWidget::fillTable(KTAMarksForTable *list)
{
    QStandardItemModel *model(static_cast<QStandardItemModel*>(tableView->model()));
    model->removeRows(0, model->rowCount());

    if (!list->empty()) {
        for (auto weakRefOnMark = list->begin(); weakRefOnMark != list->end(); weakRefOnMark++){
            SharedPointerKTAMark refOnMark = weakRefOnMark->toStrongRef();
            if (refOnMark) {
                QList<QStandardItem *> items;                
                items.append(new QStandardItem(QString::number(refOnMark.data()->az)));
                items.append(new QStandardItem(QString::number(refOnMark.data()->pointAngle)));
                items.append(new QStandardItem(QString::number(refOnMark.data()->dist)));
                items.append(new QStandardItem(QString::number(refOnMark.data()->rSpeed)));
                items.append(new QStandardItem(QString::number(10 * log10(refOnMark.data()->amp))));
                model->appendRow(items);
                if (refOnMark.data()->selected) {
                    tableView->selectRow(model->rowCount() - 1);
                    displayKTAInfo(refOnMark);
                }
            }
        }
    }
    resizeWidget(width() - 1, height() - 1);
}

void KTAInfoWidget::selectKTARequestAnswerHandler(WeakPointerKTAMark selectedIndex)
{
    displayKTAInfo(selectedIndex.toStrongRef());
}

void KTAInfoWidget::addPOIMarkSlot(POIKtaMessage msg)
{
    kta kta_loc = ktaFirst2ktaSecond(kta(0, msg.Amp, Polar(msg.D, msg.Az, msg.Um), msg.Vr));
    Coor3 coor = Polar2Coor3(kta_loc.Pol);
    Coor3 Coor = ChangeSistemCoor_L2G_AzUm_Fast(coor, msg.Az_ant, msg.Um_ant);
    kta_loc.Pol = Coor2Polar(Coor);

    VOIMarkMessage msg2;
    msg2.D = kta_loc.Pol.D;
    msg2.Azm = kta_loc.Pol.Az;
    msg2.Ugm = kta_loc.Pol.Um;
    msg2.flag_target = false;

    addVOIMarkSlot(msg2);
}

void KTAInfoWidget::addVOIMarkSlot(VOIMarkMessage msg)
{
    timeErase->stop();

    quint32 current_sec = QTime::currentTime().msecsSinceStartOfDay() / 1000;
    QPointF vertex(msg.D / 1000. * cos((90. - msg.Azm) * M_PI / 180.),
                  msg.D / 1000. * sin((90. - msg.Azm) * M_PI / 180.));

    if (!listOfMapVertex.isEmpty())  {
        if (listOfMapVertex.back().first == current_sec) {
            listOfMapVertex.back().second.insert(vertex.x(), msg);
        }
        else {
            if (listOfMapVertex.size() == timeAlive_msec / 1000) {
                listOfMapVertex.pop_front();
            }
            listOfMapVertex.push_back(qMakePair(current_sec, MapVertex()));
            listOfMapVertex.back().second.insert(vertex.x(), msg);
        }
    }
    else {
        listOfMapVertex.push_back(qMakePair(current_sec, MapVertex()));
        listOfMapVertex.back().second.insert(vertex.x(), msg);
    }
    timeErase->start(timeAlive_msec);
}

void KTAInfoWidget::sampledKTAMark(const QPointF leftBottom, const QPointF rightTop)
{
    QPointF centerRect(leftBottom.x() + ((rightTop.x() - leftBottom.x()) / 2),
                       leftBottom.y() + ((rightTop.y() - leftBottom.y()) / 2));

    QStandardItemModel *model(static_cast<QStandardItemModel*>(tableView->model()));
    model->removeRows(0, model->rowCount());

    const quint32 current_sec = QTime::currentTime().msecsSinceStartOfDay();

    QSharedPointer< QVector<float> > sharedArray(QSharedPointer< QVector<float> >::create());

    //QVector<QPair<MapVertex::const_iterator, MapVertex::const_iterator> > vectorOfSampledItreatorOfMaps;
    for (auto iter = listOfMapVertex.constBegin();
         iter != listOfMapVertex.constEnd(); iter++) {
        auto &mapItem = iter->second;
        auto leftBottomOfMap = mapItem.lowerBound(leftBottom.x()),
             rightTopOfMap = mapItem.lowerBound(rightTop.x());
        if (leftBottomOfMap != rightTopOfMap && leftBottomOfMap != mapItem.end()) {
            while (leftBottomOfMap != rightTopOfMap) {
                qreal y = leftBottomOfMap.value().D / 1000. * sin((90. - leftBottomOfMap.value().Azm) * M_PI / 180.);
                if (leftBottom.y() < y && y < rightTop.y()) {
                    sharedArray.data()->push_back(leftBottomOfMap.key());
                    sharedArray.data()->push_back(y);
                    sharedArray.data()->push_back(7.5f);
                    if (leftBottomOfMap.value().flag_target == false) {
                        sharedArray.data()->push_back(0.5);
                    }
                    else if (leftBottomOfMap.value().flag_target == true) {
                        sharedArray.data()->push_back(1.);
                    }
                    /*else if (leftBottomOfMap.value().numSurv == 2) {
                        sharedArray.data()->push_back(1.5);
                    }*/

                    sharedArray.data()->push_back(current_sec);

                    QList<QStandardItem *> items;
                    items.append(new QStandardItem(QString::number(leftBottomOfMap.value().Azm)));
                    items.append(new QStandardItem(QString::number(leftBottomOfMap.value().Ugm)));
                    items.append(new QStandardItem(QString::number(leftBottomOfMap.value().D)));
                    items.append(new QStandardItem(QString::number(leftBottomOfMap.value().Vr)));
                    items.append(new QStandardItem(QString::number(10 * log10(leftBottomOfMap.value().Amp))));
                    model->appendRow(items);
                }

                leftBottomOfMap++;
            }
        }
    }

    if (!sharedArray->isEmpty()) {
        emit drawSampledKTAMarkSignal(sharedArray);

        if (isHidden()) {
            show();
        }

        if (!showButton->selected()) {
            showButton->click();
        }
    }
}

void KTAInfoWidget::eraseOldKTA()
{
    listOfMapVertex.clear();
    timeErase->stop();
}

void KTAInfoWidget::initTable()
{
    QStandardItemModel *model = new QStandardItemModel;

    QStringList hHeader;    
    hHeader.append("Az");
    hHeader.append("Ugm");
    hHeader.append("D");
    hHeader.append("Vr");
    hHeader.append("Amp");


    model->setHorizontalHeaderLabels(hHeader);

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setMinimumWidth(25);
//    tableView->verticalHeader()->setMaximumWidth(12);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void KTAInfoWidget::displayKTAInfo(SharedPointerKTAMark refMark) {
    if (refMark) {
        distOutput->setText(QString::number(refMark.data()->dist));
        azimuthOutput->setText(QString::number(refMark.data()->az));
        pointAngleOutput->setText(QString::number(refMark.data()->pointAngle));
        ampOutput->setText(QString::number(10 * log10(refMark.data()->amp)));
        rSpeedOutput->setText(QString::number(refMark.data()->rSpeed));
    }
    else {
        distOutput->setText(strNoValue);
        azimuthOutput->setText(strNoValue);
        pointAngleOutput->setText(strNoValue);
        ampOutput->setText(strNoValue);
        rSpeedOutput->setText(strNoValue);
    }
}

void KTAInfoWidget::geometryCompensation()
{
    if (layout()) {
        if (!tableView->isHidden()) {
            QLayout *mainLayout = layout();
            QSize tableSizeHint = tableView->sizeHint();
            QLayoutItem *item = mainLayout->itemAt(mainLayout->count() - 1);
            QRect stretchGeometry = item->geometry(),
                  tableGeometry = tableView->geometry();
            if (stretchGeometry.height() > 1) {
                int stolenHeight = stretchGeometry.height() - 1;
                stretchGeometry.setHeight(1);
                item->setGeometry(stretchGeometry);

                tableGeometry.setHeight(tableSizeHint.height() + stolenHeight);
                tableView->setGeometry(tableGeometry);
            }
        }
//        else {
//            QRect mainGeometry = geometry();
//            QRect layoutGeometry = layout()->geometry();
//            QLayout *mainLayout = layout();
//            QVector<QRect> rectsOfMainLayout;
//            for (int i = 0 ; i < mainLayout->count(); i++) {
//                QLayoutItem *item = mainLayout->itemAt(i);
//                rectsOfMainLayout.append(item->geometry());
//            }
//            QLayout *tableLayout = static_cast<QLayout *>(mainLayout->itemAt(mainLayout->count() - 2));
//            for (int i = 0 ; i < tableLayout->count(); i++) {
//                QLayoutItem *item = tableLayout->itemAt(i);
//                rectsOfMainLayout.append(item->geometry());
//            }
//        }
    }
}


