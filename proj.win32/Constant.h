#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include "cocos2d.h"
#include <string>

// Ӧ�ó�������
constexpr int DESIGN_RESOLUTION_WIDTH = 1024;                               // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 768;                               // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 480;                                 // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 320;                                // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1024;                               // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 768;                               // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 2048;                                // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1536;                               // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                         // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = u8"��¶�� Stardew Valley";				// Ӧ�ó������

//�����ó�����
constexpr float MOVE_SPEED = 3.5f;											// �ƶ��ٶ�d
constexpr float MOVE_RATE = FRAME_RATE;										// �ƶ�֡��
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_Q;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��

constexpr int UP = 1;														// ��������
constexpr int DOWN = 2;														// ��������
constexpr int LEFT = 3;														// ��������
constexpr int RIGHT = 4;													// ��������

constexpr float MAP_SCALE = 1.6f;											// ��ͼ���Ŵ�С

const int SECONDS_IN_A_DAY = 86400;                                         // һ�������
const float TIME_SCALE = 3600.0f;                                             // ��Ϸʱ�����ű�������ʵ1��=��Ϸ1����
const int HOURS_IN_A_DAY = 24;                                              // һ��24Сʱ
const int SECONDS_IN_A_HOUR = 3600;                                           // ÿСʱ60����
const int SEASONS_CHANGE_PERIOD = 30;                                       // ÿ30��һ�����ڱ仯
const int SECONDS_IN_A_MIN =60;
#endif // !_CONSTANT_H_