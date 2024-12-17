/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.h
 * File Function: 箱子Box类的定义
 * Author:        尹诚成
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#pragma once
# ifndef BOX_H
# define BOX_H

# include <vector>
# include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "../proj.win32/Constant.h"

struct BoxNode {
	std::vector<ObjectListNode> _boxObjectList;	// 箱子里的物品列表
	int _maxObjectKindCount;						// 箱子最大容量
	cocos2d::Vec2 _worldPosition;					// 箱子坐标
	cocos2d::Vec2 _tilePosition;					// 箱子瓦片坐标、

	// 构造函数
	BoxNode() :
		_maxObjectKindCount(OBJECT_LIST_COLS)
	{
		_boxObjectList.resize(_maxObjectKindCount);
	}

	BoxNode(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition) :
		_maxObjectKindCount(OBJECT_LIST_COLS),
		_worldPosition(worldPosition),
		_tilePosition(tilePosition)
	{
		_boxObjectList.resize(_maxObjectKindCount);
	}
};

class Box : public cocos2d::Node {
public:
	// 获取单例
	static Box& getInstace();
	
	// 获取箱子向量列表
	std::vector<BoxNode>& getBoxList();

	// 添加单个箱子
	void addBox(const BoxNode& boxNode);

	// 利用坐标位置匹配箱子
	int matchBoxPosition(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition);
	
	// 储存物品
	bool storeObject(int boxListIndex,GameToolObject targetObject, int objectCount, int targetIndex);

	// 储存物品
	bool storeObject(int boxListIndex, GameSeedObject targetObject, int objectCount, int targetIndex);

	// 储存物品
	bool storeObject(int boxListIndex, GameBaseObject targetObject, int objectCount, int targetIndex);

	// 交换物品
	void swapObject(int boxListIndex, int startIndex, int targetIndex);

	// 取出当前选中的物品
	void getSelectedObject(int boxListIndex,int boxIndex,int objectListIndex);

	// 查找指定位置是否有物品
	ObjectListNode findObjectAtPosition(int boxListIndex,int objectIndex);

	
private:
	Character* _character;					// 角色指针
	std::vector<BoxNode> _boxObjectList;	// 箱子里的物品列表
	int _maxObjectKindCount;				// 单个箱子最大容量
	
	// 构造函数
	Box();
	Box(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition);

	// 查找箱子中是否有指定物品
	int findObject(int boxListIndex, GameCommonObject targetObject);

	// 储存物品
	bool storeObject(int boxListIndex, GameCommonObject targetObject, int objectCount,int targetIndex);

	// 检查箱子是否已满
	bool checkObjectListFull(int boxListIndex);
};

#endif // !BOX_H