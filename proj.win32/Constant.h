#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "Classes/Object/Object.h"

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

constexpr float ENLARGEMENT_RATIO = 1.2f;									// ��ť�Ŵ����
constexpr float ENLARGEMENT_TIME = 0.1f;									// ��ť�Ŵ�ʱ��

//�����ó�����
constexpr float MOVE_SPEED = 3.5f;											// �ƶ��ٶ�
constexpr float MOVE_RATE = FRAME_RATE;										// �ƶ�֡��
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��
constexpr int INVAVID_NUM = -1;												// ��Ч����


// ��ɫ����
constexpr int CHARACTER_WIDTH = 32;											// ��ɫ���
constexpr int CHARACTER_HEIGHT = 32;										// ��ɫ�߶�
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// �ƶ��ٶ�

// ��ͼ����
constexpr float LERP_SPEED = 0.1f;											// �ӽǹ��ɵ�ƽ����
constexpr float MAP_SCALE = 1.6f;											// ��ͼ���Ŵ�С
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// //��������ʱ��

// ��Ʒ����
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// ��������(�ȼ�1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// ��������(�ȼ�2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// ��������(�ȼ�3)
constexpr int MAX_STORAGE_NUM = 999;										// ������Ʒ�����洢����

// ��Ʒ������
constexpr int OBJECT_LIST_ROWS = 3;											// ��Ʒ������
constexpr int OBJECT_LIST_COLS = 12;										// ��Ʒ������



#endif // !_CONSTANT_H_