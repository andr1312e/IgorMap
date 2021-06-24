#include "sectorsviewerwidget.h"
#include "datahandler.h"
#include "controlpanelwidget.h"

#include <QBoxLayout>
#include <QPainter>
#include <QListView>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QStackedLayout>
#include <QTableView>
#include <QRadioButton>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QTimeEdit>
#include <QHeaderView>
#include <QtMath>
#include <QVector2D>
#include <QTimer>
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>


SectorsViewerWidget::SectorsViewerWidget(QWidget *parent)
    : BaseWidget(WidgetTypes::Targeting, parent),
      maxSectors(maxNumberOfSectors), defaultDropingSec(15), letterMax(10),
      emptyModel(new QStandardItemModel),
      //sharedSectorData(ptr),
      vectorOfSectorsInfo(maxSectors, qMakePair(ItemState::Empty, SectorsPrivateInfo())),
      sectorRemover(new SectorRemover(this)),
      preSetVOIParams({1,1,3,4,5,5,5,5}), forcedBanOnPlottingDSP(false)
{
    setTitle("Целеуказания");

    //BaseLabel *nubmerLabel = new BaseLabel("Номер", this);
    /*numberBox = new QComboBox();
    for(auto &item : *sharedSectorData.data()) {
        QString str;
        if (item.first == ItemState::Empty) {
            str = QString("%1 - Пустое").arg(numberBox->count() + 1);
        }
        else if (item.first == ItemState::Current) {
            str = QString("%1 - Активное").arg(numberBox->count() + 1);
        }
        else if (item.first == ItemState::Excluded) {
            str = QString("%1 - Не активное").arg(numberBox->count() + 1);
        }
        numberBox->addItem(str);
    }
    numberBox->setMaxCount(maxSectors);
    numberBox->setMaxVisibleItems(maxSectors);*/
    //numberBox->setSizePolicy();
    /*BasePushButton *addButton = new BasePushButton(":/icon/ic_list_add_off.png",
                                                   ":/icon/ic_list_add_on.png",
                                                   this);
    BasePushButton *delButton = new BasePushButton(":/icon/ic_list_del_off.png",
                                                   ":/icon/ic_list_del_on.png",
                                                   this);*/


    //BaseLabel *settingLabel = new BaseLabel("Настройки работы", this);
    autoButton = new QCheckBox("Cброс через");
    QLabel *autoButtonLabel = new QLabel("сек ");
    resetAfterLineEdit = new BaseLineEdit(RealValidator::Degrees);
    resetAfterLineEdit->setText(QString::number(defaultDropingSec));
    workButton = new QCheckBox("Разрешить работу");
    //workButton->setChecked(true);

    //Number Layout
    /*QHBoxLayout *numberHeaderLayout = new QHBoxLayout();
    numberHeaderLayout->addWidget(nubmerLabel);
    numberHeaderLayout->addStretch(1);*/

    listView = new QListView();
    QStandardItemModel *model = new QStandardItemModel(maxSectors, 1);    

    quint16 offsetInModel = 0;
    for(auto &item : vectorOfSectorsInfo) {
        QString str;
        if (item.first == ItemState::Empty) {
            str = QString("ЦУ №%1 - Пустое").arg(offsetInModel + 1);
        }
        else if (item.first == ItemState::Active) {
            str = QString("ЦУ №%1 - Активное").arg(offsetInModel + 1);
        }
        else if (item.first == ItemState::Excluded) {
            str = QString("ЦУ №%1 - Не активное").arg(offsetInModel + 1);
        }

        QStandardItem* sItem = new QStandardItem;
        sItem->setData(str, Qt::DisplayRole);
        model->setItem(offsetInModel++, 0, sItem);
    }

    listView->setModel(model);
    listView->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listView->setUniformItemSizes(true);
    listView->setFixedHeight(100);

    QHBoxLayout *numberBodyLayout = new QHBoxLayout();
    //numberBodyLayout->setContentsMargins(margin);
    numberBodyLayout->addWidget(listView);
    //numberBodyLayout->addStretch(1);
    //numberBodyLayout->addWidget(addButton);
    //numberBodyLayout->addWidget(delButton);

    /*QVBoxLayout *numberLayout = new QVBoxLayout();
    numberLayout->addLayout(numberHeaderLayout);
    numberLayout->addLayout(numberBodyLayout);
    numberLayout->addStretch(1);*/
    numberGroupBox = new QGroupBox("Набор ЦУ");
    numberGroupBox->setLayout(numberBodyLayout);

    //Parameters Layout
    //init Graphics Item
    //BaseLabel *parametersHeaderLabel = new BaseLabel("Параметры", this);
    BaseLabel *distFromLabel = new BaseLabel("от");
    BaseLabel *distToLabel = new BaseLabel("до");
    BaseLabel *azFromLabel = new BaseLabel("от");
    BaseLabel *azToLabel = new BaseLabel("до");
    BaseLabel *ugmFromLabel = new BaseLabel("от");
    BaseLabel *ugmToLabel = new BaseLabel("до");
    BaseLabel *vrFromLabel = new BaseLabel("от");
    BaseLabel *vrToLabel = new BaseLabel("до");

    BaseLabel *distUnitLabel = new BaseLabel("км");
    BaseLabel *azUnitLabel = new BaseLabel("град");
    BaseLabel *ugmUnitLabel = new BaseLabel("град");
    BaseLabel *vrUnitLabel = new BaseLabel("м/с");

    BaseLabel *distLabel = new BaseLabel("Дальность");
    BaseLabel *azLabel = new BaseLabel("Азимут");
    BaseLabel *ugmLabel = new BaseLabel("Уголместа");
    BaseLabel *vrLabel = new BaseLabel("Скорость");

    distMinLineEdit = new BaseLineEdit(RealValidator::Kilometers, this);
    distMaxLineEdit = new BaseLineEdit(RealValidator::Kilometers, this);

    vrMinLineEdit = new BaseLineEdit(-1200, 1200, 2, this);
    vrMaxLineEdit = new BaseLineEdit(-1200, 1200, 2, this);

    azMinLineEdit = new BaseLineEdit(RealValidator::Degrees, this);
    azMaxLineEdit = new BaseLineEdit(RealValidator::Degrees, this);

    ugmMinLineEdit = new BaseLineEdit(RealValidator::Degrees, this);
    ugmMaxLineEdit = new BaseLineEdit(RealValidator::Degrees, this);

    BaseLabel *dist2FromLabel = new BaseLabel("  ");
    BaseLabel *dist2ToLabel = new BaseLabel("до");
    BaseLabel *az2FromLabel = new BaseLabel("  ");
    BaseLabel *az2ToLabel = new BaseLabel("до");
    BaseLabel *ugm2FromLabel = new BaseLabel("  ");
    BaseLabel *ugm2ToLabel = new BaseLabel("до");

    BaseLabel *dist2UnitLabel = new BaseLabel("км");
    BaseLabel *az2UnitLabel = new BaseLabel("град");
    BaseLabel *ugm2UnitLabel = new BaseLabel("град");

    BaseLabel *dist2Label = new BaseLabel("Дальность");
    BaseLabel *az2Label = new BaseLabel("Азимут");
    BaseLabel *ugm2Label = new BaseLabel("Уголместа");

    dist2LineEdit = new BaseLineEdit(RealValidator::Kilometers);
    az2LineEdit = new BaseLineEdit(RealValidator::Degrees);
    ugm2LineEdit = new BaseLineEdit(RealValidator::Degrees);

    QPushButton *btnSectorAdd = new QPushButton();
    btnSectorAdd->setIcon(QIcon(":/icon/ic_list_add_on.png"));
    btnSectorAdd->setIconSize(QSize(20,20));
    btnSectorAdd->setMaximumSize(22,22);
    QPushButton *btnSectorDel = new QPushButton();
    btnSectorDel->setIcon(QIcon(":/icon/ic_list_del_on.png"));
    btnSectorDel->setIconSize(QSize(20,20));
    btnSectorDel->setMaximumSize(22,22);
    /*QPushButton *btnSectorClear = new QPushButton();
    btnSectorClear->setIcon(QIcon(":/icon/ic_list_erase_all_on.png"));
    btnSectorClear->setIconSize(QSize(20,20));
    btnSectorClear->setMaximumSize(22,22);*/

    tableView = new QTableView();

    initTable();

    BaseLabel *dataLabel = new BaseLabel("t ");
    BaseLabel *xLabel = new BaseLabel("x ");
    BaseLabel *yLabel = new BaseLabel("y ");
    BaseLabel *zLabel = new BaseLabel("z ");

    xLineEdit = new BaseLineEdit(RealValidator::Kilometers);
    xLineEdit = new BaseLineEdit(RealValidator::Kilometers);
    yLineEdit = new BaseLineEdit(RealValidator::Kilometers);
    yLineEdit = new BaseLineEdit(RealValidator::Kilometers);
    zLineEdit = new BaseLineEdit(RealValidator::Kilometers);
    zLineEdit = new BaseLineEdit(RealValidator::Kilometers);

    timeEdit = new QTimeEdit();
    timeEdit->setDisplayFormat("hh:mm.ss");

    /*distMinLineEdit->setText(QString::number(50));
    distMaxLineEdit->setText(QString::number(90));

    azMinLineEdit->setText(QString::number(0));
    azMaxLineEdit->setText(QString::number(40));

    ugmMinLineEdit->setText(QString::number(30));
    ugmMaxLineEdit->setText(QString::number(50));*/

    acceptButton = new QPushButton("Применить");
    clearButton = new QPushButton("Сбросить");

    staticModeRB = new QRadioButton("Статический режим");
    traceModeRB = new QRadioButton("Траекторный режим");
    pointModeRB = new QRadioButton("Точечный режим");
    staticModeRB->setChecked(true);

    BaseLabel *setOfModesLabel = new BaseLabel("Набор режимов");
    setOfModesBox = new QComboBox();
    setOfModesBox->setMaxCount(5);
    setOfModesBox->addItems(QStringList({TableAttributes::threeSets,                                         
                                         TableAttributes::threeSetsPlusExtra,
                                         TableAttributes::fourSets,
                                         TableAttributes::setOfLFM,
                                         TableAttributes::setOfRI}));
    QStandardItemModel *setOfModesModel = qobject_cast<QStandardItemModel *>(setOfModesBox->model());
    setOfModesModel->item(3)->setEnabled(false);
    setOfModesModel->item(4)->setEnabled(false);
    setOfModesBox->setCurrentIndex(1);
    BaseLabel *freqOfRaysLabel = new BaseLabel("Частота выборки лучей");
    freqOfRaysBox = new QComboBox();
    freqOfRaysBox->setMaxCount(11);
    QStringList strList;
    for (quint8 index = 0; index < 11; index++) {
        strList << QString::number(index);
    }
    freqOfRaysBox->addItems(strList);
    freqOfRaysBox->setCurrentIndex(6);

    //init Layout
    QVBoxLayout *modeLayout = new QVBoxLayout();
    modeLayout->setContentsMargins(margin);
    modeLayout->addWidget(staticModeRB);
    modeLayout->addWidget(traceModeRB);
    //modeLayout->addWidget(pointModeRB);
    modeLayout->addStretch(1);

    //modeGroupBox = new QGroupBox("Режим работы");
    //modeGroupBox->setLayout(modeLayout);

    QHBoxLayout *distValuesLayout = new QHBoxLayout();
    distValuesLayout->addWidget(distFromLabel);
    distValuesLayout->addWidget(distMinLineEdit);
    distValuesLayout->addWidget(distToLabel);
    distValuesLayout->addWidget(distMaxLineEdit);
    distValuesLayout->addWidget(distUnitLabel);
    distValuesLayout->addStretch(1);

    QVBoxLayout *distLayout = new QVBoxLayout();
    distLayout->addWidget(distLabel);
    distLayout->addLayout(distValuesLayout);
    distLayout->addStretch(1);

    QHBoxLayout *azValuesLayout = new QHBoxLayout();
    azValuesLayout->addWidget(azFromLabel);
    azValuesLayout->addWidget(azMinLineEdit);
    azValuesLayout->addWidget(azToLabel);
    azValuesLayout->addWidget(azMaxLineEdit);
    azValuesLayout->addWidget(azUnitLabel);
    azValuesLayout->addStretch(1);

    QVBoxLayout *azLayout = new QVBoxLayout();
    azLayout->addWidget(azLabel);
    azLayout->addLayout(azValuesLayout);
    azLayout->addStretch(1);

    QHBoxLayout *ugmValuesLayout = new QHBoxLayout();
    ugmValuesLayout->addWidget(ugmFromLabel);
    ugmValuesLayout->addWidget(ugmMinLineEdit);
    ugmValuesLayout->addWidget(ugmToLabel);
    ugmValuesLayout->addWidget(ugmMaxLineEdit);
    ugmValuesLayout->addWidget(ugmUnitLabel);
    ugmValuesLayout->addStretch(1);

    QVBoxLayout *ugmLayout = new QVBoxLayout();
    ugmLayout->addWidget(ugmLabel);
    ugmLayout->addLayout(ugmValuesLayout);
    ugmLayout->addStretch(1);

    QHBoxLayout *dist2ValuesLayout = new QHBoxLayout();
    dist2ValuesLayout->addWidget(dist2FromLabel);
    dist2ValuesLayout->addWidget(dist2LineEdit);
    dist2ValuesLayout->addWidget(dist2UnitLabel);
    dist2ValuesLayout->addStretch(1);

    QVBoxLayout *dist2Layout = new QVBoxLayout();
    dist2Layout->addWidget(dist2Label);
    dist2Layout->addLayout(dist2ValuesLayout);
    dist2Layout->addStretch(1);

    QHBoxLayout *az2ValuesLayout = new QHBoxLayout();
    az2ValuesLayout->addWidget(az2FromLabel);
    az2ValuesLayout->addWidget(az2LineEdit);
    az2ValuesLayout->addWidget(az2UnitLabel);
    az2ValuesLayout->addStretch(1);

    QVBoxLayout *az2Layout = new QVBoxLayout();
    az2Layout->addWidget(az2Label);
    az2Layout->addLayout(az2ValuesLayout);
    az2Layout->addStretch(1);

    QHBoxLayout *ugm2ValuesLayout = new QHBoxLayout();
    ugm2ValuesLayout->addWidget(ugm2FromLabel);
    ugm2ValuesLayout->addWidget(ugm2LineEdit);
    ugm2ValuesLayout->addWidget(ugm2UnitLabel);
    ugm2ValuesLayout->addStretch(1);

    QVBoxLayout *ugm2Layout = new QVBoxLayout();
    ugm2Layout->addWidget(ugm2Label);
    ugm2Layout->addLayout(ugm2ValuesLayout);
    ugm2Layout->addStretch(1);

    QHBoxLayout *vrValuesLayout = new QHBoxLayout();
    vrValuesLayout->addWidget(vrFromLabel);
    vrValuesLayout->addWidget(vrMinLineEdit);
    vrValuesLayout->addWidget(vrToLabel);
    vrValuesLayout->addWidget(vrMaxLineEdit);
    vrValuesLayout->addWidget(vrUnitLabel);
    vrValuesLayout->addStretch(1);

    QVBoxLayout *vrLayout = new QVBoxLayout();
    distLayout->addWidget(vrLabel);
    distLayout->addLayout(vrValuesLayout);
    distLayout->addStretch(1);

    QHBoxLayout *timeValuesLayout = new QHBoxLayout();
    //timeValuesLayout->setContentsMargins(margin);
    timeValuesLayout->addWidget(dataLabel);
    timeValuesLayout->addWidget(timeEdit);
    timeValuesLayout->addStretch(1);

    QHBoxLayout *xyValuesLayout = new QHBoxLayout();
    //xyValuesLayout->setContentsMargins(margin);
    xyValuesLayout->addWidget(xLabel);
    xyValuesLayout->addWidget(xLineEdit);
    xyValuesLayout->addWidget(yLabel);
    xyValuesLayout->addWidget(yLineEdit);
    xyValuesLayout->addWidget(zLabel);
    xyValuesLayout->addWidget(zLineEdit);
    xyValuesLayout->addStretch(1);

    QHBoxLayout *zButtonValuesLayout = new QHBoxLayout();
    //zButtonValuesLayout->setContentsMargins(margin);


    zButtonValuesLayout->addStretch(1);
    //zButtonValuesLayout->addWidget(btnSectorAdd);
    //zButtonValuesLayout->addWidget(btnSectorDel);
    //zButtonValuesLayout->addWidget(btnSectorClear);

    QVBoxLayout *btnTableLayout = new QVBoxLayout();
    btnTableLayout->addWidget(btnSectorAdd);
    btnTableLayout->addWidget(btnSectorDel);
    //btnTableLayout->addWidget(btnSectorClear);
    btnTableLayout->addStretch(1);

    QHBoxLayout *tableBodyLayout = new QHBoxLayout();
    tableBodyLayout->addWidget(tableView);
    tableBodyLayout->addLayout(btnTableLayout);

    QVBoxLayout *traceBodyLayout = new QVBoxLayout();
    traceBodyLayout->addLayout(timeValuesLayout);
    traceBodyLayout->addLayout(xyValuesLayout);
    //traceBodyLayout->addLayout(zButtonValuesLayout);
    traceBodyLayout->addLayout(tableBodyLayout);
    traceBodyLayout->addStretch(1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(acceptButton);
    buttonLayout->addWidget(clearButton);

    QStringList list;
    workModeForVOICb = new QComboBox();
    list << TableAttributes::reflSignal << TableAttributes::dsp << TableAttributes::respSignalLFM << TableAttributes::respSignalRI;
    workModeForVOICb->addItems(list);
    list.clear();

    QLabel *workForVOILabel = new QLabel("Работа");
    QHBoxLayout *workForVOILayout = new QHBoxLayout();
    workForVOILayout->addWidget(workForVOILabel);
    workForVOILayout->addStretch(1);
    workForVOILayout->addWidget(workModeForVOICb);

    QHBoxLayout *autoResetLayout = new QHBoxLayout();
    //autoResetLayout->setContentsMargins(margin);
    //autoResetLayout->addWidget(autoButton);
    //autoResetLayout->addWidget(new QLabel(" "));
    autoResetLayout->addWidget(autoButton);
    autoResetLayout->addStretch(1);
    autoResetLayout->addWidget(resetAfterLineEdit);
    autoResetLayout->addWidget(autoButtonLabel);

    QVBoxLayout *workRadioBoxLayout = new QVBoxLayout();
    //workRadioBoxLayout->addWidget(autoButton);
    workRadioBoxLayout->addLayout(autoResetLayout);
    workRadioBoxLayout->addWidget(workButton);
    workRadioBoxLayout->addStretch(1);

    QHBoxLayout *workBodyLayout = new QHBoxLayout();
    //workBodyLayout->setContentsMargins(margin);
    workBodyLayout->addLayout(workRadioBoxLayout);

    /*QHBoxLayout *setOfModesBoxLayout = new QHBoxLayout();
    setOfModesBoxLayout->setContentsMargins(margin);
    setOfModesBoxLayout->addWidget(new QLabel(" "));
    setOfModesBoxLayout->addWidget(setOfModesBox);
    setOfModesBoxLayout->addStretch(1);

    QVBoxLayout *setOfModesBodyLayout = new QVBoxLayout();
    setOfModesBodyLayout->addWidget(setOfModesLabel);
    setOfModesBodyLayout->addLayout(setOfModesBoxLayout);
    setOfModesBodyLayout->addStretch(1);*/

    QHBoxLayout *setOfModesBodyLayout = new QHBoxLayout();
    //setOfModesBodyLayout->setContentsMargins(margin);
    setOfModesBodyLayout->addWidget(setOfModesLabel);
    setOfModesBodyLayout->addStretch(1);
    setOfModesBodyLayout->addWidget(setOfModesBox);

    /*QHBoxLayout *freqOfRaysBoxLayout = new QHBoxLayout();
    freqOfRaysBoxLayout->setContentsMargins(margin);
    freqOfRaysBoxLayout->addWidget(new QLabel(" "));
    freqOfRaysBoxLayout->addWidget(freqOfRaysBox);
    freqOfRaysBoxLayout->addStretch(1);

    QVBoxLayout *freqOfRaysBodyLayout = new QVBoxLayout();
    freqOfRaysBodyLayout->addWidget(freqOfRaysLabel);
    freqOfRaysBodyLayout->addLayout(freqOfRaysBoxLayout);
    freqOfRaysBodyLayout->addStretch(1);*/

    QHBoxLayout *freqOfRaysBodyLayout = new QHBoxLayout();
    //freqOfRaysBodyLayout->setContentsMargins(margin);
    freqOfRaysBodyLayout->addWidget(freqOfRaysLabel);
    freqOfRaysBodyLayout->addStretch(1);
    freqOfRaysBodyLayout->addWidget(freqOfRaysBox);

    QVBoxLayout *staticParamLayout = new QVBoxLayout();
    staticParamLayout->setContentsMargins(margin);
    staticParamLayout->addLayout(azLayout);
    staticParamLayout->addLayout(ugmLayout);
    staticParamLayout->addLayout(distLayout);
    staticParamLayout->addLayout(vrLayout);

    QGroupBox *sectorParametersGroupBox = new QGroupBox("Параметры сектора");
    sectorParametersGroupBox->setStyleSheet(groupBoxCSS);
    sectorParametersGroupBox->setLayout(staticParamLayout);

    QVBoxLayout *pointParamLayout = new QVBoxLayout();
    pointParamLayout->addLayout(az2Layout);
    pointParamLayout->addLayout(ugm2Layout);
    pointParamLayout->addLayout(dist2Layout);

    //QVBoxLayout *staticModeLayout = new QVBoxLayout();
    //staticModeLayout->addWidget(sectorParametersGroupBox);
    staticModeWidget = new QWidget();
    //staticModeWidget->setLayout(staticModeLayout);

    traceModeWidget = new QWidget();
    traceModeWidget->setLayout(traceBodyLayout);

    pointModeWidget = new QWidget();
    pointModeWidget->setLayout(pointParamLayout);

    stackedLayout = new QStackedLayout();
    //stackedLayout->addWidget(staticModeWidget);
    //stackedLayout->addWidget(traceModeWidget);
    //stackedLayout->addWidget(pointModeWidget);

    //QStringList list;
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

    dspModeCb = new QComboBox();
    list << TableAttributes::offStr << TableAttributes::dsp2Str << TableAttributes::dsp20Str;
    dspModeCb->addItems(list);
    list.clear();
    plottingDSPCheckBox = new QCheckBox("Отображение ДСП");
    //QPushButton *plottingDSPButton = new QPushButton("График");
    //plottingDSPButton->setCheckable(true);
    //plottingDSPButton->setEnabled(false);
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

    QStandardItemModel *letterModel = new QStandardItemModel;
    QVector<QString> requestSignal({"1","2"}),
            codeDistance({"53","85"}),
            responseSignal({"080", "105", "160", "190", "225", "250"});    
    for (auto &firstItem : requestSignal) {
        for (auto &secondItem : codeDistance) {
            for (auto &thirdItem : responseSignal) {
                QString str = firstItem + secondItem + thirdItem;
                //list << str;
                QStandardItem *item = new QStandardItem;
                item->setData(str, Qt::DisplayRole);
                item->setData(Qt::Unchecked, Qt::CheckStateRole);
                letterModel->setItem(letterModel->rowCount(), item);
            }
        }
    }
    // test LFM
    QStandardItem *item = new QStandardItem;
    item->setData(QString::number(1111111), Qt::DisplayRole);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);
    letterModel->setItem(letterModel->rowCount(), item);
    //QLabel *letterLabel = new QLabel("Литера");
    letterCb = new QComboBox();
    //letterCb->addItems(list);
    letterCb->setModel(letterModel);
    letterCb->setEnabled(false);
    letterCb->setCurrentIndex(-1);
    letterCb->setFocusPolicy(Qt::ClickFocus);
    letterCb->installEventFilter(this);
    list.clear();

    QVBoxLayout *letterBodyLayout = new QVBoxLayout();
    letterBodyLayout->setContentsMargins(margin);
    letterBodyLayout->addWidget(letterCb);
    letterBodyLayout->addStretch(1);

    QGroupBox *letterGroupBox = new QGroupBox("Список литер");
    letterGroupBox->setStyleSheet(groupBoxCSS);
    letterGroupBox->setLayout(letterBodyLayout);

    QVBoxLayout *voiSettingLayout = new QVBoxLayout();
    voiSettingLayout->setContentsMargins(margin);
    voiSettingLayout->addLayout(workForVOILayout);
    voiSettingLayout->addLayout(setOfModesBodyLayout);
    voiSettingLayout->addLayout(freqOfRaysBodyLayout);
    voiSettingLayout->addStretch(1);

    QGroupBox *voiSettingGroupBox = new QGroupBox("Подстройка вторички");
    voiSettingGroupBox->setStyleSheet(groupBoxCSS);
    voiSettingGroupBox->setLayout(voiSettingLayout);

    QVBoxLayout *userSettingLayout = new QVBoxLayout();
    userSettingLayout->setContentsMargins(margin);
    userSettingLayout->addLayout(workBodyLayout);

    QGroupBox *userSettingGroupBox = new QGroupBox("Пользовательские настройки");
    userSettingGroupBox->setStyleSheet(groupBoxCSS);
    userSettingGroupBox->setLayout(userSettingLayout);

    QVBoxLayout *parametersBodyLayout = new QVBoxLayout();
    parametersBodyLayout->setContentsMargins(margin);
    parametersBodyLayout->addWidget(sectorParametersGroupBox);
    parametersBodyLayout->addWidget(workModeGroupBox);
    parametersBodyLayout->addWidget(dspModeGroupBox);
    parametersBodyLayout->addWidget(letterGroupBox);
    parametersBodyLayout->addWidget(voiSettingGroupBox);
    parametersBodyLayout->addWidget(userSettingGroupBox);
    //parametersBodyLayout->addLayout(stackedLayout);
    //parametersBodyLayout->addLayout(setOfModesBodyLayout);
    //parametersBodyLayout->addLayout(freqOfRaysBodyLayout);
    //parametersBodyLayout->addLayout(workBodyLayout);
    parametersBodyLayout->addLayout(buttonLayout);

    /*QVBoxLayout *parametersLayout = new QVBoxLayout();
    parametersLayout->addWidget(parametersHeaderLabel);
    parametersLayout->addLayout(parametersBodyLayout);
    parametersLayout->addStretch(1);*/
    parametersGroupBox = new QGroupBox("Параметры");
    parametersGroupBox->setLayout(parametersBodyLayout);

    //modeGroupBox->setEnabled(false);
    parametersGroupBox->setEnabled(false);

    //Work Layout
    /*QHBoxLayout *workHeaderLayout = new QHBoxLayout();
    workHeaderLayout->addWidget(settingLabel);
    workHeaderLayout->addStretch(1);*/

    /*QVBoxLayout *workLayout = new QVBoxLayout();
    workLayout->addLayout(workHeaderLayout);
    workLayout->addLayout(workBodyLayout);
    workLayout->addStretch(1);*/
    //workGroupBox = new QGroupBox("Настройки работы");
    //workGroupBox->setLayout(workBodyLayout);
    //workGroupBox->setEnabled(false);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    //mainLayout->addLayout(numberLayout);
    //mainLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    //mainLayout->addLayout(parametersLayout);
    mainLayout->addWidget(numberGroupBox);
    //mainLayout->addWidget(modeGroupBox);
    mainLayout->addWidget(parametersGroupBox);
    //mainLayout->addLayout(stackedLayout);
    //mainLayout->addWidget(workGroupBox);
    //mainLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    //mainLayout->addLayout(workLayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    connect(listView, &QListView::clicked, this, &SectorsViewerWidget::listViewItemClicked);

    connect(acceptButton, &BasePushButton::released, this, &SectorsViewerWidget::acceptEffect);
    connect(clearButton, &QPushButton::released, this, &SectorsViewerWidget::clearEffect);

    connect(dspModeCb, QOverload<int>::of(&QComboBox::activated), this, &SectorsViewerWidget::dspModeChanged);
    connect(workModeCb, QOverload<int>::of(&QComboBox::activated), this, &SectorsViewerWidget::workModeChanged);

    connect(workModeForVOICb, QOverload<int>::of(&QComboBox::activated), this, &SectorsViewerWidget::workModeForVOIChanged);
    connect(setOfModesBox, QOverload<int>::of(&QComboBox::activated), this, &SectorsViewerWidget::userSettingChanged);
    connect(freqOfRaysBox, QOverload<int>::of(&QComboBox::activated), this, &SectorsViewerWidget::userSettingChanged);
    connect(letterCb, QOverload<int>::of(&QComboBox::activated), this, &SectorsViewerWidget::letterSettingChanged);

    //connect(btnSectorAdd, &QPushButton::clicked, this, &SectorsViewerWidget::addRow);
    //connect(btnSectorDel, &QPushButton::clicked, this, &SectorsViewerWidget::delRow);
    //connect(qobject_cast<QStandardItemModel *>(listView->model()), &QStandardItemModel::itemChanged, this, &SectorsViewerWidget::itemChangeInTable);

    //connect(staticModeRB, &QRadioButton::clicked, this, &SectorsViewerWidget::changeLayout);
    //connect(traceModeRB, &QRadioButton::clicked, this, &SectorsViewerWidget::changeLayout);
    //connect(pointModeRB, &QRadioButton::clicked, this, &SectorsViewerWidget::changeLayout);

    connect(this, &BaseWidget::exit, [this] () {
        emit setSectorOutFocus();
    });

    connect(autoButton, &QCheckBox::clicked, this, &SectorsViewerWidget::autoButtonClicked);
    connect(sectorRemover, &SectorRemover::deleteSectorByTimeout,
            this, &SectorsViewerWidget::deleteSectorByTimeoutSlot);
    connect(sectorRemover, &SectorRemover::restartSectorBlinking,
            this, &SectorsViewerWidget::restartSectorBlinking);
}

