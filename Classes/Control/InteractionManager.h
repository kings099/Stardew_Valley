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
#include "Maps/FarmMap.h"
#include "../proj.win32/Constant.h"
#include "Crops/Crops.h"
#include <vector>


class InteractionManager : public cocos2d::Node {
public:
    // 构造函数
    InteractionManager();

    // 析构函数
    ~InteractionManager();

    // 创建交互管理器实例
    static InteractionManager* create(GameMap* gameMap);

    // 初始化交互管理器
    bool init(GameMap* gameMap);

    // 更新角色周围的瓦片信息
    void updateSurroundingTiles(cocos2d::Vec2& world_pos);

    // 检查角色是否站在传送点上
    bool checkTeleport(const cocos2d::Vec2& worldPos, std::string& targetMapFile);

    // 改变地图
    void setMap(GameMap* newMap);

    // 获取角色周围的瓦片信息
    const std::vector<TileInfo>& getSurroundingTiles() const;

    // 执行对应地块动画
    void ActionAnimation(GameCharacterAction action, const Vec2& TilePos);

    // 获取角色前方第n格地块信息
    const TileInfo GetLineTileInfo(Direction dir, int distance, const Vec2& WroldPos);

    // 更新角色选中物品名称
    void updateCurrentObject(const ObjectListNode& object){
        _currentObject = object;
    }
private:
    // 当前地图对象
    GameMap* _gameMap;                          

    // 储存角色周围 9 格瓦片的信息
    std::vector<TileInfo> _surroundingTiles;    

    //储存当前选中物品
    ObjectListNode _currentObject;              

    // 判断指定瓦片位置是否为不可通行区域
    bool isCollidableAtPos(const cocos2d::Vec2& tilePos);

    // 获取某个瓦片的地块信息
    const TileInfo GetTileInfoAt(const Vec2& WroldPos);

    // 某个位置播放砍树动画（多态实现要求地图是Farmmap类）
    void getTreeAndChopAt(const Vec2& tilePos);

    // 放置物品的方法
    bool placeObjectAtTile(const cocos2d::Vec2& tilePos);

    // 获取矿石信息
    void InteractionManager::GetMineInfo(int MineGID, TileInfo& tile);
};

#endif // INTERACTION_MANAGER_H
