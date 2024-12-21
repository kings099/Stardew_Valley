/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.cpp
 * File Function: �̵�Store���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#include "Store.h"

// ��ȡ����
Store* Store::getInstance() {
	static Store instance;
	return &instance;
}

 // ���캯��
Store::Store() :
	productKindCount(PRODUCE_KIND_NUM_EACH_DAY)
{
	_character = Character::getInstance();
	_product.clear();
}

// �µ�һ��ˢ���̵����
void Store::refreshStock() {
	_product.clear();
	int seedProductKind = rand() % PRODUCE_KIND_NUM_EACH_DAY;
	int baseProductKind = PRODUCE_KIND_NUM_EACH_DAY - seedProductKind;
	
	// ���ѡȡ��Ҫ�ж��Ƿ��ܹ����Լ���ɫ���ܵȼ��Ƿ��ܽ���
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
	// ���ݼ��ڸ��¼۸�
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
	_product[index] = { {  None,nullptr}, 0, 0, Season::All, Season::All };
	return true;
}

// ������Ʒ
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

// ����ָ��λ�õ���Ʒ��Ϣ
ProductNode Store::findObjectAtPosition(int index) {
	if (index < 0 || index >= _product.size()) {
		return ProductNode();
	}

	return _product[index];
}

// �ص�����
void Store::setSellProductCallback(std::function<void(bool)> callback) {
	_sellProductCallback = callback;
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

// �ж���Ʒ�Ƿ������ӵ��ջ���
bool Store::canHarvestFromAnySeed(const GameBaseObject& baseObject,  GameSeedObject& seedObject) {
	for (const auto seed : GAME_SEED_OBJECTS_ATTRS) { // ʹ�ó������ñ���
		if (baseObject._index == seed._harvestIndex) {
			seedObject = seed;
			return true;
		}
	}
	return false; // ���û���ҵ�
}
