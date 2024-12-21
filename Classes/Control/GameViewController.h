/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��Ϸ�ӽǿ�����GameViewController�Ķ���
 * Author:        �����
 * Update Date:   2024/12/11
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

    static GameViewController* create(Character* character, GameMap* gamemap);


    void update(float deltaTime);  // ÿ֡���½�ɫλ�ú������λ��

    void setMap(GameMap* newMap);    // ���µ�ͼ

private:
    Character* _character;  // ��ɫ����

    GameMap* _map;      // ��ͼ����

    // �ڰ�Ч����س�Ա
    cocos2d::LayerColor* _darknessMask;  // ��ɫ���ֲ�
    bool _darknessEnabled;              // �ڰ�Ч���Ƿ�����

    // ���캯��
    GameViewController(); 

    //���жϸ�������
    float GameViewController::clamp(float value, float minVal, float maxVal);

    // ��ʼ������
    bool init(Character* character, GameMap* gamemap);

    // ���úڰ�����Ч��,���ڿ󶴵�ͼ��Ч
    void enableDarknessEffect(); 

    // ���úڰ�����Ч�����ɿ󶴵�ͼ�л���������ͼʱ����
    void disableDarknessEffect();
};

#endif // __GAME_VIEW_CONTROLLER_H__
