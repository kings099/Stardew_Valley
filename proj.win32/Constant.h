#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_


#include <string>
#include <memory>
#include<fstream>
#include <map>
#include "cocos2d.h"
#include"../Classes/MenuImage/HoverMenuItemImage.h"

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

// 颜色相关设置
const cocos2d::Color4B HLAFBLACK = cocos2d::Color4B(0, 0, 0, 200);         // 半透明黑色

//游戏登录界面相关设置
constexpr float VISIBLE_SIZE_RATIO_X = 1.0f;                               // 横向屏幕宽度比例因子（常量，默认1.0）
constexpr float VISIBLE_SIZE_RATIO_Y = 1.0f;                               // 纵向屏幕高度比例因子（常量，默认1.0）
constexpr float INPUT_BOX_HEIGHT_RATIO = 0.07f;                            // 输入框高度的比例因子（默认 7%）,实际数值为屏幕高度*该因子
constexpr float VERTICAL_SPACING_RATIO = 0.02f;                            // 提示文本和输入框之间的垂直间距,实际数值为屏幕高度*该因子
constexpr float INPUT_BOX_SPACING_RATIO = 0.14f;                           // 输入框和输入框之间的间距比例,实际数值为屏幕高度*该因子
constexpr float LABEL_Y_OFFSET = 0.6f;                                     // 标签的Y偏移量比例因子,实际数值为屏幕高度*该因子
constexpr float HALF_FACTOR = 0.5f;                                        // 替代 / 2 的常量因子

//NPC相关设置
constexpr float NPC_WIDTH = 16;											    // NPC宽度
constexpr float NPC_HEIGHT =32;                                             // NPC高度
constexpr int   AFFECTION_INDEX = 25;                                       // NPC喜爱度因子
constexpr int   MAX_AFFECTION = 100;                                        //最大喜爱度的值
constexpr int   MARRIAGE_AFFECTION = 20;                                    //满足结婚条件的喜爱度下限
constexpr float DIALOG_WIDTH = 500.0f;                                      //对话框宽度
constexpr float DIALOG_HEIGHT = 120.0f;                                     //对话框高度
constexpr int DIALOG_X_OFFSET = 250;                                        //对话框相对NPC的偏移量
constexpr int DIALOG_Y_OFFSET = 160;                                        //对话框相对于NPC的偏移量



// 移动相关设置
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效键值

constexpr int INVAVID_NUM = -1;												// 无效编号

// 角色相关设置
constexpr int CHARACTER_WIDTH = 32;											// 角色宽度
constexpr int CHARACTER_HEIGHT = 32;										// 角色高度
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// 角色移动速度
constexpr float CHARACTER_HORIZONTAL_ANCHORPOINT = 0.5f;					// 角色水平锚点
constexpr float CHARACTER_VERTICAL_ANCHORPOINT = 0.25f;						// 角色垂直锚点
constexpr int LEVEL1_TO_LEVEL2_EXPRIENCE = 20;                              // 从一级升到二级需要的经验值
constexpr int LEVEL2_TO_LEVEL3_EXPRIENCE = 50;                              // 从二级升到三级需要的经验值
constexpr int LEVEL3_TO_LEVEL4_EXPRIENCE = 100;                             // 从三级升到四级需要的经验值
constexpr int LEVEL4_TO_LEVEL5_EXPRIENCE = 200;                             // 从四级升到五级需要的经验值
constexpr int SKILL_KIND_NUM = 4;                                           // 技能种类数量
constexpr int SKILL_LEVEL_NUM = 5;                                          // 技能最大等级
constexpr int MIN_FISHING_DISTANCE = 3;                                     // 鱼竿最小捕鱼距离
constexpr int MAX_FISHING_DISTANCE = 5;                                     // 鱼竿最大捕鱼距离
constexpr int START_UP_MONEY = 500;                                         // 初始金钱
constexpr float SKILL_GET_ITEM_PROBABILITY = 0.1f;                          // 技能等级对获取物品概率的影响因子
constexpr int SYNTHESIS_TABLE_ROWS = 4;                                     // 合成台行数
constexpr int SYNTHESIS_TABLE_COLS = 6;                                     // 合成台列数
constexpr float ACTION_RATE = 5.0f;											// 动作帧率


// 商店相关设置
constexpr int PRODUCE_KIND_NUM_EACH_DAY = 4;                                // 每日出售的商品种类数量
constexpr int MAX_PRODUCT_COUNT_EACH_DAY = 5;                               // 每日出售的一种商品的最大数量
constexpr int PRODUCT_ATTR_NUM = 3;                                         // 商品属性数量
constexpr float INCREASE_RATE_BY_SEASON = 1.2f;                             // 商品价格上涨比例(季节)
constexpr float DISCOUNT_RATE_BY_SEASON = 0.8f;                             // 商品价格下跌比例(季节)
constexpr float DISCOUNT_RATE_BY_WEEKDAY = 0.5f;                             // 商品价格下跌比例(日期)


