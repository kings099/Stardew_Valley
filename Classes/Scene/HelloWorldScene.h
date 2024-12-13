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
//#include "GameTime.h"
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void createMenuWithImage();

    void initBackground();
    // exitGameCallback: 当点击“结束”按钮时，调用此函数
    void exitGameCallback(Ref* pSender);
    void startGameCallback(Ref* pSender);
    // implement the "static create()" method manually
    void onGameStart();
    CREATE_FUNC(HelloWorld);
    void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


private:
    cocos2d::MenuItemImage* startItem;  // "开始" 按钮
    cocos2d::MenuItemImage* exitItem;   // "结束" 按钮
    cocos2d::Sprite* titleSprite;        // 标题图像
    cocos2d::Layer* loginLayer;
    //GameTime* gameTime;  // 成员变量
};

#endif // __HELLOWORLD_SCENE_H__
