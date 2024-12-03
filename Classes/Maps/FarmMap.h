/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: 初始农场地图FarmMap类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/2
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FARM_MAP_H_
#define FARM_MAP_H_

#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"


class FarmMap : public cocos2d::Node
{
public:
    FarmMap();
    ~FarmMap();

    // 创建农场地图
    static FarmMap* create(const std::string& mapFile);

    // 初始化函数
    virtual bool init(const std::string& mapFile);

    // 更新地图位置
    void updateMapPosition(const cocos2d::Vec2& characterPosition); 

    // 鼠标事件处理
    bool onMouseEvent(cocos2d::Event* event);

private:
    cocos2d::TMXTiledMap* _tileMap;  // 瓦片地图对象
};

#endif // __FARM_MAP_H__

