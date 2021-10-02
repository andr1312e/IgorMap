#include "controlpanelwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLayout>
#include <QTextLayout>
#include <QMenu>
#include <QWidgetAction>
#include <QComboBox>
#include <QPainterPath>

ControlPanelButton::ControlPanelButton(ButtonIDs _id, QWidget *parent) : QWidget(parent),
    buttonId(_id),
    currentIcon(0),
    isSelected(false),
    workPoint(0), userWorkPoint(0)
{
    setStyleSheet("padding: 0; margin: 0;");
}

void ControlPanelButton::setIcon(const QString &notSelectedIconPath, const QString &selectedIconPath)
{
    vectorOfIcons.append(ButtonIcons(notSelectedIconPath, selectedIconPath));
    setFixedSize(vectorOfIcons.at(0).iconSelected.height(), vectorOfIcons.at(0).iconSelected.width() + 4);
}

void ControlPanelButton::setSelectedButton(bool flag) {
    isSelected = flag;
    update();
}

ButtonIDs ControlPanelButton::getButtonID() const
{
    return buttonId;
}

quint8 ControlPanelButton::getWP() const
{
    return userWorkPoint;
}

void ControlPanelButton::setWP(quint8 WP)
{
    workPoint = WP;
}

void ControlPanelButton::initContextMenu()
{
    const quint8 workPointNumber = 30;
    contextMenu = new QMenu();
    QWidgetAction* pWidgetAction = new QWidgetAction(0);
    QComboBox *pComboBox = new QComboBox(contextMenu);

    pWidgetAction->setDefaultWidget(pComboBox);
    pComboBox->setMaxCount(workPointNumber);
    for (quint8 index = 1; index <= workPointNumber; index++) {
        pComboBox->addItem(QString::number(index));
    }
    connect(pComboBox, &QComboBox::currentTextChanged, this, &ControlPanelButton::userSetWP);
    contextMenu->addAction(pWidgetAction);
}

void ControlPanelButton::userSetWP(QString currentWorkPoint)
{
    contextMenu->hide();
    userWorkPoint = currentWorkPoint.toInt();
    emit clicked();
}

void ControlPanelButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect border(0, 0, size().width() - 1, size().height() - 1);
    QRect bg = event->rect();
    bg.setWidth(bg.width());
    bg.setHeight(bg.height());
    painter.fillRect(bg, Qt::transparent);

    // draw icon
    if (!vectorOfIcons.isEmpty()) {
        if (isSelected) {
            painter.drawPixmap(4, 5, vectorOfIcons.at(currentIcon).iconSelected);
        } else {
            painter.drawPixmap(4, 5, vectorOfIcons.at(currentIcon).iconNotSelected);
        }
    }
    QWidget::paintEvent(event);
}


ControlPanelWidget::ControlPanelWidget(QWidget *parent) : QWidget(parent),
    mainBodyRect(0, 225, 70, 650)
{
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(mainBodyRect);

    initButtonsAndWidgets();

    show();
}

void ControlPanelWidget::virtualOffset(QPoint point)
{
    setGeometry(point.x() + mainBodyRect.x(),
                point.y() + mainBodyRect.y(),
                mainBodyRect.width(), mainBodyRect.height());
}

void ControlPanelWidget::initButtonsAndWidgets()
{
    mapButton = new ControlPanelButton(ButtonIDs::MapButton, this);
    mapButton->setIcon(":/Resources/Icon/ic_role_cartographer_off.png", ":/Resources/Icon/ic_role_cartographer_on.png");

    connect(mapButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::MapDebug);});


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(mapButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void ControlPanelWidget::simpleChangeButtonStateOff(WidgetTypes type)
{
    if (mapButton->isSelectedButton()) {
        mapButton->setSelectedButton(false);
    }
}

void ControlPanelWidget::simpleChangeButtonStateOn(WidgetTypes type)
{

    if (!mapButton->isSelectedButton()) {
        mapButton->setSelectedButton(true);
    }
}

void ControlPanelWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor widgetBackground = BaseWidget::backgroundColor;

    QRectF border(0, 0, size().width() - 1, size().height() - 1);
    QPainterPath path;
    QColor pathColor(widgetBackground.red(), widgetBackground.green(), widgetBackground.blue(), 150);
    path.addRoundedRect(border, 10.f, 10.f);
    QPen borderPen(QColor(widgetBackground.red(), widgetBackground.green(), widgetBackground.blue(), 200));
    painter.setPen(borderPen);
    painter.fillPath(path, pathColor);
    painter.drawPath(path);

    QWidget::paintEvent(event);
}
