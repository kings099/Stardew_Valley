/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     CharacterObjectList.cpp
 * File Function: CharacterObjectList类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/05
 * License:       MIT License
 ****************************************************************/


#include "CharacterObjectList.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
CharacterObjectList::CharacterObjectList() :
	_maxObjectKindCount(MAX_OBJECT_LIST_SIZE_LEVEL1), 
	_currentObjectKindCount(0),
	_currentObjectIndex(0),
	openObjectList(false)
{
	// 初始化物品栏
	initObjectList();
}

// 初始化物品栏
void CharacterObjectList::initObjectList() {
	_objectList.resize(_maxObjectKindCount);
	for (int i = 0; i < _maxObjectKindCount; i++) {
		_objectList[i] = ObjectListNode{ {None,nullptr}, 0 ,Unselected };
	}
	_objectList[0].status = Selected;

}

// 按下键盘时的处理
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// 按下数字键,-和=键时切换物品栏
	if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
		setCurrentObject(static_cast<int>(keyCode) - static_cast<int>(EventKeyboard::KeyCode::KEY_1));
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_0) {
		setCurrentObject(9);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_MINUS) {
		setCurrentObject(10);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_EQUAL) {
		setCurrentObject(11);
	}
	// 按下Q键丢弃物品
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& getCurrentObject().count != 0) {
		discardCurrentObject();
	}
	// 按下E键打开物品栏
	else if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		openObjectList =!openObjectList;
	}
}

// 捡起物品
// TODO:设置单个物品的最大存储数量
bool CharacterObjectList::pickUpObject(GameCommonObject targetObject, int objectCount) {
	// 查找物品栏中是否有相同物品
	const int index = findObject(targetObject);

	// 如果没有相同物品，且物品栏已满，则返回false
	if (index == -1 && checkObjectListFull()) {
		return false;
	}

	// 如果有相同物品且物品栏该物品不是工具，则增加物品数量
	if (index != -1 && (targetObject.type == Base|| targetObject.type == Compose)) {
		_objectList[index].count += objectCount;
	}
	else {
		int insertIndex = -1;
		for (insertIndex = 0; insertIndex < _maxObjectKindCount; insertIndex++) {
			if(_objectList[insertIndex].count == 0)
				break;
		}
		_objectList[insertIndex].count = objectCount;
		_objectList[insertIndex].objectNode = { targetObject.type, targetObject.object };
		_objectList[insertIndex].status = Unselected;
	}
	return true;
}

// 获取当前选中的物品
ObjectListNode CharacterObjectList::getCurrentObject() {
	return _objectList[_currentObjectIndex];
}

// 检查物品栏是否已满
bool CharacterObjectList::checkObjectListFull() {
	return (_currentObjectKindCount == _maxObjectKindCount);
}

// 设置当前选中的物品
void CharacterObjectList::setCurrentObject(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return;
	}
	_currentObjectIndex = index;
}

// 丢弃当前选中的物品
ObjectListNode CharacterObjectList::discardCurrentObject() {
	ObjectListNode tempObject = getCurrentObject();
	_objectList[_currentObjectIndex] = { {None,nullptr},0,Selected };
	return tempObject;		
}


// 查找物品栏中是否有指定物品
int CharacterObjectList::findObject(GameCommonObject targetObject) {
	for (int i = 0; i < _maxObjectKindCount; i++) {
		// 只有物品不是工具才会被查找
		if (_objectList[i].objectNode.object == targetObject.object && (targetObject.type == Base || targetObject.type == Compose)) {
			return i;
		}
	}
	// 没有找到
	return -1;
}