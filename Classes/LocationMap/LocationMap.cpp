/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.cpp
 * File Function: LocationMap类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/07
 * License:       MIT License
 ****************************************************************/

#include "LocationMap.h"
#include "Classes/Character/Character.h"
#include "proj.win32/Constant.h"
#include "proj.win32/ObjectConstant.h"

 // 获取单例
LocationMap& LocationMap::getInstance()
{
    static LocationMap instance;
    return instance;
}

// 获取位置属性与屏幕坐标键值对
const std::map<ObjectListLocation, cocos2d::Vec2>& LocationMap::getLocationMap() const
{
    return locationMap;
}

// 构造函数
LocationMap::LocationMap()
{
    const auto objectListStatus = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png")->getObjectListStatus();
    // 物品栏处于打开状态
    if (objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS ; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                const ObjectListLocation objectListLocation = { Open, i * OBJECT_LIST_COLS + j };
                locationMap[objectListLocation] = cocos2d::Vec2(OPEN_OBJECT_LIST_START_X + j * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, OPEN_OBJECT_LIST_START_Y - i * OBJECT_LIST_NODE_VERTICAL_INTERVAL);
            }
        }
    }
    // 物品栏处于关闭状态
    else {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            const ObjectListLocation objectListLocation = { Close ,i };
            locationMap[objectListLocation] = cocos2d::Vec2(CLOSE_OBJECT_LIST_START_X + i * OBJECT_LIST_NODE_HORIZONTAL_INTERVAL, CLOSE_OBJECT_LIST_START_Y);
        }
    }
}