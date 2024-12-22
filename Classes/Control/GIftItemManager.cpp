
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GiftItemManager.cpp
 * File Function: 该文件实现了礼物物品管理器（GiftItemManager）的功能。
                  GiftItemManager 类用于管理游戏中的礼物物品，
                  并根据不同的 NPC 角色对礼物的喜好进行初始化和查询。
                  它采用单例模式，确保只有一个礼物管理器实例存在。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#include "GiftItemManager.h"



GiftItemManager* GiftItemManager::getInstance() {
    static GiftItemManager instance;  // 静态局部变量，确保只创建一个实例
    return &instance;  // 返回实例的指针
}

GiftItemManager::GiftItemManager() {
    // 初始化礼物数据（例如可以在这里调用 initializeGifts() 方法）
    initializeGifts();
}

void GiftItemManager::initializeGifts() {
    GiftItem rose("Ring", 10);               //NPC对Ring反应的默认值
    rose.setAffectionForNPC("Abigail", 20);  // Abigail 对 Ring 的反应更大
    rose.setAffectionForNPC("Mary", 5);      // Mary 对 Rose 的反应较小

    GiftItem chocolate("Timber", 5);
    chocolate.setAffectionForNPC("Abigail", 15);  
    chocolate.setAffectionForNPC("Mary", 10); 

    GiftItem teddyBear("Teddy Bear", 15);
    teddyBear.setAffectionForNPC("Abigail", 30);  // John 很喜欢泰迪熊
    teddyBear.setAffectionForNPC("Mary", 10);  // Mary 对泰迪熊不感兴趣

    _gifts.push_back(rose);
    _gifts.push_back(chocolate);
    _gifts.push_back(teddyBear);
}

GiftItem* GiftItemManager::getGiftByName(const std::string& name) {
    // 根据名称查找礼物
    for (auto& gift : _gifts) {
        if (gift._name == name) {
            return &gift;
        }
    }
    return nullptr;  // 如果没有找到，返回 nullptr
}