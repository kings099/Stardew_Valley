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
#include "Maps/FarmMap.h"
#include "../proj.win32/Constant.h"
#include "Crops/Crops.h"
#include <vector>


class InteractionManager : public cocos2d::Node {
public:
    // ���캯��
    InteractionManager();

    // ��������
    ~InteractionManager();

    // ��������������ʵ��
    static InteractionManager* create(GameMap* gameMap);

    // ��ʼ������������
    bool init(GameMap* gameMap);

    // ���½�ɫ��Χ����Ƭ��Ϣ
    void updateSurroundingTiles(cocos2d::Vec2& world_pos);

    // ����ɫ�Ƿ�վ�ڴ��͵���
    bool checkTeleport(const cocos2d::Vec2& worldPos, std::string& targetMapFile);

    // �ı��ͼ
    void setMap(GameMap* newMap);

    // ��ȡ��ɫ��Χ����Ƭ��Ϣ
    const std::vector<TileInfo>& getSurroundingTiles() const;

    // ִ�ж�Ӧ�ؿ鶯��
    void ActionAnimation(GameCharacterAction action, const Vec2& TilePos);

    // ��ȡ��ɫǰ����n��ؿ���Ϣ
    const TileInfo GetLineTileInfo(Direction dir, int distance, const Vec2& WroldPos);

    // ���½�ɫѡ����Ʒ����
    void updateCurrentObject(const ObjectListNode& object){
        _currentObject = object;
    }
private:
    // ��ǰ��ͼ����
    GameMap* _gameMap;                          

    // �����ɫ��Χ 9 ����Ƭ����Ϣ
    std::vector<TileInfo> _surroundingTiles;    

    //���浱ǰѡ����Ʒ
    ObjectListNode _currentObject;              

    // �ж�ָ����Ƭλ���Ƿ�Ϊ����ͨ������
    bool isCollidableAtPos(const cocos2d::Vec2& tilePos);

    // ��ȡĳ����Ƭ�ĵؿ���Ϣ
    const TileInfo GetTileInfoAt(const Vec2& WroldPos);

    // ĳ��λ�ò��ſ�����������̬ʵ��Ҫ���ͼ��Farmmap�ࣩ
    void getTreeAndChopAt(const Vec2& tilePos);

    // ������Ʒ�ķ���
    bool placeObjectAtTile(const cocos2d::Vec2& tilePos);

    // ��ȡ��ʯ��Ϣ
    void InteractionManager::GetMineInfo(int MineGID, TileInfo& tile);
};

#endif // INTERACTION_MANAGER_H
