#include "signalnoiseratiowidget.h"

#include <qwt_plot.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_canvas.h>
#include <qwt_legend_label.h>
#include <qwt_picker_machine.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_zoomer.h>
#include <qwt_color_map.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>

#include <QBoxLayout>
#include "customplotter.h"


class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( QWidget *canvas ):
        QwtPlotZoomer( canvas )
    {
        setTrackerMode( QwtPicker::AlwaysOn );
        setRubberBand( QwtPicker::CrossRubberBand );

        // RightButton: zoom out by 1
        // Ctrl+RightButton: zoom out to full size

        /*setMousePattern( QwtEventPattern::MouseSelect2,
                         Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,
                         Qt::RightButton );*/
    }

protected:
    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::white );
        bg.setAlpha( 200 );

        //QwtText text = QwtPlotZoomer::trackerTextF( pos );
        //text.setBackgroundBrush( QBrush( bg ) );

        QString strCoords = QString("%1, %2").arg(qFloor(pos.x())).arg(qFloor(pos.y()));
        QwtText text(strCoords);
        text.setBackgroundBrush( QBrush( bg ) );

        return text;
    }
};

struct compareX
{
    inline bool operator()( const double x, const QPointF &pos ) const
    {
        return ( x < pos.x() );
    }
};

CurveTracker::CurveTracker( QWidget *canvas ):
    QwtPlotPicker( canvas )
{
    setTrackerMode( QwtPlotPicker::AlwaysOn );
    setRubberBand( CrossRubberBand );

    setStateMachine( new QwtPickerTrackerMachine() );
}

QRect CurveTracker::trackerRect( const QFont &font ) const
{
    QRect r = QwtPlotPicker::trackerRect( font );

    // align r to the first curve

    /*const QwtPlotItemList curves = plot()->itemList( QwtPlotItem::Rtti_PlotCurve );
    if ( curves.size() > 0 )
    {
        QPointF pos = invTransform( trackerPosition() );

        const QLineF line = curveLineAt(
            static_cast<const QwtPlotCurve *>( curves[0] ), pos.x() );
        if ( !line.isNull() )
        {
            const double curveY = line.pointAt(
                ( pos.x() - line.p1().x() ) / line.dx() ).y();

            pos.setY( curveY );
            pos = transform( pos );

            r.moveBottom( pos.y() );
        }
    }*/

    return r;
}

QwtText CurveTracker::trackerTextF( const QPointF &pos ) const
{
    QColor bg( Qt::white );
    bg.setAlpha( 200 );

    //QwtText text = QwtPlotZoomer::trackerTextF( pos );
    //text.setBackgroundBrush( QBrush( bg ) );

    QString strCoords = QString("%1, %2").arg(qFloor(pos.x())).arg(qFloor(pos.y()));
    QwtText text(strCoords);
    text.setBackgroundBrush( QBrush( bg ) );

    return text;
}


