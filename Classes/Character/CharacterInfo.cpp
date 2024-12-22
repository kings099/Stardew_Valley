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
    this->_username = username;      // 设置用户名
    this->_farmName = farmName;      // 设置农场名称
    this->_favoriteThing = favoriteThing;  // 设置最喜欢的事物
}

// 获取用户名
std::string CharacterInfo::getUsername() const {
    return _username;  // 返回用户名
}

// 获取农场名称
std::string CharacterInfo::getFarmName() const {
    return _farmName;  // 返回农场名称
}

// 获取最喜欢的事物
std::string CharacterInfo::getFavoriteThing() const {
    return _favoriteThing;  // 返回最喜欢的事物
}