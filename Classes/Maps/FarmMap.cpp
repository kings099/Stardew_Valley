/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 初始农场地图FarmMap类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#include "FarmMap.h"
#include "Classes/Crops/Crops.h"
#include "Classes/Animal/Animal.h"
#include "Classes/Animal/Fish.h"

USING_NS_CC;

FarmMap::FarmMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}

FarmMap::~FarmMap() {
    if (_treeLayer) {
        _treeLayer->removeAllChildren();
    }
    _eventDispatcher->removeEventListenersForTarget(this);
}

FarmMap* FarmMap::create(const std::string& mapFile, Node* TreeLayer, const Vec2& mapPosition)
{
    FarmMap* ret = new FarmMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition,TreeLayer)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

// 重写初始化函数
bool FarmMap::init(const std::string& mapFile, const Vec2& mapPosition, Node* TreeLayer)
{
   
    // Call the parent class' init function
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    this->setScale(FARM_MAP_SCALE);
    if (_tile_map != nullptr) {
        CCLOG("success: _tile_map is added");
       
    }
    _mapName = mapFile;
    //// 在场景初始化时设置季节
    Crops::setSeason(Season::Spring); // 设置当前季节为春季
    
    applySavedChanges();
    // 初始化小动物
    initializeAnimals();

    // 初始化鱼
    initializeFishes();

    Vec2 startPosition_3(464, 800);  // 例如设置小动物的原点为 (100, 100)
    Animal* cow = Animal::create("cow", startPosition_3);
    _tile_map->addChild(cow);

    // 添加树木层
    _treeLayer = TreeLayer;
    plantTreesOnPathLayer(); 
  
    //监听鼠标
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseEvent, this);  // 监听鼠标点击事件

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 待定：添加农场地图独有的部分 例如事件监听器……

    return true;
}

// 鼠标事件的处理
bool FarmMap::onMouseEvent(cocos2d::Event* event)
{
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        auto mousePos = mouseEvent->getLocationInView();
        auto defaultCamera = Camera::getDefaultCamera();
        auto cameraPosition = defaultCamera->getPosition();

        const auto visibleSize = Director::getInstance()->getVisibleSize();
        float cameraOffset_x = cameraPosition.x - visibleSize.width / 2;
        float cameraOffset_y = cameraPosition.y - visibleSize.height / 2;

        Vec2 mapPosition(mousePos.x + cameraOffset_x, mousePos.y + cameraOffset_y);
        Vec2 tiledPos = absoluteToTile(mapPosition);
        CCLOG("TILED POS: %f,%f", tiledPos.x, tiledPos.y);
        int GID = getTileGIDAt("Object", tiledPos);
        CCLOG("click GID:%d", GID);
        Vec2 worldpos = tileToAbsolute(tiledPos);
        CCLOG("WORLD POS: %f,%f", worldpos.x, worldpos.y);
        return true;

    }
    CCLOG("Event is not a mouse event.");
     
    return false;
}

TMXTiledMap* FarmMap::getTiledMap() const {
    return _tile_map;
}

void FarmMap::plantTreesOnPathLayer() {
    CCLOG("!!!!!!!!!!!!plantTreesOnPathLayer");
    // 获取 path 层
    TMXLayer* pathLayer = _tile_map->getLayer("path");
    if (!pathLayer) {
        CCLOG("Error: Path layer not found!");
        return;
    }
    // 遍历 path 层的所有瓦片
    const Size layerSize = pathLayer->getLayerSize();
    for (int row = 0; row < layerSize.height; ++row) {
        for (int col = 0; col < layerSize.width; ++col) {
            Vec2 tilePos(col, row); // 瓦片坐标
            int GID = pathLayer->getTileGIDAt(tilePos);
            // 检查 GID 是否为目标 GID
           /* TMXTiledMap* testmap = _tile_map;*/
            if (GID == TileConstants::OAK_GID || GID == TileConstants::OAK_INVISIBLE_GID) {
                // 创建并种植农作物
                auto crop = Crops::create("oak", OAK_MAX_GROWTHSTAGE);
                if (crop) {
                    _treeLayer->addChild(crop); // 添加到树木层
                    _treeLayer->setScale(FARM_MAP_SCALE);
                    crop->setPosition(tileToRelative(Vec2(col,row))); // 设置位置为瓦片的世界坐标
                    crop->setGrowthStage(OAK_MAX_GROWTHSTAGE); // 直接设置为成熟阶
                    replaceTileAt("path", Vec2(col, row), TileConstants::OAK_INVISIBLE_GID);
                    replaceTileAt("Tree", Vec2(col, row), TileConstants::OAK_ROOT_GID);
                }
                else {
                    CCLOG("Error: Failed to create crop of type oak");
                }
            }
            else if (GID == TileConstants::MAMPLE_GID || GID == TileConstants::MAMPLE_INVISIBLE_GID) {

                // 创建并种植农作物
                auto crop = Crops::create("maple",MAPLE_MAX_GROWTHSTAGE);
                if (crop) {
                    _treeLayer->addChild(crop); // 添加到树木层
                    _treeLayer->setScale(FARM_MAP_SCALE);
                    crop->setPosition(tileToRelative(Vec2(col, row))); // 设置位置为瓦片的世界坐标
                    crop->setGrowthStage(MAPLE_MAX_GROWTHSTAGE); // 直接设置为成熟阶
                    replaceTileAt("path", Vec2(col, row), TileConstants::MAMPLE_INVISIBLE_GID);
                    replaceTileAt("Tree", Vec2(col, row), TileConstants::MAMPLE_ROOT_GID);
                }
                else {
                    CCLOG("Error: Failed to create crop of type maple");
                }

            }
            else if (GID == TileConstants::PINE_GID|| GID==TileConstants::PINE_INVISIBLE_GID) {
                // 创建并种植农作物
                auto crop = Crops::create("pine",PINE_MAX_GROWTHSTAGE);
                if (crop) {
                    _treeLayer->addChild(crop); // 添加到树木层
                    _treeLayer->setScale(FARM_MAP_SCALE);
                    crop->setPosition(tileToRelative(Vec2(col, row))); // 设置位置为瓦片的世界坐标
                    crop->setGrowthStage(PINE_MAX_GROWTHSTAGE); // 直接设置为成熟阶
                    replaceTileAt("path", Vec2(col, row), TileConstants::PINE_INVISIBLE_GID);// 设置树木标志为不可见
                    replaceTileAt("Tree", Vec2(col, row), TileConstants::PINE_ROOT_GID);// 设置树根图块
                }
                else {
                    CCLOG("Error: Failed to create crop of type pine");
                }

            }
        }
    }
}

