/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterObjectList.cpp
 * File Function: 角色物品栏CharacterObjectList类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/05
 * License:       MIT License
 ****************************************************************/


#include "CharacterObjectList.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
CharacterObjectList::CharacterObjectList() :
	_maxObjectKindCount(OBJECT_LIST_ROWS*OBJECT_LIST_COLS),
	_currentObjectKindCount(0),
	_currentObjectIndex(0),
	_openObjectList(false)
{
	// 初始化物品栏
	initObjectList();
}

// 按下键盘时的处理
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// 按下数字键,-和=键时切换物品栏
	if (!_openObjectList) {
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
	}
	// 按下Q键丢弃物品
	if (keyCode == EventKeyboard::KeyCode::KEY_Q && getCurrentObject().count != 0) {
		deleteCurrentObject();
	}
	// 按下E键打开/关闭物品栏
	if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		_openObjectList = !_openObjectList;
	}
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameToolObject targetObject, int objectCount) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return pickUpObject(commonObject, objectCount);
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameSeedObject targetObject, int objectCount) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Seed, targetObjectPtr);
	return pickUpObject(commonObject, objectCount);
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameBaseObject targetObject, int objectCount) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Base, targetObjectPtr);
	return pickUpObject(commonObject, objectCount);
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
	if (index != -1 && (targetObject.type == Base)) {
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

// 丢弃当前选中的物品
ObjectListNode CharacterObjectList::deleteCurrentObject() {
	ObjectListNode tempObject = getCurrentObject();
	_objectList[_currentObjectIndex] = {_currentObjectIndex ,{None,nullptr},0,Selected };
	return tempObject;
}

// 获取当前选中的物品
ObjectListNode CharacterObjectList::getCurrentObject() {
	return _objectList[_currentObjectIndex];
}

// 获取物品栏状态
bool CharacterObjectList::getObjectListStatus() {
	return _openObjectList;
}

// 查找指定位置的物品信息
ObjectListNode CharacterObjectList::findObjectAtPosition(int index) {
	return _objectList[index];
}

// 设置物品栏状态
void CharacterObjectList::setObjectListStatus(bool status) {
	_openObjectList = static_cast<bool>(status);
}


// 设置当前选中的物品
void CharacterObjectList::setCurrentObject(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return;
	}
	_currentObjectIndex = index;
	CCLOG("_currentObjectIndex:%d", _currentObjectIndex);
}


// 初始化物品栏
void CharacterObjectList::initObjectList() {
	_objectList.resize(_maxObjectKindCount);
	for (int i = 0; i < _maxObjectKindCount; i++) {
		_objectList[i] = ObjectListNode{ i,{None,nullptr}, 0 ,Unselected };
	}
	_objectList[0].status = Selected;
}

// 查找物品栏中是否有指定物品
int CharacterObjectList::findObject(GameCommonObject targetObject) {
	for (int i = 0; i < _maxObjectKindCount; i++) {
		// 只有物品不是工具才会被查找
		if (_objectList[i].objectNode.object == targetObject.object && (targetObject.type == Base)) {
			return i;
		}
	}
	// 没有找到
	return -1;
}

// 检查物品栏是否已满
bool CharacterObjectList::checkObjectListFull() {
	return (_currentObjectKindCount == _maxObjectKindCount);
}
