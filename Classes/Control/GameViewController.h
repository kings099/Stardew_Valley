/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 游戏视角控制类GameViewController的定义
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __GAME_VIEW_CONTROLLER_H__
#define __GAME_VIEW_CONTROLLER_H__

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Maps/GameMap.h"


class GameViewController : public cocos2d::Node {
public:

    static GameViewController* create(Character* character, GameMap* gamemap);


    void update(float deltaTime);  // 每帧更新角色位置和摄像机位置

    void setMap(GameMap* newMap);    // 更新地图

private:
    Character* _character;  // 角色对象

    GameMap* _map;      // 地图对象

    // 黑暗效果相关成员
    cocos2d::LayerColor* _darknessMask;  // 黑色遮罩层
    bool _darknessEnabled;              // 黑暗效果是否启用

    // 构造函数
    GameViewController(); 

    //视判断辅助函数
    float GameViewController::clamp(float value, float minVal, float maxVal);

    // 初始化方法
    bool init(Character* character, GameMap* gamemap);

    // 启用黑暗环境效果,仅在矿洞地图生效
    void enableDarknessEffect(); 

    // 禁用黑暗环境效果，由矿洞地图切换至其他地图时启用
    void disableDarknessEffect();
};

#endif // __GAME_VIEW_CONTROLLER_H__