void FarmMap::initializeAnimals() {
    CCLOG("Initializing animals...");

    Vec2 startPosition_1(416, 832); //羊
    Animal* sheep = Animal::create("sheep", startPosition_1);
    if (sheep) {
        _tile_map->addChild(sheep,10);
        CCLOG("Sheep added successfully!");
    }
    else {
        CCLOG("Error: Failed to create sheep!");
    }

    Vec2 startPosition_2(480, 816); //鸡
    Animal* chicken = Animal::create("chicken", startPosition_2);
    if (chicken) {
        _tile_map->addChild(chicken,10);
        CCLOG("Chicken added successfully!");
    }
    else {
        CCLOG("Error: Failed to create chicken!");
    }

    Vec2 startPosition_3(464, 800); //牛
    Animal* cow = Animal::create("cow", startPosition_3);
    if (cow) {
        _tile_map->addChild(cow,10);
        CCLOG("Cow added successfully!");
    }
    else {
        CCLOG("Error: Failed to create cow!");
    }
}

void FarmMap::initializeFishes() {
    CCLOG("Initializing fishes...");

    Vec2 Position_1(816, 512);
    Fishs* Bigeye = Fishs::create("Bigeye", "spring", Position_1);
    if (Bigeye) {
        _tile_map->addChild(Bigeye, 10);  // 设置 z-order 确保在前景中
        CCLOG("Fish 0 added successfully!");
    }
    else {
        CCLOG("Error: Failed to create fish_0!");
    }

    Vec2 Position_2(720, 512);
    Fishs* LargemouthBass = Fishs::create("LargemouthBass", "spring", Position_2);
    if (LargemouthBass) {
        _tile_map->addChild(LargemouthBass, 10);
        CCLOG("Fish 1 added successfully!");
    }
    else {
        CCLOG("Error: Failed to create fish_1!");
    }

    Vec2 Position_3(880, 512);
    Fishs* Salmon = Fishs::create("Salmon", "spring", Position_3);
    if (Salmon) {
        _tile_map->addChild(Salmon, 10);
        CCLOG("Fish 2 added successfully!");
    }
    else {
        CCLOG("Error: Failed to create fish_2!");
    }
}

// 获取某个位置的农作物指针
Crops* FarmMap::getTreeAtPosition(const Vec2& tilePos) {
    if (!_treeLayer) {
        CCLOG("Tree layer not initialized!");
        return nullptr;
    }

    // 将瓦片坐标转换为相对地图的绝对坐标
    Vec2 treeWorldPos = tileToRelative(tilePos);

    // 遍历树木层的所有子节点
    for (auto child : _treeLayer->getChildren()) {
        auto sprite = dynamic_cast<Crops*>(child);
        if (sprite) {
            // 获取精灵的世界坐标
            Vec2 spriteWorldPos = sprite->getPosition();
            // 如果坐标相等，返回指针
            if (spriteWorldPos.equals(treeWorldPos)) {
                return sprite;
            }
        }
    }

    CCLOG("No tree found at tile position: (%f, %f)", tilePos.x, tilePos.y);
    return nullptr; // 未找到匹配的树精灵
}

void FarmMap::plantCrops(const Vec2& tilePos, const std::string cropName,const int characterLevel) {

    // 设置玩家等级
    Crops::setPlayerLevel(characterLevel);

    int maxstage = KALE_MAX_GROWTHSTAGE;
    if (cropName == "pumpkin")
        maxstage = PUMPKIN_MAX_GROWTHSTAGE;
    // 添加指定农作物
    auto crop = Crops::create(cropName, maxstage);
    _tile_map->addChild(crop,ANIMATION_LAYER_GRADE);

    // 设置位置
    crop->setPosition(tileToRelative(tilePos));
    crop->setGrowthStage(MIN_GROWTHSTAGE);
}