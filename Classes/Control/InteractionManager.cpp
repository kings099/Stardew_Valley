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

InteractionManager::InteractionManager() : _character(nullptr), _gameMap(nullptr) {
    CCLOG("InteractionManager constructed: _character=%p, _gameMap=%p", _character, _gameMap);
}

InteractionManager::~InteractionManager() {
    CCLOG("InteractionManager destructed at %p", this);
}

InteractionManager* InteractionManager::create(Character* character, GameMap* gameMap) {
    InteractionManager* ret = new (std::nothrow) InteractionManager();
    if (ret && ret->init(character, gameMap)) {
        ret->autorelease(); // ��ӵ��ڵ���ʱ���Զ�������������
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool InteractionManager::init(Character* character, GameMap* gameMap) {
    if (!Node::init()) { // ȷ������ Node �ĳ�ʼ��
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
    // ��ͼ��λ��Ϊtrue(�����ƶ���
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
    // ��ȡ��ɫ���ڵ�Tile����
    Vec2 tile_pos = _gameMap->absoluteToTile(currentPos);
    // ��ȡ��Χ8�����Ӽ��ϵ�ǰλ�ã���9����
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),   Vec2(tile_pos.x, tile_pos.y),   Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };
    std::vector<bool> Moveable;
    for (Vec2 coord : surroundingCoords) {
        bool canNotMove = isCollidableAtPos(coord); // isCollidableAtPos ���� 0�����ƶ����� 1�������ƶ���
        Moveable.push_back(!canNotMove);
    }

    // ���������Ϣ
    CCLOG("Character at tile: (%d, %d)", static_cast<int>(tile_pos.x), static_cast<int>(tile_pos.y));
    CCLOG("Surrounding tiles walkable state:");

    for (int y = 0; y < 3; ++y) {
        std::string row;
        for (int x = 0; x < 3; ++x) {
            // �� Moveable �а�����������ȡֵ
            row += Moveable[y * 3 + x] ? "1 " : "0 ";
        }
        CCLOG("%s", row.c_str()); // ���ÿһ��
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

    // ��ȡ��Χ8�����Ӽ��ϵ�ǰλ�ã���9����
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),   Vec2(tile_pos.x, tile_pos.y),   Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };

    // ��Ҫ����ͼ��
    std::vector<std::string> layers = { "back", "path", "buildings" };

    std::vector<std::tuple<std::string, int, ValueMap>> result;
    int i = 0; // ���ڼ�¼ surroundingCoords ������
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

    // ��ȡ��Ƭ����
    //ValueMap properties = _gameMap->getTilePropertiesForGID(GID);
    if (tilePos == Vec2(0, 0)) {
        targetMapFile = "../Resources/Maps/Farm/house.tmx";
        return true;  // ��⵽���͵�
    }

    return false;
}

void InteractionManager::setMap(GameMap* newMap) {
    if (newMap) {
        _gameMap = newMap;
        CCLOG("InteractionManager updated to new map: %p", _gameMap);
    }
}
