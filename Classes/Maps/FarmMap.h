/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: ��ʼũ����ͼFarmMap��Ķ���
 * Author:        �����
 * Update Date:   2024/12/2
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FARM_MAP_H_
#define FARM_MAP_H_

#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"


class FarmMap : public cocos2d::Node
{
public:
    FarmMap();
    ~FarmMap();

    // ����ũ����ͼ
    static FarmMap* create(const std::string& mapFile);

    // ��ʼ������
    virtual bool init(const std::string& mapFile);

    // ���µ�ͼλ��
    void updateMapPosition(const cocos2d::Vec2& characterPosition); 

    // ����¼�����
    bool onMouseEvent(cocos2d::Event* event);

private:
    cocos2d::TMXTiledMap* _tileMap;  // ��Ƭ��ͼ����
};

#endif // __FARM_MAP_H__

