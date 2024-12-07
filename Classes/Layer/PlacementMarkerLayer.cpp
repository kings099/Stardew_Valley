/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.cpp
 * File Function: ���ñ�ǲ���PlacementMarkerLayer��ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/07
 * License:       MIT License
 ****************************************************************/

#include "PlacementMarkerLayer.h"
#include "LocationMap/LocationMap.h"

 // �����ռ�
using cocos2d::Sprite;
using cocos2d::Vec2;

// ��ʼ�����ñ�ǲ�
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// ��ʾ���ñ��
void PlacementMarkerLayer::showPlacementMarker(const std::vector<ObjectListNode> objectList)
{

}

// �������ñ��
void PlacementMarkerLayer::createPlacementMarker(const ObjectListLocation& objectListLocation)
{
    Sprite* placementMarker = Sprite::create("../Resources/Mouse/AvailablePlacementMarker.png");
    Vec2 coordinate = LocationMap::getInstance().getLocationMap().at(objectListLocation);
    placementMarker->setPosition(coordinate);
    this->addChild(placementMarker);
}