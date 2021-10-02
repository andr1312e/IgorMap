#ifndef MAPDEBUGGER_H
#define MAPDEBUGGER_H


#include "Widgets/basewidget.h"
#include "Math/bMath.h"

#include <QVector3D>
#include <QJsonDocument>
#include <QOpenGLBuffer>

class QComboBox;
class QCheckBox;

class MapDebugger : public BaseWidget
{
    struct PointPosition {
        PointPosition() {}
        QPointF geo, gauss, local, local2;
    };

    Q_OBJECT
public:
    MapDebugger(QWidget *parent = nullptr);

signals:
    void requestForNewMap(QJsonDocument doc);
    void moveCenterOnX(float vx);
    void moveCenterOnY(float vy);
    void userCenterViewGeo(QPointF centerGeo);
    void clearAllTilesOfMap();

    void getViewCenter();
    void infoForRender(QStringList paths, QVector<GLfloat> points);

public slots:
    void updateViewCenter(QVector3D center);
    void parseJSONDocument(QJsonDocument doc);

private:
    void initConversion();

private slots:
    void acceptButtonClicked();
    void clearButtonClicked();

    void movingButtonClicked();
    void rotateButtonClicked();

private:
    PointPosition placementPoint, currentCenter;
    QPointF middleMeridianPlacement, transferValues, ceneterInMyLocal;

    BaseLineEdit *latLineEdit, *longLineEdit,
                 *latCenterLineEdit, *longCenterLineEdit,
                 *azLineEdit,
                 *azRotateLineEdit, *movingLineEdit;

    QComboBox *layerCb;
    QCheckBox *repaintCheck;

    QPushButton *acceptButton, *clearButton,
                *upButton, *downButton,
                *leftButton, *rightButton,
                *ccwRotateButton, *cwRotateButton;

    QPointF refPoint, rlsPoint, rlsPointLocal;
    Conversion conversion;
};

#endif // MAPDEBUGGER_H
