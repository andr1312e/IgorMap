#ifndef SECTORSVIEWERWIDGET_H
#define SECTORSVIEWERWIDGET_H

#include "basewidget.h"
#include "global.h"
#include <QSharedPointer>
#include <QStandardItemModel>
#include <QMessageBox>

class QTableView;
class QStackedLayout;
class QRadioButton;
class QCheckBox;
class QGroupBox;
class QComboBox;
class QTimeEdit;
class QListView;

struct SectorsPrivateInfo {
    SectorsPrivateInfo() :
        sectorType(StaticPlacement),
        distMin(0), distMax(0),
        azMin(0), azMax(0),
        ugmMin(0), ugmMax(0),
        vrMin(0), vrMax(0),
        model(new QStandardItemModel()),
        //dist(0), az(0), ugm(0),
        setOfModes(3,1), freqOfRays(3,5),
        workIsOn(false), dropingIsOn(false), dropingSec(15),
        workMode(TargetWorkMode::ReflectedSignal),
        dspType(DSPType::None),
        isPlotting(false),
        letter()
    {

        QStringList hHeader;
        hHeader.append("t");
        hHeader.append("x");
        hHeader.append("y");
        hHeader.append("z");

        model->setHorizontalHeaderLabels(hHeader);
    }

    /*void clearModel() {
        model->removeRows(0, model->rowCount());
    }*/

    SectorType sectorType;

    float distMin, distMax;
    float azMin, azMax;
    float ugmMin, ugmMax;
    float vrMin, vrMax;

    QStandardItemModel *model;

    //float dist, az, ugm;

    QVector<quint8> setOfModes, freqOfRays;
    bool workIsOn, dropingIsOn;
    float dropingSec;

    TargetWorkMode workMode;
    DSPType dspType;
    bool isPlotting;
    QSet<quint32> letter;
};

using VectorOfSectorsPrivateInfo = QVector <QPair <ItemState, SectorsPrivateInfo>>;
using VectorOfTimers = QVector<QTimer *>;
using VectorOfBlinkingTimers = QVector<QPair<QTimer *, quint8>>;

using VectorOfMessageBox = QVector<QMessageBox*>;
using VectorOfMessageBoxState = QVector<QPair<ItemState, quint8>>;
using VectorOfStartPointOfMessageBox = QVector<QPair<QPoint, qint16>>;

class MessageBoxWindowManager : public QObject {
    Q_OBJECT
public:
    explicit MessageBoxWindowManager(QObject *parent = nullptr);
    ~MessageBoxWindowManager();
    void addMessageBoxOnDisplay(quint8 id, quint8 timeLeft);
    void updateMessageBoxOnDisplay(quint8 id, quint8 timeLeft);
    void closeMessageBox(quint8 id);

signals:
    void userAnswer(quint8 id, QMessageBox::ButtonRole role);

private slots:
    void messageBoxButtonClick(QAbstractButton *button);

private:
    const quint8 maxSectors;
    VectorOfMessageBox messageBoxVector;
    VectorOfMessageBoxState statesOfMessageBox;
    VectorOfStartPointOfMessageBox startPointOfMessageBoxs;
    QSize standardSize;
    QRect availableGeometry;
};


class SectorRemover : public QObject {
    Q_OBJECT
public:
    explicit SectorRemover(QObject *parent = nullptr);
    ~SectorRemover();

    void removeIdAfter(quint8 id, quint32 sec);
    void stopDroppingTimerOnId(quint8 id);
    void stopBlinkingTimerOnId(quint8 id);
    void resetAllOnId(quint8 id);

public slots:
    void userAnswerHandler(quint8 id, QMessageBox::ButtonRole role);

signals:
    void sectorBlinking(quint8 id, ActionsWithBlinkingSector action);
    void deleteSectorByTimeout(quint8 id);

    void addMessageBox(quint8 id, quint8 timeLeft);
    void updateMessageBox(quint8 id, quint8 timeLeft);
    void closeMessageBox(quint8 id);

    void restartSectorBlinking(quint8 id);

private slots:
    void timeoutDropping();
    void timeoutBlinking();

private:
    const quint8 maxSectors, maxBlinkingSec;
    VectorOfTimers droppingTimers;
    VectorOfBlinkingTimers blinkingTimers;

