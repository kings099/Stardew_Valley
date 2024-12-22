/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: 农作物类头文件
 * Author:        胡宝怡
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "CropData.h"

class Crops : public cocos2d::Node {
public:
    // 初始化农作物
    bool init(const std::string& type, int maxGrowthStage);

    // 更新生长逻辑
    void updateGrowth(float deltaTime);

    // 给农作物浇水
    void waterCrop();

    // 判断是否可以收获
    bool isReadyToHarvest() const;

    // 设置农作物的生长阶段
    void setGrowthStage(int stage);

    // 获取农作物类型
    std::string getType() const { return _type; }

    // 获取当前的生长阶段
    int getGrowthStage() const { return _growthStage; }

    // 施肥
    void fertilize();

    // 检查是否有害虫
    void checkPests();

    // 处理害虫
    void treatPests();

    // 根据当前天气管理干旱
    void manageDrought(Weather currentWeather);

    // 设置玩家等级
    static void setPlayerLevel(int level);

    // 判断是否可以种植特定类型的农作物
    static bool canBePlanted(const std::string& cropType);

    // 创建农作物实例
    static Crops* create(const std::string& type, int maxGrowthStage);

    // 砍树
    void chopTree();

    // 农作物收获
    void harvestCrop();

    // 设置季节
    static void setSeason(Season season);

    // 获取当前季节
    static Season getSeason();

    // 标记是否被移除
    bool _isRemoved = false;

    // 玩家等级
    static int _playerLevel;

    // 获取农作物数据
    CropData getCropData();

private:
    bool _isFertilized;         // 是否施肥
    std::string _type;          // 农作物类型
    int _growthStage;           // 当前生长阶段
    int _maxGrowthStage;        // 最大生长阶段
    float _growthTimer;         // 生长计时器
    bool _isWatered;            // 是否浇水
    int _daysWithoutWater;      // 缺水的天数
    bool _hasPests;             // 是否有害虫
    float _pestProbability;     // 害虫发生的概率
    cocos2d::Sprite* _sprite;   // 农作物的显示精灵

    CropData _cropData;         // 农作物数据

    // 静态变量：当前季节
    static Season _currentSeason;

    // 静态变量：存储各季节的农作物生长周期
    static std::unordered_map<std::string, std::unordered_map<Season, float>> _growthCycles;

    // 静态变量：存储不同季节的成熟纹理
    static std::unordered_map<std::string, std::unordered_map<Season, std::string>> _matureTextures;

    // 静态变量：存储农作物资源的映射
    static std::unordered_map<std::string, std::vector<std::string>> _resourceMap;

    // 初始化资源映射
    static void initializeResourceMap();

};

#endif // __CROP_H__
