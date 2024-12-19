
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcManager.cpp
 * File Function: 负责管理游戏中的 NPC 实例NpcManager类的实现
                  包括 NPC 的初始化、查询、对话等功能。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#include "NpcManager.h"

// 初始化静态成员
NpcManager* NpcManager::instance = nullptr;

// 构造函数
NpcManager::NpcManager() {
    // 可以在此进行初始化
    // 例如：initializeNPCs();
}

// 析构函数
NpcManager::~NpcManager() {
    // 清理 NPC 列表
    for (auto npc : npcs) {
        delete npc;
    }
    npcs.clear();
}

// 获取单例实例
NpcManager* NpcManager::getInstance() {
    if (!instance) {
        instance = new NpcManager();  // 如果实例不存在，则创建
    }
    return instance;
}

// 初始化 NPC
void NpcManager::initializeNPCs() {
    // 初始化 NPC 实例，并添加到 npcs 列表
    NPC* npc1 = new NPC("Abigail", cocos2d::Vec2(100, 200), "../Resources/Characters/NPC/Abigail_1.png", { "../Resources/Characters/NPC/Abigail_1.png", "../Resources/Characters/NPC/Abigail_2.png" ,"../Resources/Characters/NPC/Abigail_3.png","../Resources/Characters/NPC/Abigail_4.png" });
    npc1->dialogues = {
        "Hello, traveler!",
        "I feel like you care about me.",
        "Thank you for the gift!"
    };
    // 添加任务给 Abigail（现在奖励是好感度）
    Task* task1 = new Task("Give me a rare item from the mine.", 1, 1, 10); // 10 好感度
    Task* task2 = new Task("Help me repair the building.", 2, 5, 20);      // 20 好感度

    npc1->addTask(task1);
    npc1->addTask(task2);

    // 将 Abigail NPC 加入到 NPC 列表
    npcs.push_back(npc1);
 
    CCLOG("Abigail NPC initialized!");

    NPC* npc2 = new NPC("Mary", cocos2d::Vec2(300, 200), "../Resources/Characters/NPC/Abigail_1.png", { "../Resources/Characters/NPC/Abigail_1.png", "../Resources/Characters/NPC/Abigail_2.png" });
    npc2->dialogues = {
        "Welcome!",
        "You are a kind person!",
        "I appreciate your thoughtfulness!"
    };
    npcs.push_back(npc2);
    CCLOG("Mary NPC initialized!");

    // 打印列表大小，确认 NPC 是否被添加
    CCLOG("Number of NPCs: %d", npcs.size());
    // 打印所有 NPC 名称
    for (auto npc : npcs) {
        CCLOG("NPC in list: %s", npc->getName().c_str());
    }
}

// 根据名称获取 NPC
NPC* NpcManager::getNPCByName(const std::string& name) {
    for (auto npc : npcs) {
        if (npc->getName() == name) {
            return npc;
        }
    }
    return nullptr;  // 如果没有找到 NPC，则返回 nullptr
}

// 显示 NPC 对话
void NpcManager::showDialog(NPC* npc) {
    if (npc) {
        npc->showDialog();  // 调用 NPC 的对话方法
    }
}
