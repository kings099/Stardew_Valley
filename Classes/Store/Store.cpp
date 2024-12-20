/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.cpp
 * File Function: �̵�Store���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#include "Store.h"

 // ���캯��
Store::Store() :
	productKindCount(PRODUCE_KIND_NUM_EACH_DAY)
{
	_character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
	_product.clear();
}

// �µ�һ��ˢ���̵����
void Store::refreshStock() {
	srand(static_cast<unsigned int>(time(0)));

	int seedProductKind = rand() % PRODUCE_KIND_NUM_EACH_DAY;
	int baseProductKind = PRODUCE_KIND_NUM_EACH_DAY - seedProductKind;
	
	// ���ѡȡ��Ҫ�ж��Ƿ��ܹ����Լ���ɫ���ܵȼ��Ƿ��ܽ���
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

// ������Ʒ
bool Store::buyProduct(int index) {
	int characterMoney = _character->getMoney();
	if (characterMoney < _product[index].totalPrice) {
		return false;
	}
	
	_character->setMoney(_product[index].totalPrice * -1);
	_character->pickUpObject(_product[index].product, _product[index].count);

	return true;
}

// ������Ʒ
bool Store::sellProduct(GameSeedObject targetObject, int objectCount) {
	_character->deleteCurrentObject();
	_character->setMoney(targetObject._salePrice * objectCount);
	return true;
}

// ������Ʒ
bool Store::sellProduct(GameBaseObject targetObject, int objectCount) {
	if(targetObject._sale == false)
		return false;
	_character->deleteCurrentObject();
	_character->setMoney(targetObject._salePrice * objectCount);
	return true;
}

// ���ݼ��ڸ��¼۸�
void Store::updatePrices() {
	_timeManager = TimeManager::getInstance();
	int season = _timeManager->getCurrentSeason();
	for (int i = 0; i < _product.size(); i++) {
		// ��Ʒ���ڼ۸񸡶�
		if (_product[i].discountSeason != Season::All) {
			if (_product[i].discountSeason == season) {	// ����
				_product[i].totalPrice *= DISCOUNT_RATE_BY_SEASON;
			}
			else if (_product[i].increaseSeason == season) {// �Ǽ�
				_product[i].totalPrice *= INCREASE_RATE_BY_SEASON;
			}
		}
	}
}

bool Store::canHarvestFromAnySeed(const GameBaseObject& baseObject,  GameSeedObject* seedObject) {
	for (const auto& seed : GAME_SEED_OBJECTS_ATTRS) { // ʹ�ó������ñ���
		if (baseObject._index == seed._harvestIndex) {
			*seedObject = seed;
			return true;
		}
	}
	return false; // ���û���ҵ������� nullptr
}
