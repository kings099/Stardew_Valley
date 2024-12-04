/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 游戏视角控制类GameViewController的
 * Author:        金恒宇
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __GAME_VIEW_CONTROLLER_H__
#define __GAME_VIEW_CONTROLLER_H__

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Maps/FarmMap.h"


class GameViewController : public cocos2d::Node {
public:
    GameViewController(Character* character,FarmMap* farmmap);  // 构造函数，接受角色对象

    void update(float deltaTime);  // 每帧更新角色位置和摄像机位置

private:
    Character* _character;  // 角色对象
    FarmMap* _farmmap;
};

#endif // __GAME_VIEW_CONTROLLER_H__
