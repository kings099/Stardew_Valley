/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.h
 * File Function: 初始化室内地图
 * Author:        胡宝怡
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef INDOOR_MAP_H_
#define INDOOR_MAP_H_
#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"
#include "GameMap.h"

USING_NS_CC;

class IndoorMap :public GameMap
{
public:
    IndoorMap(const Vec2& mapPosition);
    ~IndoorMap();

    // 在mapposition位置创建农场地图，默认为0，0
    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 初始化函数
    bool init(const std::string& mapFile, const Vec2& mapPosition);

    MapType getType() const override { return MapType::Indoor; }
};

#endif // __INDOOR_MAP_H_

