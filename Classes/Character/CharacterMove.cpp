/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Character.cpp
 * File Function: 角色移动Character类的实现
 * Author:        尹诚成
 * Update Date:   2023/12/07
 * License:       MIT License
 ****************************************************************/

#include<fstream>
#include "CharacterMove.h"
#include "Classes/Maps/GameMap.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

// 构造函数
CharacterMove::CharacterMove() {}

CharacterMove::CharacterMove(const std::string& filename) :
    _moveSpeed(CHARACTER_MOVE_SPEED),
    _width(CHARACTER_WIDTH),
    _height(CHARACTER_HEIGHT),
    _character(nullptr),
    _moveDirection{false, false, false, false}
{
    // 获取屏幕窗口大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

     // _character->setScale(2.0f);
    if (!loadData("../GameData/CharacterMoveData.dat")) {
        _lastDirection = Down;
        _currentDirection = Down;
        _position = Vec2(visibleSize.width / 2 + origin.x + _width / 2, visibleSize.height / 2 + origin.y + _height / 2);
    }
    // 创建精灵并设置初始位置
    _character = Sprite::create(filename);
    _character->setAnchorPoint(Vec2(0.25, 0.25));
    _character->setPosition(_position);
    this->cocos2d::Node::addChild(_character);
}

// 按下键盘时的处理
void CharacterMove::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        _moveDirection[Up] = true;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        _moveDirection[Down] = true;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _moveDirection[Left] = true;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        _moveDirection[Right] = true;
        break;
    default:
        break;
    }

}

// 释放键盘时的处理
void CharacterMove::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        _moveDirection[Up] = false;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        _moveDirection[Down] = false;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _moveDirection[Left] = false;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        _moveDirection[Right] = false;
        break;
    default:
        break;
    }
    
}

// 展示动画效果
void CharacterMove::playAnimation() {
    // 动作序列
    if (_moveDirection[Left]) {
        _currentDirection = Left;
        _frames = {
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction1.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction2.png", Rect(0, 0,  _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction3.png", Rect(0, 0, _width, _height)),
           SpriteFrame::create("../Resources/Characters/Bear/BearLeftAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveDirection[Right]) {
        _currentDirection = Right;
        _frames = {
          SpriteFrame::create("../Resources/Characters/Bear/BearRightAction1.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction2.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction3.png", Rect(0, 0, _width, _height)),
         SpriteFrame::create("../Resources/Characters/Bear/BearRightAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveDirection[Up]) {
        _currentDirection =Up;
        _frames = {
                SpriteFrame::create("../Resources/Characters/Bear/BearUpAction1.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction2.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction3.png", Rect(0, 0, _width, _height)),
            SpriteFrame::create("../Resources/Characters/Bear/BearUpAction4.png", Rect(0, 0, _width, _height))
        };
    }
    else if (_moveDirection[Down]) {
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
    return _position;
}

// 设置角色位置
void CharacterMove::setPosition(const Vec2& position) {
    _character->setPosition(position);
}

// 强制停止角色移动
void CharacterMove::stopMove() {
    _moveDirection[Up] = false;
    _moveDirection[Down] = false;
    _moveDirection[Left] = false;
    _moveDirection[Right] = false;
    _character->stopAllActions();
}

// 更新角色周围瓦片地图信息
void CharacterMove::updateTileInfo(InteractionManager* interactionManager) {
    _position = _character->getPosition();
    //interactionManager->updateSurroundingTiles(currentPosition);
    _surroundingTilesInfo = interactionManager->getSurroundingTiles();
}

    // 更新角色位置
cocos2d::Vec2 CharacterMove::updatePosition(float deltaTime) {
    _position = _character->getPosition();
    Vec2 nextPosition = _position;
    Vec2 moveDirection(0, 0);

    // 移动方向确定
    if (_moveDirection[Up]) {
        moveDirection.y += 1; // 向上
    }
    if (_moveDirection[Down]) {
        moveDirection.y -= 1; // 向下
    }
    if (_moveDirection[Left]) {
        moveDirection.x -= 1; // 向左
    }
    if (_moveDirection[Right]) {
        moveDirection.x += 1; // 向右
    }

    // 碰撞检测
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

   // GameMap;
    if(moveDirection.x != 0 || moveDirection.y != 0) {
        moveDirection.normalize();
        const float currentSpeed = _moveSpeed / sqrtf(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
        nextPosition = _position + moveDirection * currentSpeed;
        playAnimation();
        if (isObstacle)
            nextPosition = _surroundingTilesInfo[4].WorldPos;
    }
    else {
        nextPosition = _surroundingTilesInfo[4].WorldPos;
        _character->stopAllActions();
    }
    _character->setPosition(nextPosition);
    _position = nextPosition;
    CCLOG("position:(%f,%f)", _position.x, _position.y);
    return nextPosition;
}

// 保存数据
bool CharacterMove::saveData(const std::string& fileName) {
    std::ofstream outFile(fileName, std::ios::binary );
    if (!outFile) {
        CCLOG("Error opening file for writing: %s", fileName.c_str());
        return false;
    }

    outFile.write((char*)&_position, sizeof(_position));
    outFile.write((char*)&_lastDirection, sizeof(_lastDirection));
    outFile.write((char*)&_currentDirection, sizeof(_currentDirection));

    outFile.close();
    return true;
}

// 加载数据
bool CharacterMove::loadData(const std::string& fileName) {
    if (!fileExists(fileName)) {
        CCLOG("File does not exist %s", fileName.c_str());
        return false;
    }

    std::ifstream inFile(fileName, std::ios::binary );
    if (!inFile) {
        CCLOG("File cannot be opened: %s", fileName.c_str());
        return false; 
    }

    inFile.read((char*)&_position, sizeof(_position));
    inFile.read((char*)&_lastDirection, sizeof(_lastDirection));
    inFile.read((char*)&_currentDirection, sizeof(_currentDirection));

    inFile.close();
    return true;
}

// 检查文件是否存在
bool CharacterMove::fileExists(const std::string& fileName) {
    std::ifstream inFile(fileName, std::ios::binary);
    return inFile.good();
}