/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��Ϸ�ӽǿ�����GameViewController��
 * Author:        �����
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __GAME_VIEW_CONTROLLER_H__
#define __GAME_VIEW_CONTROLLER_H__

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Maps/FarmMap.h"


class GameViewController : public cocos2d::Node {
public:
    GameViewController(Character* character,FarmMap* farmmap);  // ���캯�������ܽ�ɫ����

    void update(float deltaTime);  // ÿ֡���½�ɫλ�ú������λ��

private:
    Character* _character;  // ��ɫ����
    FarmMap* _farmmap;
};

#endif // __GAME_VIEW_CONTROLLER_H__