// 场景过渡相关
constexpr float LERP_SPEED = 0.1f;											// 插值平滑速度
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// 场景切换时间
constexpr float FARM_MAP_SCALE = 2.0f;										// 农场地图缩放比例
constexpr float INDOOR_MAP_SCALE = 3.0f;									// 室内地图缩放比例
constexpr float TOWN_MAP_SCALE = 2.0f;                                      // 小镇地图缩放
constexpr int FARM_HOUSE_CREAT_X = 1816;                                    // 农场室内地图创建位置
constexpr int FARM_HOUSE_CREAT_Y = 1538;                                    // 农场室内地图创建位置
constexpr int TOWN_CREAT_X = 2454;                                          // 小镇地图创建位置
constexpr int TOWN_CREAT_Y = 920;                                           // 小镇地图创建位置
constexpr int FARM_HOUSE_TELE_X = 3;                                        // 农场室内地图传送位置
constexpr int FARM_HOUSE_TELE_Y = 10;                                       // 农场室内地图传送位置
constexpr int TOWN_TELE_X = 1;                                              // 小镇地图传送位置
constexpr int TOWN_TELE_Y = 91;                                             // 小镇地图传送位置
constexpr int MINE_CREAT_X = 1080;                                          // 矿洞地图的创建位置
constexpr int MINE_CREAT_Y = 1120;                                          // 矿洞地图的创建位置
constexpr int MINE_TELE_X = 1;                                              // 农场室内地图传送X坐标
constexpr int MINE_TELE_Y = 5;                                              // 农场室内地图传送Y坐标

// 地图图块相关
namespace TileConstants {
    constexpr int DRY_FARM_TILE_GID = 2040;                                     // 干燥耕地效果动画图块GID
    constexpr int WET_FARM_TILE_GID = 2044;                                     // 湿润耕地效果动画图块GID
    constexpr int FIRT_FARM_TILE_GID = 2048;                                    // 模拟施肥动画效果
    constexpr int EMPTY_GID = 0;                                                // 空白GID
    constexpr int WOOD_GID = 7;                                                 // 树桩标记GID（不可见）
    constexpr int OAK_GID = 10;                                                 // 桦树GID
    constexpr int MAMPLE_GID = 11;                                              // MAMPLE GID
    constexpr int PINE_GID = 12;                                                // PINE GID
    constexpr int CROP_INVISIBLE_GID = 4;                                       // 作物树根图块不可见GID
    constexpr int OAK_INVISIBLE_GID = 1;                                        // OAK树根图块不可见GID
    constexpr int MAMPLE_INVISIBLE_GID = 2;                                     // MAMPLE树根图块不可见GID
    constexpr int PINE_INVISIBLE_GID = 3;                                       // PINE树根图块不可见GID
    constexpr int OAK_ROOT_GID = 191;                                           // OAK树根GID
    constexpr int MAMPLE_ROOT_GID = 194;                                        // MAMPLE树根GID
    constexpr int PINE_ROOT_GID = 201;                                          // PINE树根GID

    constexpr float GRASS_DROP_PROBABILITY = 0.5f;                              // 草掉落概率
    constexpr float STONE_DROP_PROBABILITY = 0.3f;                              // 石头掉落概率
    constexpr float BRANCH_DROP_PROBABILITY = 0.3f;                             // 树枝和树桩掉落概率
    constexpr float TREE_DROP_PROBABILITY = 0.9f;                               // 树木掉落概率
    constexpr float MINE_DROP_PROBABILITY = 0.5f;                               // 矿物掉落概率    
    constexpr float STONE_DROP_MINE_PROBABILITY = 0.1f;                         // 挖矿时石头掉落概率    
    constexpr float TREATURE_PROBABILITY = 1.0f;                                // 珍惜物品掉落概率
    constexpr float UPDATA_POSIIBILITY = 0.5f;                                  // 矿洞物品刷新几率

    constexpr int DEFAULT_DROP_QUANTITY = 1;                                    // 默认掉落数量
    constexpr int MUTI_DROP_QUANTITY = 3;                                       // 默认多个掉落数量

    // 瓦片信息
    enum TileType {
        Grass,      // 草
        Tree,       // 树木
        Wood,       // 树桩
        Branch,     // 树枝
        Mine,       // 矿石
        Treasure,   // 珍惜物品
        Stone,      // 石头
        Box,        // 箱子
        Water,      // 水
        Soil,       // 可耕种土地
        Soiled,     // 已耕种土地
        Crop,       // 作物
        Other
    };

    // 用于记录地图变化
    struct TileChange {
        std::string layerName;          // 图层名称
        cocos2d::Vec2 tileCoord;        // 瓦片坐标
        int newGID;                     // 瓦片的新 GID

