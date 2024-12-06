/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Object.h
 * File Function: Object的定义
 * Author:        尹诚成
 * Update Date:   2023/12/06
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <vector>
#include "../proj.win32/Constant.h"


 //游戏物品对应技能类型定义
typedef enum {
    Farm,				// 耕种
    Collect,			// 采集
    Mine,				// 采矿
    Fish				// 钓鱼
}GameObjectSkillType;

// 游戏工具类型定义
typedef enum {
    Hoe,				// 锄头
    Ax,					// 斧头
    Pickaxe,			// 镐子
    FishingRod,			// 鱼竿
    Kettle				// 水壶
}GameTools;

// 季节定义
typedef enum {
    Spring,				// 春天
    Summer,				// 夏天
    Fall,				// 秋天
    Winter,				// 冬天
    All					// 通用
}Season;

// 游戏物品类型定义
typedef enum {
    None,				// 空物品
    Tool,				// 工具
    Seed,				// 种子
    Base,				// 基础物品
    Compose				// 合成物品
}GameObjectMapType;

// 游戏物品共有属性定义
class GameObject {
public:
    std::string _fileName;       // 物品图片资源文件路径
    std::string _name;           // 物品名称
    GameObjectSkillType _type;   // 物品类型

    virtual ~GameObject() {}     // 虚拟析构函数
};

// 游戏工具物品属性定义
class GameToolObject : public GameObject {
public:
    int _level;                 // 工具等级
    int _actionCost;            // 执行一次操作需要的次数
    int _durability;            // 工具耐久度

    // 构造函数
    GameToolObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, int actionCost, int durability);
};

// 游戏种子物品属性定义
class GameSeedObject : public GameObject {
public:
    int _level;                             // 解锁种子所需等级
    Season _season;                         // 种子生长季节
    std::vector<int> _growthStages;         // 种子每个阶段所需的生长天数
    int _totalGrowTime;                     // 种子生长总天数
    int _harvestIndex;                      // 种子收获所得的物品索引
    int _buyPrice;                          // 种子购买价格
    int _salePrice;                         // 种子出售价格

    // 构造函数
    GameSeedObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, Season season, std::vector<int> growthStages, int totalGrowTime, int harvestIndex, int buyPrice, int salePrice);
};

// 游戏基础物品属性定义
class GameBaseObject : public GameObject {
public:
    int _maxStorage;          // 物品最大存储量
    int _level;               // 解锁物品所需等级
    int _quality;             // 物品品质等级
    bool _sale;               // 是否能出售
    int _salePrice;           // 出售价格
    bool _eat;                // 是否可以食用
    int _eatEnergy;           // 食用恢复的能量值
    bool _place;              // 能否放置

    // 构造函数
    GameBaseObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place);
};

// 游戏合成物品属性定义
class GameComposeObject : public GameObject {
public:
    GameBaseObject _baseObject;					    // 基础物品属性
    std::map<std::string, int> _ingredients;		// 合成物品的原料

    GameComposeObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place, const std::map<std::string, int>& ingredients) :
        _baseObject(fileName, name, type, maxStorage, level, quality, sale, salePrice, eat, eatEnergy, place),
        _ingredients(ingredients) {
    }
};

// 游戏物品属性定义
struct GameCommonObject {
    GameObjectMapType type;                             // 物品类型
    std::shared_ptr<GameObject> object;

    GameCommonObject() : type(None), object(nullptr) {} // 默认构造函数
    GameCommonObject(GameObjectMapType type, std::shared_ptr<GameObject> object) :
        type(type),
        object(object) {
    }
};


#endif // _CONSTANT_OBJECT_H_