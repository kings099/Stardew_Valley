/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.cpp
 * File Function: LocationMap���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/18
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
const std::map<Location, cocos2d::Vec2>& LocationMap::getLocationMap() const
{
    return _locationMap;
}

// ��ȡλ����������Ļ�����ֵ��(���ܵȼ�)
const std::map<int, cocos2d::Vec2>& LocationMap::getSkillLevelLocationMap() const {
    return _skillLevelLocationMap;
}

// ���캯��
LocationMap::LocationMap()
{
    // ��ʼ��λ����������Ļ�����ֵ��(��Ʒ��)
    for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
        for (int j = 0; j < OBJECT_LIST_COLS; j++) {
            const Location location = { OpenedObjectList ,i * OBJECT_LIST_COLS + j };
                _locationMap[location] = cocos2d::Vec2(OPEN_OBJECT_LIST_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, OPEN_OBJECT_LIST_START_Y - i * OBJECT_LIST_NODE_VERTICAL_INTERVAL);  
        }
    }
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        const Location location = { ClosedObjectList ,i };
        _locationMap[location] = cocos2d::Vec2(CLOSE_OBJECT_LIST_START_X + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, CLOSE_OBJECT_LIST_START_Y);
    }
    // ��ʼ��λ����������Ļ�����ֵ��(����)
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        const Location location = { OpenedBoxList,i };
        _locationMap[location] = cocos2d::Vec2(OBJECT_BOX_START_X + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, OBJECT_BOX_START_Y);
    }
    // ��ʼ��λ����������Ļ�����ֵ��(���ܵȼ�)
    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        for (int j = 0; j < SKILL_LEVEL_NUM; j++) {
            _skillLevelLocationMap[i * SKILL_LEVEL_NUM + j] = cocos2d::Vec2(SKILL_LEVEL_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, SKILL_LEVEL_START_Y + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL);
        }
    }
}