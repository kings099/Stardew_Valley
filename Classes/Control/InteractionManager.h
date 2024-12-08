/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 角色地图交互控制类InteractionManager的定义
 * Author:        金恒宇
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __INTERACTION_MANAGER_H__
#define __INTERACTION_MANAGER_H__

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Maps/FarmMap.h"

class InteractionManager : public cocos2d::Ref
{
public:

    static InteractionManager* create(Character* character, FarmMap* farmMap);
    virtual bool init(Character* character, FarmMap* farmMap);

    // 更新角色周围格子信息
    void updateSurroundingTiles(Vec2& world_pos);

    // 判断当前位置及指定位置上的交互属性
    bool isCollidableAtPos(const cocos2d::Vec2& worldPos);
    bool isFarmlandAtPos(const cocos2d::Vec2& worldPos);
    bool isWaterableAtPos(const cocos2d::Vec2& worldPos);

    // 获取周围位置可移动状态
    std::vector<bool> getSorroundingCollidable(const Vec2& currentPos);
    // 其它交互逻辑可以在这里扩展，比如采集资源、开垦土地等
    // void harvestAtPos(const cocos2d::Vec2& worldPos);
    // void plowAtPos(const cocos2d::Vec2& worldPos);
    // void waterAtPos(const cocos2d::Vec2& worldPos);

protected:
    InteractionManager();
    ~InteractionManager();
    // 获取周围9格（包括当前所在格）瓦片信息
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> getSurroundingTilesInfo(const cocos2d::Vec2& worldPos);

    Character* _character;
    FarmMap* _farmMap;
    //存储周围9格瓦片信息
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> _surroundingInfo;
};

#endif // __INTERACTION_MANAGER_H__
