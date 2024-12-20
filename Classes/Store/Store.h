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

class Store {
public:
	// 构造函数
	Store();

	// 新的一天刷新商店货物
	void refreshStock();

	// 根据季节更新价格
	void updatePrices();

private:
	int productKindCount;						// 商店每天售卖的货物种类
	std::vector<SeedProductNode>_seedProduct;		// 种子商品种类,数量
	std::vector<BaseProductNode> _baseProduct;		// 基础商品种类,数量
};

#endif // !__STORE_H__