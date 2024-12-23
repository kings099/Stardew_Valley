/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI界面UILayer类的定义
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/18
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
#include "Classes/Box/Box.h"
#include "Store/Store.h"
#include "../proj.win32/Constant.h"

class UILayer : public cocos2d::Layer {
public:
	// 构造函数
	UILayer();

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

	// 初始化技能板
	void initializeSkillBoard();

	// 初始化时间显示器
	void initializeTimeDisplay();

	// 初始化商店
	void initializeShop();

	// 初始化合成表
	void initializeSynthesisTable();

	// 更新物品栏
	void updateObjectList();

	// 更新时间显示器
	void updateTimeDisplay();

	// 更新角色金钱显示
	void updateCharacterMoneyLabel();

	// 更新UI界面
	void update(float deltaTime);

	// 显示物品图片
	void showObjectImage();

	// UILayer的create函数
	CREATE_FUNC(UILayer);

private:
	Character* _character;															// 角色指针
	Store *_store;																	// 商店指针
	cocos2d::Size _visibleSize;														// 可见区域的大小
	cocos2d::Label* _weekDayLabel;													// 显示星期和日期的标签指针
	cocos2d::Label* _timeHourLabel;													// 显示白天/晚上和小时的标签指针
	cocos2d::Label* _characterMoneyLabel;											// 角色金钱显示标签指针
	cocos2d::Label* _weatherLabel;													// 天气标签指针
	cocos2d::Sprite* _timeDisplayLayer;												// 用作为时间显示器背景的图片指针
	cocos2d::Sprite* _closedObjectListLayer;										// 物品栏关闭状态图片指针
	cocos2d::Sprite* _openedObjectListLayer;										// 物品栏打开状态图片指针
	cocos2d::Sprite* _boxObjectListLayer;											// 箱子物品栏图片指针
	cocos2d::Sprite* _skillLevelBoardLayer;											// 技能板图片指针
	cocos2d::Sprite* _shopLayer;													// 商店图片指针
	cocos2d::Sprite* _synthesisTableLayer;											// 合成表图片指针
	cocos2d::Sprite* _selectObjectSpriteMarker[OBJECT_LIST_COLS];					// 选中物品的标记指针(关闭状态的物品栏）
	cocos2d::Sprite* _skillLevelLayer[SKILL_KIND_NUM * SKILL_LEVEL_NUM];			// 技能等级指针
	cocos2d::Sprite* _nearestPlacementMarker;										// 最近放置标记指针
	ObjectImageInfo _closedObjectSpriteImage[OBJECT_LIST_COLS];						// 物品栏关闭时显示的物品图片指针
	ObjectImageInfo _openedObjectSpriteImage[OBJECT_LIST_COLS * OBJECT_LIST_ROWS];	// 物品栏打开时显示的物品图片指针
	ObjectImageInfo _boxObjectSpriteImage[OBJECT_LIST_COLS];						// 箱子物品图片指针
	ObjectImageInfo _selectedObjectImage;											// 当前选中的物品图片对象
	StoreObjectInfo _storeObjectInfo[PRODUCE_KIND_NUM_EACH_DAY];				    // 商店物品信息指针
	HoverMenuItemImage* _synthesisObjectSpriteImage[SYNTHESIS_TABLE_COLS * SYNTHESIS_TABLE_ROWS];	// 合成表显示的物品图片指针
	HoverMenuItemImage* _deleteObjectButton;										// 删除物品按钮
	HoverMenuItemImage* _closeObjectListButton;										// 关闭物品栏按钮
	HoverMenuItemImage* _sellObjectButton;											// 出售物品按钮
	HoverMenuItemImage* _exitButton;												// 退出按钮
	PlacementMarkerLayer* _placementMarkerLayer;									// 放置标记层类指针
	bool _objectListStatus;															// 物品栏状态
	bool _lastObjectListStatus;														// 上一次物品栏状态
	bool _boxObjectListStatus;														// 是否打开箱子
	bool _storeStatus;																// 商店状态
	bool _synthesisTableStatus;														// 合成表状态
	int _lastSelectedObjectIndex;													// 上一次物品栏索引
	Location _startLocation;														// 物品移动起始位置属性
	std::string _lastWeekDay;														// 上一天的信息
	// 创建物品图片 
	void createObjectImage(ObjectImageInfo& objectImageInfo,const std::string spriteFileName,const int count);

	// 设置物品图片位置
	void setObjectImagePosition(const ObjectImageInfo& objectImageInfo, const cocos2d::Vec2& position);

	// 设置物品图片是否可见
	void setObjectImageVisible(const ObjectImageInfo& objectImageInfo, bool visible);

	// 创建商店物品信息
	void createStoreObjectInfo(StoreObjectInfo& storeObjectInfo, const std::string spriteFileName,const std::string spriteName, const int price);

	// 设置商店物品图片位置
	void setStoreObjectInfoPosition(const StoreObjectInfo& storeObjectInfo, const cocos2d::Vec2& position);

	// 设置商店物品图片是否可见
	void setStoreObjectInfoVisible(const StoreObjectInfo& storeObjectInfo, bool visible);

	// 设置技能表是否可见
	void setSkillLevelVisible(bool visible);

	// 设置合成表是否可见
	void setSynthesisTableVisible(bool visible);

	// 寻找最近可放置坐标
	cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* objectSprite);

	// 设置选中物品标记框的显示状态
	void setSelectObjectSpriteMarker(int index, bool show);


	// 关闭回调
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif // !_UILAYER_H_


