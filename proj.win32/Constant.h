#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "ObjectConstant.h"

// 应用程序设置
constexpr int DESIGN_RESOLUTION_WIDTH = 1920;                               // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 1080;                              // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // 大分辨率高度
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
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// 场景过渡时间
constexpr float FARM_MAP_SCALE = 2.0f;										// 地图缩放大小

// 物品设置
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// 背包容量(等级1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// 背包容量(等级2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// 背包容量(等级3)
constexpr int MAX_STORAGE_NUM = 999;										// 单个物品的最大存储数量

// 物品栏设置
constexpr int OBJECT_LIST_ROWS = 3;											// 物品栏行数
constexpr int OBJECT_LIST_COLS = 12;										// 物品栏列数
constexpr int CLOSE_OBJECT_LIST_START_X = 795;								// 关闭状态的物品栏起始X坐标位置
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// 关闭状态的物品栏起始Y坐标位置
constexpr int OPEN_OBJECT_LIST_START_X = 795;								// 打开状态的物品栏起始X坐标位置
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// 打开状态的物品栏起始Y坐标位置
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;								// 物品栏节点水平间隔
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// 物品栏节点垂直间隔


// UI 界面设置
constexpr int UI_SCALE = 160.0f;                                            // UI缩放比例
constexpr int FONT_SIZE = 24;                                               // 字体大小
constexpr int MAP_LAYER_GRADE = 0;                                          // 地图层级
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // 角色层级
constexpr int UI_LAYER_GRADE = 2;                                           // UI层级
constexpr int OBJECT_LAYER_GRADE = 3;                                       // 物品层级
constexpr float BUTTON_SIZE_RATIO = 2.0f;                                   // 按钮大小变化比例
constexpr float ENLARGEMENT_RATIO = 1.2f;									// 鼠标悬停时按钮放大比例
constexpr float ENLARGEMENT_TIME = 0.1f;									// 鼠标悬停时按钮放大时间

constexpr int UI_SCALE = 160.0f;                                             //UI锟斤拷锟斤拷锟酵硷拷锟斤拷锟斤拷疟锟斤拷锟?
constexpr int FONT_SIZE = 24;                                                //


// 游戏内时间设置
constexpr int SECONDS_IN_A_DAY = 86400;                                     // 一天的秒数
constexpr float TIME_SCALE = 3600.0f;                                       // 游戏时间缩放比例，现实1秒=游戏1分钟
constexpr int HOURS_IN_A_DAY = 24;                                          // 一天24小时
constexpr int SECONDS_IN_A_HOUR = 3600;                                     // 每小时60分钟
constexpr int SEASONS_CHANGE_PERIOD = 30;                                   // 每30天一个季节变化
constexpr int SECONDS_IN_A_MIN =60;
#endif // !_CONSTANT_H_