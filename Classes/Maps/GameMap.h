/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: 地图基类Map类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "cocos2d.h"
#include "Crops/Crops.h"
#include "Control/MapStateManager.h"

USING_NS_CC;

class GameMap : public Node {
public:
    GameMap(const Vec2& mapPosition = Vec2(0, 0));
    virtual ~GameMap();

    // 创建地图
    static GameMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 初始化地图
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);

    // 转换世界坐标到地图瓦片坐标
    virtual Vec2 absoluteToTile(const Vec2& pixelPoint);

    // 转换瓦片坐标到世界坐标（中点）
    Vec2 tileToAbsolute(const Vec2& tileCoord);

    // 转换瓦片坐标到以地图为父节点的相对坐标（中点）
    Vec2 tileToRelative(const Vec2& tileCoord);

    // 地图像素大小
    const Size& getMapSize() const;

    // 地图瓦片大小
    const Size& getMapSizeinTile();

    // 地图绝对位置
    const Vec2& GameMap::getPosition();

    // 获取某位置Layername图层的GID
    virtual int getTileGIDAt(const std::string& layerName, const Vec2& tileCoord);

    // 获取某GID对应图块的属性
    virtual cocos2d::ValueMap getTilePropertiesForGID(int GID);

    // 替换指定图层的瓦片
    void replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction = true);

    // 获取作物的指针，在农场子类中实现，其他类型返回nullptr
    virtual Crops* getTreeAtPosition(const Vec2& tilePos);

    // 获取瓦片地图指针
    TMXTiledMap* getTiledMap() const;

    // 恢复存储的地图信息
    void applySavedChanges();

    // 保存地图信息，虚函数是为了防止子类有其他需要保存的信息
    virtual void saveChangesToStateManager() const;

protected:
    std::string _mapName;     // 地图文件名
    TMXTiledMap* _tile_map;  // 瓦片地图类
    Vec2 _map_position;      // 地图创建位置
};

#endif // GAME_MAP_H_
