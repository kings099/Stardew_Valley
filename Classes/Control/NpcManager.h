#pragma once
#include "Character/NPC.h"
#include "Character/Task.h"
#include <vector>
#include <string>

class NpcManager {
public:
    static NpcManager* getInstance();  // ��ȡ����ʵ��

    void initializeNPCs();  // ��ʼ�� NPC
    NPC* getNPCByName(const std::string& name);  // �������ƻ�ȡ NPC
    void showDialog(NPC* npc);  // ��ʾ NPC �Ի�

private:
    NpcManager();  // ˽�й��캯���������ⲿʵ����
    ~NpcManager();  // ��������

    static NpcManager* instance;  // ����ʵ��
    std::vector<NPC*> npcs;  // NPC �б�
};
