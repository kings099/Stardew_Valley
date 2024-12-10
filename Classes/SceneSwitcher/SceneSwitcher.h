/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SceneSwitcher.h
 * File Function: ���ڹ������л�����
 * Author:        ������
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __MAP_SWITCHER_H__
#define __MAP_SWITCHER_H__

#include "cocos2d.h"
#include "Classes/Scene/IndoorScene.h"  // ������Ҫ�л�����Ŀ�곡��
#include "Classes/Character/Character.h"
USING_NS_CC;

class MapSwitcher : public Node
{
public:
    // ���캯������������
    MapSwitcher();
    ~MapSwitcher();

    // ���� MapSwitcher ����ʼ��
    static MapSwitcher* create(const std::string& targetMapName, Character* character);

    // ��ʼ������
    bool init(const std::string& targetMapName, Character* character);

    // ÿ֡����ɫ�Ƿ�����л������л�����
    void checkCharacterPositionAndSwitchScene(float deltaTime);

    //// ���update��������
    //virtual void update(float deltaTime) override;

    // ����ɫ�Ƿ����л�������
    bool checkIfInSwitchArea_farm(const Vec2& position);
    bool checkIfInSwitchArea_house(const Vec2& position);
private:
    std::string targetMapName;  // Ŀ���ͼ����
    Character* character;  // ��ɫ�ڵ�ָ��
};

#endif // __MAP_SWITCHER_H__
