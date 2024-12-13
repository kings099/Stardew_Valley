/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 游戏视角控制类GameViewController的定义
 * Author:        金恒宇
 * Update Date:   2024/12/13
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
    GameViewController(Character* character,GameMap* gamemap);  // 构造函数，接受角色对象

    void update(float deltaTime);  // 每帧更新角色位置和摄像机位置

    void setMap(GameMap* newMap);    // 更新地图

private:
    Character* _character;  // 角色对象
    GameMap* _map;      // 地图对象
};

#endif // __GAME_VIEW_CONTROLLER_H__
