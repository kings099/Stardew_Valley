/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LoginLayer.h
 * File Function: 用户登录UI层的定义
 * Author:        达思睿
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __LOGIN_LAYER_H__
#define __LOGIN_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

class LoginLayer : public Layer
{
public:
    // 构造函数
    LoginLayer();
    virtual ~LoginLayer();

    // 创建函数
    static LoginLayer* create();

    // 初始化函数
    bool init();

    // 提交按钮回调
    void onSubmitClicked(Ref* sender);


private:
    // 输入框控件
    cocos2d::ui::TextField* usernameInput;
    cocos2d::ui::TextField* farmNameInput;
    cocos2d::ui::TextField* favoriteInput;

    // 按钮控件
    cocos2d::ui::Button* submitButton;

    // 登录界面层
    LayerColor* loginLayer;
};

#endif // __LOGIN_LAYER_H__
