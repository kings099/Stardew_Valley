#pragma once

#include "cocos2d.h"

class CharacterInfo {
public:
    // 获取单例实例，确保只存在一个 CharacterInfo 实例
    static CharacterInfo* getInstance();

    // 设置角色信息（用户名、农场名、最喜欢的事物）
    void setCharacterInfo(const std::string& username, const std::string& farmName, const std::string& favoriteThing);

    // 获取用户名
    std::string getUsername() const;

    // 获取农场名称
    std::string getFarmName() const;

    // 获取最喜欢的事物
    std::string getFavoriteThing() const;

private:
    // 私有化构造函数，确保只能通过 getInstance() 创建该类实例
    CharacterInfo() {}

    // 存储唯一的实例，单例模式
    static CharacterInfo* instance;

    // 用户信息
    std::string username;
    std::string farmName;
    std::string favoriteThing;
};

