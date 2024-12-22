/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterInfo.cpp
 * File Function: 用户信息类的实现
 * Author:        达思睿
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/

#include "CharacterInfo.h"

 // 获取单例实例，静态局部变量实现单例
CharacterInfo* CharacterInfo::getInstance() {
    static CharacterInfo* instance = nullptr;
    if (!instance) {
        instance = new CharacterInfo(); // 仅在第一次调用时创建实例
    }
    return instance;
}

// 设置角色信息，包括用户名、农场名和最喜欢的事物
void CharacterInfo::setCharacterInfo(const std::string& username, const std::string& farmName, const std::string& favoriteThing) {
    this->_username = username;      
    this->_farmName = farmName;    
    this->_favoriteThing = favoriteThing; 
}

// 获取用户名
std::string CharacterInfo::getUsername() const {
    return _username; 
}

// 获取农场名称
std::string CharacterInfo::getFarmName() const {
    return _farmName;  
}

// 获取最喜欢的事物
std::string CharacterInfo::getFavoriteThing() const {
    return _favoriteThing;
}