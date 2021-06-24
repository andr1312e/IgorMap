#ifndef DSPWIDGET_H
#define DSPWIDGET_H

#include <basewidget.h>
#include <customplotter.h>
#include <QMap>
#include <fftw3.h>
#include <QDateTime>

class QListView;
class QCheckBox;
class QComboBox;
class QGroupBox;
class FFTWProcessor;
class QDateTime;
class QFile;

using VectorOfAmp = QVector<qreal>;
using VectorOfAmpGL = QVector<float>;
using VectorRawData = QVector<qint16>;

struct DSPInfo {
    DSPInfo() : type(DSPType::None), isPlotting(false) {}
    DSPInfo(DSPType _type, bool _isPlotting) : type(_type), isPlotting(_isPlotting) {}

    DSPType type;
    bool isPlotting;
};

struct DSPData {
    DSPData() : N(0), M(0), azm(0),ugm(0), data(), dataGL() {}
    DSPData(quint32 n, quint32 m, float _azm, float _ugm) :
        N(n), M(m), azm(_azm),ugm(_ugm), data(), dataGL() {}
    quint32 N, M;
    float azm, ugm;
    VectorOfAmp data;
    VectorOfAmpGL dataGL;
};

struct IndexedData {
    IndexedData() : setOfIndexes(), completeData() {}
    IndexedData(quint8 firstId, const quint32 dataSize) : setOfIndexes({firstId}), completeData(dataSize) {}
    QSet<quint8> setOfIndexes;
    QVector<qint16> completeData;
    DSPData dataFromMessage;
};

using MapOfIndexes = QMap<quint32, IndexedData>;

struct DSPDataInfo {
    DSPDataInfo() {}

    DSPType type;
    QVector<DSPData> vectorOfData;
    MapOfIndexes mapOfIndexes;

    CustomPlotterWidget *plotterWidget;
    QDateTime timeArrival;
};


struct CTInfo {
    CTInfo() : firstTrackID(0), secondTrackID(0), isAuto(false) {}

    quint32 firstTrackID;
    quint32 secondTrackID;

    bool isAuto;
};

struct FFTWInfo {
    FFTWInfo () : n(0), m(0), complexMatrix(nullptr), fftwPlan() {}

    quint32 n, m;

    fftw_complex *complexMatrix;
    fftw_plan fftwPlan;
};

using MapOfDSP = QMap<qint32, DSPInfo>;
using MapOfDSPData = QMap<qint32, DSPDataInfo>;
using MapOfPossibleTagets = QMap<qint32,bool>;
using MapOfFFTWInfo = QMap<qint32, FFTWInfo>;

class FFTWProcessor : public QObject {
    Q_OBJECT
public:
    explicit FFTWProcessor(QObject *parent = nullptr);
    ~FFTWProcessor();

signals:
    void processedData(qint32 targetID, quint32 counter, VectorOfAmp vector);

public slots:
    void doWork();
    void dspChangedSlot(qint32 targetID, bool isPlotting);
    void newDataForWork(qint32 targetID, quint32 counter, quint32 N, VectorRawData matrix);
    void setPlane(qint32 targetID, quint32 N, quint32 M);

private:
    float moduleOfComplexValue(qreal &real, qreal &imag);

private:
    MapOfFFTWInfo mapOfFFTWInfo;

    quint32 currentCounter;
    VectorOfAmp resultMatrix;
};

class DSPDataHandler : public QObject {
    Q_OBJECT
public:
    explicit DSPDataHandler(QObject *parent = nullptr);
    ~DSPDataHandler();

    void parseDSPFile(QFile &fileWithData);

signals:
    void dspChanged(qint32 targetID, bool isPlotting);
    void prepareFFTWSignal(qint32 targetID, quint32 N, quint32 M);
    void dataReadyForProcessing(qint32 targetID, quint32 index, quint32 N, VectorRawData matrix);

