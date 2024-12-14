/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 地图基类Map类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/11
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
    float scale = this->getScale();
    // 获取瓦片大小
    Size tileSize = _tile_map->getTileSize();

    float tileX = (pixelPoint.x - _map_position.x) / (tileSize.width * scale);
    float tileY = (pixelPoint.y - _map_position.y) / (tileSize.height * scale);

    // 瓦片地图左上坐标系的y轴是翻转的
    tileY = _tile_map->getMapSize().height - tileY;

    return Vec2(floor(tileX), floor(tileY));
}

Vec2 GameMap::tileToAbsolute(const Vec2& tileCoord)
{
    float scale = this->getScale();
    // 获取瓦片大小
    Size tileSize = _tile_map->getTileSize();

    // 计算瓦片左下角的绝对坐标
    float pixelX = tileCoord.x * tileSize.width * scale + _map_position.x;
    float pixelY = (_tile_map->getMapSize().height - tileCoord.y - 1) * tileSize.height * scale + _map_position.y;

    // 加上瓦片一半的宽高，得到瓦片的中点坐标
    pixelX += (tileSize.width * scale) / 2.0f;
    pixelY += (tileSize.height * scale) / 2.0f;

    return Vec2(pixelX, pixelY);
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

cocos2d::ValueMap GameMap::getTilePropertiesForGID(int GID)
{
    if (GID == 0) return cocos2d::ValueMap();
    auto tileProperties = _tile_map->getPropertiesForGID(GID);
    if (tileProperties.getType() == Value::Type::MAP)
    {
        return tileProperties.asValueMap();
    }
    return cocos2d::ValueMap();
}

void GameMap::replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID) {
    // 获取目标图层
    auto layer = _tile_map->getLayer(layerName);
    if (!layer) {
        CCLOG("Layer '%s' not found!", layerName.c_str());
        return;
    }

    // 检查瓦片坐标是否有效
    auto mapSize = _tile_map->getMapSize(); // 地图尺寸（瓦片数）
    if (tileCoord.x < 0 || tileCoord.y < 0 || tileCoord.x >= mapSize.width || tileCoord.y >= mapSize.height) {
        CCLOG("Tile position (%f, %f) is out of bounds!", tileCoord.x, tileCoord.y);
        return;
    }

    // 设置新瓦片
    layer->setTileGID(newGID, tileCoord);
    CCLOG("Replaced tile at (%f, %f) on layer '%s' with GID=%d", tileCoord.x, tileCoord.y, layerName.c_str(), newGID);
}




