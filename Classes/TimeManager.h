/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManager.h
 * File Function: 全局时间管理类的实现
 * Author:        达思睿
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#pragma once
#include <string>
#include "cocos2d.h"  // 引入 cocos2d 的头文件，用于显示时间标签等功能

class TimeManager {
public:
    static TimeManager* getInstance();  // 获取 TimeManager 的单例对象
    void update(int deltaT); // deltaT: 时间增量，单位为秒
    std::string getTimeString() const; // 获取当前时间的字符串表示（格式：小时:分钟）
    bool isDaytime() const; // 判断是否是白天

    void setTimeLabel(cocos2d::Label* label); // 设置时间显示标签（UI控件）

    void startUpdating(); // 启动时间更新
    void stopUpdating();  // 停止时间更新

private:
    TimeManager();  // 构造函数，初始化时间管理器
    ~TimeManager();  // 析构函数

    static TimeManager* instance;  // 单例对象
    int timeInSeconds; // 当前时间，单位为秒

    int day, hour, minute, season; // 当前的天数、小时、分钟和季节
    bool isDay;  // 当前是否是白天

    cocos2d::Label* timeLabel;  // 用于显示时间的标签控件

    void updateDayNightCycle(); // 更新昼夜循环
    void updateSeason(); // 更新季节
    void updateTime(); // 更新时间（包括小时、分钟等）

    void updateLabel(); // 更新时间显示标签
};