SectorRemover *SectorsViewerWidget::getSectorRemoverRef() const
{
    return sectorRemover;
}

void SectorsViewerWidget::openMainWidget()
{
    show();
}

void SectorsViewerWidget::repeaterNewSectorSignal(SharedSectorParameters sharedSector)
{
    //emit newSector(sharedSector);
}

void SectorsViewerWidget::openWidgetWithCurrentParams(QPointF point)
{

}

void SectorsViewerWidget::targetingAddSlot(const QPointF point, bool isQuick)
{
    qint8 currentIndex = -1;
    for (auto indexOfVector = 0;
         indexOfVector != vectorOfSectorsInfo.size();
         indexOfVector++) {
        if (vectorOfSectorsInfo.at(indexOfVector).first == ItemState::Empty) {
            currentIndex = indexOfVector;
            break;
        }
    }

    if (currentIndex != -1) {

        QModelIndex selectedIndex(listView->model()->index(currentIndex, 0));
        listView->setCurrentIndex(selectedIndex);
        listViewItemClicked(selectedIndex);


        float dist = qSqrt(qPow(point.x(), 2) + qPow(point.y(), 2));
        float angDeg = qRadiansToDegrees(qAtan2(point.y(), point.x()));
        angDeg = 90. - angDeg;
        deg360TransitionCheck(angDeg);

        float minDist, maxDist, minAz, maxAz;
        if (dist < 15) {
            minDist = 5;
            maxDist = 25;
        }
        else {
            minDist = dist - 10;
            maxDist = dist + 10;
        }

        minAz = angDeg - 20;
        deg360TransitionCheck(minAz);
        maxAz = angDeg + 20;
        deg360TransitionCheck(maxAz);

        distMinLineEdit->setText(QString::number(minDist, 'f', 2));
        distMaxLineEdit->setText(QString::number(maxDist, 'f', 2));
        azMinLineEdit->setText(QString::number(minAz, 'f', 2));
        azMaxLineEdit->setText(QString::number(maxAz, 'f', 2));
        ugmMinLineEdit->setText(QString::number(0, 'f', 2));
        ugmMaxLineEdit->setText(QString::number(20, 'f', 2));

        if (isQuick) {
            workButton->setCheckState(Qt::Checked);
            acceptEffect();
        }

        makeShow();
    }

}

