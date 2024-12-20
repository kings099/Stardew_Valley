/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MineMap.h
 * File Function: 初始化矿洞地图
 * Author:        胡宝怡
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MINE_MAP_H_
#define MINE_MAP_H_
#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"
#include "GameMap.h"

USING_NS_CC;

class MineMap :public GameMap
{
public:
    MineMap(const Vec2& mapPosition);
    virtual ~MineMap();

    // 在mapposition位置创建农场地图，默认为0，0
    static MineMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 初始化函数
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);


};

#endif // __MINE_MAP_H_
