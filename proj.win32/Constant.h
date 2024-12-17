#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_


#include <string>
#include <memory>
#include <fstream>
#include <map>
#include "cocos2d.h"


// 设备分辨率
constexpr int DESIGN_RESOLUTION_WIDTH = 1920;                               // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 1080;                              // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // 小屏分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // 小屏分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // 中屏分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // 中屏分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // 大屏分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // 大屏分辨率高度
constexpr float FRAME_RATE = 60.0f;                                         // 游戏帧率
const std::string APPLICATION_TITLE = u8"星露谷物语 Stardew Valley";         // 游戏应用标题

// 移动相关设置
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效键值
constexpr float ACTION_RATE = 5.0f;											// 动作帧率
constexpr int INVAVID_NUM = -1;												// 无效编号

// 角色相关设置
constexpr int CHARACTER_WIDTH = 32;											// 角色宽度
constexpr int CHARACTER_HEIGHT = 32;										// 角色高度
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// 角色移动速度
constexpr float CHARACTER_HORIZONTAL_ANCHORPOINT = 0.5f;					// 角色水平锚点
constexpr float CHARACTER_VERTICAL_ANCHORPOINT = 0.25f;						// 角色垂直锚点
constexpr int LEVEL0_TO_LEVEL1_EXPRIENCE = 10;                              // 从零级升到一级需要的经验值
constexpr int LEVEL1_TO_LEVEL2_EXPRIENCE = 20;                              // 从一级升到二级需要的经验值
constexpr int LEVEL2_TO_LEVEL3_EXPRIENCE = 50;                              // 从二级升到三级需要的经验值
constexpr int LEVEL3_TO_LEVEL4_EXPRIENCE = 100;                             // 从三级升到四级需要的经验值
constexpr int LEVEL4_TO_LEVEL5_EXPRIENCE = 200;                             // 从四级升到五级需要的经验值
constexpr int SKILL_KIND_NUM = 4;                                           // 技能种类数量
constexpr int SKILL_LEVEL_NUM = 5;                                          // 技能最大等级

// 场景过渡相关
constexpr float LERP_SPEED = 0.1f;											// 插值平滑速度
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// 场景切换时间
constexpr float FARM_MAP_SCALE = 2.0f;										// 农场地图缩放比例
constexpr float INDOOR_MAP_SCALE = 5.0f;									// 室内地图缩放比例

// 地图图块相关
constexpr int DRY_FARM_TILE_GID = 2040;                                     // 干燥耕地效果动画图块GID
constexpr int EMPTY_GID = 0;                                                // 空白GID
constexpr int OAK_GID = 10;                                                 // 桦树GID
constexpr int MAMPLE_GID = 11;                                              // MAMPLE GID
constexpr int PINE_GID = 12;                                                // PINE GID
constexpr int OAK_INVISIBLE_GID = 1;                                        // OAK树根图块不可见GID
constexpr int MAMPLE_INVISIBLE_GID = 2;                                     // MAMPLE树根图块不可见GID
constexpr int PINE_INVISIBLE_GID = 3;                                       // PINE树根图块不可见GID
constexpr int OAK_ROOT_GID = 191;                                           // OAK树根GID
constexpr int MAMPLE_ROOT_GID = 194;                                        // MAMPLE树根GID
constexpr int PINE_ROOT_GID = 201;                                          // PINE树根GID

// 物品设置
constexpr int OBJECT_LIST_ROWS = 3;											// 物品列表行数
constexpr int OBJECT_LIST_COLS = 12;										// 物品列表列数

