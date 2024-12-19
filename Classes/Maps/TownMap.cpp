/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TownMap.cpp
 * File Function: С���ͼTownMap���ʵ��
 * Author:        �����
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
    // ���ø���ĳ�ʼ������
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }

    this->setScale(TOWN_MAP_SCALE);
    if (_tile_map != nullptr) {
        CCLOG("�ɹ���_tile_map �����");
    }


    // ��������¼�
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(TownMap::onMouseEvent, this); // ����������¼�

    // ע�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ��ӳ����ͼ���еĲ��֣������¼���������

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
        int GID = getTileGIDAt("Buildings", tiledPos); // ���轨������ "Buildings" ͼ��
        CCLOG("����� GID:%d", GID);
        Vec2 worldpos = tileToAbsolute(tiledPos);
        CCLOG("WORLD POS: %f,%f", worldpos.x, worldpos.y);

        // ���� GID ִ����Ӧ���߼�������򿪽�������Ϣ
        if (GID != 0) { // 0 ͨ����ʾû��ͼ��
        }

        return true;
    }
    CCLOG("�¼���������¼���");
    return false;
}
