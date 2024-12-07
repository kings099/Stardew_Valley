#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "../Classes/Object/Object.h"

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

// ��Ʒ����
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL1 = 12;								// ��������(�ȼ�1)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL2 = 24;								// ��������(�ȼ�2)
constexpr int MAX_OBJECT_LIST_SIZE_LEVEL3 = 36;								// ��������(�ȼ�3)
constexpr int MAX_STORAGE_NUM = 999;										// ������Ʒ�����洢����

constexpr int MAX_GROWTH_STAGE = 7;											// ���������׶��������



//// ��Ϸ������Ʒ���Զ���
//typedef struct {
//	std::string fileName;    // ����ͼƬ��Դ�ļ�·��
//	std::string name;        // ��������
//	GameObjectSkillType type;	 // ��������
//	int level;               // ���ߵȼ�
//	int actionCost;			 // ִ��һ�β�����Ҫ�Ĵ���
//	int durability;          // �����;ö�(���ˮ��)
//}GameToolObject;
//// ��Ϸ������Ʒ���Զ���
//// TODO:��Ӷ����ջ���
//typedef struct {
//	std::string fileName;						// ����ͼƬ��Դ�ļ�·��
//	std::string name;							// ��������
//	GameObjectSkillType type;						// ��������
//	int level;									// ������������ȼ�
//	Season season;								// ������������
//	int growthDays[MAX_GROWTH_STAGE];			// ����ÿ���׶��������������
//	int totalGrowTime;							// ��������������
//	int harvestIndex;							// �����ջ����õ���Ʒ����
//	int buyPrice;								// ���ӹ���۸�
//	int salePrice;								// ���ӳ��ۼ۸�
//}GameSeedObeject;
//
//// ��Ϸ������Ʒ���Զ���
//typedef struct {
//	std::string fileName;    // ��ƷͼƬ��Դ�ļ�·��
//	std::string name;        // ��Ʒ����
//	GameObjectSkillType type;	 // ��Ʒ����
//	int maxStorage;          // ��Ʒ���洢��
//	int level;               // ������Ʒ����ȼ�
//	int quality;             // ��ƷƷ�ʵȼ�
//	bool sale;               // �Ƿ��ܳ���
//	int salePrice;           // ���ۼ۸�
//	bool eat;                // �Ƿ����ʳ��
//	int eatEnegry;           // ʳ�ûָ�������ֵ
//	bool place;				 // �ܷ����
//}GameBaseObject;
//
//// ��Ϸ�ϳ���Ʒ���Զ���
//typedef struct {
//	GameBaseObject baseObject;					// ������Ʒ����
//	std::map<std::string, int> ingredients;		// �ϳ���Ʒ��ԭ��
//}GameComposeObject;
//
//// ��Ϸͨ����Ʒ���Զ���
//typedef struct {
//GameObjectMapType type;							// ��Ʒ����
//	void* object;									// ��Ʒ����
//}GameCommonObject;
//
//
//// ��Ϸ������Ʒ���Բ�������
//const std::map<int, GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
//	{1,{"","������ͷ",Farm,1,1,INT_MAX}},				// ��ͷ(һ��)
//	{2,{"","�м���ͷ",Farm,2,1,INT_MAX}},				// ��ͷ(����)
//	{3,{"","�߼���ͷ",Farm,3,1,INT_MAX}},				// ��ͷ(����)
//	{4,{"","������ͷ",Collect,1,8,INT_MAX}},				// ��ͷ(һ��)
//	{5,{"","�м���ͷ",Collect,2,7,INT_MAX}},				// ��ͷ(����)
//	{6,{"","�߼���ͷ",Collect,3,6,INT_MAX}},				// ��ͷ(����)
//	{7,{"","��������",Mine,1,10,INT_MAX}},				// ����(һ��)
//	{8,{"","�м�����",Mine,2,9,INT_MAX}},				// ����(����)
//	{9,{"","�߼�����",Mine,3,8,INT_MAX}},				// ����(����)
//	{10,{"","�������",Fish,1,1,INT_MAX}},				// ���(һ��)
//	{11,{"","�м����",Fish,2,1,INT_MAX}},				// ���(����)
//	{12,{"","�߼����",Fish,3,1,INT_MAX}},				// ���(����)
//	{13,{"","����ˮ��",Farm,1,1,40}},					// ˮ��(һ��)
//	{14,{"","�м�ˮ��",Farm,2,1,55}},					// ˮ��(����)
//	{15,{"","�߼�ˮ��",Farm,3,1,70}},					// ˮ��(����)
//};
//
//// ��Ϸ������Ʒ���Բ�������
//const std::map<int, GameSeedObeject> GAME_SEED_OBJECTS_ATTRS = {
//
//};
//
//// ��Ϸ������Ʒ���Բ�������
//const std::map<int, GameBaseObject> GAME_BASE_OBJECTS_ATTRS = {
//
//};
//
//// ��Ϸ���ӳ�����Ӧ����ƥ��
//const std::map<GameSeedObeject, GameBaseObject> SEED_TO_CROP_TYPE = {
//
//};
//
//// ��Ϸ�ϳ���Ʒ���Բ�������
//const std::map<int, GameComposeObject> GAME_COMPOSE_OBJECTS_ATTRS = {
//
//};


#endif // !_CONSTANT_H_