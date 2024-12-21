/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.cpp
 * File Function: ����Box���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#include "Box.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// ��ȡ����
Box& Box::getInstance() {
	static Box instance;
	return instance;
}

// ��ȡ����
BoxNode& Box::getBoxList() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex];
}

// ��ȡ��������
int Box::getBoxCount() {
	return _boxObjectList.size();
}

// ��ӵ�������
bool Box::addBox(const BoxNode& boxNode){
	for (int i = 0; i < _boxObjectList.size(); i++) {
		if (_boxObjectList[i]._worldPosition == boxNode._worldPosition) {
			return false;
		}
	}
	_boxObjectList.push_back(boxNode);
	return true;
}

// �Ƴ���������
void Box::removeBox() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex!= -1) {
		_boxObjectList.erase(_boxObjectList.begin() + boxListIndex);
	}
}

// ��������λ��ƥ������
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

// ���캯��
Box::Box():
	_maxObjectKindCount(OBJECT_LIST_COLS)
{
	_character = Character::getInstance();
	if (!loadData("../GameData/BoxObjectListData.dat")) {
		_boxObjectList.resize(0);
	}
}

// ������Ʒ
bool Box::storeObject(int objectListIndex ,int boxIndex) {

	const int boxListIndex = matchBoxPosition(_character->getPosition());
	const auto targetObjectInfo = _character->getCurrentObject().objectNode;
	const int objectCount = _character->getCurrentObject().count;
	_character->deleteCurrentObject();
	// �����������Ƿ�����ͬ��Ʒ
	const int index = findObject(targetObjectInfo);

	bool success = true;

	// ���û����ͬ��Ʒ������������
	if (index == -1 && checkObjectListFull()) {
		success = false;
	}

	// �������ͬ��Ʒ����Ʒ������Ʒ���ǹ��ߣ���������Ʒ����
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

// ������Ʒ
void Box::swapObject( int startIndex, int targetIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	std::swap(_boxObjectList[boxListIndex]._boxObjectList[startIndex], _boxObjectList[boxListIndex]._boxObjectList[targetIndex]);
}

// ȡ����Ʒ
void Box::getSelectedObject( int boxIndex, int objectListIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	_character->pickUpObject(_boxObjectList[boxListIndex]._boxObjectList[boxIndex].objectNode, _boxObjectList[boxListIndex]._boxObjectList[boxIndex].count, objectListIndex);
	_boxObjectList[boxListIndex]._boxObjectList[boxIndex]= { {None,nullptr},0,Unselected };
}

// ����ָ��λ���Ƿ�����Ʒ
ObjectListNode Box::findObjectAtPosition(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex]._boxObjectList[index];
}

// �����������Ƿ���ָ����Ʒ
int Box::findObject(GameCommonObject targetObject) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	for (int i = 0; i < _maxObjectKindCount; i++) {
		// ֻ����Ʒ���ǹ��߲Żᱻ����
		if (_boxObjectList[boxListIndex]._boxObjectList[i].count != 0 
			&& _boxObjectList[boxListIndex]._boxObjectList[i].objectNode.object->_index == targetObject.object->_index 
			&& (targetObject.type == Base)) {
			return i;
		}
	}
	// û���ҵ�
	return -1;
}


// ��������Ƿ�����
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

// ��������
bool Box::saveData(const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary);
	if (!outFile) {
		CCLOG("Error opening file for writing: %s", fileName.c_str());
		return false;
	}
	// ������������
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

// ��������
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