void SectorsViewerWidget::targetingExcludeSlot(const QPointF point)
{
    float dist = qSqrt(qPow(point.x(), 2) + qPow(point.y(), 2));
    float angDeg = qRadiansToDegrees(qAtan2(point.y(), point.x()));
    angDeg = 90. - angDeg;
    deg360TransitionCheck(angDeg);

    QVector< QPair<quint8, float > > vectorOfPairIndexAndMinDist;
    //QVector2D clickPoint(point);

    for (int indexOfVector = 0;
         indexOfVector != vectorOfSectorsInfo.size();
         indexOfVector++) {
        auto &constIterOfVector = vectorOfSectorsInfo.at(indexOfVector);
        if (constIterOfVector.first == ItemState::Active) {
            if (dist > constIterOfVector.second.distMin && dist < constIterOfVector.second.distMax) {
                bool stagePassed = false;
                if (constIterOfVector.second.azMax < constIterOfVector.second.azMin) {
                    if ((constIterOfVector.second.azMin < angDeg && angDeg < 360.) &&
                        (constIterOfVector.second.azMax > angDeg && angDeg > 0.)) {
                        stagePassed = true;
                    }
                }
                else {
                    if (constIterOfVector.second.azMin < angDeg && angDeg < constIterOfVector.second.azMax) {
                        stagePassed = true;
                    }
                }

                if (stagePassed) {
                    float distOfSectorCenter = constIterOfVector.second.distMin +
                            (constIterOfVector.second.distMax - constIterOfVector.second.distMin) / 2,
                          azOfSectorCenter = constIterOfVector.second.azMax - constIterOfVector.second.azMin;
                    deg360TransitionCheck(azOfSectorCenter);
                    azOfSectorCenter = constIterOfVector.second.azMin + azOfSectorCenter / 2;
                    deg360TransitionCheck(azOfSectorCenter);
                    float radOfSectorCenter = qDegreesToRadians(90. - azOfSectorCenter);

                    QPointF centerPoint(distOfSectorCenter * qCos(radOfSectorCenter),
                                        distOfSectorCenter * qSin(radOfSectorCenter));
                    QPointF deltaFromCenterToPoint(point.x() - centerPoint.x(),
                                                   point.y() - centerPoint.y());
                    float distToCenter = qSqrt(qPow(deltaFromCenterToPoint.x(), 2) + qPow(deltaFromCenterToPoint.y(), 2));

                    vectorOfPairIndexAndMinDist.push_back(qMakePair(indexOfVector, distToCenter));
                }
            }


        }
        else {
            continue;
        }
    }

    if (!vectorOfPairIndexAndMinDist.isEmpty()) {
        quint8 currentIndex = vectorOfPairIndexAndMinDist.at(0).first;
        float minDist = vectorOfPairIndexAndMinDist.at(0).second;
        for (auto indexOfVector = 1;
             indexOfVector != vectorOfPairIndexAndMinDist.size();
             indexOfVector++) {
            if (minDist > vectorOfPairIndexAndMinDist.at(indexOfVector).second) {
                currentIndex = vectorOfPairIndexAndMinDist.at(indexOfVector).first;
                minDist = vectorOfPairIndexAndMinDist.at(indexOfVector).second;
            }
        }

        auto &itemOfVector = vectorOfSectorsInfo.data()[currentIndex];
        itemOfVector.first = ItemState::Excluded;
        itemOfVector.second.workIsOn = false;
        workButton->setChecked(false);

        QString str = QString("ЦУ №%1 - Не активное").arg(currentIndex + 1);
        QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(listView->model());
        sModel->item(currentIndex)->setText(str);

        emit excludeSector(currentIndex);
    }
}

