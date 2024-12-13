#pragma once
#include "NpcManager.h"
#include "GiftItemManager.h"

class NpcInteractionManager {
public:
    // 获取 NpcInteractionManager 的单例实例
    static NpcInteractionManager* getInstance();
    void giveGiftToNPC(const std::string& npcName, const std::string& giftName);  // 给 NPC 送礼物
    void showDialog(const std::string& npcName);  // 显示某个 NPC 的对话

private:
    NpcInteractionManager();  // 私有构造函数
    NpcInteractionManager(const NpcInteractionManager&) = delete;  // 禁用拷贝构造函数
    NpcInteractionManager& operator=(const NpcInteractionManager&) = delete;  // 禁用赋值操作符
    static NpcInteractionManager* instance;
    // 不再需要手动实例化，直接通过单例访问
};
