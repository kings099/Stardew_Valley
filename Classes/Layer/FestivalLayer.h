/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FestivalLayer.h
 * File Function: 节日活动UI层的声明
 * Author:        达思睿
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FESTIVALLAYER_H
#define FESTIVALLAYER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"  // 引入Cocos2d UI组件
#include "ChatLayer.h"    // 引入ChatLayer类
#include "Control/TimeManager.h"  // 引入TimeManager类

class FestivalLayer : public cocos2d::Layer {
public:
    FestivalLayer();  // 构造函数
    ~FestivalLayer();  // 析构函数

    // 初始化函数
    bool init();

    // 创建并返回一个FestivalLayer实例
    static FestivalLayer* create();

    // 更新按钮的显示状态
    void updateFestivalButtonVisibility();
    void  updateCommunityButtonVisibility();
    void onButtonClicked(Ref* pSender, const std::string& message);



private:
    // 节日按钮
    cocos2d::ui::Button* _festivalButton;
    cocos2d::ui::Button* _communityButton;
    // 按钮点击回调，显示对话框
    void onFestivalButtonClicked(cocos2d::Ref* pSender);
};

#endif // FESTIVALLAYER_H
