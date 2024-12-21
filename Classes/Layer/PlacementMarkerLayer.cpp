/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: 放置标记层类PlacementMarkerLayer的实现
 * Author:        尹诚成
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"


USING_NS_CC;

// 初始化放置标记层
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    _character = Character::getInstance();
    return true;
}

// 显示放置标记
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

// 创建放置标记
void PlacementMarkerLayer::createPlacementMarker(const Location& location) {
    Sprite* boxPlacementMarker = Sprite::create("../Resources/UI/PlacementMarker.png");
    const Vec2 boxCoordinate = LocationMap::getInstance().getLocationMap().at(location);
    boxPlacementMarker->setPosition(boxCoordinate);
    this->addChild(boxPlacementMarker);
}