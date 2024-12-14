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
void CharacterAction::onMouseDown(cocos2d::Event* event, GameCharacterAction& gameCharacterAction, cocos2d::Vec2& targetTilePos) {
	const EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	stopMove();
	gameCharacterAction = checkActionIsValid(targetTilePos);
	if (gameCharacterAction != NoneAction) {
		updateSkillExprienceAndLevel(gameCharacterAction);
	}
}

// ��ȡ��ɫ����ִ�еĶ���
GameCharacterAction CharacterAction::getAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
		//�������
	case None:
		return NoneAction;
	case Tool: {
		auto toolObjectPtr = std::dynamic_pointer_cast<GameToolObject>(currentObject.objectNode.object);
		return toolObjectPtr->_action;
	}
	case Seed:
	case Base:
		return Placement;
	default:
		return NoneAction;
	}
}

// �жϽ�ɫ�Ƿ����ִ�ж���
GameCharacterAction CharacterAction::checkActionIsValid(Vec2 & targetTilePos) {
	const GameCharacterAction action = getAction();
	
	if (action == NoneAction)
		return NoneAction;

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
			return action;
		}
	}
	return NoneAction;
}

// ���¼��ܾ���ֵ�͵ȼ�
void CharacterAction::updateSkillExprienceAndLevel(GameCharacterAction gameCharacterAction) {
	// ���¼��ܾ���ֵ
	switch (gameCharacterAction) {
	case Plowing:
	case Harvesting:
		_sikllExprience[Farm]++;
		break;
	case Weeding:
	case Cutting:
		_sikllExprience[Collect]++;
		break;
	case Mining:
		_sikllExprience[Mine]++;
		break;
	case Fishing:
		_sikllExprience[Fish]++;
		break;
	default:
		break;
	}

	// ���¼��ܵȼ�
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