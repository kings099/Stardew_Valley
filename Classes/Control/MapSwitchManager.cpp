/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapSwitchManager.cpp
 * File Function: 地图切换控制类MapSwitchManager的实现
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "MapSwitchManager.h"

MapSwitchManager::MapSwitchManager()
    : _character(nullptr), _currentMap(nullptr) {}

MapSwitchManager::~MapSwitchManager() {}

MapSwitchManager* MapSwitchManager::create(Character* character, GameMap* currentMap) {
    MapSwitchManager* ret = new (std::nothrow) MapSwitchManager();
    if (ret && ret->init(character, currentMap)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MapSwitchManager::init(Character* character, GameMap* currentMap) {
    if (!Node::init()) {
        return false;
    }

    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(currentMap != nullptr, "Current map must not be null");

    _character = character;
    _currentMap = currentMap;

    return true;
}

bool MapSwitchManager::switchMap(const std::string& newMapFile, int teleportID)
{
    if (!_currentMap)
    {
        CCLOG("No current map to switch from.");
        return false;
    }

    // 移除旧地图
    _currentMap->loadMap(newMapFile);
    _character->setPosition(Vec2(0, 0));
    CCLOG("cPOs:%f,%f", _character->getPositionX(), _character->getPositionY());
    CCLOG("mapPos:%,%f", _currentMap->getPositionX(), _currentMap->getPositionY());
    // 根据传送点 ID 获取目标位置
    //Vec2 targetPosition = getTargetPositionByID(teleportID, _currentMap);
    //if (targetPosition == Vec2::ZERO)
    //{
    //    CCLOG("Failed to find target position for teleport ID: %d", teleportID);
    //    return false;
    //}

    // 设置角色位置
    //_character->setPosition(targetPosition);
    //CCLOG("Switched to map: %s, character moved to position: (%f, %f)",
    //    newMapFile.c_str(), targetPosition.x, targetPosition.y);

    return true;
}

//Vec2 MapSwitchManager::getTargetPositionByID(int teleportID, GameMap* newMap)
//{
//    // 获取新地图中所有传送点信息
//    auto allTiles = newMap->getAllTeleportTiles();
//    for (const auto& tile : allTiles)
//    {
//        int tileTeleportID = tile.properties["teleportID"].asInt();
//        if (tileTeleportID == teleportID)
//        {
//            return tile.position;  // 返回匹配 ID 的瓦片位置
//        }
//    }
//    return Vec2::ZERO;  // 未找到对应的传送点
//}

GameMap* MapSwitchManager::createMapByType(const std::string& mapFile)
{
    // 临时加载 TMX 文件以读取地图类型
    TMXTiledMap* tempMap = TMXTiledMap::create(mapFile);
    if (!tempMap)
    {
        CCLOG("Failed to load map for type detection: %s", mapFile.c_str());
        return nullptr;
    }

    // 获取地图类型属性
    ValueMap mapProperties = tempMap->getProperties();
    std::string mapType = mapProperties["mapType"].asString();

    // 根据地图类型创建对应的地图类实例
    GameMap* newMap = nullptr;
    if (mapType == "indoor")
    {
        newMap = IndoorMap::create(mapFile);
    }
    else if (mapType == "farm")
    {
        newMap = FarmMap::create(mapFile);
    }
    else
    {
        CCLOG("Unknown map type: %s", mapType.c_str());
    }

    // 释放临时 TMX 对象
    tempMap->removeFromParentAndCleanup(true);
    return newMap;
}
