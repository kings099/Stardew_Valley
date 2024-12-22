/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameMainScene.h
 * File Function: 游戏主场景类GameMainSecen类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __GAME_MAIN_SCENE_H__
#define __GAME_MAIN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Classes/Maps/FarmMap.h"
#include "Classes/Character/Character.h"
#include "Classes/Control/GameViewController.h"
#include "Classes/Layer/UILayer.h"
#include "Classes/Control/InteractionManager.h"
#include "../Classes/MenuImage/HoverMenuItemImage.h"
#include "../Classes/Layer/UILayer.h"
#include "../Classes/Manager/TimeManager.h"
#include "Control/MapSwitchManager.h"
#include "Layer/AudioControlLayer.h"
#include "Layer/FestivalLayer.h"
class GameMainScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化
    virtual bool init();

    // 关闭回调
    void menuCloseCallback(cocos2d::Ref* pSender);

    // 实现 create() 方法
    CREATE_FUNC(GameMainScene);
    

private:

    // 模块化初始化方法
    // 初始化地图和角色
    void initializeMapAndCharacter();  

    // 初始化视角控制和交互管理
    void initializeViewControllerAndInteraction();

    // 初始化 UI 层
    void initializeUI();     

    // 注册输入事件监听器
    void registerInputListeners();

    // 注册更新回调函数
    void registerUpdateCallbacks();        

    // 成员变量

    // 当前地图指针 初始地图为农场地图
    FarmMap* _farmMap = nullptr;                

    // 角色单例
    Character* _character = nullptr;           

    // 视角控制器
    GameViewController* _viewController = nullptr; 

    // 交互管理器
    InteractionManager* _interaction = nullptr; 

    // UI 层
    UILayer* _uiLayer = nullptr;                

    // ui容器
    Node* _uiContainer = nullptr;

    // 地图切换管理器   
    MapSwitchManager* _mapSwitchManager = nullptr;  

};

#endif // __GAME_MAIN_SCENE_H__
