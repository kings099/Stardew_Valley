/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LocationMap.cpp
 * File Function: LocationMap���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/07
 * License:       MIT License
 ****************************************************************/

#include "LocationMap.h"
#include "Classes/Character/Character.h"

 // ��ȡ����
LocationMap& LocationMap::getInstance()
{
    static LocationMap instance;
    return instance;
}

// ��ȡλ����������Ļ�����ֵ��
const std::map<ObjectListLocation, cocos2d::Vec2>& LocationMap::getLocationMap() const
{
    return locationMap;
}

// ���캯��
LocationMap::LocationMap()
{
    const auto objectListStatus = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png")->checkObjectListStatus();
    
    // ��Ʒ�����ڴ�״̬
    if (objectListStatus) {

    }
    // ��Ʒ�����ڹر�״̬
    else {


    }
}