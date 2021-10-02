#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>
#include "../CommonEntities/global.h"
#include "math.h"

class QMouseEvent;
class QPixmap;
class QMargins;

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    BaseWidget(WidgetTypes wgtT, QWidget *parent = 0);
    virtual ~BaseWidget();
    void setTitle(QString title);    
    static void triggeredBackgroundColor(bool isBlackTheme);
    void makeHide();
    void makeShow();
    void setBlockResizing(bool flag);

public slots:
    void openCloseWidget();

public:
    static QColor backgroundColor;

private:
    QPixmap *resizeOnIcon;
    QPixmap *resizeOffIcon;
    QPixmap *exitOnIcon;
    QPixmap *exitOffIcon;
    bool isResized;
    bool isExit;

    ProgramWorkMode::Mode programWorkMode;

    void Init();

signals:
    void exit(WidgetTypes type);
    void open(WidgetTypes type);
    void updateSignal();

protected:
    WidgetTypes wgtType;
    QString wndTitle;
    QPoint oldPos;
    bool isDraged = false;
    QSize screen;
    QMargins margin;
    QString groupBoxCSS;
    bool blockResizing;

    void resizeWidget(int w, int h);
    void moveWidget(int x, int y);
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseMoveEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;
    void paintEvent(QPaintEvent *event) override;
};

class BasePushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit BasePushButton(const QString &text, QWidget *parent = nullptr);
    explicit BasePushButton(const QString &iconOff, const QString &iconOn, QWidget *parent = nullptr);

    bool selected();
    void setSelected();

private:
    QPixmap iconNotSelected, iconSelected;
    bool isTextButton = true;
    const quint8 symbolSize = 10;
    bool isSelected = false;

protected:
    void paintEvent(QPaintEvent *event) override;

};

class BaseLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BaseLabel(const QString &text, QWidget *parent = nullptr);

private:
    const quint8 symbolSize = 10;
};

class RealValidator : public QDoubleValidator
{
    Q_OBJECT
public:
    enum MeasureType {
        Degrees,
        Kilometers
    };
    RealValidator(const MeasureType &_type = Kilometers, QObject *parent = nullptr);
    RealValidator(double bottom, double top, int decimals, QObject *parent = nullptr);

    QValidator::State validate(QString &s, int &i) const;
    quint32 symbolCount();

private:
    MeasureType type;
};

class BaseLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit BaseLineEdit(const RealValidator::MeasureType &type, QWidget *parent = nullptr);
    BaseLineEdit(double bottom, double top, int decimals, QWidget *parent = nullptr);
    BaseLineEdit(QWidget *parent = nullptr);

    float getValuef();

private slots:
    void keyGrubRelease();

protected:
    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;
    void focusOutEvent(QFocusEvent *evt) override;

private:
    RealValidator *validator;
    const quint8 symbolSize = 10;
};



#endif // BASEWIDGET_H
