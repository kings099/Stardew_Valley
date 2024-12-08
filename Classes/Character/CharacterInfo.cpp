/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterInfo.cpp
 * File Function: �û���Ϣ���ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#pragma once
#include "CharacterInfo.h"

// ��ʼ����̬��Ա���� instance Ϊ nullptr
CharacterInfo* CharacterInfo::instance = nullptr;

// ��ȡ����ʵ�������ʵ��Ϊ���򴴽�һ���µ�ʵ��
CharacterInfo* CharacterInfo::getInstance() {
    if (instance == nullptr) {
        // ���ʵ�������ڣ������������µ�ʵ��
        instance = new CharacterInfo();
    }
    return instance;  // ���ص���ʵ��
}

// ���ý�ɫ��Ϣ�������û�����ũ��������ϲ��������
void CharacterInfo::setCharacterInfo(const std::string& username, const std::string& farmName, const std::string& favoriteThing) {
    this->username = username;      // �����û���
    this->farmName = farmName;      // ����ũ������
    this->favoriteThing = favoriteThing;  // ������ϲ��������
}

// ��ȡ�û���
std::string CharacterInfo::getUsername() const {
    return username;  // �����û���
}

// ��ȡũ������
std::string CharacterInfo::getFarmName() const {
    return farmName;  // ����ũ������
}

// ��ȡ��ϲ��������
std::string CharacterInfo::getFavoriteThing() const {
    return favoriteThing;  // ������ϲ��������
}