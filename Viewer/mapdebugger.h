#ifndef MAPDEBUGGER_H
#define MAPDEBUGGER_H

#include <QWidget>
#include "basewidget.h"
#include "bMath.h"
#include <QVector3D>
#include <QJsonDocument>

class QComboBox;
class QCheckBox;

class MapDebugger : public BaseWidget
{
    Q_OBJECT
public:
    MapDebugger(QWidget *parent = nullptr);

signals:
    void requestForNewMap(QJsonDocument doc);
    void moveCenterOnX(float vx);
    void moveCenterOnY(float vy);

public slots:
    void updateViewCenter(QVector3D center);

private:
    void initConversion();

private slots:
    void acceptButtonClicked();
    void clearButtonClicked();

    void movingButtonClicked();
    void rotateButtonClicked();

private:
    const QPointF placementPoint;

    BaseLineEdit *latLineEdit, *longLineEdit,
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

    QVector3D currentCenter;
};

#endif // MAPDEBUGGER_H
