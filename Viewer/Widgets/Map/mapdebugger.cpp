#include "mapdebugger.h"
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLayout>
#include <QJsonObject>
#include <QElapsedTimer>
#include <QtMath>


MapDebugger::MapDebugger(QWidget *parent) : BaseWidget(WidgetTypes::MapDebug, parent)

{    
    placementPoint.geo = QPointF(56.966470, 42.257470);
    placementPoint.gauss = conversion.GeoToGauss(placementPoint.geo.x(), placementPoint.geo.y());

    setTitle("Отладка карты");

    initConversion();

    QLabel *latLabel = new QLabel("Широта");
    QLabel *longLabel = new QLabel("Долгота");
    latLineEdit = new BaseLineEdit(-180, 180, 6, this);
    latLineEdit->setReadOnly(true);
    //latLineEdit->setText(QString::number(placementPoint.x(), 'f', 6));
    longLineEdit = new BaseLineEdit(-180, 180, 6, this);
    longLineEdit->setReadOnly(true);
    //longLineEdit->setText(QString::number(placementPoint.y(), 'f', 6));

    QLabel *lat2Label = new QLabel("Широта");
    QLabel *long2Label = new QLabel("Долгота");
    latCenterLineEdit = new BaseLineEdit(-180, 180, 6, this);
    //latLineEdit->setText(QString::number(placementPoint.x(), 'f', 6));
    longCenterLineEdit = new BaseLineEdit(-180, 180, 6, this);
    //longLineEdit->setText(QString::number(placementPoint.y(), 'f', 6));

    QLabel *layerLabel = new QLabel("Слой     ");
    //layerLabel->setFixedWidth(80);
    layerCb = new QComboBox();
    layerCb->setMaxCount(11);
    for (quint8 index = 5; index < 12; index++) {
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
    latCenterLineEdit->setText(QString::number(placementPoint.geo.x(), 'f', 6));
    longCenterLineEdit->setText(QString::number(placementPoint.geo.y(), 'f', 6));

    QHBoxLayout *latLayout = new QHBoxLayout();
    latLayout->addWidget(latLabel);
    latLayout->addWidget(latLineEdit);
    latLayout->addStretch(1);

    QHBoxLayout *longLayout = new QHBoxLayout();
    longLayout->addWidget(longLabel);
    longLayout->addWidget(longLineEdit);
    longLayout->addStretch(1);

    QHBoxLayout *lat2Layout = new QHBoxLayout();
    lat2Layout->addWidget(lat2Label);
    lat2Layout->addWidget(latCenterLineEdit);
    lat2Layout->addStretch(1);

    QHBoxLayout *long2Layout = new QHBoxLayout();
    long2Layout->addWidget(long2Label);
    long2Layout->addWidget(longCenterLineEdit);
    long2Layout->addStretch(1);

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
    positionLayout->addLayout(lat2Layout);
    positionLayout->addLayout(long2Layout);
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
    //mainLayout->addWidget(debugGroupBox);
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
    ceneterInMyLocal = QPointF(center.x(), center.y());
    currentCenter.local = QPointF(placementPoint.local.x() + center.y() * 1000,
                                  placementPoint.local.y() + center.x() * 1000);//center * 1000;

    currentCenter.gauss = conversion.Loc2Gauss(currentCenter.local);
    currentCenter.geo = conversion.GaussToGeo(currentCenter.gauss);

    //qDebug() << center;

//    QPointF point(placementPoint.local.x() + currentCenter.y(),
//                  placementPoint.local.y() + currentCenter.x());
    //qDebug() << point;
    //QElapsedTimer frame;
    //frame.start();
//    point = conversion.Loc2Gauss(point);
//    point = conversion.GaussToGeo(point);
    //QPointF point2(point.y(),point.x());
    //point = point2;
    //qDebug() << frame.nsecsElapsed() / 1000 << " мкс";

    latCenterLineEdit->setText(QString::number(currentCenter.geo.x(), 'f', 6));
    longCenterLineEdit->setText(QString::number(currentCenter.geo.y(), 'f', 6));

    acceptButtonClicked();
}

void MapDebugger::parseJSONDocument(QJsonDocument doc)
{
    if (doc.isEmpty())
        return;

    QJsonObject json = doc.object();
    QStringList filePaths;
//    s={
//        ":/Map/Resources/Map/0_0.png",
//        ":/Map/Resources/Map/0_1.png",
//        ":/Map/Resources/Map/0_2.png",
//        ":/Map/Resources/Map/1_0.png",
//        ":/Map/Resources/Map/1_1.png",
//        ":/Map/Resources/Map/1_2.png",
//        ":/Map/Resources/Map/2_0.png",
//        ":/Map/Resources/Map/2_1.png",
//        ":/Map/Resources/Map/2_2.png",
//    };
    if (json.contains("filePaths") && json["filePaths"].isArray()) {
        filePaths = json["filePaths"].toVariant().toStringList();
    }
    QSizeF firstTileSize, secondTileSize, thirdTileSize;

    float lat4;
    if (json.contains("w1") && json["w1"].isDouble()) {
        firstTileSize.setWidth(json["w1"].toDouble());
    }
    if (json.contains("h1") && json["h1"].isDouble()) {
        firstTileSize.setHeight(json["h1"].toDouble());
    }
    if (json.contains("w2") && json["w2"].isDouble()) {
        secondTileSize.setWidth(json["w2"].toDouble());
    }
    if (json.contains("h2") && json["h2"].isDouble()) {
        secondTileSize.setHeight(json["h2"].toDouble());
    }
    if (json.contains("w3") && json["w3"].isDouble()) {
        thirdTileSize.setWidth(json["w3"].toDouble());
    }
    if (json.contains("h3") && json["h3"].isDouble()) {
        thirdTileSize.setHeight(json["h3"].toDouble());
    }
    if (json.contains("w4") && json["w4"].isDouble()) {
        lat4 = json["w4"].toDouble();
    }

    QPointF leftBottomCenterRect, rightBottomCenterRect, leftTopCenterRect, rightTopCenterRect;
    if (json.contains("p1_lat") && json["p1_lat"].isDouble()) {
        leftBottomCenterRect.setX(json["p1_lat"].toDouble());
    }
    if (json.contains("p1_long") && json["p1_long"].isDouble()) {
        leftBottomCenterRect.setY(json["p1_long"].toDouble());
    }
    if (json.contains("p2_lat") && json["p2_lat"].isDouble()) {
        rightTopCenterRect.setX(json["p2_lat"].toDouble());
    }
    if (json.contains("p2_long") && json["p2_long"].isDouble()) {
        rightTopCenterRect.setY(json["p2_long"].toDouble());
    }
    rightBottomCenterRect.rx() = leftBottomCenterRect.x();
    rightBottomCenterRect.ry() = rightTopCenterRect.y();
    leftTopCenterRect.rx() = rightTopCenterRect.x();
    leftTopCenterRect.ry() = leftBottomCenterRect.y();

    quint8 sideOrientation;
    PointPosition pointOfSideOfCenterRect;

    QPointF leftBottomCenterRectGauss(conversion.GeoToGauss(leftBottomCenterRect.x(), leftBottomCenterRect.y())),
            rightBottomCenterRectGauss(conversion.GeoToGauss(rightBottomCenterRect.x(), rightBottomCenterRect.y())),
            leftTopCenterRectGauss(conversion.GeoToGauss(leftTopCenterRect.x(), leftTopCenterRect.y())),
            rightTopCenterRectGauss(conversion.GeoToGauss(rightTopCenterRect.x(), rightTopCenterRect.y()));
    quint8 leftBottomCenterRectGaussZone = qFloor(leftBottomCenterRectGauss.y() / 1000000),
            rightBottomCenterRectGaussZone = qFloor(rightBottomCenterRectGauss.y() / 1000000),
            leftTopCenterRectGaussZone = qFloor(leftTopCenterRectGauss.y() / 1000000),
            rightTopCenterRectGaussZone = qFloor(rightTopCenterRectGauss.y() / 1000000),
            viewCenterGaussZone = qFloor(currentCenter.gauss.y() / 1000000);
    //quint8 differenceInZone = 0;
    //while (true) {
        //if (abs(viewCenterGaussZone - leftBottomCenterRectGaussZone) == differenceInZone) {
            sideOrientation = 0;//SideOfQuadrangle::LeftBottom;
            pointOfSideOfCenterRect.geo = leftBottomCenterRect;
            pointOfSideOfCenterRect.gauss = leftBottomCenterRectGauss;
            pointOfSideOfCenterRect.local = conversion.Gauss2LocUpdate(leftBottomCenterRectGauss);
            pointOfSideOfCenterRect.local2 = conversion.Gauss2Loc(leftBottomCenterRectGauss);
//            break;
//        }
//        else if (abs(viewCenterGaussZone - rightBottomCenterRectGaussZone) == differenceInZone) {
//            sideOrientation = 1;//SideOfQuadrangle::RightBottom;
//            pointOfSideOfCenterRect.geo = rightBottomCenterRect;
//            pointOfSideOfCenterRect.gauss = rightBottomCenterRectGauss;
//            pointOfSideOfCenterRect.local = conversion.Gauss2LocUpdate(rightBottomCenterRectGauss);
//            //pointOfSideOfCenterRect.local2 = conversion.Gauss2Loc(rightBottomCenterRectGauss);
//            break;
//        }
//        else if (abs(viewCenterGaussZone - leftTopCenterRectGaussZone) == differenceInZone) {
//            sideOrientation = 2;//SideOfQuadrangle::LeftTop;
//            pointOfSideOfCenterRect.geo = leftTopCenterRect;
//            pointOfSideOfCenterRect.gauss = leftTopCenterRectGauss;
//            pointOfSideOfCenterRect.local = conversion.Gauss2LocUpdate(leftTopCenterRectGauss);
//            //pointOfSideOfCenterRect.local2 = conversion.Gauss2Loc(leftTopCenterRectGauss);
//            break;
//        }
//        else if (abs(viewCenterGaussZone - rightTopCenterRectGaussZone) == differenceInZone) {
//            sideOrientation = 3;//SideOfQuadrangle::RightTop;
//            pointOfSideOfCenterRect.geo = rightTopCenterRect;
//            pointOfSideOfCenterRect.gauss = rightTopCenterRectGauss;
//            pointOfSideOfCenterRect.local = conversion.Gauss2LocUpdate(rightTopCenterRectGauss);
//            //pointOfSideOfCenterRect.local2 = conversion.Gauss2Loc(rightTopCenterRectGauss);
//            break;
//        }
//        differenceInZone++;
//    }
//    sideOrientation = 0;//SideOfQuadrangle::LeftBottom;
//    pointOfSideOfCenterRect.geo = leftBottomCenterRect;
//    pointOfSideOfCenterRect.gauss = leftBottomCenterRectGauss;
//    pointOfSideOfCenterRect.local = conversion.Gauss2Loc(leftBottomCenterRectGauss);

    QPointF leftBottomTemp = conversion.Gauss2LocUpdate(leftBottomCenterRectGauss),
            rightBottomTemp = conversion.Gauss2LocUpdate(rightBottomCenterRectGauss),
            leftTopTemp = conversion.Gauss2LocUpdate(leftTopCenterRectGauss),
            rightTopTemp = conversion.Gauss2LocUpdate(rightTopCenterRectGauss);

    QPointF _leftBottomMyLocal = QPointF((leftBottomTemp.y() - placementPoint.local.y()) / 1000.,
                                        (leftBottomTemp.x() - placementPoint.local.x()) / 1000.),
            _rightBottomMyLocal = QPointF((rightBottomTemp.y() - placementPoint.local.y()) / 1000.,
                                         (rightBottomTemp.x() - placementPoint.local.x()) / 1000.),
            _leftTopMyLocal = QPointF((leftTopTemp.y() - placementPoint.local.y()) / 1000.,
                                     (leftTopTemp.x() - placementPoint.local.x()) / 1000.),
            _rightTopMyLocal = QPointF((rightTopTemp.y() - placementPoint.local.y()) / 1000.,
                                      (rightTopTemp.x() - placementPoint.local.x()) / 1000.);




    QVector<GLfloat> resultVector;

    //QPointF recalcCenterView(vectorOfCenterView.x(), vectorOfCenterView.y());
    QPointF recalcCenterView((pointOfSideOfCenterRect.local.y() - placementPoint.local.y()) / 1000.,
                             (pointOfSideOfCenterRect.local.x() - placementPoint.local.x()) / 1000.);

    if (sideOrientation == 0) {
        recalcCenterView = QPointF(recalcCenterView.x() + secondTileSize.width() / 2.,
                                   recalcCenterView.y() + secondTileSize.height() / 2.);
    }
    else if (sideOrientation == 1) {
        recalcCenterView = QPointF(recalcCenterView.x() - secondTileSize.width() / 2.,
                                   recalcCenterView.y() + secondTileSize.height() / 2.);
    }
    else if (sideOrientation == 2) {
        recalcCenterView = QPointF(recalcCenterView.x() + thirdTileSize.width() / 2.,
                                   recalcCenterView.y() - secondTileSize.height() / 2.);
    }
    else if (sideOrientation == 3) {
        recalcCenterView = QPointF(recalcCenterView.x() - thirdTileSize.width() / 2.,
                                   recalcCenterView.y() - secondTileSize.height() / 2.);
    }
    //qDebug() << ceneterInMyLocal;
    //qDebug() << recalcCenterView << sideOrientation;

    //QVector<GLfloat> resultVector;

    qreal widthCenterGeo = leftBottomCenterRect.y() - rightBottomCenterRect.y(), heightCenterGeo = rightTopCenterRect.x() - rightBottomCenterRect.x();
    qreal widthCenterTranslate = secondTileSize.width() / widthCenterGeo, heightCenterTranslate = secondTileSize.height() / heightCenterGeo;
    qreal dLat = currentCenter.geo.x() - leftBottomCenterRect.x(), dLong = currentCenter.geo.y() - leftBottomCenterRect.y();
    qreal offsetX = widthCenterTranslate * dLong, offsetY = heightCenterTranslate * dLat;

    //QPointF recalcCenterView(ceneterInMyLocal.x() + offsetX,
    //                         ceneterInMyLocal.y() - offsetY);


    QPointF leftBottom, leftTop, rightBottom, rightTop;

    //1
    leftBottom.setX(recalcCenterView.x() - 3. * firstTileSize.width() / 2.);
    leftBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    leftTop.setX(recalcCenterView.x() - 3 * secondTileSize.width() / 2.);
    leftTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightBottom.setX(recalcCenterView.x() - firstTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(recalcCenterView.x() - secondTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //2
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + firstTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(recalcCenterView.x() + secondTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //3
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + 3. * firstTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2. - firstTileSize.height());

    rightTop.setX(recalcCenterView.x() + 3. * secondTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //4
    leftBottom.setX(recalcCenterView.x() - 3. * secondTileSize.width() / 2.);
    leftBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    leftTop.setX(recalcCenterView.x() - 3 * thirdTileSize.width() / 2.);
    leftTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightBottom.setX(recalcCenterView.x() - secondTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() - thirdTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //5
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + secondTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + thirdTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //6
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + 3. * secondTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() - secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + 3. * thirdTileSize.width() / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //7
    leftBottom.setX(recalcCenterView.x() - 3. * thirdTileSize.width() / 2.);
    leftBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    leftTop.setX(recalcCenterView.x() - 3 * lat4 / 2.);
    leftTop.setY(recalcCenterView.y() + secondTileSize.height() / 2. + thirdTileSize.height());

    rightBottom.setX(recalcCenterView.x() - thirdTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() - lat4 / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //8
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + thirdTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + lat4 / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //9
    leftBottom = rightBottom;
    leftTop = rightTop;

    rightBottom.setX(recalcCenterView.x() + 3. * thirdTileSize.width() / 2.);
    rightBottom.setY(recalcCenterView.y() + secondTileSize.height() / 2.);

    rightTop.setX(recalcCenterView.x() + 3. * lat4 / 2.);
    rightTop.setY(recalcCenterView.y() + secondTileSize.height() / 2.  + thirdTileSize.height());

    resultVector << leftBottom.x() << leftBottom.y()
                 << rightBottom.x() << rightBottom.y()
                 << rightTop.x() << rightTop.y()

                 << leftBottom.x() << leftBottom.y()
                 << rightTop.x() << rightTop.y()
                 << leftTop.x() << leftTop.y();

    //qDebug() << recalcCenterView;

    emit infoForRender(filePaths, resultVector);

}

void MapDebugger::initConversion()
{
    middleMeridianPlacement = QPointF(placementPoint.geo.x(), qFloor(placementPoint.geo.y() / 6.) * 6 + 3);

    conversion.Gen_point_grad = middleMeridianPlacement;
    conversion.Gen_point_gauss = conversion.GeoToGauss(middleMeridianPlacement.x(), middleMeridianPlacement.y());

    placementPoint.local = conversion.Gauss2Loc(placementPoint.gauss);

    emit getViewCenter();

    //emit userCenterViewGeo(placementPoint);

    /*QPointF point(69.338122, 88.133201);
    point = conversion.GeoToGauss(point.x(), point.y());
    point = conversion.Gauss2Loc(point);
    point /= 1000.;*/


    /*QPointF point2(1670,1252);
    double dist = sqrt(pow(point2.x(),2) + pow(point2.y(),2));
    point2 *= 1000.;
    point2 = conversion.Loc2Gauss(point2);
    point2 = conversion.GaussToGeo(point2);

    double R=6371; // радиус Земли в км.
    double lat2 = point2.x(), lat1 = placementPoint.x(), lon1 = placementPoint.y(), lon2 = point2.y();
    double lat=(lat2-lat1)*(M_PI/180);
    double lon=(lon2-lon1)*(M_PI/180);
    double rez=sin(lat/2)*sin(lat/2)+cos(lat1*(M_PI/180))*cos(lat2*(M_PI/180))*sin(lon/2)*sin(lon/2);
    double d=2*R*atan2(sqrt(rez), sqrt(1-rez));*/

    /*QPointF point3;
    point3 = conversion.GeoToGauss(point2.x(), point2.y());
    point3 = conversion.Gauss2Loc(point3);
    point3 /= 1000.;

    dist = sqrt(pow(point.x(),2) + pow(point.y(),2));*/

    //QPointF point4;
}

void MapDebugger::acceptButtonClicked()
{
    QPointF point(latCenterLineEdit->text().toFloat(), longCenterLineEdit->text().toFloat());
    qDebug() << point;
    /*point *= 1000.;
    point = conversion.Loc2Gauss(point);
    point = conversion.GaussToGeo(point);*/

    /*latCenterLineEdit->setText(QString::number(point.x(), 'f', 6));
    longCenterLineEdit->setText(QString::number(point.y(), 'f', 6));*/

    QJsonObject json;

    json["latitude"] = point.x();
    json["longtitude"] = point.y();
    json["layer"] = layerCb->currentText().toInt();
    json["azimut"] = azLineEdit->text().toFloat();
    json["repaint"] = repaintCheck->isChecked();

    emit requestForNewMap(QJsonDocument(json));
    emit userCenterViewGeo(point);

    if (repaintCheck->isChecked()) {
        repaintCheck->setChecked(false);
        emit clearAllTilesOfMap();
    }
}

void MapDebugger::clearButtonClicked()
{
    latLineEdit->setText(QString::number(placementPoint.geo.x(), 'f', 6));
    longLineEdit->setText(QString::number(placementPoint.geo.y(), 'f', 6));
    //latCenterLineEdit->setText(QString::number(placementPoint.x(), 'f', 6));
    //longCenterLineEdit->setText(QString::number(placementPoint.y(), 'f', 6));
    layerCb->setCurrentIndex(layerCb->findText("8"));
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
