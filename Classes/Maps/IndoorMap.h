/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.h
 * File Function: ��ʼ�����ڵ�ͼ
 * Author:        ������
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef INDOOR_MAP_H_
#define INDOOR_MAP_H_
#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"
#include "GameMap.h"

USING_NS_CC;

class IndoorMap :public GameMap
{
public:
    IndoorMap(const Vec2& mapPosition);
    ~IndoorMap();

    // ��mappositionλ�ô���ũ����ͼ��Ĭ��Ϊ0��0
    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // ��ʼ������
    bool init(const std::string& mapFile, const Vec2& mapPosition);

    MapType getType() const override { return MapType::Indoor; }
};

#endif // __INDOOR_MAP_H_