// UI 相关设置
constexpr int UI_SCALE = 210.0f;                                            // UI界面缩放
constexpr int FONT_SIZE = 20;                                               // 字体大小
constexpr int MAP_LAYER_GRADE = 0;                                          // 地图层级
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // 角色层级
constexpr int UI_LAYER_GRADE = 2;                                           // UI层级
constexpr int OBJECT_LAYER_GRADE = 3;                                       // 物品层级
constexpr float ENLARGEMENT_RATIO = 1.2f;									// 按钮动画缩放比例
constexpr float ENLARGEMENT_TIME = 0.15f;									// 按钮动画缩放时间
constexpr int CLOSE_OBJECT_LIST_START_X = 729;								// 物品栏(关闭状态)起始位置的X坐标
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// 物品栏(关闭状态)起始位置的Y坐标
constexpr int OPEN_OBJECT_LIST_START_X = 729;								// 物品栏(开启状态)起始位置的X坐标
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// 物品栏(开启状态)起始位置的Y坐标
constexpr int SKILL_LEVEL_START_X = 417;                                    // 技能栏起始位置的X坐标
constexpr int SKILL_LEVEL_START_Y = 456;                                    // 技能栏起始位置的Y坐标
constexpr int OBJECT_BOX_START_X = 729;                                     // 箱子起始位置的X坐标
constexpr int OBJECT_BOX_START_Y = 648;                                     // 箱子起始位置的Y坐标
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// 物品栏物品格子水平间距
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// 物品栏物品格子垂直间距
constexpr float OBJECT_NODE_SCALE = 2.0f;									// 物品缩放比例
constexpr float BUTTON_SCALE = 2.0f;										// 按钮缩放比例
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// 物品栏删除按钮左边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// 物品栏删除按钮右边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// 物品栏删除按钮上边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// 物品栏删除按钮下边界

// 游戏时间设置
constexpr int SECONDS_IN_A_DAY = 86400;                                     // 一天的秒数
constexpr float TIME_SCALE = 3600.0f;                                       // 游戏时间与实际时间的比例，1秒 = 游戏1小时
constexpr int HOURS_IN_A_DAY = 24;                                          // 一天24小时
constexpr int SECONDS_IN_A_HOUR = 3600;                                     // 一小时60分钟
constexpr int SEASONS_CHANGE_PERIOD = 30;                                   // 每30天切换一个季节
constexpr int SECONDS_IN_A_MIN = 60;                                        // 每分钟60秒
constexpr int DAYS_IN_A_SEASON = 7;                                         // 每季7天
constexpr int DAYS_IN_A_YEAR = 28;                                          // 一年28天

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

// 游戏季节定义
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

// 角色朝向
enum Direction {
    Up,
    Down,
    Left,
    Right,
};

// 鼠标按键
enum MouseButton {
    LeftButton,			// 左键
    RightButton,		// 右键
};

// 瓦片信息
enum TileType {
    Grass,      // 草
    Tree,       // 树木
    Stone,      // 矿石
    Water,      // 水
    Soil,       // 可耕种土地
    Soiled,     // 已耕种土地
    Crop,       // 作物
    Door,       // 门
    Other
};

// 单个瓦片坐标信息
struct TileInfo {
    TileType type;
    cocos2d::Vec2 tilePos;  // 瓦片坐标
    cocos2d::Vec2 WorldPos; // 世界坐标
    bool isObstacle;        // 是否为障碍物
};

// 角色动作定义
enum GameCharacterAction {
    NoneAction,			// 空动作
    Plowing,			// 耕地
    Watering,			// 浇水
    Fertilize,          // 施肥
    GetWater,			// 取水
    Weeding,            // 除草
    Cutting,			// 砍树
    Mining,				// 采矿
    Fishing,		    // 钓鱼
    Buying,				// 购买
    Harvesting,			// 收获
    Placement,			// 放置
    Transition,			// 转换场景
    OpenBox,			// 打开箱子

};

// 角色动作和地图类型对应关系
const std::map< GameCharacterAction, TileType> ACTION_TO_TILEMAP = {
    { NoneAction, Other },
    { Plowing, Soil },
    { Watering, Soiled },
    { Fertilize, Soiled },
    { GetWater, Water },
    { Weeding, Grass },
    { Cutting, Tree },
    { Mining, Stone },
    { Fishing, Water },
    { Harvesting, Crop },
    { Placement, Other },
    {Transition, Door}
};

// 游戏物品共有属性定义
class GameObject {
public:
    int _index;                  // 物品索引
    std::string _fileName;       // 物品图片资源文件路径
    std::string _name;           // 物品名称
    GameObjectSkillType _type;   // 物品类型

