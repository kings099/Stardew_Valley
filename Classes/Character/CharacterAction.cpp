/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.cpp
 * File Function: CharacterAction���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
 
# include <fstream>
#include "CharacterAction.h"
#include "Animal/Fish.h"
#include "Control/TimeManager.h"
#include "Box/Box.h"
#include"../proj.win32/Constant.h"

USING_NS_CC;

// ���캯��
CharacterAction::CharacterAction():
	CharacterObjectList(),
	CharacterMove()
{
	if (!loadData("../GameData/CharacterActionData.dat")) {
		for (int i = 0; i < SKILL_KIND_NUM; i++) {
			_skillLevel[i] = 1;
			_skillExprience[i] = 1;
			_money = START_UP_MONEY;
		}
	}
	_money = START_UP_MONEY*10;
	updateSkillLevel();
}

 // ��������¼���������
bool CharacterAction::onMouseDown(cocos2d::Event* event, GameCharacterAction& gameCharacterAction, cocos2d::Vec2& targetTilePos, InteractionManager* interactionManager) {
	const EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	stopMove();
	if (!getObjectListStatus()) {
		if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			gameCharacterAction = getLeftButtonAction();
		}
		else if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			gameCharacterAction = getRightButtonAction();
		}
		if (checkActionIsValid(gameCharacterAction, targetTilePos, interactionManager)) {
			getObject(gameCharacterAction, interactionManager);
			updateSkillExprience(gameCharacterAction);
			updateSkillLevel();
			return true;
		}
		else {
			gameCharacterAction = NoneAction;
			return false;
		}
	}
	return false;
}

// �����Ʒ
void CharacterAction::getObject(GameCharacterAction action, InteractionManager* interactionManager) {
	TileInfo targetTileNode = getTileInfo(action, interactionManager);
	std::string fishName = Fishs::catchFish(TimeManager::getInstance()->getCurrentSeason(),_skillLevel[Fish]);
	switch (action) {
		case NoneAction:
			break;
		// ���Ի����Ʒ�Ķ���
		case Weeding:
		case Cutting:
		case Mining:
			for (const auto& drop : targetTileNode.drops) {
				int probability = rand() % 100 + 1;
				if (probability >= drop.second.second * 100) {
					pickUpObject(drop.first, drop.second.first);
				}
			}
			break;
		case Fishing:
			if (fishName != "") {
				pickUpObject(fishName, 1);
			}
			break;
		
		// û����Ʒ�ı�Ķ���
		case DestoryObject:
			break;
		default:
			break;
	}
}

// ʹ����Ʒ
void CharacterAction::useObject(GameCharacterAction action, InteractionManager* interactionManager) {
	TileInfo targetTileNode = getTileInfo(action, interactionManager);
	switch (action) {
		// ��Ҫ������Ʒ�Ķ���
	case Seeding:
	case Placement:
		if (getCurrentObject().objectNode.object->_name == "Box") {	//��������
			Box::getInstance().addBox(BoxNode(targetTileNode.WorldPos));
		}
		deleteObject(1, getCurrentObjectIndex());
		break;
	}
}

// ��ȡ���ܵȼ�
int CharacterAction::getSkillLevel(GameObjectSkillType skillType) {
	if (skillType < 0 || skillType >= SKILL_KIND_NUM)
		return -1;
	return _skillLevel[skillType];
}

// ��ȡ���ܵȼ�
int CharacterAction::getMoney() {
	return _money;
}

// �޸Ľ�ɫ��Ǯ
void CharacterAction::setMoney(int money) {
	_money += money;
}


// ��ȡ��ɫ����ִ�еĶ���(������)
GameCharacterAction CharacterAction::getLeftButtonAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
	case None:
		return DestoryObject;
	case Tool: {
		auto toolObjectPtr = std::dynamic_pointer_cast<GameToolObject>(currentObject.objectNode.object);
		return toolObjectPtr->_action;
	}
	case Base:
		if (currentObject.objectNode.object->_name == "Fertilizer") {
			return Fertilize;
		}
		else {
			return DestoryObject;
		}
	default:
		return NoneAction;
	}
}

