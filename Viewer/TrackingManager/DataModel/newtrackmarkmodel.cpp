#include "newtrackmarkmodel.h"

NewTrackMarkModel::NewTrackMarkModel()
{
    magicNumberWithScale = magicNumber / CfgManager::Instance()->getUiController()->getMapScale();
}

NewTrackMarkModel::~NewTrackMarkModel()
{
    mapOfClosedZone.clear();
    mapOfForm.clear();
    mapOfInfo.clear();
    for (auto itemMap = mapOfTracks.begin(); itemMap != mapOfTracks.end(); itemMap++ ) {
        for (auto aimMessage = itemMap->second.begin(); aimMessage != itemMap->second.end(); aimMessage++ ) {
            delete *aimMessage;
        }
    }
    mapOfTracks.clear();
}

void NewTrackMarkModel::addTrackMark(RLSOaimMessage *msg)
{
    TrackMark *mark = new TrackMark;

    //float scale = CfgManager::Instance()->getUiController()->getMapScale();

    BRLSPosition airplanPos = CfgManager::Instance()->getTrackingController()->getDataModel()->getBRLSTrackModel()->getBRLSPosition();
    float dist = sqrt(pow(msg->D / CfgManager::GLOBAL_TO_LOCAL_RATIO, 2) - pow(abs(msg->sAimCoords.h - airplanPos.h)  / CfgManager::GLOBAL_TO_LOCAL_RATIO, 2));
    currentInfo.dist = dist;
    currentInfo.height = msg->sAimCoords.h;
    currentInfo.az = msg->Az;
    currentInfo.trackId = msg->trackID;

    currentInfo.scenePos.x = mark->xPos = airplanPos.x + dist * sinf((msg->Az + airplanPos.course) * PI / 180);//mark->xPos = dist * cosf(msg->Az * PI / 180);
    currentInfo.scenePos.y = mark->yPos = airplanPos.y + dist * cosf((msg->Az + airplanPos.course) * PI / 180);//mark->yPos = dist * sinf(msg->Az * PI / 180);
    currentInfo.trackHeading = mark->heading = msg->sAimCoords.tack;
    currentInfo.speed = mark->speed = msg->sAimCoords.vp;
    auto itemTrack = mapOfTracks.find(currentInfo.trackId);
    if (itemTrack != mapOfTracks.end()) {
        itemTrack->second.push_front(mark);
    }
    else {
        mapOfTracks.insert({currentInfo.trackId, TrackList()});
        mapOfTracks.find(currentInfo.trackId)->second.push_front(mark);
    }

    if (mapOfInfo.find(currentInfo.trackId) != mapOfInfo.end()) {
        deleteClosedZoneAndFormByID(msg->trackID);
    }

    findInfoPositionOnZone();
}

void NewTrackMarkModel::deleteTrackMark(int id)
{
    deleteClosedZoneAndFormByID(id);
    auto item = mapOfInfo.find(id);
    if (item != mapOfInfo.end())
        mapOfInfo.erase(item);
}

void NewTrackMarkModel::resetModel()
{
    magicNumberWithScale = magicNumber / CfgManager::Instance()->getUiController()->getMapScale();
    mapOfClosedZone.clear();
    mapOfForm.clear();

    MapOfInfo tempMap(mapOfInfo);
    mapOfInfo.clear();
    for (auto item : tempMap) {
        currentInfo = item.second;
        findInfoPositionOnZone();
    }
}

