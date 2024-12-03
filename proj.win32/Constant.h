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
constexpr float MOVE_SPEED = 5.0f;											// �ƶ��ٶ�
constexpr float MOVE_RATE = FRAME_RATE;										// �ƶ�֡��
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_Q;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��

constexpr int UP = 1;														// ��������
constexpr int DOWN = 2;														// ��������
constexpr int LEFT = 3;														// ��������
constexpr int RIGHT = 4;													// ��������

#endif // !_CONSTANT_H_