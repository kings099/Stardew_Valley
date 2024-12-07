/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: 初始农场地图FarmMap类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FARM_MAP_H_
#define FARM_MAP_H_


#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

class FarmMap : public cocos2d::Node
{
public:
    FarmMap(const Vec2& mapPosition);
    ~FarmMap();

    // 在mapposition位置创建农场地图，默认为0，0
    static FarmMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 初始化函数
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);

    // 绝对坐标到瓦片坐标的转换
    Vec2 absoluteToTile(const Vec2& pixelPoint);

    // 鼠标事件处理
    bool onMouseEvent(cocos2d::Event* event);

    //返回地图像素大小
    const Size& getMapSize()const;

    //返回瓦片地图大小（按瓦片计数）
    const Size& getMapSizeinTile();
    //获取指定位置指定图层的GID
    int getTileGIDAt(const std::string& layerName, const Vec2& tileCoord);


    // 根据GID获取瓦片属性（从 TMX 文件中的tilesets中读取）
    cocos2d::ValueMap getTilePropertiesForGID(int GID);


protected:
    cocos2d::TMXTiledMap* _tile_map;  // 瓦片地图对象
    Vec2 _map_position;
};

#endif // __FARM_MAP_H__

