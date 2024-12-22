#pragma once
#include "Character/GiftItem.h"
#include <vector>
#include <string>

class GiftItemManager {
public:
    // ��ȡ GiftItemManager �ĵ���ʵ��
    static GiftItemManager* getInstance();

    void initializeGifts();  // ��ʼ������
    GiftItem* getGiftByName(const std::string& name);  // �������ƻ�ȡ����

private:
    GiftItemManager();  // ˽�й��캯��
    std::vector<GiftItem> _gifts;  // �����б�
};
