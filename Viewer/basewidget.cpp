#include "basewidget.h"
#include <QLabel>
#include <QPainter>
#include <QTextEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QPixmap>
#include <QApplication>
#include <QScreen>
#include "math.h"

QColor BaseWidget::backgroundColor = QColor(100,100,100);

BaseWidget::BaseWidget(WidgetTypes wgtT, QWidget *parent)
    : QWidget(parent), wgtType(wgtT), blockResizing(false)
{
    screen = QApplication::screens().at(0)->availableVirtualSize();
    isResized = false;
    isExit = false;
    resizeOffIcon = new QPixmap(":/icon/ic_resize_fw_off.png");
    resizeOnIcon = new QPixmap(":/icon/ic_resize_fw_on.png");
    exitOffIcon = new QPixmap(":/icon/ic_exit_off.png");
    exitOnIcon = new QPixmap(":/icon/ic_exit_on.png");
    /*darkIncIcon = new QPixmap(":/res/ic_transporetn_inc.png");
    darkDecIcon = new QPixmap(":/res/ic_transporetn_dec.png");
    darkIcon = new QPixmap(":/res/ic_transporent.png");*/
    //setWindowOpacity(0.5);
    margin = QMargins(15,5,15,5);
    groupBoxCSS = QString("QGroupBox::title {"
                          "subcontrol-origin: margin;"
                          "subcontrol-position: top left;"
                          "padding: 0px;"
                          "margin: 0px 3px 3px 0px;"
                          "color: #aaaaaa;"
                          " }");

    setTitle("");
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_AlwaysShowToolTips);
    //setAttribute(Qt::WA_OpaquePaintEvent);
    //setWindowOpacity(0.5);

    //Init();
}

BaseWidget::~BaseWidget() {
    delete resizeOffIcon;
    delete resizeOnIcon;
    delete exitOffIcon;
    delete exitOnIcon;
    /*delete darkIncIcon;
    delete darkDecIcon;
    delete darkIcon;*/
}

void BaseWidget::setTitle(QString title)
{
    wndTitle = title;
}

void BaseWidget::triggeredBackgroundColor(bool isBlackTheme)
{
    if (isBlackTheme) {
        backgroundColor = QColor(100,100,100);
    }
    else {
        backgroundColor = QColor(0,0,0);
    }
}

void BaseWidget::makeHide()
{
    if (!isHidden()) {
        hide();
        //emit open(wgtType);
    }
}

void BaseWidget::makeShow()
{
    if (isHidden()) {
        show();
        emit open(wgtType);
    }
}

void BaseWidget::setBlockResizing(bool flag)
{
    blockResizing = flag;
}

void BaseWidget::openCloseWidget()
{
    if (isHidden())
        show();
    else
        hide();
}

void BaseWidget::Init() {
    /*QLabel *title = new QLabel();
    //title->setText(wndTitle);
    title->setStyleSheet("color: white; background-color: transparent");
    QTextEdit *edit1 = new QTextEdit;
    QTextEdit *edit2 = new QTextEdit;
    QPushButton *btn1 = new QPushButton("1");
    QPushButton *btn2 = new QPushButton("2");

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(edit1, 0, 0);
    mainLayout->addWidget(edit2, 1, 0);
    mainLayout->addWidget(btn1, 0, 1);
    mainLayout->addWidget(btn2, 1, 1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(title);
    vLayout->addLayout(mainLayout);


    setLayout(vLayout);*/
}

