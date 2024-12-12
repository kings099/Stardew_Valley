/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: 放置标记层类PlacementMarkerLayer的实现
 * Author:        尹诚成
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"
#include "Character/Character.h"

USING_NS_CC;

// 初始化放置标记层
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    _character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
    return true;
}

// 显示放置标记
void PlacementMarkerLayer::showPlacementMarker()
{
    const auto objectListStatus = _character->getObjectListStatus();
    if (objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
<<<<<<< Updated upstream
                if (_character->findObjectAtPosition(i * OBJECT_LIST_COLS + j).count==0) {
=======
                if (_character->findObjectAtPosition(i * OBJECT_LIST_COLS + j).count == 0) {
>>>>>>> Stashed changes
                    createPlacementMarker(i * OBJECT_LIST_COLS + j);
                }
            }
        }
    }
}

// 创建放置标记
void PlacementMarkerLayer::createPlacementMarker(const int& index)
{
    Sprite* placementMarker = Sprite::create("../Resources/UI/PlacementMarker.png");
    const Vec2 coordinate = LocationMap::getInstance().getLocationMap().at(index);
    placementMarker->setPosition(coordinate);
    this->addChild(placementMarker);
}