        // 默认构造
        TileChange()
            : layerName(""), tileCoord(cocos2d::Vec2::ZERO), newGID(0) {}

        TileChange(const std::string& layer, const cocos2d::Vec2& coord, int gid)
            : layerName(layer), tileCoord(coord), newGID(gid) {}
    };
    

    // 用于记录地图放置物品与对应GID的映射关系
    const std::unordered_map<std::string, int> objectGIDMap = {
            {"Box", 4231},
            // 在此添加更多物品名称和对应的 GID
    };


}
// 物品设置
constexpr int OBJECT_LIST_ROWS = 3;											// 物品列表行数
constexpr int OBJECT_LIST_COLS = 12;										// 物品列表列数

//初始界面相关设置
constexpr int BG_MOVE_SPEED = 2;                                           //背景图移动速度
constexpr float BG_UPDATE_RATIO = 0.016f;                                  //背景图更新速度






// UI 相关设置

const std::string FONT_TYPE = "fonts/arial.ttf";                            // UI界面字体类型
constexpr int UI_SCALE = 210.0f;                                            // UI界面缩放
constexpr int FONT_SIZE = 20;                                               // 字体大小
constexpr int MAP_LAYER_GRADE = 0;                                          // 地图层级
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // 角色层级
constexpr int VIEW_CONTROLLER_LAYER_GRADE = 1;                              // 视角控制类层级
constexpr int TREE_LAYER_GRADE = 2;                                         // 树木层级
constexpr int UI_LAYER_GRADE = 3;                                           // UI层级
constexpr int OBJECT_LAYER_GRADE = 4;                                       // 物品层级
constexpr int ANIMATION_LAYER_GRADE = 10;                                   // 动画层级
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
constexpr int OBJECT_STORE_IMAGE_START_X = 1410;                            // 商店售卖物品图片起始位置的X坐标
constexpr int OBJECT_STORE_IMAGE_START_Y = 603;                             // 商店售卖物品图片起始位置的Y坐标
constexpr int MONEY_COUNT_LABEL_START_X = 1807;                             // 角色金钱数量标签起始位置的X坐标
constexpr int MONEY_COUNT_LABEL_START_Y = 894;                              // 角色金钱数量标签起始位置的Y坐标
constexpr int SYNTHESIS_TABLE_START_X = 1431;                               // 合成表图片起始位置的X坐标
constexpr int SYNTHESIS_TABLE_START_Y = 583;                                // 合成表图片起始位置的Y坐标
constexpr int OBJECT_STORE_IMAGE_NAME_HORIZONTAL_INTERVAL = 102;	        // 商店售卖物品图片名称水平间距
constexpr int OBJECT_STORE_NAME_PRICE_HORIZONTAL_INTERVAL = 130;			// 商店售卖物品名称和价格水平间距
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// 物品格子水平间距
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// 物品格子垂直间距
constexpr float OBJECT_NODE_SCALE = 2.0f;									// 物品缩放比例
constexpr float BUTTON_SCALE = 2.0f;										// 按钮缩放比例
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// 物品栏删除按钮左边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// 物品栏删除按钮右边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// 物品栏删除按钮上边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// 物品栏删除按钮下边界
constexpr int OPEN_OBJIEC_LIST_SELL_BUTTON_LEFT_BOUDARY = 1472;			    // 物品栏出售按钮左边界
constexpr int OPEN_OBJIEC_LIST_SELL_BUTTON_RIGHT_BOUDARY = 1600;			// 物品栏出售按钮右边界
constexpr int OPEN_OBJIEC_LIST_SELL_BUTTON_TOP_BOUDARY = 328;				// 物品栏出售按钮上边界
constexpr int OPEN_OBJIEC_LIST_SELL_BUTTON_BOTTOM_BOUDARY = 392;			// 物品栏出售按钮下边界
const cocos2d::Vec2 RIGHT_ALIGNED_ANCHOR (1.0f, 0.5f );                     // 文字标签右对齐锚点设置

//NPC求婚对话框相关设置
constexpr float DIALOG_WIDTH_RATIO = 0.5f;                                  // 对话框宽度占屏幕宽度的比例
constexpr float DIALOG_HEIGHT_RATIO = 0.25f;                                // 对话框高度占屏幕高度的比例
constexpr float BUTTON_SIZE_RATIO = 0.1f;                                   // 按钮大小占对话框大小的比例
constexpr float BUTTON_OFFSET_RATIO = 0.2f;                                 // 按钮与对话框边缘的距离比例


// 游戏季节定义
enum Season {
    Spring,				// 春天
    Summer,				// 夏天
    Fall,				// 秋天
    Winter,				// 冬天
    All					// 通用
};
// 游戏时间设置

