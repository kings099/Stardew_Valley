/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TownMap.cpp
 * File Function: 小镇地图TownMap类的实现
 * Author:        金恒宇
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/
#include "TownMap.h"
USING_NS_CC;

TownMap::TownMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}

TownMap::~TownMap() {}

TownMap* TownMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    TownMap* ret = new TownMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool TownMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // 调用父类的初始化函数
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    _map_position = mapPosition;
    _mapName = mapFile;
    this->setScale(TOWN_MAP_SCALE);

    // 添加小镇地图初始化时需要创建的精灵
     // 初始化 NPC 和管理器

    NpcManager::getInstance()->initializeNPCs();  // 初始化 NPC
    CCLOG("NPC initialization completed.");
    // 获取 Abigail NPC
    NPC* abigail = NpcManager::getInstance()->getNPCByName("Abigail");
    // 初始化单例对象
   
    GiftItemManager::getInstance();  // 初始化礼物物品管理器




    // 如果 Abigail 存在，则将其添加到场景中
    if (abigail) {
        this->addChild(abigail, 4);  // 将整个 NPC 对象添加到场景中
        abigail->startWalkingAnimation();  // 启动动画
        CCLOG("Abigail added to scene.");
    }
    else {
        CCLOG("Abigail NPC not found!");  // 如果没有找到 Abigail NPC，则打印错误日志
    }
    CCLOG("NPC initialization completed.");
  
    return true;
}

Node* TownMap::getNodeAtPosition(const Vec2& tilePos) {

    // 添加小镇地图特有节点逻辑 （暂无）
    return nullptr; // 默认返回 nullpt
}