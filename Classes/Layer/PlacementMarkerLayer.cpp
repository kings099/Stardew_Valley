/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: 放置标记层类PlacementMarkerLayer的实现
 * Author:        尹诚成
 * Update Date:   2024/12/07
 * License:       MIT License
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"

 // 命名空间
using cocos2d::Sprite;
using cocos2d::Vec2;

// 初始化放置标记层
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// 显示放置标记
void PlacementMarkerLayer::showPlacementMarker(const std::vector<ObjectListNode> objectList)
{

}

// 创建放置标记
void PlacementMarkerLayer::createPlacementMarker(const ObjectListLocation& objectListLocation)
{
    Sprite* placementMarker = Sprite::create("../Resources/Mouse/AvailablePlacementMarker.png");
    Vec2 coordinate = LocationMap::getInstance().getLocationMap().at(objectListLocation);
    placementMarker->setPosition(coordinate);
    this->addChild(placementMarker);
}