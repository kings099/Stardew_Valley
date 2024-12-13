#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "ObjectConstant.h"

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
const std::string APPLICATION_TITLE = u8"模拟游戏 Stardew Valley";         // 游戏应用标题

// 移动相关设置
constexpr float MOVE_SPEED = 3.5f;											// 移动速度
constexpr float MOVE_RATE = FRAME_RATE;										// 移动帧率
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效键值
constexpr float ACTION_RATE = 5.0f;											// 动作帧率
constexpr int INVAVID_NUM = -1;												// 无效编号

// 角色相关设置
constexpr int CHARACTER_WIDTH = 64;											// 角色宽度
constexpr int CHARACTER_HEIGHT = 64;										// 角色高度
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// 角色移动速度

// 场景过渡相关
constexpr float LERP_SPEED = 0.1f;											// 插值平滑速度
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// 场景切换时间
constexpr float FARM_MAP_SCALE = 2.0f;										// 农场地图缩放比例
constexpr float INDOOR_MAP_SCALE = 5.0f;									// 室内地图缩放比例

// 物品设置
constexpr int OBJECT_LIST_ROWS = 3;											// 物品列表行数
constexpr int OBJECT_LIST_COLS = 12;										// 物品列表列数
constexpr int CLOSE_OBJECT_LIST_START_X = 795;								// 关闭状态物品列表起始X坐标
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// 关闭状态物品列表起始Y坐标
constexpr int OPEN_OBJECT_LIST_START_X = 795;								// 打开状态物品列表起始X坐标
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// 打开状态物品列表起始Y坐标
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// 物品节点水平间隔
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// 物品节点垂直间隔

// 背包容量设置
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// 背包容量(等级1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// 背包容量(等级2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// 背包容量(等级3)

// UI 相关设置
constexpr int UI_SCALE = 210.0f;                                            // UI界面缩放
constexpr int FONT_SIZE = 20;                                               // 字体大小
constexpr int MAP_LAYER_GRADE = 0;                                          // 地图层级
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // 角色层级
constexpr int UI_LAYER_GRADE = 2;                                           // UI层级
constexpr int OBJECT_LAYER_GRADE = 3;                                       // 物品层级
constexpr float BUTTON_SIZE_RATIO = 2.0f;                                   // 按钮大小变化比例
constexpr float ENLARGEMENT_RATIO = 1.2f;									// 按钮悬浮时放大比例
constexpr float ENLARGEMENT_TIME = 0.1f;									// 按钮悬浮时放大持续时间

// 游戏时间设置
constexpr int SECONDS_IN_A_DAY = 86400;                                     // 一天的秒数
constexpr float TIME_SCALE = 3600.0f;                                       // 游戏时间与实际时间的比例，1秒 = 游戏1小时
constexpr int HOURS_IN_A_DAY = 24;                                          // 一天24小时
constexpr int SECONDS_IN_A_HOUR = 3600;                                     // 一小时60分钟
constexpr int SEASONS_CHANGE_PERIOD = 30;                                   // 每30天切换一个季节
constexpr int SECONDS_IN_A_MIN = 60;                                        // 每分钟60秒
constexpr int DAYS_IN_A_SEASON = 7;                                         // 每季7天
constexpr int DAYS_IN_A_YEAR = 28;                                          // 一年28天

#endif // !_CONSTANT_H_
