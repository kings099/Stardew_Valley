/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManager.cpp
 * File Function: 全局时间管理类的实现
 * Author:        达思睿
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#include "TimeManager.h"
#include "cocos2d.h"  // 引入 cocos2d 的头文件，用于显示时间标签等功能

USING_NS_CC;

// 初始化单例对象为 nullptr
TimeManager* TimeManager::instance = nullptr;

TimeManager* TimeManager::getInstance() {
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

TimeManager::TimeManager()
    : timeInSeconds(0), day(1), hour(6), minute(0), season(0), isDay(true) {
    // 初始化时间（从第1天的6:00开始）
    updateTime();
}

TimeManager::~TimeManager() {
    // 清理资源，如果需要的话
}

void TimeManager::update(int deltaT) {
    // 每次调用时更新游戏时间，deltaT为实际经过的秒数
    timeInSeconds += deltaT;  // 每秒更新时间，1秒 = 游戏内1小时
    updateTime();
    updateDayNightCycle();
    updateSeason();
}

void TimeManager::updateTime() {
    // 通过计算更新小时、分钟、天数、季节等信息
    minute = 0;  // 每60秒为1分钟
    hour = (timeInSeconds) % 24;  // 每24小时为1天
    day = (timeInSeconds / (24)) + 1;  // 每1440分钟为1天

    // 判断当前是白天还是夜晚
    isDay = (hour >= 6 && hour < 18); // 假设白天是早上6点到晚上6点
}

void TimeManager::updateDayNightCycle() {
    // 根据时间来更新白天/黑夜状态
    if (hour >= 6 && hour < 18) {
        isDay = true;
    }
    else {
        isDay = false;
    }
}

void TimeManager::updateSeason() {
    // 每7天是一个季节变化
    season = (day - 1) / 7 % 4;  // 4季循环：0 春天, 1 夏天, 2 秋天, 3 冬天
}

std::string TimeManager::getWeekday(){
    // 获取星期几的名称
    std::string weekdays[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };
    return weekdays[(day - 1) % 7];  // 每7天循环一次
}

int TimeManager::getDay() {
    return day;
}
int TimeManager::getHour() {
    return hour;
}
void TimeManager::startUpdating() {
    // 启动定时器，持续更新游戏时间
    auto scheduler = Director::getInstance()->getScheduler();

    // 使用调度器的 schedule 方法
    scheduler->schedule([=](float deltaTime) {
        update(1);  // 每秒更新时间，现实世界每秒等于游戏中1分钟
        }, this, 1.0f, false, "timeUpdateKey");
}

void TimeManager::stopUpdating() {
    // 停止时间更新
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule("timeUpdateKey", this);
}


