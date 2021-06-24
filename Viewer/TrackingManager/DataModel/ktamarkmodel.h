#ifndef KTAMARKMODEL_H
#define KTAMARKMODEL_H

#include <QObject>
#include <TcpHandler/datamessage.h>
#include <vector>
#include <list>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMap>
#include <QVector>

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
typedef QVector<SharedPointerKTAMark > KTAMarkVector;       // stores kta marks mapped to a sector
typedef QMap<int, KTAMarkVector> KTAMarkMap; // stores lists of marks mapped to a sector
typedef QVector<QWeakPointer<KTAMark> > KTAMarksForTable;       // [0] for sector [0,SECTOR_SIZE] degrees


class KTAMarkModel : public QObject
{
    Q_OBJECT

public:
    static const int SECTOR_SIZE = 5; // size of sector in deg, storing objects with approp. azimuth
    static const int NUM_RADIAL_SECTORS = 360; // / SECTOR_SIZE; // number of sectors in 360 deg circle

    KTAMarkModel();
    ~KTAMarkModel();
    void addKTAMark(POIKtaMessage *msg);
    void addVOIMark(RLSOPlotMessage *msg);
    KTAMarkMap* getKTAMarkMap() { return &ktaMarkMap; }

    void eraseAllKTAMarksInCurrentAz();
    void findKTAMarkAt(float az, float dist, float scenePosX, float scenePosY, float threshold);
    void cleanModel();
    //void setKTAAliveTime(int msec);
    int getKTACount();

private:
    KTAMarkMap ktaMarkMap;
    //int timeAliveKTA = 125;
    KTAMarksForTable markForTable;
    QWeakPointer<KTAMark> selectedMark;

    int getListIndex(float radarAz);

signals:
    void returnDataToTableKTA(KTAMarksForTable *list);
    void selectKTARequestAnswer(WeakPointerKTAMark selectedIndex);

public slots:
    void selectKTARequestHandler(int indexOnKTAVector);
    void eraseAllKTA();

};

#endif // KTAMARKMODEL_H
