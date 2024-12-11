/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManagerUI.cpp
 * File Function: 显示时间信息和UI背景的类实现
 * Author:        达思睿
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#include "TimeManagerUI.h"
#include "Manager/TimeManager.h"
#include"../proj.win32/Constant.h"
USING_NS_CC;

TimeManagerUI* TimeManagerUI::create()
{
    TimeManagerUI* ret = new TimeManagerUI();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool TimeManagerUI::init()
{
    if (!Layer::init())
    {
        return false;
    }
    // 获取可见区域大小
    visibleSize = Director::getInstance()->getVisibleSize();

    // 计算右上角的位置
    Vec2 rightTopPos = Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f);  // 右上角，调整到合适的偏移量

    // 创建背景图片
    backgroundSprite = Sprite::create("../Resources/UI/timetable.png");  // 背景图片路径
    // 获取原始图片尺寸
    Size originalSize = backgroundSprite->getContentSize();

    // 计算缩放比例，使得图片适应 16x16 像素
    float scaleX = UI_SCALE / originalSize.width;  // 计算 X 方向的缩放比例
    float scaleY = UI_SCALE / originalSize.height; // 计算 Y 方向的缩放比例

    // 设置缩放比例
    backgroundSprite->setScale(scaleX, scaleY);

    // 设置背景图片位置
    backgroundSprite->setPosition(rightTopPos);

    // 添加到场景
    this->addChild(backgroundSprite, 0);  // 背景在底层

    // 计算标签的位置，使其相对于背景位置
    Vec2 labelPos1 = Vec2(visibleSize.width*0.5, visibleSize.height * 0.5);  // 在背景图片的顶部
    Vec2 labelPos2 = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5-30); ;  // 在 labelPos1 下面偏移 30

    // 创建并初始化 timeLabel1 和 timeLabel2
    timeLabel1 = Label::createWithSystemFont("111111111111111111111", "Arial", FONT_SIZE);
    timeLabel1->setPosition(labelPos1);  // 设置 timeLabel1 相对于背景图片顶部的位置
    this->addChild(timeLabel1, 1);  // 标签在背景上面

    timeLabel2 = Label::createWithSystemFont("1111111111111111111111", "Arial", FONT_SIZE);
    timeLabel2->setPosition(labelPos2);  // 设置 timeLabel2 相对于 timeLabel1 的位置
    this->addChild(timeLabel2, 1);  // 标签在背景上面

    // 初始化时显示时间
    updateTimeDisplay();

    // 每秒更新一次
    schedule([this](float deltaTime) {
        updateTimeDisplay();
        }, 1.0f, "updateTimeDisplayKey");

    return true;
}

void TimeManagerUI::updateTimeDisplay()
{
    // 获取 TimeManager 的实例
    TimeManager* timeManager = TimeManager::getInstance();

    // 获取并更新日期信息（星期和日期）
    std::string weekDay = timeManager->getWeekDay();  // 假设 TimeManager 类有 getWeekDay() 方法
    timeLabel1->setString(weekDay);  // 显示星期几  的代码部分

    // 获取并更新时间信息（白天/晚上和当前时间）
    bool isDaytime = timeManager->isDaytime();
    std::string dayOrNight = isDaytime ? "白天" : "晚上";  // 判断是否是白天或晚上
    std::string timeOfDay = timeManager->getCurrentTime();  // 假设 TimeManager 类有 getCurrentTime() 方法
    timeLabel2->setString(dayOrNight + " " + timeOfDay);  // 显示白天/晚上和当前时间  的代码部分
}
