/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Object.h
 * File Function: Object�Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/06
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OBJECT_CONSTANT_H_
#define _OBJECT_CONSTANT_H_

#include <string>
#include <vector>
#include <limits> 
#include "proj.win32/Constant.h"

 //��Ϸ��Ʒ��Ӧ�������Ͷ���
enum GameObjectSkillType {
    Farm,				// ����
    Collect,			// �ɼ�
    Mine,				// �ɿ�
    Fish				// ����
};

// ��Ϸ�������Ͷ���
enum GameTools {
    Hoe,				// ��ͷ
    Ax,					// ��ͷ
    Pickaxe,			// ����
    FishingRod,			// ���
    Kettle				// ˮ��
};

// ���ڶ���
enum Season {
    Spring,				// ����
    Summer,				// ����
    Fall,				// ����
    Winter,				// ����
    All					// ͨ��
};

// ��Ϸ��Ʒ���Ͷ���
enum GameObjectMapType {
    None,				// ����Ʒ
    Tool,				// ����
    Seed,				// ����
    Base,				// ������Ʒ
};

// ��ɫ��������
enum GameCharacterAction {
    NoneAction,			// �ն���
    Plowing,			// ����
    Watering,			// ��ˮ
    Cutting,			// ����
    Mining,				// �ɿ�
    Fishing,		    // ����
    Placement,			// ����
    Harvesting,			// �ջ�
    Buying,				// ����
    Selling,			// ����
};



// ��Ϸ��Ʒ�������Զ���
class GameObject {
public:
    std::string _fileName;       // ��ƷͼƬ��Դ�ļ�·��
    std::string _name;           // ��Ʒ����
    GameObjectSkillType _type;   // ��Ʒ����

    GameObject() = default;
    GameObject(const std::string& fileName, const std::string& name, GameObjectSkillType type) :
        _fileName(fileName),
        _name(name),
        _type(type) {
    }
    virtual ~GameObject() {}     // ������������
};

// ��Ϸ������Ʒ���Զ���
class GameToolObject : public GameObject {
public:
    int _level;                 // ���ߵȼ�
    int _actionCost;            // ִ��һ�β�����Ҫ�Ĵ���
    int _durability;            // �����;ö�
    GameCharacterAction _action; // ���ߵ�ǰִ�еĶ���

    // ���캯��
    GameToolObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, int actionCost, int durability, GameCharacterAction action):
        GameObject(fileName, name, type),
        _level(level),
        _actionCost(actionCost),
        _durability(durability),
        _action(action)
    {}
};

// ��Ϸ������Ʒ���Զ���
class GameSeedObject : public GameObject {
public:
    int _level;                                             // ������������ȼ�
    Season _season;                                         // ������������
    std::vector<int> _growthStages;                         // ����ÿ���׶��������������
    std::vector<std::string> _growthStagesFileNames;        // ����ÿ�������׶ε�ͼƬ��Դ�ļ�·��
    int _totalGrowTime;                                     // ��������������
    int _harvestIndex;                                      // �����ջ����õ���Ʒ����
    int _buyPrice;                                          // ���ӹ���۸�
    int _salePrice;                                         // ���ӳ��ۼ۸�

    // ���캯��
    GameSeedObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, Season season, std::vector<int> growthStages, int totalGrowTime, int harvestIndex, int buyPrice, int salePrice):
        GameObject(fileName, name, type),
        _level(level),
        _season(season),
        _growthStages(growthStages),
        _totalGrowTime(totalGrowTime),
        _harvestIndex(harvestIndex),
        _buyPrice(buyPrice),
        _salePrice(salePrice) 
    {}
};

// ��Ϸ������Ʒ���Զ���
class GameBaseObject : public GameObject {
public:
    int _maxStorage;                            // ��Ʒ���洢��
    int _level;                                 // ������Ʒ����ȼ�
    int _quality;                               // ��ƷƷ�ʵȼ�
    bool _sale;                                 // �Ƿ��ܳ���
    int _salePrice;                             // ���ۼ۸�
    bool _eat;                                  // �Ƿ����ʳ��
    int _eatEnergy;                             // ʳ�ûָ�������ֵ
    bool _place;                                // �ܷ����
    bool _synthesis;                            // �Ƿ���Ժϳ�
    std::map<std::string, int> _ingredients;	// �ϳ���Ʒ��ԭ��
    // ���캯��
    GameBaseObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place, bool synthesis, std::map<std::string, int> ingredients):
        GameObject(fileName, name, type),
        _maxStorage(maxStorage),
        _level(level),
        _quality(quality),
        _sale(sale),
        _salePrice(salePrice),
        _eat(eat),
        _eatEnergy(eatEnergy),
        _place(place) ,
        _synthesis(synthesis),
        _ingredients(ingredients)
    {}
};

