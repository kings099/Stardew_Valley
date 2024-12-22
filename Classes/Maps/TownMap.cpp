/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TownMap.cpp
 * File Function: 小镇地图TownMap类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/
#include "TownMap.h"
USING_NS_CC;

TownMap::TownMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}

TownMap::~TownMap() {}

TownMap* TownMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    TownMap* ret = new TownMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool TownMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用父类的初始化函数
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    _map_position = mapPosition;
    _mapName = mapFile;
    this->setScale(TOWN_MAP_SCALE);

    // 添加小镇地图初始化时需要创建的精灵
    return true;
}

Node* TownMap::getNodeAtPosition(const Vec2& tilePos) {

    // 添加小镇地图特有节点逻辑 （暂无）
    return nullptr; // 默认返回 nullpt
}