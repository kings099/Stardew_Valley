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
<<<<<<< Updated upstream
constexpr float MOVE_SPEED = 3.5f;											// �ƶ��ٶ�d
constexpr float MOVE_RATE = FRAME_RATE;										// �ƶ�֡��
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��

<<<<<<< Updated upstream
constexpr int STAY = 0;														// ��ֹ
constexpr int UP = 1;														// ��������
constexpr int DOWN = 2;														// ��������
constexpr int LEFT = 3;														// ��������
constexpr int RIGHT = 4;													// ��������
=======
=======

constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// ��Ч����
constexpr float ACTION_RATE = 5.0f;											// �������֡��

// ��ɫ����
constexpr int CHARACTER_WIDTH = 32;											// ��ɫ���
constexpr int CHARACTER_HEIGHT = 32;										// ��ɫ�߶�
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// �ƶ��ٶ�

// ��ͼ����
constexpr float LERP_SPEED = 0.1f;											// �ӽǹ��ɵ�ƽ����
>>>>>>> Stashed changes
constexpr float MAP_SCALE = 1.6f;											// ��ͼ���Ŵ�С
>>>>>>> Stashed changes

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// ���������ȼ�1
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// ���������ȼ�2
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// ���������ȼ�3

<<<<<<< Updated upstream
=======
constexpr int MAX_STORAGE_NUM = 999;										// ������Ʒ�����洢����

>>>>>>> Stashed changes
//��Ϸ��Ʒ���Ͷ���
typedef enum {
	Farm,				// ����
	Collect,			// �ɼ�
	Mine,				// �ɿ�
	Fish				// ����
}GameObjectType;

// ��Ϸ�������Ͷ���
typedef enum {
	Hoe,				// ��ͷ
	Ax,					// ��ͷ
	Pickaxe,			// ����
	FishingRod,			// ���
	Kettle				// ˮ��
}GameTools;

// ��Ϸ������Ʒ���Զ���
typedef struct {
	std::string fileName;    // �ļ�·��
	std::string name;        // ��������
	GameObjectType type;	 // ��������
	int level;               // ���ߵȼ�
	int durability;          // �����;ö�(���ˮ��)
}GameToolObject;

// ��Ϸ������Ʒ���Զ���
typedef struct {
	std::string fileName;    // �ļ�·��
	std::string name;        // ��Ʒ����
	GameObjectType type;	 // ��Ʒ����
<<<<<<< Updated upstream
=======
	int maxStorage;          // ��Ʒ���洢��
>>>>>>> Stashed changes
	int level;               // ��Ʒ�ȼ�
	bool sale;               // �Ƿ��ܳ���
	int salePrice;           // ���ۼ۸�
	bool eat;                // �Ƿ����ʳ��
	int eatEnegry;           // ʳ�ûָ�������ֵ
}GameBaseObject;

// ��Ϸ�ϳ���Ʒ���Զ���
typedef struct {
	GameBaseObject baseObject;					// ������Ʒ����
	std::map<std::string,int> ingredients;		// �ϳ���Ʒ��ԭ��
}GameComposeObject;

// ��Ϸ��Ʒ���Ͷ���
typedef enum {
<<<<<<< Updated upstream
	None,				// ��Ч��Ʒ
=======
	None,				// ����Ʒ
>>>>>>> Stashed changes
	Tool,				// ����
	Base,				// ������Ʒ
	Compose				// �ϳ���Ʒ
}GameObjectMapType;

// ��Ϸͨ����Ʒ���Զ���
typedef struct {
	GameObjectMapType type;							// ��Ʒ����
	void* object;									// ��Ʒ����
}GameCommonObject;

// ��Ϸ������Ʒ���Բ�������
const std::map<int, GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
	{1,{"","��ͷ",Farm,1,INT_MAX}},					// ��ͷ
	{2,{"","��ͷ",Collect,1,INT_MAX}},				// ��ͷ
	{3,{"","����",Mine,1,INT_MAX}},					// ����
	{4,{"","���",Fish,1,INT_MAX}},					// ���
	{5,{"","ˮ��",Farm,1,40}},						// ˮ��(һ��)
	{6,{"","ˮ��",Farm,2,55}},						// ˮ��(����)
	{7,{"","ˮ��",Farm,3,70}},						// ˮ��(����)
};

// ��Ϸ������Ʒ���Բ�������
const std::map<int, GameBaseObject> GAME_BASE_OBJECTS_ATTRS = {

};

// ��Ϸ�ϳ���Ʒ���Բ�������
const std::map<int, GameComposeObject> GAME_COMPOSE_OBJECTS_ATTRS = {

};
#endif // !_CONSTANT_H_