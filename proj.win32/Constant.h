#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "../Classes/Object/Object.h"

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
constexpr float MOVE_SPEED = 3.5f;											// 移动速度
constexpr float MOVE_RATE = FRAME_RATE;										// 移动帧率
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效按键
constexpr float ACTION_RATE = 5.0f;											// 动作间隔帧率
constexpr int INVAVID_NUM = -1;												// 无效数字


// 角色属性
constexpr int CHARACTER_WIDTH = 32;											// 角色宽度
constexpr int CHARACTER_HEIGHT = 32;										// 角色高度
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// 移动速度

// 地图设置
constexpr float LERP_SPEED = 0.1f;											// 视角过渡的平滑度
constexpr float MAP_SCALE = 1.6f;											// 地图缩放大小

// 物品设置
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// 背包容量(等级1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// 背包容量(等级2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// 背包容量(等级3)
constexpr int MAX_STORAGE_NUM = 999;										// 单个物品的最大存储数量

constexpr int MAX_GROWTH_STAGE = 7;											// 种子生长阶段最大数量



//// 游戏工具物品属性定义
//typedef struct {
//	std::string fileName;    // 工具图片资源文件路径
//	std::string name;        // 工具名称
//	GameObjectSkillType type;	 // 工具类型
//	int level;               // 工具等级
//	int actionCost;			 // 执行一次操作需要的次数
//	int durability;          // 工具耐久度(针对水壶)
//}GameToolObject;
//// 游戏种子物品属性定义
//// TODO:添加额外收获功能
//typedef struct {
//	std::string fileName;						// 种子图片资源文件路径
//	std::string name;							// 种子名称
//	GameObjectSkillType type;						// 种子类型
//	int level;									// 解锁种子所需等级
//	Season season;								// 种子生长季节
//	int growthDays[MAX_GROWTH_STAGE];			// 种子每个阶段所需的生长天数
//	int totalGrowTime;							// 种子生长总天数
//	int harvestIndex;							// 种子收获所得的物品索引
//	int buyPrice;								// 种子购买价格
//	int salePrice;								// 种子出售价格
//}GameSeedObeject;
//
//// 游戏基础物品属性定义
//typedef struct {
//	std::string fileName;    // 物品图片资源文件路径
//	std::string name;        // 物品名称
//	GameObjectSkillType type;	 // 物品类型
//	int maxStorage;          // 物品最大存储量
//	int level;               // 解锁物品所需等级
//	int quality;             // 物品品质等级
//	bool sale;               // 是否能出售
//	int salePrice;           // 出售价格
//	bool eat;                // 是否可以食用
//	int eatEnegry;           // 食用恢复的能量值
//	bool place;				 // 能否放置
//}GameBaseObject;
//
//// 游戏合成物品属性定义
//typedef struct {
//	GameBaseObject baseObject;					// 基础物品属性
//	std::map<std::string, int> ingredients;		// 合成物品的原料
//}GameComposeObject;
//
//// 游戏通用物品属性定义
//typedef struct {
//	GameObjectMapType type;							// 物品类型
//	void* object;									// 物品对象
//}GameCommonObject;
//
//
//// 游戏工具物品属性参数定义
//const std::map<int, GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
//	{1,{"","初级锄头",Farm,1,1,INT_MAX}},				// 锄头(一级)
//	{2,{"","中级锄头",Farm,2,1,INT_MAX}},				// 锄头(二级)
//	{3,{"","高级锄头",Farm,3,1,INT_MAX}},				// 锄头(三级)
//	{4,{"","初级斧头",Collect,1,8,INT_MAX}},				// 斧头(一级)
//	{5,{"","中级斧头",Collect,2,7,INT_MAX}},				// 斧头(二级)
//	{6,{"","高级斧头",Collect,3,6,INT_MAX}},				// 斧头(三级)
//	{7,{"","初级镐子",Mine,1,10,INT_MAX}},				// 镐子(一级)
//	{8,{"","中级镐子",Mine,2,9,INT_MAX}},				// 镐子(二级)
//	{9,{"","高级镐子",Mine,3,8,INT_MAX}},				// 镐子(三级)
//	{10,{"","初级鱼竿",Fish,1,1,INT_MAX}},				// 鱼竿(一级)
//	{11,{"","中级鱼竿",Fish,2,1,INT_MAX}},				// 鱼竿(二级)
//	{12,{"","高级鱼竿",Fish,3,1,INT_MAX}},				// 鱼竿(三级)
//	{13,{"","初级水壶",Farm,1,1,40}},					// 水壶(一级)
//	{14,{"","中级水壶",Farm,2,1,55}},					// 水壶(二级)
//	{15,{"","高级水壶",Farm,3,1,70}},					// 水壶(三级)
//};
//
//// 游戏种子物品属性参数定义
//const std::map<int, GameSeedObeject> GAME_SEED_OBJECTS_ATTRS = {
//
//};
//
//// 游戏基础物品属性参数定义
//const std::map<int, GameBaseObject> GAME_BASE_OBJECTS_ATTRS = {
//
//};
//
//// 游戏种子成熟后对应作物匹配
//const std::map<GameSeedObeject, GameBaseObject> SEED_TO_CROP_TYPE = {
//
//};
//
//// 游戏合成物品属性参数定义
//const std::map<int, GameComposeObject> GAME_COMPOSE_OBJECTS_ATTRS = {
//
//};


const int SECONDS_IN_A_DAY = 86400;                                         // һ�������
const float TIME_SCALE = 3600.0f;                                             // ��Ϸʱ�����ű�������ʵ1��=��Ϸ1����
const int HOURS_IN_A_DAY = 24;                                              // һ��24Сʱ
const int SECONDS_IN_A_HOUR = 3600;                                           // ÿСʱ60����
const int SEASONS_CHANGE_PERIOD = 30;                                       // ÿ30��һ�����ڱ仯
const int SECONDS_IN_A_MIN =60;
#endif // !_CONSTANT_H_