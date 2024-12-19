/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TownMap.h
 * File Function: С���ͼTownMap��Ķ���
 * Author:        �����
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef TOWNMAP_H
#define TOWNMAP_H

#include "GameMap.h"
USING_NS_CC;

class TownMap : public GameMap
{
public:
    // ���캯������������
    TownMap(const Vec2& mapPosition);
    virtual ~TownMap();

    // ��������
    static TownMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // ��д��ʼ������
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition) override;

    // ��ȡ TMXTiledMap ����
    virtual TMXTiledMap* getTiledMap() const;

    // ��������¼�
    bool onMouseEvent(Event* event);

private:


    // �����ͼ�����ű���
    static constexpr float TOWN_MAP_SCALE = 2.0f; // ������Ҫ�������ű���
};

#endif // TOWNMAP_H