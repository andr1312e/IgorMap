#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QVector>

#include "Widgets/basewidget.h"

enum ButtonIDs {
    MapButton,
};

struct ButtonIcons {
    ButtonIcons() : iconNotSelected(), iconSelected() {}
    ButtonIcons(const QString& notSelectedIconPath, const QString& selectedIconPath) {
        iconNotSelected.load(notSelectedIconPath);
        iconSelected.load(selectedIconPath);
    }

    QPixmap iconNotSelected, iconSelected;
};

using VectorOfIcons = QVector< ButtonIcons >;
class ControlPanelButton : public QWidget
{
    Q_OBJECT

public:
    ControlPanelButton(ButtonIDs _id,QWidget *parent = nullptr);
    void setIcon(const QString& notSelectedIconPath, const QString& selectedIconPath);
    bool isSelectedButton() { return isSelected; }
    void setSelectedButton(bool flag);

    ButtonIDs getButtonID() const;
    quint8 getWP() const;
    void setWP(quint8 WP);

private:
    void initContextMenu();

private slots:
    void userSetWP(QString currentWorkPoint);

signals:
    void openCloseSignal();
    void clicked();


private:
    ButtonIDs buttonId;
    VectorOfIcons vectorOfIcons;
    qint8 currentIcon;
    bool isSelected;

    quint8 workPoint, userWorkPoint;
    QMenu *contextMenu;

protected:
    void paintEvent(QPaintEvent *event) override;
};


class ControlPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelWidget(QWidget *parent = nullptr);
    void virtualOffset(QPoint point);

public slots:
    void simpleChangeButtonStateOff(WidgetTypes type);
    void simpleChangeButtonStateOn(WidgetTypes type);

signals:
    void openWidgetSignal(WidgetTypes type);
    void sendCommand(QByteArray msg);

private:
    void initButtonsAndWidgets();

private:
    const QRect mainBodyRect;

    ControlPanelButton  *mapButton;


protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // CONTROLPANELWIDGET_H
