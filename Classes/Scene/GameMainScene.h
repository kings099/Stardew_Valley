/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameMainScene.h
 * File Function: 游戏主场景类GameMainSecen类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

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
#include "../Classes/Layer/TimeManagerUI.h"
#include "Control/MapSwitchManager.h"
#include "Layer/AudioControlLayer.h"

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
    // 农场地图
    FarmMap* _farmMap;
  
    // 角色
    Character* _character;

    // 视角控制器
    GameViewController* _viewController;

    // 交互类管理
    InteractionManager* _interaction;

    // UI层
    UILayer* _uiLayer;
};

#endif // __FARM_SCENE_H__
