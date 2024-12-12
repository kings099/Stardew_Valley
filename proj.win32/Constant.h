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


//角色测试用常变量
constexpr float MOVE_SPEED = 3.5f;											// 移动速度
constexpr float MOVE_RATE = FRAME_RATE;										// 移动帧率
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// 无效按键
constexpr float ACTION_RATE = 5.0f;											// 动作间隔帧率
constexpr int INVAVID_NUM = -1;												// 无效数字

// 角色属性
constexpr int CHARACTER_WIDTH = 32;											// 角色宽度
constexpr int CHARACTER_HEIGHT = 32;										// 角色高度
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// 移动速度

<<<<<<< Updated upstream
// 地图设置
constexpr float LERP_SPEED = 0.1f;											// 视角过渡的平滑度
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// 场景过渡时间
constexpr float FARM_MAP_SCALE = 2.0f;										// 地图缩放大小


// 物品栏设置
constexpr int OBJECT_LIST_ROWS = 3;											// 物品栏行数
constexpr int OBJECT_LIST_COLS = 12;										// 物品栏列数
=======
// 鐗╁搧璁剧疆
constexpr int OBJECT_LIST_ROWS = 3;											// 鐗╁搧鍒楄〃琛屾暟
constexpr int OBJECT_LIST_COLS = 12;										// 鐗╁搧鍒楄〃鍒楁暟

// UI 鐩稿叧璁剧疆
constexpr int UI_SCALE = 190.0f;                                            // UI鐣岄潰缂╂斁
constexpr int FONT_SIZE = 20;                                               // 瀛椾綋澶у皬
constexpr int MAP_LAYER_GRADE = 0;                                          // 鍦板浘灞傜骇
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // 瑙掕壊灞傜骇
constexpr int UI_LAYER_GRADE = 2;                                           // UI灞傜骇
constexpr int OBJECT_LAYER_GRADE = 3;                                       // 鐗╁搧灞傜骇
constexpr float BUTTON_SIZE_RATIO = 2.0f;                                   // 鎸夐挳澶у皬鍙樺寲姣斾緥
constexpr float ENLARGEMENT_RATIO = 1.2f;									// 鎸夐挳鍔ㄧ敾缂╂斁姣斾緥
constexpr float ENLARGEMENT_TIME = 0.15f;									// 鎸夐挳鍔ㄧ敾缂╂斁鏃堕棿
constexpr int CLOSE_OBJECT_LIST_START_X = 729;								// 鐗╁搧鏍�(鍏抽棴鐘舵��)璧峰浣嶇疆鐨刋鍧愭爣
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// 鐗╁搧鏍�(鍏抽棴鐘舵��)璧峰浣嶇疆鐨刌鍧愭爣
constexpr int OPEN_OBJECT_LIST_START_X = 729;								// 鐗╁搧鏍�(寮�鍚姸鎬�)璧峰浣嶇疆鐨刋鍧愭爣
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// 鐗╁搧鏍�(寮�鍚姸鎬�)璧峰浣嶇疆鐨刌鍧愭爣
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// 鐗╁搧鏍忕墿鍝佹牸瀛愭按骞抽棿璺�
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// 鐗╁搧鏍忕墿鍝佹牸瀛愬瀭鐩撮棿璺�
constexpr float OBJECT_NODE_SCALE = 2.0f;									// 鐗╁搧缂╂斁姣斾緥
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// 鐗╁搧鏍忓垹闄ゆ寜閽乏杈圭晫
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// 鐗╁搧鏍忓垹闄ゆ寜閽彸杈圭晫
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// 鐗╁搧鏍忓垹闄ゆ寜閽笂杈圭晫
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// 鐗╁搧鏍忓垹闄ゆ寜閽笅杈圭晫
>>>>>>> Stashed changes



// UI 界面设置
constexpr int UI_SCALE = 160.0f;                                            // UI???????
constexpr int FONT_SIZE = 24;                                               // 字体大小
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
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// 物品栏物品格子水平间距
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// 物品栏物品格子垂直间距
constexpr float OBJECT_NODE_SCALE = 2.0f;									// 物品缩放比例

constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// 物品栏删除按钮左边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// 物品栏删除按钮右边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// 物品栏删除按钮上边界
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// 物品栏删除按钮下边界


constexpr int SECONDS_IN_A_DAY = 86400;                                         // 一天的秒数
constexpr float TIME_SCALE = 3600.0f;                                           // 游戏时间缩放比例，现实1秒=游戏1分钟
constexpr int HOURS_IN_A_DAY = 24;                                              // 一天24小时
constexpr int SECONDS_IN_A_HOUR = 3600;                                         // 每小时60分钟
constexpr int SEASONS_CHANGE_PERIOD = 30;                                       // 每30天一个季节变化
constexpr int SECONDS_IN_A_MIN = 60;
#endif // !_CONSTANT_H_