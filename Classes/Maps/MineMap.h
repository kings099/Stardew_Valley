/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MineMap.h
 * File Function: 初始化矿洞地图
 * Author:        胡宝怡、金恒宇（修改其中的虚函数，重写继承自基类的一些方法，灯光模拟类）
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

    ~MineMap();

    // 在mapposition位置创建农场地图，默认为0，0
    static MineMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 初始化函数
    bool init(const std::string& mapFile, const Vec2& mapPosition);

    // 重写替换地块逻辑，增加刷新逻辑
    void replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction = true) override;

    MapType getType() const { return MapType::Mine; }

private:

    // 获取指定瓦片的类型
    TileConstants::TileType getTileTypeAt(const Vec2& tileCoord) const;
};
#endif // __MINE_MAP_H_
