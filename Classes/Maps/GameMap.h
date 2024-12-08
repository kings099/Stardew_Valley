/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: ��ͼ����Map��Ķ���
 * Author:        �����
 * Update Date:   2024/12/8
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "cocos2d.h"

USING_NS_CC;

class GameMap : public Node {
public:
    GameMap(const Vec2& mapPosition = Vec2(0, 0));
    virtual ~GameMap();

    // ������ͼ
    static GameMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // ��ʼ����ͼ
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);

    // ת���������굽��ͼ��Ƭ����
    virtual Vec2 absoluteToTile(const Vec2& pixelPoint);

    // ��ͼ���ش�С
    virtual const Size& getMapSize() const;

    // ��ͼ��Ƭ��С
    virtual const Size& getMapSizeinTile();

    // ��ȡĳλ��Layernameͼ���GID
    virtual int getTileGIDAt(const std::string& layerName, const Vec2& tileCoord);

protected:
    TMXTiledMap* _tile_map;  // ��Ƭ��ͼ��
    Vec2 _map_position;      // ��ͼ����λ��
};

#endif // GAME_MAP_H_