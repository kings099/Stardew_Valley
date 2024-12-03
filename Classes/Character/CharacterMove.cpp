/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/03
 * License:       MIT License
 ****************************************************************/

#include "CharacterMove.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

//��������
CharacterMove* CharacterMove::create(const std::string& filename) {
    CharacterMove* ret = new(std::nothrow) CharacterMove();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//��ʼ��
bool CharacterMove::init(const std::string& filename) {
    if (!Node::init()) {
        return false;
    }
    //���ݳ�Ա��ʼ��
    moveSpeed = MOVE_SPEED;
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
    animationPlaying = false;
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �������鲢���ó�ʼλ��
    character = Sprite::create(filename);
    character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(character);

    // ��ȡ����Ŀ��
    width = character->getContentSize().width;
    height = character->getContentSize().height;

    // ���̼����¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CharacterMove::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(CharacterMove::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ÿ֡���½�ɫλ��
    //this->schedule(CC_SCHEDULE_SELECTOR(CharacterMove::updatePosition), 1.0f / FRAME_RATE);

    return true;
}

// ���¼���ʱ�Ĵ���
void CharacterMove::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
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
void CharacterMove::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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

// չʾ����Ч��
void CharacterMove::playAnimation() {
    // ��������
    if (moveLeft) {
        currentDirection = "left";
        frames = {
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction1.png", Rect(0, 0, width, height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction2.png", Rect(0, 0, width, height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction3.png", Rect(0, 0, width, height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction4.png", Rect(0, 0, width, height))
        };
    }
    else if (moveRight) {
        currentDirection = "right";
        frames = {
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction1.png", Rect(0, 0, width, height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction2.png", Rect(0, 0, width, height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction3.png", Rect(0, 0, width, height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction4.png", Rect(0, 0, width, height))
        };
    }
    else if (moveUp && (!moveRight && !moveLeft)) {
        currentDirection = "up";
        frames = {
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction1.png", Rect(0, 0, width, height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction2.png", Rect(0, 0, width, height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction3.png", Rect(0, 0, width, height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction4.png", Rect(0, 0, width, height))
        };
    }
    else if (moveDown && (!moveRight  && !moveLeft )) {
        currentDirection = "down";
        frames = {
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction1.png", Rect(0, 0, width, height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction2.png", Rect(0, 0, width, height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction3.png", Rect(0, 0, width, height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction4.png", Rect(0, 0, width, height))
        };
    }

    // ��������
    if (!frames.empty()&&(currentDirection != lastDirection)) {
        auto animation = Animation::createWithSpriteFrames(frames, 1.0f / ACTION_RATE);
        auto animate = Animate::create(animation);
        character->stopAllActions();
        character->runAction(RepeatForever::create(animate));
        animationPlaying = true;
        lastDirection = currentDirection; 
    }
}

// ���½�ɫλ��
Vec2 CharacterMove::updatePosition(float deltaTime) {
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
        playAnimation();
    }
    else {
        character->stopAllActions();
        animationPlaying = false;
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

    return newPosition;
}