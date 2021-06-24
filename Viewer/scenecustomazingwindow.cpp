#include "scenecustomazingwindow.h"
#include <QGroupBox>

#include <QColor>
#include <QLineEdit>
#include <QBoxLayout>
#include <QColorDialog>

SceneCustomazingWindow::SceneCustomazingWindow(BaseWidget *parent) : BaseWidget(WidgetTypes::Customizing, parent)
{
    setTitle("Настройка GUI");

    //QMargins margin(15,5,15,5);
    const quint16 colorButtonWidth = 150;

    QValidator *validator = new QIntValidator(0, 999);
    //QString strStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(30, 30, 30, 50), stop:1 rgba(30, 30, 30, 150));}");

    QLabel *adBackGroundColorLabel = new QLabel("Цвет фона");
    adBackGroundColorButton = new QPushButton();//QColor::fromRgbF(0.0f, 0.0f, 0.0f, 1.0f).name());
    adBackGroundColorButton->setFixedWidth(colorButtonWidth);
    //adBackGroundColorButton->setStyleSheet(strStyleSheet);
    QHBoxLayout *adBackGroundColorLayout = new QHBoxLayout();
    adBackGroundColorLayout->addWidget(adBackGroundColorLabel, 1, Qt::AlignLeft);
    adBackGroundColorLayout->addWidget(adBackGroundColorButton, 1, Qt::AlignRight);

    QLabel *adGrideColorLabel = new QLabel("Цвет сетки");
    adGrideColorButton = new QPushButton();//QColor::fromRgbF(0.4f, 0.4f, 0.4f, 0.6f).name());
    adGrideColorButton->setFixedWidth(colorButtonWidth);
    //adGrideColorButton->setStyleSheet(strStyleSheet);
    QHBoxLayout *adGrideColorLayout = new QHBoxLayout();
    adGrideColorLayout->addWidget(adGrideColorLabel, 1, Qt::AlignLeft);
    adGrideColorLayout->addWidget(adGrideColorButton, 1, Qt::AlignRight);

    /*QLabel *adGrideDistMaxLabel = new QLabel("Максимальная дальность");
    adGrideDistMaxLineEdit = new QLineEdit();
    adGrideDistMaxLineEdit->setValidator(validator);
    QHBoxLayout *adGrideDistMaxLayout = new QHBoxLayout();
    adGrideDistMaxLayout->addWidget(adGrideDistMaxLabel, 1, Qt::AlignLeft);
    adGrideDistMaxLayout->addWidget(adGrideDistMaxLineEdit, 1, Qt::AlignRight);

    /QLabel *adGrideDistDiscretLabel = new QLabel("Дискрет дальности");
    adGrideDistDiscretLineEdit = new QLineEdit();
    adGrideDistDiscretLineEdit->setValidator(validator);
    QHBoxLayout *adGrideDistDiscretLayout = new QHBoxLayout();
    adGrideDistDiscretLayout->addWidget(adGrideDistDiscretLabel, 1, Qt::AlignLeft);
    adGrideDistDiscretLayout->addWidget(adGrideDistDiscretLineEdit, 1, Qt::AlignRight);

    QLabel *adGrideAzDiscretLabel = new QLabel("Дискрет азимута");
    adGrideAzDiscretLineEdit = new QLineEdit();
    adGrideAzDiscretLineEdit->setValidator(validator);
    QHBoxLayout *adGrideAzDiscretLayout = new QHBoxLayout();
    adGrideAzDiscretLayout->addWidget(adGrideAzDiscretLabel, 1, Qt::AlignLeft);
    adGrideAzDiscretLayout->addWidget(adGrideAzDiscretLineEdit, 1, Qt::AlignRight);*/

    QLabel *adGrideTextColorLabel = new QLabel("Цвет текста");
    adGrideTextColorButton = new QPushButton();//QColor::fromRgb(0,0,0,0).name());
    adGrideTextColorButton->setFixedWidth(colorButtonWidth);
    //adGrideTextColorButton->setStyleSheet(strStyleSheet);
    QHBoxLayout *adGrideTextColorLayout = new QHBoxLayout();
    adGrideTextColorLayout->addWidget(adGrideTextColorLabel, 1, Qt::AlignLeft);
    adGrideTextColorLayout->addWidget(adGrideTextColorButton, 1, Qt::AlignRight);

    const quint16 buttonWidth = 30;
    QLabel *adGrideTextSizeLabel = new QLabel("Размер текста");
    adTextSizeInc = new QPushButton("+");
    adTextSizeInc->setFixedWidth(buttonWidth);
    adTextSizeDec = new QPushButton("-");
    adTextSizeDec->setFixedWidth(buttonWidth);
    adTextSizeRst = new QPushButton("Rst");
    adTextSizeRst->setFixedWidth(buttonWidth + 47);
    //adGrideTextSizeLineEdit = new QLineEdit();
    //adGrideTextSizeLineEdit->setValidator(validator);
    QHBoxLayout *adGrideTextSizeLayout = new QHBoxLayout();
    adGrideTextSizeLayout->addWidget(adGrideTextSizeLabel, 1, Qt::AlignLeft);
    adGrideTextSizeLayout->addWidget(adTextSizeInc,1);
    adGrideTextSizeLayout->addWidget(adTextSizeDec,1);
    adGrideTextSizeLayout->addWidget(adTextSizeRst,1);
    //adGrideTextSizeLayout->addWidget(adGrideTextSizeLineEdit, 1, Qt::AlignRight);

    adGrideDistTextCheck = new QCheckBox("Включить метки по дальности");
    adGrideAzTextCheck = new QCheckBox("Включить метки по азимуту");

    QVBoxLayout *azDistLayout = new QVBoxLayout();
    azDistLayout->addLayout(adBackGroundColorLayout);
    azDistLayout->addLayout(adGrideColorLayout);
    //azDistLayout->addLayout(adGrideDistMaxLayout);
    //azDistLayout->addLayout(adGrideDistDiscretLayout);
    //azDistLayout->addLayout(adGrideAzDiscretLayout);
    azDistLayout->addLayout(adGrideTextColorLayout);
    azDistLayout->addLayout(adGrideTextSizeLayout);
    azDistLayout->addWidget(adGrideDistTextCheck);
    azDistLayout->addWidget(adGrideAzTextCheck);
    azDistLayout->addStretch(1);

    QGroupBox *azDistGride = new QGroupBox("Дальностно-азимутальная развёртка");
    azDistGride->setLayout(azDistLayout);

    QLabel *ktaPOIColorLabel = new QLabel("Цвет ПОИ");
    ktaPOIColorButton = new QPushButton();
    ktaPOIColorButton->setFixedWidth(colorButtonWidth);
    QHBoxLayout *ktaPOIColorLayout = new QHBoxLayout();
    ktaPOIColorLayout->addWidget(ktaPOIColorLabel, 1, Qt::AlignLeft);
    ktaPOIColorLayout->addWidget(ktaPOIColorButton, 1, Qt::AlignRight);
    QLabel *ktaPOISizeLabel = new QLabel("Размер ПОИ");
    ktaPOISizeInc = new QPushButton("+");
    ktaPOISizeInc->setFixedWidth(buttonWidth);
    ktaPOISizeDec = new QPushButton("-");
    ktaPOISizeDec->setFixedWidth(buttonWidth);
    ktaPOISizeRst = new QPushButton("Rst");
    ktaPOISizeRst->setFixedWidth(buttonWidth + 47);
    QHBoxLayout *ktaPOISizeLayout = new QHBoxLayout();
    ktaPOISizeLayout->addWidget(ktaPOISizeLabel, 1, Qt::AlignLeft);
    ktaPOISizeLayout->addWidget(ktaPOISizeInc,1);
    ktaPOISizeLayout->addWidget(ktaPOISizeDec,1);
    ktaPOISizeLayout->addWidget(ktaPOISizeRst,1);
    QLabel *ktaVOIColorLabel = new QLabel("Цвет ВОИ");
    ktaVOIColorButton = new QPushButton();
    ktaVOIColorButton->setFixedWidth(colorButtonWidth);
    QHBoxLayout *ktaVOIColorLayout = new QHBoxLayout();
    ktaVOIColorLayout->addWidget(ktaVOIColorLabel, 1, Qt::AlignLeft);
    ktaVOIColorLayout->addWidget(ktaVOIColorButton, 1, Qt::AlignRight);
    QLabel *ktaVOISizeLabel = new QLabel("Размер ВОИ");
    ktaVOISizeInc = new QPushButton("+");
    ktaVOISizeInc->setFixedWidth(buttonWidth);
    ktaVOISizeDec = new QPushButton("-");
    ktaVOISizeDec->setFixedWidth(buttonWidth);
    ktaVOISizeRst = new QPushButton("Rst");
    ktaVOISizeRst->setFixedWidth(buttonWidth + 47);
    QHBoxLayout *ktaVOISizeLayout = new QHBoxLayout();
    ktaVOISizeLayout->addWidget(ktaVOISizeLabel, 1, Qt::AlignLeft);
    ktaVOISizeLayout->addWidget(ktaVOISizeInc,1);
    ktaVOISizeLayout->addWidget(ktaVOISizeDec,1);
    ktaVOISizeLayout->addWidget(ktaVOISizeRst,1);

    QVBoxLayout *ktaLayout = new QVBoxLayout();
    ktaLayout->addLayout(ktaPOIColorLayout);
    ktaLayout->addLayout(ktaPOISizeLayout);
    ktaLayout->addLayout(ktaVOIColorLayout);
    ktaLayout->addLayout(ktaVOISizeLayout);
    ktaLayout->addStretch(1);

    QGroupBox *ktaGroupBox = new QGroupBox("КТА");
    ktaGroupBox->setLayout(ktaLayout);

    QLabel *sectorsColorLabel = new QLabel("Цвет ЦУ");
    sectorsColorButton = new QPushButton();
    sectorsColorButton->setFixedWidth(colorButtonWidth);
    QHBoxLayout *sectorsColorLayout = new QHBoxLayout();
    sectorsColorLayout->addWidget(sectorsColorLabel, 1, Qt::AlignLeft);
    sectorsColorLayout->addWidget(sectorsColorButton, 1, Qt::AlignRight);
    QVBoxLayout *sectorsLayout = new QVBoxLayout();
    sectorsLayout->addLayout(sectorsColorLayout);
    sectorsLayout->addStretch(1);

    QGroupBox *sectorsGroupBox = new QGroupBox("Сектора ЦУ");
    sectorsGroupBox->setLayout(sectorsLayout);

    QLabel *rayColorLabel = new QLabel("Цвет Луча");
    rayColorButton = new QPushButton();
    rayColorButton->setFixedWidth(colorButtonWidth);
    QHBoxLayout *rayColorLayout = new QHBoxLayout();
    rayColorLayout->addWidget(rayColorLabel, 1, Qt::AlignLeft);
    rayColorLayout->addWidget(rayColorButton, 1, Qt::AlignRight);
    QLabel *rayMaxDistLabel = new QLabel("Предел дальности");
    rayMaxDistLineEdit = new QLineEdit();
    rayMaxDistLineEdit->setValidator(validator);
    rayMaxDistLineEdit->setFixedWidth(colorButtonWidth);
    QHBoxLayout *rayMaxDistLayout = new QHBoxLayout();
    rayMaxDistLayout->addWidget(rayMaxDistLabel, 1, Qt::AlignLeft);
    rayMaxDistLayout->addWidget(rayMaxDistLineEdit, 1, Qt::AlignRight);

    QVBoxLayout *rayLayout = new QVBoxLayout();
    rayLayout->addLayout(rayColorLayout);
    rayLayout->addLayout(rayMaxDistLayout);
    rayLayout->addStretch(1);

    QGroupBox *rayGroupBox = new QGroupBox("Лучи");
    rayGroupBox->setLayout(rayLayout);

    QLabel *traceColorLabel = new QLabel("Цвет Трассы");
    traceColorButton = new QPushButton();
    traceColorButton->setFixedWidth(colorButtonWidth);
    QHBoxLayout *traceColorLayout = new QHBoxLayout();
    traceColorLayout->addWidget(traceColorLabel, 1, Qt::AlignLeft);
    traceColorLayout->addWidget(traceColorButton, 1, Qt::AlignRight);
    QLabel *traceLogBookColorLabel = new QLabel("Цвет Формуляра");
    traceLogBookColorButton = new QPushButton();
    traceLogBookColorButton->setFixedWidth(colorButtonWidth);
    QHBoxLayout *traceLogBookColorLayout = new QHBoxLayout();
    traceLogBookColorLayout->addWidget(traceLogBookColorLabel, 1, Qt::AlignLeft);
    traceLogBookColorLayout->addWidget(traceLogBookColorButton, 1, Qt::AlignRight);
    QLabel *traceLogBookTextColorLabel = new QLabel("Цвет текста");
    traceLBTextColor = new QPushButton();
    traceLBTextColor->setFixedWidth(colorButtonWidth);
    QHBoxLayout *traceLogBookTextColorLayout = new QHBoxLayout();
    traceLogBookTextColorLayout->addWidget(traceLogBookTextColorLabel, 1, Qt::AlignLeft);
    traceLogBookTextColorLayout->addWidget(traceLBTextColor, 1, Qt::AlignRight);
    QLabel *traceLogBookTextSizeLabel = new QLabel("Размер текста");
    traceTextSizeInc = new QPushButton("+");
    traceTextSizeInc->setFixedWidth(buttonWidth);
    traceTextSizeDec = new QPushButton("-");
    traceTextSizeDec->setFixedWidth(buttonWidth);
    traceTextSizeRst = new QPushButton("Rst");
    traceTextSizeRst->setFixedWidth(buttonWidth + 47);
    QHBoxLayout *traceTextSizeLayout = new QHBoxLayout();
    traceTextSizeLayout->addWidget(traceLogBookTextSizeLabel, 1, Qt::AlignLeft);
    traceTextSizeLayout->addWidget(traceTextSizeInc,1);
    traceTextSizeLayout->addWidget(traceTextSizeDec,1);
    traceTextSizeLayout->addWidget(traceTextSizeRst,1);

    QVBoxLayout *traceLayout = new QVBoxLayout();
    traceLayout->addLayout(traceColorLayout);
    traceLayout->addLayout(traceLogBookColorLayout);
    traceLayout->addLayout(traceLogBookTextColorLayout);
    traceLayout->addLayout(traceTextSizeLayout);
    traceLayout->addStretch(1);

    QGroupBox *traceGroupBox = new QGroupBox("Трассы");
    traceGroupBox->setLayout(traceLayout);

    lightThemeButton = new QPushButton("Светлая");
    lightThemeButton->setFixedWidth(100);
    lightThemeButton->setCheckable(true);
    darkThemeButton = new QPushButton("Темная");
    darkThemeButton->setFixedWidth(100);
    darkThemeButton->setCheckable(true);
    darkThemeButton->setChecked(true);
    customThemeButton = new QPushButton("Своя");
    customThemeButton->setFixedWidth(100);
    customThemeButton->setCheckable(true);
    QHBoxLayout *themeLayout = new QHBoxLayout();
    themeLayout->addWidget(lightThemeButton,1);
    themeLayout->addWidget(darkThemeButton,1);
    themeLayout->addWidget(customThemeButton,1);

    QGroupBox *preSetGroupBox = new QGroupBox("Пресеты тем");
    preSetGroupBox->setLayout(themeLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(preSetGroupBox);
    mainLayout->addWidget(azDistGride);
    mainLayout->addWidget(ktaGroupBox);
    mainLayout->addWidget(sectorsGroupBox);
    mainLayout->addWidget(rayGroupBox);
    mainLayout->addWidget(traceGroupBox);

    setLayout(mainLayout);

    connect(adBackGroundColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);
    connect(adGrideColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);
    connect(adGrideTextColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);

    connect(adTextSizeInc, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(adTextSizeDec, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(adTextSizeRst, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);

    connect(adGrideDistTextCheck, &QCheckBox::clicked, this, &SceneCustomazingWindow::adFlagChecked);
    connect(adGrideAzTextCheck, &QCheckBox::clicked, this, &SceneCustomazingWindow::adFlagChecked);

    connect(ktaPOIColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);
    connect(ktaVOIColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);

    connect(ktaPOISizeInc, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(ktaPOISizeDec, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(ktaPOISizeRst, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(ktaVOISizeInc, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(ktaVOISizeDec, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(ktaVOISizeRst, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);

    connect(sectorsColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);

    connect(rayColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);

    connect(traceColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);
    connect(traceLogBookColorButton, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);
    connect(traceLBTextColor, &QPushButton::clicked, this, &SceneCustomazingWindow::adColorChange);

    connect(traceTextSizeInc, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(traceTextSizeDec, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);
    connect(traceTextSizeRst, &QPushButton::clicked, this, &SceneCustomazingWindow::adTextSizeChanged);

    connect(rayMaxDistLineEdit, &QLineEdit::editingFinished, this, &SceneCustomazingWindow::adTextChange);

    connect(lightThemeButton, &QPushButton::clicked, this, &SceneCustomazingWindow::themeChange);
    connect(darkThemeButton, &QPushButton::clicked, this, &SceneCustomazingWindow::themeChange);
    connect(customThemeButton, &QPushButton::clicked, this, &SceneCustomazingWindow::themeChange);
}

void SceneCustomazingWindow::initCustomDataSlot(const SceneCustomDataInit &cData)
{
    setButtonBackground(adBackGroundColorButton, cData.backgroundColor);
    setButtonBackground(adGrideColorButton, cData.grideColor);
    setButtonBackground(adGrideTextColorButton, cData.grideTextColor);

    adGrideDistTextCheck->setChecked(cData.grideDistMark);
    adGrideAzTextCheck->setChecked(cData.grideAzMark);

    setButtonBackground(ktaPOIColorButton, cData.ktaPOIColor);
    setButtonBackground(ktaVOIColorButton, cData.ktaVOIColor);

    setButtonBackground(sectorsColorButton, cData.sectorsColor);

    setButtonBackground(rayColorButton, cData.rayColor);
    rayMaxDistLineEdit->setText(QString::number(cData.rayDistMax));

    setButtonBackground(traceColorButton, cData.traceColor);
    setButtonBackground(traceLogBookColorButton, cData.traceLBColor);
    setButtonBackground(traceLBTextColor, cData.traceLBTextColor);
}

void SceneCustomazingWindow::adColorChange()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    const QColor color = QColorDialog::getColor(QColor(button->text()), this, "Выбрать цвет", QColorDialog::ShowAlphaChannel);

    setButtonBackground(button, color);

    if (button == adGrideColorButton) {
        emit adChangeGrideColor(color);
    }
    else if (button == adGrideTextColorButton) {
        emit adChangeTextColor(color);
    }
    else if (button == adBackGroundColorButton) {
        emit adChangeBackGroundColor(color);
    }
    else if (button == ktaPOIColorButton) {
        emit ktaColorChangeSignal(true, color);
    }
    else if (button == ktaVOIColorButton) {
        emit ktaColorChangeSignal(false, color);
    }
    else if (button == sectorsColorButton) {
        emit sectorsColorChangeSignal(color);
    }
    else if (button == rayColorButton) {
        emit rayColorChangeSignal(color);
    }
    else if (button == traceColorButton) {
        emit traceColorChangeSignal(color);
    }
    else if (button == traceLogBookColorButton) {
        emit traceLBColorChangeSignal(color);
    }
    else if (button == traceLBTextColor) {
        emit traceLBTextColorChangeSignal(color);
    }
}

void SceneCustomazingWindow::adTextChange()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(sender());

    if (lineEdit == rayMaxDistLineEdit) {
        quint16 value = lineEdit->text().toUInt();
        if (value > 10 && value < 300) {
            emit rayMaxDistChangeSignal(value);
        }
    }
    /*quint16 value = lineEdit->text().toUInt();
    if (lineEdit == adGrideDistMaxLineEdit) {
        azDistconfig.grideDistMax = value;
        emit adChangeDistMax(value);
    }
    else if (lineEdit == adGrideDistDiscretLineEdit) {
        azDistconfig.grideDistDiscret = value;
        emit adChangeDistDiscret(value);
    }
    else if (lineEdit == adGrideAzDiscretLineEdit) {
        azDistconfig.grideAzDiscret = value;
        emit adChangeAzDiscret(value);
    }
    else if (lineEdit == adGrideTextSizeLineEdit) {
        azDistconfig.textSize = value;
        emit adChangeTextSize(value);
    }*/
}

void SceneCustomazingWindow::adFlagChecked()
{
    QCheckBox *check = qobject_cast<QCheckBox *>(sender());

    if (check == adGrideDistTextCheck) {
        emit adDistMarkChecked(check->isChecked());
    }
    else if (check == adGrideAzTextCheck) {
        emit adAzMarkChecked(check->isChecked());
    }
}

void SceneCustomazingWindow::adTextSizeChanged()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (button == adTextSizeInc) {
        emit adChangeTextSize(Increas);
    }
    else if (button == adTextSizeDec) {
        emit adChangeTextSize(Decreas);
    }
    else if (button == adTextSizeRst) {
        emit adChangeTextSize(Reset);
    }
    else if (button == ktaPOISizeInc) {
        emit ktaSizeChangeSignal(true, Increas);
    }
    else if (button == ktaPOISizeDec) {
        emit ktaSizeChangeSignal(true, Decreas);
    }
    else if (button == ktaPOISizeRst) {
        emit ktaSizeChangeSignal(true, Reset);
    }
    else if (button == ktaVOISizeInc) {
        emit ktaSizeChangeSignal(false, Increas);
    }
    else if (button == ktaVOISizeDec) {
        emit ktaSizeChangeSignal(false, Decreas);
    }
    else if (button == ktaVOISizeRst) {
        emit ktaSizeChangeSignal(false, Reset);
    }
    else if (button == traceTextSizeInc) {
        emit traceTextSizeChangeSignal(Increas);
    }
    else if (button == traceTextSizeDec) {
        emit traceTextSizeChangeSignal(Decreas);
    }
    else if (button == traceTextSizeRst) {
        emit traceTextSizeChangeSignal(Reset);
    }
}

void SceneCustomazingWindow::themeChange()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button == lightThemeButton) {
        lightThemeButton->setChecked(true);
        darkThemeButton->setChecked(false);
        customThemeButton->setChecked(false);
        emit themeChangedSignal(ThemeEnum::Light);
        BaseWidget::triggeredBackgroundColor(false);
    }
    else if (button == darkThemeButton) {
        lightThemeButton->setChecked(false);
        darkThemeButton->setChecked(true);
        customThemeButton->setChecked(false);
        emit themeChangedSignal(ThemeEnum::Dark);
        BaseWidget::triggeredBackgroundColor(true);
    }
    else if (button == customThemeButton) {
        lightThemeButton->setChecked(false);
        darkThemeButton->setChecked(false);
        customThemeButton->setChecked(true);
        emit themeChangedSignal(ThemeEnum::Custom);
    }
}

void SceneCustomazingWindow::setButtonBackground(QPushButton *button, const QColor &color)
{
    if (color.isValid()) {
        QPalette Pal(button->palette());
        Pal.setColor(QPalette::Button, color);

        button->setText(color.name(QColor::HexArgb));
        button->setPalette(Pal);
        button->setAutoFillBackground(true);
    }

    //QString qss = QString("background-color: %1").arg(color.name());
//    QString qss = QString("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
//                          "stop:0 rgba(%1, %2, %3, 150), "
//                          "stop:1 rgba(%1, %2, %3, 250))").
//            arg(color.red()).arg(color.green()).arg(color.blue());
//    button->setStyleSheet(qss);
}
