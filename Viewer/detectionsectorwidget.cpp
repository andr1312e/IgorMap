#include "detectionsectorwidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QRegExpValidator>
#include <QPainter>
#include <QMouseEvent>
#include <QTextEdit>
#include <QPushButton>


DetectionSectorWidget::DetectionSectorWidget(BaseWidget *parent)
    : BaseWidget(KTAInfo, parent)
{
    Init();
}

DetectionSectorWidget::~DetectionSectorWidget() {

}

void DetectionSectorWidget::Init() {
    const int textLabelWidth = 40,
              outputTextWidth = 60;
    const QString strNoValue = "-";

    QLabel *radTextLabel = new QLabel("Радиус (км)");
    QLineEdit *radSpallLine = new QLineEdit;
    radSpallLine->setValidator(new QRegExpValidator( QRegExp("^\\d*[.]?\\d*$"), radSpallLine ));
    //radSpallLine->setText(QString::number(CfgManager::Instance()->getUiController()->getMainUIView()->getKTAClickThreshold(), 'f', 2));
    radSpallLine->setFixedWidth(outputTextWidth);
    QHBoxLayout *radSpallLayout = new QHBoxLayout;
    radSpallLayout->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
    radSpallLayout->addWidget(radTextLabel);
    radSpallLayout->addWidget(radSpallLine);
    radSpallLayout->addStretch(1);

    QLabel *paramTextLabel = new QLabel("Параметры скола");
    QVBoxLayout *paramSpallLayout = new QVBoxLayout;
    paramSpallLayout->addWidget(paramTextLabel);
    paramSpallLayout->addLayout(radSpallLayout);
    paramSpallLayout->addStretch(1);

    QLabel *distLabel = new QLabel("D:");
    distLabel->setFixedWidth(textLabelWidth);
    QLabel *distOutput = new QLabel(strNoValue);
    distOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *distLayout = new QHBoxLayout();
    distLayout->addWidget(distLabel);
    distLayout->addWidget(distOutput);

    QLabel *azLabel = new QLabel("Az:");
    azLabel->setFixedWidth(textLabelWidth);
    QLabel *azimuthOutput = new QLabel(strNoValue);
    azimuthOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *azLayout = new QHBoxLayout();
    azLayout->addWidget(azLabel);
    azLayout->addWidget(azimuthOutput);

    QLabel *pointAngleLabel = new QLabel("E:");
    pointAngleLabel->setFixedWidth(textLabelWidth);
    QLabel *pointAngleOutput = new QLabel(strNoValue);
    pointAngleOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *pointAngleLayout = new QHBoxLayout();
    pointAngleLayout->addWidget(pointAngleLabel);
    pointAngleLayout->addWidget(pointAngleOutput);

    QHBoxLayout *firstInfoLayout = new QHBoxLayout;
    firstInfoLayout->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
    firstInfoLayout->addLayout(distLayout);
    firstInfoLayout->addLayout(azLayout);
    firstInfoLayout->addLayout(pointAngleLayout);
    firstInfoLayout->addStretch(1);

    QLabel *ampLabel = new QLabel("Amp:");
    ampLabel->setFixedWidth(textLabelWidth);
    QLabel *ampOutput = new QLabel(strNoValue);
    ampOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *ampLayout = new QHBoxLayout();
    ampLayout->addWidget(ampLabel);
    ampLayout->addWidget(ampOutput);

    QLabel *rSpeedLabel = new QLabel("Vr:");
    rSpeedLabel->setFixedWidth(textLabelWidth);
    QLabel *rSpeedOutput = new QLabel(strNoValue);
    rSpeedOutput->setFixedWidth(outputTextWidth);
    QHBoxLayout *rSpeedLayout = new QHBoxLayout();
    rSpeedLayout->addWidget(rSpeedLabel);
    rSpeedLayout->addWidget(rSpeedOutput);

    QHBoxLayout *secondInfoLayout = new QHBoxLayout;
    secondInfoLayout->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
    secondInfoLayout->addLayout(ampLayout);
    secondInfoLayout->addLayout(rSpeedLayout);
    secondInfoLayout->addStretch(1);

    QLabel *infoKTALabel = new QLabel("Информация о выбраной КТА");
    QVBoxLayout *infoKTALayout = new QVBoxLayout();
    infoKTALayout->addWidget(infoKTALabel);
    infoKTALayout->addLayout(firstInfoLayout);
    infoKTALayout->addLayout(secondInfoLayout);
    infoKTALayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addLayout(paramSpallLayout);
    mainLayout->addLayout(infoKTALayout);
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}
