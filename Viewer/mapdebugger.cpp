#include "mapdebugger.h"
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLayout>
#include <QJsonObject>

MapDebugger::MapDebugger(QWidget *parent) : BaseWidget(WidgetTypes::MapDebug, parent),
    placementPoint(49.4824, 79.)
{    
    setTitle("Отладка карты");

    initConversion();

    QLabel *latLabel = new QLabel("Широта");
    QLabel *longLabel = new QLabel("Долгота");
    latLineEdit = new BaseLineEdit(40, 80, 6, this);
    //latLineEdit->setText(QString::number(placementPoint.x(), 'f', 6));
    longLineEdit = new BaseLineEdit(26, 180, 6, this);
    //longLineEdit->setText(QString::number(placementPoint.y(), 'f', 6));

    QLabel *layerLabel = new QLabel("Слой     ");
    //layerLabel->setFixedWidth(80);
    layerCb = new QComboBox();
    layerCb->setMaxCount(11);
    for (quint8 index = 1; index < 12; index++) {
        layerCb->addItem(QString::number(index));
    }
    //layerCb->setCurrentIndex(layerCb->findText("9"));

    QLabel *azLabel = new QLabel("Азимут ");
    azLineEdit = new BaseLineEdit(RealValidator::Degrees, this);
    //azLineEdit->setText(QString::number(0));

    repaintCheck = new QCheckBox("Перерисовать");

    acceptButton = new QPushButton("Apply");
    clearButton = new QPushButton("Rst");

    clearButtonClicked();

    QHBoxLayout *latLayout = new QHBoxLayout();
    latLayout->addWidget(latLabel);
    latLayout->addWidget(latLineEdit);
    latLayout->addStretch(1);

    QHBoxLayout *longLayout = new QHBoxLayout();
    longLayout->addWidget(longLabel);
    longLayout->addWidget(longLineEdit);
    longLayout->addStretch(1);

    QHBoxLayout *layerLayout = new QHBoxLayout();
    layerLayout->addWidget(layerLabel);
    layerLayout->addWidget(layerCb);
    layerLayout->addStretch(1);

    QHBoxLayout *azLayout = new QHBoxLayout();
    azLayout->addWidget(azLabel);
    azLayout->addWidget(azLineEdit);
    azLayout->addStretch(1);

    QHBoxLayout *acceptLayout = new QHBoxLayout();
    //acceptLayout->addStretch(1);
    acceptLayout->addWidget(acceptButton);
    acceptLayout->addWidget(clearButton);

    QVBoxLayout *positionLayout = new QVBoxLayout();
    positionLayout->setContentsMargins(margin);
    positionLayout->addLayout(latLayout);
    positionLayout->addLayout(longLayout);
    positionLayout->addLayout(layerLayout);
    positionLayout->addLayout(azLayout);
    positionLayout->addWidget(repaintCheck);
    positionLayout->addLayout(acceptLayout);

    QGroupBox *positionGroupBox = new QGroupBox("Позиция");
    positionGroupBox->setLayout(positionLayout);

    upButton = new QPushButton("Вверх");
    downButton = new QPushButton("Вниз");
    leftButton = new QPushButton("Влево");
    rightButton = new QPushButton("Вправо");

    ccwRotateButton = new QPushButton("CCW");
    cwRotateButton = new QPushButton("CW");

    QLabel *movingFirstLabel = new QLabel("на");
    QLabel *movingSecondLabel = new QLabel("км");

    QLabel *rotateFirstLabel = new QLabel("на");
    QLabel *rotateSecondLabel = new QLabel("град");

    azRotateLineEdit = new BaseLineEdit(0, 90, 2, this);
    azRotateLineEdit->setText(QString::number(1, 'f', 2));
    movingLineEdit = new BaseLineEdit(0, 300, 2, this);
    movingLineEdit->setText(QString::number(10, 'f', 0));

    QHBoxLayout *leftRightMovingLayout = new QHBoxLayout();
    leftRightMovingLayout->addWidget(leftButton);
    leftRightMovingLayout->addWidget(rightButton);

    QVBoxLayout *upDownMovingLayout = new QVBoxLayout();
    upDownMovingLayout->addWidget(upButton);
    upDownMovingLayout->addLayout(leftRightMovingLayout);
    upDownMovingLayout->addWidget(downButton);

    QHBoxLayout *upDownMovingWithStretchLayout = new QHBoxLayout();
    upDownMovingWithStretchLayout->addLayout(upDownMovingLayout);
    upDownMovingWithStretchLayout->addStretch(1);

    QHBoxLayout *kmMovingLayout = new QHBoxLayout();
    kmMovingLayout->addWidget(movingFirstLabel);
    kmMovingLayout->addWidget(movingLineEdit);
    kmMovingLayout->addWidget(movingSecondLabel);

    QVBoxLayout *movingLayout = new QVBoxLayout();
    movingLayout->setContentsMargins(margin);
    movingLayout->addLayout(upDownMovingWithStretchLayout);
    movingLayout->addLayout(kmMovingLayout);

    QGroupBox *movingGroupBox = new QGroupBox("Перемещение");
    movingGroupBox->setLayout(movingLayout);

    QHBoxLayout *buttonRotateLayout = new QHBoxLayout();
    buttonRotateLayout->addWidget(ccwRotateButton);
    buttonRotateLayout->addWidget(cwRotateButton);
    buttonRotateLayout->addStretch(1);

    QHBoxLayout *degreeRotateLayout = new QHBoxLayout();
    degreeRotateLayout->addWidget(rotateFirstLabel);
    degreeRotateLayout->addWidget(azRotateLineEdit);
    degreeRotateLayout->addWidget(rotateSecondLabel);
    degreeRotateLayout->addStretch(1);

    QVBoxLayout *rotateLayout = new QVBoxLayout();
    rotateLayout->setContentsMargins(margin);
    rotateLayout->addLayout(buttonRotateLayout);
    rotateLayout->addLayout(degreeRotateLayout);
    rotateLayout->addStretch(1);

    QGroupBox *rotateGroupBox = new QGroupBox("Поворот");
    rotateGroupBox->setLayout(rotateLayout);

    QVBoxLayout *debugMenuLayout = new QVBoxLayout();
    debugMenuLayout->addWidget(movingGroupBox);
    debugMenuLayout->addWidget(rotateGroupBox);

    QGroupBox *debugGroupBox = new QGroupBox("Меню отладки");
    debugGroupBox->setLayout(debugMenuLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(positionGroupBox);
    mainLayout->addWidget(debugGroupBox);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    connect(acceptButton, &QPushButton::released, this, &MapDebugger::acceptButtonClicked);
    connect(clearButton, &QPushButton::released, this, &MapDebugger::clearButtonClicked);

    connect(upButton, &QPushButton::released, this, &MapDebugger::movingButtonClicked);
    connect(downButton, &QPushButton::released, this, &MapDebugger::movingButtonClicked);
    connect(leftButton, &QPushButton::released, this, &MapDebugger::movingButtonClicked);
    connect(rightButton, &QPushButton::released, this, &MapDebugger::movingButtonClicked);

    connect(ccwRotateButton, &QPushButton::released, this, &MapDebugger::rotateButtonClicked);
    connect(cwRotateButton, &QPushButton::released, this, &MapDebugger::rotateButtonClicked);
}

void MapDebugger::updateViewCenter(QVector3D center)
{
    currentCenter = center;

    acceptButtonClicked();
}

void MapDebugger::initConversion()
{
    conversion.Gen_point_grad = placementPoint;
    conversion.Gen_point_gauss = conversion.GeoToGauss(placementPoint.x(), placementPoint.y());
}

void MapDebugger::acceptButtonClicked()
{
    QPointF point(currentCenter.x(), currentCenter.y());
    qDebug() << point;
    point = conversion.Loc2Gauss(point);
    point = conversion.GaussToGeo(point);

    latLineEdit->setText(QString::number(point.x(), 'f', 6));
    longLineEdit->setText(QString::number(point.y(), 'f', 6));

    QJsonObject json;

    json["latitude"] = point.x();
    json["longtitude"] = point.y();
    json["layer"] = layerCb->currentText().toInt();
    json["azimut"] = azLineEdit->text().toFloat();
    json["repaint"] = repaintCheck->isChecked();

    emit requestForNewMap(QJsonDocument(json));
}

void MapDebugger::clearButtonClicked()
{
    latLineEdit->setText(QString::number(placementPoint.x(), 'f', 6));
    longLineEdit->setText(QString::number(placementPoint.y(), 'f', 6));
    /////
    layerCb->setCurrentIndex(layerCb->findText("10"));
    azLineEdit->setText(QString::number(0));

    repaintCheck->setChecked(false);
}

void MapDebugger::movingButtonClicked()
{
    QPushButton *button = static_cast<QPushButton *>(sender());

    float dDist = movingLineEdit->text().toFloat();
    if (button == upButton) {
        emit moveCenterOnY(dDist);
    }
    else if (button == downButton) {
        emit moveCenterOnY(-dDist);
    }
    else if (button == leftButton) {
        emit moveCenterOnX(-dDist);
    }
    else if (button == rightButton) {
        emit moveCenterOnX(dDist);
    }
}

void MapDebugger::rotateButtonClicked()
{
    QPushButton *button = static_cast<QPushButton *>(sender());
    float az = azLineEdit->text().toFloat();
    float dAz = azRotateLineEdit->text().toFloat();

    if (button == ccwRotateButton) {
        az = CorrectPlus(az, -dAz);
    }
    else if (button == cwRotateButton){
        az = CorrectPlus(az, dAz);
    }

    azLineEdit->setText(QString::number(az, 'f', 2));
    acceptButtonClicked();
}