void SectorsViewerWidget::deleteSectorByTimeoutSlot(quint8 id)
{
    auto &itemOfVector = vectorOfSectorsInfo.data()[id];
    itemOfVector.first = ItemState::Excluded;
    itemOfVector.second.workIsOn = false;
    workButton->setChecked(false);

    QString str = QString("ЦУ №%1 - Не активное").arg(id + 1);
    QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(listView->model());
    sModel->item(id)->setText(str);

    emit excludeSector(id);
}

void SectorsViewerWidget::restartSectorBlinking(quint8 id)
{
    if (vectorOfSectorsInfo.at(id).first == ItemState::Active) {
        auto &itemOfInfoStruct = vectorOfSectorsInfo[id].second;
        itemOfInfoStruct.dropingIsOn = autoButton->isChecked();
        itemOfInfoStruct.dropingSec = resetAfterLineEdit->text().toFloat();
        if (itemOfInfoStruct.dropingIsOn) {
            sectorRemover->removeIdAfter(id, itemOfInfoStruct.dropingSec);
        }
    }
}

void SectorsViewerWidget::isDSPExceedingUsageLimit(bool resolutionToSwitchingOn, bool resolutionToPlottingOn)
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
        const int currentIndex = listView->currentIndex().row();
        if (!vectorOfSectorsInfo.at(currentIndex).second.isPlotting) {
            plottingDSPCheckBox->setChecked(false);
            plottingDSPCheckBox->setEnabled(false);
        }
        else {
            plottingDSPCheckBox->setEnabled(true);
        }
        forcedBanOnPlottingDSP = true;
    }
    qDebug() << "SectorsViewerWidget::isDSPExceedingUsageLimit - SwitchingOn " << resolutionToSwitchingOn << " PlottingOn" << resolutionToPlottingOn;
}

