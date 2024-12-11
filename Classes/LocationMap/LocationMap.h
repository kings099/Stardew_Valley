/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.h
 * File Function: λ����������Ļ�����ֵ����LocationMap��Ķ���
 * Author:        ���ϳ�
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
    // ��ȡ����
    static LocationMap& getInstance();

    // ��ȡλ����������Ļ�����ֵ��
    const std::map<ObjectListLocation, cocos2d::Vec2>& getLocationMap() const;

private:
    std::map<ObjectListLocation, cocos2d::Vec2> locationMap; // λ����������Ļ�����ֵ��

    // ���캯��
    LocationMap();
};

#endif // !_LOCATION_MAP_H_