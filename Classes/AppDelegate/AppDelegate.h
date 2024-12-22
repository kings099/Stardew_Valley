/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AppDelegate.h
 * File Function: Main function of the game.
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    //析构函数
    virtual ~AppDelegate();

    //初始化 OpenGL 上下文属性
    virtual void initGLContextAttrs();

    // 当应用程序完成启动并准备进入主循环时调用此函数
    virtual bool applicationDidFinishLaunching();

    // 当应用程序进入后台时调用此函数
    virtual void applicationDidEnterBackground();

    // 当应用程序从后台返回到前台时调用此函数
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

