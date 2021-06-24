#include "llfreadercontrolwidget.h"
#include <QFileDialog>
#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>
#include <QTextLayout>
#include <QDebug>


void LLFRSlider::mousePressEvent(QMouseEvent *event) {
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    if (event->button() == Qt::LeftButton &&
        sr.contains(event->pos()) == false)
    {
      int newVal;
      if (orientation() == Qt::Vertical)
         newVal = minimum() + ((maximum()-minimum()) * (height()-event->y())) / height();
      else
         newVal = minimum() + ((maximum()-minimum()) * event->x()) / width();

      if (invertedAppearance() == true)
          setValue(maximum() - newVal);
      else
          setValue(newVal);

      event->accept();
    }
    QSlider::mousePressEvent(event);
}

LLFReaderCWButton::LLFReaderCWButton() {
    isSelected = false;
    setStyleSheet("padding: 0; margin: 0;");
    setFixedSize(30, 30);
}

void LLFReaderCWButton::setIcon(QString notSelectedIconPath, QString selectedIconPath) {
    iconNotSelected.load(notSelectedIconPath);
    iconSelected.load(selectedIconPath);
    setFixedSize(iconNotSelected.width(), iconNotSelected.height());
}

void LLFReaderCWButton::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // draw background
    //painter.fillRect(this->rect(), Qt::SolidPattern);

    if (type == BTN_NONE) {
        // draw icon
        if (isSelected) {
            painter.drawPixmap(0, 0, iconSelected);
        } else {
            painter.drawPixmap(0, 0, iconNotSelected);
        }
    }
    else if (type == BTN_FORWARD_SPEED) {
        float value = 2;
        if (value == 3)
            value = 0.5;

        QFont font;
        font.setFamily("Calibri");
        font.setPixelSize(26);
        painter.setPen(QPen(QColor(255, 255, 255, 200), 1, Qt::SolidLine, Qt::FlatCap));

        QString str(QString::number(value) + "x");
        QTextLayout textLayout(str, font);
        qreal marginX = 2, marginY = 2;
        qreal y = 0;
        textLayout.beginLayout();
        while (1) {
            QTextLine line = textLayout.createLine();
            if (!line.isValid())
                break;

            line.setLineWidth(width() - marginX);
            qreal _widthText = (line.width() - line.naturalTextWidth()) / 2;
            line.setPosition(QPointF(marginX + _widthText, marginY + y));
            y += line.height() - marginY;
        }
        textLayout.endLayout();
        textLayout.draw(&painter, QPoint(0, 0));
    }
}

