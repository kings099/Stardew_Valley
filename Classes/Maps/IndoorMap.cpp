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
    _mapName = mapFile;
    _map_position = mapPosition;
    this->setScale(INDOOR_MAP_SCALE);

    return true;
}

// ��ȡ���ڵ�ͼ�ض��ڵ�
Node* IndoorMap::getNodeAtPosition(const Vec2& tilePos) {
    // �������ڵ�ͼ�ڵ�������ݣ�Ŀǰ���ޣ�

    return nullptr;
}



