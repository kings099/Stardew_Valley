/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/02
 * License:       MIT License
 ****************************************************************/

#include "Character.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

//��������
Character* Character::create(const std::string& filename) {
    Character* ret = new Character();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//��ʼ��
bool Character::init(const std::string& filename) {
    if (!Node::init()) {
        return false;
    }
    moveSpeed = MOVE_SPEED;
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �������鲢���ó�ʼλ��
    character = Sprite::create(filename);
    character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(character);

    // ���̼����¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Character::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Character::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ÿ֡���½�ɫλ��
    this->schedule(CC_SCHEDULE_SELECTOR(Character::updatePosition), 1.0f / FRAME_RATE);

    return true;
}

// ���¼���ʱ�Ĵ���
void Character::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        moveUp = true; 
        break;
    case EventKeyboard::KeyCode::KEY_S:
        moveDown = true; 
        break;
    case EventKeyboard::KeyCode::KEY_A:
        moveLeft = true;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        moveRight = true; 
        break;
    default:
        break;
    }
}

// �ͷż���ʱ�Ĵ���
void Character::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        moveUp = false; 
        break;
    case EventKeyboard::KeyCode::KEY_S:
        moveDown = false; 
        break;
    case EventKeyboard::KeyCode::KEY_A:
        moveLeft = false; 
        break;
    case EventKeyboard::KeyCode::KEY_D:
        moveRight = false;
        break;
    default:
        break;
    }
}

// ���½�ɫλ��
void Character::updatePosition(float deltaTime) {
    const float moveSpeed = MOVE_SPEED;

    Vec2 newPosition = character->getPosition();
    Vec2 moveDirection(0, 0);

    // �ƶ�����ȷ��
    if (moveUp) {
        moveDirection.y += 1; // ����
    }
    if (moveDown) {
        moveDirection.y -= 1; // ����
    }
    if (moveLeft) {
        moveDirection.x -= 1; // ����
    }
    if (moveRight) {
        moveDirection.x += 1; // ����
    }
    if (moveDirection.x != 0 || moveDirection.y != 0) {
        moveDirection.normalize();
        const float currentSpeed = moveSpeed / sqrtf(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
        newPosition += moveDirection * currentSpeed; 
    }

    // �߽���
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const float halfWidth = character->getContentSize().width / 2;
    const float halfHeight = character->getContentSize().height / 2;
    if (newPosition.x - halfWidth < 0) {
        newPosition.x = halfWidth; 
    }
    if (newPosition.x + halfWidth > visibleSize.width) {
        newPosition.x = visibleSize.width - halfWidth; 
    }
    if (newPosition.y - halfHeight < 0) {
        newPosition.y = halfHeight; 
    }
    if (newPosition.y + halfHeight > visibleSize.height) {
        newPosition.y = visibleSize.height - halfHeight;
    }

    // ���¾���λ��
    character->setPosition(newPosition);
}