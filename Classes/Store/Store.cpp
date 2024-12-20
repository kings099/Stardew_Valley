/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.cpp
 * File Function: 商店Store类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#include "Store.h"

 // 构造函数
Store::Store() :
	productKindCount(PRODUCE_KIND_NUM_EACH_DAY)
{
	_character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
	_product.clear();
}

// 新的一天刷新商店货物
void Store::refreshStock() {
	srand(static_cast<unsigned int>(time(0)));

	int seedProductKind = rand() % PRODUCE_KIND_NUM_EACH_DAY;
	int baseProductKind = PRODUCE_KIND_NUM_EACH_DAY - seedProductKind;
	
	// 随机选取后要判断是否能购买以及角色技能等级是否能解锁
	for (int i = 0; i < seedProductKind; i++) {
		int seedIndex = INVAVID_NUM;
		do {
			seedIndex = rand() % GAME_BASE_OBJECTS_ATTRS.size();
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
		GameCommonObject commonObject(GameObjectMapType::Seed, targetObjectPtr);

		GameSeedObject *seedObject;
		if (canHarvestFromAnySeed(GAME_BASE_OBJECTS_ATTRS[baseIndex], seedObject)) {
			_product.push_back(ProductNode{ commonObject , productCount, productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice, seedObject->_season,static_cast<Season>((seedObject->_season+2)%4) });
		}
		else {
			_product.push_back(ProductNode{ commonObject , productCount, productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice ,All ,All });
		}
	
	}

	updatePrices();
}

// 购买商品
bool Store::buyProduct(int index) {
	int characterMoney = _character->getMoney();
	if (characterMoney < _product[index].totalPrice) {
		return false;
	}
	
	_character->setMoney(_product[index].totalPrice * -1);
	_character->pickUpObject(_product[index].product, _product[index].count);

	return true;
}

// 出售商品
bool Store::sellProduct(GameSeedObject targetObject, int objectCount) {
	_character->deleteCurrentObject();
	_character->setMoney(targetObject._salePrice * objectCount);
	return true;
}

// 出售商品
bool Store::sellProduct(GameBaseObject targetObject, int objectCount) {
	if(targetObject._sale == false)
		return false;
	_character->deleteCurrentObject();
	_character->setMoney(targetObject._salePrice * objectCount);
	return true;
}

// 根据季节更新价格
void Store::updatePrices() {
	_timeManager = TimeManager::getInstance();
	int season = _timeManager->getCurrentSeason();
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
}

bool Store::canHarvestFromAnySeed(const GameBaseObject& baseObject,  GameSeedObject* seedObject) {
	for (const auto& seed : GAME_SEED_OBJECTS_ATTRS) { // 使用常量引用遍历
		if (baseObject._index == seed._harvestIndex) {
			*seedObject = seed;
			return true;
		}
	}
	return false; // 如果没有找到，返回 nullptr
}
