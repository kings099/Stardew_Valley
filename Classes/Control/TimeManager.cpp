#include "TimeManager.h"

USING_NS_CC;



// 获取 TimeManager 的单例
TimeManager* TimeManager::getInstance() {
    static TimeManager* instance=nullptr;  // 单例指针
    if (instance == nullptr) {
        instance = new TimeManager();
    }
    return instance;
}

// 构造函数
TimeManager::TimeManager()
    : _timeInSeconds(INIT_HOUR), _day(INIT_DAY),_hour(INIT_HOUR), _minute(INIT_MIN), _season(INIT_SEASON), _isDay(INIT_IS_DAY), _weather(INIT_WEATHER) {
    // 初始化时间（从第1天的6:00开始）
    updateTime();
}

// 析构函数
TimeManager::~TimeManager() {
    // 如果需要，可以在此清理资源
}

// 更新游戏时间
void TimeManager::update(int deltaT) {
    // 每次调用时更新游戏时间，deltaT为现实世界的秒数
    _timeInSeconds += deltaT;

    // 防止 `timeInSeconds` 超过最大范围，使用模运算循环计时
    _timeInSeconds %= (HOURS_IN_A_DAY * DAYS_IN_A_YEAR); 

    updateTime();
    updateDayNightCycle();
    updateSeason();
}

// 获取当前星期几
std::string TimeManager::getWeekDay() const {
    std::string weekDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    return weekDays[(_day - 1) % DAYS_IN_A_WEEK];  // 将天数转化为星期几
}

// 获取当前时间（小时:分钟）格式的字符串
std::string TimeManager::getCurrentTime() const {
    // 返回当前时间（小时:分钟）格式
    return StringUtils::format("%02d:%02d", _hour, _minute);
}

// 获取当前季节
Season TimeManager::getCurrentSeason() const {
    return _season;
}

// 获取当前季节的字符串表示
std::string TimeManager::getCurrentSeasonStr() const {
    switch (_season) {
    case Spring:
        return "Spr";  // 春天
    case Summer:
        return "Sum";  // 夏天
    case Fall:
        return "Aut";  // 秋天
    case Winter:
        return "Win";  // 冬天
    default:
        return "Unknown";  // 默认返回未知
    }
}

// 获取当前日期
int TimeManager::getCurrentDay() const {
    return _day;
}

// 更新昼夜周期
void TimeManager::updateDayNightCycle() {
    // 根据时间来更新昼夜变化
    _isDay = (_hour >= DAY_START && _hour < DAY_END);
}

// 获取当前天气
Weather TimeManager::getCurrentWeather() const {
    return _weather;
}

// 获取当前天气的字符串表示
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

// 判断是否是白天
bool TimeManager::isDaytime() const {
    return _isDay;
}

// 启动时间更新
void TimeManager::startUpdating() {
    // 启动定时器，持续更新游戏时间
    auto scheduler = Director::getInstance()->getScheduler();

    // 使用调度器的 schedule 方法
    scheduler->schedule([this](float deltaTime) {
        update(1);  // 每秒更新时间，现实世界每秒等于游戏中1小时
        }, this, 1.0f, false, "timeUpdateKey");
}

// 停止时间更新
void TimeManager::stopUpdating() {
    // 停止时间更新
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule("_timeUpdateKey", this);
}

// 更新时间（小时、分钟、天数, 天气）
void TimeManager::updateTime() {
    // 通过计算更新小时、分钟、天数、季节等信息
    _hour = _timeInSeconds % HOURS_IN_A_DAY;  // 每24小时为1天
    _day = (_timeInSeconds / HOURS_IN_A_DAY) + 1;  // 每86400秒为1天
    _minute = 0;  // 每60秒为1分钟

    // 判断当前是白天还是黑夜
    _isDay = (_hour >= DAY_START && _hour < DAY_END); // 假设白天是早上6点到晚上6点

    if (_hour == 0 && _minute == 0) {  
        updateWeather();
    }
}


// 更新季节
void TimeManager::updateSeason() {
    // 每7天是一个季节变化 
    _season = static_cast<Season>((_day - 1) / DAYS_IN_A_SEASON % 4);  // 4季节循环：0 Spring, 1 Summer, 2 Fall, 3 Winter
}

// 更新天气
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


