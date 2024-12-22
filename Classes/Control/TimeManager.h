#pragma once
#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include "cocos2d.h"
#include "../proj.win32/Constant.h"

class TimeManager {
public:
    // 获取 TimeManager 的单例
    static TimeManager* getInstance();

    // 更新游戏时间
    void update(int deltaT);

    // 获取当前星期几（如：星期一、星期二）
    std::string getWeekDay() const;

    // 获取当前时间（小时:分钟）格式的字符串
    std::string getCurrentTime() const;

    // 获取当前季节
    Season getCurrentSeason() const;

    // 获取当前季节的字符串表示
    std::string getCurrentSeasonStr() const;

    // 获取当前游戏日
    int getCurrentDay() const;

    // 获取当前天气
    Weather getCurrentWeather() const;

    // 获取当前天气的字符串表示
    std::string getCurrentWeatherStr() const;

    // 判断是否是白天
    bool isDaytime() const;

    // 启动时间更新
    void startUpdating();

    // 停止时间更新
    void stopUpdating();

private:
    // 构造函数
    TimeManager();

    // 析构函数
    ~TimeManager(); 

    // 更新时间（小时、分钟、天数）
    void updateTime();

    // 更新昼夜周期
    void updateDayNightCycle();

    // 更新季节
    void updateSeason();

    // 更新天气
    void updateWeather();

    static TimeManager* instance;  // 单例指针

    int _timeInSeconds;  // 游戏总时间（秒）
    int _day;            // 当前游戏日
    int _hour;           // 当前小时
    int _minute;         // 当前分钟
    Season _season;      // 当前季节
    Weather _weather;    // 当前天气
    bool _isDay;         // 是否为白天
};

#endif // ! __TIMEMANAGER_H__