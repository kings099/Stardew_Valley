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
    : _character(nullptr), _currentMap(nullptr), _viewController(nullptr) {}

MapSwitchManager* MapSwitchManager::create(Character* character, GameMap* currentMap, GameViewController* viewController,InteractionManager* interactionManager) {
    MapSwitchManager* ret = new (std::nothrow) MapSwitchManager();
    if (ret && ret->init(character, currentMap, viewController, interactionManager)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MapSwitchManager::init(Character* character, GameMap* currentMap, GameViewController* viewController, InteractionManager* interactionManager) {
    if (!Node::init()) {
        return false;
    }

    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(currentMap != nullptr, "Current map must not be null");
    CCASSERT(viewController != nullptr, "GameViewController must not be null");
    CCASSERT(interactionManager != nullptr, "InteractionManager must not be null");

    _character = character;
    _currentMap = currentMap;
    _viewController = viewController;
    _interactionManager = interactionManager;

    return true;
}

bool MapSwitchManager::switchMap(const std::string& newMapFile, int teleportID) {
    CCLOG("Switching map to: %s", newMapFile.c_str());

    if (_currentMap) {
        _currentMap->removeFromParentAndCleanup(true);
    }

    GameMap* newMap = nullptr;

    if (newMapFile.find("farm") != std::string::npos) {
        newMap = FarmMap::create(newMapFile);
    }
    else if (newMapFile.find("house") != std::string::npos) {
        newMap = IndoorMap::create(newMapFile,Vec2(_character->getPosition().x-300,_character->getPosition().y));
    }
    else {
        CCLOG("Unknown map type for file: %s", newMapFile.c_str());
        return false;
    }

    if (!newMap) {
        CCLOG("Failed to create map: %s", newMapFile.c_str());
        return false;
    }

    _currentMap = newMap;
    this->addChild(_currentMap);

    Vec2 targetPosition = getTargetPositionByID(teleportID, _currentMap);
    //if (targetPosition == Vec2::ZERO) {
    //    CCLOG("Failed to find target position for teleport ID: %d", teleportID);
    //    return false;
    //}
    Vec2 localPosition = _character->getParent()->convertToNodeSpace(targetPosition);
    CCLOG("Character local position set to: (%f, %f)", localPosition.x, localPosition.y);
    // 更新 InteractionManager 的地图引用
    if (_interactionManager) {
        _interactionManager->setMap(_currentMap);
        CCLOG("InteractionManager map updated.");
    }

    // 更新视角控制器的地图引用
    if (_viewController) {
        _viewController->setMap(_currentMap);
        CCLOG("GameViewController map updated.");
    }

    return true;
}

Vec2 MapSwitchManager::getTargetPositionByID(int teleportID, GameMap* newMap) {
    //auto allTeleportTiles = newMap->getAllTeleportTiles();
    //for (const auto& tile : allTeleportTiles) {
    //    if (tile.properties["teleportID"].asInt() == teleportID) {
    //        return tile.position;
    //    }
    //}
    return Vec2(0,0);
}



