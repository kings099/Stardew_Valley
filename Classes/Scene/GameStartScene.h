/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameStartScene.h
 * File Function: 游戏启动场景类的实现
 * Author:        达思睿
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/

#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Layer/LoginLayer.h"
#include "ui/CocosGUI.h"
#include "Maps/FarmMap.h"
#include "Character/CharacterInfo.h"         
#include "Layer/AudioControlLayer.h"
#include "MenuImage/HoverMenuItemImage.h"

class GameStartScene : public cocos2d::Scene
{
public:
    // 创建并返回 游戏启动场景
    static cocos2d::Scene* createScene();

    // 初始化 游戏启动场景
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

    //创建 游戏启动场景
    CREATE_FUNC(GameStartScene);

private:
    cocos2d::MenuItemImage* _startItem;  // "开始" 按钮
    cocos2d::MenuItemImage* _exitItem;   // "结束" 按钮
    cocos2d::Sprite* _titleSprite;       // 标题图像
    cocos2d::Layer* _loginLayer;         // 登录界面
};

#endif // __GAMESTART_SCENE_H__