void SectorsViewerWidget::changeDSPSlot(qint32 trackID, DSPType type, bool isPlotting)
{
    if (trackID < 0) {
        trackID = abs(trackID + 1);

        const int currentIndexInList = listView->currentIndex().row();

        SectorsPrivateInfo &info = vectorOfSectorsInfo.data()[trackID].second;
        ItemState &state = vectorOfSectorsInfo.data()[trackID].first;
        info.dspType = type;
        info.isPlotting = isPlotting;

        if (currentIndexInList != -1 && currentIndexInList == trackID) {
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

        QString workModeStr, dspStr;
        if (info.workMode == TargetWorkMode::ReflectedSignal) {
            workModeStr = "Отр";
        }
        else if (info.workMode == TargetWorkMode::ResponseSignal) {
            workModeStr = "Отв";
        }
        else {
            workModeStr = "Отр и Отв";
        }
        if (info.dspType != DSPType::None) {
            dspStr = "ДСП";
        }

        QString str;
        if (state == ItemState::Active) {
            str = QString("ЦУ №%1 - Активное").arg(trackID + 1);
            if (!workModeStr.isEmpty()) {
                str += " - ";
                str += workModeStr;
            }
            if (!dspStr.isEmpty()){
                str += " - ";
                str += dspStr;
            }
        }
        else if (state == ItemState::Excluded) {
            str = QString("ЦУ №%1 - Не активное").arg(trackID + 1);
        }
        QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(listView->model());
        sModel->item(trackID)->setText(str);

        generateMessageToVOI(trackID, info, true);
    }
    else {
        qDebug() << "SectorsViewerWidget::changeDSPSlot() - Cant find trackID in map";
    }
}


void SectorsViewerWidget::acceptEffect()
{
    if (!checkingForEmptyFields()) {
        return;
    }

    if (workModeCb->currentText() == TableAttributes::respSignal ||
        workModeCb->currentText() == TableAttributes::reflRespSignal) {
        if (letterCb->findData(Qt::Checked, Qt::CheckStateRole) == -1)
            return;
    }

    const int currentIndex = listView->currentIndex().row();
    SectorsPrivateInfo &sectorInfo = vectorOfSectorsInfo.data()[currentIndex].second;//vectorOfSectorsInfo[listView->currentIndex().row()].second;
    ItemState &sectorState = vectorOfSectorsInfo.data()[currentIndex].first;

    bool isNewSector;
    if (sectorState != ItemState::Active) {
        isNewSector = true;
    }
    else {
        if (checkingForModifyFields(sectorInfo)) {
            isNewSector = true;
        }
        else
            isNewSector = false;
    }

    //if (staticModeRB->isChecked()) {
        sectorInfo.sectorType = SectorType::StaticPlacement;
        sectorInfo.distMin = distMinLineEdit->text().toFloat();
        sectorInfo.distMax = distMaxLineEdit->text().toFloat();
        sectorInfo.azMin = azMinLineEdit->text().toFloat();
        sectorInfo.azMax = azMaxLineEdit->text().toFloat();
        sectorInfo.ugmMin = ugmMinLineEdit->text().toFloat();
        sectorInfo.ugmMax = ugmMaxLineEdit->text().toFloat();
        sectorInfo.vrMin = vrMinLineEdit->text().toFloat();
        sectorInfo.vrMax = vrMaxLineEdit->text().toFloat();
    /*}
    else if (traceModeRB->isChecked()) {
        sectorInfo.sectorType = SectorType::DynamicPlacement;
    }
    else if (pointModeRB->isChecked()) {
        sectorInfo.sectorType = SectorType::PointPlacement;
        sectorInfo.dist = dist2LineEdit->text().toFloat();
        sectorInfo.az = az2LineEdit->text().toFloat();
        sectorInfo.ugm = ugm2LineEdit->text().toFloat();
    }*/

    sectorInfo.workIsOn = workButton->isChecked();
    sectorInfo.dropingIsOn = autoButton->isChecked();
    sectorInfo.dropingSec = resetAfterLineEdit->text().toFloat();
    sectorInfo.setOfModes.clear();
    sectorInfo.freqOfRays.clear();
    sectorInfo.setOfModes << preSetVOIParams.at(0) << preSetVOIParams.at(1) << preSetVOIParams.at(2) << preSetVOIParams.at(3);
    sectorInfo.freqOfRays << preSetVOIParams.at(4) << preSetVOIParams.at(5) << preSetVOIParams.at(6) << preSetVOIParams.at(7);
    QString workModeStr, dspStr;
    if (workModeCb->currentText() == TableAttributes::reflSignal) {
        sectorInfo.workMode = TargetWorkMode::ReflectedSignal;
        workModeStr = "Отр";
    }
    else if (workModeCb->currentText() == TableAttributes::respSignal) {
        sectorInfo.workMode = TargetWorkMode::ResponseSignal;
        workModeStr = "Отв";
    }
    else {
        sectorInfo.workMode = TargetWorkMode::ReflectedAndResponse;
        workModeStr = "Отр и Отв";
    }
    if (dspModeCb->currentText() == TableAttributes::dsp2Str) {
        sectorInfo.dspType = DSPType::DSP2;
        dspStr = "ДСП";
    }
    else if (dspModeCb->currentText() == TableAttributes::dsp20Str) {
        sectorInfo.dspType = DSPType::DSP20;
        dspStr = "ДСП";
    }
    else {
        sectorInfo.dspType = DSPType::None;
    }
    sectorInfo.isPlotting = plottingDSPCheckBox->isChecked();
    /*if (sectorInfo.workMode == TargetWorkMode::ResponseSignal ||
        sectorInfo.workMode == TargetWorkMode::ReflectedAndResponse) {
        if (!sectorInfo.letter.isEmpty())
            sectorInfo.letter.clear();
        sectorInfo.letter.insert(letterCb->currentText().toInt());
    }*/
    sectorInfo.letter.clear();
    for (quint16 index = 0; index != letterCb->count(); index++) {
        if (letterCb->itemData(index, Qt::CheckStateRole) == Qt::Checked) {
            sectorInfo.letter.insert(letterCb->itemText(index).toInt());
        }
    }

    sectorState = workButton->isChecked() ? ItemState::Active : ItemState::Excluded;

    QString str;
    if (sectorState == ItemState::Active) {
        str = QString("ЦУ №%1 - Активное").arg(currentIndex + 1);
        if (!workModeStr.isEmpty()) {
            str += " - ";
            str += workModeStr;
        }
        if (!dspStr.isEmpty()){
            str += " - ";
            str += dspStr;
        }
    }
    else if (sectorState == ItemState::Excluded) {
        str = QString("ЦУ №%1 - Не активное").arg(currentIndex + 1);
    }
    QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(listView->model());
    sModel->item(currentIndex)->setText(str);

    if (sectorState == ItemState::Active) {
        SharedSectorParameters sector;
        if (sectorInfo.sectorType == SectorType::StaticPlacement) {
            sector = SharedSectorParameters(new SectorParameters(distMinLineEdit->getValuef(), distMaxLineEdit->getValuef(),
                                                                 azMinLineEdit->getValuef(), azMaxLineEdit->getValuef(),
                                                                 ugmMinLineEdit->getValuef(), ugmMaxLineEdit->getValuef()));
        }
        else if (sectorInfo.sectorType == SectorType::DynamicPlacement) {

        }
        /*else if (sectorInfo.sectorType == SectorType::PointPlacement) {
            sector = SharedSectorParameters(new SectorParameters(dist2LineEdit->getValuef() - 3, dist2LineEdit->getValuef() + 3,
                                                                 az2LineEdit->getValuef() - 1.5, az2LineEdit->getValuef() + 1.5,
                                                                 ugm2LineEdit->getValuef() - 1.5, ugm2LineEdit->getValuef() + 1.5));
        }*/

        generateMessageToVOI(currentIndex, sectorInfo, !isNewSector);

        emit newSector(currentIndex, sector);

        emit newSectorToDSPWidget(-(currentIndex + 1));
        //if (sectorInfo.dspType != DSPType::None) {
            emit dspActivationOnSector(-(currentIndex + 1), sectorInfo.dspType, sectorInfo.isPlotting);
        //}

        if (sectorInfo.dropingIsOn) {
            sectorRemover->removeIdAfter(currentIndex, sectorInfo.dropingSec);
        }
    }
    else if (sectorState == ItemState::Excluded) {
        emit excludeSector(currentIndex);

        SharedSectorParameters sector;
        if (sectorInfo.sectorType == SectorType::StaticPlacement) {
            sector = SharedSectorParameters(new SectorParameters(distMinLineEdit->getValuef(), distMaxLineEdit->getValuef(),
                                                                 azMinLineEdit->getValuef(), azMaxLineEdit->getValuef(),
                                                                 ugmMinLineEdit->getValuef(), ugmMaxLineEdit->getValuef()));
        }
        else if (sectorInfo.sectorType == SectorType::DynamicPlacement) {

        }
        /*else if (sectorInfo.sectorType == SectorType::PointPlacement) {
            sector = SharedSectorParameters(new SectorParameters(dist2LineEdit->getValuef() - 3, dist2LineEdit->getValuef() + 3,
                                                                 az2LineEdit->getValuef() - 1.5, az2LineEdit->getValuef() + 1.5,
                                                                 ugm2LineEdit->getValuef() - 1.5, ugm2LineEdit->getValuef() + 1.5));
        }*/
        emit presetSector(currentIndex, sector);

        RMOTargetDeleteMessage msg;
        msg.id = currentIndex;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_11);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(RMO_VOI_TARGET_DELETE_MESSAGE);
        out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(RMOTargetDeleteMessage));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        emit deleteSectorToVOI(arr);

        emit clearSectorToDSPWidget(-(currentIndex + 1));
    }


    /*if (!sector.isNull()) {
        sector.clear();
    }

    sector = SharedSectorParameters(new SectorParameters(distMinLineEdit->getValuef(), distMaxLineEdit->getValuef(),
                                                         azMinLineEdit->getValuef(), azMaxLineEdit->getValuef(),
                                                         ugmMinLineEdit->getValuef(), ugmMaxLineEdit->getValuef()));*/
    //emit newSector(numberBox->currentIndex(), sector);
    //numberBox->setItemText(numberBox->currentIndex(), QString("%1 - Активное").arg(numberBox->currentIndex() + 1));
}

