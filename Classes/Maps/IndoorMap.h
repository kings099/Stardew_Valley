/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.h
 * File Function: 初始化室内地图
 * Author:        胡宝怡
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

    // 在mapposition位置创建农场地图，默认为0，0
    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));

    // 初始化函数
    bool init(const std::string& mapFile, const Vec2& mapPosition);

    MapType getType() const override { return MapType::Farm; }
};

#endif // __INDOOR_MAP_H_

///****************************************************************
// * Project Name:  Stardew_Valley
// * File Name:     IndoorMap.h
// * File Function: 初始化室内地图
// * Author:        胡宝怡
// * Update Date:   2024/12/4
// * License:       MIT License
// ****************************************************************/
//#pragma once
//#ifndef INDOOR_MAP_H_
//#define INDOOR_MAP_H_
//
//
//#include "cocos2d.h"
//#include "2d/CCTMXTiledMap.h"
//#include "proj.win32/Constant.h"
//
//USING_NS_CC;
//
//class IndoorMap : public cocos2d::Node
//{
//public:
//    IndoorMap(const Vec2& mapPosition);
//    ~IndoorMap();
//
//    // 在mapposition位置创建农场地图，默认为0，0
//    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));
//
//    // 初始化函数
//    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);
//
//    // 绝对坐标到瓦片坐标的转换
//    Vec2 absoluteToTile(const Vec2& pixelPoint);
//
//    // 鼠标事件处理
//    bool onMouseEvent(cocos2d::Event* event);
//
//    //返回地图像素大小
//    const Size& getMapSize()const;
//
//
//
//private:
//    cocos2d::TMXTiledMap* _tileMap;  // 瓦片地图对象
//    Vec2 _mapPosition;
//};
//
//#endif // __INDOOR_MAP_H__
//#include "cocos2d.h"
//#include "2d/CCTMXTiledMap.h"
//#include "proj.win32/Constant.h"
//#include "GameMap.h"
//
//USING_NS_CC;
//
//class IndoorMap : public GameMap {
//public:
//    IndoorMap(const Vec2& mapPosition = Vec2(0, 0));
//    virtual ~IndoorMap();
//
//    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));
//
//    // 重写初始化函数
//    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);
//    virtual Vec2 absoluteToTile(const Vec2& pixelPoint);
//    // 鼠标事件的处理
//    bool onMouseEvent(cocos2d::Event* event);
//
//    // 获取某GID图块的属性
//    cocos2d::ValueMap getTilePropertiesForGID(int GID);
//};
//
//#endif // __Indoor_MAP_H_
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.h
 * File Function: 初始化室内地图
 * Author:        胡宝怡
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/
 //#pragma once
 //#ifndef INDOOR_MAP_H_
 //#define INDOOR_MAP_H_
 //#include "cocos2d.h"
 //#include "2d/CCTMXTiledMap.h"
 //#include "proj.win32/Constant.h"
 //USING_NS_CC;
 //class IndoorMap : public cocos2d::Node
 //{
 //public:
 //    IndoorMap(const Vec2& mapPosition);
 //    ~IndoorMap();
 //    // 在mapposition位置创建农场地图，默认为0，0
 //    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));
 //    // 初始化函数
 //    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);
 //    // 绝对坐标到瓦片坐标的转换
 //    Vec2 absoluteToTile(const Vec2& pixelPoint);
 //    // 鼠标事件处理
 //    bool onMouseEvent(cocos2d::Event* event);
 //    //返回地图像素大小
 //    const Size& getMapSize()const;
 //private:
 //    cocos2d::TMXTiledMap* _tileMap;  // 瓦片地图对象
 //    Vec2 _mapPosition;
 //};
 //#endif // __INDOOR_MAP_H__