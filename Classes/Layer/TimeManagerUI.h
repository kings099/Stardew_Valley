/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManagerUI.h
 * File Function: 显示时间信息和UI背景的类
 * Author:        达思睿
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#pragma once
#include "cocos2d.h"


class TimeManagerUI : public cocos2d::Layer
{
public:
    static TimeManagerUI* create();  // 创建 TimeManagerUI 对象
    virtual bool init() override;  // 初始化

    void updateTimeDisplay();  // 更新时间显示


private:
    cocos2d::Label* timeLabel1;  // 显示星期和日期的标签
    cocos2d::Label* timeLabel2;  // 显示白天/晚上和小时的标签
    cocos2d::Sprite* backgroundSprite;  // 用于作为UI背景的图片

    cocos2d::Size visibleSize;   // 可见区域的大小
};
