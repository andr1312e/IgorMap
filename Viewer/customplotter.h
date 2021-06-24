#ifndef CUSTOMPLOTTER_H
#define CUSTOMPLOTTER_H

#include <QStyledItemDelegate>
#include <QListView>
#include "basewidget.h"
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_scale_widget.h>
#include <circlepalette.h>
#include <QSet>
#include <fftw3.h>

class QTimer;
class QTableView;

enum ColorMap
{
    RGBMap,
    HueMap,
    IndexMap,    
    AlphaMap
};

/*struct DSPDataInfo {
    DSPDataInfo() : N(0), M(0), data() {}
    quint32 N,M;
    QVector<float> data;
};

class DSPDataHandler : public QObject {
    Q_OBJECT
public:
    explicit DSPDataHandler(QObject *parent = nullptr);
    ~DSPDataHandler();

signals:
    void dataReady(DSPDataInfo data);

public slots:
    void newData(quint32 N, quint32 M, QVector<qint16> matrix);
    void deletePlan();

private:
    float moduleOfComplexValue(qreal &real, qreal &imag);

private:
    bool isFFTInit;
    fftw_complex *complexMatrix;
    fftw_plan fftwPlan;

    DSPDataInfo resultInfo;
};*/


class SpectrogramData : public QwtMatrixRasterData {

public:
    SpectrogramData();
    SpectrogramData(quint16 xMax, quint16 yMax);
    void refreshMatrix();
    void updateMatrix(const quint32 &n, const quint32 &m, const QVector<qreal> &vector);
    void setBackground();
};

class CustomPlotterWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit CustomPlotterWidget(qint32 _targetID, bool _displayPlot = true, QWidget *parent = nullptr);
    ~CustomPlotterWidget();

    void updateData(const quint32 &n, const quint32 &m, const quint32 &counter, const QVector<qreal> &vector);
    void forceSendColorRangesToScene();

signals:
    void setPositionOnVectorOfDSP(const qint32 target, quint32 pos);
    void sendColorRangesToScene(const qint32 target, ColorRanges colorRanges);

public slots:
    void showContour( bool on );
    void showSpectrogram( bool on );
    void setColorMap( int );
    void setColorsMap(const ColorsMap &colors );
    void setAlpha( int );
    void setAntiAlasing(int on);

    void updatePlotSlot();
    void pannerHandler(int dx,int dy);
    void zoomHandler(const QRectF & rect);

    void schemeChangedSlot(QString nameScheme, QString newNameScheme, QVector<QColor> colors, QVector<int> ranges);
    void schemeDeletedSlot(QString nameScheme);

private:
    void setItemToPresetComboBox(const quint32 &index, const MapOfColorRanges::iterator &itemOfColorMap);
    void createColorArray(const ColorRanges &colorRanges);

private slots:
    void startStopClicked();
    void sliderOffset();
    void timerTimeout();

    void currentSchemeChanged();

private:
    QwtPlot *plot;
    QwtPlotSpectrogram *d_spectrogram;
    SpectrogramData *sp_data;

    ColorSchemeWidget *colorSchemeWidget;

    QSlider *sliderControl;
    BasePushButton *startStopButton;
    QComboBox *presetComboBox;

    QTimer *updatePlot;

    MapOfColorRanges mapOfColorRanges;

    int d_mapType;
    int d_alpha;    
    const quint16 dspRefreshRate;
    const qint32 targetID;
    const bool displayPlot;
};

class DSPSettingWidget : public BaseWidget {
    Q_OBJECT
public:
    explicit DSPSettingWidget(QWidget *parent = nullptr);

signals:
    void updateTraceInfoToDelegate(qint32 trackId, bool isReset);

public slots:
    void customMenuForTable(QPoint pos);
    void updateTraceInfo(qint32 trackId, bool isReset);

private:
    void initMenu();

private:
    QTableView *tableView;
    QMenu *tableMenu;
    CustomPlotterWidget *plotterWidget;
};

#endif // CUSTOMPLOTTER_H