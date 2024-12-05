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
<<<<<<< Updated upstream
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
=======
CharacterObjectList::CharacterObjectList() :
	_maxObjectCount(MAX_OBJECT_LIST_SIZE_LEVEL1), 
	_currentObjectKindCount(0),
	_currentObjectIndex(0),
	openObjectList(false)
{
	// 初始化物品栏
	initObjectList();
}

// 初始化物品栏函数
void CharacterObjectList::initObjectList() {
	_objectList.resize(_maxObjectCount);
	for (int i = 0; i < _maxObjectCount; i++) {
		_objectList[i] = ObjectListNode{ {None,nullptr}, 0 ,Unselected };
	}
	_objectList[0].status = Selected;

>>>>>>> Stashed changes
}

// 按下键盘时的处理
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
<<<<<<< Updated upstream
	// 按下数字键切换物品栏物品
=======
	// 按下数字键,'-'键,'='键切换物品栏物品
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& _currentObject.object.type != None) {
		discardCurrentObject();
	}
=======
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& getCurrentObject().count != 0) {
		discardCurrentObject();
	}
	// 按下E键打开物品栏
	else if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		openObjectList =!openObjectList;
	}
}

// 捡起物品
// TODO:设置单个物品最大存储数量功能
bool CharacterObjectList::pickUpObject(GameCommonObject targetObject, int objectCount) {
	// 查找物品栏中是否有相同物品
	const int index = findObject(targetObject);

	// 物品栏没有相同物品且物品栏已满
	if (index == -1 && checkObjectListFull()) {
		return false;
	}

	// 物品栏有相同物品且目标物品不是工具
	if (index != -1 && (targetObject.type == Base|| targetObject.type == Compose)) {
		_objectList[index].count += objectCount;
	}
	else {
		int insertIndex = -1;
		for (insertIndex = 0; insertIndex < _maxObjectCount; insertIndex++) {
			if(_objectList[insertIndex].count == 0)
				break;
		}
		_objectList[insertIndex].count = objectCount;
		_objectList[insertIndex].objectNode = { targetObject.type, targetObject.object };
		_objectList[insertIndex].status = Unselected;
	}
	return true;
}

// 检查物品栏是否已满
bool CharacterObjectList::checkObjectListFull() {
	return (_currentObjectKindCount == _maxObjectCount);
>>>>>>> Stashed changes
}

// 设置当前物品
void CharacterObjectList::setCurrentObject(int index) {
	if (index < 0 || index >= _maxObjectCount) {
		return;
	}
	_currentObjectIndex = index;
<<<<<<< Updated upstream
	_currentObject = * _objectList[_currentObjectIndex];
=======
>>>>>>> Stashed changes
}

// 丢弃当前物品
ObjectListNode CharacterObjectList::discardCurrentObject() {
<<<<<<< Updated upstream
	ObjectListNode tempObject = *_objectList[_currentObjectIndex];
	*_objectList[_currentObjectIndex] = { _currentObjectIndex, {None,nullptr},0 };
	_currentObject = *_objectList[_currentObjectIndex];
	return tempObject;		
=======
	ObjectListNode tempObject = getCurrentObject();
	_objectList[_currentObjectIndex] = { {None,nullptr},0,Selected };
	
	return tempObject;		
}

// 获取选中的物品
ObjectListNode CharacterObjectList::getCurrentObject() {
	return _objectList[_currentObjectIndex];
}

// 查找指定物品
int CharacterObjectList::findObject(GameCommonObject targetObject) {
	for (int i = 0; i < _maxObjectCount; i++) {
		// 只有目标物品属于非工具非空类型才进行查找
		if (_objectList[i].objectNode.object == targetObject.object && (targetObject.type == Base || targetObject.type == Compose)) {
			return i;
		}
	}
	// 没找到
	return -1;
>>>>>>> Stashed changes
}