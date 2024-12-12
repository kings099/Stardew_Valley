/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.cpp
 * File Function: CharacterAction类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/11
 * License:       MIT License
 ****************************************************************/
 
#include "CharacterAction.h"

USING_NS_CC;

 // 按下鼠标事件触发函数
void CharacterAction::onMouseDown(cocos2d::Event* event) {
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	const GameCharacterAction action = getAction();
	const cocos2d::Vec2& currentPosition = getPosition();
	// 点击鼠标左键执行的动作
	if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

	}
	// 点击鼠标右键执行的动作
	else if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {

	}
}

// 获取角色打算执行的动作
GameCharacterAction CharacterAction::getAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
		//左键动作
	case None:
		return NoneAction;
	case Tool:{
		auto toolObjectPtr = std::dynamic_pointer_cast<GameToolObject>(currentObject.objectNode.object);
		return toolObjectPtr->_action;
	}
		//右键动作
	case Seed:
	case Base:
		return Placement;
	default:
		return NoneAction;
	}
}

// 判断角色是否可以执行动作
bool CharacterAction::checkActionIsValid() {
	const GameCharacterAction action = getAction();
	const cocos2d::Vec2& position = getPosition();

	if (action == NoneAction)
		return false;

	return true;
	// TODO: 结合角色坐标周围地块信息，判断动作是否有效
}

// 执行动作
void CharacterAction::doAction() {
	if(!checkActionIsValid())
		return;

	const GameCharacterAction action = getAction();
}