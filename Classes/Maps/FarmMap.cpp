/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 初始农场地图FarmMap类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#include "FarmMap.h"
USING_NS_CC;

FarmMap::FarmMap(const Vec2& mapPosition)
    : _tileMap(nullptr),_mapPosition(mapPosition)
{
}

FarmMap::~FarmMap()
{
}

FarmMap* FarmMap::create(const std::string& mapFile,const Vec2& mapPosition)
{
    FarmMap* ret = new FarmMap(mapPosition);
    if (ret && ret->init(mapFile,mapPosition)) {
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
    this->setPosition(_mapPosition);
    this->setScale(MAP_SCALE);

    //监听鼠标
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseEvent, this);  // 监听鼠标点击事件

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool FarmMap::onMouseEvent(cocos2d::Event* event)
{
    // 获取鼠标事件
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标的屏幕位置
        auto mousePos = mouseEvent->getLocationInView();
        // 获取默认摄像机的世界坐标偏移
        auto defaultCamera = Camera::getDefaultCamera();
        auto cameraPosition = defaultCamera->getPosition();

        // 可视范围
        const auto visibleSize = Director::getInstance()->getVisibleSize();

        float cameraOffset_x = cameraPosition.x - visibleSize.width / 2;
        float cameraOffset_y = cameraPosition.y - visibleSize.height / 2;

        // 将屏幕坐标修正为相对于地图的绝对坐标
        Vec2 mapPosition(mousePos.x + cameraOffset_x - _mapPosition.x,
            mousePos.y + cameraOffset_y - _mapPosition.y);
        // 转换为瓦片坐标
        Vec2 tiledPos = absoluteToTile(mapPosition);
        CCLOG("tilePos:%f,%f", tiledPos.x, tiledPos.y);
        auto layer = _tileMap->getLayer("Back"); // 确保替换为你实际的图层名称
        int tileGID = layer->getTileGIDAt(tiledPos);

        CCLOG("GID: % d", tileGID);
         //打印点击位置
        if (tileGID == 1247) {
            CCLOG("WATER!!!!!!!!!!");
        }
        else
        {
            CCLOG("SOIL!!!!!!!!!");
        }

        // 返回 true 表示事件已处理
        return true;
    }

    return false;
}


Vec2 FarmMap::absoluteToTile(const Vec2& pixelPoint)
{
    // 获取瓦片的大小
    Size tileSize = _tileMap->getTileSize();

    float tileX = (pixelPoint.x) / (tileSize.width * MAP_SCALE);
    float tileY = (pixelPoint.y) / (tileSize.height * MAP_SCALE);
    // 瓦片地图y轴是从上到下的，需要翻转y轴
    tileY = _tileMap->getMapSize().height - tileY; 

    return Vec2(floor(tileX), floor(tileY));
}

const Size& FarmMap:: getMapSize()const {
    Size map_size_in_tiles = _tileMap->getMapSize();
    // 获取每个瓦片的大小
    Size tile_size = _tileMap->getTileSize();  // 获取每个瓦片的像素大小

    // 将瓦片数转换为像素数
    float map_width_in_pixels = map_size_in_tiles.width * tile_size.width;
    float map_heightin_Pixels = map_size_in_tiles.height * tile_size.height;
    return Size(map_width_in_pixels, map_heightin_Pixels);
}