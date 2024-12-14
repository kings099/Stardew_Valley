/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��ɫ��ͼ����������InteractionManager��ʵ��
 * Author:        �����
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

    _surroundingTiles.clear(); // ����ϴε���Ƭ��Ϣ
    Vec2 tile_pos = _gameMap->absoluteToTile(world_pos);

    // ��ȡ��Χ 9 �����Ƭ
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),     Vec2(tile_pos.x, tile_pos.y),     Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };

    for (const auto& coord : surroundingCoords) {
        TileInfo tileInfo;
        tileInfo.tilePos = coord;
        tileInfo.type = Other; // Ĭ������
        tileInfo.isObstacle = isCollidableAtPos(coord);

        // ��ȡ path ����Ƭ��Ϣ
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

        // ����Ƿ�Ϊ Soil���ɸ������أ�
        int backGID = _gameMap->getTileGIDAt("back", coord);
        int buildingGID = _gameMap->getTileGIDAt("buildings", coord);
        if (backGID != 0 && buildingGID == 0 && pathGID == 0) {
            ValueMap backProps = _gameMap->getTilePropertiesForGID(backGID);
            if (backProps.find("canFarm") != backProps.end() && backProps["canFarm"].asBool()) {
                tileInfo.type = Soil;
            }
        }

        _surroundingTiles.push_back(tileInfo); // ���浽 _surroundingTiles
    }
   // CCLOG("Surrounding tiles obstacle map:");
    for (int row = 0; row < 3; ++row) {
        std::string line;
        for (int col = 0; col < 3; ++col) {
            int index = row * 3 + col;
            line += _surroundingTiles[index].isObstacle ? "1 " : "0 ";
        }
      //  CCLOG("%s", line.c_str());
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
    Vec2 tile_pos = _gameMap->absoluteToTile(currentPos);
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),   Vec2(tile_pos.x, tile_pos.y),   Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };
    std::vector<bool> Moveable;
    for (Vec2 coord : surroundingCoords) {
        bool canNotMove = isCollidableAtPos(coord);
        Moveable.push_back(!canNotMove);
    }
    return Moveable;
}

bool InteractionManager::checkTeleport(const Vec2& worldPos, std::string& targetMapFile) {
    if (!_gameMap) return false;

    Vec2 tilePos = _gameMap->absoluteToTile(worldPos);
    if (tilePos == Vec2(0, 0)) {
        targetMapFile = "../Resources/Maps/Farm/house.tmx";
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