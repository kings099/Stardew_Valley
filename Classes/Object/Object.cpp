/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Object.cpp
 * File Function: Object的实现
 * Author:        尹诚成
 * Update Date:   2023/12/06
 * License:       MIT License
 ****************************************************************/

#include "Object.h"    

// GameToolObject的构造函数
GameToolObject::GameToolObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, int actionCost, int durability) {
    this->_fileName = fileName;
    this->_name = name;
    this->_type = type;
    this->_level = level;
    this->_actionCost = actionCost;
    this->_durability = durability;
}

// GameSeedObject的构造函数
GameSeedObject::GameSeedObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int level, Season season, std::vector<int> growthStages, int totalGrowTime, int harvestIndex, int buyPrice, int salePrice) {
    this->_fileName = fileName;
    this->_name = name;
    this->_type = type;
    this->_level = level;
    this->_season = season;
    this->_growthStages = growthStages;
    this->_totalGrowTime = totalGrowTime;
    this->_harvestIndex = harvestIndex;
    this->_buyPrice = buyPrice;
    this->_salePrice = salePrice;

}

// GameBaseObject的构造函数
GameBaseObject::GameBaseObject(const std::string& fileName, const std::string& name, GameObjectSkillType type, int maxStorage, int level, int quality, bool sale, int salePrice, bool eat, int eatEnergy, bool place) {
    this->_fileName = fileName;
    this->_name = name;
    this->_type = type;
    this->_maxStorage = maxStorage;
    this->_level = level;
    this->_quality = quality;
    this->_sale = sale;
    this->_salePrice = salePrice;
    this->_eat = eat;
    this->_eatEnergy = eatEnergy;
    this->_place = place;
}