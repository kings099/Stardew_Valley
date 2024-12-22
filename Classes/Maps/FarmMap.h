/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: ��ʼũ����ͼFarmMap��Ķ���
 * Author:        �����
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FARM_MAP_H_
#define FARM_MAP_H_


#include "cocos2d.h"
#include "2d/CCTMXTiledMap.h"
#include "proj.win32/Constant.h"
#include "GameMap.h"
#include"Classes/Crops/Crops.h"

USING_NS_CC;

class FarmMap : public GameMap {
public:
    FarmMap(const Vec2& mapPosition = Vec2(0, 0));
    ~FarmMap();

    static FarmMap* create(const std::string& mapFile ,  Node* TreeLayer,const Vec2& mapPosition = Vec2(0, 0));

    // ��д��ʼ������
    bool init(const std::string& mapFile, const Vec2& mapPosition, Node* TreeLayer);

    // ����¼��Ĵ���
    bool onMouseEvent(cocos2d::Event* event);

    TMXTiledMap* FarmMap::getTiledMap() const;

    // ��ȡ��ľͼ��
    static void setTreeLayer(cocos2d::Node* treeLayer);

    // ��д��ȡ�ڵ�ķ���
    Node* getNodeAtPosition(const Vec2& tilePos) override;

    // ��ȡũ����ָ��ķ���
    Crops* getCropAtPosition(const Vec2& tilePos);


    // ��ȡ��ͼ����
    MapType getType() const override { return MapType::Farm; }

    // ��ֲ����
    void plantCrops(const Vec2& tilePos, const std::string cropName,const int characterLevel);

private:
    cocos2d::Node* _treeLayer; // ��ľ��ڵ�

    //��path����ֲָ��gid����
    void plantTreesOnPathLayer();

    // ��ʼ������
    void initializeAnimals();

    // ��ʼ����
    void initializeFishes();
};

#endif // __FARM_MAP_H_
