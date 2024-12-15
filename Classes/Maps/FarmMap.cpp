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
USING_NS_CC;

FarmMap::FarmMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}

FarmMap::~FarmMap() {}

FarmMap* FarmMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    FarmMap* ret = new FarmMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

// 重写初始化函数
bool FarmMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
   
    // Call the parent class' init function
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    this->setScale(FARM_MAP_SCALE);
    if (_tile_map != nullptr) {
        CCLOG("success: _tile_map is added");
       
    }
    //// 在场景初始化时设置季节
    Crops::setSeason(Season::Spring); // 设置当前季节为春季
    // 在 path 层种植橡树，枫树，松树
    plantTreesOnPathLayer(5);
    
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
        int GID = getTileGIDAt("path", tiledPos);
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

void FarmMap::plantTreesOnPathLayer(int maxGrowthStage) {
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
            if (GID == OAK_GID) {
                // 创建并种植农作物
                auto crop = Crops::create("oak", maxGrowthStage);
                if (crop) {
                    _tile_map->addChild(crop,10);       // 添加到当前节点
                    crop->setPosition(tileToRelative(Vec2(col,row))); // 设置位置为瓦片的世界坐标
                    crop->setGrowthStage(maxGrowthStage); // 直接设置为成熟阶
                    replaceTileAt("path", Vec2(col, row), OAK_INVISIBLE_GID);
                }
                else {
                    CCLOG("Error: Failed to create crop of type oak");
                }
            }
            else if (GID == MAMPLE_GID) {

                // 创建并种植农作物
                auto crop = Crops::create("maple", maxGrowthStage);
                if (crop) {
                    _tile_map->addChild(crop, 10);       // 添加到当前节点
                    crop->setPosition(tileToRelative(Vec2(col, row))); // 设置位置为瓦片的世界坐标
                    crop->setGrowthStage(maxGrowthStage); // 直接设置为成熟阶
                    replaceTileAt("path", Vec2(col, row), MAMPLE_INVISIBLE_GID);
                }
                else {
                    CCLOG("Error: Failed to create crop of type maple");
                }

            }
            else if (GID == PINE_GID) {
                // 创建并种植农作物
                auto crop = Crops::create("pine", maxGrowthStage);
                if (crop) {
                    _tile_map->addChild(crop, 10);       // 添加到当前节点
                    crop->setPosition(tileToRelative(Vec2(col, row))); // 设置位置为瓦片的世界坐标
                    crop->setGrowthStage(maxGrowthStage); // 直接设置为成熟阶
                    replaceTileAt("path", Vec2(col, row), PINE_INVISIBLE_GID);
                }
                else {
                    CCLOG("Error: Failed to create crop of type pine");
                }

            }
        }
    }
}

