#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "ObjectConstant.h"

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1920;                               // ��Ʒֱ��ʿ���
constexpr int DESIGN_RESOLUTION_HEIGHT = 1080;                              // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // С�ֱ��ʿ���
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // �зֱ��ʿ���
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // ��ֱ��ʿ���
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                         // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = u8"��¶�� Stardew Valley";				// Ӧ�ó������



//�����ó�����
constexpr float MOVE_SPEED = 3.5f;											// �ƶ��ٶ�
constexpr float MOVE_RATE = FRAME_RATE;										// �ƶ�֡��
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��
constexpr int INVAVID_NUM = -1;												// ��Ч����

// ��ɫ����
constexpr int CHARACTER_WIDTH = 32;											// ��ɫ����
constexpr int CHARACTER_HEIGHT = 32;										// ��ɫ�߶�
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// �ƶ��ٶ�

// ��ͼ����
constexpr float LERP_SPEED = 0.1f;											// �ӽǹ��ɵ�ƽ����
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// ��������ʱ��
constexpr float FARM_MAP_SCALE = 2.0f;										// ��ͼ���Ŵ�С

// ��Ʒ����
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// ��������(�ȼ�1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// ��������(�ȼ�2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// ��������(�ȼ�3)
constexpr int MAX_STORAGE_NUM = 999;										// ������Ʒ�����洢����


// ��Ʒ������
constexpr int OBJECT_LIST_ROWS = 3;											// ��Ʒ������
constexpr int OBJECT_LIST_COLS = 12;										// ��Ʒ������
constexpr int CLOSE_OBJECT_LIST_START_X = 795;								// �ر�״̬����Ʒ����ʼX����λ��
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// �ر�״̬����Ʒ����ʼY����λ��
constexpr int OPEN_OBJECT_LIST_START_X = 795;								// ��״̬����Ʒ����ʼX����λ��
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// ��״̬����Ʒ����ʼY����λ��
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;								// ��Ʒ���ڵ�ˮƽ���
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// ��Ʒ���ڵ㴹ֱ���

// 物品设置
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// 背包容量(等级1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// 背包容量(等级2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// 背包容量(等级3)
constexpr int MAX_STORAGE_NUM = 999;										// 单个物品的最大存储数量



// UI ��������
constexpr int UI_SCALE = 160.0f;                                            // UI���ű���
constexpr int FONT_SIZE = 24;                                               // �����С
constexpr int MAP_LAYER_GRADE = 0;                                          // ��ͼ�㼶
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // ��ɫ�㼶
constexpr int UI_LAYER_GRADE = 2;                                           // UI�㼶
constexpr int OBJECT_LAYER_GRADE = 3;                                       // ��Ʒ�㼶
constexpr float BUTTON_SIZE_RATIO = 2.0f;                                   // ��ť��С�仯����
constexpr float ENLARGEMENT_RATIO = 1.2f;									// �����ͣʱ��ť�Ŵ����
constexpr float ENLARGEMENT_TIME = 0.1f;									// �����ͣʱ��ť�Ŵ�ʱ��

constexpr int UI_SCALE = 160.0f;                                             //UI�����ͼ�����ű���?
constexpr int FONT_SIZE = 24;                                                //


// ��Ϸ��ʱ������
constexpr int SECONDS_IN_A_DAY = 86400;                                     // һ�������
constexpr float TIME_SCALE = 3600.0f;                                       // ��Ϸʱ�����ű�������ʵ1��=��Ϸ1����
constexpr int HOURS_IN_A_DAY = 24;                                          // һ��24Сʱ
constexpr int SECONDS_IN_A_HOUR = 3600;                                     // ÿСʱ60����
constexpr int SEASONS_CHANGE_PERIOD = 30;                                   // ÿ30��һ�����ڱ仯
constexpr int SECONDS_IN_A_MIN =60;
#endif // !_CONSTANT_H_