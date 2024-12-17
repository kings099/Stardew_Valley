/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.cpp
 * File Function: LocationMap���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/

#include "LocationMap.h"
#include "Classes/Character/Character.h"
#include "proj.win32/Constant.h"

 // ��ȡ����
LocationMap& LocationMap::getInstance()
{
    static LocationMap instance;
    return instance;
}

// ��ȡλ����������Ļ�����ֵ��
const std::map<int, cocos2d::Vec2>& LocationMap::getLocationMap() const
{
    const auto objectListStatus = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png")->getObjectListStatus();
    if (objectListStatus) {
        return _openedlocationMap;
    }
    else {
        return _closedlocationMap;
    }
}

// ��ȡλ����������Ļ�����ֵ��(���ܵȼ�)
const std::map<int, cocos2d::Vec2>& LocationMap::getSkillLevelLocationMap() const {
    return _skillLevelLocationMap;
}

// ��ȡλ����������Ļ�����ֵ��(����)
const std::map<int, cocos2d::Vec2>& LocationMap::getBoxLocationMap() const {
    return _boxlocationMap;
}

// ���캯��
LocationMap::LocationMap()
{
    // ��ʼ��λ����������Ļ�����ֵ��(��Ʒ��)
    for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
        for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                _openedlocationMap[i * OBJECT_LIST_COLS + j] = cocos2d::Vec2(OPEN_OBJECT_LIST_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, OPEN_OBJECT_LIST_START_Y - i * OBJECT_LIST_NODE_VERTICAL_INTERVAL);
        }
    }
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        _closedlocationMap[i] = cocos2d::Vec2(CLOSE_OBJECT_LIST_START_X + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, CLOSE_OBJECT_LIST_START_Y);
    }
    // ��ʼ��λ����������Ļ�����ֵ��(���ܵȼ�)
    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        for (int j = 0; j < SKILL_LEVEL_NUM; j++) {
            _skillLevelLocationMap[i * SKILL_LEVEL_NUM + j] = cocos2d::Vec2(SKILL_LEVEL_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, SKILL_LEVEL_START_Y + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL);
        }
    }
    // ��ʼ��λ����������Ļ�����ֵ��(����)
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        _boxlocationMap[i] = cocos2d::Vec2(OBJECT_BOX_START_X + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, OBJECT_BOX_START_Y);
    }
}