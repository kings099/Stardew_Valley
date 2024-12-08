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
CharacterInfo* CharacterInfo::instance = nullptr;

// 获取单例实例，如果实例为空则创建一个新的实例
CharacterInfo* CharacterInfo::getInstance() {
    if (instance == nullptr) {
        // 如果实例不存在，创建并返回新的实例
        instance = new CharacterInfo();
    }
    return instance;  // 返回单例实例
}

// 设置角色信息，包括用户名、农场名和最喜欢的事物
void CharacterInfo::setCharacterInfo(const std::string& username, const std::string& farmName, const std::string& favoriteThing) {
    this->username = username;      // 设置用户名
    this->farmName = farmName;      // 设置农场名称
    this->favoriteThing = favoriteThing;  // 设置最喜欢的事物
}

// 获取用户名
std::string CharacterInfo::getUsername() const {
    return username;  // 返回用户名
}

// 获取农场名称
std::string CharacterInfo::getFarmName() const {
    return farmName;  // 返回农场名称
}

// 获取最喜欢的事物
std::string CharacterInfo::getFavoriteThing() const {
    return favoriteThing;  // 返回最喜欢的事物
}