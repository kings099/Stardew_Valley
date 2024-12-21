/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterObjectList.cpp
 * File Function: 角色物品栏CharacterObjectList类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/15
 * License:       MIT License
 ****************************************************************/

#include <fstream>
#include <algorithm>
#include <functional>
#include "CharacterObjectList.h"

USING_NS_CC;

// 构造函数
CharacterObjectList::CharacterObjectList() :
	_maxObjectKindCount(OBJECT_LIST_ROWS*OBJECT_LIST_COLS),
	_currentObjectIndex(0),
	_openObjectList(false),
	_openBox(false),
	_openShop(false),
	_pickUpCallback(nullptr)
{
	if (!loadData("../GameData/CharacterObjectListData.dat")) {
		// 初始化物品栏
		_objectList.resize(_maxObjectKindCount, { ObjectListNode{ {None,nullptr}, 0 ,Unselected } });
		pickUpObject("BeginnerHoe", 1);
		pickUpObject("BeginnerAxe", 1);
		pickUpObject("BeginnerPickaxe", 1);
		pickUpObject("BeginnerFishingRods", 1);
		pickUpObject("BeginnerKattle", 1);
		pickUpObject("scythe", 1);
	}
	pickUpObject("CopperParticle", 11);
	synthesisObject("Copper");
	synthesisObject("Copper");
	synthesisObject("Iron");
}

// 按下键盘时的处理
void CharacterObjectList::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	static bool isEKeyEnabled = true;
	static bool isRKeyEnabled = true;
	static bool isTKeyEnabled = true;
	// 按下数字键,-和=键时切换物品栏
	if (!_openObjectList) {
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
		// 按下Q键丢弃物品
		if (keyCode == EventKeyboard::KeyCode::KEY_Q && getCurrentObject().count != 0) {
			deleteCurrentObject();
		}
	}
	// 按下E键打开/关闭物品栏
	if (keyCode == EventKeyboard::KeyCode::KEY_E && isEKeyEnabled) {
		_openObjectList = !_openObjectList;
		_openBox = false;
		_openShop = false;
		isRKeyEnabled = !isRKeyEnabled;
		isTKeyEnabled = !isTKeyEnabled;
	}
	// 按下R键打开物品栏和箱子
	if (keyCode == EventKeyboard::KeyCode::KEY_R && isRKeyEnabled) {
		_openObjectList = !_openObjectList;
		_openBox = !_openBox;
		_openShop = false;
		isEKeyEnabled = !isEKeyEnabled;
		isTKeyEnabled = !isTKeyEnabled;
	}
	// 按下T建打开物品栏和商店
	if (keyCode == EventKeyboard::KeyCode::KEY_T && isTKeyEnabled) {
		_openObjectList = !_openObjectList;
		_openBox = false;
		_openShop = !_openShop;
		isEKeyEnabled = !isEKeyEnabled;
		isRKeyEnabled = !isRKeyEnabled;
	}
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameToolObject targetObject, int objectCount, int targetIndex) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameToolObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Tool, targetObjectPtr);
	return pickUpObject(commonObject, objectCount, targetIndex);
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameSeedObject targetObject, int objectCount, int targetIndex) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Seed, targetObjectPtr);
	return pickUpObject(commonObject, objectCount, targetIndex);
}

// 捡起物品
bool CharacterObjectList::pickUpObject(GameBaseObject targetObject, int objectCount, int targetIndex) {
	std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(targetObject);
	GameCommonObject commonObject(GameObjectMapType::Base, targetObjectPtr);
	return pickUpObject(commonObject, objectCount, targetIndex);
}

