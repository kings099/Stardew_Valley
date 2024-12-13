/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��Ϸ�ӽǿ�����GameViewController�Ķ���
 * Author:        �����
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __GAME_VIEW_CONTROLLER_H__
#define __GAME_VIEW_CONTROLLER_H__

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Maps/GameMap.h"


class GameViewController : public cocos2d::Node {
public:
    GameViewController(Character* character,GameMap* gamemap);  // ���캯�������ܽ�ɫ����

    void update(float deltaTime);  // ÿ֡���½�ɫλ�ú������λ��

    void setMap(GameMap* newMap);    // ���µ�ͼ

private:
    Character* _character;  // ��ɫ����
    GameMap* _map;      // ��ͼ����
};

#endif // __GAME_VIEW_CONTROLLER_H__
