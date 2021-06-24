#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include <QObject>
#include <QColor>

#include "global.h"

class CustomData : public QObject
{
    Q_OBJECT
public:
    explicit CustomData(QObject *parent = nullptr);
    void initDefaultTheme();

public slots:
    void backgroundColorChangeSlot(QColor color);

    void grideColorChangeSlot(QColor color);
    void grideTextColorChangeSlot(QColor color);
    void grideTextSizeChangeSlot(const TextSizeAction flag);
    void grideAzMarkOnSlot(bool flag);
    void grideDistMarkOnSlot(bool flag);

    void ktaColorChangeSlot(bool isPOI, QColor color);
    void ktaSizeChangeSlot(bool isPOI, const TextSizeAction flag);

    void sectorsColorChangeSlot(const QColor color);

    void rayColorChangeSlot(const QColor color);
    void rayMaxDistChangeSlot(const float value);

    void traceColorChangeSlot(const QColor color);
    void traceLBColorChangeSlot(const QColor color);
    void traceLBTextColorChangeSlot(const QColor color);
    void traceTextSizeChangeSlot(const TextSizeAction flag);

    void themeChangeSlot(ThemeEnum theme);

signals:
    void backgroundColorChangeEcho(QColor color);

    void grideColorChangeEcho(QColor color);
    void grideTextColorChangeEcho(QColor color);
    void grideTextSizeChangeEcho(const TextSizeAction flag, float value);
    void grideAzMarkOnEcho(bool flag);
    void grideDistMarkOnEcho(bool flag);

    void ktaColorChangeEcho(bool isPOI, QColor color);
    void ktaSizeChangeEcho(bool isPOI, const TextSizeAction flag, const float value);

    void sectorsColorChangeEcho(const QColor color);

    void rayColorChangeEcho(const QColor color);
    void rayMaxDistChangeEcho(const float value);

    void traceColorChangeEcho(const QColor color);
    void traceLBColorChangeEcho(const QColor color);
    void traceLBTextColorChangeEcho(const QColor color);
    void traceTextSizeChangeEcho(const TextSizeAction flag, const float value);

    void initCustomData(const SceneCustomDataInit& cData);

private:
    QColor backgroundColor;

    QColor grideColor;
    QColor grideTextColor;
    float grideTextSize;
    bool grideAzMarkOn;
    bool grideDistMarkOn;

    SceneCustomDataInit darkTheme, lightTheme, customTheme;

};

#endif // CUSTOMDATA_H
