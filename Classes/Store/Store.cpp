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
	_seedProduct.clear();
	_baseProduct.clear();
}

// 新的一天刷新商店货物
void Store::refreshStock() {
	srand(static_cast<unsigned int>(time(0)));

	int seedProductKind = rand() % PRODUCE_KIND_NUM_EACH_DAY;
	int baseProductKind = PRODUCE_KIND_NUM_EACH_DAY - seedProductKind;
	
	for (int i = 0; i < seedProductKind; i++) {
		int seedIndex = rand() % GAME_BASE_OBJECTS_ATTRS.size();
		int productCount = rand() % MAX_PRODUCT_COUNT_EACH_DAY + 1;
		_seedProduct.push_back({ GAME_SEED_OBJECTS_ATTRS[seedIndex], productCount, productCount * GAME_SEED_OBJECTS_ATTRS[seedIndex]._buyPrice });
	}

	for (int i = seedProductKind; i < productKindCount; i++) {
		int baseIndex = INVAVID_NUM;
		do {
			int baseIndex = rand() % GAME_BASE_OBJECTS_ATTRS.size();
		} while (!GAME_BASE_OBJECTS_ATTRS[baseIndex]._buy);
		int productCount = rand() % MAX_PRODUCT_COUNT_EACH_DAY + 1;
		_baseProduct.push_back({ GAME_BASE_OBJECTS_ATTRS[baseIndex], productCount, productCount * GAME_BASE_OBJECTS_ATTRS[baseIndex]._buyPrice });
	}
}
