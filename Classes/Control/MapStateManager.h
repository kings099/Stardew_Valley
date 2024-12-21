/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapStateManager.cpp
 * File Function: 地图保存管理单例类MapStateManager的实现
 * Author:        金恒宇
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MAP_STATE_MANAGER_H_
#define MAP_STATE_MANAGER_H_

#include <unordered_map>
#include <vector>
#include <string>
#include "proj.win32/Constant.h"
#include "cocos2d.h"


class MapStateManager {
public:
    // 获取单例实例
    static MapStateManager& getInstance();

    // 保存瓦片更改
    void saveTileChange(const std::string& mapName, const TileConstants::TileChange& change);

    // 获取指定地图的所有更改
    const std::vector<TileConstants::TileChange>& getTileChanges(const std::string& mapName) const;

    // 清除指定地图的所有更改
    void clearTileChanges(const std::string& mapName);

private:
    // 构造函数和析构函数私有化
    MapStateManager() = default;
    ~MapStateManager() = default;

    // 禁用拷贝构造和赋值运算符
    MapStateManager(const MapStateManager&) = delete;
    MapStateManager& operator=(const MapStateManager&) = delete;

    // 存储每张地图的瓦片更改
    std::unordered_map<std::string, std::vector<TileConstants::TileChange>> _mapChanges;
};
#endif // MAP_STATE_MANAGER_H_
