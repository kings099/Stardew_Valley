/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterObjectList.h
 * File Function: 角色物品栏CharacterObjectList的定义
 * Author:        尹诚成
 * Update Date:   2023/12/15
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_OBJECT_LIST_H__
#define __CHARACTER_OBJECT_LIST_H__

#include <vector>
#include "cocos2d.h"
#include "../proj.win32/Constant.h"


class CharacterObjectList : virtual public cocos2d::Node {
public:
	//构造函数 
	CharacterObjectList();

	// 按下键盘事件触发函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 捡起物品
	bool pickUpObject(GameToolObject targetObject, int objectCount, int targetIndex = INVAVID_NUM);

	// 捡起物品
	bool pickUpObject(GameSeedObject targetObject, int objectCount, int targetIndex = INVAVID_NUM);

	// 捡起物品
	bool pickUpObject(GameBaseObject targetObject, int objectCount, int targetIndex = INVAVID_NUM);

	// 捡起物品
	bool pickUpObject(GameCommonObject targetObject, int objectCount, int targetIndex = INVAVID_NUM);

	// 捡起物品
	bool pickUpObject(const std::string& targetObjectName, int objectCount, int targetIndex = INVAVID_NUM);

	// 丢弃当前选中的物品
	ObjectListNode deleteCurrentObject();

	// 丢弃指定数量的物品
	void deleteObject(int objectCount, int targetIndex = INVAVID_NUM);

	// 合成物品
	bool synthesizeObject(GameBaseObject targetObject);

	// 合成物品
	bool synthesizeObject(GameToolObject targetObject);

	// 交换物品
	void swapObject(int startIndex, int targetIndex);

	// 获取当前选中的物品
	ObjectListNode getCurrentObject();

	// 获取物品栏状态
	bool getObjectListStatus();

	// 获取箱子是否打开
	bool getBoxStatus();

	// 获取商店是否打开
	bool getStoreStatus();

	// 获取合成表是否打开
	bool getSynthesisTableStatus();

	// 查找指定位置的物品信息
	ObjectListNode findObjectAtPosition(int index);

	// 查找物品栏中是否有指定物品
	int findObjectByObjectList(GameCommonObject targetObject);

	// 查找物品栏中是否有指定物品
	int findObjectByObjectList(std::string targetObjectName);

	// 获取当前选中的物品索引
	int getCurrentObjectIndex();

	// 获取当前选中物品的名称
	std::string getCurrentObjectName();

	// 设置当前选中的物品
	void setCurrentObject(int index);

	// 重置按键启用
	void resetKeyEnabled();

	// 保存数据
	bool saveData(const std::string& fileName);

	// 加载数据
	bool loadData(const std::string& fileName);

	std::function<void(bool)> _callback;  // 用于保存回调

private:
	std::vector<ObjectListNode> _objectList;	// 物品栏列表
	int _maxObjectKindCount;					// 物品栏最大物品种类容量
	int _currentObjectIndex;					// 当前选中的物品索引
	bool _openObjectList;						// 是否打开物品栏
	bool _openBox;								// 是否打开箱子
	bool _openShop;							    // 是否打开商店
	bool _openSynthesisTable;					// 是否打开合成台
	bool _isEKeyEnabled;							// 是否启用E键
	bool _isRKeyEnabled;							// 是否启用R键
	bool _isTKeyEnabled;							// 是否启用T键
	bool _isYKeyEnabled;							// 是否启用Y键
	
	// 查找物品栏中是否有指定物品
	GameCommonObject findObjectByName(const std::string& name);

	// 检查物品栏是否已满
	bool checkObjectListFull();

	// 检查物品栏是否为空
	bool checkObjectListEmpty();
};

#endif // !__CHARACTER_OBJECT_LIST_H__