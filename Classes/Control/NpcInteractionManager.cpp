
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcInteractionManager.cpp
 * File Function: 该文件实现了 NPC 互动管理器（NpcInteractionManager）的功能。
                  NpcInteractionManager 类用于处理玩家与 NPC 之间的互动，
                  例如送礼和显示对话，采用单例模式。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#include "NpcInteractionManager.h"

// 初始化静态成员
NpcInteractionManager* NpcInteractionManager::instance = nullptr;

NpcInteractionManager* NpcInteractionManager::getInstance() {
    if (!instance) {
        instance = new NpcInteractionManager();  // 如果实例不存在，则创建
    }
    return instance;
}

NpcInteractionManager::NpcInteractionManager() {
    // 这里可以保持为空，NpcManager 和 GiftItemManager 已经是单例，不需要重复初始化
}

void NpcInteractionManager::giveGiftToNPC(const std::string& npcName, const std::string& giftName) {
    // 直接通过单例获取 NpcManager 和 GiftItemManager
    NPC* npc = NpcManager::getInstance()->getNPCByName(npcName);
    GiftItem* gift = GiftItemManager::getInstance()->getGiftByName(giftName);

    if (npc && gift) {
        npc->giftItem(gift);  // 给 NPC 送礼物
    }
}

void NpcInteractionManager::showDialog(const std::string& npcName) {
    // 直接通过单例获取 NpcManager
    NPC* npc = NpcManager::getInstance()->getNPCByName(npcName);
    if (npc) {
        NpcManager::getInstance()->showDialog(npc);  // 显示 NPC 对话
    }
}
