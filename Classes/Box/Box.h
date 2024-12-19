/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.h
 * File Function: 箱子Box类的定义
 * Author:        尹诚成
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#pragma once
# ifndef BOX_H
# define BOX_H

# include <vector>
# include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "../proj.win32/Constant.h"

class Box : public cocos2d::Node {
public:
	// 获取单例
	static Box& getInstance();
	
	// 获取箱子
	BoxNode& getBoxList();

	// 获取箱子数量
	int getBoxCount();

	// 添加单个箱子
	bool addBox(const BoxNode& boxNode);

	// 移除单个箱子
	void removeBox();

	// 利用坐标位置匹配箱子
	int matchBoxPosition(cocos2d::Vec2 worldPosition);
	
	// 储存物品
	bool storeObject(int objectListIndex, int boxIndex);

	// 交换物品
	void swapObject(int startIndex, int targetIndex);

	// 取出物品
	void getSelectedObject(int boxIndex,int objectListIndex);

	// 查找指定位置是否有物品
	ObjectListNode findObjectAtPosition(int objectIndex);

	// 保存数据
	bool saveData(const std::string& fileName);

	// 加载数据
	bool loadData(const std::string& fileName);
private:
	Character* _character;					// 角色指针
	std::vector<BoxNode> _boxObjectList;	// 箱子里的物品列表
	int _maxObjectKindCount;				// 单个箱子最大容量
	
	// 构造函数
	Box();
	Box(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition);

	// 查找箱子中是否有指定物品
	int findObject( GameCommonObject targetObject);

	// 检查箱子是否已满
	bool checkObjectListFull();
};

#endif // !BOX_H