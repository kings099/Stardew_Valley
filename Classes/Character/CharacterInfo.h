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
    static CharacterInfo* instance;

    // �û���Ϣ
    std::string username;
    std::string farmName;
    std::string favoriteThing;
};

