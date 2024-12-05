/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��ʼũ����ͼFarmMap���ʵ��
 * Author:        �����
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
    // ���ø���ĳ�ʼ������
    if (!Node::init()) {
        return false;
    }

    // ������Ƭ��ͼ
    _tileMap = TMXTiledMap::create(mapFile);
    if (!_tileMap) {
        CCLOG("Failed to load map");
        return false;
    }

    // ��ӵ�ͼ����ǰ�ڵ�
    this->addChild(_tileMap, 0);
    this->setPosition(_mapPosition);
    this->setScale(MAP_SCALE);

    //�������
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseEvent, this);  // ����������¼�

    // ע�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool FarmMap::onMouseEvent(cocos2d::Event* event)
{
    // ��ȡ����¼�
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ������Ļλ��
        auto mousePos = mouseEvent->getLocationInView();
        // ��ȡĬ�����������������ƫ��
        auto defaultCamera = Camera::getDefaultCamera();
        auto cameraPosition = defaultCamera->getPosition();

        // ���ӷ�Χ
        const auto visibleSize = Director::getInstance()->getVisibleSize();

        float cameraOffset_x = cameraPosition.x - visibleSize.width / 2;
        float cameraOffset_y = cameraPosition.y - visibleSize.height / 2;

        // ����Ļ��������Ϊ����ڵ�ͼ�ľ�������
        Vec2 mapPosition(mousePos.x + cameraOffset_x - _mapPosition.x,
            mousePos.y + cameraOffset_y - _mapPosition.y);

        CCLOG("mapPosition:%f,%f", mapPosition.x, mapPosition.y);
        // ת��Ϊ��Ƭ����
        Vec2 tiledPos = absoluteToTile(mapPosition);
        CCLOG("tilePos:%f,%f", tiledPos.x, tiledPos.y);
        auto layer = _tileMap->getLayer("Back"); // ȷ���滻Ϊ��ʵ�ʵ�ͼ������
        int tileGID = layer->getTileGIDAt(tiledPos);

        CCLOG("GID: % d", tileGID);
        // ��ӡ���λ��
        //if (tileGID == 1247) {
        //    CCLOG("WATER!!!!!!!!!!");
        //}
        //else
        //{
        //    CCLOG("SOIL!!!!!!!!!");
        //}

        // ���� true ��ʾ�¼��Ѵ���
        return true;
    }

    return false;
}


Vec2 FarmMap::absoluteToTile(const Vec2& pixelPoint)
{
    // ��ȡ��Ƭ�Ĵ�С
    Size tileSize = _tileMap->getTileSize();

    float tileX = (pixelPoint.x) / (tileSize.width * MAP_SCALE);
    float tileY = (pixelPoint.y) / (tileSize.height * MAP_SCALE);
    CCLOG("mapheight:%f", _tileMap->getMapSize().height);
    CCLOG("tileY:%f", tileY);
    // ��Ƭ��ͼy���Ǵ��ϵ��µģ���Ҫ��תy��
    tileY = _tileMap->getMapSize().height - tileY; 

    return Vec2(floor(tileX), floor(tileY));
}

const Size& FarmMap:: getMapSize()const {
    Size map_size_in_tiles = _tileMap->getMapSize();
    // ��ȡÿ����Ƭ�Ĵ�С
    Size tile_size = _tileMap->getTileSize();  // ��ȡÿ����Ƭ�����ش�С

    // ����Ƭ��ת��Ϊ������
    float map_width_in_pixels = map_size_in_tiles.width * tile_size.width;
    float map_heightin_Pixels = map_size_in_tiles.height * tile_size.height;
    return Size(map_width_in_pixels, map_heightin_Pixels);
}