#include "customdata.h"

CustomData::CustomData(QObject *parent) : QObject(parent)
{
    darkTheme.backgroundColor = QColor::fromRgbF(.0f, .0f, .0f, 1);
    darkTheme.grideColor = QColor::fromRgbF(0.4f, 0.4f, 0.4f, 0.6f);
    darkTheme.grideTextColor = QColor::fromRgbF(0.60f, 0.55f, 0.09f, 0.7);
    darkTheme.grideTextSize = 0.1f;
    darkTheme.grideDistMark = true;
    darkTheme.grideAzMark = true;

    darkTheme.ktaPOIColor = QColor::fromRgbF(0.15f, 0.56f, 0.15f, 0.66f);
    darkTheme.ktaPOISize = 0.005;
    darkTheme.ktaVOIColor = QColor::fromRgbF(0.8f, 0.8f, 0.0f, 0.66f);
    darkTheme.ktaVOISize = 0.008;

    darkTheme.sectorsColor = QColor::fromRgbF(0.28f, 0.77f, 0.15f, 0.15f);

    darkTheme.rayColor = QColor::fromRgbF(0.3, 0.3, 0.3, 0.5);
    darkTheme.rayDistMax = 300;

    darkTheme.traceColor = QColor::fromRgbF(0.6,0.6,0.6,0.99);
    darkTheme.traceLBColor = QColor::fromRgbF(0.35,0.35,0.35,0.8);
    darkTheme.traceLBTextColor = QColor::fromRgbF(0.50f,0.45f,0.09f, 0.99);
    darkTheme.traceLBTextSize = 0.075f;

    lightTheme = darkTheme;

    lightTheme.backgroundColor = QColor::fromRgbF(.6f, .6f, .6f, 1);
    lightTheme.grideColor = QColor::fromRgbF(0.2f, 0.2f, 0.2f, 0.6f);
    lightTheme.grideTextColor = QColor::fromRgbF(0.80f, 0.8f, 0.09f, 0.7);
    lightTheme.ktaPOIColor = QColor::fromRgbF(0.15f, 0.56f, 0.15f, 0.66f);
    lightTheme.ktaVOIColor = QColor::fromRgbF(0.8f, 0.8f, 0.0f, 0.66f);
    lightTheme.sectorsColor = QColor::fromRgbF(0.28f, 0.77f, 0.15f, 0.15f);
    lightTheme.rayColor = QColor::fromRgbF(0.1, 0.1, 0.1, 0.2);
    lightTheme.traceColor = QColor::fromRgbF(0.12,0.12,0.12,1.);
    lightTheme.traceLBColor = QColor::fromRgbF(0.28,0.28,0.28,0.8);
    lightTheme.traceLBTextColor = QColor::fromRgbF(0.60f,0.55f,0.09f, 1);


    customTheme = darkTheme;
}

void CustomData::initDefaultTheme()
{
    emit initCustomData(customTheme);
}

void CustomData::grideColorChangeSlot(QColor color)
{
    customTheme.grideColor = color;
    emit grideColorChangeEcho(customTheme.grideColor);
}

void CustomData::backgroundColorChangeSlot(QColor color)
{
    customTheme.backgroundColor = color;
    emit backgroundColorChangeEcho(customTheme.backgroundColor);
}

void CustomData::grideTextColorChangeSlot(QColor color)
{
    customTheme.grideTextColor = color;
    emit grideTextColorChangeEcho(customTheme.grideTextColor);
}

void CustomData::grideTextSizeChangeSlot(const TextSizeAction flag)
{
    float value = 0;
    switch(flag) {
        case Increas: {
            customTheme.grideTextSize += 0.001;
            value = 0.001;
            break;
        }
        case Decreas:  {
            customTheme.grideTextSize -= 0.001;
            value = -0.001;
            break;
        }
        case Reset:  {
            customTheme.grideTextSize = darkTheme.grideTextSize;
            value = customTheme.grideTextSize;
            break;
        }
    }
    emit grideTextSizeChangeEcho(flag, value);
}

void CustomData::grideAzMarkOnSlot(bool flag)
{
    customTheme.grideAzMark = flag;
    emit grideAzMarkOnEcho(customTheme.grideAzMark);
}

void CustomData::grideDistMarkOnSlot(bool flag)
{
    customTheme.grideDistMark = flag;
    emit grideDistMarkOnEcho(customTheme.grideDistMark);
}

void CustomData::ktaColorChangeSlot(bool isPOI, QColor color)
{
    if (isPOI) {
        customTheme.ktaPOIColor = color;
    }
    else {
        customTheme.ktaVOIColor = color;
    }

    emit ktaColorChangeEcho(isPOI, isPOI ? customTheme.ktaPOIColor : customTheme.ktaVOIColor);
}

void CustomData::ktaSizeChangeSlot(bool isPOI, const TextSizeAction flag)
{
    float *pValue = nullptr;
    if (isPOI) {
        pValue = &customTheme.ktaPOISize;
    }
    else {
        pValue = &customTheme.ktaVOISize;
    }

    float value = 0;
    switch(flag) {
        case Increas: {
            *pValue += 0.001;
            value = 0.001;
            break;
        }
        case Decreas:  {
            *pValue -= 0.001;
            value = -0.001;
            break;
        }
        case Reset:  {
            if (isPOI) {
                customTheme.ktaPOISize = darkTheme.ktaPOISize;
            }
            else {
                customTheme.ktaVOISize = darkTheme.ktaVOISize;
            }
            value = *pValue;
            break;
        }
    }
    emit ktaSizeChangeEcho(isPOI, flag, value);
}

void CustomData::sectorsColorChangeSlot(const QColor color)
{
    customTheme.sectorsColor = color;
    emit sectorsColorChangeEcho(customTheme.sectorsColor);
}

void CustomData::rayColorChangeSlot(const QColor color)
{
    customTheme.rayColor = color;
    emit rayColorChangeEcho(customTheme.rayColor);
}

void CustomData::rayMaxDistChangeSlot(const float value)
{
    customTheme.rayDistMax = value;
    emit rayMaxDistChangeEcho(customTheme.rayDistMax);
}

void CustomData::traceColorChangeSlot(const QColor color)
{
    customTheme.traceColor = color;
    emit traceColorChangeEcho(customTheme.traceColor);
}

void CustomData::traceLBColorChangeSlot(const QColor color)
{
    customTheme.traceLBColor = color;
    emit traceLBColorChangeEcho(customTheme.traceLBColor);
}

void CustomData::traceLBTextColorChangeSlot(const QColor color)
{
    customTheme.traceLBTextColor = color;
    emit traceLBTextColorChangeEcho(customTheme.traceLBTextColor);
}

void CustomData::traceTextSizeChangeSlot(const TextSizeAction flag)
{
    float value = 0;
    switch(flag) {
        case Increas: {
            customTheme.traceLBTextSize += 0.001;
            value = 0.001;
            break;
        }
        case Decreas:  {
            customTheme.traceLBTextSize -= 0.001;
            value = -0.001;
            break;
        }
        case Reset:  {
            customTheme.traceLBTextSize = darkTheme.traceLBTextSize;
            value = customTheme.traceLBTextSize;
            break;
        }
    }
    emit traceTextSizeChangeEcho(flag, value);
}

void CustomData::themeChangeSlot(ThemeEnum theme)
{
    if (theme == ThemeEnum::Dark) {
        customTheme = darkTheme;
        initDefaultTheme();
    }
    else if (theme == ThemeEnum::Light) {
        customTheme = lightTheme;
        initDefaultTheme();
    }
    else if (theme == ThemeEnum::Light) {
        initDefaultTheme();
    }
}
