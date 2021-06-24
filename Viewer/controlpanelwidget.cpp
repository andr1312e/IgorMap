#include "controlpanelwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLayout>

ControlPanelButton::ControlPanelButton(QWidget *parent) : QWidget(parent),
    currentIcon(0),
    isSelected(false)
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
    //if (flag) {
        update();
    //}
}

void ControlPanelButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect border(0, 0, size().width() - 1, size().height() - 1);
    // border
    /*border.setCoords(0, 0, border.width() - 1, border.height() - 1);
    QPen borderPen(QColor(100, 100, 100, 200));
    painter.setPen(borderPen);
    painter.drawRect(border);*/

    // draw background
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

void ControlPanelButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isSelected = !isSelected;
        emit openCloseSignal();
        update();
    }
    QWidget::mouseReleaseEvent(event);
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
    targetingButton = new ControlPanelButton(this);
    targetingButton->setIcon(":/icon/ic_targeting_off.png", ":/icon/ic_targeting_on.png");

    trackButton = new ControlPanelButton(this);
    trackButton->setIcon(":/icon/ic_trace_off.png", ":/icon/ic_trace_on.png");

    dspButton = new ControlPanelButton(this);
    dspButton->setIcon(":/icon/ic_dsp_off.png", ":/icon/ic_dsp_on.png");

    fcButton = new ControlPanelButton(this);
    fcButton->setIcon(":/icon/ic_state_system3_off.png", ":/icon/ic_state_system3_on.png");

    emittingButton = new ControlPanelButton(this);
    emittingButton->setIcon(":/icon/ic_emitting_off.png", ":/icon/ic_emitting_on.png");

    rtButton = new ControlPanelButton(this);
    rtButton->setIcon(":/icon/ic_rt2_off.png", ":/icon/ic_rt2_on.png");

    //respButton = new ControlPanelButton(this);
    //respButton->setIcon(":/icon/ic_respondent_off.png", ":/icon/ic_respondent_on.png");

    historyButton = new ControlPanelButton(this);
    historyButton->setIcon(":/icon/ic_history_off.png", ":/icon/ic_history_on.png");

    ktaInfoButton = new ControlPanelButton(this);
    ktaInfoButton->setIcon(":/icon/ic_kta_info_hidden.png", ":/icon/ic_kta_info_shown.png");

    customButton = new ControlPanelButton(this);
    customButton->setIcon(":/icon/ic_track_list_hidden.png", ":/icon/ic_track_list_shown.png");

    snrButton = new ControlPanelButton(this);
    snrButton->setIcon(":/icon/ic_signalNoiseRatio_off.png", ":/icon/ic_signalNoiseRatio_on.png");

    //colorSchemeButton = new ControlPanelButton(this);
    //colorSchemeButton->setIcon(":/icon/ic_colorScheme_off.png", ":/icon/ic_colorScheme_on.png");

    /*targetingWidget = new SectorsViewerWidget(parentWidget());
    targetingWidget->setTitle("Настройка Целеуказания");*/

    connect(targetingButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::Targeting);});
    connect(fcButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::FunctionalControl);});
    connect(customButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::Customizing);});
    connect(ktaInfoButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::KTAInfo);});
    connect(trackButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::Track);});
    connect(dspButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::DSPControl);});
    connect(snrButton, &ControlPanelButton::openCloseSignal,
            [this] {emit openWidgetSignal(WidgetTypes::SignalNoiseRatio);});


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(emittingButton);
    //mainLayout->addWidget(respButton);
    mainLayout->addWidget(rtButton);
    mainLayout->addWidget(historyButton);
    mainLayout->addWidget(ktaInfoButton);
    mainLayout->addWidget(targetingButton);
    mainLayout->addWidget(trackButton);
    mainLayout->addWidget(dspButton);
    mainLayout->addWidget(fcButton);
    mainLayout->addWidget(customButton);
    mainLayout->addWidget(snrButton);
    //mainLayout->addWidget(colorSchemeButton);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void ControlPanelWidget::changeButtonState(WidgetTypes type, bool open)
{
    if (type == WidgetTypes::Targeting) {
        if (open && !targetingButton->isSelectedButton()) {
            targetingButton->setSelectedButton(open);
        }
    }
}

void ControlPanelWidget::simpleChangeButtonStateOff(WidgetTypes type)
{
    if (type == WidgetTypes::Targeting) {
        if (targetingButton->isSelectedButton()) {
            targetingButton->setSelectedButton(false);
        }
    }
    else if (type == WidgetTypes::KTAInfo) {
        if (ktaInfoButton->isSelectedButton()) {
            ktaInfoButton->setSelectedButton(false);
        }
    }
    else if (type == WidgetTypes::Customizing) {
        if (customButton->isSelectedButton()) {
            customButton->setSelectedButton(false);
        }
    }
    else if (type == WidgetTypes::FunctionalControl) {
        if (fcButton->isSelectedButton()) {
            fcButton->setSelectedButton(false);
        }
    }
    else if (type == WidgetTypes::Track) {
        if (trackButton->isSelectedButton()) {
            trackButton->setSelectedButton(false);
        }
    }
    else if (type == WidgetTypes::DSPControl) {
        if (dspButton->isSelectedButton()) {
            dspButton->setSelectedButton(false);
        }
    }
    else if (type == WidgetTypes::SignalNoiseRatio) {
        if (snrButton->isSelectedButton()) {
            snrButton->setSelectedButton(false);
        }
    }
}

void ControlPanelWidget::simpleChangeButtonStateOn(WidgetTypes type)
{
    if (type == WidgetTypes::Targeting) {
        if (!targetingButton->isSelectedButton()) {
            targetingButton->setSelectedButton(true);
        }
    }
    else if (type == WidgetTypes::KTAInfo) {
        if (!ktaInfoButton->isSelectedButton()) {
            ktaInfoButton->setSelectedButton(true);
        }
    }
    else if (type == WidgetTypes::Customizing) {
        if (!customButton->isSelectedButton()) {
            customButton->setSelectedButton(true);
        }
    }
    else if (type == WidgetTypes::FunctionalControl) {
        if (!fcButton->isSelectedButton()) {
            fcButton->setSelectedButton(true);
        }
    }
    else if (type == WidgetTypes::Track) {
        if (trackButton->isSelectedButton()) {
            trackButton->setSelectedButton(true);
        }
    }
    else if (type == WidgetTypes::DSPControl) {
        if (dspButton->isSelectedButton()) {
            dspButton->setSelectedButton(true);
        }
    }
    else if (type == WidgetTypes::SignalNoiseRatio) {
        if (snrButton->isSelectedButton()) {
            snrButton->setSelectedButton(true);
        }
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