LLFReaderControlWidget::LLFReaderControlWidget(BaseWidget *parent) : BaseWidget(WidgetTypes::Replay, parent) {

    setTitle(tr("История"));
    resizeWidget(150,
                 300);
    //widgetState = LLFRC_DISPLAY_HISTORY;

    initMap();

    labDir = new QLabel();

    btnSetDir = new QPushButton("Выбор файла регистрации");
    connect(btnSetDir, &QPushButton::pressed, this, &LLFReaderControlWidget::selectDir);

    btnSelectAll = new QPushButton("Выбрать/снять все записи");
    btnSelectAll->setCheckable(true);
    connect(btnSelectAll, &QPushButton::toggled, this, &LLFReaderControlWidget::selectAllMsg);

    listMsg = new QListWidget();
    listMsg->setSelectionMode(QAbstractItemView::MultiSelection);
    listMsg->setSortingEnabled(false);
    for (auto iter = mapMsg.begin(); iter != mapMsg.end(); iter++) {
        QListWidgetItem *item = new QListWidgetItem(iter->first, listMsg);
        Q_UNUSED(item);
        //item->setSelected(true);
    }

    connect(listMsg, &QListWidget::itemClicked, this, &LLFReaderControlWidget::selectMsg);

    btnDecSpeed = new LLFReaderCWButton();
    btnDecSpeed->setIcon(":/res/llfr_ic_flash_back_on.png", ":/res/llfr_ic_flash_back_off.png");
    btnPause = new LLFReaderCWButton();
    btnPause->setIcon(":/res/llfr_ic_pause_off.png", ":/res/llfr_ic_pause_on.png");
    btnStart = new LLFReaderCWButton();
    btnStart->setIcon(":/res/llfr_ic_play_off.png", ":/res/llfr_ic_play_on.png");
    btnIncSpeed = new LLFReaderCWButton();
    btnIncSpeed->setIcon(":/res/llfr_ic_flash_forward_on.png", ":/res/llfr_ic_flash_forward_off.png");
    btnStop = new LLFReaderCWButton();
    btnStop->setIcon(":/res/llfr_ic_seek_start_off.png", ":/res/llfr_ic_seek_start_on.png");
    btnToggledSpeed = new LLFReaderCWButton();
    btnToggledSpeed->setType(BTN_FORWARD_SPEED);

    lineTime = new QDateTimeEdit();
    btnAccept = new QPushButton("Применить");
    QHBoxLayout *timeControlsLayout = new QHBoxLayout();
    timeControlsLayout->addWidget(lineTime);
    timeControlsLayout->addWidget(btnAccept);

    QHBoxLayout *playControlsLayout = new QHBoxLayout();
    playControlsLayout->setContentsMargins(0, 0, 0, 0);    
    playControlsLayout->addWidget(btnStop);
    playControlsLayout->addWidget(btnDecSpeed);
    playControlsLayout->addWidget(btnPause);
    playControlsLayout->addWidget(btnStart);
    playControlsLayout->addWidget(btnIncSpeed);
    playControlsLayout->addWidget(btnToggledSpeed);

    QVBoxLayout *historyLayout = new QVBoxLayout();
    historyLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));
    historyLayout->addWidget(labDir, Qt::AlignLeft | Qt::AlignTop);
    historyLayout->addWidget(btnSetDir, Qt::AlignLeft | Qt::AlignTop);
    historyLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));
    historyLayout->addLayout(timeControlsLayout);
    historyLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));
    historyLayout->addLayout(playControlsLayout);
    historyLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));
    historyLayout->addWidget(btnSelectAll);
    historyLayout->addWidget(listMsg);
    historyLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));

    connect(btnPause, SIGNAL(clicked()), this, SLOT(setSpeed()));
    connect(btnStart, SIGNAL(clicked()), this, SLOT(setSpeed()));
    connect(btnDecSpeed, SIGNAL(clicked()), this, SLOT(setSpeed()));
    connect(btnIncSpeed, SIGNAL(clicked()), this, SLOT(setSpeed()));
    connect(btnToggledSpeed, SIGNAL(clicked()), this, SLOT(setSpeed()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(stop()));

    connect(btnAccept, &QPushButton::clicked, this, &LLFReaderControlWidget::timeChanged);

    /*QHBoxLayout *topPanel = new QHBoxLayout();
    topPanel->addSpacerItem(new QSpacerItem(50, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    topPanel->addLayout(historyLayout);
    topPanel->addSpacerItem(new QSpacerItem(50, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));*/

    setLayout(historyLayout);    
}

void LLFReaderControlWidget::resizeWidget(int w, int h) {


    resize(w, h);
}

void LLFReaderControlWidget::moveWidget(int x, int y) {


    move(x, y);
}

void LLFReaderControlWidget::pause() {
    if (!btnPause->selected()) {
        resetButtons();
        btnPause->setSelected(true);

        simPlayOn msg;
        msg.playOn = SIM_CMD_PAUSE;

        playerState = (SIM_PLAY_CONTROL)msg.playOn;
        speed = SIM_CMD_PAUSE;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(SIM_PLAY_ON);
        out.writeRawData((char*)&msg, sizeof(simPlayOn));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        //CfgManager::Instance()->getTrackingController()->SendMsg(arr);
    }
}

