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
constexpr float MOVE_SPEED = 5.0f;											// 移动速度
constexpr float MOVE_RATE = FRAME_RATE;										// 移动帧率
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_Q;		// 无效按键
constexpr float ACTION_RATE = 5.0f;											// 动作间隔帧率

constexpr int UP = 1;														// 方向向上
constexpr int DOWN = 2;														// 方向向下
constexpr int LEFT = 3;														// 方向向左
constexpr int RIGHT = 4;													// 方向向右

#endif // !_CONSTANT_H_