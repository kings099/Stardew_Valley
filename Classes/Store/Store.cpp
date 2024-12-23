/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.cpp
 * File Function: 商店Store类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#include "Store.h"

// 获取单例
Store* Store::getInstance() {
	static Store instance;
	return &instance;
}

 // 构造函数
Store::Store() :
	productKindCount(PRODUCE_KIND_NUM_EACH_DAY)
{
	_character = Character::getInstance();
	_product.clear();
}

// 新的一天刷新商店货物
void Store::refreshStock() {
	_product.clear();
	int seedProductKind = rand() % PRODUCE_KIND_NUM_EACH_DAY+1;	//至少有一个种子
	int baseProductKind = PRODUCE_KIND_NUM_EACH_DAY - seedProductKind;
	
	// 随机选取后要判断是否能购买以及角色技能等级是否能解锁
	for (int i = 0; i < seedProductKind; i++) {
		int seedIndex = INVAVID_NUM;
		do {
			seedIndex = rand() % GAME_SEED_OBJECTS_ATTRS.size();
		} while (!(_character->getSkillLevel(GAME_SEED_OBJECTS_ATTRS[seedIndex]._type) >= GAME_SEED_OBJECTS_ATTRS[seedIndex]._level));

		int productCount = rand() % MAX_PRODUCT_COUNT_EACH_DAY + 1;
		std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameSeedObject>(GAME_SEED_OBJECTS_ATTRS[seedIndex]);
		GameCommonObject commonObject(GameObjectMapType::Seed, targetObjectPtr);
		_product.push_back(ProductNode{ commonObject , productCount, productCount * GAME_SEED_OBJECTS_ATTRS[seedIndex]._buyPrice,GAME_SEED_OBJECTS_ATTRS[seedIndex]._season,static_cast<Season>((GAME_SEED_OBJECTS_ATTRS[seedIndex]._season+2)%4) });
	}

	for (int i = seedProductKind; i < productKindCount; i++) {
		int baseIndex = INVAVID_NUM;
		do {
			baseIndex = rand() % GAME_BASE_OBJECTS_ATTRS.size();
		} while (!(GAME_BASE_OBJECTS_ATTRS[baseIndex]._buy 
			&& (_character->getSkillLevel(GAME_BASE_OBJECTS_ATTRS[baseIndex]._type) >= GAME_BASE_OBJECTS_ATTRS[baseIndex]._level)));
		int productCount = rand() % MAX_PRODUCT_COUNT_EACH_DAY + 1;
		std::shared_ptr<GameObject> targetObjectPtr = std::make_shared<GameBaseObject>(GAME_BASE_OBJECTS_ATTRS[baseIndex]);
		GameCommonObject commonObject(GameObjectMapType::Base, targetObjectPtr);

		GameSeedObject seedObject;
		if (canHarvestFromAnySeed(GAME_BASE_OBJECTS_ATTRS[baseIndex], seedObject)) {
			_product.push_back(ProductNode{ commonObject , productCount, productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice, seedObject._season,static_cast<Season>((seedObject._season+2)%4) });
		}
		else {
			_product.push_back(ProductNode{ commonObject , productCount, productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice ,All ,All });
	    }
	}
	// 根据季节更新价格
	updatePrices();
}

// 购买商品
bool Store::buyProduct(int index) {  
	int characterMoney = _character->getMoney();
	if (characterMoney < _product[index].totalPrice) {
		return false;
	}
	else if (_product[index].product.type == None) {
		return false;
	}
	
	if (_character->pickUpObject(_product[index].product, _product[index].count) == true) {
		_character->setMoney(_product[index].totalPrice * -1);
		_product[index] = { {  None,nullptr}, 0, 0, Season::All, Season::All };
		return true;
	}
	return false;
}

// 出售商品
bool Store::sellProduct(const GameCommonObject targetObject, int objectCount) {
	int salePrice = 0;
	if (targetObject.type == Tool) {
		return false;
	}
	else if (targetObject.type == Seed) {
		GameSeedObject* seedObject = dynamic_cast<GameSeedObject*>(_character->getCurrentObject().objectNode.object.get());
		salePrice = seedObject->_sellPrice;
	}
	else if (targetObject.type == Base) {
		GameBaseObject* baseObject = dynamic_cast<GameBaseObject*>(_character->getCurrentObject().objectNode.object.get());
		if (baseObject->_sell == false) {
			return false;
		}
		salePrice = baseObject->_sellPrice;
	}
	_character->deleteCurrentObject();
	_character->setMoney(objectCount*salePrice);
	_sellProductCallback(true);
	return true;
}

// 查找指定位置的商品信息
ProductNode Store::findObjectAtPosition(int index) {
	if (index < 0 || index >= _product.size()) {
		return ProductNode();
	}

	return _product[index];
}

// 回调函数
void Store::setSellProductCallback(std::function<void(bool)> callback) {
	_sellProductCallback = callback;
}

// 更新价格
void Store::updatePrices() {
	_timeManager = TimeManager::getInstance();

	// 根据季节更新价格
	const int season = _timeManager->getCurrentSeason();
	for (int i = 0; i < _product.size(); i++) {
		// 物品存在价格浮动
		if (_product[i].discountSeason != Season::All) {
			if (_product[i].discountSeason == season) {	// 打折
				_product[i].totalPrice *= DISCOUNT_RATE_BY_SEASON;
			}
			else if (_product[i].increaseSeason == season) {// 涨价
				_product[i].totalPrice *= INCREASE_RATE_BY_SEASON;
			}
		}
	}

	// 根据日期更新价格
	std::string weekDay = _timeManager->getWeekDay();
	if (weekDay == "Thursday") {
		for (int i = 0; i < _product.size(); i++) {
			_product[i].totalPrice *= DISCOUNT_RATE_BY_SEASON;
		}
	}
}

// 判断物品是否是种子的收获物
bool Store::canHarvestFromAnySeed(const GameBaseObject& baseObject,  GameSeedObject& seedObject) {
	for (const auto seed : GAME_SEED_OBJECTS_ATTRS) { // 使用常量引用遍历
		if (baseObject._index == seed._harvestIndex) {
			seedObject = seed;
			return true;
		}
	}
	return false; // 如果没有找到
}
