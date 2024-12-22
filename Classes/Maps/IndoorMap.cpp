/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.cpp
 * File Function: 初始化室内地图
 * Author:        胡宝怡
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#include "IndoorMap.h"

USING_NS_CC;

IndoorMap::IndoorMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}


IndoorMap::~IndoorMap()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}

IndoorMap* IndoorMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    IndoorMap* ret = new IndoorMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool IndoorMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用父类的初始化方法
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    _mapName = mapFile;
    _map_position = mapPosition;
    this->setScale(INDOOR_MAP_SCALE);

    return true;
}

// 获取室内地图特定节点
Node* IndoorMap::getNodeAtPosition(const Vec2& tilePos) {
    // 根据室内地图节点添加内容（目前暂无）

    return nullptr;
}



