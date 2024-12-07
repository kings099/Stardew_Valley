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
    : _tile_map(nullptr),_map_position(mapPosition)
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
    _tile_map = TMXTiledMap::create(mapFile);
    if (!_tile_map) {
        CCLOG("Failed to load map");
        return false;
    }

    // 添加地图到当前节点
    this->addChild(_tile_map, 0);
    this->setPosition(_map_position);
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
        Vec2 mapPosition(mousePos.x + cameraOffset_x ,
            mousePos.y + cameraOffset_y );
        // 转换为瓦片坐标
        Vec2 tiledPos = absoluteToTile(mapPosition);

        // 返回 true 表示事件已处理
        return true;
    }

    return false;
}


Vec2 FarmMap::absoluteToTile(const Vec2& pixelPoint)
{
    // 获取瓦片的大小
    Size tileSize = _tile_map->getTileSize();


    float tileX = (pixelPoint.x - _map_position.x) / (tileSize.width * MAP_SCALE);
    float tileY = (pixelPoint.y - _map_position.y) / (tileSize.height * MAP_SCALE);
    // 瓦片地图y轴是从上到下的，需要翻转y轴
    tileY = _tile_map->getMapSize().height - tileY; 
    return Vec2(floor(tileX), floor(tileY));
}

const Size& FarmMap:: getMapSize()const {
    Size map_size_in_tiles = _tile_map->getMapSize();
    // 获取每个瓦片的大小
    Size tile_size = _tile_map->getTileSize();  // 获取每个瓦片的像素大小

    // 将瓦片数转换为像素数
    float map_width_in_pixels = map_size_in_tiles.width * tile_size.width;
    float map_heightin_Pixels = map_size_in_tiles.height * tile_size.height;
    return Size(map_width_in_pixels, map_heightin_Pixels);
}

const Size& FarmMap::getMapSizeinTile() {
    return _tile_map->getMapSize();
}
int FarmMap::getTileGIDAt(const std::string& layerName, const Vec2& tileCoord)
{
    auto layer = _tile_map->getLayer(layerName);
    if (!layer) {
        CCLOG("invalied Layername");
        return 0;
    }
    // 获取地图尺寸
    auto map_size = _tile_map->getMapSize(); // 地图的行列数（瓦片数量）
    auto tile_size = _tile_map->getTileSize(); // 单个瓦片的像素尺寸

    // 检查 tileCoord 是否在地图的范围内
    if (tileCoord.x < 0 || tileCoord.y < 0 ||
        tileCoord.x >= map_size.width || tileCoord.y >= map_size.height)
    {
        return 0; // 坐标超出范围，返回 GID 为 0
    }

    // 如果坐标合法，获取对应的瓦片 GID
    return layer->getTileGIDAt(tileCoord);
}

ValueMap FarmMap::getTilePropertiesForGID(int GID)
{
    if (GID == 0) return ValueMap();
    auto tileProperties = _tile_map->getPropertiesForGID(GID);
    if (tileProperties.getType() == Value::Type::MAP)
    {
        return tileProperties.asValueMap();
    }
    return ValueMap();
}
