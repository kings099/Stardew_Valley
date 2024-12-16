/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.cpp
 * File Function: CharacterAction���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/11
 * License:       MIT License
 ****************************************************************/
 
# include <fstream>
#include "CharacterAction.h"
#include"../proj.win32/Constant.h"

USING_NS_CC;

// ���캯��
CharacterAction::CharacterAction(const std::string &filename):
	CharacterObjectList(),
	CharacterMove(filename)
{
	if (!loadData("../GameData/CharacterActionData.dat")) {
		for (int i = 0; i < SKILL_KIND_NUM; i++) {
			_skillLevel[i] = i;
			_skillExprience[i] = 0;
		}
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
	targetTilePos = targetTileNode.tilePos;
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
		_skillExprience[Farm]++;
		break;
	case Weeding:
	case Cutting:
		_skillExprience[Collect]++;
		break;
	case Mining:
		_skillExprience[Mine]++;
		break;
	case Fishing:
		_skillExprience[Fish]++;
		break;
	default:
		break;
	}

	// ���¼��ܵȼ�
	for (int i = 0; i < SKILL_KIND_NUM; i++) {
		if (_skillExprience[i] >= LEVEL0_TO_LEVEL1_EXPRIENCE) {
			_skillLevel[i] = 1;
		}
		else if (_skillExprience[i] >= LEVEL1_TO_LEVEL2_EXPRIENCE) {
			_skillLevel[i] = 2;
		}
		else if (_skillExprience[i] >= LEVEL2_TO_LEVEL3_EXPRIENCE) {
			_skillLevel[i] = 3;
		}
		else if (_skillExprience[i] >= LEVEL3_TO_LEVEL4_EXPRIENCE) {
			_skillLevel[i] = 4;
		}
		else if (_skillExprience[i] >= LEVEL4_TO_LEVEL5_EXPRIENCE) {
			_skillLevel[i] = 5;
		}
	}
}

// ��ȡ���ܵȼ�
int CharacterAction::getSkillLevel(int index) {
	if (index < 0 || index >= SKILL_KIND_NUM)
		return -1;
	return _skillLevel[index];
}

// ��������
bool CharacterAction::saveData(const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary );
	if (!outFile) {
		CCLOG("Error opening file for writing: %s", fileName.c_str());
		return false;
	}

	for (const auto& exp : _skillExprience) {
		outFile.write((char*)&exp, sizeof(int));
	}
	for (const auto& level : _skillLevel) {
		outFile.write((char*)&level, sizeof(int));
	}

	outFile.close();
	return true;
}

// ��������
bool CharacterAction::loadData(const std::string& fileName) {
	if (!fileExists(fileName)) {
		CCLOG("File does not exist %s", fileName.c_str());
		return false;
	}

	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile) {
		CCLOG("File cannot be opened: %s", fileName.c_str());
		return false;
	}

	// ��ȡ��ǰλ��
	std::streampos currentPos = inFile.tellg();

	for (auto& exp : _skillExprience) {
		inFile.read((char*)&exp, sizeof(int));
	}
	for (auto& level : _skillLevel) {
		inFile.read((char*)&level, sizeof(int));
	}

	inFile.close();
	return true;
}