#include "TimeManager.h"
#include"proj.win32/Constant.h"
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
    : timeInSeconds(0), day(1), hour(6), minute(0), season(0), isDay(true), timeLabel(nullptr) {
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
    updateLabel(); // 更新时间显示标签
}

void TimeManager::updateTime() {
    // 通过计算更新小时、分钟、天数、季节等信息
    //示例，后续会修改
    minute = 0;  // 每60秒为1分钟
    hour = (timeInSeconds) % HOURS_IN_A_DAY;  // 每24小时为1天
    day = (timeInSeconds / HOURS_IN_A_DAY) + 1;  // 每86400秒为1天

    // 判断当前是白天还是黑夜
    isDay = (hour >= 6 && hour < 18); // 假设白天是早上6点到晚上6点

    // 更新季节（每一天为一个季节）
    updateSeason();
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

void TimeManager::updateLabel() {
    if (timeLabel != nullptr) {
        // 设置时间显示标签，格式：Season, Day, Hour
        timeLabel->setString(getTimeString());
    }
}

std::string TimeManager::getTimeString() const {
    // 返回时间的字符串表示，格式为：Season, Day, Hour
    std::string seasonNames[] = { "Spring", "Summer", "Fall", "Winter" };
    return StringUtils::format("Season: %s, Day %d, %02d:%02d", seasonNames[season].c_str(), day, hour, minute);
}

bool TimeManager::isDaytime() const {
    return isDay;
}

void TimeManager::setTimeLabel(Label* label) {
    timeLabel = label;  // 设置时间显示标签
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
