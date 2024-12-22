/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.cpp
 * File Function: CharacterAction类的实现
 * Author:        尹诚成
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

// 构造函数
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

 // 按下鼠标事件触发函数
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

		if (gameCharacterAction != NoneAction) {
			_targetTileNode = getTileInfo(interactionManager, gameCharacterAction);
		}
		targetTilePos = _targetTileNode.tilePos;
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

// 获得物品
void CharacterAction::getObject(GameCharacterAction action, InteractionManager* interactionManager) {
	std::string fishName = Fishs::catchFish(TimeManager::getInstance()->getCurrentSeason(),_skillLevel[Fish]);
	int probability = rand() % 100 + 1, extraObject = rand() % 100 + 1;
	int extraObjectProbability = 100;
	switch (action) {
		case NoneAction:
			break;
		// 可以获得物品的动作
		case Weeding:
			extraObjectProbability -= _skillLevel[Farm] * SKILL_GET_ITEM_PROBABILITY * 100;
		case Cutting:
			extraObjectProbability -= _skillLevel[Collect] * SKILL_GET_ITEM_PROBABILITY * 100;
		case Mining:
			extraObjectProbability -= _skillLevel[Mine] * SKILL_GET_ITEM_PROBABILITY * 100;
		case Harvesting:
			extraObjectProbability -= _skillLevel[Farm]* SKILL_GET_ITEM_PROBABILITY * 100;
			for (const auto& drop : _targetTileNode.drops) {
				if (probability >= drop.second.second * 100) {
					pickUpObject(drop.first, drop.second.first);
				}
				if (extraObject >= extraObjectProbability) {
					pickUpObject(drop.first, 1);
				}
			}
			break;
		case Fishing:
			if (fishName != "") {
				pickUpObject(fishName, 1);
			}
			break;
		
		// 没有物品改变的动作
		//case DestoryObject:
			break;
		default:
			break;
	}
}

// 使用物品
void CharacterAction::useObject(GameCharacterAction action, InteractionManager* interactionManager) {
	switch (action) {
		// 需要消耗物品的动作
	case Seeding:
	case Placement:
		if (getCurrentObject().objectNode.object->_name == "Box") {	//放置箱子
			Box::getInstance().addBox(BoxNode(_targetTileNode.WorldPos));
		}
		deleteObject(1, getCurrentObjectIndex());
		break;
	}
}

// 获取技能等级
int CharacterAction::getSkillLevel(GameObjectSkillType skillType) {
	if (skillType < 0 || skillType >= SKILL_KIND_NUM)
		return -1;
	return _skillLevel[skillType];
}

// 获取技能等级
int CharacterAction::getMoney() {
	return _money;
}

// 修改角色金钱
void CharacterAction::setMoney(int money) {
	_money += money;
}


// 获取角色打算执行的动作(鼠标左键)
GameCharacterAction CharacterAction::getLeftButtonAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
	case None:
		if (_targetTileNode.type == TileConstants::TileType::Crop) {
			return Debug;
		}
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

// 获取角色打算执行的动作(鼠标右键)
GameCharacterAction CharacterAction::getRightButtonAction() {
	ObjectListNode currentObject = getCurrentObject();
	if (_targetTileNode.type == TileConstants::TileType::Crop) {
		return Harvesting;
	}
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
		if (!_targetTileNode.isObstacle) {
			return Placement;
		}
		return NoneAction;
	default:
		return NoneAction;
	}
}

// 判断角色是否可以执行动作
bool CharacterAction::checkActionIsValid(GameCharacterAction action, Vec2& targetTilePos, InteractionManager* interactionManager) {
	if (action == NoneAction)
		return false;

	// 检查动作是否与目标地块类型匹配
	for (auto& test : ACTION_TO_TILEMAP) {
		if (action == test.first) {
			for (auto& tileType : test.second) {
				if (tileType == _targetTileNode.type) {
					return true;
				}
			}
		}
	}
	if (action == Placement && !_targetTileNode.isObstacle) {
		return true;
	}
	return false;
}

// 获取角色动作对象的瓦片信息
TileInfo CharacterAction::getTileInfo( InteractionManager* interactionManager, GameCharacterAction action) {
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

// 更新技能等级
void CharacterAction::updateSkillLevel() {
	// 更新技能等级
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


// 更新技能经验值
void CharacterAction::updateSkillExprience(GameCharacterAction gameCharacterAction) {
	// 更新技能经验值
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

// 保存数据
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

// 加载数据
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