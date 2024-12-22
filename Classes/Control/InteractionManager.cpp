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

// 更新角色周围的瓦片信息
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

// 判断指定瓦片位置是否为不可通行区域
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

// 检查角色是否站在传送点上，并获取传送目标地图
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

// 改变地图
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

            tileInfo.drops["Grass"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::GRASS_DROP_PROBABILITY }; // 掉落1个草，概率为50%
        }
        else if (pathProps.find("isStone") != pathProps.end() && pathProps["isStone"].asBool()) {
            tileInfo.type = TileConstants::Stone;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["Stone"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::STONE_DROP_PROBABILITY }; // 掉落1个石头，概率为30%

        }
        // 对应树桩
        else if(pathProps.find("isWood") != pathProps.end() && pathProps["isWood"].asBool())
        {
            tileInfo.type = TileConstants::Wood;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["Timber"] = {TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::BRANCH_DROP_PROBABILITY}; // 掉落1个木材，概率为30%
        }
        // 对应树枝
        else if (pathProps.find("isBranch") != pathProps.end() && pathProps["isBranch"].asBool())
        {
            tileInfo.type = TileConstants::Branch;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["Timber"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::BRANCH_DROP_PROBABILITY }; // 掉落1个木材，概率为30%
        }
        else if(pathProps.find("isTree") != pathProps.end() && pathProps["isTree"].asBool())
        {
            tileInfo.type = TileConstants::Tree;
            tileInfo.drops.clear(); // 清空默认的 "None" 项
            tileInfo.drops["Timber"] = { TileConstants::MUTI_DROP_QUANTITY, TileConstants::TREE_DROP_PROBABILITY }; // 掉落3个木材，概率为90%
        }
    }

    // 判断water层
    int WaterGID = _gameMap->getTileGIDAt("Water", Tile_pos);

    if (WaterGID != 0) {
        tileInfo.type = TileConstants::Water;
    }
    // 判断矿洞地图的矿石类型以及掉落物
    if (_gameMap && _gameMap->getType() == MapType::Mine) {
        int MineGID = _gameMap->getTileGIDAt("ore", Tile_pos);
        GetMineInfo(MineGID, tileInfo);
    }

    // 判断农场地图特有属性
    if(_gameMap && _gameMap->getType() == MapType::Farm)
    {
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

        // 判断物品层
        int ObjectGID = _gameMap->getTileGIDAt("Object", Tile_pos);

        ValueMap ObjectProps = _gameMap->getTilePropertiesForGID(ObjectGID);

        if (ObjectProps.find("isBox") != ObjectProps.end() && ObjectProps["isBox"].asBool()) {
            tileInfo.type = TileConstants::Box;
        }

    }
    return tileInfo;
}

// 获取矿石信息
void InteractionManager::GetMineInfo(int MineGID,TileInfo& tileInfo) {
    ValueMap oreProps = _gameMap->getTilePropertiesForGID(MineGID);
    if (oreProps.find("isSteel") != oreProps.end() && oreProps["isSteel"].asBool())
    {
        tileInfo.type = TileConstants::Mine;//矿石
        tileInfo.drops.clear(); // 清空默认的 "None" 项
        tileInfo.drops["IronParticle"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::MINE_DROP_PROBABILITY }; // 掉落1个铁，概率为50%
        tileInfo.drops["Stone"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::STONE_DROP_MINE_PROBABILITY };// 掉落石头 概率10%
        }
    else if (oreProps.find("isCopper") != oreProps.end() && oreProps["isCopper"].asBool())
    {
        tileInfo.type = TileConstants::Mine;//矿石
        tileInfo.drops.clear(); // 清空默认的 "None" 项
        tileInfo.drops["CopperParticle"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::MINE_DROP_PROBABILITY }; // 掉落1个铜，概率为50%
        tileInfo.drops["Stone"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::STONE_DROP_MINE_PROBABILITY };// 掉落石头 概率10%
        }
    else if (oreProps.find("isTreasure") != oreProps.end() && oreProps["isTreasure"].asBool())
    {
        tileInfo.type = TileConstants::Treasure;
        tileInfo.drops.clear(); // 清空默认的 "None" 项
        tileInfo.drops["Ruby"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::TREATURE_PROBABILITY }; // 掉落1个红宝石，概率为100%
        }
    else if (oreProps.find("isRing") != oreProps.end() && oreProps["isRing"].asBool())
    {
        tileInfo.type = TileConstants::Treasure;
        tileInfo.drops.clear(); // 清空默认的 "None" 项
        tileInfo.drops["Ring"] = { TileConstants::DEFAULT_DROP_QUANTITY, TileConstants::TREATURE_PROBABILITY }; // 掉落1个戒指，概率为100%
        }

}

