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
#include"../proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
CharacterAction::CharacterAction(const std::string &filename):
	CharacterObjectList(),
	CharacterMove(filename)
{
	if (!loadData("../GameData/CharacterActionData.dat")) {
		for (int i = 0; i < SKILL_KIND_NUM; i++) {
			_skillLevel[i] = 0;
			_skillExprience[i] = 0;
			_money = START_UP_MONEY;
		}
	}
	updateSkillLevel();
}

 // 按下鼠标事件触发函数
void CharacterAction::onMouseDown(cocos2d::Event* event, GameCharacterAction& gameCharacterAction, cocos2d::Vec2& targetTilePos, InteractionManager* interactionManager) {
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
			updateSkillExprience(gameCharacterAction);
			updateSkillLevel();
		}
		else {
			gameCharacterAction = NoneAction;
		}
	}
}

// 获取角色打算执行的动作(鼠标左键)
GameCharacterAction CharacterAction::getLeftButtonAction() {
	ObjectListNode currentObject = getCurrentObject();
	switch (currentObject.objectNode.type) {
	case None:
		return NoneAction;
	case Tool: {
		auto toolObjectPtr = std::dynamic_pointer_cast<GameToolObject>(currentObject.objectNode.object);
		return toolObjectPtr->_action;
	}
	case Base:
		if (currentObject.objectNode.object->_name == "fertilizer") {
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
	case Base:
		return Placement;
	default:
		return NoneAction;
	}
}

// 判断角色是否可以执行动作
bool CharacterAction::checkActionIsValid(GameCharacterAction action,Vec2 & targetTilePos, InteractionManager* interactionManager) {
	if (action == NoneAction)
		return NoneAction;

	TileInfo targetTileNode = getTileInfo(action, interactionManager);
	targetTilePos = targetTileNode.tilePos;
	// 检查动作是否与目标地块类型匹配
	for (auto& test : ACTION_TO_TILEMAP) {
		if (action == test.first && targetTileNode.type == test.second) {
			return action;
		}
	}
	return NoneAction;
}

// 获取角色动作对象的瓦片信息
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

// 更新技能等级
void CharacterAction::updateSkillLevel() {
	// 更新技能等级
	for (int i = 0; i < SKILL_KIND_NUM; i++) {
		if (LEVEL0_TO_LEVEL1_EXPRIENCE<=_skillExprience[i] && _skillExprience[i]<=LEVEL1_TO_LEVEL2_EXPRIENCE) {
			_skillLevel[i] = 1;
		}
		else if (LEVEL1_TO_LEVEL2_EXPRIENCE<=_skillExprience[i] && _skillExprience[i]<=LEVEL2_TO_LEVEL3_EXPRIENCE) {
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

// 获取技能等级
int CharacterAction::getSkillLevel(int index) {
	if (index < 0 || index >= SKILL_KIND_NUM)
		return -1;
	return _skillLevel[index];
}

// 获取物品
void CharacterAction::getObject() {

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