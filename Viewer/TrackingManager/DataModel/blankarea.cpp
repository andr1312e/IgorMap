/*#include "blankarea.h"
#include <qmath.h>
#include <ConfigurationManager/cfgmanager.h>

BlankArea::BlankArea()
{
    blankAreaObjectMap = new BlankAreaObjectMap;
    firstEnteryFlag = false;
    objectId = 0;
}

BlankArea::~BlankArea()
{

    for (BlankAreaObjectMap::iterator iter = blankAreaObjectMap->begin(); iter != blankAreaObjectMap->end(); iter++)
        delete iter->second;
    blankAreaObjectMap->erase(blankAreaObjectMap->begin(),blankAreaObjectMap->end());
    delete blankAreaObjectMap;
}

void BlankArea::createObject()
{
    //BlankAreaObject *newObject = new BlankAreaObject;
    //blankAreaObjectList->push_back(newObject);
    //createObjectFlag = true;
}

void BlankArea::endObject()
{
    if (firstEnteryFlag)
        firstEnteryFlag = false;
}

void BlankArea::addObject(BlankAreaObject *obj)
{
    blankAreaObjectMap->insert(make_pair(objectId, obj));

    sendToCreate();
}

void BlankArea::changeObject(uint id, BlankAreaObject *obj)
{
    BlankAreaObjectMap::iterator iter = blankAreaObjectMap->find(id);
    iter->second->x1 = obj->x1;
    iter->second->y1 = obj->y1;
    iter->second->x2 = obj->x2;
    iter->second->y2 = obj->y2;

    sendToCreate();
}

void BlankArea::deleteObject(float nx, float ny)
{
    //uint id = 0;
    //bool initializationFlag = false;
    for (BlankAreaObjectMap::iterator iter = blankAreaObjectMap->begin();
         iter != blankAreaObjectMap->end();
         iter++)
    {
        bool flag1 = false, flag2 = false;
        if (iter->second->x1 > iter->second->x2 )
        {
            if (iter->second->x1 >= nx && iter->second->x2 <= nx )
                flag1 = true;
        }
        else
        {
            if (iter->second->x1 <= nx && iter->second->x2 >= nx )
                flag1 = true;
        }
        if (iter->second->y1 > iter->second->y2 )
        {
            if (iter->second->y1 >= ny && iter->second->y2 <= ny )
                flag2 = true;
        }
        else
        {
            if (iter->second->y1 <= ny && iter->second->y2 >= ny )
                flag2 = true;
        }
        if (flag1 && flag2)
        {

            CfgManager::Instance()->getUiController()->getBlankAreaWidget()->setRow(iter->first);
            break;
        }
    }
    //if (initializationFlag)
     //   CfgManager::Instance()->getUiController()->getBlankAreaWidget()->removeObject(id);
}

void BlankArea::deleteObject(uint id)
{
    delete blankAreaObjectMap->find(id)->second;
    blankAreaObjectMap->erase(blankAreaObjectMap->find(id));
}

void BlankArea::addPoint(float nx, float ny)
{
    if (!firstEnteryFlag)
    {
        firstEnteryFlag = true;
        tempAz = nx;
        tempDis = ny;
    }
    else
    {
        firstEnteryFlag = false;
        BlankAreaObject *obj = new BlankAreaObject;
        obj->x1 = tempAz;
        obj->y1 = tempDis;
        obj->x2 = nx;
        obj->y2 = ny;
        blankAreaObjectMap->insert(make_pair(objectId, obj));
        CfgManager::Instance()->getUiController()->getBlankAreaWidget()->displayOdject();

        sendToCreate();
    }
}

void BlankArea::sendToCreate()
{
    BlankAreaCreateMessage msg;
    BlankAreaObjectMap::iterator iter = blankAreaObjectMap->find(objectId);

    float az,dis;
    dis = sqrt( iter->second->x1 * iter->second->x1 +
                iter->second->y1 * iter->second->y1 );
    az = atan2(iter->second->x1, iter->second->y1) * 180 / PI;
    msg.az1 = az;
    msg.dis1 = dis;
    dis = sqrt( iter->second->x2 * iter->second->x2 +
                iter->second->y2 * iter->second->y2 );
    az = atan2(iter->second->x2, iter->second->y2) * 180 / PI;
    msg.az2 = az;
    msg.dis2 = dis;
    msg.id = objectId++;

    QByteArray datagram;
    QUdpSocket socket;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << qint8(0);
    out << quint8(BLANK_AREA_CREATE_MESSAGE);
    out.writeRawData((char*)&msg, sizeof(BlankAreaCreateMessage));
    out << qint8(datagram.size() - sizeof(quint8));
    socket.writeDatagram(datagram, QHostAddress::LocalHost, 1000);
    socket.flush();
}

void BlankArea::sendToRemove(uint id)
{
    BlankAreaRemoveMessage msg;
    msg.id = id;

    QByteArray datagram;
    QUdpSocket socket;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << qint8(0);
    out << quint8(BLANK_AREA_REMOVE_MESSAGE);
    out.writeRawData((char*)&msg, sizeof(BlankAreaRemoveMessage));
    out << qint8(datagram.size() - sizeof(quint8));
    socket.writeDatagram(datagram, QHostAddress::LocalHost, 1000);
    socket.flush();
}
*/