    void dspPackToScene(qint32 targetID, QSharedPointer<QVector<DSPData>> sharedVector);
    void sendColorRangesOnSceneRepeaterSignal(const qint32 target, ColorRanges colorRanges);
    void deleteDSPFromScene(qint32 targetID);

public slots:
    void dspMessageHandler(RLSODSPDataMessage msg);

    void prepareDSPInfo(qint32 targetID, DSPType type, bool isPlotting);
    void setData(qint32 targetID, quint32 counter, VectorOfAmp vector);

    void showPlot(qint32 targetID);

    void setPositionOnVectorOfDSPSlot(const qint32 target, quint32 pos);
    void setPositionOnVectorOfDSPPleerSlot(const qint32 target, quint32 pos);

    void sendColorRangesOnSceneRepeaterSlot(const qint32 target, ColorRanges colorRanges);

private:
    float moduleOfComplexValue(qint16 &real, qint16 &imag);
    void saveDataOnDisk(MapOfDSPData::iterator currentItem);

private:
    MapOfDSPData mapOfDSPData;

    //DSPDataInfo resultInfo;
    QThread *threadObject;
    FFTWProcessor *fftwProcessorObject;

    const quint16 maxPartOfData;
    const QString dateFormat, extensionOfFiles;

    MapOfDSPData mapOfDSPDataForPleer;
    QString currentFile;

    //ColorSchemeWidget *colorSchemeWidget;
    CustomPlotterWidget *plotterWidget;
};

class DSPWidget : public BaseWidget
{
    Q_OBJECT
public:
    DSPWidget(QWidget *parent = nullptr);
    DSPDataHandler *getDSPDataHandler() const;

signals:
    void isExceedingUsageLimitSignal(bool resolutionToSwitchingOn, bool resolutionToPlottingOn);
    void changeDSP(qint32 targetID, DSPType type, bool isPlotting);

    void updateComboBoxWithTargetsSignal();
    void showDSPPlot(qint32 targetID);

public slots:
    void dspAvailabilityRequest();
    void insertDSP(qint32 targetID, DSPType type, bool isPlotting);
    void removeDSP(qint32 targetID);

    void newTarget(qint32 targetID);
    void clearTarget(qint32 targetID);

private:
    void initMenu();
    void initDSPList();

    void updateFields(QMap<qint32, DSPInfo>::iterator &itemOfMap);
    void clearFields();

    qint32 idFromString(QString str);
    qint32 idFromSelectedItemOfList();
    qint32 idFromSelectedItemOfComboBox();

private slots:
    void customMenuForList(QPoint pos);
    void listViewItemClicked(const QModelIndex &index);
    void updateComboBoxWithTargetsSlot();    
    void plottingToggled();

    void acceptEffectDSP();
    void clearEffectDSP();
    void acceptEffectCT();
    void clearEffectCT();

    void showHidePlotterWidget();

    void openDSPFile(const QModelIndex &index);

private:
    QListView *listView, *dspListView;
    QGroupBox *listDSPGroupBox, *parametersDSPGroupBox, *ctGroupBox, *pleerDSPGroupBox;
    QCheckBox *plottingDSPCheckBox, *autoCTCheckBox;
    QComboBox *dspModeCb, *numberOfTargetCb, *track1Cb, *track2Cb;
    QPushButton *plottingDSPButton, *plottingCTButton, *startCTButton,
                *acceptDSPButton, *clearDSPButton,
                *acceptCTButton, *clearCTButton;

    MapOfPossibleTagets mapOfPossibleTargets;
    MapOfDSP mapOfDSP;
    quint16 dspCounter, dspPlottingCounter;
    const quint16 maxDSP, maxDSPPlotting;
    const qint32 incorrectID;

    QMenu *tableMenu;    

    DSPDataHandler *dspDataHandler;    

    const QString dataPathStr;
    int replacementRow;
};

Q_DECLARE_METATYPE(RLSODSPDataMessage)

#endif // DSPWIDGET_H
