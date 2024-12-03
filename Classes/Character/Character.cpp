/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#include "Character.h"

 // 创建Character对象
Character* Character::create(const std::string& filename) {
    Character* character = new (std::nothrow) Character();
    if (character && character->init(filename)) {
        character->autorelease();
        return character;
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

// 初始化Character对象
bool Character::init(const std::string& filename) {
    if (!CharacterMove::init(filename)) {
        return false;
    }

    return true;
}

// 按下键盘时的处理
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CharacterMove::onKeyPressed(keyCode, event);
}

// 释放键盘时的处理
void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CharacterMove::onKeyReleased(keyCode, event);
}