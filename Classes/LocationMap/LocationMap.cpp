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
    const auto objectListStatus = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png")->checkObjectListStatus();
    
    // 物品栏处于打开状态
    if (objectListStatus) {

    }
    // 物品栏处于关闭状态
    else {


    }
}