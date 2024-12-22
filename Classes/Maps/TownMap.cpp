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
    _map_position = mapPosition;
    _mapName = mapFile;
    this->setScale(TOWN_MAP_SCALE);

    // ���С���ͼ��ʼ��ʱ��Ҫ�����ľ���
     // ��ʼ�� NPC �͹�����

    NpcManager::getInstance()->initializeNPCs();  // ��ʼ�� NPC
    CCLOG("NPC initialization completed.");
    // ��ȡ Abigail NPC
    NPC* abigail = NpcManager::getInstance()->getNPCByName("Abigail");
    // ��ʼ����������
   
    GiftItemManager::getInstance();  // ��ʼ��������Ʒ������




    // ��� Abigail ���ڣ�������ӵ�������
    if (abigail) {
        this->addChild(abigail, 4);  // ������ NPC ������ӵ�������
        abigail->startWalkingAnimation();  // ��������
        CCLOG("Abigail added to scene.");
    }
    else {
        CCLOG("Abigail NPC not found!");  // ���û���ҵ� Abigail NPC�����ӡ������־
    }
    CCLOG("NPC initialization completed.");
  
    return true;
}

Node* TownMap::getNodeAtPosition(const Vec2& tilePos) {

    // ���С���ͼ���нڵ��߼� �����ޣ�
    return nullptr; // Ĭ�Ϸ��� nullpt
}