constexpr int INIT_DAY = 1;                                                 //游戏启动时的天数 
constexpr int INIT_HOUR = 6;                                                //游戏启动时的时间
constexpr int INIT_MIN = 0;                                                 //游戏启动时的分钟数
constexpr bool INIT_IS_DAY = 0;                                             //游戏启动时是否白天
const Season  INIT_SEASON =Season::Spring;                                  //游戏启动时的季节
constexpr int HOURS_IN_A_DAY = 24;                                          // 一天24小时                                     
constexpr int DAYS_IN_A_SEASON = 7;                                         // 每季7天
constexpr int DAYS_IN_A_WEEK = 7;                                           // 每周7天
constexpr int DAYS_IN_A_YEAR = 28;                                          // 一年28天
constexpr int DAY_START = 6;                                                // 白天的开始时间
constexpr int DAY_END = 18;                                                 // 白天的结束时间

//农作物相关设置
constexpr int MIN_GROWTHSTAGE = 0;                                          //最小生长阶段
constexpr int CAULIFLOWER_MAX_GROWTHSTAGE = 5;                              //花椰菜共有5个生长阶段
constexpr int KALE_MAX_GROWTHSTAGE = 5;                                     //甘蓝菜共有5个生长阶段
constexpr int PUMPKIN_MAX_GROWTHSTAGE = 6;                                  //南瓜共有6个生长阶段
constexpr int OAK_MAX_GROWTHSTAGE = 5;                                      //橡树共有5个生长阶段
constexpr int MAPLE_MAX_GROWTHSTAGE = 5;                                    //枫树共有5个生长阶段
constexpr int PINE_MAX_GROWTHSTAGE = 5;                                     //松树共有5个生长阶段
constexpr float CROP_START_RATIO = 1.5f;                                    //农作物未成熟时的缩放比例
constexpr float CROP_MATURE_RATIO = 1.0f;                                    //农作物成熟时的缩放比例
constexpr float CROP_HORIZONTAL_ANCHORPOINT = 0.5f;					        // 树水平锚点
constexpr float CROP_VERTICAL_ANCHORPOINT = 0.0f;						    // 树垂直锚点

//动物类
constexpr float ANIMAL_RATIO = 1.0f;                                            //动物类的缩放比例
constexpr float ANGRY_ICON_RATIO = 0.8f;                                        //动物发怒提示的缩放比例

//鱼类
constexpr float FISH_RATIO = 1.0f;                                              // 鱼的缩放比例
constexpr float FAIL_TO_GET_FISH = 0.3f;                                        // 钓不到鱼的概率

//动画类
constexpr float WOOD_CUT_RATIO = 0.3f;                                          // 砍木桩动画的缩放比例
constexpr float WEEDING_RATIO = 0.4f;                                           // 除草动画的缩放比例
constexpr float STONE_BREAK_RATIO = 0.2f;                                       // 碎石动画的缩放比例
constexpr float WATER_RATIO = 0.8f;                                             // 浇水动画的缩放比例
constexpr float BRANCH_RATIO = 0.5f;                                            // 砍树枝动画的缩放比例

// 地图类型设置
enum class MapType {
    Generic,
    Mine,
    Farm,
    Indoor,
    Town
};


//游戏物品对应技能类型定义
enum GameObjectSkillType {
    Farm,				// 耕种
    Collect,			// 采集
    Mine,				// 采矿
    Fish,				// 钓鱼
   // None,				// 无
};

// 游戏工具类型定义
enum GameTools {
    Hoe,				// 锄头
    Ax,					// 斧头
    Pickaxe,			// 镐子
    FishingRod,			// 鱼竿
    Kettle				// 水壶
};



// 游戏天气定义
enum Weather {
    Sunny,              // 晴天
    Rainy,              // 雨天
    Dry                 // 干旱
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
    Up,                 // 上
    Down,               // 下
    Left,               // 左
    Right,              // 右
};

// 鼠标按键
enum MouseButton {
    LeftButton,			// 左键
    RightButton,		// 右键
};

// 物品栏中物品状态定义
enum ObjectListNodeStatus {
    Unselected,		// 未选中
    Selected		// 选中
};

// 位置状态定义
enum LocationStatus {
    ClosedObjectList,		// 物品栏关闭
    OpenedObjectList,		// 物品栏打开
    OpenedBoxList,			// 箱子列表打开
};


// 角色动作定义
enum GameCharacterAction {
    NoneAction,			// 空动作
    Plowing,			// 耕地
    Seeding,            // 播种
    Watering,			// 浇水
    Fertilize,          // 施肥
    GetWater,			// 取水
    Weeding,            // 除草
    Cutting,			// 砍树
    Mining,				// 采矿
    Fishing,		    // 钓鱼
    Harvesting,			// 收获
    Placement,			// 放置
    OpenBox,			// 打开箱子
    DestoryObject,		// 破坏物品
};


