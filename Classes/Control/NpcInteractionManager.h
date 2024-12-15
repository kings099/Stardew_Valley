#pragma once
#include "NpcManager.h"
#include "GiftItemManager.h"

class NpcInteractionManager {
public:
    // ��ȡ NpcInteractionManager �ĵ���ʵ��
    static NpcInteractionManager* getInstance();
    void giveGiftToNPC(const std::string& npcName, const std::string& giftName);  // �� NPC ������
    void showDialog(const std::string& npcName);  // ��ʾĳ�� NPC �ĶԻ�

private:
    NpcInteractionManager();  // ˽�й��캯��
    NpcInteractionManager(const NpcInteractionManager&) = delete;  // ���ÿ������캯��
    NpcInteractionManager& operator=(const NpcInteractionManager&) = delete;  // ���ø�ֵ������
    static NpcInteractionManager* instance;
    // ������Ҫ�ֶ�ʵ������ֱ��ͨ����������
};
