/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterInfo.cpp
 * File Function: 用户信息类的实现
 * Author:        达思睿
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#pragma once
#include "CharacterInfo.h"

// 初始化静态成员变量 instance 为 nullptr
CharacterInfo* CharacterInfo::_instance = nullptr;

// 获取单例实例，如果实例为空则创建一个新的实例
CharacterInfo* CharacterInfo::getInstance() {
    if (_instance == nullptr) {
        // 如果实例不存在，创建并返回新的实例
        _instance = new CharacterInfo();
    }
    return _instance;  // 返回单例实例
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