void SectorsViewerWidget::clearEffect()
{
    const int currentIndex = listView->currentIndex().row();
    QString str = QString("ЦУ №%1 - Пустое").arg(currentIndex + 1);
    QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(listView->model());
    sModel->item(currentIndex)->setText(str);

    vectorOfSectorsInfo.data()[currentIndex].first = ItemState::Empty;

    listView->clearSelection();

    //modeGroupBox->setEnabled(false);
    parametersGroupBox->setEnabled(false);

    tableView->model()->removeRows(0, tableView->model()->rowCount());
    tableView->setModel(emptyModel);

    RMOTargetDeleteMessage msg;
    msg.id = currentIndex;

    QByteArray arr;

    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << qint16(0);
    out << quint8(RMO_VOI_TARGET_DELETE_MESSAGE);
    out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(RMOTargetDeleteMessage));
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));

    emit deleteSectorToVOI(arr);
    qDebug() << "RMO_VOI_TARGET_DELETE_MESSAGE";

    clearLineEdit();
    //emit setSectorOutFocus();
    emit deleteSector(currentIndex);

    emit clearSectorToDSPWidget(-(currentIndex + 1));
}

void SectorsViewerWidget::changeLayout()
{
    QRadioButton *rb = qobject_cast<QRadioButton *>(sender());

    if (rb == staticModeRB) {
        stackedLayout->setCurrentIndex(0);
        acceptButton->setEnabled(true);
    }
    else if (rb == traceModeRB) {
        stackedLayout->setCurrentIndex(1);
        acceptButton->setEnabled(false);
    }
    /*else if (rb == pointModeRB) {
        stackedLayout->setCurrentIndex(2);
        acceptButton->setEnabled(true);
    }*/
}


void SectorsViewerWidget::initTable()
{
    QStringList hHeader;
    hHeader.append("t");
    hHeader.append("x");
    hHeader.append("y");
    hHeader.append("z");

    emptyModel->setHorizontalHeaderLabels(hHeader);

    tableView->setModel(emptyModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setMinimumWidth(12);    
}

bool SectorsViewerWidget::checkingForEmptyFields()
{
    if (staticModeRB->isChecked()) {
        if (distMinLineEdit->text().isEmpty() || distMaxLineEdit->text().isEmpty()
                || azMinLineEdit->text().isEmpty() || azMaxLineEdit->text().isEmpty()
                || ugmMinLineEdit->text().isEmpty() || ugmMaxLineEdit->text().isEmpty()) {
            return false;
        }
        else
            return true;
    }
    else if (traceModeRB->isChecked()) {
        if (tableView->model()->rowCount() > 1) {
            return false;
        }
        else
            return true;
    }
    /*else if (pointModeRB->isChecked()) {
        if (dist2LineEdit->text().isEmpty()
            || az2LineEdit->text().isEmpty()
            || ugm2LineEdit->text().isEmpty()) {
            return false;
        }
        else
            return true;
    }*/
    else
        return false;
}

bool SectorsViewerWidget::checkingForModifyFields(SectorsPrivateInfo &sectorInfo)
{
    float epsilon = 0.01;
    if ((fabs(sectorInfo.azMax - azMaxLineEdit->text().toFloat()) < epsilon)
            && (fabs(sectorInfo.azMin - azMinLineEdit->text().toFloat()) < epsilon)
            && (fabs(sectorInfo.distMin - distMinLineEdit->text().toFloat()) < epsilon)
            && (fabs(sectorInfo.distMax - distMaxLineEdit->text().toFloat()) < epsilon)
            && (fabs(sectorInfo.ugmMin - ugmMinLineEdit->text().toFloat()) < epsilon)
            && (fabs(sectorInfo.ugmMax - ugmMaxLineEdit->text().toFloat()) < epsilon)
            /*&& (fabs(sectorInfo.vrMin - vrMinLineEdit->text().toFloat()) < epsilon)
            && (fabs(sectorInfo.vrMax - vrMaxLineEdit->text().toFloat()) < epsilon) */
            ){
        return false;
    }
    else
        return true;
}

void SectorsViewerWidget::clearLineEdit()
{
    distMinLineEdit->clear();
    distMaxLineEdit->clear();
    azMinLineEdit->clear();
    azMaxLineEdit->clear();
    ugmMinLineEdit->clear();
    ugmMaxLineEdit->clear();
    vrMinLineEdit->clear();
    vrMaxLineEdit->clear();

    xLineEdit->clear();
    yLineEdit->clear();
    zLineEdit->clear();

    dist2LineEdit->clear();
    az2LineEdit->clear();
    ugm2LineEdit->clear();
    resetAfterLineEdit->clear();

    autoButton->setCheckState(Qt::Unchecked);
    workButton->setCheckState(Qt::Unchecked);

    preSetVOIParams = QVector<quint8>({1,1,3,4,5,5,5,5});
    setOfModesBox->setCurrentIndex(preSetVOIParams.at(0));
    freqOfRaysBox->setCurrentIndex(preSetVOIParams.at(4));

    workModeCb->setCurrentIndex(workModeCb->findText(TableAttributes::reflSignal));
    dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::offStr));
    plottingDSPCheckBox->setEnabled(false);
    plottingDSPCheckBox->setChecked(false);
    workModeForVOICb->setCurrentIndex(workModeForVOICb->findText(TableAttributes::reflSignal));
    qint32 indexOfLetterData = letterCb->findData(Qt::Checked, Qt::CheckStateRole);
    while(indexOfLetterData != -1) {
        letterCb->setItemData(indexOfLetterData, Qt::Unchecked, Qt::CheckStateRole);
        indexOfLetterData = letterCb->findData(Qt::Checked, Qt::CheckStateRole);
    }
    letterCb->setEnabled(false);
    //letterCb->setCurrentIndex(0);
}


void SectorsViewerWidget::addRow()
{
    /*if (!firstAzLabel->text().isEmpty() && !lastAzLabel->text().isEmpty()) {
        int first = firstAzLabel->text().toInt(),
            last  = lastAzLabel->text().toInt();
        if (first > 359) {
            first = 359;
        }
        if (last > 359) {
            last = 359;
        }

        QStandardItemModel *model(static_cast<QStandardItemModel*>(tableView->model()));
        if (model->rowCount() < 4) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::number(first)));
            items.append(new QStandardItem(QString::number(last)));
            model->appendRow(items);
        }
        else
            return;

        firstAzLabel->clear();
        lastAzLabel->clear();
    }*/

    if (!xLineEdit->text().isEmpty()
            && !yLineEdit->text().isEmpty()
            && !zLineEdit->text().isEmpty()) {
        QStandardItemModel *model(static_cast<QStandardItemModel*>(tableView->model()));

        QList<QStandardItem *> items;
        items.append(new QStandardItem(timeEdit->text()));
        items.append(new QStandardItem(xLineEdit->text()));
        items.append(new QStandardItem(yLineEdit->text()));
        items.append(new QStandardItem(zLineEdit->text()));
        model->appendRow(items);
    }

}

void SectorsViewerWidget::delRow()
{
    QModelIndexList list(tableView->selectionModel()->selectedIndexes());
    QStandardItemModel *model(static_cast<QStandardItemModel*>(tableView->model()));
    foreach (auto item, list) {
        if (!model->removeRow(item.row())){
            qDebug() << "Row not deleted";
        }
    }
}

void SectorsViewerWidget::itemChangeInTable(QStandardItem *item)
{

}

void SectorsViewerWidget::listViewItemClicked(const QModelIndex &index)
{
    /*if (!modeGroupBox->isEnabled()) {
        modeGroupBox->setEnabled(true);
        parametersGroupBox->setEnabled(true);
    }*/
    parametersGroupBox->setEnabled(true);
    //distMinLineEdit->setReadOnly(false);
    //distMaxLineEdit->setReadOnly(false);


    if (vectorOfSectorsInfo.at(index.row()).first != ItemState::Empty) {
        fillParametersField(vectorOfSectorsInfo.at(index.row()).second);
        emit setSectorInFocus(index.row());
    }
    else {
        clearLineEdit();
        tableView->setModel(vectorOfSectorsInfo.at(index.row()).second.model);
        resetAfterLineEdit->setText(QString::number(defaultDropingSec));

        emit setSectorOutFocus();
        emit isDSPAvailableSignal();
        qDebug() << "SectorsViewerWidget::listViewItemClicked - emit isDSPAvailableSignal";
    }    
}