    MessageBoxWindowManager *messageBoxManager;
};

class SectorsViewerWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit SectorsViewerWidget(QWidget *parent = nullptr);
    SectorRemover *getSectorRemoverRef() const;

signals:
    void presetSector(const quint8 index, SharedSectorParameters sharedSector);
    void newSector(const quint8 index, SharedSectorParameters sharedSector);
    void excludeSector(const quint8 index);
    void deleteSector(const quint8 index);
    void addSectorsToVOI(QByteArray msg);
    void deleteSectorToVOI(QByteArray msg);

    void setSectorInFocus(const quint8 index);
    void setSectorOutFocus();

    void dspActivationOnSector(qint32 targetID, DSPType type, bool isPlotting);
    void newSectorToDSPWidget(qint32 targetID);
    void clearSectorToDSPWidget(qint32 targetID);
    void isDSPAvailableSignal();

public slots:
    void openMainWidget();
    void repeaterNewSectorSignal(SharedSectorParameters sharedSector);
    void openWidgetWithCurrentParams(QPointF point);
    void targetingAddSlot(const QPointF point, bool isQuick);
    void targetingExcludeSlot(const QPointF point);
    void deleteSectorByTimeoutSlot(quint8 id);
    void restartSectorBlinking(quint8 id);

    void isDSPExceedingUsageLimit(bool resolutionToSwitchingOn, bool resolutionToPlottingOn);
    void changeDSPSlot(qint32 trackID, DSPType type, bool isPlotting);

private:
    void initTable();
    bool checkingForEmptyFields();
    bool checkingForModifyFields(SectorsPrivateInfo &sectorInfo);
    void clearLineEdit();
    void deg360TransitionCheck(float &ang);

    void generateMessageToVOI(quint32 trackID, SectorsPrivateInfo &info, bool isUpdate);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void acceptEffect();
    void clearEffect();
    void changeLayout();

    void addRow();
    void delRow();
    void itemChangeInTable(QStandardItem *item);

    void listViewItemClicked(const QModelIndex &index);
    void fillParametersField(const SectorsPrivateInfo &info);

    void autoButtonClicked();

    void dspModeChanged(int index);
    void workModeForVOIChanged(int index);
    void workModeChanged(int index);
    void userSettingChanged(int index);
    void letterSettingChanged(int index);

private:
    const quint16 maxSectors, defaultDropingSec, letterMax;
    QComboBox *setOfModesBox, *freqOfRaysBox;
    //QComboBox *numberBox;
    QGroupBox *numberGroupBox, *modeGroupBox,
                *parametersGroupBox, *dspModeGroupBox;
    BaseLineEdit *distMinLineEdit, *distMaxLineEdit,
                *azMinLineEdit, *azMaxLineEdit,
                *ugmMinLineEdit, *ugmMaxLineEdit,
                *vrMinLineEdit, *vrMaxLineEdit,
                *dist2LineEdit, *az2LineEdit, *ugm2LineEdit,
                *resetAfterLineEdit;

    QPushButton *acceptButton, *clearButton;
    QWidget *staticModeWidget, *traceModeWidget, *pointModeWidget;
    QStackedLayout *stackedLayout;

    QTableView *tableView;
    QListView *listView;
    QTimeEdit *timeEdit;
    BaseLineEdit *xLineEdit, *yLineEdit, *zLineEdit;
    QStandardItemModel *emptyModel;

    QCheckBox *autoButton, *workButton, *plottingDSPCheckBox;
    QRadioButton *staticModeRB, *traceModeRB, *pointModeRB;
    QComboBox *workModeCb, *dspModeCb, *letterCb, *workModeForVOICb;
    //SharedSectorParameters sector;
    //SharedSectorsVector sharedSectorData;

    VectorOfSectorsPrivateInfo vectorOfSectorsInfo;
    SectorRemover *sectorRemover;

    QVector<quint8> preSetVOIParams;

    bool forcedBanOnPlottingDSP;
};

#endif // SECTORSVIEWERWIDGET_H
