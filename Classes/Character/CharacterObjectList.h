/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterObjectList.h
 * File Function: 角色物品栏CharacterObjectList的定义
 * Author:        尹诚成
 * Update Date:   2023/12/05
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_OBJECT_LIST_H__
#define __CHARACTER_OBJECT_LIST_H__

#include <vector>
#include "cocos2d.h"
#include "../proj.win32/Constant.h"
#include "../proj.win32/ObjectConstant.h"

class CharacterObjectList : virtual public cocos2d::Node {
public:
	//构造函数 
	CharacterObjectList();

	// 按下键盘时的处理
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 捡起物品
	bool pickUpObject(GameCommonObject targetObject, int objectCount);

	// 移动物品
	void moveObject(ObjectListNode object);

	// 获取当前选中的物品
	ObjectListNode getCurrentObject();

	// 检查物品栏是否已满
	bool checkObjectListFull();
protected:
	bool _openObjectList;						// 是否打开物品栏

private:
	std::vector<ObjectListNode> _objectList;	// 物品栏列表
	int _maxObjectKindCount;					// 物品栏最大物品种类容量
	int _currentObjectKindCount;				// 当前物品种类物品数量
	int _currentObjectIndex;					// 当前选中的物品索引

	// 初始化物品栏
	void initObjectList();

	// 设置当前选中的物品
	void setCurrentObject(int index);			

	// 丢弃当前选中的物品
	ObjectListNode discardCurrentObject();

	// 查找物品栏中是否有指定物品
	int findObject(GameCommonObject targetObject);
};

#endif // !__CHARACTER_OBJECT_LIST_H__