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
}

// ���¼���ʱ�Ĵ���
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// �������ּ��л���Ʒ����Ʒ
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
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q&& _currentObject.object.type != None) {
		discardCurrentObject();
	}
}

// ���õ�ǰ��Ʒ
void CharacterObjectList::setCurrentObject(int index) {
	if (index < 0 || index >= _maxObjectCount) {
		return;
	}
	_currentObjectIndex = index;
	_currentObject = * _objectList[_currentObjectIndex];
}

// ������ǰ��Ʒ
ObjectListNode CharacterObjectList::discardCurrentObject() {
	ObjectListNode tempObject = *_objectList[_currentObjectIndex];
	*_objectList[_currentObjectIndex] = { _currentObjectIndex, {None,nullptr},0 };
	_currentObject = *_objectList[_currentObjectIndex];
	return tempObject;		
}