// ��Ϸ��Ʒ���Զ���
struct GameCommonObject {
    GameObjectMapType type;                             // ��Ʒ����
    std::shared_ptr<GameObject> object;

    GameCommonObject() : type(None), object(nullptr) {} // Ĭ�Ϲ��캯��
    GameCommonObject(GameObjectMapType type, std::shared_ptr<GameObject> object) :
        type(type),
        object(object)
    {}
};
// ��Ʒ������Ʒ״̬����
enum ObjectListNodeStatus {
    Unselected,		// δѡ��
    Selected		// ѡ��
};

// ��ɫ��Ʒ��������Ʒ���Զ���
struct ObjectListNode {
    int index;                      // ��Ʒ����
    GameCommonObject objectNode;	// ��Ʒ��Ϣ
    int count;						// ��Ʒ����
    ObjectListNodeStatus status;	// ��Ʒ״̬(ѡ��/δѡ��)
};


// ��Ϸ��Ʒ���Բ�������
const std::vector<GameToolObject> GAME_TOOL_OBJECTS_ATTRS = {
    GameToolObject("../Resources/Objects/Tools/BeginnerHoe.png", "������ͷ", Farm, 1, 1, INT_MAX, Plowing),
    GameToolObject("../Resources/Objects/Tools/IntermediateHoe.png", "�м���ͷ", Farm, 2, 1, INT_MAX, Plowing),
    GameToolObject("../Resources/Objects/Tools/AdvancedHoe.png", "�߼���ͷ", Farm, 3, 1, INT_MAX, Plowing),
    GameToolObject("../Resources/Objects/Tools/BeginnerAxe.png", "������ͷ", Collect, 1, 5, INT_MAX, Cutting),
    GameToolObject("../Resources/Objects/Tools/IntermediateAxe.png", "�м���ͷ", Collect, 2, 4, INT_MAX, Cutting),
    GameToolObject("../Resources/Objects/Tools/AdvancedAxe.png", "�߼���ͷ", Collect, 3, 3, INT_MAX, Cutting),
    GameToolObject("../Resources/Objects/Tools/BeginnerPickaxe.png", "��������", Mine, 1, 5, INT_MAX, Mining),
    GameToolObject("../Resources/Objects/Tools/IntermediatePickaxe.png", "�м�����", Mine, 2, 4, INT_MAX, Mining),
    GameToolObject("../Resources/Objects/Tools/AdvancedPickaxe.png", "�߼�����", Mine, 3, 3, INT_MAX, Mining),
    GameToolObject("../Resources/Objects/Tools/BeginnerFishingRods.png", "�������", Fish, 1, 1, INT_MAX, Fishing),
    GameToolObject("../Resources/Objects/Tools/IntermediateFishingRods.png", "�м����", Fish, 2, 1, INT_MAX, Fishing),
    GameToolObject("../Resources/Objects/Tools/AdvancedFishingRods.png", "�߼����", Fish, 3, 1, INT_MAX, Fishing),
    GameToolObject("../Resources/Objects/Tools/", "����ˮ��", Farm, 1, 1, 40, Watering),
    GameToolObject("../Resources/Objects/Tools/", "�м�ˮ��", Farm, 2, 1, 55, Watering),
    GameToolObject("../Resources/Objects/Tools/", "�߼�ˮ��", Farm, 3, 1, 70, Watering)
};

//enum GameMapNodeType {
//    Grass,       // �ݵ�
//    Tree,        // ��ľ
//    Stone,       // ʯͷ
//    Water,       // ˮ
//    Soil,        // ����
//    Sand         // ɳ��
//    //.....
//};
//
//struct GameMapNode {
//    GameMapNodeType type;       // �ڵ�����
//    int x, y;                   // ����
//    int layer;                  // ����
//    bool isObstacle;            // �Ƿ��ϰ���
//    std::vector<GameCommonObject> dropObjects; // ������Ʒ
//    std::vector<int> dropObjectsNum;           // ������Ʒ����
//};

#endif // _CONSTANT_OBJECT_H_