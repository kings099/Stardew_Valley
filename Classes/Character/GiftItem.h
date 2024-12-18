/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcInteractionManager.cpp
 * File Function: 该文件定义了 `GiftItem` 类，表示游戏中的礼物对象。
                  每个礼物包含名称、基础好感度增益值，
                  以及特定 NPC 对该礼物的特殊反应值。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#ifndef GIFTITEM_H
#define GIFTITEM_H

#include <map>
#include <string>

class GiftItem {
public:
    std::string name;  // 礼物名称
    int baseAffectionValue;  // 礼物的基本好感度增益

    // 存储不同 NPC 对该礼物的不同好感度反应
    std::map<std::string, int> affectionByNPC;

    GiftItem(const std::string& name, int baseAffectionValue)
        : name(name), baseAffectionValue(baseAffectionValue) {}

    // 设置某个 NPC 对该礼物的特殊好感度值
    void setAffectionForNPC(const std::string& npcName, int value) {
        affectionByNPC[npcName] = value;
    }

    // 获取某个 NPC 对该礼物的好感度
    int getAffectionForNPC(const std::string& npcName) {
        if (affectionByNPC.find(npcName) != affectionByNPC.end()) {
            return affectionByNPC[npcName];
        }
        return baseAffectionValue;  // 默认使用基础好感度值
    }
};

#endif // GIFTITEM_H
