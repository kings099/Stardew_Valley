/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.cpp
 * File Function: CharacterAction���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/11
 * License:       MIT License
 ****************************************************************/
 
#include "CharacterAction.h"
#include"../proj.win32/Constant.h"

USING_NS_CC;

// ���캯��
CharacterAction::CharacterAction(const std::string &filename):
	CharacterObjectList(),
	CharacterMove(filename)
{
	for (int i = 0; i < SKILL_KIND_NUM; i++) {
		_sikllLevel[i] = 0;
		_sikllExprience[i] = 0;
	}
}

 // ��������¼���������
void CharacterAction::onMouseDown(cocos2d::Event* event) {
	const EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	const GameCharacterAction action = getAction();
	const cocos2d::Vec2& currentPosition = getPosition();
	stopMove();
	const bool actionResult = (checkActionIsValid()==true) ? 1 : 0;
	if (actionResult) {
		updateSkillLevel();
	}
	CCLOG("ACTION: %d,%d", action, actionResult);
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
	const auto position = getPosition();

	if (action == NoneAction)
		return false;
	TileInfo targetTileNode;
	switch (_currentDirection) {
	case Direction::Up:
		targetTileNode = _surroundingTilesInfo[1];
		break;
	case Direction::Down:
		targetTileNode = _surroundingTilesInfo[7];
		break;
	case Direction::Left:
		targetTileNode = _surroundingTilesInfo[3];
		break;
	case Direction::Right:
		targetTileNode = _surroundingTilesInfo[5];
		break;
	default:
		break;
	}

	// ��鶯���Ƿ���Ŀ��ؿ�����ƥ��
	for (auto& test : ACTION_TO_TILEMAP) {
		if (action == test.first && targetTileNode.type == test.second) {
			return true;
		}
	}
	return false;
}

// ִ�ж���
void CharacterAction::doAction() {
	if(!checkActionIsValid())
		return;

	const GameCharacterAction action = getAction();
}

// ���¼��ܵȼ�
void CharacterAction::updateSkillLevel() {
	for (int i = 0; i < SKILL_KIND_NUM; i++) {
		if (_sikllExprience[i] >= LEVEL0_TO_LEVEL1_EXPRIENCE) {
			_sikllLevel[i] = 1;
		}
		else if (_sikllExprience[i] >= LEVEL1_TO_LEVEL2_EXPRIENCE) {
			_sikllLevel[i] = 2;
		}
		else if (_sikllExprience[i] >= LEVEL2_TO_LEVEL3_EXPRIENCE) {
			_sikllLevel[i] = 3;
		}
		else if (_sikllExprience[i] >= LEVEL3_TO_LEVEL4_EXPRIENCE) {
			_sikllLevel[i] = 4;
		}
		else if (_sikllExprience[i] >= LEVEL4_TO_LEVEL5_EXPRIENCE) {
			_sikllLevel[i] = 5;
		}
	}
}