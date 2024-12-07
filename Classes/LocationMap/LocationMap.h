/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.h
 * File Function: 位置属性与屏幕坐标键值对类LocationMap类的定义
 * Author:        尹诚成
 * Update Date:   2024/12/07
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _LOCATION_MAP_H_
#define _LOCATION_MAP_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "proj.win32/ObjectConstant.h"

class LocationMap {
public:
    // 获取单例
    static LocationMap& getInstance();

    // 获取位置属性与屏幕坐标键值对
    const std::map<ObjectListLocation, cocos2d::Vec2>& getLocationMap() const;

private:
    std::map<ObjectListLocation, cocos2d::Vec2> locationMap; // 位置属性与屏幕坐标键值对

    // 构造函数
    LocationMap();
};

#endif // !_LOCATION_MAP_H_