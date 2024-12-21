/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MineMap.cpp
 * File Function: ��ʼ���󶴵�ͼ
 * Author:        ������
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#include "MineMap.h"

USING_NS_CC;

MineMap::MineMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}


MineMap::~MineMap()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}

MineMap* MineMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    MineMap* ret = new MineMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool MineMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // ���ø���ĳ�ʼ������
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    _mapName = mapFile;
    _map_position = mapPosition;
    this->setScale(INDOOR_MAP_SCALE);

    return true;
}

