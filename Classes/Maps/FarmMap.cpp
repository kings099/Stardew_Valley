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

bool FarmMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // Call the parent class' init function
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    this->setScale(FARM_MAP_SCALE);
    if (_tile_map != nullptr) {
        CCLOG("success: _tile_map is added");
        /*  return true;*/
    }
    //添加一个农作物树
    auto crop = Crop::create("grass", 0);
    if (crop == nullptr) {
        CCLOG("Error: Failed to create Crop instance");
        return false;
    }
    else {
        CCLOG("success: Crop instance created");
    }
    crop->setPosition(Vec2(200, 200));
    _tile_map->addChild(crop);

    _tile_map->schedule([crop](float dt) {
        crop->updateGrowth(dt);
        }, 1.0f, "growth_key");
    this->setScale(FARM_MAP_SCALE);

    _tile_map->scheduleOnce([crop](float) {
        crop->playWeedingAnimation();
        }, 10.0f, "play_animation_key");

    //监听鼠标
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseEvent, this);  // 监听鼠标点击事件

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 待定：添加农场地图独有的部分 例如事件监听器……

    return true;
}

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


        // 检查 `_tile_map` 是否有效
        if (_tile_map == nullptr) {
            CCLOG("Error: _tile_map is null.");
            return false;
        }
        // 检查是否点击到农作物
        for (auto child : _tile_map->getChildren()) {
            CCLOG("Child type: %s", typeid(*child).name());
            auto crop = dynamic_cast<Crop*>(child);
            if (crop == nullptr) {
                CCLOG("Child is not a Crop instance.");
                continue;
            }
            auto croptype = crop->getType();
            auto cropPos = crop->getPosition();
            CCLOG("Found Crop of type: %s at position: %f, %f", croptype.c_str(), cropPos.x, cropPos.y);
            if (crop && crop->getBoundingBox().containsPoint(mapPosition) && croptype == "grass") {
                CCLOG("Crop clicked at position: %f, %f", mapPosition.x, mapPosition.y);
                crop->playWeedingAnimation();
                return true;
            }
        }
        CCLOG("No crop clicked.");
        return true;
    }
    CCLOG("Event is not a mouse event.");
     
    return false;
}

