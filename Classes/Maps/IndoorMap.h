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

    MapType getType() const override { return MapType::Farm; }
};

#endif // __INDOOR_MAP_H_

///****************************************************************
// * Project Name:  Stardew_Valley
// * File Name:     IndoorMap.h
// * File Function: ��ʼ�����ڵ�ͼ
// * Author:        ������
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
//    // ��mappositionλ�ô���ũ����ͼ��Ĭ��Ϊ0��0
//    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));
//
//    // ��ʼ������
//    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);
//
//    // �������굽��Ƭ�����ת��
//    Vec2 absoluteToTile(const Vec2& pixelPoint);
//
//    // ����¼�����
//    bool onMouseEvent(cocos2d::Event* event);
//
//    //���ص�ͼ���ش�С
//    const Size& getMapSize()const;
//
//
//
//private:
//    cocos2d::TMXTiledMap* _tileMap;  // ��Ƭ��ͼ����
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
//    // ��д��ʼ������
//    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);
//    virtual Vec2 absoluteToTile(const Vec2& pixelPoint);
//    // ����¼��Ĵ���
//    bool onMouseEvent(cocos2d::Event* event);
//
//    // ��ȡĳGIDͼ�������
//    cocos2d::ValueMap getTilePropertiesForGID(int GID);
//};
//
//#endif // __Indoor_MAP_H_
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorMap.h
 * File Function: ��ʼ�����ڵ�ͼ
 * Author:        ������
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
 //    // ��mappositionλ�ô���ũ����ͼ��Ĭ��Ϊ0��0
 //    static IndoorMap* create(const std::string& mapFile, const Vec2& mapPosition = Vec2(0, 0));
 //    // ��ʼ������
 //    virtual bool init(const std::string& mapFile, const Vec2& mapPosition);
 //    // �������굽��Ƭ�����ת��
 //    Vec2 absoluteToTile(const Vec2& pixelPoint);
 //    // ����¼�����
 //    bool onMouseEvent(cocos2d::Event* event);
 //    //���ص�ͼ���ش�С
 //    const Size& getMapSize()const;
 //private:
 //    cocos2d::TMXTiledMap* _tileMap;  // ��Ƭ��ͼ����
 //    Vec2 _mapPosition;
 //};
 //#endif // __INDOOR_MAP_H__