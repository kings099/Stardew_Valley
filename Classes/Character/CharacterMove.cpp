/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.cpp
 * File Function: Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#include "CharacterMove.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

//创建对象
CharacterMove* CharacterMove::create(const std::string& filename) {
    CharacterMove* ret = new(std::nothrow) CharacterMove();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//初始化
bool CharacterMove::init(const std::string& filename) {
    if (!Node::init()) {
        return false;
    }
    //数据成员初始化
    _moveSpeed = MOVE_SPEED;
    _moveUp = false;
    _moveDown = false;
    _moveLeft = false;
    _moveRight = false;
    _animationPlaying = false;
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建精灵并设置初始位置
    _character = Sprite::create(filename);
    _character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(_character);

    // 获取精灵的宽高
    _width = _character->getContentSize().width;
    _height = _character->getContentSize().height;

    // 键盘监视事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CharacterMove::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(CharacterMove::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 按下键盘时的处理
void CharacterMove::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        _moveUp = true;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        _moveDown = true;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _moveLeft = true;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        _moveRight = true;
        break;
    default:
        break;
    }
}

// 释放键盘时的处理
void CharacterMove::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        _moveUp = false;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        _moveDown = false;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _moveLeft = false;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        _moveRight = false;
        break;
    default:
        break;
    }
}

// 展示动画效果
void CharacterMove::playAnimation() {
    // 动作序列
    if (_moveLeft) {
        _currentDirection = "left";
        _frames = {
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction1.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction2.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction3.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveRight) {
        _currentDirection = "right";
        _frames = {
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction1.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction2.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction3.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveUp && (!_moveRight && !_moveLeft)) {
        _currentDirection = "up";
        _frames = {
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction1.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction2.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction3.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveDown && (!_moveRight && !_moveLeft)) {
        _currentDirection = "down";
        _frames = {
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction1.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction2.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction3.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction4.png", Rect(0, 0, _width, _height))
        };
    }

    // 动画播放
    if (!_frames.empty() && (_currentDirection != _lastDirection)) {
        auto animation = Animation::createWithSpriteFrames(_frames, 1.0f / ACTION_RATE);
        auto animate = Animate::create(animation);
        _character->stopAllActions();
        _character->runAction(RepeatForever::create(animate));
        _animationPlaying = true;
        _lastDirection = _currentDirection;
    }
}

// 更新角色位置
Vec2 CharacterMove::updatePosition(float deltaTime) {
    Vec2 newPosition = _character->getPosition();
    Vec2 moveDirection(0, 0);

    // 移动方向确定
    if (_moveUp) {
        moveDirection.y += 1; // 向上
    }
    if (_moveDown) {
        moveDirection.y -= 1; // 向下
    }
    if (_moveLeft) {
        moveDirection.x -= 1; // 向左
    }
    if (_moveRight) {
        moveDirection.x += 1; // 向右
    }
    if (moveDirection.x != 0 || moveDirection.y != 0) {
        moveDirection.normalize();
        const float currentSpeed = _moveSpeed / sqrtf(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
        newPosition += moveDirection * currentSpeed;
        playAnimation();
    }
    else {
        _character->stopAllActions();
        _animationPlaying = false;
    }

    // 边界检测
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const float halfWidth = _character->getContentSize().width / 2;
    const float halfHeight = _character->getContentSize().height / 2;
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
    _character->setPosition(newPosition);

    return newPosition;
}