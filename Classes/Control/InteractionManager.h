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
#include "Maps/GameMap.h"
#include "../proj.win32/Constant.h"
#include "Crops/Crops.h"
#include <vector>


class InteractionManager : public cocos2d::Node {
public:
    InteractionManager();
    ~InteractionManager();

    // ��������������ʵ��
    static InteractionManager* create(GameMap* gameMap);

    // ��ʼ������������
    bool init(GameMap* gameMap);

    // ���½�ɫ��Χ����Ƭ��Ϣ
    void updateSurroundingTiles(cocos2d::Vec2& world_pos);

    // �ж�ָ����Ƭλ���Ƿ�Ϊ����ͨ������
    bool isCollidableAtPos(const cocos2d::Vec2& tilePos);

    // ����ɫ�Ƿ�վ�ڴ��͵���
    bool checkTeleport(const cocos2d::Vec2& worldPos, std::string& targetMapFile);

    // �ı��ͼ
    void setMap(GameMap* newMap);

    // ��ȡ��ɫ��Χ����Ƭ��Ϣ
    const std::vector<TileInfo>& getSurroundingTiles() const;

    void ActionAnimation(GameCharacterAction action, const Vec2& TilePos);

    // ��ȡ��ɫǰ����n��ؿ���Ϣ
    const TileInfo GetLineTileInfo(Direction dir, int distance, const Vec2& WroldPos);

private:
    GameMap* _gameMap;             // ��ǰ��ͼ���������
    std::vector<TileInfo> _surroundingTiles; // �����ɫ��Χ 9 ����Ƭ����Ϣ

    // ��ȡĳ����Ƭ�ĵؿ���Ϣ
    const TileInfo GetTileInfoAt(const Vec2& WroldPos);
};

#endif // INTERACTION_MANAGER_H
