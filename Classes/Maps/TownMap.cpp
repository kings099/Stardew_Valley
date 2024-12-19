/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TownMap.cpp
 * File Function: 小镇地图TownMap类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/
#include "TownMap.h"
USING_NS_CC;

TownMap::TownMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}

TownMap::~TownMap() {}

TownMap* TownMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    TownMap* ret = new TownMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool TownMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用父类的初始化函数
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }

    this->setScale(TOWN_MAP_SCALE);
    if (_tile_map != nullptr) {
        CCLOG("成功：_tile_map 已添加");
    }


    // 监听鼠标事件
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(TownMap::onMouseEvent, this); // 监听鼠标点击事件

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 添加城镇地图独有的部分，例如事件监听器等

    return true;
}

TMXTiledMap* TownMap::getTiledMap() const {
    return _tile_map;
}

bool TownMap::onMouseEvent(Event* event)
{
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
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
        int GID = getTileGIDAt("Buildings", tiledPos); // 假设建筑物在 "Buildings" 图层
        CCLOG("点击的 GID:%d", GID);
        Vec2 worldpos = tileToAbsolute(tiledPos);
        CCLOG("WORLD POS: %f,%f", worldpos.x, worldpos.y);

        // 根据 GID 执行相应的逻辑，例如打开建筑物信息
        if (GID != 0) { // 0 通常表示没有图块
        }

        return true;
    }
    CCLOG("事件不是鼠标事件。");
    return false;
}