SignalNoiseRatioWidget::SignalNoiseRatioWidget(QWidget *parent) : BaseWidget(WidgetTypes::SignalNoiseRatio, parent),
    xMaxInterval(90), yMaxInterval(xMaxInterval)
{
    setTitle("Отношение Сигнал/Шум");

    plot = new QwtPlot();
    //plot->setStyleSheet("QWidget {background-color: black;}");
    plot->setTitle( "График" );
    //plot->setCanvasBackground( Qt::black );

    //plot->insertLegend( new QwtLegend() );

    plot->setAutoReplot( true );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setFrameStyle( QFrame::NoFrame );
    canvas->setLineWidth( 1 );
    canvas->setPalette( Qt::white );
    plot->setCanvas( canvas );

    curveAz = new QwtPlotCurve();
    curveAz->setPen( QColor::fromRgbF(0.36f, 0.31f, 0.80f, 1.), 2 ),
    curveAz->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    /*QwtSymbol *symbolAz = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 2, 2 ) );
    curveAz->setSymbol( symbolAz );*/

    /*QPolygonF points;
    points << QPointF( 0.0, 40.4 ) << QPointF( 10.0, 30.0 )
        << QPointF( 20.0, 40.5 ) << QPointF( 30.0, 60.8 )
        << QPointF( 40.0, 70.9 ) << QPointF( 50.0, 70.1 );
    curveAz->setSamples( points );*/

    curveAz->attach( plot );

    curveUgm = new QwtPlotCurve();
    curveUgm->setPen( QColor::fromRgbF(0.90f, 0.31f, 0.42f, 1.), 2 ),
    curveUgm->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    /*QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Triangle,
        QBrush( Qt::yellow ), QPen( Qt::white, 2 ), QSize( 2, 2 ) );
    curveUgm->setSymbol( symbol );*/

    /*points.clear();
    points << QPointF( 0.0, 30.4 ) << QPointF( 20.0, 30.0 )
        << QPointF( 50.0, 40.5 ) << QPointF( 10.0, 60.8 )
        << QPointF( 15.0, 70.9 ) << QPointF( 65.0, 70.1 );
    curveUgm->setSamples( points );*/

    curveUgm->attach( plot );

    initData();

    // Legend
    /*QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );
    plot->insertLegend( legend, QwtPlot::TopLegend );*/

    // Axes
    plot->enableAxis( QwtPlot::yLeft );
    plot->enableAxis( QwtPlot::xBottom );

    // Axe X bottom
    plot->setAxisTitle( QwtPlot::xBottom, "Аз [град]" );
    plot->setAxisScale(QwtPlot::xBottom, 0., xMaxInterval, 10.);
    //setAxisLabelRotation( QwtPlot::xBottom, -50.0 );
    plot->setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    plot->setAxisTitle( QwtPlot::yLeft, "Угм [град]" );
    plot->setAxisScale(QwtPlot::yLeft, 0., yMaxInterval, 10.);
    //setAxisLabelRotation( QwtPlot::xBottom, -50.0 );
    plot->setAxisLabelAlignment( QwtPlot::yLeft, Qt::AlignLeft | Qt::AlignBottom );

    // Grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    //grid->enableX( true );
    //grid->enableY( true );
    //grid->enableXMin(true);
    //grid->enableYMin(true);
    //grid->setXDiv(QwtScaleDiv(5,10));
    //grid->setYDiv(QwtScaleDiv(5,10));
    grid->setMajorPen( Qt::darkGray, 1.0, Qt::DotLine);
    grid->setMinorPen( Qt::darkGray, 1.0, Qt::DotLine );
    grid->attach( plot );

    CurveTracker* tracker = new CurveTracker( plot->canvas() );
    tracker->setRubberBandPen( QPen( "MediumOrchid" ) );

    QwtPlotZoomer* zoomer = new QwtPlotZoomer( plot->canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );
    const QColor c( Qt::blue );
    zoomer->setRubberBandPen( c );
    //zoomer->setTrackerPen( c );

    connect(zoomer, SIGNAL(zoomed(QRectF)), this, SLOT(zoomHandler(QRectF)));

    QwtPlotPanner *panner = new QwtPlotPanner( plot->canvas() );
    panner->setAxisEnabled( QwtPlot::yRight, false );
    panner->setMouseButton( Qt::MiddleButton );

    connect(panner, SIGNAL(panned(int,int)), this, SLOT(pannerHandler(int,int)));

    //auto ticks = grid->xScaleDiv().ticks(QwtScaleDiv::MinorTick);

    QwtPlotSpectrogram *d_spectrogram = new QwtPlotSpectrogram();
    //d_spectrogram->setRenderThreadCount( 4 ); // use system specific thread count
    d_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

    SpectrogramData *sp_data = new SpectrogramData(100,100);
    d_spectrogram->setData(sp_data);
    d_spectrogram->attach( plot );

    QwtScaleWidget *axis = plot->axisWidget( QwtPlot::yRight );
    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );
    d_spectrogram->setColorMap( new QwtLinearColorMap(Qt::black, Qt::red, QwtColorMap::RGB) );
    axis->setColorMap( zInterval, new QwtLinearColorMap(Qt::black, Qt::red, QwtColorMap::RGB) );
    d_spectrogram->setAlpha( 255 );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(plot);

    setLayout(mainLayout);

    connect(this, &SignalNoiseRatioWidget::updateSignal, this, &SignalNoiseRatioWidget::replot);
}

