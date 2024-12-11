/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapSwitchManager.cpp
 * File Function: ��ͼ�л�������MapSwitchManager��ʵ��
 * Author:        �����
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

    // �Ƴ��ɵ�ͼ
    _currentMap->loadMap(newMapFile);
    _character->setPosition(Vec2(0, 0));
    CCLOG("cPOs:%f,%f", _character->getPositionX(), _character->getPositionY());
    CCLOG("mapPos:%,%f", _currentMap->getPositionX(), _currentMap->getPositionY());
    // ���ݴ��͵� ID ��ȡĿ��λ��
    //Vec2 targetPosition = getTargetPositionByID(teleportID, _currentMap);
    //if (targetPosition == Vec2::ZERO)
    //{
    //    CCLOG("Failed to find target position for teleport ID: %d", teleportID);
    //    return false;
    //}

    // ���ý�ɫλ��
    //_character->setPosition(targetPosition);
    //CCLOG("Switched to map: %s, character moved to position: (%f, %f)",
    //    newMapFile.c_str(), targetPosition.x, targetPosition.y);

    return true;
}

//Vec2 MapSwitchManager::getTargetPositionByID(int teleportID, GameMap* newMap)
//{
//    // ��ȡ�µ�ͼ�����д��͵���Ϣ
//    auto allTiles = newMap->getAllTeleportTiles();
//    for (const auto& tile : allTiles)
//    {
//        int tileTeleportID = tile.properties["teleportID"].asInt();
//        if (tileTeleportID == teleportID)
//        {
//            return tile.position;  // ����ƥ�� ID ����Ƭλ��
//        }
//    }
//    return Vec2::ZERO;  // δ�ҵ���Ӧ�Ĵ��͵�
//}

GameMap* MapSwitchManager::createMapByType(const std::string& mapFile)
{
    // ��ʱ���� TMX �ļ��Զ�ȡ��ͼ����
    TMXTiledMap* tempMap = TMXTiledMap::create(mapFile);
    if (!tempMap)
    {
        CCLOG("Failed to load map for type detection: %s", mapFile.c_str());
        return nullptr;
    }

    // ��ȡ��ͼ��������
    ValueMap mapProperties = tempMap->getProperties();
    std::string mapType = mapProperties["mapType"].asString();

    // ���ݵ�ͼ���ʹ�����Ӧ�ĵ�ͼ��ʵ��
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

    // �ͷ���ʱ TMX ����
    tempMap->removeFromParentAndCleanup(true);
    return newMap;
}