    GameObject() = default;
    GameObject(const int index, const std::string& fileName, const std::string& name, GameObjectSkillType type) :
        _index(index),
        _fileName(fileName),
        _name(name),
        _type(type) {
    }
    int getID() {
        return _index;
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
    GameToolObject(const int index, const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, int actionCost, int durability, GameCharacterAction action) :
        GameObject(index,fileName, name, type),
        _level(level),
        _actionCost(actionCost),
        _durability(durability),
        _action(action)
    {
    }
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
    GameSeedObject(const int index, const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, Season season, std::vector<int> growthStages, int totalGrowTime, int harvestIndex, int buyPrice, int salePrice) :
        GameObject(index,fileName, name, type),
        _level(level),
        _season(season),
        _growthStages(growthStages),
        _totalGrowTime(totalGrowTime),
        _harvestIndex(harvestIndex),
        _buyPrice(buyPrice),
        _salePrice(salePrice)
    {
    }
};

// 游戏基础物品属性定义
class GameBaseObject : public GameObject {
public:
    int _maxStorage;                            // 物品最大存储量
    int _level;                                 // 解锁物品所需等级
    bool _sale;                                 // 是否能出售
    int _salePrice;                             // 出售价格
    bool _buy;                                  // 是否能购买
    int _buyPrice;                              // 购买价格
    bool _eat;                                  // 是否可以食用
    int _eatEnergy;                             // 食用恢复的能量值
    bool _place;                                // 能否放置
    bool _synthesis;                            // 是否可以合成
    std::map<int, int> _ingredients;	// 合成物品的原料
    // 构造函数
    GameBaseObject(const int index,const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level,  bool sale, int salePrice, bool buy,int buyPrice,bool eat, int eatEnergy, bool place, bool synthesis, std::map<int, int> ingredients = {}) :
        GameObject(index,fileName, name, type),
        _maxStorage(maxStorage),
        _level(level),
        _sale(sale),
        _salePrice(salePrice),
        _buy(buy),
        _buyPrice(buyPrice),
        _eat(eat),
        _eatEnergy(eatEnergy),
        _place(place),
        _synthesis(synthesis),
        _ingredients(ingredients)
    {
    }
};

// 游戏工具类物品属性参数定义
const std::vector<GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
    GameToolObject(1,"../Resources/Objects/Tools/BeginnerHoe.png", "初级锄头", Farm, 1, 1, INT_MAX, Plowing),
    GameToolObject(2,"../Resources/Objects/Tools/IntermediateHoe.png", "中级锄头", Farm, 2, 1, INT_MAX, Plowing),
    GameToolObject(3,"../Resources/Objects/Tools/AdvancedHoe.png", "高级锄头", Farm, 3, 1, INT_MAX, Plowing),
    GameToolObject(4,"../Resources/Objects/Tools/BeginnerAxe.png", "初级斧头", Collect, 1, 5, INT_MAX, Cutting),
    GameToolObject(5,"../Resources/Objects/Tools/IntermediateAxe.png", "中级斧头", Collect, 2, 4, INT_MAX, Cutting),
    GameToolObject(6,"../Resources/Objects/Tools/AdvancedAxe.png", "高级斧头", Collect, 3, 3, INT_MAX, Cutting),
    GameToolObject(7,"../Resources/Objects/Tools/BeginnerPickaxe.png", "初级镐子", Mine, 1, 5, INT_MAX, Mining),
    GameToolObject(8,"../Resources/Objects/Tools/IntermediatePickaxe.png", "中级镐子", Mine, 2, 4, INT_MAX, Mining),
    GameToolObject(9,"../Resources/Objects/Tools/AdvancedPickaxe.png", "高级镐子", Mine, 3, 3, INT_MAX, Mining),
    GameToolObject(10,"../Resources/Objects/Tools/BeginnerFishingRods.png", "初级鱼竿", Fish, 1, 1, INT_MAX, Fishing),
    GameToolObject(11,"../Resources/Objects/Tools/IntermediateFishingRods.png", "中级鱼竿", Fish, 2, 1, INT_MAX, Fishing),
    GameToolObject(12,"../Resources/Objects/Tools/AdvancedFishingRods.png", "高级鱼竿", Fish, 3, 1, INT_MAX, Fishing),
    GameToolObject(13,"../Resources/Objects/Tools/BeginnerKattle.png", "初级水壶", Farm, 1, 1, 40, Watering),
    GameToolObject(14,"../Resources/Objects/Tools/IntermediateKattle.png", "中级水壶", Farm, 2, 1, 55, Watering),
    GameToolObject(15,"../Resources/Objects/Tools/AdvancedKattle.png", "高级水壶", Farm, 3, 1, 70, Watering),
    GameToolObject(16,"../Resources/Objects/Tools/scythe.png","镰刀",Collect,1,1,INT_MAX,Weeding)
};


