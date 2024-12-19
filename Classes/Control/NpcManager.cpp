
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcManager.cpp
 * File Function: ���������Ϸ�е� NPC ʵ��NpcManager���ʵ��
                  ���� NPC �ĳ�ʼ������ѯ���Ի��ȹ��ܡ�
 * Author:        ��˼�
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#include "NpcManager.h"

// ��ʼ����̬��Ա
NpcManager* NpcManager::instance = nullptr;

// ���캯��
NpcManager::NpcManager() {
    // �����ڴ˽��г�ʼ��
    // ���磺initializeNPCs();
}

// ��������
NpcManager::~NpcManager() {
    // ���� NPC �б�
    for (auto npc : npcs) {
        delete npc;
    }
    npcs.clear();
}

// ��ȡ����ʵ��
NpcManager* NpcManager::getInstance() {
    if (!instance) {
        instance = new NpcManager();  // ���ʵ�������ڣ��򴴽�
    }
    return instance;
}

// ��ʼ�� NPC
void NpcManager::initializeNPCs() {
    // ��ʼ�� NPC ʵ��������ӵ� npcs �б�
    NPC* npc1 = new NPC("Abigail", cocos2d::Vec2(100, 200), "../Resources/Characters/NPC/Abigail_1.png", { "../Resources/Characters/NPC/Abigail_1.png", "../Resources/Characters/NPC/Abigail_2.png" ,"../Resources/Characters/NPC/Abigail_3.png","../Resources/Characters/NPC/Abigail_4.png" });
    npc1->dialogues = {
        "Hello, traveler!",
        "I feel like you care about me.",
        "Thank you for the gift!"
    };
    // �������� Abigail�����ڽ����Ǻøжȣ�
    Task* task1 = new Task("Give me a rare item from the mine.", 1, 1, 10); // 10 �øж�
    Task* task2 = new Task("Help me repair the building.", 2, 5, 20);      // 20 �øж�

    npc1->addTask(task1);
    npc1->addTask(task2);

    // �� Abigail NPC ���뵽 NPC �б�
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

    // ��ӡ�б��С��ȷ�� NPC �Ƿ����
    CCLOG("Number of NPCs: %d", npcs.size());
    // ��ӡ���� NPC ����
    for (auto npc : npcs) {
        CCLOG("NPC in list: %s", npc->getName().c_str());
    }
}

// �������ƻ�ȡ NPC
NPC* NpcManager::getNPCByName(const std::string& name) {
    for (auto npc : npcs) {
        if (npc->getName() == name) {
            return npc;
        }
    }
    return nullptr;  // ���û���ҵ� NPC���򷵻� nullptr
}

// ��ʾ NPC �Ի�
void NpcManager::showDialog(NPC* npc) {
    if (npc) {
        npc->showDialog();  // ���� NPC �ĶԻ�����
    }
}
