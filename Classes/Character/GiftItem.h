/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NpcInteractionManager.cpp
 * File Function: ���ļ������� `GiftItem` �࣬��ʾ��Ϸ�е��������
                  ÿ������������ơ������øж�����ֵ��
                  �Լ��ض� NPC �Ը���������ⷴӦֵ��
 * Author:        ��˼�
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#ifndef GIFTITEM_H
#define GIFTITEM_H

#include <map>
#include <string>

class GiftItem {
public:
    std::string name;  // ��������
    int baseAffectionValue;  // ����Ļ����øж�����

    // �洢��ͬ NPC �Ը�����Ĳ�ͬ�øжȷ�Ӧ
    std::map<std::string, int> affectionByNPC;

    GiftItem(const std::string& name, int baseAffectionValue)
        : name(name), baseAffectionValue(baseAffectionValue) {}

    // ����ĳ�� NPC �Ը����������øж�ֵ
    void setAffectionForNPC(const std::string& npcName, int value) {
        affectionByNPC[npcName] = value;
    }

    // ��ȡĳ�� NPC �Ը�����ĺøж�
    int getAffectionForNPC(const std::string& npcName) {
        if (affectionByNPC.find(npcName) != affectionByNPC.end()) {
            return affectionByNPC[npcName];
        }
        return baseAffectionValue;  // Ĭ��ʹ�û����øж�ֵ
    }
};

#endif // GIFTITEM_H
