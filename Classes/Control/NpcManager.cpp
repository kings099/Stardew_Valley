
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
NpcManager* NpcManager::_instance = nullptr;

// 构造函数
NpcManager::NpcManager() {

}

// 析构函数
NpcManager::~NpcManager() {
    for (auto npc : _npcs) {
        delete npc;
    }
    _npcs.clear();
}

// 获取单例实例
NpcManager* NpcManager::getInstance() {
    if (!_instance) {
        _instance = new NpcManager();  // 如果实例不存在，则创建
    }
    return _instance;
}

// 初始化 NPC
void NpcManager::initializeNPCs() {
    // 初始化 NPC 实例，并添加到 npcs 列表
    NPC* npc1 = new NPC("Abigail", cocos2d::Vec2(100, 160), "../Resources/Characters/NPC/Abigail_1.png", { "../Resources/Characters/NPC/Abigail_1.png", "../Resources/Characters/NPC/Abigail_2.png" ,"../Resources/Characters/NPC/Abigail_3.png","../Resources/Characters/NPC/Abigail_4.png" });
    npc1->_dialogues = {
        "Hello, traveler",
        "I feel like you care about me",
        "Thank you for the gift"
    };
    // 添加任务给 Abigail（现在奖励是好感度）
    Task* task1 = new Task("Give me a gift (I like pumpkin)", "pumpkin", 1, 10);               
    Task* task2 = new Task("Help me repair the building.","Timber", 4, 20);                  

    npc1->addTask(task1);
    npc1->addTask(task2);
    _npcs.push_back(npc1);
 

    NPC* npc2 = new NPC("Mary", cocos2d::Vec2(300, 200), "../Resources/Characters/NPC/Abigail_1.png", { "../Resources/Characters/NPC/Abigail_1.png", "../Resources/Characters/NPC/Abigail_2.png" });
    npc2->_dialogues = {
        "Welcome",
        "You are a kind person",
        "I appreciate your thoughtfulness"
    };
    _npcs.push_back(npc2);
   
}

// 根据名称获取 NPC
NPC* NpcManager::getNPCByName(const std::string& name) {
    for (auto npc : _npcs) {
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