void SectorsViewerWidget::fillParametersField(const SectorsPrivateInfo &info)
{
    //if (info.sectorType == SectorType::StaticPlacement) {
        distMinLineEdit->setText(QString::number(info.distMin, 'f', 2));
        distMaxLineEdit->setText(QString::number(info.distMax, 'f', 2));
        azMinLineEdit->setText(QString::number(info.azMin, 'f', 2));
        azMaxLineEdit->setText(QString::number(info.azMax, 'f', 2));
        ugmMinLineEdit->setText(QString::number(info.ugmMin, 'f', 2));
        ugmMaxLineEdit->setText(QString::number(info.ugmMax, 'f', 2));
        vrMinLineEdit->setText(QString::number(info.vrMin, 'f', 2));
        vrMaxLineEdit->setText(QString::number(info.vrMax, 'f', 2));
    //}
    //else if (info.sectorType == SectorType::DynamicPlacement) {
        tableView->setModel(info.model);
    //}
    //else if (info.sectorType == SectorType::PointPlacement) {
//        dist2LineEdit->setText(QString::number(info.dist, 'f', 2));
//        az2LineEdit->setText(QString::number(info.az, 'f', 2));
//        ugm2LineEdit->setText(QString::number(info.ugm, 'f', 2));
    //}

    autoButton->setCheckState(info.dropingIsOn ? Qt::Checked : Qt::Unchecked);
    workButton->setCheckState(info.workIsOn ? Qt::Checked : Qt::Unchecked);
    resetAfterLineEdit->setText(QString::number(info.dropingSec));
    workModeForVOICb->setCurrentIndex(workModeForVOICb->findText(TableAttributes::reflSignal));
    setOfModesBox->setCurrentIndex(info.setOfModes.at(0));
    freqOfRaysBox->setCurrentIndex(info.freqOfRays.at(0));
    preSetVOIParams.clear();
    preSetVOIParams << info.setOfModes << info.freqOfRays;
    QString workModeStr;
    if (info.workMode == TargetWorkMode::ReflectedSignal) {
        workModeStr = TableAttributes::reflSignal;
    }
    else if (info.workMode == TargetWorkMode::ResponseSignal) {
        workModeStr = TableAttributes::respSignal;
    }
    else {
        workModeStr = TableAttributes::reflRespSignal;
    }
    workModeCb->setCurrentIndex(workModeCb->findText(workModeStr));
    if (info.dspType != DSPType::None) {
        if (info.dspType == DSPType::DSP2) {
            dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::dsp2Str));
        }
        else {
            dspModeCb->setCurrentIndex(dspModeCb->findText(TableAttributes::dsp20Str));
        }
        if (info.isPlotting) {
            plottingDSPCheckBox->setEnabled(true);
        }
        else {
            if (forcedBanOnPlottingDSP) {
                plottingDSPCheckBox->setEnabled(false);
            }
        }
        plottingDSPCheckBox->setChecked(info.isPlotting);
    }
    else {
        plottingDSPCheckBox->setEnabled(false);
    }
    for (quint16 index = 0; index != letterCb->count(); index++) {
        quint32 itemText = letterCb->itemText(index).toInt();
        auto itemOfInfoLetter = info.letter.find(itemText);
        if (itemOfInfoLetter != info.letter.end()){
            letterCb->setItemData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else {
            letterCb->setItemData(index, Qt::Unchecked, Qt::CheckStateRole);
        }
    }

    if (info.workMode == TargetWorkMode::ResponseSignal ||
            info.workMode == TargetWorkMode::ReflectedAndResponse) {
        //if (!info.letter.isEmpty())
        //    letterCb->setCurrentIndex(letterCb->findText(QString::number(*(info.letter.constBegin()))));
        letterCb->setEnabled(true);
    }
    else {
        letterCb->setEnabled(false);
        //letterCb->setCurrentIndex(0);
    }
}

void SectorsViewerWidget::autoButtonClicked()
{
    QModelIndexList listViewRowSelected = listView->selectionModel()->selectedRows();

    if (!listViewRowSelected.isEmpty()) {
        quint8 currentIndex = listViewRowSelected.at(0).row();
        if (vectorOfSectorsInfo.at(currentIndex).first == ItemState::Active) {
            auto &itemOfInfoStruct = vectorOfSectorsInfo[currentIndex].second;
            itemOfInfoStruct.dropingIsOn = autoButton->isChecked();
            itemOfInfoStruct.dropingSec = resetAfterLineEdit->text().toFloat();
            if (itemOfInfoStruct.dropingIsOn) {
                sectorRemover->removeIdAfter(currentIndex, itemOfInfoStruct.dropingSec);
            }
        }
    }
}

void SectorsViewerWidget::dspModeChanged(int )
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    QString str = cb->currentText();
    if (str == TableAttributes::offStr) {
        plottingDSPCheckBox->setEnabled(false);
        plottingDSPCheckBox->setChecked(false);
    }
    else {
        if (!forcedBanOnPlottingDSP)
            plottingDSPCheckBox->setEnabled(true);
    }
}

void SectorsViewerWidget::workModeForVOIChanged(int )
{
    QComboBox *cb = qobject_cast<QComboBox *>(sender());
    if (cb->currentIndex() == -1)
        return;

    QStandardItemModel *setOfModesModel = qobject_cast<QStandardItemModel *>(setOfModesBox->model());
    QString str = cb->currentText();
    if (str == TableAttributes::reflSignal ||  str == TableAttributes::dsp) {
        for (quint8 index = 0; index != setOfModesModel->rowCount(); index++) {
            if (index < 3) {
                setOfModesModel->item(index)->setEnabled(true);
            }
            else
                setOfModesModel->item(index)->setEnabled(false);
        }
        setOfModesBox->setCurrentIndex(1);
    }
    else if (str == TableAttributes::respSignalLFM) {
        for (quint8 index = 0; index != setOfModesModel->rowCount(); index++) {
            if (index == 3) {
                setOfModesModel->item(index)->setEnabled(true);
            }
            else
                setOfModesModel->item(index)->setEnabled(false);
        }
        setOfModesBox->setCurrentIndex(3);
    }
    else if (str == TableAttributes::respSignalRI) {
        for (quint8 index = 0; index != setOfModesModel->rowCount(); index++) {
            if (index == 4) {
                setOfModesModel->item(index)->setEnabled(true);
            }
            else
                setOfModesModel->item(index)->setEnabled(false);
        }
        setOfModesBox->setCurrentIndex(4);
    }
}

void SectorsViewerWidget::workModeChanged(int )
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    QString str = cb->currentText();
    if (str == TableAttributes::respSignal ||
        str == TableAttributes::reflRespSignal) {
        letterCb->setEnabled(true);
    }
    else {
        letterCb->setEnabled(false);
    }
}

void SectorsViewerWidget::userSettingChanged(int)
{
    //QString strWorkMode = workModeForVOICb->currentText();
    int workModeForVOICbIndex = workModeForVOICb->currentIndex();
    if (workModeForVOICbIndex == -1)
        return;
    QComboBox *cb = qobject_cast<QComboBox *>(sender());
    if (cb == setOfModesBox) {
        preSetVOIParams.data()[workModeForVOICbIndex] = cb->currentIndex();
    }
    else if (cb == freqOfRaysBox) {
        preSetVOIParams.data()[workModeForVOICbIndex + 4] = cb->currentText().toInt();
    }
}

void SectorsViewerWidget::letterSettingChanged(int)
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    quint16 letterCounter = 0;
    for (quint16 index = 0; index != cb->count(); index++){
        if (cb->itemData(index, Qt::CheckStateRole) == Qt::Checked)
            letterCounter++;
    }

    if (letterCounter == letterMax) {
        if (cb->currentData(Qt::CheckStateRole) == Qt::Checked) {
            cb->setItemData(cb->currentIndex(), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
    else {
        Qt::CheckState checkState = (Qt::CheckState)cb->currentData(Qt::CheckStateRole).toInt();
        cb->setItemData(cb->currentIndex(), checkState == Qt::Unchecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
    }
    cb->clearFocus();
}

void SectorsViewerWidget::deg360TransitionCheck(float &ang) {
    if (ang > 360) {
        ang -= 360;
    }
    else if (ang < 0) {
        ang += 360;
    }
}

void SectorsViewerWidget::generateMessageToVOI(quint32 trackID, SectorsPrivateInfo &info, bool isUpdate)
{
    RMOTargetPositionMessage msg;
    msg.id = trackID;
    msg.azimuth[0] = info.azMin;
    msg.azimuth[1] = info.azMax;
    msg.ugm[0] = info.ugmMin;
    msg.ugm[1] = info.ugmMax;
    msg.dist[0] = info.distMin;
    msg.dist[1] = info.distMax;
    msg.vr[0] = info.vrMin;
    msg.vr[1] = info.vrMax;
    msg.isUpdate = isUpdate;
    msg.count_letter = info.letter.count();
    quint16 counterOfLetterArray = 0;
    for (auto &item : info.letter) {
        bool isLFM = false;
        if (item > 1000000) {
            isLFM = true;
        }
        msg.answer[counterOfLetterArray].type_letter = !isLFM;
        msg.answer[counterOfLetterArray].set_mode = info.setOfModes.at(isLFM ? 2 : 3);
        msg.answer[counterOfLetterArray].freq_rays = info.freqOfRays.at(isLFM ? 2 : 3);
        msg.answer[counterOfLetterArray++].letter = item;
    }
    if (info.dspType != DSPType::None) {
        if (info.workMode == TargetWorkMode::ResponseSignal) {
            msg.work_mode = TargetWorkMode::ResponseAndDSP;
        }
        else if (info.workMode == TargetWorkMode::ReflectedSignal) {
            msg.work_mode = TargetWorkMode::ReflectedAndDSP;
        }
        else  {
            msg.work_mode = TargetWorkMode::ReflectedAndResponseAndDSP;
        }
        msg.out_dsp = info.isPlotting;
    }
    else {
        msg.work_mode = info.workMode;
    }

    for (quint8 i = 0; i < 2; i++)
        msg.set_mode[i] = info.setOfModes.at(i);
    for (quint8 i = 0; i < 2; i++)
        msg.freq_rays[i] = info.freqOfRays.at(i);

    if (info.dspType == DSPType::DSP20) {
        msg.DSP = 1;
    }
    else
        msg.DSP = 0;


    QByteArray arr;

    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_11);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << qint16(0);
    out << quint8(RMO_VOI_TARGET_POSITION_MESSAGE);
    out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(RMOTargetPositionMessage));
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));

    emit addSectorsToVOI(arr);
    qDebug() << "RMO_VOI_TARGET_POSITION_MESSAGE" << "isNewSector " << isUpdate;
}

