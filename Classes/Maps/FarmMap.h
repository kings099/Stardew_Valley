/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: ��ʼũ����ͼFarmMap��Ķ���
 * Author:        �����
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FARM_MAP_H_
#define FARM_MAP_H_


#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

class FarmMap : public cocos2d::Node
{
public:
    FarmMap(const Vec2& mapPosition);
    ~FarmMap();

    // ��mappositionλ�ô���ũ����ͼ��Ĭ��Ϊ0��0
    static FarmMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // ��ʼ������
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);

    // �������굽��Ƭ�����ת��
    Vec2 absoluteToTile(const Vec2& pixelPoint);

    // ����¼�����
    bool onMouseEvent(cocos2d::Event* event);

    //���ص�ͼ���ش�С
    const Size& getMapSize()const;

    //������Ƭ��ͼ��С������Ƭ������
    const Size& getMapSizeinTile();
    //��ȡָ��λ��ָ��ͼ���GID
    int getTileGIDAt(const std::string& layerName, const Vec2& tileCoord);


    // ����GID��ȡ��Ƭ���ԣ��� TMX �ļ��е�tilesets�ж�ȡ��
    cocos2d::ValueMap getTilePropertiesForGID(int GID);


protected:
    cocos2d::TMXTiledMap* _tile_map;  // ��Ƭ��ͼ����
    Vec2 _map_position;
};

#endif // __FARM_MAP_H__

