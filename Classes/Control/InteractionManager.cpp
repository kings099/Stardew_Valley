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

InteractionManager::InteractionManager() : _character(nullptr), _gameMap(nullptr) {
    CCLOG("InteractionManager constructed: _character=%p, _gameMap=%p", _character, _gameMap);
}

InteractionManager::~InteractionManager() {
    CCLOG("InteractionManager destructed at %p", this);
}

InteractionManager* InteractionManager::create(Character* character, GameMap* gameMap) {
    InteractionManager* ret = new (std::nothrow) InteractionManager();
    if (ret && ret->init(character, gameMap)) {
        ret->autorelease(); // 添加到节点树时会自动管理生命周期
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool InteractionManager::init(Character* character, GameMap* gameMap) {
    if (!Node::init()) { // 确保调用 Node 的初始化
        return false;
    }

    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(gameMap != nullptr, "GameMap must not be null");

    _character = character;
    _gameMap = gameMap;

    return true;
}

void InteractionManager::updateSurroundingTiles(Vec2& world_pos) {
    if (!_gameMap || !_character) {
        CCLOG("InteractionManager: Invalid state. gameMap or character is null.");
        return;
    }

    _surroundingInfo = getSurroundingTilesInfo(world_pos);
}

bool InteractionManager::isCollidableAtPos(const Vec2& tilePos) {
    if (!_gameMap) {
        CCLOG("wrong map");
        return true;
    }
    Size mapSizeinTile = _gameMap->getMapSizeinTile();
    // 地图外位置为true(不可移动）
    if (tilePos.x < 0 || tilePos.y < 0 || tilePos.x >= mapSizeinTile.width || tilePos.y >= mapSizeinTile.height) {
        CCLOG("%f,%f", mapSizeinTile.width, mapSizeinTile.height);
        return true;
    }
    int GIDPath = _gameMap->getTileGIDAt("path", tilePos);
    int GIDBuildings = _gameMap->getTileGIDAt("buildings", tilePos);
    ValueMap path_properties = _gameMap->getTilePropertiesForGID(GIDPath);
    ValueMap buildings_properties = _gameMap->getTilePropertiesForGID(GIDBuildings);
    if (!path_properties.empty() || !buildings_properties.empty()) {
        if (path_properties.find("canNotMove") != path_properties.end()) {
            return path_properties["canNotMove"].asBool();
        }
        if (buildings_properties.find("canNotMove") != buildings_properties.end()) {
            return buildings_properties["canNotMove"].asBool();
        }
    }
    return false;
}

std::vector<bool> InteractionManager::getSurroundingCollidable(const Vec2& currentPos) {
    // 获取角色所在的Tile坐标
    Vec2 tile_pos = _gameMap->absoluteToTile(currentPos);
    // 获取周围8个格子加上当前位置，即9个点
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),   Vec2(tile_pos.x, tile_pos.y),   Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };
    std::vector<bool> Moveable;
    for (Vec2 coord : surroundingCoords) {
        bool canNotMove = isCollidableAtPos(coord); // isCollidableAtPos 返回 0（可移动）或 1（不可移动）
        Moveable.push_back(!canNotMove);
    }

    // 输出调试信息
    CCLOG("Character at tile: (%d, %d)", static_cast<int>(tile_pos.x), static_cast<int>(tile_pos.y));
    CCLOG("Surrounding tiles walkable state:");

    for (int y = 0; y < 3; ++y) {
        std::string row;
        for (int x = 0; x < 3; ++x) {
            // 从 Moveable 中按行列索引获取值
            row += Moveable[y * 3 + x] ? "1 " : "0 ";
        }
        CCLOG("%s", row.c_str()); // 输出每一行
    }

    return Moveable;
}

bool InteractionManager::isFarmlandAtPos(const Vec2& worldPos) {
    if (!_gameMap) return false;

    Vec2 tilePos = _gameMap->absoluteToTile(worldPos);
    int GIDBack = _gameMap->getTileGIDAt("back", tilePos);
    ValueMap properties = _gameMap->getTilePropertiesForGID(GIDBack);
    if (!properties.empty()) {
        if (properties.find("canFarm") != properties.end()) {
            return properties["canFarm"].asBool();
        }
    }
    return false;
}

std::vector<std::tuple<std::string, int, ValueMap>> InteractionManager::getSurroundingTilesInfo(const Vec2& worldPos) {
    if (!_gameMap) {
        CCLOG("InteractionManager: gameMap is null in getSurroundingTilesInfo.");
        return {};
    }

    Vec2 tile_pos = _gameMap->absoluteToTile(worldPos);

    // 获取周围8个格子加上当前位置，即9个点
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),   Vec2(tile_pos.x, tile_pos.y),   Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };

    // 需要检查的图层
    std::vector<std::string> layers = { "back", "path", "buildings" };

    std::vector<std::tuple<std::string, int, ValueMap>> result;
    int i = 0; // 用于记录 surroundingCoords 的索引
    for (auto& coord : surroundingCoords) {
        for (auto& layerName : layers) {
            int GID = _gameMap->getTileGIDAt(layerName, coord);
            ValueMap prop = _gameMap->getTilePropertiesForGID(GID);
            result.push_back(std::make_tuple(layerName, GID, prop));
        }
        ++i;
    }

    return result;
}

bool InteractionManager::checkTeleport(const Vec2& worldPos, std::string& targetMapFile) {
    if (!_gameMap) return false;

    Vec2 tilePos = _gameMap->absoluteToTile(worldPos);
    //int GID = _gameMap->getTileGIDAt("teleport", tilePos);

    // 获取瓦片属性
    //ValueMap properties = _gameMap->getTilePropertiesForGID(GID);
    if (tilePos == Vec2(0, 0)) {
        targetMapFile = "../Resources/Maps/Farm/house.tmx";
        return true;  // 检测到传送点
    }

    return false;
}

void InteractionManager::setMap(GameMap* newMap) {
    if (newMap) {
        _gameMap = newMap;
        CCLOG("InteractionManager updated to new map: %p", _gameMap);
    }
}
