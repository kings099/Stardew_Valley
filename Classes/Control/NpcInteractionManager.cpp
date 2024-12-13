
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcInteractionManager.cpp
 * File Function: ���ļ�ʵ���� NPC ������������NpcInteractionManager���Ĺ��ܡ�
                  NpcInteractionManager �����ڴ�������� NPC ֮��Ļ�����
                  �����������ʾ�Ի������õ���ģʽ��
 * Author:        ��˼�
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#include "NpcInteractionManager.h"

// ��ʼ����̬��Ա
NpcInteractionManager* NpcInteractionManager::instance = nullptr;

NpcInteractionManager* NpcInteractionManager::getInstance() {
    if (!instance) {
        instance = new NpcInteractionManager();  // ���ʵ�������ڣ��򴴽�
    }
    return instance;
}

NpcInteractionManager::NpcInteractionManager() {
    // ������Ա���Ϊ�գ�NpcManager �� GiftItemManager �Ѿ��ǵ���������Ҫ�ظ���ʼ��
}

void NpcInteractionManager::giveGiftToNPC(const std::string& npcName, const std::string& giftName) {
    // ֱ��ͨ��������ȡ NpcManager �� GiftItemManager
    NPC* npc = NpcManager::getInstance()->getNPCByName(npcName);
    GiftItem* gift = GiftItemManager::getInstance()->getGiftByName(giftName);

    if (npc && gift) {
        npc->giftItem(gift);  // �� NPC ������
    }
}

void NpcInteractionManager::showDialog(const std::string& npcName) {
    // ֱ��ͨ��������ȡ NpcManager
    NPC* npc = NpcManager::getInstance()->getNPCByName(npcName);
    if (npc) {
        NpcManager::getInstance()->showDialog(npc);  // ��ʾ NPC �Ի�
    }
}
