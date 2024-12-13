/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Character.cpp
 * File Function: Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/06
 * License:       MIT License
 ****************************************************************/

#include "Character.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;
// 获取单例
Character* Character::getInstance(const std::string& filename) {
    static Character* instance = nullptr; 
    if (!instance) {
        instance = new Character(filename); // 仅在第一次调用时创建实例
    }
    return instance;
}

// 构造函数
Character::Character(const std::string& filename){
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建精灵并设置初始位置
    _character = Sprite::create(filename);
    _character->setScale(2.0);
    _character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->cocos2d::Node::addChild(_character);
}

// 按下键盘时的处理
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // 角色移动处理函数
    if (!CharacterObjectList::getObjectListStatus()) {
        CharacterMove::onKeyPressed(keyCode, event);
    }
    else {
        stopMove();
    }
    CharacterObjectList::onKeyPressed(keyCode, event);
}

// 释放键盘时的处理
void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // 角色移动处理函数
    if (!CharacterObjectList::getObjectListStatus()) {
        CharacterMove::onKeyReleased(keyCode, event);
    }
    else {
        stopMove();
    }
}

// 更新角色位置
Vec2 Character::updatePosition(float deltaTime) {
    return CharacterMove::updatePosition(deltaTime);
}


// 获取角色精灵节点
Sprite* Character::getCharacterSprite() const{
    return _character;
}
