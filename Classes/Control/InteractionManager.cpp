/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��ɫ��ͼ����������InteractionManager��ʵ��
 * Author:        �����
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#include "InteractionManager.h"
USING_NS_CC;

InteractionManager::InteractionManager() : _character(nullptr), _farmMap(nullptr)
{}

InteractionManager::~InteractionManager()
{}

InteractionManager* InteractionManager::create(Character* character, FarmMap* gameMap)
{
    InteractionManager* ret = new (std::nothrow) InteractionManager();
    if (ret && ret->init(character, gameMap))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool InteractionManager::init(Character* character, FarmMap* gameMap)
{
    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(gameMap != nullptr, "GameMap must not be null");

    _character = character;
    _farmMap = gameMap;

    return true;
}

void InteractionManager::updateSurroundingTiles(Vec2& world_pos)
{
    if (!_farmMap || !_character) return;


    _surroundingInfo = getSurroundingTilesInfo(world_pos);
}

bool InteractionManager::isCollidableAtPos(const Vec2& tilePos)
{
    if (!_farmMap) {
        CCLOG("wrong map");
        return true;
    }
    Size mapSizeinTile = _farmMap->getMapSizeinTile();
    // ��ͼ��λ��Ϊtrue(�����ƶ���
    if (tilePos.x<0 || tilePos.y<0 || tilePos.x>=mapSizeinTile.width || tilePos.y>=mapSizeinTile.height) {
        CCLOG("%f,%f", mapSizeinTile.width,mapSizeinTile.height);
        return true;
    }
    int GIDPath = _farmMap->getTileGIDAt("path", tilePos);
    int GIDBuildings = _farmMap->getTileGIDAt("buildings", tilePos);
    ValueMap path_properties = _farmMap->getTilePropertiesForGID(GIDPath);
    ValueMap buildings_properties = _farmMap->getTilePropertiesForGID(GIDBuildings);
    if (!path_properties.empty() || !buildings_properties.empty())
    {
        if (path_properties.find("canNotMove") != path_properties.end())
        {
            return path_properties["canNotMove"].asBool();
        }
        if (buildings_properties.find("canNotMove") != buildings_properties.end())
        {
            return buildings_properties["canNotMove"].asBool();
        }
    }
    return false;
}

std::vector<bool> InteractionManager::getSorroundingCollidable(const Vec2& currentPos) {
    // ��ȡ��ɫ���ڵ�Tile����
    Vec2 tile_pos = _farmMap->absoluteToTile(currentPos);
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

bool InteractionManager::isFarmlandAtPos(const Vec2& worldPos)
{
    if (!_farmMap) return false;

    Vec2 tilePos = _farmMap->absoluteToTile(worldPos);
    int GIDBack = _farmMap->getTileGIDAt("back", tilePos);
    ValueMap properties = _farmMap->getTilePropertiesForGID(GIDBack);
    if (!properties.empty())
    {
        if (properties.find("canFarm") != properties.end())
        {
            return properties["canFarm"].asBool();
        }
    }
    return false;
}

std::vector<std::tuple<std::string, int, ValueMap>> InteractionManager::getSurroundingTilesInfo(const Vec2& worldPos)
{
    // ��ȡ��ɫ���ڵ�Tile����
    Vec2 tile_pos = _farmMap->absoluteToTile(worldPos);

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
    for (auto& coord : surroundingCoords)
    {
        for (auto& layerName : layers)
        {
            int GID = _farmMap->getTileGIDAt(layerName, coord);
            ValueMap prop = _farmMap->getTilePropertiesForGID(GID);
            result.push_back(std::make_tuple(layerName, GID, prop));
        }
        ++i;
    }

    return result;
}