void NewTrackMarkModel::findInfoPositionOnZone()
{
    float currentX = currentInfo.scenePos.x - magicNumberWithScale, currentY = currentInfo.scenePos.y - magicNumberWithScale;

    int index = 2;
    int face = 0;
    int resultDirection = 0;
    while (1) {
        bool flagRecsue = false;
        if (++face == 5) {
            face = 1;
            index++;
            currentX -= magicNumberWithScale, currentY -= magicNumberWithScale;
        }
        for (int _index = 0; _index != index; _index++) {
            if (face != 1 && _index == 0) {
                _index++;
                if (face == 2) {
                    currentY += 2 * magicNumberWithScale;
                }
                else if (face == 3) {
                    currentX -= 2 * magicNumberWithScale;
                }
                else if (face == 4) {
                    currentY -= 2 * magicNumberWithScale;
                }
            }
            if (face == 4 && (_index + 1) == index) {
                currentY -= 2 * magicNumberWithScale;
                continue;
            }
            float _x1 = currentX - magicNumberWithScale, _x2 = currentX + magicNumberWithScale,
                  _y1 = currentY - magicNumberWithScale, _y2 = currentY + magicNumberWithScale;
            int zoneDirection = 15;
            for (auto itemB = mapOfClosedZone.lower_bound(_x1),
                 itemE = mapOfClosedZone.upper_bound(_x2);
                 itemB != itemE; itemB++) {
                auto infoItem = mapOfInfo.find(itemB->second.id)->second;
                for (int i = 0; i < 4; i++) {
                    int koeffX = (i == 2 || i == 4) ? 1 : -1,
                        koeffY = (i == 3 || i == 4) ? 1 : -1;
                    float width = min((float)max(infoItem.closedZone.point1.x, infoItem.closedZone.point2.x),
                                      max(currentX, currentX + magicNumberWithScale * koeffX)) -
                                  max((float)min(infoItem.closedZone.point1.x, infoItem.closedZone.point2.x),
                                      min(currentX, currentX + magicNumberWithScale * koeffX));
                    float height = min((float)max(infoItem.closedZone.point1.y, infoItem.closedZone.point2.y),
                                       max(currentY, currentY + magicNumberWithScale * koeffY)) -
                                   max((float)min(infoItem.closedZone.point1.y, infoItem.closedZone.point2.y),
                                       min(currentY, currentY + magicNumberWithScale * koeffY));
                    if (width > 10 || height > 10) {
                        zoneDirection &= 0b1111 ^ 1 << i;
                    }
                }
            }
            if (zoneDirection) {
                int formDirection = 15;
                for (auto itemB = mapOfForm.lower_bound(_x1),
                     itemE = mapOfForm.upper_bound(_x2);
                     itemB != itemE; itemB++) {
                    /*if (_x1 <= itemB->first && itemB->first < currentX) {
                        if (_y1 <= itemB->second.y && itemB->second.y < currentY) {
                            formDirection &= 0b1111 ^ 1 << 0; // 1
                        }
                        else if (itemB->second.y <= currentY && itemB->second.y < _y2) {
                            formDirection &= 0b1111 ^ 1 << 2; // 3
                        }
                    }
                    else if (currentX <= itemB->first && itemB->first < _x2) {
                        if (_y1 <= itemB->second.y && itemB->second.y < currentY) {
                            formDirection &= 0b1111 ^ 1 << 1; // 2
                        }
                        else if (itemB->second.y <= currentY && itemB->second.y < _y2) {
                            formDirection &= 0b1111 ^ 1 << 3; // 4
                        }
                    }*/
                    auto infoItem = mapOfInfo.find(itemB->second.id)->second;
                    for (int i = 0; i < 4; i++) {
                        int koeffX = (i == 2 || i == 4) ? 1 : -1,
                            koeffY = (i == 3 || i == 4) ? 1 : -1;
                        float width = min((float)max(infoItem.form.point1.x, infoItem.form.point2.x),
                                          max(currentX, currentX + magicNumberWithScale * koeffX)) -
                                      max((float)min(infoItem.form.point1.x, infoItem.form.point2.x),
                                          min(currentX, currentX + magicNumberWithScale * koeffX));
                        float height = min((float)max(infoItem.form.point1.y, infoItem.form.point2.y),
                                           max(currentY, currentY + magicNumberWithScale * koeffY)) -
                                       max((float)min(infoItem.form.point1.y, infoItem.form.point2.y),
                                           min(currentY, currentY + magicNumberWithScale * koeffY));
                        if (width > 2 || height > 2) {
                            formDirection &= 0b1111 ^ 1 << i;
                        }
                    }
                }
                resultDirection = zoneDirection & formDirection;
                if (resultDirection) {
                    if (face == 1) {
                        if (_index == 0) {
                            resultDirection &= 0b0111;
                        }
                        else if ((_index + 1) == index) {
                            resultDirection &= 0b1011;
                        }
                        else {
                            resultDirection &= 0b0011;
                        }
                    }
                    else if (face == 2) {
                        if ((_index + 1) == index) {
                            resultDirection &= 0b1110;
                        }
                        else {
                            resultDirection &= 0b0110;
                        }
                    }
                    else if (face == 3) {
                        if ((_index + 1) == index) {
                            resultDirection &= 0b1101;
                        }
                        else {
                            resultDirection &= 0b1100;
                        }
                    }
                    else if (face == 4) {
                        resultDirection &= 0b0101;
                    }
                    if (resultDirection) {
                        flagRecsue = true;
                        break;
                    }
                }
            }

            if (face == 1) {
                currentX += 2 * magicNumberWithScale;
            }
            else if (face == 2) {
                currentY += 2 * magicNumberWithScale;
            }
            else if (face == 3) {
                currentX -= 2 * magicNumberWithScale;
            }
            else if (face == 4) {
                currentY -= 2 * magicNumberWithScale;
            }
        }
        if (flagRecsue)
            break;
    }

    currentInfo.closedZone.point1.x = currentInfo.scenePos.x - magicNumberWithScale;
    currentInfo.closedZone.point2.x = currentInfo.scenePos.x + magicNumberWithScale;
    currentInfo.closedZone.point1.y = currentInfo.scenePos.y - magicNumberWithScale;
    currentInfo.closedZone.point2.y = currentInfo.scenePos.y + magicNumberWithScale;
    mapOfClosedZone.insert({currentInfo.closedZone.point1.x, {currentInfo.closedZone.point1.y, currentInfo.trackId}});
    mapOfClosedZone.insert({currentInfo.closedZone.point2.x, {currentInfo.closedZone.point2.y, currentInfo.trackId}});
    currentInfo.direction = resultDirection;
    if (resultDirection && 0b0001) {
        currentInfo.form.point1.x = currentX - magicNumberWithScale;
        currentInfo.form.point2.x = currentX;
        currentInfo.form.point1.y = currentY;
        currentInfo.form.point2.y = currentY - magicNumberWithScale;
    }
    else if (resultDirection && 0b0010) {
        currentInfo.form.point1.x = currentX;
        currentInfo.form.point2.x = currentX + magicNumberWithScale;
        currentInfo.form.point1.y = currentY;
        currentInfo.form.point2.y = currentY - magicNumberWithScale;
    }
    else if (resultDirection && 0b0100) {
        currentInfo.form.point1.x = currentX + magicNumberWithScale;
        currentInfo.form.point2.x = currentX;
        currentInfo.form.point1.y = currentY - magicNumberWithScale;
        currentInfo.form.point2.y = currentY;
    }
    else if (resultDirection && 0b1000) {
        currentInfo.form.point1.x = currentX;
        currentInfo.form.point2.x = currentX + magicNumberWithScale;
        currentInfo.form.point1.y = currentY + magicNumberWithScale;
        currentInfo.form.point2.y = currentY;
    }
    mapOfForm.insert({currentInfo.form.point1.x, {currentInfo.form.point1.y, currentInfo.trackId}});
    mapOfForm.insert({currentInfo.form.point2.x, {currentInfo.form.point2.y, currentInfo.trackId}});

    auto item = mapOfInfo.find(currentInfo.trackId);
    if (item != mapOfInfo.end()) {
        item->second = currentInfo;
    }
    else {
        mapOfInfo.insert({currentInfo.trackId, currentInfo});
    }
}

void NewTrackMarkModel::deleteClosedZoneAndFormByID(int id)
{
    auto item = mapOfInfo.find(id);
    for (auto pos = mapOfClosedZone.equal_range(item->second.closedZone.point1.x);
         pos.first != pos.second; pos.first++) {
        if (id == pos.first->second.id) {
            mapOfClosedZone.erase(pos.first);
            break;
        }
    }
    for (auto pos = mapOfClosedZone.equal_range(item->second.closedZone.point2.x);
         pos.first != pos.second; pos.first++) {
        if (id == pos.first->second.id) {
            mapOfClosedZone.erase(pos.first);
            break;
        }
    }
    auto itemForm = mapOfForm.find(item->second.form.point1.x);
    if (itemForm != mapOfForm.end()) {
        mapOfForm.erase(itemForm);
    }
    itemForm = mapOfForm.find(item->second.form.point2.x);
    if (itemForm != mapOfForm.end()) {
        mapOfForm.erase(itemForm);
    }
}
