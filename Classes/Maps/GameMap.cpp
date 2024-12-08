/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 地图基类Map类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/8
 * License:       MIT License
 ****************************************************************/

#include "GameMap.h"

USING_NS_CC;

GameMap::GameMap(const Vec2& mapPosition)
    : _tile_map(nullptr), _map_position(mapPosition) {}

GameMap::~GameMap() {}

GameMap* GameMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    GameMap* ret = new GameMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool GameMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用基类初始化方法
    if (!Node::init()) {
        return false;
    }

    // 加载地图
    _tile_map = TMXTiledMap::create(mapFile);
    if (!_tile_map) {
        CCLOG("Failed to load map");
        return false;
    }

    // 添加地图到当前节点
    this->addChild(_tile_map, 0);
    this->setPosition(_map_position);

    return true;
}

Vec2 GameMap::absoluteToTile(const Vec2& pixelPoint)
{
    // 获取瓦片大小
    Size tileSize = _tile_map->getTileSize();

    float tileX = (pixelPoint.x - _map_position.x) / tileSize.width;
    float tileY = (pixelPoint.y - _map_position.y) / tileSize.height;

    // 瓦片地图左上坐标系的y轴是翻转的
    tileY = _tile_map->getMapSize().height - tileY;

    return Vec2(floor(tileX), floor(tileY));
}

const Size& GameMap::getMapSize() const
{
    Size map_size_in_tiles = _tile_map->getMapSize();
    Size tile_size = _tile_map->getTileSize();

    float map_width_in_pixels = map_size_in_tiles.width * tile_size.width;
    float map_height_in_pixels = map_size_in_tiles.height * tile_size.height;

    return Size(map_width_in_pixels, map_height_in_pixels);
}

const Size& GameMap::getMapSizeinTile()
{
    return _tile_map->getMapSize();
}

int GameMap::getTileGIDAt(const std::string& layerName, const Vec2& tileCoord)
{
    auto layer = _tile_map->getLayer(layerName);
    if (!layer) {
        CCLOG("Invalid Layer name");
        return 0;
    }

    auto map_size = _tile_map->getMapSize();
    auto tile_size = _tile_map->getTileSize();

    if (tileCoord.x < 0 || tileCoord.y < 0 || tileCoord.x >= map_size.width || tileCoord.y >= map_size.height) {
        return 0;
    }

    return layer->getTileGIDAt(tileCoord);
}