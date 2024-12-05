/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     CharacterObjectList.h
 * File Function: CharacterObjectList类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/05
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_OBJECT_LIST_H__
#define __CHARACTER_OBJECT_LIST_H__

#include <vector>
#include "cocos2d.h"
#include "../proj.win32/Constant.h"

// 物品栏物品状态定义
typedef enum {
	Unselected,						// 未被选中
	Selected,						// 被选中
}ObjectStatus;

// 物品栏单个物品信息定义
typedef struct {
<<<<<<< Updated upstream
	int id;							// 物品栏索引
	GameCommonObject object;		// 物品对象
=======
	GameCommonObject objectNode;	// 物品对象
>>>>>>> Stashed changes
	int count;						// 物品数量
	ObjectStatus status;			// 物品状态
}ObjectListNode;


<<<<<<< Updated upstream

class CharacterObjectList : public cocos2d::Node {
=======
class CharacterObjectList : virtual public cocos2d::Node {
>>>>>>> Stashed changes
public:
	// 构造函数
	CharacterObjectList();

<<<<<<< Updated upstream
	// 析构函数
	~CharacterObjectList();

	// 按下键盘时的处理
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 按下鼠标时的处理
	void onMouseDown(cocos2d::Event* event);

	// 捡起物品
	bool pickUpObject(GameCommonObject object);	
=======
	// 按下键盘时的处理
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 捡起物品
	bool pickUpObject(GameCommonObject targetObject, int objectCount);
>>>>>>> Stashed changes

	// 移动物品
	void moveObject(ObjectListNode object);

<<<<<<< Updated upstream
private:
	std::vector<ObjectListNode*> _objectList;   // 物品列表
	ObjectListNode _currentObject;				// 当前物品
	int _maxObjectCount;						// 最大物品数量
	int _currentObjectCount;					// 当前物品数量
	int _currentObjectIndex;					// 当前物品索引
=======
	// 获取当前物品栏索引的物品
	ObjectListNode getCurrentObject();

	// 检查物品栏是否已满
	bool checkObjectListFull();
protected:
	bool openObjectList;						// 是否打开物品栏

private:
	std::vector<ObjectListNode> _objectList;	// 物品列表
	int _maxObjectCount;						// 最大物品数量
	int _currentObjectKindCount;				// 当前物品种类数量
	int _currentObjectIndex;					// 当前物品栏索引
	// 初始化物品栏函数
	void initObjectList();
>>>>>>> Stashed changes

	// 设置当前物品
	void setCurrentObject(int index);			

	// 丢弃当前物品
	ObjectListNode discardCurrentObject();
<<<<<<< Updated upstream
=======

	// 查找指定物品
	int findObject(GameCommonObject targetObject);
>>>>>>> Stashed changes
};

#endif // !__CHARACTER_OBJECT_LIST_H__