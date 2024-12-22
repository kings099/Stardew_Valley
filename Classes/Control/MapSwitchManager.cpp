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

bool MapSwitchManager::switchMap(const std::string& newMapFile, Vec2& teleportPOS, Node* TreeLayer,Node* MapLayer) {
    CCLOG("Switching map to: %s", newMapFile.c_str());

    // 清理灯光效果（RAII 会自动销毁旧灯光）
    _lightingGuard.reset();

    if (_currentMap) {
        // 保存当前地图状态
        _currentMap->saveChangesToStateManager();
        MapLayer->removeChild(_currentMap, true); // 清理旧地图
    }
    

    GameMap* newMap = nullptr;

    if (newMapFile.find("Combat") != std::string::npos) {
        newMap = FarmMap::create(newMapFile,TreeLayer);
    }
    else if (newMapFile.find("house") != std::string::npos) {
        newMap = IndoorMap::create(newMapFile, Vec2(FARM_HOUSE_CREAT_X, FARM_HOUSE_CREAT_Y));
        teleportPOS = newMap->tileToAbsolute(Vec2(FARM_HOUSE_TELE_X, FARM_HOUSE_TELE_Y));
    }
    else if (newMapFile.find("Town") != std::string::npos) {
        newMap = TownMap::create(newMapFile,Vec2(TOWN_CREAT_X, TOWN_CREAT_Y));
        teleportPOS = newMap->tileToAbsolute(Vec2(TOWN_TELE_X, TOWN_TELE_Y));
    }
    else if (newMapFile.find("Mine") != std::string::npos) {
        newMap = MineMap::create(newMapFile, Vec2(MINE_CREAT_X, MINE_CREAT_Y));
        teleportPOS = newMap->tileToAbsolute(Vec2(MINE_TELE_X, MINE_TELE_Y));
        if (newMap) {
            // 为矿洞地图添加灯光效果
            _lightingGuard = std::make_unique<IndoorLighting>(newMap);
        }
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
    _currentMap->applySavedChanges();
    MapLayer->addChild(_currentMap,MAP_LAYER_GRADE);

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