// 单个瓦片坐标信息定义
struct TileInfo {
    TileConstants::TileType type;   // 瓦片类型
    cocos2d::Vec2 tilePos;          // 瓦片坐标
    cocos2d::Vec2 WorldPos;         // 世界坐标
    bool isObstacle;                // 是否为障碍物
    std::unordered_map<std::string, std::pair<int, float>> drops; // 掉落物品映射 (物品名称 -> {数量, 概率})
};

// 位置属性定义
struct Location {
    LocationStatus status;   // 位置状态
    int position;            // 位置编号
    bool operator<(const Location& other) const { // 重载运算符 < 用于 std::map
        if (status < other.status) {
            return true;
        }
        if (status > other.status) {
            return false;
        }
        return position < other.position;
    }
};

// 物品图片信息定义
struct ObjectImageInfo {
    cocos2d::Sprite* sprite; // 物品图片
    cocos2d::Label* label;   // 物品数量标签
    

    ObjectImageInfo() :
        sprite(nullptr),
        label(nullptr) {
    }
    ObjectImageInfo(cocos2d::Sprite* sprite, cocos2d::Label* label) :
        sprite(sprite),
        label(label) {
    }

    ObjectImageInfo& operator = (const ObjectImageInfo& other) {
        if (this != &other) { // 防止自我赋值
            sprite = other.sprite;
            label = other.label;
        }
        return *this;
    }
};

// 商店物品信息定义
struct StoreObjectInfo {
    cocos2d::Sprite* sprite;     // 物品图片
    cocos2d::Label* namelabel;   // 物品名称标签
    cocos2d::Label* pricelabel;  // 物品价格标签

    StoreObjectInfo() :
        sprite(nullptr),
        namelabel(nullptr),
        pricelabel(nullptr) {
        }
    StoreObjectInfo(cocos2d::Sprite* sprite, cocos2d::Label* namelabel, cocos2d::Label* pricelabel) :
        sprite(sprite),
        namelabel(namelabel),
        pricelabel(pricelabel) {
    }

    StoreObjectInfo& operator = (const StoreObjectInfo& other) {
        if (this != &other) { // 防止自我赋值
            sprite = other.sprite;
            namelabel = other.namelabel;
            pricelabel = other.pricelabel;
        }
        return *this;
    }
};

// 角色动作和地图类型对应关系
const std::map< GameCharacterAction, std::vector<TileConstants::TileType>> ACTION_TO_TILEMAP = {
    { NoneAction,   { TileConstants::Other }},
    { Plowing,      { TileConstants::Soil}},           // 左键
    { Seeding,      { TileConstants::Soiled }},        // 右键
    { Watering,     { TileConstants::Soiled }},       // 左键
    { Fertilize,    { TileConstants::Soiled}},        // 左键
    { GetWater,     { TileConstants::Water }},         // 右键
    { Weeding,      { TileConstants::Grass }},         // 左键
    { Cutting,      { TileConstants::Tree ,TileConstants::Branch,TileConstants::Wood}},          // 左键
    { Mining,       { TileConstants::Stone,TileConstants::Mine ,TileConstants::Treasure}},            // 左键
    { Fishing,      { TileConstants::Water }},         // 左键
    { Harvesting,   { TileConstants::Crop }},          // 右键
    { Placement,    { TileConstants::Soil }},          // 右键
    //{ OpenBox,      {TileConstants::Box}},            // 右键
    { DestoryObject, {TileConstants::Other,TileConstants::Box}}         // 左键
  };

// 游戏物品共有属性定义
class GameObject {
public:
    int _index;                  // 物品索引
    std::string _fileName;       // 物品图片资源文件路径
    std::string _name;           // 物品名称(英文）
    std::string _nameCN;         // 物品名称(中文)
    GameObjectSkillType _type;   // 物品类型

    GameObject() = default;
    GameObject(const int index, const std::string& fileName, const std::string& name,const std::string& nameCN, GameObjectSkillType type) :
        _index(index),
        _fileName(fileName),
        _nameCN(nameCN),
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
    int _level;                                     // 工具等级
    int _durability;                                // 工具耐久度
    GameCharacterAction _action;                    // 工具当前执行的动作
    bool _isUpgradable ;                            // 是否可以升级
    std::map<std::string, int> _ingredients;	    // 升级工具的原料

    // 构造函数
    GameToolObject(const int index, const std::string& fileName, const std::string& name,const std::string& nameCN, GameObjectSkillType type, int level, int durability, GameCharacterAction action, bool isUpgradable, std::map<std::string, int> ingredients) :
        GameObject(index,fileName, name, nameCN,type),
        _level(level),
        _durability(durability),
        _action(action),
        _isUpgradable(isUpgradable),
        _ingredients(ingredients)
    {
    }

    GameToolObject() {};
};

