#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include "global.h"


class SectorData : public QObject {
    Q_OBJECT

public:
    SectorData();
    SharedSectorsVector getSharedSectorsVector() const { return sharedSectorsData; }

signals:
    void addSectorsToScene(const quint8 &index, SharedSectorParameters sharedSector);
    void addSectorsToVOI(QByteArray msg);

public slots:
    void addSector(const quint8 index, SharedSectorParameters sharedSector);
    void verificationState(const quint8 index, const ItemState &state);

private:
    const quint8 maxSecorsNumber = 10;
    SectorsVector *sectorsVector;
    SharedSectorsVector sharedSectorsData;
};

#endif // DATAHANDLER_H
