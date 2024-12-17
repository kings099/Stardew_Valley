/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterObjectList.cpp
 * File Function: 角色物品栏CharacterObjectList类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/15
 * License:       MIT License
 ****************************************************************/

#include <fstream>
#include <algorithm>
#include <functional>
#include "CharacterObjectList.h"

USING_NS_CC;

// 构造函数
CharacterObjectList::CharacterObjectList() :
	_maxObjectKindCount(OBJECT_LIST_ROWS*OBJECT_LIST_COLS),
	_currentObjectIndex(0),
	_openObjectList(false)
{
	if (!loadData("../GameData/CharacterObjectListData.dat")) {
		// 初始化物品栏
		_objectList.resize(_maxObjectKindCount, { ObjectListNode{ {None,nullptr}, 0 ,Unselected } });
		pickUpObject(GAME_TOOL_OBJECTS_ATTRS[0], 1);
		pickUpObject(GAME_TOOL_OBJECTS_ATTRS[3], 1);
		pickUpObject(GAME_TOOL_OBJECTS_ATTRS[6], 1);
		pickUpObject(GAME_TOOL_OBJECTS_ATTRS[9], 1);
		pickUpObject(GAME_TOOL_OBJECTS_ATTRS[12], 1);
		pickUpObject(GAME_TOOL_OBJECTS_ATTRS[15], 1);
	}
	//pickUpObject(GAME_TOOL_OBJECTS_ATTRS[0], 1);
	pickUpObject(GAME_BASE_OBJECTS_ATTRS[0], 1);
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
		// 按下Q键丢弃物品
		if (keyCode == EventKeyboard::KeyCode::KEY_Q && getCurrentObject().count != 0) {
			deleteCurrentObject();
		}
	}
	// 按下E键打开/关闭物品栏
	if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		_openObjectList = !_openObjectList;
		_openBox = false;
	}
	// 按下R键打开物品栏和箱子
	if (keyCode == EventKeyboard::KeyCode::KEY_R) {
		_openObjectList = !_openObjectList;
		_openBox = !_openBox;
	}
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameToolObject targetObject, int objectCount, int targetIndex) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return pickUpObject(commonObject, objectCount, targetIndex);
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameSeedObject targetObject, int objectCount, int targetIndex) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Seed, targetObjectPtr);
	return pickUpObject(commonObject, objectCount, targetIndex);
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameBaseObject targetObject, int objectCount, int targetIndex) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Base, targetObjectPtr);
	return pickUpObject(commonObject, objectCount, targetIndex);
}

// 捡起物品
// TODO:设置单个物品的最大存储数量
bool CharacterObjectList::pickUpObject(GameCommonObject targetObject, int objectCount, int targetIndex) {
	// 查找物品栏中是否有相同物品
	const int index = findObject(targetObject);
	bool success = true;

	// 如果没有相同物品，且物品栏已满，则返回false
	if (index == -1 && checkObjectListFull()) {
		success =  false;
	}

	// 如果有相同物品且物品栏该物品不是工具，则增加物品数量
	if (index != -1 && (targetObject.type == Base)) {
		_objectList[index].count += objectCount;
	}
	else {
		if (targetIndex == INVAVID_NUM) {
			int insertIndex = -1;
			for (insertIndex = 0; insertIndex < _maxObjectKindCount; insertIndex++) {
				if (_objectList[insertIndex].count == 0) {
					break;
				}
			}
			_objectList[insertIndex] = { { targetObject.type, targetObject.object } , objectCount, Unselected };
		}
		else {
			if (targetIndex< 0||targetIndex >= _maxObjectKindCount || _objectList[targetIndex].count != 0) {
				success = false;
			}
			else {
				_objectList[targetIndex] = { { targetObject.type, targetObject.object } , objectCount, Unselected };
			}

		}
	}
	if (_pickUpCallback) {
		_pickUpCallback(success); 
	}
	return success;
}

// 丢弃当前选中的物品
ObjectListNode CharacterObjectList::deleteCurrentObject() {
	ObjectListNode tempObject = getCurrentObject();
	_objectList[_currentObjectIndex] = { {None,nullptr},0,Selected };
	return tempObject;
}

// 交换物品
void  CharacterObjectList::swapObject(int startIndex, int targetIndex) {
	if (startIndex < 0 || startIndex >= _maxObjectKindCount) {
		return;
	}
	std::swap(_objectList[startIndex], _objectList[targetIndex]);
	_currentObjectIndex = targetIndex;
}

// 获取当前选中的物品
ObjectListNode CharacterObjectList::getCurrentObject() {
	return _objectList[_currentObjectIndex];
}

// 获取物品栏状态
bool CharacterObjectList::getObjectListStatus() {
	return _openObjectList;
}

// 获取箱子是否打开
bool CharacterObjectList::getBoxStatus() {
	return _openBox;
}

// 查找指定位置的物品信息
ObjectListNode CharacterObjectList::findObjectAtPosition(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	return _objectList[index];
}

// 获取当前选中的物品索引
int CharacterObjectList::getCurrentObjectIndex() {
	return _currentObjectIndex;
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

// 查找物品栏中是否有指定物品
int CharacterObjectList::findObject(GameCommonObject targetObject) {
	for (int i = 0; i < _maxObjectKindCount; i++) {
		// 只有物品不是工具才会被查找
		if (_objectList[i].count!=0&& _objectList[i].objectNode.object->_index == targetObject.object->_index && (targetObject.type == Base)) {
			return i;
		}
	}
	// 没有找到
	return -1;
}

// 检查物品栏是否已满
bool CharacterObjectList::checkObjectListFull() {
	bool isFull = true;
	for (const auto& item : _objectList) {
		if (item.count == 0) {
			isFull = false;
			break;
		}
	}
	return isFull;
}

// 检查物品栏是否为空
bool CharacterObjectList::checkObjectListEmpty() {
	bool isEmpty = true;
	for (const auto& item : _objectList) {
		if (item.count != 0) {
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

// 回调
void CharacterObjectList::setPickUpCallback(std::function<void(bool)> callback) {
	_pickUpCallback = callback;
}

// 保存数据
bool CharacterObjectList::saveData(const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary);
	if (!outFile) {
		CCLOG("Error opening file for writing: %s", fileName.c_str());
		return false;
	}
	int itemCount = OBJECT_LIST_ROWS * OBJECT_LIST_COLS;
	outFile.write(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));
	// 写入物品列表
	for (const auto& item : _objectList) {
		item.save(outFile);
	}
	outFile.close();
	return true;
}

// 加载数据
bool CharacterObjectList::loadData(const std::string& fileName) {
	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile) {
		CCLOG("File does not exist or cannot be opened: %s", fileName.c_str());
		return false;
	}

	int itemCount = OBJECT_LIST_ROWS * OBJECT_LIST_COLS; 
	inFile.read(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));

	_objectList.resize(itemCount);

	// 读取物品列表
	for (auto& item : _objectList) {
		item.load(inFile);
	}

	// 填充空物品
	for (size_t i = 0; i < _objectList.size(); ++i) {
		if (_objectList[i].count == 0) {
			_objectList[i] = ObjectListNode{ {None,nullptr}, 0 ,Unselected };
		}
	}

	inFile.close();
	return true;
}

