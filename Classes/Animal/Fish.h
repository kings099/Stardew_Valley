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
#include "proj.win32/Constant.h"

USING_NS_CC;

class Fishs : public Node {
public:
    Fishs();
    virtual ~Fishs();
    //初始化每种季节对应的鱼的类型的关联容器
    static void initializeSeasonFishMap();

    //创建并返回一个新的 Fishs 对象。
    static Fishs* create(const std::string& name, const std::string& season, const Vec2& position);

    //初始化每条鱼的信息
    bool init(const std::string& name, const std::string& season, const Vec2& position);

    //设置每条鱼的自由移动范围
    void setActivityRange(float range);
    //获取当前鱼的种类类型
    std::string getFishImagePath() const;

    // 随机移动
    void moveRandomly(float deltaTime);

    // 更新动画
    void updateAnimation();

    // 捕获鱼
    static std::string catchFish(const Season season, int playerLevel);

private:
    std::string _name;                    // 鱼的名字
    std::string _season;                  // 当前季节
    Vec2 _position;                       // 当前鱼的位置
    float _activityRange;                 // 鱼的活动范围
    Sprite* _sprite;                      // 鱼的精灵
    Animate* _currentAnimation;           // 当前动画
    int _moveDirection;                   // 鱼的移动方向 (1: 向右, -1: 向左)
    Vec2 _initialPosition;                // 保存鱼的初始位置
    // 季节性鱼类映射
    static std::unordered_map<Season, std::vector<std::string>> _seasonFishMap;

    // 加载动画帧的辅助函数
    Vector<SpriteFrame*> loadFrames(const std::vector<std::string>& framePaths, const Rect& frameRect);
};

#endif // __FISH_H__
