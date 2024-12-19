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
    virtual ~TownMap();

    // 创建函数
    static TownMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 重写初始化函数
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition) override;

    // 获取 TMXTiledMap 对象
    virtual TMXTiledMap* getTiledMap() const;

    // 处理鼠标事件
    bool onMouseEvent(Event* event);

private:


    // 城镇地图的缩放比例
    static constexpr float TOWN_MAP_SCALE = 2.0f; // 根据需要调整缩放比例
};

#endif // TOWNMAP_H