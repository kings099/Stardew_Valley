/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapSwitchManager.h
 * File Function: 地图切换控制类MapSwitchManager的定义
 * Author:        金恒宇
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MAP_SWITCH_MANAGER_H_
#define MAP_SWITCH_MANAGER_H_

#include "cocos2d.h"
#include "Maps/GameMap.h"
#include "Maps/FarmMap.h"
#include "Maps/IndoorMap.h"
#include "Character/Character.h"

USING_NS_CC;

class MapSwitchManager : public Node
{
public:
    // 创建 MapSwitchManager 实例
    static MapSwitchManager* create(Character* character, GameMap* currentMap);

    // 切换地图
    bool switchMap(const std::string& newMapFile, int teleportID);

private:
    // 构造函数和析构函数
    MapSwitchManager();
    ~MapSwitchManager();

    bool init(Character* character, GameMap* currentMap);

    // 根据传送点 ID 获取目标位置
    //Vec2 getTargetPositionByID(int teleportID, GameMap* newMap);

    // 动态创建地图实例（根据类型）
    GameMap* createMapByType(const std::string& mapFile);

private:
    Character* _character;  // 当前的角色对象
    GameMap* _currentMap;   // 当前地图对象
};

#endif // MAP_SWITCH_MANAGER_H_
