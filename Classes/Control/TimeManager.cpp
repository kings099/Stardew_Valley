#include "TimeManager.h"
#include "proj.win32/Constant.h"
USING_NS_CC;

// ��ʼ������ָ��
TimeManager* TimeManager::instance = nullptr;

// ��ȡ TimeManager �ĵ���
TimeManager* TimeManager::getInstance() {
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

// ���캯��
TimeManager::TimeManager()
    : _timeInSeconds(INIT_HOUR), _day(INIT_DAY),_hour(INIT_HOUR), _minute(INIT_MIN), _season(INIT_SEASON), _isDay(INIT_IS_DAY) {
    // ��ʼ��ʱ�䣨�ӵ�1���6:00��ʼ��
    updateTime();
}

// ��������
TimeManager::~TimeManager() {
    // �����Ҫ�������ڴ�������Դ
}

// ������Ϸʱ��
void TimeManager::update(int deltaT) {
    // ÿ�ε���ʱ������Ϸʱ�䣬deltaTΪ��ʵ���������
    _timeInSeconds += deltaT;

    // ��ֹ `timeInSeconds` �������Χ��ʹ��ģ����ѭ����ʱ
    _timeInSeconds %= (HOURS_IN_A_DAY * DAYS_IN_A_YEAR); // ����Ϊһ���ڵ�������

    updateTime();
    updateDayNightCycle();
    updateSeason();
}

// ��ȡ��ǰ���ڼ����磺����һ�����ڶ���
std::string TimeManager::getWeekDay() const {
    // ���ص�ǰ���ڼ�
    std::string weekDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    return weekDays[(_day - 1) % DAYS_IN_A_WEEK];  // ������ת��Ϊ���ڼ�
}

// ��ȡ��ǰʱ�䣨Сʱ:���ӣ���ʽ���ַ���
std::string TimeManager::getCurrentTime() const {
    // ���ص�ǰʱ�䣨Сʱ:���ӣ���ʽ
    return StringUtils::format("%02d:%02d", _hour, _minute);
}

// ��ȡ��ǰ����
Season TimeManager::getCurrentSeason() const {
    return _season;
}


// ��ȡ��ǰ���ڵ��ַ�����ʾ
std::string TimeManager::getCurrentSeason_() const {
    switch (_season) {
    case Spring:
        return "Spr";  // ����
    case Summer:
        return "Sum";  // ����
    case Fall:
        return "Aut";  // ����
    case Winter:
        return "Win";  // ����
    default:
        return "Unknown";  // Ĭ�Ϸ���δ֪
    }
}

// ��ȡ��ǰ����
int TimeManager::getCurrentDay() const {
    return _day;
}

// �ж��Ƿ��ǰ���
bool TimeManager::isDaytime() const {
    return _isDay;
}

// ����ʱ�����
void TimeManager::startUpdating() {
    // ������ʱ��������������Ϸʱ��
    auto scheduler = Director::getInstance()->getScheduler();

    // ʹ�õ������� schedule ����
    scheduler->schedule([this](float deltaTime) {
        update(1);  // ÿ�����ʱ�䣬��ʵ����ÿ�������Ϸ��1Сʱ
        }, this, 1.0f, false, "timeUpdateKey");
}

// ֹͣʱ�����
void TimeManager::stopUpdating() {
    // ֹͣʱ�����
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule("_timeUpdateKey", this);
}

// ����ʱ�䣨Сʱ�����ӡ�������
void TimeManager::updateTime() {
    // ͨ���������Сʱ�����ӡ����������ڵ���Ϣ
    _hour = _timeInSeconds % HOURS_IN_A_DAY;  // ÿ24СʱΪ1��
    _day = (_timeInSeconds / HOURS_IN_A_DAY) + 1;  // ÿ86400��Ϊ1��
    _minute = 0;  // ÿ60��Ϊ1����

    // �жϵ�ǰ�ǰ��컹�Ǻ�ҹ
    _isDay = (_hour >= DAY_START && _hour < DAY_END); // �������������6�㵽����6��
}

// ��ȡ��ǰ����
void TimeManager::updateDayNightCycle() {
    // ����ʱ����������ҹ�仯
    _isDay = (_hour >= DAY_START && _hour < DAY_END);
}

// ���¼���
void TimeManager::updateSeason() {
    // ÿ7����һ�����ڱ仯 
    _season = static_cast<Season>((_day - 1) / DAYS_IN_A_SEASON % 4);  // 4����ѭ����0 Spring, 1 Summer, 2 Fall, 3 Winter
}