bool SectorsViewerWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == letterCb && event->type() == QEvent::Wheel)
    {
        return true;
    }
    return QObject::eventFilter(watched, event);
}


SectorRemover::SectorRemover(QObject *parent)  :
    QObject(parent),
    maxSectors(maxNumberOfSectors), maxBlinkingSec(16),
    messageBoxManager(new MessageBoxWindowManager)
{
    for (quint8 i = 0; i < maxSectors; i++) {
        droppingTimers.push_back(new QTimer);
        connect(droppingTimers.at(i), &QTimer::timeout,
                this, &SectorRemover::timeoutDropping);
    }
    for (quint8 i = 0; i < maxSectors; i++) {
        blinkingTimers.push_back(qMakePair(new QTimer, maxBlinkingSec));
        connect(blinkingTimers.at(i).first, &QTimer::timeout,
                this, &SectorRemover::timeoutBlinking);
    }

    connect(this, &SectorRemover::addMessageBox,
            messageBoxManager, &MessageBoxWindowManager::addMessageBoxOnDisplay);
    connect(this, &SectorRemover::updateMessageBox,
            messageBoxManager, &MessageBoxWindowManager::updateMessageBoxOnDisplay);
    connect(this, &SectorRemover::closeMessageBox,
            messageBoxManager, &MessageBoxWindowManager::closeMessageBox);
    connect(messageBoxManager, &MessageBoxWindowManager::userAnswer,
            this, &SectorRemover::userAnswerHandler);
}

SectorRemover::~SectorRemover()
{
    for (quint8 i = 0; i < maxSectors; i++) {
        droppingTimers.at(i)->stop();
        delete droppingTimers.at(i);
    }
}

void SectorRemover::removeIdAfter(quint8 id, quint32 sec)
{
    droppingTimers.at(id)->stop();
    droppingTimers.at(id)->start(sec * 1000);
}

void SectorRemover::stopDroppingTimerOnId(quint8 id)
{
    droppingTimers.at(id)->stop();
}

void SectorRemover::stopBlinkingTimerOnId(quint8 id)
{
    blinkingTimers.at(id).first->stop();
    blinkingTimers[id].second = maxBlinkingSec;
    emit sectorBlinking(id, ActionsWithBlinkingSector::ResetValue);
}

void SectorRemover::resetAllOnId(quint8 id)
{
    droppingTimers.at(id)->stop();

    if (blinkingTimers.at(id).first->isActive()){
        blinkingTimers.at(id).first->stop();
        blinkingTimers[id].second = maxBlinkingSec;
        emit sectorBlinking(id, ActionsWithBlinkingSector::ResetValue);
    }
}

void SectorRemover::userAnswerHandler(quint8 id, QMessageBox::ButtonRole role)
{
    resetAllOnId(id);
    if (role == QMessageBox::AcceptRole) {
        emit deleteSectorByTimeout(id);
    }
    else if (role == QMessageBox::RejectRole) {
        emit restartSectorBlinking(id);
    }
}

void SectorRemover::timeoutDropping()
{
    QTimer *timerSender = qobject_cast<QTimer *>(sender());
    timerSender->stop();
    quint8 currentId = 0;
    for (quint8 index = 0; index != droppingTimers.size(); index++) {
        if (droppingTimers.at(index) == timerSender) {
            currentId = index;
            break;
        }
    }

    emit addMessageBox(currentId, maxBlinkingSec / 2);
    blinkingTimers.at(currentId).first->start(500);
}

void SectorRemover::timeoutBlinking()
{
    QTimer *timerSender = qobject_cast<QTimer *>(sender());
    quint8 currentId = 0;
    for (quint8 index = 0; index != droppingTimers.size(); index++) {
        if (blinkingTimers.at(index).first == timerSender) {
            currentId = index;
            break;
        }
    }

    if (blinkingTimers.at(currentId).second != 0) {
        blinkingTimers.data()[currentId].second--;
        emit updateMessageBox(currentId, blinkingTimers.at(currentId).second / 2);
        emit sectorBlinking(currentId, ActionsWithBlinkingSector::Reverse);
    }
    else {
        timerSender->stop();
        blinkingTimers.data()[currentId].second = maxBlinkingSec;
        emit closeMessageBox(currentId);
        emit deleteSectorByTimeout(currentId);
        //emit sectorBlinking(currentId, ActionsWithBlinkingSector::Remove);
    }
}

MessageBoxWindowManager::MessageBoxWindowManager(QObject *parent) :
    QObject(parent),
    maxSectors(maxNumberOfSectors)
{
    for (quint8 i = 0; i < maxSectors; i++) {
        QMessageBox *sameItem = new QMessageBox;
        sameItem->setWindowFlags( Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint ); //makes sure the msgbox is deleted automatically when closed
        sameItem->addButton("Сбросить сейчас", QMessageBox::AcceptRole);
        sameItem->addButton("Продлить", QMessageBox::RejectRole);
        sameItem->setText("Cброс сектора 10 через 10...");
        sameItem->setModal(false);

        connect(sameItem, &QMessageBox::buttonClicked,
                this, &MessageBoxWindowManager::messageBoxButtonClick);

        messageBoxVector.push_back(sameItem);
    }

    QRect availableGeometryOnScreen = QGuiApplication::screens().at(currentScreenIndex)->availableGeometry();
    standardSize = messageBoxVector.at(0)->sizeHint();
    quint16 messageBoxCountOnY = availableGeometryOnScreen.height() / standardSize.height();
    quint16 nubmerOfFreePosition = 0;
    if (messageBoxCountOnY > 5) {
        nubmerOfFreePosition = (messageBoxCountOnY - 5) / 2;
    }
    else {
        qDebug() << "Сan't fit the messageBox onto the screen";
    }
    availableGeometry = QRect(availableGeometryOnScreen.width() / 2 - standardSize.width(),
                              nubmerOfFreePosition * standardSize.height(),
                              2 * standardSize.width(),
                              5 * standardSize.height());
    QPoint startPoint = QPoint(availableGeometry.x(), availableGeometry.y());
    for (quint8 i = 0; i < maxSectors; i++) {
        if (i == (maxSectors / 2)) {
            startPoint = QPoint(availableGeometry.x() + standardSize.width(), availableGeometry.y());
            startPointOfMessageBoxs.push_back(qMakePair(startPoint, -1));
        }
        else {
            startPointOfMessageBoxs.push_back(qMakePair(startPoint, -1));
            startPoint.ry() += standardSize.height();
        }
    }

    for (quint8 i = 0; i < maxSectors; i++) {
        statesOfMessageBox.push_back(qMakePair(ItemState::Empty, 0));
    }


}

MessageBoxWindowManager::~MessageBoxWindowManager()
{
    for (quint8 i = 0; i < maxSectors; i++) {
        delete messageBoxVector.at(i);
    }
}

void MessageBoxWindowManager::addMessageBoxOnDisplay(quint8 id, quint8 timeLeft)
{
    if (statesOfMessageBox[id].first == ItemState::Active)
        return;

    statesOfMessageBox[id].first = ItemState::Active;
    quint8 freePosition = 0;
    for (quint8 i = 0; i < maxSectors; i++) {
        if (startPointOfMessageBoxs.at(i).second == -1) {
            freePosition = i;
            startPointOfMessageBoxs[freePosition].second = id;
            break;
        }
    }
    statesOfMessageBox[id].second = freePosition;

    messageBoxVector.at(id)->move(startPointOfMessageBoxs.at(freePosition).first);

    messageBoxVector.at(id)->setText(QString("Cброс сектора %1 через %1...").arg(id + 1).arg(timeLeft));
    messageBoxVector.at(id)->open();
}

void MessageBoxWindowManager::updateMessageBoxOnDisplay(quint8 id, quint8 timeLeft)
{
    messageBoxVector.at(id)->setText(QString("Cброс сектора %1 через %2...").arg(id + 1).arg(timeLeft));
}

void MessageBoxWindowManager::closeMessageBox(quint8 id)
{
    statesOfMessageBox[id].first = ItemState::Empty;
    messageBoxVector.at(id)->close();
    startPointOfMessageBoxs[statesOfMessageBox.at(id).second].second = -1;
}

void MessageBoxWindowManager::messageBoxButtonClick(QAbstractButton *button)
{
    QMessageBox *messageBoxSender = qobject_cast<QMessageBox *>(sender());

    quint8 currentIndex = 0;
    for (quint8 i = 0; i < maxSectors; i++) {
        if (messageBoxVector.at(i) == messageBoxSender) {
            currentIndex = i;
            break;
        }
    }

    statesOfMessageBox[currentIndex].first = ItemState::Empty;
    startPointOfMessageBoxs[statesOfMessageBox.at(currentIndex).second].second = -1;

    emit userAnswer(currentIndex, messageBoxSender->buttonRole(button));
}