// 游戏种子物品属性定义
class GameSeedObject : public GameObject {
public:
    int _level;                             // 解锁种子所需等级
    Season _season;                         // 种子生长季节
    int _harvestIndex;                      // 种子收获所得的物品索引
    int _buyPrice;                          // 种子购买价格
    int _sellPrice;                         // 种子出售价格

    // 构造函数
    GameSeedObject(const int index, const std::string& fileName, const std::string& name, const std::string& nameCN, GameObjectSkillType type, int level, Season season,  int harvestIndex, int buyPrice, int sellPrice) :
        GameObject(index,fileName, name,nameCN, type),
        _level(level),
        _season(season),
        _harvestIndex(harvestIndex),
        _buyPrice(buyPrice),
        _sellPrice(sellPrice)
    {
    }
    GameSeedObject() {};
};

// 游戏基础物品属性定义
class GameBaseObject : public GameObject {
public:
    int _maxStorage;                            // 物品最大存储量
    int _level;                                 // 解锁物品所需等级
    bool _sell;                                 // 是否能出售
    int _sellPrice;                             // 出售价格
    bool _buy;                                  // 是否能购买
    int _buyPrice;                              // 购买价格
    bool _eat;                                  // 是否可以食用
    int _eatEnergy;                             // 食用恢复的能量值
    bool _place;                                // 能否放置
    bool _synthesis;                            // 是否可以合成
    std::map<std::string, int> _ingredients;	        // 合成物品的原料
    // 构造函数
    GameBaseObject(const int index, const std::string& fileName, const std::string& name, const std::string& nameCN, GameObjectSkillType type, int maxStorage, int level, bool sell, int sellPrice, bool buy, int buyPrice, bool eat, int eatEnergy, bool place, bool synthesis, std::map<std::string, int> ingredients = {}) :
        GameObject(index, fileName, name,nameCN, type),
        _maxStorage(maxStorage),
        _level(level),
        _sell(sell),
        _sellPrice(sellPrice),
        _buy(buy),
        _buyPrice(buyPrice),
        _eat(eat),
        _eatEnergy(eatEnergy),
        _place(place),
        _synthesis(synthesis),
        _ingredients(ingredients)
    {
    }

    GameBaseObject() {};


};


// 游戏工具类物品属性参数定义
const std::vector<GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
    GameToolObject(1,"../Resources/Objects/Tools/BeginnerHoe.png","BeginnerHoe", "初级锄头", Farm, 1, INT_MAX, Plowing,false,{}),
    GameToolObject(2,"../Resources/Objects/Tools/IntermediateHoe.png","IntermediateHoe", "中级锄头", Farm, 2, INT_MAX, Plowing,true,{{"BeginnerHoe",1}, {"Copper",3}}),
    GameToolObject(3,"../Resources/Objects/Tools/AdvancedHoe.png","AdvancedHoe" ,"高级锄头", Farm, 3, INT_MAX, Plowing,true,{{"IntermediateHoe",1}, {"Iron",3}}),
    GameToolObject(4,"../Resources/Objects/Tools/BeginnerAxe.png","BeginnerAxe","初级斧头", Collect, 1, INT_MAX, Cutting,false,{}),
    GameToolObject(5,"../Resources/Objects/Tools/IntermediateAxe.png","IntermediateAxe","中级斧头", Collect, 2, INT_MAX, Cutting,true,{{"BeginnerAxe",1}, {"Copper",3}}),
    GameToolObject(6,"../Resources/Objects/Tools/AdvancedAxe.png","AdvancedAxe", "高级斧头", Collect, 3, INT_MAX, Cutting,true,{{"IntermediateAxe",1}, {"Iron",3}}),
    GameToolObject(7,"../Resources/Objects/Tools/BeginnerPickaxe.png","BeginnerPickaxe","初级镐子", Mine, 1, INT_MAX, Mining,false,{}),
    GameToolObject(8,"../Resources/Objects/Tools/IntermediatePickaxe.png","IntermediatePickaxe", "中级镐子", Mine, 2, INT_MAX, Mining,true,{{"BeginnerPickaxe",1}, {"Copper",3}}),
    GameToolObject(9,"../Resources/Objects/Tools/AdvancedPickaxe.png","AdvancedPickaxe", "高级镐子", Mine, 3, INT_MAX, Mining,true,{{"IntermediatePickaxe",1}, {"Iron",3}}),
    GameToolObject(10,"../Resources/Objects/Tools/BeginnerFishingRods.png","BeginnerFishingRods", "初级鱼竿", Fish, 1, INT_MAX, Fishing,false,{}),
    GameToolObject(11,"../Resources/Objects/Tools/IntermediateFishingRods.png", "IntermediateFishingRods","中级鱼竿", Fish, 2,  INT_MAX, Fishing,true,{{"BeginnerFishingRods",1}, {"Copper",3}}),
    GameToolObject(12,"../Resources/Objects/Tools/AdvancedFishingRods.png","AdvancedFishingRods", "高级鱼竿", Fish, 3, INT_MAX, Fishing,true,{{"IntermediateFishingRods",1}, {"Iron",3}}),
    GameToolObject(13,"../Resources/Objects/Tools/BeginnerKattle.png","BeginnerKattle", "初级水壶", Farm, 1, 40, Watering,false,{}),
    GameToolObject(14,"../Resources/Objects/Tools/IntermediateKattle.png","IntermediateKattle", "中级水壶", Farm, 2, 55, Watering,true,{{"BeginnerKattle",1}, {"Copper",3}}),
    GameToolObject(15,"../Resources/Objects/Tools/AdvancedKattle.png","AdvancedKattle", "高级水壶", Farm, 3, 70, Watering,true,{{"IntermediateKattle",1}, {"Iron",3}}),
    GameToolObject(16,"../Resources/Objects/Tools/scythe.png","scythe","镰刀",Collect,1,INT_MAX,Weeding,false,{})
};

