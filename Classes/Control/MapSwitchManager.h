/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapSwitchManager.h
 * File Function: ��ͼ�л�������MapSwitchManager�Ķ���
 * Author:        �����
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MAP_SWITCH_MANAGER_H_
#define MAP_SWITCH_MANAGER_H_

#include "cocos2d.h"
#include "Maps/GameMap.h"
#include "Maps/FarmMap.h"
#include "Maps/IndoorMap.h"
#include "Character/Character.h"

USING_NS_CC;

class MapSwitchManager : public Node
{
public:
    // ���� MapSwitchManager ʵ��
    static MapSwitchManager* create(Character* character, GameMap* currentMap);

    // �л���ͼ
    bool switchMap(const std::string& newMapFile, int teleportID);

private:
    // ���캯������������
    MapSwitchManager();
    ~MapSwitchManager();

    bool init(Character* character, GameMap* currentMap);

    // ���ݴ��͵� ID ��ȡĿ��λ��
    //Vec2 getTargetPositionByID(int teleportID, GameMap* newMap);

    // ��̬������ͼʵ�����������ͣ�
    GameMap* createMapByType(const std::string& mapFile);

private:
    Character* _character;  // ��ǰ�Ľ�ɫ����
    GameMap* _currentMap;   // ��ǰ��ͼ����
};

#endif // MAP_SWITCH_MANAGER_H_
