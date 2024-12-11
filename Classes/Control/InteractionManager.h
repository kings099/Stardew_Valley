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
#include "Character/Character.h"
#include "Maps/GameMap.h"
#include <vector>
#include <tuple>

 // 交互管理器类，用于管理角色与地图之间的交互逻辑
class InteractionManager : public cocos2d::Node {
public:
    // 构造函数与析构函数
    InteractionManager();
    ~InteractionManager();

    // 创建交互管理器实例
    static InteractionManager* create(Character* character, GameMap* gameMap);

    // 初始化交互管理器
    bool init(Character* character, GameMap* gameMap);

    // 更新角色周围的瓦片信息
    void updateSurroundingTiles(cocos2d::Vec2& world_pos);

    // 判断指定瓦片位置是否为不可通行区域
    bool isCollidableAtPos(const cocos2d::Vec2& tilePos);

    // 获取角色周围的可通行状态
    // 返回一个包含9个布尔值的向量，对应角色当前位置及周围8个瓦片是否可通行
    std::vector<bool> getSurroundingCollidable(const cocos2d::Vec2& currentPos);

    // 判断指定世界坐标是否为可农耕区域
    bool isFarmlandAtPos(const cocos2d::Vec2& worldPos);

    // 获取角色周围瓦片的详细信息
    // 返回包含层名称、GID、属性的元组列表
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> getSurroundingTilesInfo(const cocos2d::Vec2& worldPos);

    // 检查角色是否站在传送点上
    // 如果是传送点，返回目标地图文件路径
    bool checkTeleport(const cocos2d::Vec2& worldPos, std::string& targetMapFile);

    // 改变地图
    void setMap(GameMap* newMap);

private:
    Character* _character;         // 当前角色对象的引用
    GameMap* _gameMap;             // 当前地图对象的引用
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> _surroundingInfo; // 缓存的周围瓦片信息
};
#endif // __INTERACTION_MANAGER_H__
