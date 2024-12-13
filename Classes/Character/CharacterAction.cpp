/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.cpp
 * File Function: CharacterAction���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/11
 * License:       MIT License
 ****************************************************************/
 
#include "CharacterAction.h"

USING_NS_CC;

 // ��������¼���������
void CharacterAction::onMouseDown(cocos2d::Event* event) {
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	const GameCharacterAction action = getAction();
	const cocos2d::Vec2& currentPosition = getPosition();
	// ���������ִ�еĶ���
	if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

	}
	// �������Ҽ�ִ�еĶ���
	else if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {

	}
}

// ��ȡ��ɫ����ִ�еĶ���
GameCharacterAction CharacterAction::getAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
		//�������
	case None:
		return NoneAction;
	case Tool:{
		auto toolObjectPtr = std::dynamic_pointer_cast<GameToolObject>(currentObject.objectNode.object);
		return toolObjectPtr->_action;
	}
		//�Ҽ�����
	case Seed:
	case Base:
		return Placement;
	default:
		return NoneAction;
	}
}

// �жϽ�ɫ�Ƿ����ִ�ж���
bool CharacterAction::checkActionIsValid() {
	const GameCharacterAction action = getAction();
	const cocos2d::Vec2& position = getPosition();

	if (action == NoneAction)
		return false;

	return true;
	// TODO: ��Ͻ�ɫ������Χ�ؿ���Ϣ���ж϶����Ƿ���Ч
}

// ִ�ж���
void CharacterAction::doAction() {
	if(!checkActionIsValid())
		return;

	const GameCharacterAction action = getAction();
}