/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Object.h
 * File Function: Object�Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/06
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <vector>
#include "../proj.win32/Constant.h"


 //��Ϸ��Ʒ��Ӧ�������Ͷ���
typedef enum {
    Farm,				// ����
    Collect,			// �ɼ�
    Mine,				// �ɿ�
    Fish				// ����
}GameObjectSkillType;

// ��Ϸ�������Ͷ���
typedef enum {
    Hoe,				// ��ͷ
    Ax,					// ��ͷ
    Pickaxe,			// ����
    FishingRod,			// ���
    Kettle				// ˮ��
}GameTools;

// ���ڶ���
typedef enum {
    Spring,				// ����
    Summer,				// ����
    Fall,				// ����
    Winter,				// ����
    All					// ͨ��
}Season;

// ��Ϸ��Ʒ���Ͷ���
typedef enum {
    None,				// ����Ʒ
    Tool,				// ����
    Seed,				// ����
    Base,				// ������Ʒ
    Compose				// �ϳ���Ʒ
}GameObjectMapType;

// ��Ϸ��Ʒ�������Զ���
class GameObject {
public:
    std::string _fileName;       // ��ƷͼƬ��Դ�ļ�·��
    std::string _name;           // ��Ʒ����
    GameObjectSkillType _type;   // ��Ʒ����

    virtual ~GameObject() {}     // ������������
};

// ��Ϸ������Ʒ���Զ���
class GameToolObject : public GameObject {
public:
    int _level;                 // ���ߵȼ�
    int _actionCost;            // ִ��һ�β�����Ҫ�Ĵ���
    int _durability;            // �����;ö�

    // ���캯��
    GameToolObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, int actionCost, int durability);
};

// ��Ϸ������Ʒ���Զ���
class GameSeedObject : public GameObject {
public:
    int _level;                             // ������������ȼ�
    Season _season;                         // ������������
    std::vector<int> _growthStages;         // ����ÿ���׶��������������
    int _totalGrowTime;                     // ��������������
    int _harvestIndex;                      // �����ջ����õ���Ʒ����
    int _buyPrice;                          // ���ӹ���۸�
    int _salePrice;                         // ���ӳ��ۼ۸�

    // ���캯��
    GameSeedObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, Season season, std::vector<int> growthStages, int totalGrowTime, int harvestIndex, int buyPrice, int salePrice);
};

// ��Ϸ������Ʒ���Զ���
class GameBaseObject : public GameObject {
public:
    int _maxStorage;          // ��Ʒ���洢��
    int _level;               // ������Ʒ����ȼ�
    int _quality;             // ��ƷƷ�ʵȼ�
    bool _sale;               // �Ƿ��ܳ���
    int _salePrice;           // ���ۼ۸�
    bool _eat;                // �Ƿ����ʳ��
    int _eatEnergy;           // ʳ�ûָ�������ֵ
    bool _place;              // �ܷ����

    // ���캯��
    GameBaseObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place);
};

// ��Ϸ�ϳ���Ʒ���Զ���
class GameComposeObject : public GameObject {
public:
    GameBaseObject _baseObject;					    // ������Ʒ����
    std::map<std::string, int> _ingredients;		// �ϳ���Ʒ��ԭ��

    GameComposeObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place, const std::map<std::string, int>& ingredients) :
        _baseObject(fileName, name, type, maxStorage, level, quality, sale, salePrice, eat, eatEnergy, place),
        _ingredients(ingredients) {
    }
};

// ��Ϸ��Ʒ���Զ���
struct GameCommonObject {
    GameObjectMapType type;                             // ��Ʒ����
    std::shared_ptr<GameObject> object;

    GameCommonObject() : type(None), object(nullptr) {} // Ĭ�Ϲ��캯��
    GameCommonObject(GameObjectMapType type, std::shared_ptr<GameObject> object) :
        type(type),
        object(object) {
    }
};


#endif // _CONSTANT_OBJECT_H_