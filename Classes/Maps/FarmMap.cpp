/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 初始农场地图FarmMap类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/2
 * License:       MIT License
 ****************************************************************/

#include "FarmMap.h"
USING_NS_CC;

FarmMap::FarmMap()
    : _tileMap(nullptr)
{
}

FarmMap::~FarmMap()
{
}

FarmMap* FarmMap::create(const std::string& mapFile)
{
    FarmMap* ret = new FarmMap();
    if (ret && ret->init(mapFile)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool FarmMap::init(const std::string& mapFile)
{
    // 调用父类的初始化方法
    if (!Node::init()) {
        return false;
    }

    // 加载瓦片地图
    _tileMap = TMXTiledMap::create(mapFile);
    if (!_tileMap) {
        CCLOG("Failed to load map");
        return false;
    }

    // 添加地图到当前节点
    this->addChild(_tileMap, 0);
    //监听鼠标
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseEvent, this);  // 监听鼠标点击事件

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void FarmMap::updateMapPosition(const Vec2& characterPosition)
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    // 计算地图应移动的位置
    Vec2 mapPosition = Vec2(characterPosition.x - visibleSize.width / 2,
        characterPosition.y - visibleSize.height / 2);

    // 限制地图的移动范围
    auto mapSize = _tileMap->getMapSize();
    auto tileSize = _tileMap->getTileSize();
    float maxX = (mapSize.width * tileSize.width) - visibleSize.width;
    float maxY = (mapSize.height * tileSize.height) - visibleSize.height;

    // 确保地图位置不超出边界
    mapPosition.x = std::max(0.0f, std::min(mapPosition.x, maxX));
    mapPosition.y = std::max(0.0f, std::min(mapPosition.y, maxY));

    // 更新地图的位置
    _tileMap->setPosition(mapPosition);
}

bool FarmMap::onMouseEvent(cocos2d::Event* event)
{
    // 获取鼠标事件
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标点击的位置
        auto mousePosition = mouseEvent->getLocation();

        // 获取当前地图的坐标位置
        auto mapPosition = _tileMap->convertToNodeSpace(mousePosition);

        // 打印点击位置
        CCLOG("Mouse clicked at screen position: (%.2f, %.2f)", mousePosition.x, mousePosition.y);
        CCLOG("Map position: (%.2f, %.2f)", mapPosition.x, mapPosition.y);

        // 返回 true 表示事件已处理
        return true;
    }

    return false;
}