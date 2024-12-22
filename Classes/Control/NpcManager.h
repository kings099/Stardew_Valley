
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcManager.h
 * File Function: 负责管理游戏中的 NPC 实例NpcManager类的实现
                  包括 NPC 的初始化、查询、对话等功能。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#pragma once
#include "Character/NPC.h"
#include "Character/Task.h"
#include <vector>
#include <string>

class NpcManager {
public:
    static NpcManager* getInstance();  // 获取单例实例

    void initializeNPCs();  // 初始化 NPC
    NPC* getNPCByName(const std::string& name);  // 根据名称获取 NPC
    void showDialog(NPC* npc);  // 显示 NPC 对话

private:
    NpcManager();  // 私有构造函数，避免外部实例化
    ~NpcManager();  // 析构函数

    static NpcManager* _instance;  // 单例实例
    std::vector<NPC*> _npcs;  // NPC 列表
};
