/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.cpp
 * File Function: 箱子Box类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#include "Box.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// 获取单例
Box& Box::getInstace() {
	static Box instance;
	return instance;
}

// 获取箱子向量列表
BoxNode& Box::getBoxList() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex];
}

// 添加单个箱子
void Box::addBox(const BoxNode& boxNode){
	_boxObjectList.push_back(boxNode);
}

// 移除单个箱子
void Box::removeBox() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex!= -1) {
		_boxObjectList.erase(_boxObjectList.begin() + boxListIndex);
	}
}

// 构造函数
Box::Box():
	_maxObjectKindCount(OBJECT_LIST_COLS)
{
	_character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
	_boxObjectList.resize(0);
}

// 储存物品
bool Box::storeObject(GameToolObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject( commonObject, objectCount, targetIndex);
}

// 储存物品
bool Box::storeObject(GameSeedObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(commonObject, objectCount, targetIndex);
}

// 储存物品
bool Box::storeObject( GameBaseObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(commonObject, objectCount, targetIndex);
}

// 交换物品
void Box::swapObject( int startIndex, int targetIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	std::swap(_boxObjectList[boxListIndex]._boxObjectList[startIndex], _boxObjectList[boxListIndex]._boxObjectList[targetIndex]);
}

// 取出当前选中的物品
void Box::getSelectedObject( int boxIndex, int objectListIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	_character->pickUpObject(_boxObjectList[boxListIndex]._boxObjectList[boxIndex].objectNode, _boxObjectList[boxListIndex]._boxObjectList[boxIndex].count, objectListIndex);
	_boxObjectList[boxListIndex]._boxObjectList[boxIndex]= { {None,nullptr},0,Unselected };
}

// 查找指定位置是否有物品
ObjectListNode Box::findObjectAtPosition( int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex]._boxObjectList[index];
}

// 利用坐标位置匹配箱子
int Box::matchBoxPosition(cocos2d::Vec2 worldPosition) {
	int index = -1;
	float minDistance = FLT_MAX;
	for (int i = 0; i < _boxObjectList.size(); i++) {
		float distance = _character->getPosition().distance(worldPosition);
		if (distance < minDistance) {
			minDistance = distance;
			index = i;
		}
	}
	return index;
}

// 查找箱子中是否有指定物品
int Box::findObject(GameCommonObject targetObject) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	for (int i = 0; i < _maxObjectKindCount; i++) {
		// 只有物品不是工具才会被查找
		if (_boxObjectList[boxListIndex]._boxObjectList[i].count != 0 
			&& _boxObjectList[boxListIndex]._boxObjectList[i].objectNode.object->_index == targetObject.object->_index 
			&& (targetObject.type == Base)) {
			return i;
		}
	}
	// 没有找到
	return -1;
}

// 储存物品
bool Box::storeObject(GameCommonObject targetObject, int objectCount, int targetIndex) {
	_character->deleteCurrentObject();
	int boxListIndex = matchBoxPosition(_character->getPosition());
	// 查找物品栏中是否有相同物品
	const int index = findObject(targetObject);
	bool success = true;

	// 如果没有相同物品，且物品栏已满，则返回false
	if (index == -1 && checkObjectListFull()) {
		success = false;
	}

	// 如果有相同物品且物品栏该物品不是工具，则增加物品数量
	if (index != -1 && (targetObject.type == Base)) {
		_boxObjectList[boxListIndex]._boxObjectList[index].count += objectCount;
	}
	else {
		if (targetIndex == INVAVID_NUM) {
			int insertIndex = -1;
			for (insertIndex = 0; insertIndex < _maxObjectKindCount; insertIndex++) {
				if (_boxObjectList[boxListIndex]._boxObjectList[insertIndex].count == 0) {
					break;
				}
			}
			_boxObjectList[boxListIndex]._boxObjectList[insertIndex] = { { targetObject.type, targetObject.object } , objectCount, Unselected };
		}
		else {
			if (targetIndex < 0 || targetIndex >= _maxObjectKindCount || _boxObjectList[boxListIndex]._boxObjectList[targetIndex].count != 0) {
				success = false;
			}
			else {
				_boxObjectList[boxListIndex]._boxObjectList[targetIndex] = { { targetObject.type, targetObject.object } , objectCount, Unselected };
			}
		}
	}
	return success;
}

// 检查箱子是否已满
bool Box::checkObjectListFull() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	bool isFull = true;
	for (const auto& item : _boxObjectList[boxListIndex]._boxObjectList) {
		if (item.count == 0) {
			isFull = false;
			break;
		}
	}
	return isFull;
}