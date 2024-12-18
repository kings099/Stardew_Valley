/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animal.h
 * File Function: 小动物类，实现小动物的各种基本操作
 * Author:        胡宝怡
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <unordered_map>
#include <string>
#include <vector>

USING_NS_CC;

class Animal : public Node {

    
protected:
    std::string type;   // 动物类型 (如：chicken、cow、sheep)
    float affection;    // 动物的好感度
    bool isFed;         // 是否喂养
    float lastFedTime;  // 最后喂养时间
    float affectionDecayRate; // 好感度衰减速率
    float maxAffection;    // 最大好感度

    Sprite* sprite;   // 动物的精灵
    Action* currentAnimation; // 当前播放的动画
    
    Vec2 position;     // 动物的当前坐标
    Vec2 origin;       // 创建小动物时指定的原点 (正方形的左下角)
    float areaSize;    // 正方形区域的大小 (20x20)

    // 动物的资源映射
    static std::unordered_map<std::string, std::vector<std::string>> resourceMap;
    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> animationMap;

public:
    Vec2 direction;
    Animal();
    ~Animal();
    void setDirection(const Vec2& dir);
    // 初始化资源
    static void initializeResourceMap();
    static void initializeAnimationMap();

    // 创建动物实例
    static Animal* create(const std::string& type, const Vec2& startPosition);
    bool init(const std::string& type, const Vec2& startPosition);
    // 喂养动物
    void feed();

    // 更新好感度
    void updateAffection(float deltaTime);

    // 判断动物是否发狂
    bool isAngry() const;

    // 动物发狂时的处理
    void handleAngry();

    // 获取动物当前好感度
    float getAffection() const;

    // 获取动物类型
    const std::string& getType() const;

    // 设置动物的随机移动
    void setRandomMovement(float deltaTime);
    void startRandomMovement();
    // 播放方向动画
    void playDirectionAnimation(const std::string& direction, int repeatCount);
};

#endif // ANIMAL_H