// 游戏基础类物品属性参数定义
const std::vector<GameBaseObject> GAME_BASE_OBJECTS_ATTRS = {
    GameBaseObject(17,"../Resources/Objects/Base/Timber.png","木材",Collect,99,0,true,3,false,INVAVID_NUM,false,INVAVID_NUM,false,false),
    GameBaseObject(18,"../Resources/Objects/Base/Stone.png","石头",Mine,99,0,true,5,false,INVAVID_NUM,false,INVAVID_NUM,false,false),
    GameBaseObject(19,"../Resources/Objects/Base/CopperParticle.png","铜粒",Mine,99,0,true,12,false,INVAVID_NUM,false,INVAVID_NUM,false,false),
    GameBaseObject(20,"../Resources/Objects/Base/IronParticle.png","铁粒",Mine,99,2,true,25,false,INVAVID_NUM,false,INVAVID_NUM,false,false),
    GameBaseObject(21,"../Resources/Objects/Base/Copper.png","铜锭",Mine,99,0,true,120,false,INVAVID_NUM,false,INVAVID_NUM,false,true,std::map<int, int>{{19,10}}),
    GameBaseObject(22,"../Resources/Objects/Base/Iron.png","铁锭",Mine,99,0,true,250,false,INVAVID_NUM,false,INVAVID_NUM,false,true,std::map<int, int>{{20,10}})
};

// 游戏种子类物品属性参数定义
const std::vector<GameSeedObject> GAME_SEED_OBJECTS_ATTRS = {

};

// 游戏物品属性定义
struct GameCommonObject {
    GameObjectMapType type;                             // 物品类型
    std::shared_ptr<GameObject> object;

    GameCommonObject() : type(None), object(nullptr) {} // 默认构造函数
    GameCommonObject(GameObjectMapType type, std::shared_ptr<GameObject> object) :
        type(type),
        object(object)
    {
    }

    std::shared_ptr<GameObject> loadGameObjectByID(int id) {
        // 尝试从工具对象列表中查找
        for (const auto& tool : GAME_TOOL_OBJECTS_ATTRS) {
            if (tool._index == id) {
                return std::make_shared<GameToolObject>(tool); // 找到工具对象，返回复制的 shared_ptr
            }
        }

        // 尝试从种子对象列表中查找
        for (const auto& seed : GAME_SEED_OBJECTS_ATTRS) {
            if (seed._index == id) {
                return std::make_shared<GameSeedObject>(seed); // 找到种子对象，返回复制的 shared_ptr
            }
        }

        // 尝试从基础对象列表中查找
        for (const auto& base : GAME_BASE_OBJECTS_ATTRS) {
            if (base._index == id) {
                return std::make_shared<GameBaseObject>(base); // 找到基础对象，返回复制的 shared_ptr
            }
        }
        return nullptr;
    }

    void save(std::ofstream& outFile) const {
        outFile.write(reinterpret_cast<const char*>(&type), sizeof(type));
        int objectID = object ? object->getID() : -1; // 假设有 getID 方法
        outFile.write(reinterpret_cast<const char*>(&objectID), sizeof(objectID));
    }

    void load(std::ifstream& inFile) {
        inFile.read(reinterpret_cast<char*>(&type), sizeof(type));
        int objectID;
        inFile.read(reinterpret_cast<char*>(&objectID), sizeof(objectID));

        if (objectID != -1) {
            object = loadGameObjectByID(objectID); // 通过 ID 加载对象的方法
        }
        else {
            object = nullptr;
        }
    }
};
// 物品栏中物品状态定义
enum ObjectListNodeStatus {
    Unselected,		// 未选中
    Selected		// 选中
};

// 角色物品栏单个物品属性定义
struct ObjectListNode {
    GameCommonObject objectNode;	// 物品信息
    int count;						// 物品数量
    ObjectListNodeStatus status;	// 物品状态(选中/未选中)

    // 自定义序列化函数
    void save(std::ofstream& outFile) const {
        objectNode.save(outFile);
        outFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
        outFile.write(reinterpret_cast<const char*>(&status), sizeof(status));
    }

    // 自定义反序列化函数
    void load(std::ifstream& inFile) {
        objectNode.load(inFile);
        inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
        inFile.read(reinterpret_cast<char*>(&status), sizeof(status));
    }
};

// 单个箱子的结构定义
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

    BoxNode(cocos2d::Vec2 worldPosition) :
        _maxObjectKindCount(OBJECT_LIST_COLS),
        _worldPosition(worldPosition)
    {
        _boxObjectList.resize(_maxObjectKindCount);
    }
};




#endif // !_CONSTANT_H_
