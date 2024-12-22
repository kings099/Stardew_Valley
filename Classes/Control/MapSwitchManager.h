/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapSwitchManager.h
 * File Function: ��ͼ�л�������MapSwitchManager�Ķ���
 * Author:        �����
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MAP_SWITCH_MANAGER_H_
#define MAP_SWITCH_MANAGER_H_

#include "cocos2d.h"
#include "Maps/GameMap.h"
#include "Maps/FarmMap.h"
#include "Maps/IndoorMap.h"
#include "Maps/TownMap.h"
#include "Maps/MineMap.h"
#include "Maps/IndoorLighting.h"
#include "Character/Character.h"
#include "GameViewController.h"
#include "InteractionManager.h"

USING_NS_CC;

class MapSwitchManager : public Node
{
public:
    // ���� MapSwitchManager ʵ��
    static MapSwitchManager* create(Character* character, GameMap* currentMap, GameViewController* viewController,InteractionManager* interactionManager);

    // �л���ͼ
    bool switchMap(const std::string& newMapFile, Vec2& teleportPOS,Node* TreeLayer, Node* MapLayer);

private:
    // ���캯������������
    MapSwitchManager();

    bool init(Character* character, GameMap* currentMap, GameViewController* viewController, InteractionManager* interactionManager);

    // ���ݴ��͵� ID ��ȡĿ��λ��
    Vec2 getTargetPositionByID(int teleportID, GameMap* newMap);


private:
    // ��ǰ�Ľ�ɫ����
    Character* _character; 

    // ��ǰ��ͼ����
    GameMap* _currentMap; 

    // �ӽǿ�����
    GameViewController* _viewController;

    // ����������
    InteractionManager* _interactionManager; 

    // RAII ����ƹ�Ч��
    std::unique_ptr<IndoorLighting> _lightingGuard; 


};

#endif // MAP_SWITCH_MANAGER_H_
