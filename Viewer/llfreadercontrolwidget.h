#ifndef LLFREADERCONTROLWIDGET_H
#define LLFREADERCONTROLWIDGET_H

#include "basewidget.h"
#include "TcpHandler/datamessage.h"
#include <QPushButton>
#include <QComboBox>
#include <QWidget>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QTableWidget>
#include <map>
#include <QListWidget>
#include <QDateTimeEdit>

typedef std::map<QString, int> MapMsg;


enum LLFREADER_CONTROL_STATE {
    LLFRC_DISPLAY_HISTORY,
    LLFRC_DISPLAY_TRACK
};

enum BTN_TYPE{
    BTN_NONE,
    BTN_FORWARD_SPEED,
};

class LLFRSlider : public QSlider {
    Q_OBJECT

public:
    LLFRSlider()
    {
        connect(this,SIGNAL(sliderPressed()),this,SLOT(sliderPressed()));
        connect(this,SIGNAL(sliderReleased()),this,SLOT(sliderReleased()));
    }
    void setValueWithIf(int val)
    {
        if (!isSliderMoved)
            this->setValue(val);
    }
    void resetFlag()
    {
        isSliderMoved = false;
    }

signals:
    void PosChanged(int);

public slots:
    void sliderPressed() { isSliderMoved = true; }
    void sliderReleased()
    {
        int val = this->value();
        emit PosChanged(val);
        isSliderMoved = false;
    }

protected:
    void mousePressEvent(QMouseEvent *ev);

private:
    bool isSliderMoved;



};

class LLFReaderCWButton : public QPushButton {
    Q_OBJECT

public:
    LLFReaderCWButton();
    void setIcon(QString notSelectedIconPath, QString selectedIconPath);
    bool selected() { return isSelected; }
    void setSelected(bool sel) { isSelected = sel; }
    void setType(BTN_TYPE _type) { type = _type; setFixedSize(50, 30);}

protected:
    virtual void paintEvent(QPaintEvent *evt);

private:
    bool isSelected;
    QPixmap iconNotSelected;
    QPixmap iconSelected;
    BTN_TYPE type = BTN_NONE;
};

class LLFReaderControlWidget : public BaseWidget
{
    Q_OBJECT

public:
    LLFReaderControlWidget(BaseWidget *parent = 0);
    void makeShow();
    void makeHide();
    void updateCurrentPos(timeval &tv, int curpos);
    void resizeWidget(int w, int h);
    void moveWidget(int x, int y);
    SIM_PLAY_CONTROL getPlayerState() { return playerState; }
    int getSpeed() { return speed; }

public slots:
    void selectDir();
    void selectMsg(QListWidgetItem *item);
    void selectAllMsg();
    void timeChanged();

private:
    QString dir;
    QPushButton *btnSetDir;
    QLabel *labDir;
    MapMsg mapMsg;
    QListWidget *listMsg;
    QPushButton *btnSelectAll;
    QPushButton *btnAccept;

    LLFReaderCWButton *btnStart;
    LLFReaderCWButton *btnPause;
    LLFReaderCWButton *btnDecSpeed;
    LLFReaderCWButton *btnStop;
    LLFReaderCWButton *btnIncSpeed;
    LLFReaderCWButton *btnToggledSpeed;
    QDateTimeEdit *lineTime;
    SIM_PLAY_CONTROL playerState = SIM_CMD_STOP;
    int speed = SIM_CMD_PAUSE;

    void lockControls(bool reading);
    void unlockControls(bool reading);


private slots:
    void pause();
    void setSpeed();
    void stop();

private:
    void initMap();
    void resetButtons();

};

#endif // LLFREADERCONTROLWIDGET_H
