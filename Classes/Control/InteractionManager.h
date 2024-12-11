/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��ɫ��ͼ����������InteractionManager�Ķ���
 * Author:        �����
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __INTERACTION_MANAGER_H__
#define __INTERACTION_MANAGER_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "Maps/GameMap.h"
#include <vector>
#include <tuple>

 // �����������࣬���ڹ����ɫ���ͼ֮��Ľ����߼�
class InteractionManager : public cocos2d::Node {
public:
    // ���캯������������
    InteractionManager();
    ~InteractionManager();

    // ��������������ʵ��
    static InteractionManager* create(Character* character, GameMap* gameMap);

    // ��ʼ������������
    bool init(Character* character, GameMap* gameMap);

    // ���½�ɫ��Χ����Ƭ��Ϣ
    void updateSurroundingTiles(cocos2d::Vec2& world_pos);

    // �ж�ָ����Ƭλ���Ƿ�Ϊ����ͨ������
    bool isCollidableAtPos(const cocos2d::Vec2& tilePos);

    // ��ȡ��ɫ��Χ�Ŀ�ͨ��״̬
    // ����һ������9������ֵ����������Ӧ��ɫ��ǰλ�ü���Χ8����Ƭ�Ƿ��ͨ��
    std::vector<bool> getSurroundingCollidable(const cocos2d::Vec2& currentPos);

    // �ж�ָ�����������Ƿ�Ϊ��ũ������
    bool isFarmlandAtPos(const cocos2d::Vec2& worldPos);

    // ��ȡ��ɫ��Χ��Ƭ����ϸ��Ϣ
    // ���ذ��������ơ�GID�����Ե�Ԫ���б�
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> getSurroundingTilesInfo(const cocos2d::Vec2& worldPos);

    // ����ɫ�Ƿ�վ�ڴ��͵���
    // ����Ǵ��͵㣬����Ŀ���ͼ�ļ�·��
    bool checkTeleport(const cocos2d::Vec2& worldPos, std::string& targetMapFile);

    // �ı��ͼ
    void setMap(GameMap* newMap);

private:
    Character* _character;         // ��ǰ��ɫ���������
    GameMap* _gameMap;             // ��ǰ��ͼ���������
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> _surroundingInfo; // �������Χ��Ƭ��Ϣ
};
#endif // __INTERACTION_MANAGER_H__
