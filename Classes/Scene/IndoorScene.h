/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorScene.h
 * File Function: 室内类的创建的头文件
 * Author:        胡宝怡
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __INDOOR_SCENE_H__
#define __INDOOR_SCENE_H__

#include "cocos2d.h"
#include "Classes/Scene/FarmScene.h"
#include "Classes/Control/GameViewController.h"  // 添加视角控制器头文件
#include "Classes/Maps/IndoorMap.h"
#include "Classes/Layer/UILayer.h"
#include "Classes/Control/InteractionManager.h"

USING_NS_CC;

class IndoorScene : public cocos2d::Scene
{
public:
    // 创建并初始化室内地图
    static IndoorScene* create(const std::string& mapFile);

    // 初始化地图
    bool init(const std::string& mapFile);

    // 创建场景并返回
    static cocos2d::Scene* createScene(const std::string& mapFile);


    // 关闭回调
    void menuCloseCallback(cocos2d::Ref* pSender);

    //// 添加update方法声明
    //virtual void update(float deltaTime) override;

    //// 添加析构函数声明
    //virtual ~IndoorScene();
private:
    IndoorMap* indoorMap;         // 瓦片地图
    std::unique_ptr<Character> character;           // 角色
    GameViewController* viewController; // 视角控制器
};

#endif  // __INDOOR_SCENE_H__
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorScene.h
 * File Function: 室内类的创建的头文件
 * Author:        胡宝怡
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
 //#ifndef __INDOOR_MAP_H__
 //#define __INDOOR_MAP_H__
 //
 //#include "cocos2d.h"
 //#include "Classes/Scene/FarmScene.h"
 //#include "Classes/Control/GameViewController.h"  // 添加视角控制器头文件
 //#include "Classes/Maps/IndoorMap.h"
 //
 //USING_NS_CC;
 //
 //class IndoorScene : public cocos2d::Scene
 //{
 //public:
 //    // 创建并初始化室内地图
 //    static IndoorScene* create(const std::string& mapFile);
 //
 //    // 初始化地图
 //    bool init(const std::string& mapFile);
 //
 //    // 创建场景并返回
 //    static cocos2d::Scene* createScene(const std::string& mapFile);
 //
 //    // 检查角色位置并切换场景
 //    void checkCharacterPositionAndSwitchScene();
 //
 //    // 关闭回调
 //    void menuCloseCallback(cocos2d::Ref* pSender);
 //
 //private:
 //    IndoorMap* indoorMap;         // 瓦片地图
 //    Character* character;             // 角色
 //    GameViewController* viewController; // 视角控制器
 //};
 //
 //#endif  // __INDOOR_MAP_H__
 //#include "cocos2d.h"
 //#include "Classes/Maps/IndoorMap.h"
 //#include "Classes/Character/Character.h"
 //#include "Classes/Control/GameViewController.h"
 //#include "Classes/Layer/UILayer.h"
 //#include "Classes/Control/InteractionManager.h"
 //
 //
 //class IndoorScene : public cocos2d::Scene
 //{
 //public:
 //    // 创建场景
 //    static cocos2d::Scene* createScene();
 //
 //    // 初始化
 //    virtual bool init();
 //
 //    // 关闭回调
 //    void menuCloseCallback(cocos2d::Ref* pSender);
 //
 //    // 实现 create() 方法
 //    CREATE_FUNC(IndoorScene);
 //
 //private:
 //    // 农场地图
 //    IndoorMap* indoorMap;
 //
 //    // 角色
 //    Character* character;
 //
 //    // 视角控制器
 //    GameViewController* viewController;
 //
 //    // UI层
 //    UILayer* uiLayer;
 //};
 //#include "cocos2d.h"
 //#include "Classes/Scene/FarmScene.h"
 //#include "Classes/Control/GameViewController.h"  // 添加视角控制器头文件
 //#include "Classes/Maps/IndoorMap.h"
 //USING_NS_CC;
 //class IndoorScene : public cocos2d::Scene
 //{
 //public:
 //    // 创建并初始化室内地图
 //    static IndoorScene* create(const std::string& mapFile);
 //    // 初始化地图
 //    bool init(const std::string& mapFile);
 //    // 创建场景并返回
 //    static cocos2d::Scene* createScene(const std::string& mapFile);
 //    // 检查角色位置并切换场景
 //    void checkCharacterPositionAndSwitchScene();
 //    // 关闭回调
 //    void menuCloseCallback(cocos2d::Ref* pSender);
 //private:
 //    IndoorMap* indoorMap;         // 瓦片地图
 //    Character* character;             // 角色
 //    GameViewController* viewController; // 视角控制器
 //};
 //#endif // __INDOOR_SCENE_H__