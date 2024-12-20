/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.h
 * File Function: 初始农场地图FarmMap类的定义
 * Author:        金恒宇
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
    virtual ~FarmMap();

    static FarmMap* create(const std::string& mapFile ,  Node* TreeLayer,const Vec2& mapPosition = Vec2(0, 0));

    // 重写初始化函数
    virtual bool init(const std::string& mapFile, const Vec2& mapPosition, Node* TreeLayer);

    // 鼠标事件的处理
    bool onMouseEvent(cocos2d::Event* event);

    TMXTiledMap* FarmMap::getTiledMap() const;

    // 获取树木图层
    static void setTreeLayer(cocos2d::Node* treeLayer);

    // 获取指定位置的树木精灵指针
    Crops* getTreeAtPosition(const Vec2& tilePos) override;

private:
    cocos2d::Node* _treeLayer; // 树木层节点

    //在path层种植指定gid的树
    void plantTreesOnPathLayer();
    void initializeAnimals();
    void initializeFishes();
};

#endif // __FARM_MAP_H_
