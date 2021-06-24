#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QQmlApplicationEngine>
#include <QThread>

#include "widget.h"
#include "detectionsectorwidget.h"
#include "sectorsviewerwidget.h"
#include "datahandler.h"
#include "mainwidgetcontroller.h"
#include "controlpanelwidget.h"
#include "scenecustomazingwindow.h"
#include "TcpHandler/incomingdatahandler.h"
#include "customdata.h"
#include "ktainfowindow.h"
#include "customplotter.h"
#include "dspwidget.h"
//#include "circlepalette.h"
#include "signalnoiseratiowidget.h"
#include "mapdebugger.h"

#include "tracewidget.h"


class UIController : public QObject
{
    Q_OBJECT
public:
    explicit UIController(QObject *parent = nullptr);
    ~UIController();

signals:
    void openCloseQML(bool);
    void changeProjection(bool);
    void windowState(WidgetTypes type, bool open);

    //void addMark(RLSOPlotMessage msg, bool isPOI);
    void addRaySet(RaySet raySet);
    void addTrace(RLSOaimMessage msg);

private slots:
    /*void testKTAMsg();
    void testTraceMsg();
    void testTraceMsg2();
    void testTraceMsg3();
    void testTraceMsg4();
    void testRayMsg();*/

private:
    void initTestConnection();
    void initControlPanel();
    void initTcpHandler();
    void initSceneCustomizationSignals();
    void initWidgetsInteractions();

private:
    Widget *backgroundWidget,
     *backgroundWidget2;
    DetectionSectorWidget *settingWidget;
    SectorsViewerWidget *sectorsViewer;
    //MainWidgetController *mainWidgetController;
    MainWidget *mainWidget;
    ControlPanelWidget *controlPanel;
    SceneCustomazingWindow *sceneCustomazingWindow;
    KTAInfoWidget *ktaInfoWidget;
    DSPSettingWidget *dspSettingWidget;
    //ColorSchemeWidget *colorSchemeWidget;
    SignalNoiseRatioWidget *snrWidget;
    MapDebugger *mapDebugger;

    SectorData *sectorsData;
    TrackWidget *trackWidget;
    DSPWidget *dspWidget;

    QQmlApplicationEngine engine;
    IncomingDataHandler *incomingDataHandler;
    QThread *tcpThread;

    CustomData *customData;

};
#endif // UICONTROLLER_H
