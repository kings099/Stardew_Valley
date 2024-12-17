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

// ��ȡ���������б�
BoxNode& Box::getBoxList() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex];
}

// ��ӵ�������
void Box::addBox(const BoxNode& boxNode){
	_boxObjectList.push_back(boxNode);
}

// �Ƴ���������
void Box::removeBox() {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex!= -1) {
		_boxObjectList.erase(_boxObjectList.begin() + boxListIndex);
	}
}

// ���캯��
Box::Box():
	_maxObjectKindCount(OBJECT_LIST_COLS)
{
	_character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
	_boxObjectList.resize(0);
}

// ������Ʒ
bool Box::storeObject(GameToolObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject( commonObject, objectCount, targetIndex);
}

// ������Ʒ
bool Box::storeObject(GameSeedObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(commonObject, objectCount, targetIndex);
}

// ������Ʒ
bool Box::storeObject( GameBaseObject targetObject, int objectCount, int targetIndex) {
	if (targetIndex < 0 || targetIndex >= _maxObjectKindCount) {
		return false;
	}
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return storeObject(commonObject, objectCount, targetIndex);
}

// ������Ʒ
void Box::swapObject( int startIndex, int targetIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	std::swap(_boxObjectList[boxListIndex]._boxObjectList[startIndex], _boxObjectList[boxListIndex]._boxObjectList[targetIndex]);
}

// ȡ����ǰѡ�е���Ʒ
void Box::getSelectedObject( int boxIndex, int objectListIndex) {
	int boxListIndex = matchBoxPosition(_character->getPosition());
	if (boxListIndex == -1) {
		return;
	}
	_character->pickUpObject(_boxObjectList[boxListIndex]._boxObjectList[boxIndex].objectNode, _boxObjectList[boxListIndex]._boxObjectList[boxIndex].count, objectListIndex);
	_boxObjectList[boxListIndex]._boxObjectList[boxIndex]= { {None,nullptr},0,Unselected };
}

// ����ָ��λ���Ƿ�����Ʒ
ObjectListNode Box::findObjectAtPosition( int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	int boxListIndex = matchBoxPosition(_character->getPosition());
	return _boxObjectList[boxListIndex]._boxObjectList[index];
}

// ��������λ��ƥ������
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

// ������Ʒ
bool Box::storeObject(GameCommonObject targetObject, int objectCount, int targetIndex) {
	_character->deleteCurrentObject();
	int boxListIndex = matchBoxPosition(_character->getPosition());
	// ������Ʒ�����Ƿ�����ͬ��Ʒ
	const int index = findObject(targetObject);
	bool success = true;

	// ���û����ͬ��Ʒ������Ʒ���������򷵻�false
	if (index == -1 && checkObjectListFull()) {
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