/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     CharacterObjectList.cpp
 * File Function: CharacterObjectList���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/05
 * License:       MIT License
 ****************************************************************/


#include "CharacterObjectList.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// ���캯��
<<<<<<< Updated upstream
CharacterObjectList::CharacterObjectList() :_maxObjectCount(MAX_OBJECT_LIST_SIZE_LEVEL1), _currentObjectCount(0), _currentObjectIndex(0) {
	// ��ʼ����Ʒ��
	_objectList.resize(_maxObjectCount);
	for (int i = 0; i < _maxObjectCount; i++) {
		_objectList[i] = new ObjectListNode{ i, {None,nullptr}, 0 }; 
	}

	// ���̼����¼�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(CharacterObjectList::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ��������
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
	// ��ʼ����Ʒ��
	initObjectList();
}

// ��ʼ����Ʒ������
void CharacterObjectList::initObjectList() {
	_objectList.resize(_maxObjectCount);
	for (int i = 0; i < _maxObjectCount; i++) {
		_objectList[i] = ObjectListNode{ {None,nullptr}, 0 ,Unselected };
	}
	_objectList[0].status = Selected;

>>>>>>> Stashed changes
}

// ���¼���ʱ�Ĵ���
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
<<<<<<< Updated upstream
	// �������ּ��л���Ʒ����Ʒ
=======
	// �������ּ�,'-'��,'='���л���Ʒ����Ʒ
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
	// ����Q��������ǰ��Ʒ
<<<<<<< Updated upstream
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& _currentObject.object.type != None) {
		discardCurrentObject();
	}
=======
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& getCurrentObject().count != 0) {
		discardCurrentObject();
	}
	// ����E������Ʒ��
	else if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		openObjectList =!openObjectList;
	}
}

// ������Ʒ
// TODO:���õ�����Ʒ���洢��������
bool CharacterObjectList::pickUpObject(GameCommonObject targetObject, int objectCount) {
	// ������Ʒ�����Ƿ�����ͬ��Ʒ
	const int index = findObject(targetObject);

	// ��Ʒ��û����ͬ��Ʒ����Ʒ������
	if (index == -1 && checkObjectListFull()) {
		return false;
	}

	// ��Ʒ������ͬ��Ʒ��Ŀ����Ʒ���ǹ���
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

// �����Ʒ���Ƿ�����
bool CharacterObjectList::checkObjectListFull() {
	return (_currentObjectKindCount == _maxObjectCount);
>>>>>>> Stashed changes
}

// ���õ�ǰ��Ʒ
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

// ������ǰ��Ʒ
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

// ��ȡѡ�е���Ʒ
ObjectListNode CharacterObjectList::getCurrentObject() {
	return _objectList[_currentObjectIndex];
}

// ����ָ����Ʒ
int CharacterObjectList::findObject(GameCommonObject targetObject) {
	for (int i = 0; i < _maxObjectCount; i++) {
		// ֻ��Ŀ����Ʒ���ڷǹ��߷ǿ����ͲŽ��в���
		if (_objectList[i].objectNode.object == targetObject.object && (targetObject.type == Base || targetObject.type == Compose)) {
			return i;
		}
	}
	// û�ҵ�
	return -1;
>>>>>>> Stashed changes
}