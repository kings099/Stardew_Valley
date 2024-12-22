/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MineMap.h
 * File Function: ��ʼ���󶴵�ͼ
 * Author:        �������������޸����е��麯������д�̳��Ի����һЩ�������ƹ�ģ���ࣩ
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MINE_MAP_H_
#define MINE_MAP_H_
#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"
#include "GameMap.h"

USING_NS_CC;

class MineMap :public GameMap
{
public:
    MineMap(const Vec2& mapPosition);

    ~MineMap();

    // ��mappositionλ�ô���ũ����ͼ��Ĭ��Ϊ0��0
    static MineMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // ��ʼ������
    bool init(const std::string& mapFile, const Vec2& mapPosition);

    // ��д�滻�ؿ��߼�������ˢ���߼�
    void replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction = true) override;

    MapType getType() const { return MapType::Mine; }

private:

    // ��ȡָ����Ƭ������
    TileConstants::TileType getTileTypeAt(const Vec2& tileCoord) const;
};
#endif // __MINE_MAP_H_
