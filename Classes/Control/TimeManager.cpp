#include "TimeManager.h"

USING_NS_CC;



// ��ȡ TimeManager �ĵ���
TimeManager* TimeManager::getInstance() {
    static TimeManager* instance=nullptr;  // ����ָ��
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

// ���캯��
TimeManager::TimeManager()
    : _timeInSeconds(INIT_HOUR), _day(INIT_DAY),_hour(INIT_HOUR), _minute(INIT_MIN), _season(INIT_SEASON), _isDay(INIT_IS_DAY), _weather(INIT_WEATHER) {
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
    _timeInSeconds %= (HOURS_IN_A_DAY * DAYS_IN_A_YEAR); 

    updateTime();
    updateDayNightCycle();
    updateSeason();
}

// ��ȡ��ǰ���ڼ�
std::string TimeManager::getWeekDay() const {
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
std::string TimeManager::getCurrentSeasonStr() const {
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

// ������ҹ����
void TimeManager::updateDayNightCycle() {
    // ����ʱ����������ҹ�仯
    _isDay = (_hour >= DAY_START && _hour < DAY_END);
}

// ��ȡ��ǰ����
Weather TimeManager::getCurrentWeather() const {
    return _weather;
}

// ��ȡ��ǰ�������ַ�����ʾ
std::string TimeManager::getCurrentWeatherStr() const {
    switch (_weather) {
    case Sunny:
        return "Sunny";
    case Rainy:
        return "Rainy";
    case Dry:
        return "Dry";
    default:
        return "Unknown";
    }
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

// ����ʱ�䣨Сʱ�����ӡ�����, ������
void TimeManager::updateTime() {
    // ͨ���������Сʱ�����ӡ����������ڵ���Ϣ
    _hour = _timeInSeconds % HOURS_IN_A_DAY;  // ÿ24СʱΪ1��
    _day = (_timeInSeconds / HOURS_IN_A_DAY) + 1;  // ÿ86400��Ϊ1��
    _minute = 0;  // ÿ60��Ϊ1����

    // �жϵ�ǰ�ǰ��컹�Ǻ�ҹ
    _isDay = (_hour >= DAY_START && _hour < DAY_END); // �������������6�㵽����6��

    if (_hour == 0 && _minute == 0) {  
        updateWeather();
    }
}


// ���¼���
void TimeManager::updateSeason() {
    // ÿ7����һ�����ڱ仯 
    _season = static_cast<Season>((_day - 1) / DAYS_IN_A_SEASON % 4);  // 4����ѭ����0 Spring, 1 Summer, 2 Fall, 3 Winter
}

// ��������
void TimeManager::updateWeather() {
    int weather = rand() % 100 + 1;
    if (weather < SUNNY_PROBABILITY * 100) {
        _weather = Sunny;
    }
    else if (weather < (RAINY_PROBABILITY+SUNNY_PROBABILITY) * 100) {
        _weather = Rainy;
    }
    else if (weather < (DRY_PROBABILITY + RAINY_PROBABILITY + SUNNY_PROBABILITY) * 100) {
        _weather = Dry;
    }
}


