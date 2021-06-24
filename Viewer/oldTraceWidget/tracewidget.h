#ifndef TRACEWIDGET_H
#define TRACEWIDGET_H

#include "basewidget.h"
#include "customplotter.h"
#include "global.h"

class QTableView;
class QStandardItem;

/*enum ComboBoxDelegateType {
    TypeDSP,
    TargetDSP,
    PlottingDSP,
    PriorityType
};*/

namespace TableAttributes {

const QString offStr("Откл"), onStr("Вкл"),
                normalPriorityStr("Обычный"),
                hightPriorityStr("Высокий"),
                dsp2Str("2 мс"), dsp20Str("20 мс"),
                reflSignal("Отр"),
                respSignal("Отв"),
                reflDSP("Отр + ДСП"),respDSP("Отв + ДСП"),
                reflRespSignal("Отр и Отв");

enum ColumnName {
    TrackID = 0,
    Priority = 1,
    WorkMode = 2,
    Letter = 3,
    DSP = 4,
    CT = 5,
    Plotting = 6,
    Trace = 7
};
}





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
    TrackInfo() : dspType(DSPType::None), isConvergingTargets(false),
    isPriority(false), isPlotting(false), drawTrace(false), extendCounter(0),
    workMode(WorkMode::ReflectedSignal){}
    RLSOaimMessage msg;
    DSPType dspType;
    bool isConvergingTargets;
    bool isPriority;
    bool isPlotting;
    bool drawTrace;
    quint8 extendCounter;
    int letter;

    enum WorkMode {
        ReflectedSignal = 0,
        ResponseSignal = 1,
        ReflectedDSP = 2,
        ResponseDSP = 3,
        ReflectedAndResponse = 4
    } workMode;
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

public slots:
    void customMenuForTable(QPoint pos);
    void addTraceMark(RLSOaimMessage msg);
    void eraseOldTrace(quint32 idTrace);

    void interactiveActionsWithTrack(quint32 id, ActionsWithTrack action);

private slots:
    void dataInModelChanged(QStandardItem *item);

private:
    void initMenu();
    //void genMessageToVoi(quint32 id);

private:
    QTableView *tableView;
    QMenu *tableMenu;
    CustomPlotterWidget *plotterWidget;
    MapOfTrack mapOfTrack;

    quint32 ctCounter, plottingCounter, traceCounter, dspCounter;
    const quint32 ctLimit, plottingLimit, traceLimit, dspLimit;
};

#endif // TRACEWIDGET_H
