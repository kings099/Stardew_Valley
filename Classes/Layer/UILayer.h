/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI界面UILayer类的定义
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Control/TimeManager.h"
#include "Classes/MenuImage/HoverMenuItemImage.h"
#include "Classes/Layer/PlacementMarkerLayer.h"
#include "../proj.win32/Constant.h"

class UILayer : public cocos2d::Layer {
public:
	// 构造函数
	UILayer();

	// 析构函数
	~UILayer();

	// 初始化UI层
	virtual bool init();

	// 按下鼠标事件触发函数
	void onMouseDown(cocos2d::Event* event);

	// 移动鼠标事件触发函数
	void onMouseMove(cocos2d::Event* event);

	// 释放鼠标事件触发函数
	void onMouseUp(cocos2d::Event* event);

	// 按下键盘事件触发函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 初始化物品栏
	void initializeObjectList();

	// 更新物品栏
	void updateObjectList();

	// 显示物品图片
	void showObjectImage();

	// 初始化时间显示器
	void initializeTimeDisplay();

	// 更新时间显示器
	void updateTimeDisplay();

	// 更新UI界面
	void update(float deltaTime);

	// UILayer的create函数
	CREATE_FUNC(UILayer);

private:
	Character* character;															// 角色指
	cocos2d::Size visibleSize;														// 可见区域的大小
	cocos2d::Label* timeLabel1;														// 显示星期和日期的标签指针
	cocos2d::Label* timeLabel2;														// 显示白天/晚上和小时的标签指针
	cocos2d::Sprite* timeDisplayLayer;												// 用作为时间显示器背景的图片指针
	cocos2d::Sprite* closedobjectListLayer;											// 物品栏关闭状态图片指针
	cocos2d::Sprite* openedobjectListLayer;											// 物品栏打开状态图片指针
	cocos2d::Sprite* closedObjectSpriteImage[OBJECT_LIST_COLS];						// 物品栏关闭时显示的物品图片指针
	cocos2d::Sprite* openedObjectSpriteImage[OBJECT_LIST_COLS * OBJECT_LIST_ROWS];	// 物品栏打开时显示的物品图片指针
	cocos2d::Sprite* selectObjectSpriteMarker[OBJECT_LIST_COLS];					// 选中物品的标记指针
	cocos2d::Sprite* nearestPlacementMarker;										// 最近放置标记指针
	cocos2d::Sprite* selectedObjectSprite;											// 当前选中的对象
	HoverMenuItemImage *deleteObjectButton;											// 删除物品按钮
	HoverMenuItemImage *closeObjectListButton;										// 关闭物品栏按钮
	PlacementMarkerLayer* placementMarkerLayer;										// 放置标记层类指针
	bool objectListStatus;															// 物品栏状态
	bool lastObjectListStatus;														// 上一次物品栏状态
	int lastSelectedObjectIndex;													// 上一次物品栏索引
	int startLocation;																// 起始位置
	// 寻找最近可放置坐标
	cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* objectSprite);

	// 设置选中物品标记框的显示状态
	void setSelectObjectSpriteMarker(int index, bool show);
};

#endif // !_UILAYER_H_


