#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QThread>

#include "widget.h"
#include "Widgets/Map/mapdebugger.h"
#include "TcpHandler/incomingdatahandler.h"


class UIController : public QObject
{
    Q_OBJECT
public:
    explicit UIController(QObject *parent = nullptr);
    ~UIController();


signals:
    void sendMsg(QByteArray msg);

private:
    void initTcpHandler();
    void initWidgetsInteractions();


private:
    Widget *backgroundWidget;

    MapDebugger *mapDebugger;

    IncomingDataHandler *incomingDataHandler;
    QThread *tcpThread;


};
#endif // UICONTROLLER_H
