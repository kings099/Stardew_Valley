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
    Character* ret = new(std::nothrow) Character();
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
    animationPlaying = false;
    lastKeyCode = INVIAID_KEY;
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������ǩ
    keyStatusLabel = Label::createWithSystemFont("", "Arial", 24);
    keyStatusLabel->setPosition(200, 100);
    this->addChild(keyStatusLabel); 

    // �������鲢���ó�ʼλ��
    character = Sprite::create(filename);
    character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(character);

    // ��ȡ����Ŀ��
    width = character->getContentSize().width;
    height = character->getContentSize().height;

    // ���̼����¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Character::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Character::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ÿ֡���½�ɫλ��
    //this->schedule(CC_SCHEDULE_SELECTOR(Character::updatePosition), 1.0f / FRAME_RATE);

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

    lastKeyCode = keyCode;
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

// ���¼���״̬��ʾ
void Character::updateKeyStatus() {
    std::string status = "W: " + std::to_string(moveUp) +
        " S: " + std::to_string(moveDown) +
        " A: " + std::to_string(moveLeft) +
        " D: " + std::to_string(moveRight) + 
        " lastKeyCode" + std::to_string(static_cast<int>(lastKeyCode));
    keyStatusLabel->setString(status); // ���±�ǩ����
}

void Character::playAnimation() {
    Vector<SpriteFrame*> frames;

    if (lastKeyCode == EventKeyboard::KeyCode::KEY_W) {
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearUpAction1.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearUpAction2.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearUpAction3.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearUpAction4.png", Rect(0, 0, width, height)));
    }
    else if (lastKeyCode == EventKeyboard::KeyCode::KEY_S) {
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearDownAction1.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearDownAction2.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearDownAction3.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearDownAction4.png", Rect(0, 0, width, height)));
    }
    else if (lastKeyCode == EventKeyboard::KeyCode::KEY_A) {
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction1.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction2.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction3.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction4.png", Rect(0, 0, width, height)));
    }
    else if (lastKeyCode == EventKeyboard::KeyCode::KEY_D) {
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearRightAction1.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearRightAction2.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearRightAction3.png", Rect(0, 0, width, height)));
        frames.pushBack(SpriteFrame::create("../Resources/Characters/Bear/BearRightAction4.png", Rect(0, 0, width, height)));
    }

    if (!frames.empty()) {
        auto animation = Animation::createWithSpriteFrames(frames, 1.0f / ACTION_RATE);
        auto animate = Animate::create(animation);
        character->runAction(RepeatForever::create(animate));
        animationPlaying = true;
        frames.erase(frames.begin(), frames.begin()+4);
    }
}

// ���½�ɫλ��
Vec2 Character::updatePosition(float deltaTime) {
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
        if (!animationPlaying) {
            playAnimation();
        }
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

    updateKeyStatus();
    return newPosition;
}