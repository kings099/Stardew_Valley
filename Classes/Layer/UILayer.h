/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI界面UILayer类的定义
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/9
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Manager/TimeManager.h"
#include "Classes/MenuImage/HoverMenuItemImage.h"
#include "../proj.win32/ObjectConstant.h"

class UILayer : public cocos2d::Layer {
public:
	// 析构函数
	~UILayer();

	// 初始化UI层
	virtual bool init();

	// 初始化物品栏
	void initializeObjectList();

	// 更新物品栏
	void updateObjectList();

	// 初始化时间显示器
	void initializeTimeDisplay();

	// 更新时间显示器
	void updateTimeDisplay();

	// 更新UI界面
	void update(float deltaTime);

	// UILayer的create函数
	CREATE_FUNC(UILayer);

private:
	Character* character;							// 角色层
	cocos2d::Size visibleSize;						// 可见区域的大小

	cocos2d::Label* timeLabel1;						// 显示星期和日期的标签
	cocos2d::Label* timeLabel2;						// 显示白天/晚上和小时的标签
	cocos2d::Sprite* timeDisplayLayer;				// 用作为UI背景的图片

	cocos2d::Sprite* objectListLayer = nullptr;			// 物品栏状态
	HoverMenuItemImage *deleteObjectButton = nullptr;	// 删除物品按钮
	HoverMenuItemImage *closeObjectListButton = nullptr;	// 关闭物品栏按钮
};

#endif // !_UILAYER_H_


