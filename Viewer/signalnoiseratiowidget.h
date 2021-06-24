#ifndef SIGNALNOISERATIOWIDGET_H
#define SIGNALNOISERATIOWIDGET_H

#include "basewidget.h"
#include <qwt_plot_picker.h>

class QwtPlotCurve;
class QwtPlot;
class QwtText;

class CurveTracker: public QwtPlotPicker
{
public:
    CurveTracker( QWidget * );

protected:
    virtual QwtText trackerTextF( const QPointF & ) const;
    virtual QRect trackerRect( const QFont & ) const;

private:
    QString curveInfoAt( const QwtPlotCurve *, const QPointF & ) const;
    QLineF curveLineAt( const QwtPlotCurve *, double x ) const;
};

class SignalNoiseRatioWidget : public BaseWidget
{
    Q_OBJECT
public:
    SignalNoiseRatioWidget(QWidget *parent = nullptr);

public slots:
    void setData(const QVector<QPointF> data, bool isAz);

    void pannerHandler(int dx,int dy);
    void zoomHandler(const QRectF & rect);

private:
    void initData();

private slots:
    void replot();

private:
    QwtPlot *plot;
    QwtPlotCurve *curveUgm, *curveAz;

    const quint16 xMaxInterval, yMaxInterval;
};

#endif // SIGNALNOISERATIOWIDGET_H
