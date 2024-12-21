/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: ���ñ�ǲ���PlacementMarkerLayer��ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"


USING_NS_CC;

// ��ʼ�����ñ�ǲ�
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    _character = Character::getInstance();
    return true;
}

// ��ʾ���ñ��
void PlacementMarkerLayer::showPlacementMarker()
{
    const auto objectListStatus = _character->getObjectListStatus();
    const auto boxListStatus = _character->getBoxStatus();
    if (objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                if (_character->findObjectAtPosition(i * OBJECT_LIST_COLS + j).count == 0) { 
                    createPlacementMarker({OpenedObjectList, i * OBJECT_LIST_COLS + j});
                }
            }
        }
    }

    if (boxListStatus) {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if (Box::getInstance().getBoxCount() != 0) {
                if (Box::getInstance().getBoxList()._boxObjectList[i].count == 0) {
                    createPlacementMarker({ OpenedBoxList, i });
                }
            }
        }
    }
}

// �������ñ��
void PlacementMarkerLayer::createPlacementMarker(const Location& location) {
    Sprite* boxPlacementMarker = Sprite::create("../Resources/UI/PlacementMarker.png");
    const Vec2 boxCoordinate = LocationMap::getInstance().getLocationMap().at(location);
    boxPlacementMarker->setPosition(boxCoordinate);
    this->addChild(boxPlacementMarker);
}