/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.h
 * File Function: 商店Store类的定义
 * Author:        尹诚成
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef __STORE_H__
#define __STORE_H__

#include <string>
#include <vector>
#include <map>
#include "Character/Character.h"
#include "Control/TimeManager.h"

class Store {
public:
	// 构造函数
	Store();

	// 新的一天刷新商店货物
	void refreshStock();

	// 根据季节更新价格
	void updatePrices();

	// 购买商品
	bool buyProduct(int index);

	// 出售商品
	bool sellProduct(const GameSeedObject targetObject,int objectCount);

	// 出售商品
	bool sellProduct(const GameBaseObject targetObject, int objectCount);

private:
	Character *_character;					// 玩家角色
	TimeManager* _timeManager;				// 时间管理器
	int productKindCount;					// 商店每天售卖的货物种类
	std::vector<ProductNode>_product;		// 商品种类,数量

	// 判断物品是否是种子的收获物
	bool canHarvestFromAnySeed(const GameBaseObject& baseObject, GameSeedObject* seedObject);
};

#endif // !__STORE_H__