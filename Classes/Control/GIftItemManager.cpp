
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GiftItemManager.cpp
 * File Function: ���ļ�ʵ����������Ʒ��������GiftItemManager���Ĺ��ܡ�
                  GiftItemManager �����ڹ�����Ϸ�е�������Ʒ��
                  �����ݲ�ͬ�� NPC ��ɫ�������ϲ�ý��г�ʼ���Ͳ�ѯ��
                  �����õ���ģʽ��ȷ��ֻ��һ�����������ʵ�����ڡ�
 * Author:        ��˼�
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#include "GiftItemManager.h"



GiftItemManager* GiftItemManager::getInstance() {
    static GiftItemManager instance;  // ��̬�ֲ�������ȷ��ֻ����һ��ʵ��
    return &instance;  // ����ʵ����ָ��
}

GiftItemManager::GiftItemManager() {
    // ��ʼ���������ݣ����������������� initializeGifts() ������
    initializeGifts();
}

void GiftItemManager::initializeGifts() {
    GiftItem rose("Rose", 10);
    rose.setAffectionForNPC("John", 20);  // John �� Rose �ķ�Ӧ����
    rose.setAffectionForNPC("Mary", 5);   // Mary �� Rose �ķ�Ӧ��С

    GiftItem chocolate("Chocolate", 5);
    chocolate.setAffectionForNPC("John", 15);  // John ϲ���ɿ���
    chocolate.setAffectionForNPC("Mary", 10);  // Mary Ҳϲ���ɿ���

    GiftItem teddyBear("Teddy Bear", 15);
    teddyBear.setAffectionForNPC("John", 30);  // John ��ϲ��̩����
    teddyBear.setAffectionForNPC("Mary", 10);  // Mary ��̩���ܲ�����Ȥ

    gifts.push_back(rose);
    gifts.push_back(chocolate);
    gifts.push_back(teddyBear);
}

GiftItem* GiftItemManager::getGiftByName(const std::string& name) {
    // �������Ʋ�������
    for (auto& gift : gifts) {
        if (gift.name == name) {
            return &gift;
        }
    }
    return nullptr;  // ���û���ҵ������� nullptr
}