void SignalNoiseRatioWidget::setData(const QVector<QPointF> data, bool isAz)
{
    if (isAz) {
        curveAz->setSamples(data);
    }
    else {
        curveUgm->setSamples(data);
    }
    if (!isHidden())
        plot->replot();
}

void SignalNoiseRatioWidget::initData()
{
    QVector<QPointF> initData;
    for (quint16 index = 0; index != xMaxInterval + 1; index++) {
        initData.push_back(QPointF(index, 0));
    }
    curveAz->setSamples(initData);

    initData.clear();
    for (quint16 index = 0; index != yMaxInterval + 1; index++) {
        initData.push_back(QPointF(0, index));
    }
    curveUgm->setSamples(initData);

    if (!isHidden())
        plot->replot();
}

void SignalNoiseRatioWidget::replot()
{
    //plot->replot();
    qDebug() << "replot";
}

void SignalNoiseRatioWidget::pannerHandler(int dx, int dy)
{
    QwtPlotPanner *panner = qobject_cast<QwtPlotPanner *>(sender());
    QwtPlot *plot_ptr = panner->plot();

    QwtInterval intervalY = plot_ptr->axisInterval(QwtPlot::yLeft);
    QwtInterval intervalX = plot_ptr->axisInterval(QwtPlot::xBottom);

    //qDebug() << intervalX << intervalY;

    QwtInterval correctIntervalY;
    if (intervalY.minValue() < 0) {
        correctIntervalY.setMinValue(0);
    }
    else {
        correctIntervalY.setMinValue(intervalY.minValue());
    }
    if (intervalY.maxValue() > yMaxInterval) {
        correctIntervalY.setMaxValue(yMaxInterval);
    }
    else {
        correctIntervalY.setMaxValue(intervalY.maxValue());
    }

    QwtInterval correctIntervalX;
    if (intervalX.minValue() < 0) {
        correctIntervalX.setMinValue(0);
    }
    else {
        correctIntervalX.setMinValue(intervalX.minValue());
    }
    if (intervalX.maxValue() > xMaxInterval) {
        correctIntervalX.setMaxValue(xMaxInterval);
    }
    else {
        correctIntervalX.setMaxValue(intervalX.maxValue());
    }


    plot_ptr->setAxisScale(QwtPlot::yLeft, correctIntervalY.minValue(), correctIntervalY.maxValue());
    plot_ptr->setAxisScale(QwtPlot::xBottom, correctIntervalX.minValue(), correctIntervalX.maxValue());

    plot->replot();
}

void SignalNoiseRatioWidget::zoomHandler(const QRectF &rect)
{
    QwtPlotZoomer *zoomer = qobject_cast<QwtPlotZoomer *>(sender());
    //QwtPlot *plot_ptr = panner->plot();

    QRectF correctRect(rect);
    if (rect.x() < 0) {
        correctRect.setX(0);
    }
    else if (rect.x() > (xMaxInterval - 10)) {
        correctRect.setX(xMaxInterval - 10);
        if (rect.width() > 10)
            correctRect.setWidth(10);
    }
    if (rect.y() < 0) {
        correctRect.setY(0);
    }
    else if (rect.y() > (yMaxInterval - 10)) {
        correctRect.setY(yMaxInterval - 10);
        if (rect.height() > 10)
            correctRect.setHeight(10);
    }

    if (rect.right() > xMaxInterval) {
        correctRect.setWidth(xMaxInterval - rect.left());
    }

    if (rect.bottom() > yMaxInterval) {
        correctRect.setHeight(yMaxInterval - rect.top());
    }

    if (correctRect != rect) {
        zoomer->zoom(-1);
        zoomer->zoom(correctRect);

        plot->replot();
    }

    //qDebug() << rect;
    //qDebug() << zoomer->zoomBase();
}
