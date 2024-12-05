/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#include "Character.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// ���캯��
Character::Character(const std::string& filename) {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �������鲢���ó�ʼλ��
    _character = Sprite::create(filename);
    _character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->cocos2d::Node::addChild(_character);

    // ���̼����¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Character::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Character::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  /*  auto listener2 = EventListenerKeyboard::create();
    listener2->onKeyPressed = CC_CALLBACK_2(CharacterObjectList::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);*/
  
}

// ���¼���ʱ�Ĵ���
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // ��ɫ�ƶ�������
    if (!openObjectList) {
        CharacterMove::onKeyPressed(keyCode, event);
    }
    CharacterObjectList::onKeyPressed(keyCode, event);
}

// �ͷż���ʱ�Ĵ���
void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    // ��ɫ�ƶ�������
    if (!openObjectList) {
        CharacterMove::onKeyReleased(keyCode, event);
    }
}

// ���½�ɫλ��
Vec2 Character::updatePosition(float deltaTime) {
    return CharacterMove::updatePosition(deltaTime);
}