// 游戏种子类物品属性参数定义
const std::vector<GameSeedObject> GAME_SEED_OBJECTS_ATTRS = {
     GameSeedObject(17,"../Resources/Crops/Cauliflower/cauliflower_0.png","cauliflowerSeed","花椰菜种子",Farm,1,Spring,20,80,175),//花椰菜种子
     GameSeedObject(18,"../Resources/Crops/Kale/kale_0.png","kaleSeed","甘蓝菜种子",Farm,1,Spring,21,60,90),//甘蓝菜种子
     GameSeedObject(19, "../Resources/Crops/Pumpkin/pumpkin_0.png","pumpkinSeed","南瓜种子",Farm,3,Fall,22,100,160)//南瓜种子
};

// 游戏种子名称到农作物名称的映射，可拓展
const std::unordered_map<std::string, std::string> GAME_SEED_TO_CROP_MAP = {
    {"cauliflowerSeed", "cauliflower"},
    {"kaleSeed", "kale"},
    {"pumpkinSeed", "pumpkin"}
};


// 游戏基础类物品属性参数定义
const std::vector<GameBaseObject> GAME_BASE_OBJECTS_ATTRS = {
     GameBaseObject(20, "../Resources/Crops/Cauliflower/cauliflower_4.png", "cauliflower","花椰菜", Farm,//花椰菜
        500, // 最大存储量
        1,   // 解锁所需等级
        true, // 是否能出售
        120,  // 出售价格
        true, // 是否可以购买
        150,    // 购买价格
        true, // 是否可以食用
        20,   // 食用恢复的能量值
        false, // 能否放置
        false, // 是否可以合成
        {}    // 合成物品的原料
    ),
    GameBaseObject(21, "../Resources/Crops/Kale/kale_4.png", "kale", "甘蓝菜",Farm,//甘蓝菜
        400, // 最大存储量
        1,   // 解锁所需等级
        true, // 是否能出售
        100,  // 出售价格
        true, // 是否可以购买
        120,    // 购买价格
        true, // 是否可以食用
        15,   // 食用恢复的能量值
        false, // 能否放置
        false, // 是否可以合成
        {}    // 合成物品的原料
    ),
    GameBaseObject(22, "../Resources/Crops/Pumpkin/pumpkin_5.png", "pumpkin","南瓜" ,Farm,//南瓜
        600, // 最大存储量
        3,   // 解锁所需等级
        true, // 是否能出售
        150,  // 出售价格
        true, // 是否可以购买
        180,    // 购买价格
        true, // 是否可以食用
        25,   // 食用恢复的能量值
        false, // 能否放置
        true,  // 是否可以合成
        {{"pumpkin_seed", 3}, {"Fertilizer", 1}} // 合成物品的原料
    ),
    GameBaseObject(23,"../Resources/Objects/Base/Timber.png","Timber", "木材",Collect,99,1,true,3,false,INVAVID_NUM,false,INVAVID_NUM,false,false,{}),
    GameBaseObject(24,"../Resources/Objects/Base/Stone.png","Stone","石头",Mine,99,1,true,5,false,INVAVID_NUM,false,INVAVID_NUM,false,false,{}),
    GameBaseObject(25,"../Resources/Objects/Base/CopperParticle.png","CopperParticle","铜粒",Mine,99,1,true,12,false,INVAVID_NUM,false,INVAVID_NUM,false,false,{}),
    GameBaseObject(26,"../Resources/Objects/Base/IronParticle.png","IronParticle","铁粒",Mine,99,2,true,25,false,INVAVID_NUM,false,INVAVID_NUM,false,false,{}),
    GameBaseObject(27,"../Resources/Objects/Base/Copper.png","Copper","铜锭",Mine,99,1,true,120,false,INVAVID_NUM,false,INVAVID_NUM,false,true,{{"CopperParticle",5}}),
    GameBaseObject(28,"../Resources/Objects/Base/Iron.png","Iron","铁锭",Mine,99,1,true,250,false,INVAVID_NUM,false,INVAVID_NUM,false,true,{{"IronParticle",5}}),
    GameBaseObject(29,"../Resources/Objects/Base/Fertilizer.png","Fertilizer","肥料",Farm,99,1,true,150,true,200,false,INVAVID_NUM,false,true,{{"Grass",3}}),
    GameBaseObject(30,"../Resources/Objects/Base/Grass.png","Grass","草",Collect,99,1,true,5,false,INVAVID_NUM,false,INVAVID_NUM,false,false,{}),
    GameBaseObject(31,"../Resources/Objects/Base/Box.png","Box","箱子",Collect,1,1,true,5,false,INVAVID_NUM,false,INVAVID_NUM,false,true,{{"Timber",5}}),


GameBaseObject(31, "../Resources/Objects/Base/Bigeye.png", "Bigeye", "大眼鱼", Fish,  // 大眼鱼
   100, // 最大存储量
   1,   // 解锁所需等级
   true, // 是否能出售
   150,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   40,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(32, "../Resources/Objects/Base/LargemouthBass.png", "LargemouthBass", "大嘴鲈鱼", Fish,  // 大嘴鲈鱼
   100, // 最大存储量
   2,   // 解锁所需等级
   true, // 是否能出售
   170,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   45,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(33, "../Resources/Objects/Base/Salmon.png", "Salmon", "鲑鱼", Fish,  // 鲑鱼
   100, // 最大存储量
   3,   // 解锁所需等级
   true, // 是否能出售
   200,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   50,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(34, "../Resources/Objects/Base/Squid.png", "Squid", "鱿鱼", Fish,  // 鱿鱼
   100, // 最大存储量
   1,   // 解锁所需等级
   true, // 是否能出售
   225,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   70,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(35, "../Resources/Objects/Base/Sardines.png", "Sardines", "沙丁鱼", Fish,  // 沙丁鱼
   100, // 最大存储量
   2,   // 解锁所需等级
   true, // 是否能出售
   150,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   40,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(36, "../Resources/Objects/Base/Herring.png", "Herring", "鲱鱼", Fish,  // 鲱鱼
   100, // 最大存储量
   5,   // 解锁所需等级
   true, // 是否能出售
   350,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   60,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(37, "../Resources/Objects/Base/RedMullet.png", "RedMullet", "红鲻鱼", Fish,  // 红鲻鱼
   100, // 最大存储量
   1,   // 解锁所需等级
   true, // 是否能出售
   180,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   35,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(38, "../Resources/Objects/Base/Carps.png", "Carps", "鲤鱼", Fish,  // 鲤鱼
   100, // 最大存储量
   1,   // 解锁所需等级
   true, // 是否能出售
   180,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   45,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(39, "../Resources/Objects/Base/Octopus.png", "Octopus", "章鱼", Fish,  // 章鱼
   100, // 最大存储量
   3,   // 解锁所需等级
   true, // 是否能出售
   275,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   70,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(40, "../Resources/Objects/Base/RedSnapper.png", "RedSnapper", "红鲷鱼", Fish,  // 红鲷鱼
   100,     // 最大存储量
   3,       // 解锁所需等级
   true,    // 是否能出售
   200,     // 出售价格
   false,   // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true,           // 是否可以食用
   50,             // 食用恢复的能量值
   false,          // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(41, "../Resources/Objects/Base/SmallmouthBass.png", "SmallmouthBass", "小嘴鲈鱼", Fish,  // 小嘴鲈鱼
   100, // 最大存储量
   2,   // 解锁所需等级
   true, // 是否能出售
   180,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   45,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
),

GameBaseObject(42, "../Resources/Objects/Base/TunaFish.png", "TunaFish", "金枪鱼", Fish,  // 金枪鱼
   100, // 最大存储量
   3,   // 解锁所需等级
   true, // 是否能出售
   300,  // 出售价格
   false, // 是否可以购买
   INVAVID_NUM,    // 购买价格
   true, // 是否可以食用
   70,    // 食用恢复的能量值
   false, // 能否放置
   false, //能否合成
   {}    //合成物品的原料
)

   // GameBaseObject(30,"","None","无效物品",GameObjectSkillType::None,0,0,false,INVAVID_NUM,false,INVAVID_NUM,false,INVAVID_NUM,false,false,{})
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

    GameCommonObject(const GameBaseObject& baseObject) {

    }
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

// 商品信息定义
struct  ProductNode {
    GameCommonObject product;	// 商品信息
    int count;					// 商品数量
    int totalPrice;				// 商品价格
    Season discountSeason;      // 商品打折的季节
    Season increaseSeason;      // 商品涨价的季节
};


#endif // !_CONSTANT_H_
