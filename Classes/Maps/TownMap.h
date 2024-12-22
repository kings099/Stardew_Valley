/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TownMap.h
 * File Function: 小镇地图TownMap类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef TOWNMAP_H
#define TOWNMAP_H

#include "GameMap.h"
USING_NS_CC;

class TownMap : public GameMap
{
public:
    // 构造函数和析构函数
    TownMap(const Vec2& mapPosition);
    ~TownMap();

    // 创建函数
    static TownMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 重写初始化函数 
    bool init(const std::string& mapFile, const Vec2& mapPosition) override;


    MapType getType() const override { return MapType::Farm; }
};

#endif // TOWNMAP_H