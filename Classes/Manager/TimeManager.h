#pragma once
#include <string>
#include "cocos2d.h"  // 包含 cocos2d 的相关头文件，用于显示时间标签等

class TimeManager {
public:
    static TimeManager* getInstance();  // 获取 TimeManager 的单例
    void update(int deltaT); // deltaT: 时间增量，单位秒
    std::string getTimeString() const; // 获取当前时间的字符串形式（小时:分钟）
    bool isDaytime() const; // 判断是否是白天

    void setTimeLabel(cocos2d::Label* label); // 设置时间标签（外部传入）

    void startUpdating(); // 启动时间更新
    void stopUpdating();  // 停止时间更新

private:
    TimeManager();  // 私有构造函数，避免外部实例化
    ~TimeManager();  // 析构函数

    static TimeManager* instance;  // 单例指针
    int timeInSeconds; // 当前时间，以秒为单位
   

    int day, hour, minute, season; // 当前的天数、小时、分钟、季节
    bool isDay;  // 当前是白天还是夜晚

    cocos2d::Label* timeLabel;  // 用于显示时间的标签指针

    void updateDayNightCycle(); // 更新昼夜变化
    void updateSeason(); // 更新季节变化
    void updateTime(); // 更新时间（小时、分钟）

    void updateLabel(); // 更新时间显示标签
};
