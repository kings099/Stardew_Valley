/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Object.h
 * File Function: Object的定义
 * Author:        尹诚成
 * Update Date:   2023/12/06
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OBJECT_CONSTANT_H_
#define _OBJECT_CONSTANT_H_

#include <string>
#include <vector>
#include <limits> 
#include "proj.win32/Constant.h"

 //游戏物品对应技能类型定义
enum GameObjectSkillType {
    Farm,				// 耕种
    Collect,			// 采集
    Mine,				// 采矿
    Fish				// 钓鱼
};

// 游戏工具类型定义
enum GameTools {
    Hoe,				// 锄头
    Ax,					// 斧头
    Pickaxe,			// 镐子
    FishingRod,			// 鱼竿
    Kettle				// 水壶
};

// 季节定义
enum Season {
    Spring,				// 春天
    Summer,				// 夏天
    Fall,				// 秋天
    Winter,				// 冬天
    All					// 通用
};

// 游戏物品类型定义
enum GameObjectMapType {
    None,				// 空物品
    Tool,				// 工具
    Seed,				// 种子
    Base,				// 基础物品
};

// 角色动作定义
enum GameCharacterAction {
    NoneAction,			// 空动作
    Plowing,			// 耕地
    Watering,			// 浇水
    Cutting,			// 砍树
    Mining,				// 采矿
    Fishing,		    // 钓鱼
    Placement,			// 放置
    Harvesting,			// 收获
    Buying,				// 购买
    Selling,			// 出售
};



// 游戏物品共有属性定义
class GameObject {
public:
    std::string _fileName;       // 物品图片资源文件路径
    std::string _name;           // 物品名称
    GameObjectSkillType _type;   // 物品类型

    GameObject() = default;
    GameObject(const std::string& fileName, const std::string& name, GameObjectSkillType type) :
        _fileName(fileName),
        _name(name),
        _type(type) {
    }
    virtual ~GameObject() {}     // 虚拟析构函数
};

// 游戏工具物品属性定义
class GameToolObject : public GameObject {
public:
    int _level;                 // 工具等级
    int _actionCost;            // 执行一次操作需要的次数
    int _durability;            // 工具耐久度
    GameCharacterAction _action; // 工具当前执行的动作

    // 构造函数
    GameToolObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, int actionCost, int durability, GameCharacterAction action):
        GameObject(fileName, name, type),
        _level(level),
        _actionCost(actionCost),
        _durability(durability),
        _action(action)
    {}
};

// 游戏种子物品属性定义
class GameSeedObject : public GameObject {
public:
    int _level;                                             // 解锁种子所需等级
    Season _season;                                         // 种子生长季节
    std::vector<int> _growthStages;                         // 种子每个阶段所需的生长天数
    std::vector<std::string> _growthStagesFileNames;        // 种子每个生长阶段的图片资源文件路径
    int _totalGrowTime;                                     // 种子生长总天数
    int _harvestIndex;                                      // 种子收获所得的物品索引
    int _buyPrice;                                          // 种子购买价格
    int _salePrice;                                         // 种子出售价格

    // 构造函数
    GameSeedObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, Season season, std::vector<int> growthStages, int totalGrowTime, int harvestIndex, int buyPrice, int salePrice):
        GameObject(fileName, name, type),
        _level(level),
        _season(season),
        _growthStages(growthStages),
        _totalGrowTime(totalGrowTime),
        _harvestIndex(harvestIndex),
        _buyPrice(buyPrice),
        _salePrice(salePrice) 
    {}
};

// 游戏基础物品属性定义
class GameBaseObject : public GameObject {
public:
    int _maxStorage;                            // 物品最大存储量
    int _level;                                 // 解锁物品所需等级
    int _quality;                               // 物品品质等级
    bool _sale;                                 // 是否能出售
    int _salePrice;                             // 出售价格
    bool _eat;                                  // 是否可以食用
    int _eatEnergy;                             // 食用恢复的能量值
    bool _place;                                // 能否放置
    bool _synthesis;                            // 是否可以合成
    std::map<std::string, int> _ingredients;	// 合成物品的原料
    // 构造函数
    GameBaseObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place, bool synthesis, std::map<std::string, int> ingredients):
        GameObject(fileName, name, type),
        _maxStorage(maxStorage),
        _level(level),
        _quality(quality),
        _sale(sale),
        _salePrice(salePrice),
        _eat(eat),
        _eatEnergy(eatEnergy),
        _place(place) ,
        _synthesis(synthesis),
        _ingredients(ingredients)
    {}
};