void BaseWidget::mousePressEvent(QMouseEvent *evt) {
    if(evt->button() == Qt::LeftButton) {
        QRect resizeIconRect(width() - resizeOffIcon->width() - exitOffIcon->width() - 2 * 2, 0, resizeOffIcon->width(), resizeOffIcon->height());
        QRect exitIconRect(width() - exitOffIcon->width() - 2, 0, exitOffIcon->width(), exitOffIcon->height());
        QRect titleRect;
        //titleRect.setCoords(0, 0, sizeHint().width() - resizeIconRect.width() - exitIconRect.width(), 21);
        titleRect.setCoords(0, 0, geometry().width() - resizeIconRect.width() - exitIconRect.width(), 21);
        /*QRect darkDecIconRect(width() - resizeOffIcon->width() - exitOffIcon->width() - darkIncIcon->width() - 2 * 3,
                              0, darkIcon->width(), darkIcon->height());
        QRect darkIncIconRect(width() - resizeOffIcon->width() - exitOffIcon->width() - darkIcon->width() - darkIncIcon->width() - darkDecIcon->width() - 2 * 5,
                              0, darkDecIcon->width(), darkDecIcon->height());*/
        if (resizeIconRect.contains(evt->pos())) {
            if (!blockResizing)
                isResized = true;
        }
        else if (exitIconRect.contains(evt->pos())) {
            isExit = true;
        }
        /*else if (darkIncIconRect.contains(evt->pos())) {
            if (darkRatio < 3)
                darkRatio++;
        }
        else if (darkDecIconRect.contains(evt->pos())) {
            if (darkRatio > 1)
                darkRatio--;
        }*/
        else if (titleRect.contains(evt->pos())){
            isDraged = true;
        }
        oldPos = evt->globalPos();
    }
    //QWidget::mousePressEvent(evt);
}

void BaseWidget::resizeWidget(int w, int h) {
    resize(w, h);
    qDebug() << QSize(w,h);
    //emit updateSignal();
}

void BaseWidget::moveWidget(int x, int y) {
    move(x, y);
    qDebug() << QPoint(x,y);
    //emit updateSignal();
}

void BaseWidget::mouseMoveEvent(QMouseEvent *evt) {

    //if(!isActiveWindow()) {
    //    activateWindow();
    //}

    if (isDraged) {
        const QPoint delta = evt->globalPos() - oldPos;
        int newX = x() + delta.x(),
            newY = y() + delta.y();

        // don't let window go out of screen
        if ( (x() + delta.x() + width()) >= screen.width() ) {
            newX = screen.width() - width();
        } else if ( (x() + delta.x()) <= 0 ) {
            newX = 0;
        }
        if ( (y() + delta.y() + height()) >= screen.height() ) {
            newY = screen.height() - height();
        } else if ( (y() + delta.y()) <= 0 ) {
            newY = 0;
        }

        moveWidget(newX, newY);
        oldPos = evt->globalPos();
    } else if(isResized && !blockResizing) {
        const QPoint delta = evt->globalPos() - oldPos;
        int oldHeight = height();

        if (width() + delta.x() < screen.width() &&
            height() - delta.y() < screen.height())
        {
            resizeWidget(width() + delta.x(), height() - delta.y());
            QSize newSize = size();
            if (newSize.height() != oldHeight) {
                moveWidget(x(), y() + delta.y());
            }
        }
        oldPos = evt->globalPos();
    }
    //QWidget::mouseMoveEvent(evt);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *evt) {
    isDraged = false;
    isResized = false;
    if (isExit) {
        emit exit(wgtType);
        isExit = false;
        hide();
    }
    //QWidget::mouseReleaseEvent(evt);
}

void BaseWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    QRect border(0, 0, size().width(), size().height());// event->rect();
    QRect bg;
    bg.setCoords(1, 1, border.width() - 1, border.height() - 1);
    QRect titleRect;
    titleRect.setCoords(0, 0, bg.width(), 21);

    // border
    border.setCoords(1, 0, border.width() - 1, border.height() - 2);
    QPen borderPen(QColor(100, 100, 100, 200));
    painter.setPen(borderPen);
    painter.drawRect(border);

    // background
    QLinearGradient bgGradient(bg.topLeft(), bg.bottomLeft()); // diagonal gradient from top-left to bottom-right
    bgGradient.setColorAt(0, QColor(backgroundColor.red(), backgroundColor.green(), backgroundColor.blue(), 225));//30 * darkRatio));
    bgGradient.setColorAt(1, QColor(backgroundColor.red(), backgroundColor.green(), backgroundColor.blue(), 175));//50 * darkRatio));
    painter.fillRect(bg, bgGradient);

    // title background
    QLinearGradient titleGradient(titleRect.topLeft(), titleRect.bottomLeft()); // diagonal gradient from top-left to bottom-right
    titleGradient.setColorAt(0, QColor(255, 255, 255, 100));
    titleGradient.setColorAt(1, QColor(255, 255, 255, 50));
    painter.fillRect(titleRect, titleGradient);

    // title text
    QPen textPen(QColor(0, 0, 0, 200));
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(textPen);
    titleRect.setWidth(titleRect.width() -resizeOffIcon->width() - exitOffIcon->width()  - 2 * 5); // чтобы текст не наезжал на иконки // - darkIcon->width() - darkIncIcon->width() - darkDecIcon->width()
    painter.drawText(titleRect, Qt::AlignCenter, wndTitle);

    /*painter.drawPixmap(width() - resizeOffIcon->width() - exitOffIcon->width() - darkIcon->width() - darkIncIcon->width() - darkDecIcon->width()  - 2 * 5,
                       0, darkDecIcon->width(), darkDecIcon->height(), *darkIncIcon);
    painter.drawPixmap(width() - resizeOffIcon->width() - exitOffIcon->width() - darkIcon->width() - darkIncIcon->width() - 2 * 4,
                       0, darkIcon->width(), darkIcon->height(), *darkIcon);
    painter.drawPixmap(width() - resizeOffIcon->width() - exitOffIcon->width() - darkIncIcon->width() - 2 * 3,
                       0, darkIncIcon->width(), darkIncIcon->height(), *darkDecIcon);*/

    if (!blockResizing) {
        if (isResized) {
            painter.drawPixmap(width() - resizeOffIcon->width() - exitOffIcon->width() - 2 * 2, 0, resizeOffIcon->width(), resizeOffIcon->height(), *resizeOnIcon);
        } else {
            painter.drawPixmap(width() - resizeOffIcon->width() - exitOffIcon->width() - 2 * 2, 0, resizeOffIcon->width(), resizeOffIcon->height(), *resizeOffIcon);
        }
    }

    if (isExit) {
        painter.drawPixmap(width() - exitOffIcon->width() - 2 * 1, 0, exitOffIcon->width(), exitOffIcon->height(), *exitOnIcon);
    }
    else {
        painter.drawPixmap(width() - exitOffIcon->width() - 2 * 1, 0, exitOffIcon->width(), exitOffIcon->height(), *exitOffIcon);
    }
}

BaseLabel::BaseLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    //setFixedWidth(text.size() * symbolSize);
}

RealValidator::RealValidator(const MeasureType &_type, QObject *parent)
    : QDoubleValidator(parent), type(_type)
{
    switch (type) {
    case Degrees:
        setRange(0., 359.9, 3);
        break;
    case Kilometers:
        setRange(1., 999., 3);
        break;
    }
    setNotation(StandardNotation);
}

RealValidator::RealValidator(double bottom, double top, int decimals, QObject *parent)
    : QDoubleValidator(bottom, top, decimals, parent)
{
    setNotation(StandardNotation);
}

QValidator::State RealValidator::validate(QString &s, int &i) const
{
    if (s.isEmpty()) {
        return QValidator::Intermediate;
    }

    if (s == "-" && (bottom() > 0 || top() > 0)) {
            return QValidator::Invalid;
    }

    QChar decimalPoint = '.';//locale().decimalPoint();

    if(s.indexOf(decimalPoint) != -1) {
        int charsAfterPoint = s.length() - s.indexOf(decimalPoint) - 1;

        if (charsAfterPoint > decimals()) {
            return QValidator::Invalid;
        }
    }

    bool ok;
    double d = s.toDouble(&ok);//locale().toDouble(s, &ok);

    if (ok && d >= bottom() && d <= top()) {
        return QValidator::Acceptable;
    } else {
        return QValidator::Invalid;
    }
}

quint32 RealValidator::symbolCount()
{
    quint32 count(1);
    if (top() < 0)
        count++;
    quint32 topInt(abs(top()));
    while ((topInt /= 10) > 0) {
        count++;
    }
    if (decimals() > 0) {
        count += decimals();
        count++;
    }
    return count;
}


