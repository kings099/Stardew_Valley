/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SceneSwitcher.h
 * File Function: 用于管理场景切换的类
 * Author:        胡宝怡
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __MAP_SWITCHER_H__
#define __MAP_SWITCHER_H__

#include "cocos2d.h"
#include "Classes/Scene/IndoorScene.h"  // 假设你要切换到的目标场景
#include "Classes/Character/Character.h"
USING_NS_CC;

class MapSwitcher : public Node
{
public:
    // 构造函数和析构函数
    MapSwitcher();
    ~MapSwitcher();

    // 创建 MapSwitcher 并初始化
    static MapSwitcher* create(const std::string& targetMapName, Character* character);

    // 初始化函数
    bool init(const std::string& targetMapName, Character* character);

    // 每帧检查角色是否进入切换区域并切换场景
    void checkCharacterPositionAndSwitchScene(float deltaTime);

    //// 添加update方法声明
    //virtual void update(float deltaTime) override;

    // 检查角色是否在切换区域内
    bool checkIfInSwitchArea_farm(const Vec2& position);
    bool checkIfInSwitchArea_house(const Vec2& position);
private:
    std::string targetMapName;  // 目标地图名称
    Character* character;  // 角色节点指针
};

#endif // __MAP_SWITCHER_H__
