/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/02
 * License:       MIT License
 ****************************************************************/

#include "Character.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

//创建对象
Character* Character::create(const std::string& filename) {
    Character* ret = new(std::nothrow) Character();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//初始化
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

    // 创建标签
    keyStatusLabel = Label::createWithSystemFont("", "Arial", 24);
    keyStatusLabel->setPosition(200, 100);
    this->addChild(keyStatusLabel); 

    // 创建精灵并设置初始位置
    character = Sprite::create(filename);
    character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(character);

    // 获取精灵的宽高
    width = character->getContentSize().width;
    height = character->getContentSize().height;

    // 键盘监视事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Character::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Character::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 每帧更新角色位置
    //this->schedule(CC_SCHEDULE_SELECTOR(Character::updatePosition), 1.0f / FRAME_RATE);

    return true;
}

// 按下键盘时的处理
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

// 释放键盘时的处理
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

// 更新键盘状态显示
void Character::updateKeyStatus() {
    std::string status = "W: " + std::to_string(moveUp) +
        " S: " + std::to_string(moveDown) +
        " A: " + std::to_string(moveLeft) +
        " D: " + std::to_string(moveRight) + 
        " lastKeyCode" + std::to_string(static_cast<int>(lastKeyCode));
    keyStatusLabel->setString(status); // 更新标签内容
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

// 更新角色位置
Vec2 Character::updatePosition(float deltaTime) {
    const float moveSpeed = MOVE_SPEED;

    Vec2 newPosition = character->getPosition();
    Vec2 moveDirection(0, 0);

    // 移动方向确定
    if (moveUp) {
        moveDirection.y += 1; // 向上
    }
    if (moveDown) {
        moveDirection.y -= 1; // 向下
    }
    if (moveLeft) {
        moveDirection.x -= 1; // 向左
    }
    if (moveRight) {
        moveDirection.x += 1; // 向右
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

    // 边界检测
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

    // 更新精灵位置
    character->setPosition(newPosition);

    updateKeyStatus();
    return newPosition;
}