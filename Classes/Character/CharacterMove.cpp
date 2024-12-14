/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Character.cpp
 * File Function: 角色移动Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/07
 * License:       MIT License
 ****************************************************************/

#include "CharacterMove.h"
#include "Classes/Maps/FarmMap.h"

#include "../proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
CharacterMove::CharacterMove() {}

CharacterMove::CharacterMove(const std::string& filename) :
    _moveSpeed(CHARACTER_MOVE_SPEED),
    _moveUp(false),
    _moveDown(false),
    _moveLeft(false),
    _moveRight(false),
    _width(CHARACTER_WIDTH),
    _height(CHARACTER_HEIGHT),
    _character(nullptr),
    _currentDirection(Down),
    _lastDirection(Down)
{
    // 获取屏幕窗口大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建精灵并设置初始位置
    _character = Sprite::create(filename);
    _character->setAnchorPoint(Vec2(0.5, 0.5));
   // _character->setScale(2.0f);
    _character->setPosition(Vec2(visibleSize.width / 2 + origin.x + _width / 2, visibleSize.height / 2 + origin.y + _height / 2));
    this->cocos2d::Node::addChild(_character);
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
        _currentDirection = Left;
        _frames = {
            SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction1.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction2.png", Rect(0, 0,  _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction3.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveRight) {
        _currentDirection = Right;
        _frames = {
          SpriteFrame::create("../Resources/Characters/Bear/BearRightAction1.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction2.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction3.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveUp) {
        _currentDirection =Up;
        _frames = {
                SpriteFrame::create("../Resources/Characters/Bear/BearUpAction1.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction2.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction3.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveDown) {
        _currentDirection = Down;
        _frames = {
             SpriteFrame::create("../Resources/Characters/Bear/BearDownAction1.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction2.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction3.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearDownAction4.png", Rect(0, 0, _width, _height))
        };
    }

    // 动画播放

    if (!_frames.empty() && (_currentDirection != _lastDirection)) {
        auto animation = Animation::createWithSpriteFrames(_frames, 0.8f / ACTION_RATE);
        auto animate = Animate::create(animation);
        _character->stopAllActions();
        _character->runAction(RepeatForever::create(animate));
        _lastDirection = _currentDirection;
    }
   
}

// 获取角色当前位置
cocos2d::Vec2 CharacterMove::getPosition() {
    return _character->getPosition();
}

// 设置角色位置
void CharacterMove::setPosition(const Vec2& position) {
    _character->setPosition(position);
}

// 强制停止角色移动
void CharacterMove::stopMove() {
    _moveUp = false;
    _moveDown = false;
    _moveLeft = false;
    _moveRight = false;
    _character->stopAllActions();

}

// 更新角色周围瓦片地图信息
void CharacterMove::updateTileInfo(InteractionManager* interactionManager) {
    Vec2 currentPosition = _character->getPosition();
    //interactionManager->updateSurroundingTiles(currentPosition);
    _surroundingTilesInfo = interactionManager->getSurroundingTiles();
}

    // 更新角色位置
cocos2d::Vec2 CharacterMove::updatePosition(float deltaTime) {
    Vec2 currentPosition = _character->getPosition();
    Vec2 nextPosition = currentPosition;
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

    bool isObstacle = false;
    switch (_currentDirection) {
    case Up:
        if (_surroundingTilesInfo[1].isObstacle)
            isObstacle = true;
        break;
    case Down:
        if (_surroundingTilesInfo[7].isObstacle)
            isObstacle = true;
        break;
    case Left:
        if (_surroundingTilesInfo[3].isObstacle)
            isObstacle = true;
        break;
    case Right:
        if (_surroundingTilesInfo[5].isObstacle)
            isObstacle = true;
        break;
    default:
        break;
    }

    if(moveDirection.x != 0 || moveDirection.y != 0) {
        moveDirection.normalize();
        const float currentSpeed = _moveSpeed / sqrtf(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
        nextPosition = currentPosition + moveDirection * currentSpeed;
        playAnimation();
        if (isObstacle)
            nextPosition = currentPosition;
    }
    else {
        nextPosition = currentPosition;
        _character->stopAllActions();
    }
    _character->setPosition(nextPosition);

    return nextPosition;
}