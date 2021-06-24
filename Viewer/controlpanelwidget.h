#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QVector>

#include "global.h"
#include "basewidget.h"
#include "sectorsviewerwidget.h"

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
    ControlPanelButton(QWidget *parent = nullptr);
    void setIcon(const QString& notSelectedIconPath, const QString& selectedIconPath);
    bool isSelectedButton() { return isSelected; }
    void setSelectedButton(bool flag);

signals:
    void openCloseSignal();

private:


private:
    VectorOfIcons vectorOfIcons;
    qint8 currentIcon;
    bool isSelected;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};


class ControlPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelWidget(QWidget *parent = nullptr);
    void virtualOffset(QPoint point);

public slots:
    void changeButtonState(WidgetTypes type, bool open);
    void simpleChangeButtonStateOff(WidgetTypes type);
    void simpleChangeButtonStateOn(WidgetTypes type);

signals:
    void openWidgetSignal(WidgetTypes type);

private:
    void initButtonsAndWidgets();

private:
    const QRect mainBodyRect;

    ControlPanelButton *targetingButton, *fcButton, *dspButton, *trackButton,
                        *emittingButton, *rtButton, *respButton,
                        *historyButton, *ktaInfoButton, *customButton,
                        *colorSchemeButton, *snrButton;


protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // CONTROLPANELWIDGET_H
