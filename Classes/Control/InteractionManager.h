/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 角色地图交互控制类InteractionManager的定义
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __INTERACTION_MANAGER_H__
#define __INTERACTION_MANAGER_H__

#include "cocos2d.h"
#include "Maps/GameMap.h"
#include "../proj.win32/Constant.h"
#include <vector>


class InteractionManager : public cocos2d::Node {
public:
    InteractionManager();
    ~InteractionManager();

    // 创建交互管理器实例
    static InteractionManager* create(GameMap* gameMap);

    // 初始化交互管理器
    bool init(GameMap* gameMap);

    // 更新角色周围的瓦片信息
    void updateSurroundingTiles(cocos2d::Vec2& world_pos);

    // 判断指定瓦片位置是否为不可通行区域
    bool isCollidableAtPos(const cocos2d::Vec2& tilePos);

    // 获取角色周围的可通行状态
    std::vector<bool> getSurroundingCollidable(const cocos2d::Vec2& currentPos);

    // 判断指定世界坐标是否为可农耕区域
    bool isFarmlandAtPos(const cocos2d::Vec2& worldPos);

    // 检查角色是否站在传送点上
    bool checkTeleport(const cocos2d::Vec2& worldPos, std::string& targetMapFile);

    // 改变地图
    void setMap(GameMap* newMap);

    // 获取角色周围的瓦片信息
    const std::vector<TileInfo>& getSurroundingTiles() const;

private:
    GameMap* _gameMap;             // 当前地图对象的引用
    std::vector<TileInfo> _surroundingTiles; // 储存角色周围 9 格瓦片的信息
};

#endif // INTERACTION_MANAGER_H
