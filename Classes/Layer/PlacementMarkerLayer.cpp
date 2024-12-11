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
#include "Character/Character.h"

USING_NS_CC;

// ��ʼ�����ñ�ǲ�
bool PlacementMarkerLayer::init()
{
    if (!Layer::init()&& (_character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png"))!= nullptr) {
        return false;
    }
    return true;
}

// ��ʾ���ñ��
void PlacementMarkerLayer::showPlacementMarker(const std::vector<ObjectListNode> objectList)
{
    const auto objectListStatus = _character->getObjectListStatus();
    if (objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                if (_character->findObjectAtPosition(i * OBJECT_LIST_COLS + j).count==0) {
                    createPlacementMarker(i * OBJECT_LIST_COLS + j);
                }
            }
        }
    }
}

// �������ñ��
void PlacementMarkerLayer::createPlacementMarker(const int& index)
{
    Sprite* placementMarker = Sprite::create("../Resources/Mouse/AvailablePlacementMarker.png");
    Vec2 coordinate = LocationMap::getInstance().getLocationMap().at(index);
    placementMarker->setPosition(coordinate);
    this->addChild(placementMarker);
}