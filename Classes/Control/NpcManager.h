
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcManager.h
 * File Function: ���������Ϸ�е� NPC ʵ��NpcManager���ʵ��
                  ���� NPC �ĳ�ʼ������ѯ���Ի��ȹ��ܡ�
 * Author:        ��˼�
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
    static NpcManager* getInstance();  // ��ȡ����ʵ��

    void initializeNPCs();  // ��ʼ�� NPC
    NPC* getNPCByName(const std::string& name);  // �������ƻ�ȡ NPC
    void showDialog(NPC* npc);  // ��ʾ NPC �Ի�

private:
    NpcManager();  // ˽�й��캯���������ⲿʵ����
    ~NpcManager();  // ��������

    static NpcManager* _instance;  // ����ʵ��
    std::vector<NPC*> _npcs;  // NPC �б�
};
