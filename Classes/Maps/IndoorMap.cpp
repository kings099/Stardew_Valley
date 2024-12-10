/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.cpp
 * File Function: ��ʼ�����ڵ�ͼ
 * Author:        ������
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
    // ���ø���ĳ�ʼ������
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    this->setScale(INDOOR_MAP_SCALE);


    //�������
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(IndoorMap::onMouseEvent, this);  // ����������¼�

    // ע�������
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
    // ��ȡ��Ƭ�Ĵ�С
    Size tileSize = _tile_map->getTileSize();


    float tileX = (pixelPoint.x - _map_position.x) / (tileSize.width * INDOOR_MAP_SCALE);
    float tileY = (pixelPoint.y - _map_position.y) / (tileSize.height * INDOOR_MAP_SCALE);
    // ��Ƭ��ͼy���Ǵ��ϵ��µģ���Ҫ��תy��
    tileY = _tile_map->getMapSize().height - tileY;
    return Vec2(floor(tileX), floor(tileY));
}

//��ȡĳ��ͼ�������
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
