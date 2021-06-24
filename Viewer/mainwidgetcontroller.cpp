#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QBoxLayout>
#include <QTimer>
#include "mainwidgetcontroller.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      headerRect(1519, 0, 400, 20),
      mainBodyRect(headerRect.x(),
                   headerRect.y() + headerRect.height(),
                   headerRect.width(),
                   200)
{
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setGeometry(headerRect);
    setTitle("Функциональный контроль");

    hideWindowIcon = new QPixmap(":/icon/ic_hide_widget.png");
    showWindowIcon = new QPixmap(":/icon/ic_show_widget.png");

    connect(this, &MainWidget::resizeSignal, this, &MainWidget::resize);
}

void MainWidget::setTitle(QString title)
{
    wndTitle = title;
}

void MainWidget::resize()
{
    if (isOpened) {
        setGeometry(headerRect.x(), headerRect.y(),
                    headerRect.width(), headerRect.height() + mainBodyRect.height());
    }
    else {
        setGeometry(headerRect);
    }
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int margin = 5;
    QRect border(0, 0, size().width(), size().height());// event->rect();
    QRect bg;
    bg.setCoords(1, 1, border.width() - 1, border.height() - 1);
    QRect iconRect(headerRect.width() - hideWindowIcon->width() - margin,
                   0,
                   hideWindowIcon->width(),
                   hideWindowIcon->height());
    QRect titleRect(margin,
                    0,
                    headerRect.width() - iconRect.width() - margin,
                    headerRect.height());

    titleRect.setX(titleRect.x() + margin);
    titleRect.setWidth(titleRect.width() - 2 * margin);

    // border
    border.setCoords(1, 1, border.width() - 1, border.height() - 1);
    QPen borderPen(QColor(100, 100, 100, 200));
    painter.setPen(borderPen);
    painter.drawRect(border);

    // background
    QLinearGradient bgGradient(bg.topLeft(), bg.bottomLeft()); // diagonal gradient from top-left to bottom-right
    bgGradient.setColorAt(0, QColor(100, 100, 100, 150));//30 * darkRatio));
    bgGradient.setColorAt(1, QColor(100, 100, 100, 100));//50 * darkRatio));
    painter.fillRect(bg, bgGradient);

    // title background
    QLinearGradient titleGradient(bg.topLeft(), bg.bottomLeft()); // diagonal gradient from top-left to bottom-right
    if (isOpened) {
        titleGradient.setColorAt(0, QColor(255, 255, 255, 125));
        titleGradient.setColorAt(1, QColor(255, 255, 255, 75));
    }
    else {
        titleGradient.setColorAt(0, QColor(255, 255, 255, 75));
        titleGradient.setColorAt(1, QColor(255, 255, 255, 25));
    }
    painter.fillRect(bg, titleGradient);

    // title text
    QPen textPen(QColor(0, 0, 0, 200));
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(textPen);
    painter.drawText(titleRect, Qt::AlignVCenter | Qt::AlignLeft, wndTitle);

    painter.drawPixmap(iconRect, isOpened ? *hideWindowIcon : *showWindowIcon);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint localPos(event->pos());
    QPoint localPos2(event->globalPos());
    if (headerRect.contains(localPos2)) {
        isOpened = !isOpened;
        emit resizeSignal();
    }
}


MainWidgetController::MainWidgetController(QWidget *parent)
    : QWidget(parent)
{
    mainWidget = new MainWidget();
    mainWidget->show();
}