// ��ȡ��ɫ����ִ�еĶ���(����Ҽ�)
GameCharacterAction CharacterAction::getRightButtonAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
	case None:
		return NoneAction;
	case Tool: {
		if ((currentObject.objectNode.object->_name == "BeginnerKattle")
			|| (currentObject.objectNode.object->_name == "IntermediateKattle")
			|| (currentObject.objectNode.object->_name == "AdvancedKattle")) {
			return GetWater;
		}
		else {
			return NoneAction;
		}
	}
	case Seed:
		return Seeding;
	case Base:
		return Placement;
	default:
		return NoneAction;
	}
}

// �жϽ�ɫ�Ƿ����ִ�ж���
bool CharacterAction::checkActionIsValid(GameCharacterAction action, Vec2& targetTilePos, InteractionManager* interactionManager) {
	if (action == NoneAction)
		return NoneAction;

	TileInfo targetTileNode = getTileInfo(action, interactionManager);
	targetTilePos = targetTileNode.tilePos;
	// ��鶯���Ƿ���Ŀ��ؿ�����ƥ��
	for (auto& test : ACTION_TO_TILEMAP) {
		if (action == test.first) {
			for (auto& tileType : test.second) {
				if (tileType == targetTileNode.type) {
					if (action == Watering) {
							
						}

					return action;
				}
			}
		}
	}
	return NoneAction;
}

// ��ȡ��ɫ�����������Ƭ��Ϣ
TileInfo CharacterAction::getTileInfo(GameCharacterAction action, InteractionManager* interactionManager) {
	TileInfo targetTileNode;
	switch (action) {
	case Fishing:
		targetTileNode = interactionManager->GetLineTileInfo(_currentDirection, std::min(_skillLevel[Fish] + MIN_FISHING_DISTANCE, MAX_FISHING_DISTANCE), _character->getPosition());
		break;
	case NoneAction:
		targetTileNode = { TileConstants::TileType::Other, cocos2d::Vec2(INVAVID_NUM, INVAVID_NUM),false };
		break;
	default:
		targetTileNode = interactionManager->GetLineTileInfo(_currentDirection, 1, _character->getPosition());
		break;
	}

	return targetTileNode;
}

// ���¼��ܵȼ�
void CharacterAction::updateSkillLevel() {
	// ���¼��ܵȼ�
	for (int i = 0; i < SKILL_KIND_NUM; i++) {
		if (LEVEL1_TO_LEVEL2_EXPRIENCE<=_skillExprience[i] && _skillExprience[i]<=LEVEL2_TO_LEVEL3_EXPRIENCE) {
			_skillLevel[i] = 2;
		}
		else if (LEVEL2_TO_LEVEL3_EXPRIENCE<= _skillExprience[i] && _skillExprience[i]<=LEVEL3_TO_LEVEL4_EXPRIENCE) {
			_skillLevel[i] = 3;
		}
		else if (LEVEL3_TO_LEVEL4_EXPRIENCE<=_skillExprience[i] && _skillExprience[i]<=LEVEL4_TO_LEVEL5_EXPRIENCE) {
			_skillLevel[i] = 4;
		}
		else if (_skillExprience[i] >= LEVEL4_TO_LEVEL5_EXPRIENCE) {
			_skillLevel[i] = 5;
		}
	}
}


// ���¼��ܾ���ֵ
void CharacterAction::updateSkillExprience(GameCharacterAction gameCharacterAction) {
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
}



// ��������
bool CharacterAction::saveData(const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary );
	if (!outFile) {
		CCLOG("Error opening file for writing: %s", fileName.c_str());
		return false;
	}

	outFile.write((char*)&_money, sizeof(int));
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

	inFile.read((char*)&_money, sizeof(int));

	for (auto& exp : _skillExprience) {
		inFile.read((char*)&exp, sizeof(int));
	}
	for (auto& level : _skillLevel) {
		inFile.read((char*)&level, sizeof(int));
	}

	inFile.close();
	return true;
}