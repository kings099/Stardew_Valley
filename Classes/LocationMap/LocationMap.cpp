/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.cpp
 * File Function: LocationMap类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#include "LocationMap.h"
#include "Classes/Character/Character.h"
#include "proj.win32/Constant.h"

 // 获取单例
LocationMap& LocationMap::getInstance()
{
    static LocationMap instance;
    return instance;
}

// 获取位置属性与屏幕坐标键值对
const std::map<Location, cocos2d::Vec2>& LocationMap::getLocationMap() const
{
    return _locationMap;
}

// 获取位置属性与屏幕坐标键值对(技能等级)
const std::map<int, cocos2d::Vec2>& LocationMap::getSkillLevelLocationMap() const {
    return _skillLevelLocationMap;
}

// 获取位置属性与屏幕坐标键值对(商店)
const std::map<int, cocos2d::Vec2>& LocationMap::getStoreLocationMap() const {
    return _storeLocationMap;
}

// 获取位置属性与屏幕坐标键值对(合成表)
const std::map<int, cocos2d::Vec2>& LocationMap::getSysthesisTableLocationMap() const {
    return _systhesisTableLocationMap;
}


// 构造函数
LocationMap::LocationMap()
{
    // 初始化位置属性与屏幕坐标键值对(物品栏)
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

    // 初始化位置属性与屏幕坐标键值对(箱子)
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        const Location location = { OpenedBoxList,i };
        _locationMap[location] = cocos2d::Vec2(OBJECT_BOX_START_X + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, OBJECT_BOX_START_Y);
    }

    // 初始化位置属性与屏幕坐标键值对(技能等级)
    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        for (int j = 0; j < SKILL_LEVEL_NUM; j++) {
            _skillLevelLocationMap[i * SKILL_LEVEL_NUM + j] = cocos2d::Vec2(SKILL_LEVEL_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, SKILL_LEVEL_START_Y + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL);
        }
    }

    // 初始化位置属性与屏幕坐标键值对(商店)
    for (int i = 0; i < PRODUCE_KIND_NUM_EACH_DAY; i++) {
        _storeLocationMap[i] = cocos2d::Vec2(OBJECT_STORE_IMAGE_START_X, OBJECT_STORE_IMAGE_START_Y - i * OBJECT_LIST_NODE_VERTICAL_INTERVAL);
    }

    // 初始化位置属性与屏幕坐标键值对(合成表)
    for (int i = 0; i < SYNTHESIS_TABLE_ROWS; i++) {
        for (int j = 0; j < SYNTHESIS_TABLE_COLS; j++) {
            _systhesisTableLocationMap[i * SYNTHESIS_TABLE_COLS + j] = cocos2d::Vec2(SYNTHESIS_TABLE_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, SYNTHESIS_TABLE_START_Y - i * OBJECT_LIST_NODE_VERTICAL_INTERVAL);
        }
    }
}