#include "datahandler.h"
#include <QDebug>
#include <QDataStream>


SectorData::SectorData()
    : maxSecorsNumber(10),
      sectorsVector(new SectorsVector(maxSecorsNumber, qMakePair(ItemState::Empty, SectorParameters()))),
      sharedSectorsData(sectorsVector)
{

}

void SectorData::addSector(const quint8 index, SharedSectorParameters sharedSector)
{
    /*
    //for (int index = 0; index < maxSecorsNumber; index++) {
    //    if (sectorsVector.at(index).first == ItemState::Empty) {
            sectorsVector->replace(index, qMakePair(ItemState::Added, *sharedSector));
            emit addSectorsToScene(index, sharedSector);

            RMOTargetPositionMessage msg;
            msg.id = index;
            msg.azimuth[0] = sharedSector.data()->azMin;
            msg.azimuth[1] = sharedSector.data()->azMax;
            msg.ugm[0] = sharedSector.data()->ugmMin;
            msg.ugm[1] = sharedSector.data()->ugmMax;
            msg.dist[0] = sharedSector.data()->distMin;
            msg.dist[1] = sharedSector.data()->distMax;

            QByteArray arr;

            QDataStream out(&arr, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_11);
            out.setByteOrder(QDataStream::LittleEndian);
            out.setFloatingPointPrecision(QDataStream::SinglePrecision);

            out << qint16(0);
            out << quint8(RMO_VOI_TARGET_POSITION_MESSAGE);
            out.writeRawData(reinterpret_cast<const char *>(&msg), sizeof(RMOTargetPositionMessage));
            out.device()->seek(0);
            out << quint16(arr.size() - sizeof(quint16));

            emit addSectorsToVOI(arr);
            qDebug() << "RMO_VOI_TARGET_POSITION_MESSAGE";

    //        break;
    //    }
    //}*/
}

void SectorData::verificationState(const quint8 index, const ItemState &state)
{
    /*switch (state) {
    case ItemState::Current: {
        if (sectorsVector->at(index).first == ItemState::Added){
            (*sectorsVector)[index].first = state;
            //*sectorsVector[index].first() = state;
        }
        else
            qDebug() << "Unexpected state!";
        break;
    }
    case ItemState::Excluded: {
        if (sectorsVector->at(index).first != state)
            qDebug() << "Unexpected state!";
        break;
    }
    case ItemState::Empty: {
        if (sectorsVector->at(index).first == ItemState::Deleted){
            (*sectorsVector)[index].first = state;
        }
        else
            qDebug() << "Unexpected state!";
        break;
    }
    case ItemState::Added:
    case ItemState::Deleted:
        qDebug() << "Unexpected state!";
        break;
    }*/
}
