/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��ɫ��ͼ����������InteractionManager�Ķ���
 * Author:        �����
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __INTERACTION_MANAGER_H__
#define __INTERACTION_MANAGER_H__

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Maps/FarmMap.h"

class InteractionManager : public cocos2d::Ref
{
public:

    static InteractionManager* create(Character* character, FarmMap* farmMap);
    virtual bool init(Character* character, FarmMap* farmMap);

    // ���½�ɫ��Χ������Ϣ
    void updateSurroundingTiles(Vec2& world_pos);

    // �жϵ�ǰλ�ü�ָ��λ���ϵĽ�������
    bool isCollidableAtPos(const cocos2d::Vec2& worldPos);
    bool isFarmlandAtPos(const cocos2d::Vec2& worldPos);
    bool isWaterableAtPos(const cocos2d::Vec2& worldPos);

    // ��ȡ��Χλ�ÿ��ƶ�״̬
    std::vector<bool> getSorroundingCollidable(const Vec2& currentPos);
    // ���������߼�������������չ������ɼ���Դ���������ص�
    // void harvestAtPos(const cocos2d::Vec2& worldPos);
    // void plowAtPos(const cocos2d::Vec2& worldPos);
    // void waterAtPos(const cocos2d::Vec2& worldPos);

protected:
    InteractionManager();
    ~InteractionManager();
    // ��ȡ��Χ9�񣨰�����ǰ���ڸ���Ƭ��Ϣ
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> getSurroundingTilesInfo(const cocos2d::Vec2& worldPos);

    Character* _character;
    FarmMap* _farmMap;
    //�洢��Χ9����Ƭ��Ϣ
    std::vector<std::tuple<std::string, int, cocos2d::ValueMap>> _surroundingInfo;
};

#endif // __INTERACTION_MANAGER_H__
