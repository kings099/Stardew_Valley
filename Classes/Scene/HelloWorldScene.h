/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     HelloScene.h
 * File Function: 游戏启动场景HelloScene的实现
 * Author:        达思睿
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    // 创建并返回 HelloWorld 场景
    static cocos2d::Scene* createScene();

    // 初始化 HelloWorld 场景
    virtual bool init();
  
    // 关闭游戏的回调函数
    void menuCloseCallback(cocos2d::Ref* pSender);

    // 创建并设置菜单项图片
    void createMenuWithImage();

    // 初始化背景
    void initBackground();
 
    // 退出游戏的回调函数
    void exitGameCallback(Ref* pSender);

    // 开始游戏的回调函数
    void startGameCallback(Ref* pSender);

    // 开始游戏后的处理
    void onGameStart();

    CREATE_FUNC(HelloWorld);

    void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


private:
    cocos2d::MenuItemImage* _startItem;  // "开始" 按钮
    cocos2d::MenuItemImage* _exitItem;   // "结束" 按钮
    cocos2d::Sprite* _titleSprite;        // 标题图像
    cocos2d::Layer* _loginLayer;
    
};

#endif // __HELLOWORLD_SCENE_H__
