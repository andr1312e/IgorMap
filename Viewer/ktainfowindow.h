#ifndef KTAINFOWINDOW_H
#define KTAINFOWINDOW_H

#include "basewidget.h"
#include "global.h"
#include <QTableView>

struct KTAMark {
    bool selected = false;

    float sceneX;
    float sceneY;
    float absX;
    float absY;
    float dist;
    float az;
    float pointAngle;
    float amp;
    float rSpeed;
    int type;
    float limit;
};

typedef QSharedPointer<KTAMark> SharedPointerKTAMark;
typedef QWeakPointer<KTAMark> WeakPointerKTAMark;
typedef QVector<SharedPointerKTAMark > KTAMarkVector;
typedef QMap<int, KTAMarkVector> KTAMarkMap;
typedef QVector<QWeakPointer<KTAMark> > KTAMarksForTable;

//using MapVertex = QMap< Vertex, RLSOPlotMessage>;
using MapVertex = QMap< float, VOIMarkMessage >;
using PairOfTimeAndMapVertex = QPair< quint32, MapVertex >;
using ListOfPair = QList<PairOfTimeAndMapVertex>;

class KTAInfoWidget : public BaseWidget
{
    Q_OBJECT

public:
    KTAInfoWidget(QWidget *parent = nullptr);

    void resizeWidget(int w, int h);
    void moveWidget(int x, int y);

public slots:
    void fillTable(KTAMarksForTable *list);
    void selectKTARequestAnswerHandler(WeakPointerKTAMark selectedIndex);

    void addPOIMarkSlot(POIKtaMessage msg);
    void addVOIMarkSlot(VOIMarkMessage msg);
    void sampledKTAMark(const QPointF leftBottom, const QPointF rightTop);

private slots:
     void eraseOldKTA();

private:
    QLabel *distOutput;
    QLabel *azimuthOutput;
    QLabel *pointAngleOutput;
    QLabel *ampOutput;
    QLabel *rSpeedOutput;

    QLineEdit *radSpallLine;
    BasePushButton *showButton;
    QTableView *tableView;

    ListOfPair listOfMapVertex;
    quint32 timeAlive_msec;
    QTimer *timeErase;
    float *dynamicArrayOfKTAVertex;
    quint32 lastSizeOfDynamicArray;

    const QString strNoValue = "-";    

private:
    void initTable();
    void Init();
    void resetData();
    void displayKTAInfo(SharedPointerKTAMark refMark);
    void geometryCompensation();

signals:
    void selectKTARequest(int indexOnKTAVector);
    void sampledKTAMarkVertexArray(const float *array,const quint32 size);
    void drawSampledKTAMarkSignal(QSharedPointer< QVector<float> > sharedArray);

private slots:
    void showTable();
    void rowSelected();

};



#endif // KTAINFOWINDOW_H