// 根据动作做出对应地块变化
void InteractionManager::ActionAnimation(GameCharacterAction action, const Vec2& TilePos) {
    TileInfo actionTileInfo = GetTileInfoAt(TilePos);
    switch (action) {
    case Plowing:
        _gameMap->replaceTileAt("farm", TilePos, TileConstants::DRY_FARM_TILE_GID);
        break;
    case Watering:
        _gameMap->replaceTileAt("watering", TilePos, TileConstants::WET_FARM_TILE_GID);
        WateringAt(TilePos);
        break;
    case Weeding:
        _gameMap->replaceTileAt("path", TilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playWeedingAnimation(_gameMap->tileToRelative(TilePos), _gameMap->getTiledMap());
        break;
    case Mining:
        MiningAt(TilePos);
        break;
    case Cutting:
        ChopTree(TilePos);
        break;
    case Placement:
    case Seeding:
        placeObjectAtTile(TilePos);
        break;
    case Fertilize:
        FertilizeAt(TilePos);
        break;
    case DestoryObject:
        // 可添加对应物品损坏的动画
        _gameMap->replaceTileAt("Object", TilePos, TileConstants::EMPTY_GID);
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
    treeSprite->waterCrop();
    if (treeSprite) {
        CCLOG("Tree found at (%f, %f). Chopping tree...", tilePos.x, tilePos.y);
        treeSprite->chopTree();
    }
    else {
        CCLOG("No tree found at tile position: (%f, %f)", tilePos.x, tilePos.y);
    }
}

// 放置物品函数
bool InteractionManager::placeObjectAtTile(const Vec2& tilePos) {
    const std::string currentObjectName = _currentObject.objectNode.object->_name;
    GameObjectMapType currentObjectType = _currentObject.objectNode.type;

    // 当前物品为种子
    if (currentObjectType == Seed) {

        // 检查当前地图是否为农场
        if (_gameMap->getType() == MapType::Farm) {
            FarmMap* farmMap = dynamic_cast<FarmMap*>(_gameMap);
            // 地图错误
            if(!farmMap) {
                CCLOG("Error: Failed to cast GameMap to FarmMap.");
                return false;
            }

            // 判断种子是否可以种植
            if (GAME_SEED_TO_CROP_MAP.find(currentObjectName) != GAME_SEED_TO_CROP_MAP.end()) {
                std::string cropName = GAME_SEED_TO_CROP_MAP.at(currentObjectName);

                // 判断目标瓦片是否为耕地
                TileInfo tileInfo = GetTileInfoAt(tilePos);
                farmMap->plantCrops(tilePos, cropName, _characterFarmLevel);
                CCLOG("Planted crop '%s' at tile (%f, %f)", cropName.c_str(), tilePos.x, tilePos.y);
                return true;
            }
            else {
                CCLOG("Error: Seed '%s' does not map to any crop.", currentObjectName.c_str());
                return false;
            }
        }
        else {
            CCLOG("Error: Seeds can only be planted on FarmMap.");
            return false;
        }
    }
    else // 其他放置物品
    {
        // 在对应映射表寻找放置物品的GID，替换对应图块
        auto it = TileConstants::objectGIDMap.find(currentObjectName);
        if (it != TileConstants::objectGIDMap.end()) {
            int targetGID = it->second;
            _gameMap->replaceTileAt("Object", tilePos, targetGID);
            CCLOG("Placed other object '%s' at (%f, %f) with GID=%d.", currentObjectName.c_str(), tilePos.x, tilePos.y, targetGID);
            return true;
        }
        else {
            CCLOG("Unknown object '%s' cannot be placed.", currentObjectName.c_str());
            return false;
        }
    }
    return false;
}

// 浇水效果
bool InteractionManager::WateringAt(const Vec2& tilePos) {
    if (!_gameMap) {
        CCLOG("InteractionManager: _gameMap is null.");
        return false;
    }

    // 使用多态调用 GameMap 的 getTreeAtPosition获取农作物指针
    auto cropSprite = _gameMap->getTreeAtPosition(tilePos);
    if(!cropSprite)
    {
        cropSprite->waterCrop();
        return true;
    }
    return false;
}

// 施肥效果
bool InteractionManager::FertilizeAt(const Vec2& tilePos) {
    if (!_gameMap) {
        CCLOG("InteractionManager: _gameMap is null.");
        return false;
    }

    // 使用多态调用 GameMap 的 getTreeAtPosition获取农作物指针
    auto cropSprite = _gameMap->getTreeAtPosition(tilePos);
    if (!cropSprite)
    {
        cropSprite->fertilize();
        return true;
    }
    return false;
}

bool InteractionManager::MiningAt(const Vec2& tilePos) {
    TileInfo tileinfo = GetTileInfoAt(tilePos);

    // 石头物品逻辑
    if (tileinfo.type == TileConstants::TileType::Stone) {
        _gameMap->replaceTileAt("path", tilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playStoneBreakingAnimation(_gameMap->tileToRelative(tilePos), _gameMap->getTiledMap());
        return true;
    }
    //  对应非石头
    else if(tileinfo.type == TileConstants::TileType::Mine|| tileinfo.type == TileConstants::TileType::Treasure)// 矿物
    {

        _gameMap->replaceTileAt("path", tilePos, TileConstants::EMPTY_GID);
        _gameMap->replaceTileAt("ore", tilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playStoneBreakingAnimation(_gameMap->tileToRelative(tilePos), _gameMap->getTiledMap());
        return true;

    }
    else
    {
        CCLOG("unkonw mine type");
        return false;
    }
}


// 对树干，树桩和树枝条的处理
bool InteractionManager::ChopTree(const Vec2& tilePos) {
    TileInfo tileinfo = GetTileInfoAt(tilePos);

    if(tileinfo.type == TileConstants::TileType::Tree)
    {
        // 砍树干对应动作
        _gameMap->replaceTileAt("path", tilePos, TileConstants::WOOD_GID); // 将类型改为树桩
        getTreeAndChopAt(tilePos);

        return true;
    }
    else if (tileinfo.type == TileConstants::TileType::Wood) 
    {
        //砍树状对应动作
        _gameMap->replaceTileAt("path", tilePos, TileConstants::EMPTY_GID);
        _gameMap->replaceTileAt("Tree", tilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playWoodCuttingAnimation(_gameMap->tileToRelative(tilePos), _gameMap->getTiledMap());
    }
    else if(tileinfo.type == TileConstants::TileType::Branch)
    {
        // 树枝对应动作
        _gameMap->replaceTileAt("path", tilePos, TileConstants::EMPTY_GID);
        AnimationHelper::playChopingBranchAnimation(_gameMap->tileToRelative(tilePos), _gameMap->getTiledMap());
    
        return true;
    }
    else {
        return false;
    }
}