// 捡起物品
// TODO:设置单个物品的最大存储数量
bool CharacterObjectList::pickUpObject(GameCommonObject targetObject, int objectCount, int targetIndex) {
	// 查找物品栏中是否有相同物品
	auto object = findObjectByObjectList(targetObject);
	bool success = true;

	// 如果没有相同物品，且物品栏已满，则返回false
	if (object.count == 0 && checkObjectListFull()) {
		success =  false;
	}

	// 如果有相同物品且物品栏该物品不是工具，则增加物品数量
	if (object.count > 0 && (targetObject.type == Base)) {
		object.count += objectCount;
	}
	else {
		if (targetIndex == INVAVID_NUM) {
			int insertIndex = -1;
			for (insertIndex = 0; insertIndex < _maxObjectKindCount; insertIndex++) {
				if (_objectList[insertIndex].count == 0) {
					break;
				}
			}
			_objectList[insertIndex] = { { targetObject.type, targetObject.object } , objectCount, Unselected };
		}
		else {
			if (targetIndex< 0||targetIndex >= _maxObjectKindCount || _objectList[targetIndex].count != 0) {
				success = false;
			}
			else {
				_objectList[targetIndex] = { { targetObject.type, targetObject.object } , objectCount, Unselected };
			}

		}
	}
	if (_pickUpCallback) {
		_pickUpCallback(success); 
	}
	return success;
}

// 捡起物品
bool CharacterObjectList::pickUpObject(const std::string& targetObjectName, int objectCount, int targetIndex) {
	return pickUpObject(findObjectByName(targetObjectName), objectCount, targetIndex);
}

// 丢弃当前选中的物品
ObjectListNode CharacterObjectList::deleteCurrentObject() {
	ObjectListNode tempObject = getCurrentObject();
	_objectList[_currentObjectIndex] = { {None,nullptr},0,Selected };
	return tempObject;
}

// 合成物品
bool CharacterObjectList::synthesisObject(GameBaseObject targetObject) {
	if (!targetObject._synthesis) {
		return false;
	}

	// 寻找列表的物品原料
	for (const auto& ingredient : targetObject._ingredients) {
		ObjectListNode ingredientObject = findObjectByObjectList(ingredient.first);
		if (ingredientObject.count < ingredient.second) {
			return false;
		}
	}

	//合成物品
	for (const auto& ingredient : targetObject._ingredients) {
		ObjectListNode ingredientObject = findObjectByObjectList(ingredient.first);
		ingredientObject.count -= ingredient.second;
	}
	pickUpObject(targetObject, 1);
	return true;
}

// 合成物品
bool CharacterObjectList::synthesisObject(const std::string& targetObjectName) {
	 GameCommonObject targetObject = findObjectByName(targetObjectName);
	 if (targetObject.type != Base ) {
		 return false;
	 }

	 GameBaseObject* targetBaseObject = dynamic_cast<GameBaseObject*>(targetObject.object.get());

	 // 寻找列表的物品原料
	 for (const auto& ingredient : targetBaseObject->_ingredients) {
		 ObjectListNode ingredientObject = findObjectByObjectList(ingredient.first);
		 if (ingredientObject.count < ingredient.second) {
			 return false;
		 }
	 }

	 //合成物品
	 for (const auto& ingredient : targetBaseObject->_ingredients) {
		 ObjectListNode ingredientObject = findObjectByObjectList(ingredient.first);
		 ingredientObject.count -= ingredient.second;
	 }
	 pickUpObject(targetObject, 1);
	 return true;
}


// 交换物品
void  CharacterObjectList::swapObject(int startIndex, int targetIndex) {
	if (startIndex < 0 || startIndex >= _maxObjectKindCount) {
		return;
	}
	std::swap(_objectList[startIndex], _objectList[targetIndex]);
	_currentObjectIndex = targetIndex;
}

// 获取当前选中的物品
ObjectListNode CharacterObjectList::getCurrentObject() {
	return _objectList[_currentObjectIndex];
}

// 查找物品栏中是否有指定物品
ObjectListNode CharacterObjectList::findObjectByObjectList(GameCommonObject targetObject) {
	for (int i = 0; i < _maxObjectKindCount; i++) {
		// 只有物品不是工具才会被查找
		if (_objectList[i].count != 0 && _objectList[i].objectNode.object->_index == targetObject.object->_index && (targetObject.type == Base)) {
			return _objectList[i];
		}
	}
	// 没有找到
	return  ObjectListNode{ {None,nullptr}, 0 ,Unselected };
}

// 查找物品栏中是否有指定物品
ObjectListNode CharacterObjectList::findObjectByObjectList(std::string targetObjectName) {
	for (int i = 0; i < _maxObjectKindCount; i++) {
		if (_objectList[i].objectNode.object != nullptr && _objectList[i].objectNode.object->_name == targetObjectName) {
			return _objectList[i];
		}
	}
	return  ObjectListNode{ {None,nullptr}, 0 ,Unselected };
}


