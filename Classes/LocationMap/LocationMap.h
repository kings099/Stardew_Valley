/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.h
 * File Function: λ����������Ļ�����ֵ����LocationMap��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _LOCATION_MAP_H_
#define _LOCATION_MAP_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"


class LocationMap {
public:
    // ��ȡ����
    static LocationMap& getInstance();

    // ��ȡλ����������Ļ�����ֵ��(��Ʒ��)
    const std::map<Location, cocos2d::Vec2>& getLocationMap() const;

    // ��ȡλ����������Ļ�����ֵ��(���ܵȼ�)
    const std::map<int, cocos2d::Vec2>& getSkillLevelLocationMap() const;

    // ��ȡλ����������Ļ�����ֵ��(�̵�)
    const std::map<int, cocos2d::Vec2>& getStoreLocationMap() const;

    // ��ȡλ����������Ļ�����ֵ��(�ϳɱ�)
    const std::map<int, cocos2d::Vec2>& getSysthesisTableLocationMap() const;
private:
    std::map<int, cocos2d::Vec2> _skillLevelLocationMap;        //λ����������Ļ�����ֵ��(���ܵȼ�)
    std::map<Location, cocos2d::Vec2>_locationMap;              //λ����������Ļ�����ֵ��(��Ʒ��)
    std::map<int, cocos2d::Vec2>_storeLocationMap;              //λ����������Ļ�����ֵ��(�̵�)
    std::map<int , cocos2d::Vec2> _systhesisTableLocationMap;   //λ����������Ļ�����ֵ��(�ϳɱ�)
    // ���캯��
    LocationMap();
};

#endif // !_LOCATION_MAP_H_