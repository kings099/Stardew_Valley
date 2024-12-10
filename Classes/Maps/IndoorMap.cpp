/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.cpp
 * File Function: 初始化室内地图
 * Author:        胡宝怡
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#include "IndoorMap.h"
USING_NS_CC;

IndoorMap::IndoorMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}


IndoorMap::~IndoorMap()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}

IndoorMap* IndoorMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    IndoorMap* ret = new IndoorMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool IndoorMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用父类的初始化方法
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    this->setScale(INDOOR_MAP_SCALE);


    //监听鼠标
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(IndoorMap::onMouseEvent, this);  // 监听鼠标点击事件

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool IndoorMap::onMouseEvent(cocos2d::Event* event)
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

        return true;
    }
    return false;
}


Vec2 IndoorMap::absoluteToTile(const Vec2& pixelPoint)
{
    // 获取瓦片的大小
    Size tileSize = _tile_map->getTileSize();


    float tileX = (pixelPoint.x - _map_position.x) / (tileSize.width * INDOOR_MAP_SCALE);
    float tileY = (pixelPoint.y - _map_position.y) / (tileSize.height * INDOOR_MAP_SCALE);
    // 瓦片地图y轴是从上到下的，需要翻转y轴
    tileY = _tile_map->getMapSize().height - tileY;
    return Vec2(floor(tileX), floor(tileY));
}

//获取某个图块的属性
cocos2d::ValueMap IndoorMap::getTilePropertiesForGID(int GID)
{
    if (GID == 0) return cocos2d::ValueMap();
    auto tileProperties = _tile_map->getPropertiesForGID(GID);
    if (tileProperties.getType() == Value::Type::MAP)
    {
        return tileProperties.asValueMap();
    }
    return cocos2d::ValueMap();
}
