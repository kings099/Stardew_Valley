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
CharacterObjectList::CharacterObjectList() :_maxObjectCount(MAX_OBJECT_LIST_SIZE_LEVEL1), _currentObjectCount(0), _currentObjectIndex(0) {
	// 初始化物品栏
	_objectList.resize(_maxObjectCount);
	for (int i = 0; i < _maxObjectCount; i++) {
		_objectList[i] = new ObjectListNode{ i, {None,nullptr}, 0 }; 
	}

	// 键盘监视事件
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(CharacterObjectList::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 析构函数
CharacterObjectList::~CharacterObjectList() {
	for (auto obj : _objectList) {
		delete obj;
	}
}

// 按下键盘时的处理
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// 按下数字键切换物品栏物品
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
	// 按下Q键丢弃当前物品
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& _currentObject.object.type != None) {
		discardCurrentObject();
	}
}

// 设置当前物品
void CharacterObjectList::setCurrentObject(int index) {
	if (index < 0 || index >= _maxObjectCount) {
		return;
	}
	_currentObjectIndex = index;
	_currentObject = * _objectList[_currentObjectIndex];
}

// 丢弃当前物品
ObjectListNode CharacterObjectList::discardCurrentObject() {
	ObjectListNode tempObject = *_objectList[_currentObjectIndex];
	*_objectList[_currentObjectIndex] = { _currentObjectIndex, {None,nullptr},0 };
	_currentObject = *_objectList[_currentObjectIndex];
	return tempObject;		
}