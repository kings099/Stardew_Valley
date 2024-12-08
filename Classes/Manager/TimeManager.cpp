#include "TimeManager.h"
#include"proj.win32/Constant.h"
USING_NS_CC;

// ��ʼ������ָ��
TimeManager* TimeManager::instance = nullptr;

TimeManager* TimeManager::getInstance() {
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

TimeManager::TimeManager()
    : timeInSeconds(0), day(1), hour(6), minute(0), season(0), isDay(true), timeLabel(nullptr) {
    // ��ʼ��ʱ�䣨�ӵ�1���6:00��ʼ��
    updateTime();
}

TimeManager::~TimeManager() {
    // �����Ҫ�������ڴ�������Դ
}

void TimeManager::update(int deltaT) {
    // ÿ�ε���ʱ������Ϸʱ�䣬deltaTΪ��ʵ���������
    timeInSeconds += deltaT;  // ÿ�����ʱ�䣬1�� = 1Сʱ����Ϸʱ��
    updateTime();
    updateDayNightCycle();
    updateSeason();
    updateLabel(); // ����ʱ����ʾ��ǩ
}

void TimeManager::updateTime() {
    // ͨ���������Сʱ�����ӡ����������ڵ���Ϣ
    //ʾ�����������޸�
    minute = 0;  // ÿ60��Ϊ1����
    hour = (timeInSeconds) % HOURS_IN_A_DAY;  // ÿ24СʱΪ1��
    day = (timeInSeconds / HOURS_IN_A_DAY) + 1;  // ÿ86400��Ϊ1��

    // �жϵ�ǰ�ǰ��컹�Ǻ�ҹ
    isDay = (hour >= 6 && hour < 18); // �������������6�㵽����6��

    // ���¼��ڣ�ÿһ��Ϊһ�����ڣ�
    updateSeason();
}

void TimeManager::updateDayNightCycle() {
    // ����ʱ����������ҹ�仯
    if (hour >= 6 && hour < 18) {
        isDay = true;
    }
    else {
        isDay = false;
    }
}

void TimeManager::updateSeason() {
    // ÿ1����һ�����ڱ仯
    season = (day - 1) % 4;  // 4����ѭ����0 Spring, 1 Summer, 2 Fall, 3 Winter
}

void TimeManager::updateLabel() {
    if (timeLabel != nullptr) {
        // ����ʱ����ʾ��ǩ����ʽ��Season, Day, Hour
        timeLabel->setString(getTimeString());
    }
}

std::string TimeManager::getTimeString() const {
    // ����ʱ����ַ�����ʾ����ʽΪ��Season, Day, Hour
    std::string seasonNames[] = { "Spring", "Summer", "Fall", "Winter" };
    return StringUtils::format("Season: %s, Day %d, %02d:%02d", seasonNames[season].c_str(), day, hour, minute);
}

bool TimeManager::isDaytime() const {
    return isDay;
}

void TimeManager::setTimeLabel(Label* label) {
    timeLabel = label;  // ����ʱ����ʾ��ǩ
}

void TimeManager::startUpdating() {
    // ������ʱ��������������Ϸʱ��
    auto scheduler = Director::getInstance()->getScheduler();

    // ʹ�õ������� schedule ����
    scheduler->schedule([=](float deltaTime) {
        update(1);  // ÿ�����ʱ�䣬��ʵ����ÿ�������Ϸ��1Сʱ
        }, this, 1.0f, false, "timeUpdateKey");
}

void TimeManager::stopUpdating() {
    // ֹͣʱ�����
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule("timeUpdateKey", this);
}