void LLFReaderControlWidget::stop() {
    if (!btnStop->selected()) {
        resetButtons();
        btnStop->setSelected(true);

        //CfgManager::Instance()->getTrackingController()->getDataModel()->cleanModel();
        //CfgManager::Instance()->getTrackingController()->getDataModel()->releaseModel();

        simPlayOn msg;
        msg.playOn = SIM_CMD_STOP;
        speed = SIM_CMD_PAUSE;

        playerState = (SIM_PLAY_CONTROL)msg.playOn;

        QByteArray arr;

        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out.setByteOrder(QDataStream::LittleEndian);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out << qint16(0);
        out << quint8(SIM_PLAY_ON);
        out.writeRawData((char*)&msg, sizeof(simPlayOn));
        out.device()->seek(0);
        out << quint16(arr.size() - sizeof(quint16));

        //CfgManager::Instance()->getTrackingController()->SendMsg(arr);
    }
}

void LLFReaderControlWidget::setSpeed() {
    //if (!dir.isEmpty()) {
        LLFReaderCWButton *btn = (LLFReaderCWButton*) sender();
        if (!btn->selected() || (btn == btnDecSpeed || btn == btnIncSpeed || btn == btnToggledSpeed)) {
            resetButtons();
            btn->setSelected(true);

            simPlayOn msg;

            if ( btn == btnPause ) {
                speed = SIM_CMD_PAUSE;
            }
            else if ( btn == btnStart ) {
                speed = SIM_CMD_PLAY;
            }
            else if ( btn == btnIncSpeed ) {
                if (speed == SIM_CMD_PAUSE)
                    speed = SIM_CMD_HALF_SPEED;
                else if (speed == SIM_CMD_HALF_SPEED)
                    speed = SIM_CMD_PLAY;
                else {
                    speed <<= 1;
                }
                if (speed > SIM_CMD_8x)
                    speed = SIM_CMD_8x;
            }
            else if (btn == btnDecSpeed ) {
                if (speed == SIM_CMD_PAUSE || speed == SIM_CMD_HALF_SPEED)
                    speed = SIM_CMD_PAUSE;
                else if (speed == SIM_CMD_PLAY)
                    speed = SIM_CMD_HALF_SPEED;
                else if (speed == SIM_CMD_2x)
                    speed = SIM_CMD_PLAY;
                else {
                    speed >>= 1;
                }
            }
            else if (btn == btnToggledSpeed ) {
                if (speed == SIM_CMD_PAUSE)
                    speed = SIM_CMD_HALF_SPEED;
                else if (speed == SIM_CMD_HALF_SPEED)
                    speed = SIM_CMD_PLAY;
                else {
                    speed <<= 1;
                }
                if (speed > SIM_CMD_8x)
                    speed = SIM_CMD_PAUSE;
            }

            msg.playOn = speed;
            playerState = (SIM_PLAY_CONTROL)msg.playOn;

            QByteArray arr;

            QDataStream out(&arr, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_3);
            out.setByteOrder(QDataStream::LittleEndian);
            out.setFloatingPointPrecision(QDataStream::SinglePrecision);

            out << qint16(0);
            out << quint8(SIM_PLAY_ON);
            out.writeRawData((char*)&msg, sizeof(simPlayOn));
            out.device()->seek(0);
            out << quint16(arr.size() - sizeof(quint16));

            //CfgManager::Instance()->getTrackingController()->SendMsg(arr);
        }
    //}
}

void LLFReaderControlWidget::resetButtons() {
    //btnSeekStart->setSelected(false);
    btnPause->setSelected(false);
    btnStart->setSelected(false);
    btnIncSpeed->setSelected(false);
    //btnIncSpeed4x->setSelected(false);
    //btnIncSpeed10x->setSelected(false);
    btnDecSpeed->setSelected(false);
    btnStop->setSelected(false);
    //progressValue = 0;
    //logFileSize = 0;
}


void LLFReaderControlWidget::makeHide() {    
    hide();
}

void LLFReaderControlWidget::makeShow() {
    show();
}