BaseLineEdit::BaseLineEdit(const RealValidator::MeasureType &type, QWidget *parent)
    : QLineEdit(parent)
{
    validator = new RealValidator(type, this);
    setValidator(validator);
    setFixedWidth(symbolSize * 8);
    setReadOnly(false);
    //setFixedWidth(validator->symbolCount() * symbolSize);

    connect(this, SIGNAL(editingFinished()), this, SLOT(keyGrubRelease()));
}

BaseLineEdit::BaseLineEdit(double bottom, double top, int decimals, QWidget *parent)
    : QLineEdit(parent)
{
    validator = new RealValidator(bottom, top, decimals, this);
    setValidator(validator);
    setFixedWidth(symbolSize * 8);
    setReadOnly(false);
    //setFixedWidth(validator->symbolCount() * symbolSize);

    connect(this, SIGNAL(editingFinished()), this, SLOT(keyGrubRelease()));
}

BaseLineEdit::BaseLineEdit(QWidget *parent) : QLineEdit(parent) {
    //setFixedWidth(symbolSize * 8);
    setReadOnly(false);

    connect(this, SIGNAL(editingFinished()), this, SLOT(keyGrubRelease()));
}

float BaseLineEdit::getValuef()
{
    return text().toFloat();
}

void BaseLineEdit::keyGrubRelease()
{
    releaseKeyboard();
    releaseMouse();
    //qDebug() << "releaseKeyboard";
}

void BaseLineEdit::mousePressEvent(QMouseEvent *evt)
{
    //if (evt->button() == Qt::LeftButton) {
    //    grabMouse();
    //}
    QLineEdit::mousePressEvent(evt);
}

void BaseLineEdit::mouseReleaseEvent(QMouseEvent *evt)
{
    if (evt->button() == Qt::LeftButton) {
        //activateWindow();
        grabKeyboard();
        grabMouse();
        //qDebug() << "grabKeyboard";
    }
    QLineEdit::mouseReleaseEvent(evt);
}

void BaseLineEdit::focusOutEvent(QFocusEvent *evt)
{
    if (evt->reason() == Qt::PopupFocusReason) {
        keyGrubRelease();
        //qDebug() << "Qt::PopupFocusReason";
    }
    else if (evt->reason() == Qt::ActiveWindowFocusReason) {
        keyGrubRelease();
        //qDebug() << "Qt::ActiveWindowFocusReason";
    }
    QLineEdit::focusOutEvent(evt);
}

BasePushButton::BasePushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setFixedWidth((text.size() + 3) * symbolSize);
    isTextButton = true;
}

BasePushButton::BasePushButton(const QString &iconOff, const QString &iconOn, QWidget *parent)
    : QPushButton(parent)
{
    setStyleSheet(QString("QPushButton {background-color: none; color: none;}"
                          "QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(30, 255, 30, 150), stop:1 rgba(30, 255, 30, 100));"
                          "color: #000000;}"));
    iconNotSelected.load(iconOff);
    iconSelected.load(iconOn);
    setFixedSize(iconSelected.size());
    isTextButton = false;
    isSelected = false;
    connect(this, &QPushButton::clicked, [&] {isSelected = !isSelected;});
}

bool BasePushButton::selected()
{
    return isSelected;
}

void BasePushButton::setSelected()
{
    isSelected = true;
}

void BasePushButton::paintEvent(QPaintEvent *event)
{
    if (!isTextButton) {
        QPainter painter(this);

        /*QRect border(0, 0, size().width() - 1, size().height() - 1);
        // border
        border.setCoords(0, 0, border.width() - 1, border.height() - 1);
        QPen borderPen(QColor(100, 100, 100, 200));
        painter.setPen(borderPen);
        painter.drawRect(border);*/

        // draw background
        /*QRect bg = event->rect();
        bg.setWidth(bg.width());
        bg.setHeight(bg.height());
        painter.fillRect(bg, Qt::transparent);*/

        // draw icon
        if (isSelected) {
        //if (isEnabled()) {
            painter.drawPixmap(0, 0, iconSelected);
        } else {
            painter.drawPixmap(0, 0, iconNotSelected);
        }
    }
    QPushButton::paintEvent(event);
}
