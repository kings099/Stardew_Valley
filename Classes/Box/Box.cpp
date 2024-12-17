/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.cpp
 * File Function: ����Box���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#include "Box.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// ��ȡ����
Box& Box::getInstace() {
	static Box instance;
	return instance;
}

// ���캯��
Box::Box():
	_maxObjectKindCount(OBJECT_LIST_COLS)
{
	_character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
	_boxObjectList.resize(0);
}

// ������Ʒ
bool Box::storeObject(int boxListIndex, GameToolObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(boxListIndex, commonObject, objectCount, targetIndex);
}

// ������Ʒ
bool Box::storeObject(int boxListIndex, GameSeedObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(boxListIndex, commonObject, objectCount, targetIndex);
}

// ������Ʒ
bool Box::storeObject(int boxListIndex, GameBaseObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(boxListIndex, commonObject, objectCount, targetIndex);
}

// ������Ʒ
void Box::swapObject(int boxListIndex, int startIndex, int targetIndex) {
	std::swap(_boxObjectList[boxListIndex]._boxObjectList[startIndex], _boxObjectList[boxListIndex]._boxObjectList[targetIndex]);
}

// ȡ����ǰѡ�е���Ʒ
void Box::getSelectedObject(int boxListIndex, int boxIndex, int objectListIndex) {
	_character->pickUpObject(_boxObjectList[boxListIndex]._boxObjectList[boxIndex].objectNode, _boxObjectList[boxListIndex]._boxObjectList[boxIndex].count, objectListIndex);
	_boxObjectList[boxListIndex]._boxObjectList[boxIndex]= { {None,nullptr},0,Unselected };
}

// ����ָ��λ���Ƿ�����Ʒ
ObjectListNode Box::findObjectAtPosition(int boxListIndex, int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	return _boxObjectList[boxListIndex]._boxObjectList[index];
}

// ��������λ��ƥ������
int Box::matchBoxPosition(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition) {
	for (int i = 0; i < _boxObjectList.size(); i++) {
	   if(_boxObjectList[i]._worldPosition == worldPosition && _boxObjectList[i]._tilePosition == tilePosition)
		   return i;
	}
	return -1;
}

// �����������Ƿ���ָ����Ʒ
int Box::findObject(int boxListIndex, GameCommonObject targetObject) {
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

// ������Ʒ
bool Box::storeObject(int boxListIndex, GameCommonObject targetObject, int objectCount, int targetIndex) {
	_character->deleteCurrentObject();
	
	// ������Ʒ�����Ƿ�����ͬ��Ʒ
	const int index = findObject(boxListIndex,targetObject);
	bool success = true;

	// ���û����ͬ��Ʒ������Ʒ���������򷵻�false
	if (index == -1 && checkObjectListFull(boxListIndex)) {
		success = false;
	}

	// �������ͬ��Ʒ����Ʒ������Ʒ���ǹ��ߣ���������Ʒ����
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

// ��������Ƿ�����
bool Box::checkObjectListFull(int boxListIndex) {
	bool isFull = true;
	for (const auto& item : _boxObjectList[boxListIndex]._boxObjectList) {
		if (item.count == 0) {
			isFull = false;
			break;
		}
	}
	return isFull;
}