// 游戏物品属性定义
struct GameCommonObject {
    GameObjectMapType type;                             // 物品类型
    std::shared_ptr<GameObject> object;

    GameCommonObject() : type(None), object(nullptr) {} // 默认构造函数
    GameCommonObject(GameObjectMapType type, std::shared_ptr<GameObject> object) :
        type(type),
        object(object)
    {}
};
// 物品栏中物品状态定义
enum ObjectListNodeStatus {
    Unselected,		// 未选中
    Selected		// 选中
};

// 角色物品栏单个物品属性定义
struct ObjectListNode {
    int index;                      // 物品索引
    GameCommonObject objectNode;	// 物品信息
    int count;						// 物品数量
    ObjectListNodeStatus status;	// 物品状态(选中/未选中)
};


// 游戏物品属性参数定义
const std::vector<GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
    GameToolObject("../Resources/Objects/Tools/BeginnerHoe.png", "初级锄头", Farm, 1, 1, INT_MAX, Plowing),
    GameToolObject("../Resources/Objects/Tools/IntermediateHoe.png", "中级锄头", Farm, 2, 1, INT_MAX, Plowing),
    GameToolObject("../Resources/Objects/Tools/AdvancedHoe.png", "高级锄头", Farm, 3, 1, INT_MAX, Plowing),
    GameToolObject("../Resources/Objects/Tools/BeginnerAxe.png", "初级斧头", Collect, 1, 5, INT_MAX, Cutting),
    GameToolObject("../Resources/Objects/Tools/IntermediateAxe.png", "中级斧头", Collect, 2, 4, INT_MAX, Cutting),
    GameToolObject("../Resources/Objects/Tools/AdvancedAxe.png", "高级斧头", Collect, 3, 3, INT_MAX, Cutting),
    GameToolObject("../Resources/Objects/Tools/BeginnerPickaxe.png", "初级镐子", Mine, 1, 5, INT_MAX, Mining),
    GameToolObject("../Resources/Objects/Tools/IntermediatePickaxe.png", "中级镐子", Mine, 2, 4, INT_MAX, Mining),
    GameToolObject("../Resources/Objects/Tools/AdvancedPickaxe.png", "高级镐子", Mine, 3, 3, INT_MAX, Mining),
    GameToolObject("../Resources/Objects/Tools/BeginnerFishingRods.png", "初级鱼竿", Fish, 1, 1, INT_MAX, Fishing),
    GameToolObject("../Resources/Objects/Tools/IntermediateFishingRods.png", "中级鱼竿", Fish, 2, 1, INT_MAX, Fishing),
    GameToolObject("../Resources/Objects/Tools/AdvancedFishingRods.png", "高级鱼竿", Fish, 3, 1, INT_MAX, Fishing),
    GameToolObject("../Resources/Objects/Tools/", "初级水壶", Farm, 1, 1, 40, Watering),
    GameToolObject("../Resources/Objects/Tools/", "中级水壶", Farm, 2, 1, 55, Watering),
    GameToolObject("../Resources/Objects/Tools/", "高级水壶", Farm, 3, 1, 70, Watering)
};

//enum GameMapNodeType {
//    Grass,       // 草地
//    Tree,        // 树木
//    Stone,       // 石头
//    Water,       // 水
//    Soil,        // 泥土
//    Sand         // 沙子
//    //.....
//};
//
//struct GameMapNode {
//    GameMapNodeType type;       // 节点类型
//    int x, y;                   // 坐标
//    int layer;                  // 层数
//    bool isObstacle;            // 是否障碍物
//    std::vector<GameCommonObject> dropObjects; // 掉落物品
//    std::vector<int> dropObjectsNum;           // 掉落物品数量
//};

#endif // _CONSTANT_OBJECT_H_