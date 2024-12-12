/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 角色地图交互控制类InteractionManager的实现
 * Author:        金恒宇
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#include "InteractionManager.h"
USING_NS_CC;

<<<<<<< Updated upstream
InteractionManager::InteractionManager() : _character(nullptr), _farmMap(nullptr)
{}

InteractionManager::~InteractionManager()
{}

InteractionManager* InteractionManager::create(Character* character, FarmMap* gameMap)
{
=======
// 构造函数
InteractionManager::InteractionManager() : _character(nullptr), _gameMap(nullptr) {
    //CCLOG("InteractionManager constructed: _character=%p, _gameMap=%p", _character, _gameMap);
}

// 析构函数
InteractionManager::~InteractionManager() {
    //CCLOG("InteractionManager destructed at %p", this);
}

// 创建交互管理器实例
InteractionManager* InteractionManager::create(Character* character, GameMap* gameMap) {
>>>>>>> Stashed changes
    InteractionManager* ret = new (std::nothrow) InteractionManager();
    if (ret && ret->init(character, gameMap))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

<<<<<<< Updated upstream
bool InteractionManager::init(Character* character, FarmMap* gameMap)
{
=======
// 初始化交互管理器
bool InteractionManager::init(Character* character, GameMap* gameMap) {
    if (!Node::init()) {
        return false;
    }

>>>>>>> Stashed changes
    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(gameMap != nullptr, "GameMap must not be null");

    _character = character;
    _farmMap = gameMap;

    return true;
}

<<<<<<< Updated upstream
void InteractionManager::updateSurroundingTiles(Vec2& world_pos)
{
    if (!_farmMap || !_character) return;
=======
// 更新角色周围的瓦片信息
void InteractionManager::updateSurroundingTiles(Vec2& world_pos) {
    if (!_gameMap || !_character) {
        CCLOG("InteractionManager: Invalid state. gameMap or character is null.");
        return;
    }
>>>>>>> Stashed changes


    _surroundingInfo = getSurroundingTilesInfo(world_pos);
}

<<<<<<< Updated upstream
bool InteractionManager::isCollidableAtPos(const Vec2& tilePos)
{
    if (!_farmMap) {
=======
// 判断指定瓦片位置是否为不可通行区域
bool InteractionManager::isCollidableAtPos(const Vec2& tilePos) {
    if (!_gameMap) {
>>>>>>> Stashed changes
        CCLOG("wrong map");
        return true;
    }
    Size mapSizeinTile = _farmMap->getMapSizeinTile();
    // 地图外位置为true(不可移动）
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

<<<<<<< Updated upstream
std::vector<bool> InteractionManager::getSorroundingCollidable(const Vec2& currentPos) {
    // 获取角色所在的Tile坐标
    Vec2 tile_pos = _farmMap->absoluteToTile(currentPos);
    // 获取周围8个格子加上当前位置，即9个点
=======
// 获取角色周围的可通行状态
std::vector<bool> InteractionManager::getSurroundingCollidable(const Vec2& currentPos) {
    Vec2 tile_pos = _gameMap->absoluteToTile(currentPos);
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
bool InteractionManager::isFarmlandAtPos(const Vec2& worldPos)
{
    if (!_farmMap) return false;
=======
// 判断指定世界坐标是否为可农耕区域
bool InteractionManager::checkTeleport(const Vec2& worldPos, std::string& targetMapFile) {
    if (!_gameMap) return false;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
std::vector<std::tuple<std::string, int, ValueMap>> InteractionManager::getSurroundingTilesInfo(const Vec2& worldPos)
{
    // 获取角色所在的Tile坐标
    Vec2 tile_pos = _farmMap->absoluteToTile(worldPos);

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
=======
// 改变地图
void InteractionManager::setMap(GameMap* newMap) {
    if (newMap) {
        _gameMap = newMap;
        CCLOG("InteractionManager updated to new map: %p", _gameMap);
    }
}

// 获取角色周围的瓦片信息
const std::vector<TileInfo>& InteractionManager::getSurroundingTiles() const {
    return _surroundingTiles;
>>>>>>> Stashed changes
}