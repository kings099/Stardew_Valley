
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
NpcManager* NpcManager::_instance = nullptr;

// ���캯��
NpcManager::NpcManager() {

}

// ��������
NpcManager::~NpcManager() {
    for (auto npc : _npcs) {
        delete npc;
    }
    _npcs.clear();
}

// ��ȡ����ʵ��
NpcManager* NpcManager::getInstance() {
    if (!_instance) {
        _instance = new NpcManager();  // ���ʵ�������ڣ��򴴽�
    }
    return _instance;
}

// ��ʼ�� NPC
void NpcManager::initializeNPCs() {
    // ��ʼ�� NPC ʵ��������ӵ� npcs �б�
    NPC* npc1 = new NPC("Abigail", cocos2d::Vec2(100, 160), "../Resources/Characters/NPC/Abigail_1.png", { "../Resources/Characters/NPC/Abigail_1.png", "../Resources/Characters/NPC/Abigail_2.png" ,"../Resources/Characters/NPC/Abigail_3.png","../Resources/Characters/NPC/Abigail_4.png" });
    npc1->_dialogues = {
        "Hello, traveler",
        "I feel like you care about me",
        "Thank you for the gift"
    };
    // �������� Abigail�����ڽ����Ǻøжȣ�
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

// �������ƻ�ȡ NPC
NPC* NpcManager::getNPCByName(const std::string& name) {
    for (auto npc : _npcs) {
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
