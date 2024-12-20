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
#include "Classes/Animation/Animation.h"

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

    _surroundingTiles.clear(); // 清除周围砖块
    Vec2 tile_pos = _gameMap->absoluteToTile(world_pos);

    // 周围九格地块信息
    std::vector<Vec2> surroundingCoords = {
        Vec2(tile_pos.x - 1, tile_pos.y - 1), Vec2(tile_pos.x, tile_pos.y - 1), Vec2(tile_pos.x + 1, tile_pos.y - 1),
        Vec2(tile_pos.x - 1, tile_pos.y),     Vec2(tile_pos.x, tile_pos.y),     Vec2(tile_pos.x + 1, tile_pos.y),
        Vec2(tile_pos.x - 1, tile_pos.y + 1), Vec2(tile_pos.x, tile_pos.y + 1), Vec2(tile_pos.x + 1, tile_pos.y + 1),
    };
    for (const auto& coord : surroundingCoords) {
        TileInfo tileInfo = GetTileInfoAt(coord);
        _surroundingTiles.push_back(tileInfo); //  更新 _surroundingTiles
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
    int GIDCollidable = _gameMap->getTileGIDAt("Collidable", tilePos);
    if (GIDCollidable != 0)
        return true;// 对应碰撞体积层有标注情况，直接返回True
    //对应碰撞层无标注情况，判断是否有物品
    int GIDPath = _gameMap->getTileGIDAt("path", tilePos);
    int GIDHouse = _gameMap->getTileGIDAt("house", tilePos);
    ValueMap path_properties = _gameMap->getTilePropertiesForGID(GIDPath);
    ValueMap house_properties = _gameMap->getTilePropertiesForGID(GIDHouse);
    if (!path_properties.empty()||!house_properties.empty()) {
        if (path_properties.find("canNotMove") != path_properties.end()) {
            return path_properties["canNotMove"].asBool();
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
            return true;  // 触发传送逻辑
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

// 在指定瓦片位置获取图块信息
const TileInfo InteractionManager::GetTileInfoAt(const Vec2& Tile_pos) {
    TileInfo tileInfo;
    tileInfo.tilePos = Tile_pos;
    tileInfo.WorldPos = _gameMap->tileToAbsolute(Tile_pos);
    tileInfo.type = TileConstants::Other; // 默认类型
    tileInfo.isObstacle = isCollidableAtPos(Tile_pos);


    // 初始化默认掉落物品信息
    tileInfo.drops["None"] = { 0, 0.0f }; // 默认无物品掉落

    // 判断path层
    int pathGID = _gameMap->getTileGIDAt("path", Tile_pos);
    if (pathGID != 0) {
        ValueMap pathProps = _gameMap->getTilePropertiesForGID(pathGID);
        if (pathProps.find("isGrass") != pathProps.end() && pathProps["isGrass"].asBool()) {
            tileInfo.type = TileConstants::Grass; // 这个位置如果用草会报错 初步怀疑是编码的问题
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            // 这个位置如果用草会报错 初步怀疑是编码的问题
            tileInfo.drops["Grass"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::GRASS_DROP_PROBABILITY }; // 掉落1个草，概率为50%
        }
        else if (pathProps.find("isStone") != pathProps.end() && pathProps["isStone"].asBool()) {
            tileInfo.type = TileConstants::Stone;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["石头"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::STONE_DROP_PROBABILITY }; // 掉落1个石头，概率为30%
        }
        // 对应树枝和树桩
        else if(pathProps.find("isWood") != pathProps.end() && pathProps["isWood"].asBool())
        {
            tileInfo.type = TileConstants::Wood;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["木材"] = {TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::BRANCH_DROP_PROBABILITY}; // 掉落1个木材，概率为30%
        }
        else if(pathProps.find("isTree") != pathProps.end() && pathProps["isTree"].asBool())
        {
            tileInfo.type = TileConstants::Tree;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["木材"] = { TileConstants::MUTI_DROP_QUANTITY, TileConstants::TREE_DROP_PROBABILITY }; // 掉落3个木材，概率为90%
        }
    }

    // 判断water层
    int WaterGID = _gameMap->getTileGIDAt("Water", Tile_pos);
    if (WaterGID != 0) {
        tileInfo.type = TileConstants::Water;
    }
    // 判断是否为耕地
    int backGID = _gameMap->getTileGIDAt("back", Tile_pos);
    int buildingGID = _gameMap->getTileGIDAt("buildings", Tile_pos);
    int FarmGID = _gameMap->getTileGIDAt("farm", Tile_pos);
    if (backGID != 0 && buildingGID == 0 && pathGID == 0) {
        ValueMap backProps = _gameMap->getTilePropertiesForGID(backGID);
        if (backProps.find("canFarm") != backProps.end() && backProps["canFarm"].asBool()) {
            tileInfo.type = TileConstants::Soil;
        }
    }
    // 判断是否为耕种过土地
    if (FarmGID == TileConstants::DRY_FARM_TILE_GID) {
        tileInfo.type = TileConstants::Soiled;
    }
    return tileInfo;
}

// 根据动作做出对应地块变化
void InteractionManager::ActionAnimation(GameCharacterAction action, const Vec2& TilePos) {
    TileInfo actionTileInfo = GetTileInfoAt(TilePos);
    switch (action) {
    case Plowing:
        _gameMap->replaceTileAt("farm", TilePos, TileConstants::DRY_FARM_TILE_GID);
        break;
    case Watering:
        _gameMap->replaceTileAt("farm", TilePos, TileConstants::DRY_FARM_TILE_GID);
        break;
    case Weeding:
        _gameMap->replaceTileAt("path", TilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playWeedingAnimation(_gameMap->tileToRelative(TilePos), _gameMap->getTiledMap());
        break;
    case Mining:
        _gameMap->replaceTileAt("path", TilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playStoneBreakingAnimation(_gameMap->tileToRelative(TilePos), _gameMap->getTiledMap());      
        break;
    case Cutting:
        _gameMap->replaceTileAt("path", TilePos, TileConstants::WOOD_GID); // 将类型改为树桩
        getTreeAndChopAt(TilePos);
        break;
    case Placement:
        // TODO : 种子放置和砍树
        break;
    }
    // 输出掉落物的调试信息
    for (const auto& dropPair : actionTileInfo.drops) {
        const std::string& name = dropPair.first;       // 物品名称
        const auto& dropInfo = dropPair.second;         // 对应的掉落信息
        int quantity = dropInfo.first;                 // 数量
        float probability = dropInfo.second;           // 概率

        CCLOG("Item: %s, Quantity: %d, Probability: %.2f", name.c_str(), quantity, probability);
    }
}

// 在WorldPos的dir方向第n格获取地块信息
const TileInfo InteractionManager::GetLineTileInfo(Direction dir, int distance, const Vec2& WroldPos) {
    int x_offset = 0, y_offset = 0; // 横纵坐标瓦片偏移量
    Vec2 Tile_pos = _gameMap->absoluteToTile(WroldPos);
    switch (dir)
    {
        case Up:
            y_offset = -1;
            break;
        case Down:
            y_offset = 1;
            break;
        case Left:
            x_offset = -1;
            break;
        case Right:
            x_offset = 1;
            break;
        default:
            break;
    }
    Vec2 pos = Vec2(Tile_pos.x + x_offset * distance, Tile_pos.y + y_offset * distance);
    TileInfo tileinfo = GetTileInfoAt(pos);
    return tileinfo;
}

// 某个位置播放砍树动画（要求地图是Farmmap类）
void InteractionManager::getTreeAndChopAt(const Vec2& tilePos) {
    if (!_gameMap) {
        CCLOG("InteractionManager: _gameMap is null.");
        return;
    }

    // 使用多态调用 GameMap 的 getTreeAtPosition
    auto treeSprite = _gameMap->getTreeAtPosition(tilePos);
    if (treeSprite) {
        CCLOG("Tree found at (%f, %f). Chopping tree...", tilePos.x, tilePos.y);
        treeSprite->chopTree();
    }
    else {
        CCLOG("No tree found at tile position: (%f, %f)", tilePos.x, tilePos.y);
    }
}