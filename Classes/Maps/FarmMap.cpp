/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��ʼũ����ͼFarmMap���ʵ��
 * Author:        �����
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
    //�������
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseEvent, this);  // ����������¼�

    // ע�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void FarmMap::updateMapPosition(const Vec2& characterPosition)
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    // �����ͼӦ�ƶ���λ��
    Vec2 mapPosition = Vec2(characterPosition.x - visibleSize.width / 2,
        characterPosition.y - visibleSize.height / 2);

    // ���Ƶ�ͼ���ƶ���Χ
    auto mapSize = _tileMap->getMapSize();
    auto tileSize = _tileMap->getTileSize();
    float maxX = (mapSize.width * tileSize.width) - visibleSize.width;
    float maxY = (mapSize.height * tileSize.height) - visibleSize.height;

    // ȷ����ͼλ�ò������߽�
    mapPosition.x = std::max(0.0f, std::min(mapPosition.x, maxX));
    mapPosition.y = std::max(0.0f, std::min(mapPosition.y, maxY));

    // ���µ�ͼ��λ��
    _tileMap->setPosition(mapPosition);
}

bool FarmMap::onMouseEvent(cocos2d::Event* event)
{
    // ��ȡ����¼�
    auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ�������λ��
        auto mousePosition = mouseEvent->getLocation();

        // ��ȡ��ǰ��ͼ������λ��
        auto mapPosition = _tileMap->convertToNodeSpace(mousePosition);

        // ��ӡ���λ��
        CCLOG("Mouse clicked at screen position: (%.2f, %.2f)", mousePosition.x, mousePosition.y);
        CCLOG("Map position: (%.2f, %.2f)", mapPosition.x, mapPosition.y);

        // ���� true ��ʾ�¼��Ѵ���
        return true;
    }

    return false;
}