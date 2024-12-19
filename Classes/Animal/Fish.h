#pragma once
/****************************************************************
 * Project Name:  FishWorld
 * File Name:     Fish.h
 * File Function: 鱼类，处理鱼的生成、活动范围和季节性钓鱼
 * Author:        胡宝怡
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/

#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <unordered_map>
#include <vector>
#include <string>

USING_NS_CC;

class Fishs : public Node {
public:
    Fishs();
    virtual ~Fishs();

    static void initializeSeasonFishMap();
    static Fishs* create(const std::string& name, const std::string& season, const Vec2& position);

    bool init(const std::string& name, const std::string& season, const Vec2& position);
    void setActivityRange(float range);
    std::string getFishImagePath() const;

    // 随机移动
    void moveRandomly(float deltaTime);

    // 更新动画
    void updateAnimation();

    // 捕获鱼
    static std::string catchFish(const std::string& season);

private:
    std::string name;                    // 鱼的名字
    std::string season;                  // 当前季节
    Vec2 position;                       // 当前鱼的位置
    float activityRange;                 // 鱼的活动范围
    Sprite* sprite;                      // 鱼的精灵
    Animate* currentAnimation;           // 当前动画
    int moveDirection;                   // 鱼的移动方向 (1: 向右, -1: 向左)
    Vec2 initialPosition;                // 保存鱼的初始位置
    // 季节性鱼类映射
    static std::unordered_map<std::string, std::vector<std::string>> seasonFishMap;

    // 加载动画帧的辅助函数
    Vector<SpriteFrame*> loadFrames(const std::vector<std::string>& framePaths, const Rect& frameRect);
};

#endif // __FISH_H__
