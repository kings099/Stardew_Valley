#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include "cocos2d.h"
#include <string>

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1024;                               // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 768;                               // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 480;                                 // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 320;                                // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1024;                               // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 768;                               // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 2048;                                // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1536;                               // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                         // 应用程序帧率
const std::string APPLICATION_TITLE = u8"星露谷 Stardew Valley";				// 应用程序标题

//测试用常变量
<<<<<<< Updated upstream
constexpr float MOVE_SPEED = 3.5f;											// 移动速度d
constexpr float MOVE_RATE = FRAME_RATE;										// 移动帧率
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效按键
constexpr float ACTION_RATE = 5.0f;											// 动作间隔帧率

<<<<<<< Updated upstream
constexpr int STAY = 0;														// 静止
constexpr int UP = 1;														// 方向向上
constexpr int DOWN = 2;														// 方向向下
constexpr int LEFT = 3;														// 方向向左
constexpr int RIGHT = 4;													// 方向向右
=======
=======

constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效按键
constexpr float ACTION_RATE = 5.0f;											// 动作间隔帧率

// 角色属性
constexpr int CHARACTER_WIDTH = 32;											// 角色宽度
constexpr int CHARACTER_HEIGHT = 32;										// 角色高度
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// 移动速度

// 地图设置
constexpr float LERP_SPEED = 0.1f;											// 视角过渡的平滑度
>>>>>>> Stashed changes
constexpr float MAP_SCALE = 1.6f;											// 地图缩放大小
>>>>>>> Stashed changes

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// 背包容量等级1
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// 背包容量等级2
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// 背包容量等级3

<<<<<<< Updated upstream
=======
constexpr int MAX_STORAGE_NUM = 999;										// 单个物品的最大存储数量

>>>>>>> Stashed changes
//游戏物品类型定义
typedef enum {
	Farm,				// 耕种
	Collect,			// 采集
	Mine,				// 采矿
	Fish				// 钓鱼
}GameObjectType;

// 游戏工具类型定义
typedef enum {
	Hoe,				// 锄头
	Ax,					// 斧头
	Pickaxe,			// 镐子
	FishingRod,			// 鱼竿
	Kettle				// 水壶
}GameTools;

// 游戏工具物品属性定义
typedef struct {
	std::string fileName;    // 文件路径
	std::string name;        // 工具名称
	GameObjectType type;	 // 工具类型
	int level;               // 工具等级
	int durability;          // 工具耐久度(针对水壶)
}GameToolObject;

// 游戏基础物品属性定义
typedef struct {
	std::string fileName;    // 文件路径
	std::string name;        // 物品名称
	GameObjectType type;	 // 物品类型
<<<<<<< Updated upstream
=======
	int maxStorage;          // 物品最大存储量
>>>>>>> Stashed changes
	int level;               // 物品等级
	bool sale;               // 是否能出售
	int salePrice;           // 出售价格
	bool eat;                // 是否可以食用
	int eatEnegry;           // 食用恢复的能量值
}GameBaseObject;

// 游戏合成物品属性定义
typedef struct {
	GameBaseObject baseObject;					// 基础物品属性
	std::map<std::string,int> ingredients;		// 合成物品的原料
}GameComposeObject;

// 游戏物品类型定义
typedef enum {
<<<<<<< Updated upstream
	None,				// 无效物品
=======
	None,				// 空物品
>>>>>>> Stashed changes
	Tool,				// 工具
	Base,				// 基础物品
	Compose				// 合成物品
}GameObjectMapType;

// 游戏通用物品属性定义
typedef struct {
	GameObjectMapType type;							// 物品类型
	void* object;									// 物品对象
}GameCommonObject;

// 游戏工具物品属性参数定义
const std::map<int, GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
	{1,{"","锄头",Farm,1,INT_MAX}},					// 锄头
	{2,{"","斧头",Collect,1,INT_MAX}},				// 斧头
	{3,{"","镐子",Mine,1,INT_MAX}},					// 镐子
	{4,{"","鱼竿",Fish,1,INT_MAX}},					// 鱼竿
	{5,{"","水壶",Farm,1,40}},						// 水壶(一级)
	{6,{"","水壶",Farm,2,55}},						// 水壶(二级)
	{7,{"","水壶",Farm,3,70}},						// 水壶(三级)
};

// 游戏基础物品属性参数定义
const std::map<int, GameBaseObject> GAME_BASE_OBJECTS_ATTRS = {

};

// 游戏合成物品属性参数定义
const std::map<int, GameComposeObject> GAME_COMPOSE_OBJECTS_ATTRS = {

};
#endif // !_CONSTANT_H_