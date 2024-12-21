/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.cpp
 * File Function: 箱子Box类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#include "Box.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// 获取单例
Box& Box::getInstance() {
	static Box instance;
	return instance;
}

// 获取箱子
BoxNode& Box::getBoxList() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex];
}

// 获取箱子数量
int Box::getBoxCount() {
	return _boxObjectList.size();
}

// 添加单个箱子
bool Box::addBox(const BoxNode& boxNode){
	for (int i = 0; i < _boxObjectList.size(); i++) {
		if (_boxObjectList[i]._worldPosition == boxNode._worldPosition) {
			return false;
		}
	}
	_boxObjectList.push_back(boxNode);
	return true;
}

// 移除单个箱子
void Box::removeBox() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex!= -1) {
		_boxObjectList.erase(_boxObjectList.begin() + boxListIndex);
	}
}

// 利用坐标位置匹配箱子
int Box::matchBoxPosition(cocos2d::Vec2 worldPosition) {
	int index = -1;
	float minDistance = FLT_MAX;
	for (int i = 0; i < _boxObjectList.size(); i++) {
		float distance = _boxObjectList[i]._worldPosition.distance(worldPosition);
		if (distance < minDistance) {
			minDistance = distance;
			index = i;
		}
	}
	return index;
}

// 构造函数
Box::Box():
	_maxObjectKindCount(OBJECT_LIST_COLS)
{
	_character = Character::getInstance();
	if (!loadData("../GameData/BoxObjectListData.dat")) {
		_boxObjectList.resize(0);
	}
}

// 储存物品
bool Box::storeObject(int objectListIndex ,int boxIndex) {

	const int boxListIndex = matchBoxPosition(_character->getPosition());
	const auto targetObjectInfo = _character->getCurrentObject().objectNode;
	const int objectCount = _character->getCurrentObject().count;
	_character->deleteCurrentObject();
	// 查找箱子中是否有相同物品
	const int index = findObject(targetObjectInfo);

	bool success = true;

	// 如果没有相同物品，且箱子已满
	if (index == -1 && checkObjectListFull()) {
		success = false;
	}

	// 如果有相同物品且物品栏该物品不是工具，则增加物品数量
	if (index != -1 && (targetObjectInfo.type == Base)) {
		_boxObjectList[boxListIndex]._boxObjectList[index].count += objectCount;
	}
	else {
		if (boxIndex < 0 || boxIndex >= _maxObjectKindCount || _boxObjectList[boxListIndex]._boxObjectList[boxIndex].count != 0) {
			success = false;
		}
		else {
			_boxObjectList[boxListIndex]._boxObjectList[boxIndex] = { { targetObjectInfo.type, targetObjectInfo.object } , objectCount, Unselected };
		}
	}
	return success;
}

// 交换物品
void Box::swapObject( int startIndex, int targetIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	std::swap(_boxObjectList[boxListIndex]._boxObjectList[startIndex], _boxObjectList[boxListIndex]._boxObjectList[targetIndex]);
}

// 取出物品
void Box::getSelectedObject( int boxIndex, int objectListIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	_character->pickUpObject(_boxObjectList[boxListIndex]._boxObjectList[boxIndex].objectNode, _boxObjectList[boxListIndex]._boxObjectList[boxIndex].count, objectListIndex);
	_boxObjectList[boxListIndex]._boxObjectList[boxIndex]= { {None,nullptr},0,Unselected };
}

// 查找指定位置是否有物品
ObjectListNode Box::findObjectAtPosition(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex]._boxObjectList[index];
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

// 保存数据
bool Box::saveData(const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary);
	if (!outFile) {
		CCLOG("Error opening file for writing: %s", fileName.c_str());
		return false;
	}
	// 保存箱子数量
	size_t boxSize = _boxObjectList.size();
	outFile.write((char*)&boxSize, sizeof(boxSize));
	for (const auto& boxNode : _boxObjectList) {
		for (const auto& item : boxNode._boxObjectList) {
			item.save(outFile);
		}
		outFile.write((char*)&boxNode._worldPosition, sizeof(boxNode._worldPosition));
	}

	outFile.close();
	return true;
}

// 加载数据
bool Box::loadData(const std::string& fileName) {
	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile) {
		CCLOG("File does not exist or cannot be opened: %s", fileName.c_str());
		return false;
	}
	size_t boxSize;
	inFile.read(reinterpret_cast<char*>(&boxSize), sizeof(boxSize));
	_boxObjectList.resize(boxSize);

	for (auto& boxNode : _boxObjectList) {
		boxNode._boxObjectList.resize(OBJECT_LIST_COLS);
		for (auto& item : boxNode._boxObjectList) {
		
			item.load(inFile);
		}
		inFile.read((char*)&boxNode._worldPosition, sizeof(boxNode._worldPosition));
	}
	inFile.close();
	return true;
}