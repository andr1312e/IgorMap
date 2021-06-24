#ifndef SCENECUSTOMAZINGWINDOW_H
#define SCENECUSTOMAZINGWINDOW_H

#include "basewidget.h"
#include "global.h"
#include <QCheckBox>

class SceneCustomazingWindow : public BaseWidget
{
    Q_OBJECT
public:
    explicit SceneCustomazingWindow(BaseWidget *parent = nullptr);

public slots:
    void initCustomDataSlot(const SceneCustomDataInit& cData);

signals:
    void adChangeGrideColor(const QColor color);
    void adChangeTextColor(const QColor color);
    void adChangeBackGroundColor(const QColor color);
    void adChangeDistMax(const quint16 value);
    void adChangeDistDiscret(const quint16 value);
    void adChangeAzDiscret(const quint16 value);
    void adChangeTextSize(const TextSizeAction flag);
    void adDistMarkChecked(bool flag);
    void adAzMarkChecked(bool flag);

    void ktaColorChangeSignal(bool isPOI, QColor color);
    void ktaSizeChangeSignal(bool isPOI, const TextSizeAction flag);

    void sectorsColorChangeSignal(const QColor color);

    void rayColorChangeSignal(const QColor color);
    void rayMaxDistChangeSignal(const float value);

    void traceColorChangeSignal(const QColor color);
    void traceLBColorChangeSignal(const QColor color);
    void traceLBTextColorChangeSignal(const QColor color);
    void traceTextSizeChangeSignal(const TextSizeAction flag);

    void themeChangedSignal(ThemeEnum theme);

private slots:
    void adColorChange();
    void adTextChange();
    void adFlagChecked();
    void adTextSizeChanged();

    void themeChange();

private:
    void setButtonBackground(QPushButton *button, const QColor &color);

private:
    QPushButton *adGrideColorButton, *adGrideTextColorButton, *adBackGroundColorButton,
                *adTextSizeInc, *adTextSizeDec, *adTextSizeRst,
                *ktaPOIColorButton, *ktaVOIColorButton,
                *ktaPOISizeInc, *ktaPOISizeDec, *ktaPOISizeRst,
                *ktaVOISizeInc, *ktaVOISizeDec, *ktaVOISizeRst,
                *sectorsColorButton,
                *rayColorButton,
                *traceColorButton, *traceLogBookColorButton, *traceLBTextColor,
                *traceTextSizeInc, *traceTextSizeDec, *traceTextSizeRst,
                *lightThemeButton, *darkThemeButton, *customThemeButton;
    QLineEdit *rayMaxDistLineEdit;
    QCheckBox *adGrideDistTextCheck, *adGrideAzTextCheck;
};

#endif // SCENECUSTOMAZINGWINDOW_H
