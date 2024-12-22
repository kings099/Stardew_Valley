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
#include "proj.win32/Constant.h"
#include "CropData.h"

class Crops : public cocos2d::Node {
public:
   

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
    std::string getType() const { return _type; }

    // 获取当前生长阶段
    int getGrowthStage() const { return _growthStage; }

    // 新增：施肥函数
    void fertilize();

    //新增管理病虫害
    void checkPests();     // 检查病虫害
    void treatPests();     // 治疗病虫害
    //通过天气管理浇水
    void manageDrought(Weather currentWeather);
    // 其他成员函数和变量
    static void setPlayerLevel(int level); // 设置人物等级
    // 判断是否能种植当前农作物
    static bool canBePlanted(const std::string& cropType);
    // 创建农作物时检查是否可以种植
    static Crops* create(const std::string& type, int maxGrowthStage);
    void chopTree();                       //砍树
    void harvestCrop();

    static void setSeason(Season season); // 设置季节
    static Season getSeason();           // 获取当前季节
    bool _isRemoved = false;
    // 玩家等级
    static int _playerLevel;
    // 返回 CropData
    CropData getCropData();

private:
    bool _isFertilized;         //是否施肥
    std::string _type;          // 农作物类型
    int _growthStage;           // 当前生长阶段
    int _maxGrowthStage;        // 最大生长阶段
    float _growthTimer;         // 生长计时器
    bool _isWatered;            // 是否被浇水
    int _daysWithoutWater;       //没有被浇水的天数
    bool _hasPests;         // 标记是否有病虫害
    float _pestProbability; // 感染病虫害的概率
    cocos2d::Sprite* _sprite;   // 农作物的显示精灵
    CropData _cropData;         //农作物的基本信息
    // 静态成员：季节和生长周期表
    static Season _currentSeason;
    static std::unordered_map<std::string, std::unordered_map<Season, float>> _growthCycles;

    // 用于存储不同季节下农作物成熟阶段的图片
    static std::unordered_map<std::string, std::unordered_map<Season, std::string>> _matureTextures;

    // 静态资源映射表
    static std::unordered_map<std::string, std::vector<std::string>> _resourceMap;

    // 加载资源表
    static void initializeResourceMap();
   
};

#endif // __CROP_H__

