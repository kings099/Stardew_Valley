#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "ObjectConstant.h"

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1920;                               // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 1080;                              // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                         // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = u8"��¶�� Stardew Valley";				// Ӧ�ó������


//��ɫ�����ó�����
constexpr float MOVE_SPEED = 3.5f;											// �ƶ��ٶ�
constexpr float MOVE_RATE = FRAME_RATE;										// �ƶ�֡��
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��
constexpr int INVAVID_NUM = -1;												// ��Ч����

// ��ɫ����
constexpr int CHARACTER_WIDTH = 32;											// ��ɫ���
constexpr int CHARACTER_HEIGHT = 32;										// ��ɫ�߶�
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// �ƶ��ٶ�

<<<<<<< Updated upstream
// ��ͼ����
constexpr float LERP_SPEED = 0.1f;											// �ӽǹ��ɵ�ƽ����
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// ��������ʱ��
constexpr float FARM_MAP_SCALE = 2.0f;										// ��ͼ���Ŵ�С


// ��Ʒ������
constexpr int OBJECT_LIST_ROWS = 3;											// ��Ʒ������
constexpr int OBJECT_LIST_COLS = 12;										// ��Ʒ������
=======
// 物品设置
constexpr int OBJECT_LIST_ROWS = 3;											// 物品列表行数
constexpr int OBJECT_LIST_COLS = 12;										// 物品列表列数

// UI 相关设置
constexpr int UI_SCALE = 190.0f;                                            // UI界面缩放
constexpr int FONT_SIZE = 20;                                               // 字体大小
constexpr int MAP_LAYER_GRADE = 0;                                          // 地图层级
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // 角色层级
constexpr int UI_LAYER_GRADE = 2;                                           // UI层级
constexpr int OBJECT_LAYER_GRADE = 3;                                       // 物品层级
constexpr float BUTTON_SIZE_RATIO = 2.0f;                                   // 按钮大小变化比例
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
>>>>>>> Stashed changes



// UI ��������
constexpr int UI_SCALE = 160.0f;                                            // UI???????
constexpr int FONT_SIZE = 24;                                               // �����С
constexpr int MAP_LAYER_GRADE = 0;                                          // ��ͼ�㼶
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // ��ɫ�㼶
constexpr int UI_LAYER_GRADE = 2;                                           // UI�㼶
constexpr int OBJECT_LAYER_GRADE = 3;                                       // ��Ʒ�㼶
constexpr float ENLARGEMENT_RATIO = 1.2f;									// ��ť�������ű���
constexpr float ENLARGEMENT_TIME = 0.15f;									// ��ť��������ʱ��
constexpr int CLOSE_OBJECT_LIST_START_X = 729;								// ��Ʒ��(�ر�״̬)��ʼλ�õ�X����
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// ��Ʒ��(�ر�״̬)��ʼλ�õ�Y����
constexpr int OPEN_OBJECT_LIST_START_X = 729;								// ��Ʒ��(����״̬)��ʼλ�õ�X����
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// ��Ʒ��(����״̬)��ʼλ�õ�Y����
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// ��Ʒ����Ʒ����ˮƽ���
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// ��Ʒ����Ʒ���Ӵ�ֱ���
constexpr float OBJECT_NODE_SCALE = 2.0f;									// ��Ʒ���ű���

constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// ��Ʒ��ɾ����ť��߽�
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// ��Ʒ��ɾ����ť�ұ߽�
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// ��Ʒ��ɾ����ť�ϱ߽�
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// ��Ʒ��ɾ����ť�±߽�


constexpr int SECONDS_IN_A_DAY = 86400;                                         // һ�������
constexpr float TIME_SCALE = 3600.0f;                                           // ��Ϸʱ�����ű�������ʵ1��=��Ϸ1����
constexpr int HOURS_IN_A_DAY = 24;                                              // һ��24Сʱ
constexpr int SECONDS_IN_A_HOUR = 3600;                                         // ÿСʱ60����
constexpr int SEASONS_CHANGE_PERIOD = 30;                                       // ÿ30��һ�����ڱ仯
constexpr int SECONDS_IN_A_MIN = 60;
#endif // !_CONSTANT_H_