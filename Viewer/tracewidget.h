#ifndef TRACEWIDGET_H
#define TRACEWIDGET_H

#include "basewidget.h"
//#include "customplotter.h"
#include "global.h"
#include <QStyledItemDelegate>

class QListView;
class QStandardItem;
class QGroupBox;
class QComboBox;
class QCheckBox;

/*enum ComboBoxDelegateType {
    TypeDSP,
    TargetDSP,
    PlottingDSP,
    PriorityType
};*/


class ComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ComboBoxItemDelegate(TableAttributes::ColumnName _type, QObject *parent = nullptr);
    ~ComboBoxItemDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    //void setTraceInfo(qint32 trackId, bool isReset);

public slots:
    void cbCommitData(int index);
    void cbResetData(int index);

private:
    TableAttributes::ColumnName type;
    //QSet<QString> setOfTargetName;
    //quint16 plottingCounter;
};

struct TrackInfo {
    TrackInfo() : workMode(TargetWorkMode::ReflectedSignal), workModeVOI(TargetWorkMode::ReflectedSignal),
        dspType(DSPType::None), isConvergingTargets(false),
        isPriority(false), isPlotting(false), drawTrace(false), extendCounter(0),
        becomeSpecialSector(false), isSpecialSectorPriority(false), timeToResetSpecialSector(15),
        isFirstEntry(true) {}

    friend bool operator==(const TrackInfo &l, const TrackInfo &r)
    {
        //bool returnedFlag = false;
        if (l.workMode != r.workMode)
            return false;
        if (l.isPriority != r.isPriority)
            return false;
        if (l.dspType != r.dspType)
            return false;
        if (l.isPlotting != r.isPlotting)
            return false;
        if (l.isConvergingTargets != r.isConvergingTargets)
            return false;
        if (l.workMode == TargetWorkMode::ResponseSignal ||
                l.workMode == TargetWorkMode::ResponseAndDSP ||
                l.workMode == TargetWorkMode::ReflectedAndResponse) {
            if (l.letter != r.letter)
                return false;
        }
        if (l.becomeSpecialSector != r.becomeSpecialSector)
            return false;
        else {
            if (l.isSpecialSectorPriority != r.isSpecialSectorPriority)
                return false;
            if (l.timeToResetSpecialSector != r.timeToResetSpecialSector)
                return false;
        }

        return true;
    }

    friend bool operator !=(const TrackInfo &l, const TrackInfo &r) {
        return !(l == r);
    }

    RLSOaimMessage msg;
    TargetWorkMode workMode, workModeVOI;
    DSPType dspType;
    bool isConvergingTargets;
    bool isPriority;
    bool isPlotting;
    bool drawTrace;
    quint8 extendCounter;
    quint32 letter;
    bool becomeSpecialSector;
    bool isSpecialSectorPriority;
    quint8 timeToResetSpecialSector;

    bool isFirstEntry;
};

using MapOfTrack = QMap<quint32, TrackInfo>;

class TrackWidget : public BaseWidget
{
    Q_OBJECT    

public:
    explicit TrackWidget(QWidget *parent = nullptr);

signals:
    void activatedTableItem(quint32 id, ActionsWithTrack action, quint32 addParameter);

    void msgToVOI(QByteArray msg);
    void activeTrackDrawing(quint32 id, bool isDrawing);

    void isDSPAvailableSignal();
    void insertDSP(qint32 trackID, DSPType type, bool isPlotting);

    void newTrack(quint32 trackID);
    void eraseTrack(quint32 trackID);

public slots:
    //void customMenuForTable(QPoint pos);
    void addTraceMark(RLSOaimMessage msg);
    void eraseOldTrace(quint32 idTrace);

    void interactiveActionsWithTrack(quint32 id, ActionsWithTrack action);
    void isDSPExceedingUsageLimit(bool resolutionToSwitchingOn, bool resolutionToPlottingOn);

    void changeDSPSlot(qint32 trackID, DSPType type, bool isPlotting);

private slots:
    void dataInModelChanged(QStandardItem *item);
    void listViewItemClicked(const QModelIndex &index);

    void currentModeChanged(int index);
    void currentDSPChanged(int index);
    void specialSectorSettingSwitching(int state);

    void acceptEffect();
    void clearEffect();
    void specialSectorGlobalAccept();

private:
    void initMenu();

    qint32 idFromString(QString str);
    //void genMessageToVoi(quint32 id);

    void testGenAimMessage();
    void generateMessageToVOI(quint32 trackID, TrackInfo &info);

private:
    QListView *listView;    
    QGroupBox *dspModeGroupBox, *optionsGroupBox, *specialSectorGroupBox;
    QWidget *localOptionsWidget;
    QComboBox *priorityCb, *workModeCb, *dspModeCb,
              *letterCb;
    QCheckBox *plottingDSPCheckBox, *specialSectorSwitchingCheckBox,
              *specialSectorPriorityCheckBox;
    QPushButton *acceptButton, *resetButton, *plottingDSPButton,
                *specialSectorGlobalButton, *ctAddButton;
    BaseLineEdit *specialSectorTimeLineEdit;

    //QMenu *tableMenu;
    //CustomPlotterWidget *plotterWidget;
    MapOfTrack mapOfTrack;

    quint32 ctCounter, plottingCounter, traceCounter, dspCounter;
    const quint32 ctLimit, plottingLimit, traceLimit, dspLimit;

    bool forcedBanOnPlottingDSP;
};

#endif // TRACEWIDGET_H
