/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 角色地图交互控制类InteractionManager的实现
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
 // InteractionManager.cpp
#include "InteractionManager.h"
#include "cocos2d.h"

USING_NS_CC;

InteractionManager::InteractionManager() :  _gameMap(nullptr) {
    CCLOG("InteractionManager constructed: _gameMap=%p",  _gameMap);
}

InteractionManager::~InteractionManager() {
    CCLOG("InteractionManager destructed at %p", this);
}

InteractionManager* InteractionManager::create(GameMap* gameMap) {
    InteractionManager* ret = new (std::nothrow) InteractionManager();
    if (ret && ret->init(gameMap)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool InteractionManager::init(GameMap* gameMap) {
    if (!Node::init()) {
        return false;
    }

    CCASSERT(gameMap != nullptr, "GameMap must not be null");

    _gameMap = gameMap;

    return true;
}

void InteractionManager::updateSurroundingTiles(Vec2& world_pos) {
    if (!_gameMap ) {
        CCLOG("InteractionManager: Invalid state. gameMap is null.");
        return;
    }

    _surroundingTiles.clear(); // 清空上次的瓦片信息
    Vec2 tile_pos = _gameMap->absoluteToTile(world_pos);

    // 获取周围 9 格的瓦片
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),     Vec2(tile_pos.x, tile_pos.y),     Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };
    for (const auto& coord : surroundingCoords) {
        TileInfo tileInfo;
        tileInfo.tilePos = coord;
        tileInfo.WorldPos = _gameMap->tileToAbsolute(coord);
        tileInfo.type = Other; // 默认类型
        tileInfo.isObstacle = isCollidableAtPos(coord);

        // 获取 path 层瓦片信息
        int pathGID = _gameMap->getTileGIDAt("path", coord);
        if (pathGID != 0) {
            ValueMap pathProps = _gameMap->getTilePropertiesForGID(pathGID);
            if (pathProps.find("isGrass") != pathProps.end() && pathProps["isGrass"].asBool()) {
                tileInfo.type = Grass;
            }
            else if (pathProps.find("isStone") != pathProps.end() && pathProps["isStone"].asBool()) {
                tileInfo.type = Stone;
            }
        }

        // 检查是否为 Soil（可耕种土地）
        int backGID = _gameMap->getTileGIDAt("back", coord);
        int buildingGID = _gameMap->getTileGIDAt("buildings", coord);
        int FarmGID = _gameMap->getTileGIDAt("farm", coord);
        if (backGID != 0 && buildingGID == 0 && pathGID == 0) {
            ValueMap backProps = _gameMap->getTilePropertiesForGID(backGID);
            if (backProps.find("canFarm") != backProps.end() && backProps["canFarm"].asBool()) {
                tileInfo.type = Soil;
            }
        }
        // 检查是否为 Soiled
        if (FarmGID == DRY_FARM_TILE_GID) {
            tileInfo.type = Soiled;
        }

        _surroundingTiles.push_back(tileInfo); // 保存到 _surroundingTiles
    }
}

bool InteractionManager::isCollidableAtPos(const Vec2& tilePos) {
    if (!_gameMap) {
        CCLOG("wrong map");
        return true;
    }
    Size mapSizeinTile = _gameMap->getMapSizeinTile();
    if (tilePos.x < 0 || tilePos.y < 0 || tilePos.x >= mapSizeinTile.width || tilePos.y >= mapSizeinTile.height) {
        CCLOG("%f,%f", mapSizeinTile.width, mapSizeinTile.height);
        return true;
    }
    int GIDPath = _gameMap->getTileGIDAt("path", tilePos);
    int GIDBuildings = _gameMap->getTileGIDAt("buildings", tilePos);
    int GIDHouse = _gameMap->getTileGIDAt("house", tilePos);
    ValueMap path_properties = _gameMap->getTilePropertiesForGID(GIDPath);
    ValueMap buildings_properties = _gameMap->getTilePropertiesForGID(GIDBuildings);
    ValueMap house_properties = _gameMap->getTilePropertiesForGID(GIDHouse);
    if (GIDBuildings != 0) {
        return true;
    }
    if (!path_properties.empty() || !buildings_properties.empty()||!house_properties.empty()) {
        if (path_properties.find("canNotMove") != path_properties.end()) {
            return path_properties["canNotMove"].asBool();
        }
        if (buildings_properties.find("canNotMove") != buildings_properties.end()) {
            return buildings_properties["canNotMove"].asBool();
        }
        if (house_properties.find("canNotMove") != house_properties.end()) {
            return house_properties["canNotMove"].asBool();
        }
    }
    return false;
}


bool InteractionManager::checkTeleport(const Vec2& worldPos, std::string& targetMapFile) {
    if (!_gameMap) return false;

    Vec2 tilePos = _gameMap->absoluteToTile(worldPos);
    int teleprtGID = _gameMap->getTileGIDAt("Teleport",tilePos);
    if (teleprtGID != 0 ) {
        ValueMap properties = _gameMap->getTilePropertiesForGID(teleprtGID);
        if (!properties.empty() && properties.find("TargetMap") != properties.end()) {
            targetMapFile = properties["TargetMap"].asString();
            return true;  // 检测到传送点
        }
        return true;
    }
    return false;
}

void InteractionManager::setMap(GameMap* newMap) {
    if (newMap) {
        _gameMap = newMap;
        CCLOG("InteractionManager updated to new map: %p", _gameMap);
    }
}

const std::vector<TileInfo>& InteractionManager::getSurroundingTiles() const {
    return _surroundingTiles;
}

// 在指定位置播放对应action的图块变化
void InteractionManager::ActionAnimation(GameCharacterAction action, const Vec2& TilePos) {
    switch (action) {
    case Plowing:
        _gameMap->replaceTileAt("farm", TilePos, DRY_FARM_TILE_GID);
        break;
    case Watering:
        _gameMap->replaceTileAt("farm", TilePos, DRY_FARM_TILE_GID);
        break;
    case Weeding:
        _gameMap->replaceTileAt("path", TilePos, EMPTY_GID);
        Crops::playWeedingAnimation(_gameMap->tileToRelative(TilePos), _gameMap->getTiledMap());
        break;
    case Mining:
        _gameMap->replaceTileAt("path", TilePos, EMPTY_GID);
        Crops::playStoneBreakingAnimationAt(_gameMap->tileToRelative(TilePos), _gameMap->getTiledMap());
        
        break;
    case Placement:
        // TODO : 播种 待实现
        break;
    }
}