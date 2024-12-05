/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmScene.h
 * File Function: 农场场景类FamrScene的定义
 * Author:        金恒宇
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __FARM_SCENE_H__
#define __FARM_SCENE_H__

#include "cocos2d.h"
#include "Classes/Maps/FarmMap.h"
#include "Classes/Character/Character.h"
#include "Classes/Control/GameViewController.h"

class FarmScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化
    virtual bool init();

    // 关闭回调
    void menuCloseCallback(cocos2d::Ref* pSender);

    // 实现 create() 方法
    CREATE_FUNC(FarmScene);

private:
    // 农场地图
    FarmMap* farmMap;

    // 角色
    Character* character;

    // 视角控制器
    GameViewController* viewController;
};

#endif // __FARM_SCENE_H__
