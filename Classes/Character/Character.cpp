/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#include "Character.h"

 // ����Character����
Character* Character::create(const std::string& filename) {
    Character* character = new (std::nothrow) Character();
    if (character && character->init(filename)) {
        character->autorelease();
        return character;
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

// ��ʼ��Character����
bool Character::init(const std::string& filename) {
    if (!CharacterMove::init(filename)) {
        return false;
    }

    return true;
}

// ���¼���ʱ�Ĵ���
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CharacterMove::onKeyPressed(keyCode, event);
}

// �ͷż���ʱ�Ĵ���
void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CharacterMove::onKeyReleased(keyCode, event);
}