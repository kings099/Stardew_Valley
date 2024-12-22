
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
    GiftItem rose("Ring", 10);               //NPC��Ring��Ӧ��Ĭ��ֵ
    rose.setAffectionForNPC("Abigail", 20);  // Abigail �� Ring �ķ�Ӧ����
    rose.setAffectionForNPC("Mary", 5);      // Mary �� Rose �ķ�Ӧ��С

    GiftItem chocolate("Timber", 5);
    chocolate.setAffectionForNPC("Abigail", 15);  
    chocolate.setAffectionForNPC("Mary", 10); 

    GiftItem teddyBear("Teddy Bear", 15);
    teddyBear.setAffectionForNPC("Abigail", 30);  // John ��ϲ��̩����
    teddyBear.setAffectionForNPC("Mary", 10);  // Mary ��̩���ܲ�����Ȥ

    _gifts.push_back(rose);
    _gifts.push_back(chocolate);
    _gifts.push_back(teddyBear);
}

GiftItem* GiftItemManager::getGiftByName(const std::string& name) {
    // �������Ʋ�������
    for (auto& gift : _gifts) {
        if (gift._name == name) {
            return &gift;
        }
    }
    return nullptr;  // ���û���ҵ������� nullptr
}