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
#include "proj.win32/Constant.h"

USING_NS_CC;

class Animal : public Node {
    
protected:
    Sprite* _angryIcon; // 动物发怒的图标
    std::string _type;   // 动物类型
    float _affection;    // 动物的好感度
    float _previousAffection;  // 昨天的好感度
    float _secondLastAffection;  // 前天的好感度
    bool _isFed;         // 是否被喂食
    float _lastFedTime;  // 上次喂食的时间
    float _affectionDecayRate; // 好感度衰减速度
    float _maxAffection;    // 最大好感度
    int currentEggCount;  // 当前蛋的数量
    Sprite* _sprite;   // 动物的精灵
    Action* _currentAnimation; // 当前正在播放的动画

    Vec2 _position;     // 动物当前位置
    Vec2 _origin;       // 动物初始化时的原点 (地图的左下角坐标)
    float _areaSize;    // 动物活动范围的大小 (例如20x20范围)

    static std::unordered_map<std::string, std::vector<std::string>> _resourceMap;
    // 静态资源映射表，用于存储动物类型与其资源路径的对应关系

    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> _animationMap;
    // 静态动画映射表，用于存储动物类型、动作方向和对应动画资源的映射

public:
    Vec2 _direction; // 动物当前的移动方向

    Animal(); // 构造函数
    ~Animal(); // 析构函数

    // 初始化资源映射表
    static void initializeResourceMap();

    // 初始化动画映射表
    static void initializeAnimationMap();

    // 创建动物实例
    static Animal* create(const std::string& type, const Vec2& startPosition);

    // 初始化动物信息
    bool init(const std::string& type, const Vec2& startPosition);

    // 喂食动物
    void feed();

    // 更新好感度
    void updateAffection(float deltaTime);
   
    // 判断动物是否发怒
    bool isAngry() const;

    // 处理动物发怒时的逻辑
    void handleAngry();

    // 获取动物当前的好感度
    float getAffection() const;

    // 获取动物类型
    const std::string& getType() const;

    // 设置动物的随机移动
    void setRandomMovement(float deltaTime);

    // 播放方向动画
    void playDirectionAnimation(const std::string& direction, int repeatCount);
    //下蛋函数
    void layEgg();
};

#endif // ANIMAL_H
