/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterInfo.h
 * File Function: �û���Ϣ���ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#pragma once

#include "cocos2d.h"

class CharacterInfo {
public:
    // ��ȡ����ʵ����ȷ��ֻ����һ�� CharacterInfo ʵ��
    static CharacterInfo* getInstance();

    // ���ý�ɫ��Ϣ���û�����ũ��������ϲ�������
    void setCharacterInfo(const std::string& username, const std::string& farmName, const std::string& favoriteThing);

    // ��ȡ�û���
    std::string getUsername() const;

    // ��ȡũ������
    std::string getFarmName() const;

    // ��ȡ��ϲ��������
    std::string getFavoriteThing() const;

private:
    // ˽�л����캯����ȷ��ֻ��ͨ�� getInstance() ��������ʵ��
    CharacterInfo() {}

    // �洢Ψһ��ʵ��������ģʽ
    static CharacterInfo* _instance;

    // �û���Ϣ
    std::string _username;
    std::string _farmName;
    std::string _favoriteThing;
};