// 获取物品栏状态
bool CharacterObjectList::getObjectListStatus() {
	return _openObjectList;
}

// 获取箱子是否打开
bool CharacterObjectList::getBoxStatus() {
	return _openBox;
}

// 获取商店是否打开
bool CharacterObjectList::getStoreStatus() {
	return _openShop;
}

// 查找指定位置的物品信息
ObjectListNode CharacterObjectList::findObjectAtPosition(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return { {None,nullptr},0,Unselected };
	}
	return _objectList[index];
}

// 获取当前选中的物品索引
int CharacterObjectList::getCurrentObjectIndex() {
	return _currentObjectIndex;
}

// 设置当前选中的物品
void CharacterObjectList::setCurrentObject(int index) {
	if (index < 0 || index >= _maxObjectKindCount) {
		return;
	}
	_currentObjectIndex = index;
}

// 设置物品栏状态
void CharacterObjectList::setObjectListStatus(bool status) {
	_openObjectList = static_cast<bool>(status);
}

// 查找物品栏中是否有指定物品
GameCommonObject CharacterObjectList::findObjectByName(const std::string& name) {
{
	GameCommonObject result = { GameObjectMapType::None,nullptr };
	if (name == "None") {
		return result;
	}

	// 尝试从工具对象列表中查找
	for (const auto& tool : GAME_TOOL_OBJECTS_ATTRS) {
		if (tool._name == name) {
			result = GameCommonObject(GameObjectMapType::Tool, std::make_shared<GameToolObject>(tool)); // 创建并返回工具对象
			return result;
		}
	}

	// 尝试从种子对象列表中查找
	for (const auto& seed : GAME_SEED_OBJECTS_ATTRS) {
		if (seed._name == name) {
			result = GameCommonObject(GameObjectMapType::Seed, std::make_shared<GameSeedObject>(seed)); // 创建并返回种子对象
			return result;
		}
	}

	// 尝试从基础对象列表中查找
	for (const auto& base : GAME_BASE_OBJECTS_ATTRS) {
		if (base._name == name) {
			result = GameCommonObject(GameObjectMapType::Base, std::make_shared<GameBaseObject>(base)); // 创建并返回基础对象
			return result;
		}
	}

		// 如果未找到，则返回类型为 None 的 GameCommonObject
		result.type = GameObjectMapType::None;
		result.object = nullptr;
		return result;
	}
}

// 检查物品栏是否已满
bool CharacterObjectList::checkObjectListFull() {
	bool isFull = true;
	for (const auto& item : _objectList) {
		if (item.count == 0) {
			isFull = false;
			break;
		}
	}
	return isFull;
}

// 检查物品栏是否为空
bool CharacterObjectList::checkObjectListEmpty() {
	bool isEmpty = true;
	for (const auto& item : _objectList) {
		if (item.count != 0) {
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

// 回调函数
void CharacterObjectList::setPickUpCallback(std::function<void(bool)> callback) {
	_pickUpCallback = callback;
}

// 保存数据
bool CharacterObjectList::saveData(const std::string& fileName) {
	std::ofstream outFile(fileName, std::ios::binary);
	if (!outFile) {
		CCLOG("Error opening file for writing: %s", fileName.c_str());
		return false;
	}
	int itemCount = OBJECT_LIST_ROWS * OBJECT_LIST_COLS;
	outFile.write(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));
	// 写入物品列表
	for (const auto& item : _objectList) {
		item.save(outFile);
	}
	outFile.close();
	return true;
}

// 加载数据
bool CharacterObjectList::loadData(const std::string& fileName) {
	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile) {
		CCLOG("File does not exist or cannot be opened: %s", fileName.c_str());
		return false;
	}

	int itemCount;
	inFile.read(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));

	_objectList.resize(itemCount);

	// 读取物品列表
	for (auto& item : _objectList) {
		item.load(inFile);
	}

	// 填充空物品
	for (size_t i = 0; i < _objectList.size(); ++i) {
		if (_objectList[i].count == 0) {
			_objectList[i] = ObjectListNode{ {None,nullptr}, 0 ,Unselected };
		}
	}

	inFile.close();
	return true;
}