void LLFReaderControlWidget::selectDir()
{
    /*QString str = QFileDialog::getOpenFileName(0, "Open File Registartion", "/usr/local/code", "*.bin");
    if (str.isEmpty())
        return;
    if (dir.isEmpty())
        dir = str;
    else {
        if (dir == str);
            //return;
        else
            dir = str;
    }    

    QFile file(dir);
    labDir->setText(file.fileName());
    if (!file.open(QIODevice::ReadOnly))    {
        qDebug()<<"Error opening file";
        return;
    }

    CfgManager::Instance()->getTrackingController()->getDataModel()->cleanModel();
    CfgManager::Instance()->getTrackingController()->getDataModel()->releaseModel();

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_3);
    in.setByteOrder(QDataStream::LittleEndian);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);

    RegFileHeader header;
    quint16 size;
    in >> size;
    in.readRawData((char *) &header, sizeof(RegFileHeader));
    timeval tv1;
    in.readRawData((char *) &tv1, sizeof(timeval));

    lineTime->setDateTime(QDateTime::fromTime_t(tv1.tv_sec));

    file.close();

    QByteArray arr1;

    QDataStream out1(&arr1, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_5_3);
    out1.setByteOrder(QDataStream::LittleEndian);
    out1.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out1 << qint16(0);
    out1 << quint8(SIM_CHANGE_FILE);
    out1 << dir;
    out1.device()->seek(0);
    out1 << quint16(arr1.size() - sizeof(quint16));



    CfgManager::Instance()->getTrackingController()->SendMsg(arr1);*/
}

void LLFReaderControlWidget::selectMsg(QListWidgetItem *item)
{
     auto iter = mapMsg.find(item->text());

     if (iter == mapMsg.end())
         return;

     SimMessageOn msg;
     msg.mesId = iter->second;
     msg.flagOn = item->isSelected();

     QByteArray arr1;

     QDataStream out1(&arr1, QIODevice::WriteOnly);
     out1.setVersion(QDataStream::Qt_5_3);
     out1.setByteOrder(QDataStream::LittleEndian);
     out1.setFloatingPointPrecision(QDataStream::SinglePrecision);

     out1 << qint16(0);
     out1 << quint8(SIM_MES_ON);
     out1.writeRawData((char*)&msg, sizeof(SimMessageOn));
     out1.device()->seek(0);
     out1 << quint16(arr1.size() - sizeof(quint16));

     //CfgManager::Instance()->getTrackingController()->SendMsg(arr1);
}

void LLFReaderControlWidget::selectAllMsg()
{
    bool flagChecked = btnSelectAll->isChecked();
    for(int i = 0; i < listMsg->count(); ++i)
    {
        QListWidgetItem* item = listMsg->item(i);
        item->setSelected(flagChecked);
    }

    for (auto iter = mapMsg.begin(); iter != mapMsg.end(); iter++) {
        SimMessageOn msg;
        msg.mesId = iter->second;
        msg.flagOn = flagChecked;

        QByteArray arr1;

        QDataStream out1(&arr1, QIODevice::WriteOnly);
        out1.setVersion(QDataStream::Qt_5_3);
        out1.setByteOrder(QDataStream::LittleEndian);
        out1.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out1 << qint16(0);
        out1 << quint8(SIM_MES_ON);
        out1.writeRawData((char*)&msg, sizeof(SimMessageOn));
        out1.device()->seek(0);
        out1 << quint16(arr1.size() - sizeof(quint16));

        //CfgManager::Instance()->getTrackingController()->SendMsg(arr1);
    }
}

void LLFReaderControlWidget::timeChanged() {

    SimMessageRewind msg;
    msg.timeStart.tv_sec = lineTime->dateTime().toTime_t();
    msg.timeStart.tv_usec = 0;

    QByteArray arr;

    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);

    out << qint16(0);
    out << quint8(SIM_RREWIND_FILE);
    out.writeRawData((char*)&msg, sizeof(SimMessageRewind));
    out.device()->seek(0);
    out << quint16(arr.size() - sizeof(quint16));

    //CfgManager::Instance()->getTrackingController()->SendMsg(arr);
}

