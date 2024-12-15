/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: 农作物类的头文件
 * Author:        胡宝怡
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"

class Crop : public cocos2d::Node {
public:
    static Crop* create(const std::string& type, int maxGrowthStage);

    // 初始化农作物
    bool init(const std::string& type, int maxGrowthStage);

    // 更新生长逻辑
    void updateGrowth(float deltaTime);

    // 浇水逻辑
    void waterCrop();

    // 判断是否可以收获
    bool isReadyToHarvest() const;

    // 设置生长阶段
    void setGrowthStage(int stage);

    // 获取农作物类型
    std::string getType() const { return type; }

    // 获取当前生长阶段
    int getGrowthStage() const { return growthStage; }

    //除草动画cocos2d::
    void playWeedingAnimation(const cocos2d::Vec2& position, cocos2d::TMXTiledMap* farmMap);
    //碎石动画
    void playStoneBreakingAnimationAt(const cocos2d::Vec2& position, cocos2d::TMXTiledMap* farmMap);
    // 新增：施肥函数
    void fertilize();

private:
    bool isFertilized;         //是否施肥
    std::string type;          // 农作物类型
    int growthStage;           // 当前生长阶段
    int maxGrowthStage;        // 最大生长阶段
    float growthTimer;         // 生长计时器
    bool isWatered;            // 是否被浇水
    int daysWithoutWater;       //没有被浇水的天数
    // 静态资源映射表
    static std::unordered_map<std::string, std::vector<std::string>> resourceMap;

    // 加载资源表
    static void initializeResourceMap();
    cocos2d::Sprite* sprite;   // 农作物的显示精灵
};

#endif // __CROP_H__

