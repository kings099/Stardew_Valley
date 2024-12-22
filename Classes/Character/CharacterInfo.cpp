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
CharacterInfo* CharacterInfo::_instance = nullptr;

// ��ȡ����ʵ�������ʵ��Ϊ���򴴽�һ���µ�ʵ��
CharacterInfo* CharacterInfo::getInstance() {
    if (_instance == nullptr) {
        // ���ʵ�������ڣ������������µ�ʵ��
        _instance = new CharacterInfo();
    }
    return _instance;  // ���ص���ʵ��
}

// ���ý�ɫ��Ϣ�������û�����ũ��������ϲ��������
void CharacterInfo::setCharacterInfo(const std::string& username, const std::string& farmName, const std::string& favoriteThing) {
    this->_username = username;      // �����û���
    this->_farmName = farmName;      // ����ũ������
    this->_favoriteThing = favoriteThing;  // ������ϲ��������
}

// ��ȡ�û���
std::string CharacterInfo::getUsername() const {
    return _username;  // �����û���
}

// ��ȡũ������
std::string CharacterInfo::getFarmName() const {
    return _farmName;  // ����ũ������
}

// ��ȡ��ϲ��������
std::string CharacterInfo::getFavoriteThing() const {
    return _favoriteThing;  // ������ϲ��������
}