void LLFReaderControlWidget::initMap()
{
    mapMsg.insert({"CMD_START_RADIATION_MESSAGE",1});
    mapMsg.insert({"CMD_CHANGE_RT_MESSAGE",2});
    mapMsg.insert({"RLSO_COMMAND_MESSAGE",6});
    mapMsg.insert({"RLSO_ANSWER_COMMAND_MESSAGE",7});
    mapMsg.insert({"RLSO_STATE_MESSAGE",8});
    mapMsg.insert({"RLSO_PLOT_MESSAGE",9});
    mapMsg.insert({"RLSO_AIM_MESSAGE",10});
    mapMsg.insert({"CP_PRIORITY_TRACK_MESSAGE",11});
    mapMsg.insert({"GK_COORDS_MESSAGE",20});
    mapMsg.insert({"COORDS_RAY_MESSAGE",21});
    mapMsg.insert({"MYO_TIME_SCANNING_MESSAGE",22});
    mapMsg.insert({"INS_MESSAGE",27});
    mapMsg.insert({"MYO_COORDINATES_TARGET_MESSAGE",28});
    mapMsg.insert({"MYO_CALIBRATION_MESSAGE",29});
    mapMsg.insert({"MYO_SETTINGS_MODE_MESSAGE",30});
    mapMsg.insert({"MYO_MANUAL_MODE_MESSAGE",31});
    mapMsg.insert({"MYO_INT_COMMAND_MESSAGE",32});
    mapMsg.insert({"MYO_QUERY_MESSAGE",33});
    mapMsg.insert({"MYO_INIT_MESSAGE",34});
    mapMsg.insert({"MYO_CONFIG_TARGET_MESSAGE",35});
    mapMsg.insert({"MYO_PARKIN_MESSAGE",36});
    mapMsg.insert({"MYO_READY_MESSAGE",37});
    mapMsg.insert({"RLSO_START_RAY_MESSAGE",39});
    mapMsg.insert({"RLSO_FINISH_RAY_MESSAGE",40});
    mapMsg.insert({"RLSO_AZIMUTH_SENSOR_MESSAGE",41});
    mapMsg.insert({"RLSO_GENERATOR_MESSAGE",42});
    mapMsg.insert({"RLSO_RTM_MESSAGE",43});
    mapMsg.insert({"RLSO_DRIVE_CMD_MESSAGE",44});
    mapMsg.insert({"RLSO_DRIVE_ANS_MESSAGE",45});
    mapMsg.insert({"RLSO_DSP_CONFIG_MESSAGE",46});
    mapMsg.insert({"RLSO_DSP_STATE_MESSAGE",47});
    mapMsg.insert({"RLSO_TIME_MESSAGE",48});
    mapMsg.insert({"RLSO_DSP_PARAMS_MESSAGE",49});
    mapMsg.insert({"RLSO_IMITATOR_CONFIG_MESSAGE",50});
    mapMsg.insert({"RLSO_ESCORT_AIM_MESSAGE",51});
    mapMsg.insert({"RLSO_IMITATOR_PLOT_MESSAGE",52});
    mapMsg.insert({"RLSO_ERASE_KTA_MESSAGE",53});
    mapMsg.insert({"RLSO_POI_DATA_MESSAGE",54});
    mapMsg.insert({"RLSO_AZ_ERROR_MESSAGE",55});
    mapMsg.insert({"RMO_OUTSIDE_COORD_TARGET_MESSAGE",110});
    mapMsg.insert({"RMO_OUTSIDE_CONFIG_TARGET_MESSAGE",111});
    mapMsg.insert({"SIM_GK_COORDS_MESSAGE",120});
    mapMsg.insert({"SIM_PWD_START_MESSAGE",121});
    mapMsg.insert({"SIM_PWD_STATE_MESSAGE",122});
    mapMsg.insert({"SIM_PWD_ANSWER",123});
    mapMsg.insert({"SIM_MES_ON",124});
    mapMsg.insert({"SIM_CHANGE_FILE",125});
    mapMsg.insert({"TM_MESSAGE",130});
    mapMsg.insert({"ALL_SYSTEM_HANDSHAKE",255});
}
