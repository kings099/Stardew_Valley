#include "TimeManager.h"
#include "proj.win32/Constant.h"
USING_NS_CC;

// 初始化单例指针
TimeManager* TimeManager::instance = nullptr;

TimeManager* TimeManager::getInstance() {
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

TimeManager::TimeManager()
    : timeInSeconds(6), day(1), hour(6), minute(0), season(0), isDay(true) {
    // 初始化时间（从第1天的6:00开始）
    updateTime();
}

TimeManager::~TimeManager() {
    // 如果需要，可以在此清理资源
}

void TimeManager::update(int deltaT) {
    // 每次调用时更新游戏时间，deltaT为现实世界的秒数
    timeInSeconds += deltaT;  // 每秒更新时间，1秒 = 1小时的游戏时间
    updateTime();
    updateDayNightCycle();
    updateSeason();
}

void TimeManager::updateTime() {
    // 通过计算更新小时、分钟、天数、季节等信息
    minute = 0;  // 每60秒为1分钟
    hour = (timeInSeconds) % HOURS_IN_A_DAY;  // 每24小时为1天
    day = (timeInSeconds / HOURS_IN_A_DAY) + 1;  // 每86400秒为1天

    // 判断当前是白天还是黑夜
    isDay = (hour >= 6 && hour < 18); // 假设白天是早上6点到晚上6点
}

void TimeManager::updateDayNightCycle() {
    // 根据时间来更新昼夜变化
    if (hour >= 6 && hour < 18) {
        isDay = true;
    }
    else {
        isDay = false;
    }
}

void TimeManager::updateSeason() {
    // 每1天是一个季节变化
    season = (day - 1) % 4;  // 4季节循环：0 Spring, 1 Summer, 2 Fall, 3 Winter
}


std::string TimeManager::getWeekDay() const {
    // 返回当前星期几
    std::string weekDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    return weekDays[(day - 1) % 7];  // 将天数转化为星期几
}

std::string TimeManager::getCurrentTime() const {
    // 返回当前时间（小时:分钟）格式
    return StringUtils::format("%02d:%02d", hour, minute);
}

bool TimeManager::isDaytime() const {
    return isDay;
}

void TimeManager::startUpdating() {
    // 启动定时器，持续更新游戏时间
    auto scheduler = Director::getInstance()->getScheduler();

    // 使用调度器的 schedule 方法
    scheduler->schedule([=](float deltaTime) {
        update(1);  // 每秒更新时间，现实世界每秒等于游戏中1小时
        }, this, 1.0f, false, "timeUpdateKey");
}

void TimeManager::stopUpdating() {
    // 停止时间更新
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule("timeUpdateKey", this);
}
