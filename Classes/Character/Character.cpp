/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#include "Character.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
Character::Character(const std::string& filename) {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建精灵并设置初始位置
    _character = Sprite::create(filename);
    _character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->cocos2d::Node::addChild(_character);

    // 键盘监视事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Character::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Character::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  /*  auto listener2 = EventListenerKeyboard::create();
    listener2->onKeyPressed = CC_CALLBACK_2(CharacterObjectList::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);*/
  
}

// 按下键盘时的处理
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // 角色移动处理函数
    if (!openObjectList) {
        CharacterMove::onKeyPressed(keyCode, event);
    }
    CharacterObjectList::onKeyPressed(keyCode, event);
}

// 释放键盘时的处理
void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // 角色移动处理函数
    if (!openObjectList) {
        CharacterMove::onKeyReleased(keyCode, event);
    }
}

// 更新角色位置
Vec2 Character::updatePosition(float deltaTime) {
    return CharacterMove::updatePosition(deltaTime);
}