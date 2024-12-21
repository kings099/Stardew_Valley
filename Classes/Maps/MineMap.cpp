/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MineMap.cpp
 * File Function: 初始化矿洞地图
 * Author:        胡宝怡、金恒宇
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#include "MineMap.h"

USING_NS_CC;

MineMap::MineMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}


MineMap::~MineMap()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}

MineMap* MineMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    MineMap* ret = new MineMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool MineMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用父类的初始化方法
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    _mapName = mapFile;
    _map_position = mapPosition;
    this->setScale(INDOOR_MAP_SCALE);

    return true;
}

// 采矿地图的更改地块逻辑重写
void MineMap::replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction) {
    // 获取目标图层
    auto layer = _tile_map->getLayer(layerName);
    if (!layer) {
        CCLOG("Layer '%s' not found!", layerName.c_str());
        return;
    }

    // 检查瓦片坐标是否在地图范围内
    auto mapSize = _tile_map->getMapSize(); // 地图的瓦片尺寸（宽高瓦片数）
    if (tileCoord.x < 0 || tileCoord.y < 0 || tileCoord.x >= mapSize.width || tileCoord.y >= mapSize.height) {
        CCLOG("Tile position (%f, %f) is out of bounds!", tileCoord.x, tileCoord.y);
        return;
    }

    // 设置新的瓦片 GID
    layer->setTileGID(newGID, tileCoord);
    CCLOG("Replaced tile at (%f, %f) on layer '%s' with GID=%d", tileCoord.x, tileCoord.y, layerName.c_str(), newGID);

    // 如果是用户行为，处理保存逻辑；非用户行为（如应用保存的更改）不保存，避免死循环
    if (isUserAction) {
        // 获取当前瓦片的 TileInfo
        TileConstants::TileType tiletype = getTileTypeAt(tileCoord);

        // 根据 TileInfo 类型处理
        if (tiletype == TileConstants::TileType::Treasure) {
            // 如果瓦片类型为 "Treasure"，直接保存更改
            MapStateManager::getInstance().saveTileChange(
                _mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
            CCLOG("Treasure tile at (%f, %f) saved with new GID=%d", tileCoord.x, tileCoord.y, newGID);
        }
        else if (tiletype == TileConstants::TileType::Mine) {
            // 如果瓦片类型为 "Mine"，20% 的概率保存毁坏状态
            float randomValue = CCRANDOM_0_1(); // 生成随机数 [0, 1]
            if (randomValue <= 0.2f) {
                // 满足概率条件时保存更改
                MapStateManager::getInstance().saveTileChange(
                    _mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
                CCLOG("Mine tile at (%f, %f) recorded for destruction (20%% chance triggered)", tileCoord.x, tileCoord.y);
            }
            else {
                // 未满足概率条件时，不保存
                CCLOG("Mine tile at (%f, %f) not recorded for destruction (20%% chance not triggered)", tileCoord.x, tileCoord.y);
            }
        }
        else {
            // 其他瓦片类型直接保存
            MapStateManager::getInstance().saveTileChange(
                _mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
            CCLOG("Tile at (%f, %f) of type '%d' saved with new GID=%d", tileCoord.x, tileCoord.y, tiletype, newGID);
        }
    }
}

// 获取指定瓦片的类型
TileConstants::TileType MineMap::getTileTypeAt(const Vec2& tileCoord) const {
    int layerGID = this->getTileGIDAt("ore", tileCoord); 
    if (layerGID == 0) {
        CCLOG("No tile found at (%f, %f)", tileCoord.x, tileCoord.y);
        return TileConstants::TileType::Other; // 返回默认类型
    }

    // 获取瓦片的属性信息
    ValueMap tileProps = this->getTilePropertiesForGID(layerGID);

    // 判断瓦片类型
    if (tileProps.find("isSteel") != tileProps.end() && tileProps["isSteel"].asBool()) {
        return TileConstants::TileType::Mine; // 矿石类型：钢矿
    }
    else if (tileProps.find("isCopper") != tileProps.end() && tileProps["isCopper"].asBool()) {
        return TileConstants::TileType::Mine; // 矿石类型：铜矿
    }
    else if (tileProps.find("isTreasure") != tileProps.end() && tileProps["isTreasure"].asBool()) {
        return TileConstants::TileType::Treasure; // 宝藏类型
    }
    else if (tileProps.find("isRing") != tileProps.end() && tileProps["isRing"].asBool()) {
        return TileConstants::TileType::Treasure; // 戒指类型
    }

    return TileConstants::TileType::Other; // 其他类型
}