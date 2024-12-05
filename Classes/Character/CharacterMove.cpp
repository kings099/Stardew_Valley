/****************************************************************
 * Project Name:  Stardew Valley
<<<<<<< Updated upstream
 * File Name:     Character.cpp
 * File Function: Character���ʵ��
 * Author:        ���ϳ�
<<<<<<<< Updated upstream:Classes/Character/CharacterMove.cpp
 * Update Date:   2023/12/03
=======
 * File Name:     CharacterMove.cpp
 * File Function: CharacterMove���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2023/12/04
>>>>>>> Stashed changes
 * License:       MIT License
 ****************************************************************/

#include "CharacterMove.h"
#include "../proj.win32/Constant.h"


USING_NS_CC;

<<<<<<< Updated upstream
//��������
CharacterMove* CharacterMove::create(const std::string& filename) {
    CharacterMove* ret = new(std::nothrow) CharacterMove();
    if (ret && ret->init(filename)) {
        ret->autorelease();
        return ret;
<<<<<<< Updated upstream
========
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#include "Character.h"

 // ����Character����
Character* Character::create(const std::string& filename) {
    Character* character = new (std::nothrow) Character();
    if (character && character->init(filename)) {
        character->autorelease();
        return character;
>>>>>>>> Stashed changes:Classes/Character/Character.cpp
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

<<<<<<<< Updated upstream:Classes/Character/CharacterMove.cpp
=======
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

>>>>>>> Stashed changes
//��ʼ��
bool CharacterMove::init(const std::string& filename) {
    if (!Node::init()) {
        return false;
    }
    //���ݳ�Ա��ʼ��
<<<<<<< Updated upstream
    moveSpeed = MOVE_SPEED;
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
    animationPlaying = false;
=======
    _moveSpeed = MOVE_SPEED;
    _moveUp = false;
    _moveDown = false;
    _moveLeft = false;
    _moveRight = false;
    _animationPlaying = false;
>>>>>>> Stashed changes
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �������鲢���ó�ʼλ��
<<<<<<< Updated upstream
    character = Sprite::create(filename);
    character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(character);

    // ��ȡ����Ŀ��
    width = character->getContentSize().width;
    height = character->getContentSize().height;
=======
    _character = Sprite::create(filename);
    _character->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(_character);

    // ��ȡ����Ŀ��
    _width = _character->getContentSize().width;
    _height = _character->getContentSize().height;
>>>>>>> Stashed changes

    // ���̼����¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CharacterMove::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(CharacterMove::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

<<<<<<< Updated upstream
    // ÿ֡���½�ɫλ��
    //this->schedule(CC_SCHEDULE_SELECTOR(CharacterMove::updatePosition), 1.0f / FRAME_RATE);
========
// ��ʼ��Character����
bool Character::init(const std::string& filename) {
    if (!CharacterMove::init(filename)) {
        return false;
    }
>>>>>>>> Stashed changes:Classes/Character/Character.cpp

=======
>>>>>>> Stashed changes
    return true;
}
=======
// ���캯��
CharacterMove::CharacterMove() :
    _moveSpeed(CHARACTER_MOVE_SPEED),
    _moveUp(false),
    _moveDown(false),
    _moveLeft(false),
    _moveRight(false),
    _animationPlaying(false),
    _width(CHARACTER_WIDTH),
    _height(CHARACTER_HEIGHT),
    _character(nullptr)
{}

>>>>>>> Stashed changes

// ���¼���ʱ�Ĵ���
<<<<<<< Updated upstream
<<<<<<<< Updated upstream:Classes/Character/CharacterMove.cpp
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
=======
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
>>>>>>> Stashed changes
        break;
    default:
        break;
    }
  
}

// �ͷż���ʱ�Ĵ���
void CharacterMove::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
}

// չʾ����Ч��
void CharacterMove::playAnimation() {
    // ��������
<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
        };
    }

    // ��������
<<<<<<< Updated upstream
    if (!frames.empty()&&(currentDirection != lastDirection)) {
        auto animation = Animation::createWithSpriteFrames(frames, 1.0f / ACTION_RATE);
        auto animate = Animate::create(animation);
        character->stopAllActions();
        character->runAction(RepeatForever::create(animate));
        animationPlaying = true;
        lastDirection = currentDirection; 
=======
    if (!_frames.empty() && (_currentDirection != _lastDirection)) {
        auto animation = Animation::createWithSpriteFrames(_frames, 1.0f / ACTION_RATE);
        auto animate = Animate::create(animation);
        _character->stopAllActions();
        _character->runAction(RepeatForever::create(animate));
        _animationPlaying = true;
        _lastDirection = _currentDirection;
>>>>>>> Stashed changes
    }
}

// ���½�ɫλ��
<<<<<<< Updated upstream
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
=======
cocos2d::Vec2 CharacterMove::updatePosition(float deltaTime) {
    Vec2 newPosition = _character->getPosition();
    Vec2 moveDirection(0, 0);

    // �ƶ�����ȷ��
    if (_moveUp) {
        moveDirection.y += 1; // ����
    }
    if (_moveDown) {
        moveDirection.y -= 1; // ����
    }
    if (_moveLeft) {
        moveDirection.x -= 1; // ����
    }
    if (_moveRight) {
>>>>>>> Stashed changes
        moveDirection.x += 1; // ����
    }
    if (moveDirection.x != 0 || moveDirection.y != 0) {
        moveDirection.normalize();
<<<<<<< Updated upstream
        const float currentSpeed = moveSpeed / sqrtf(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
=======
        const float currentSpeed = _moveSpeed / sqrtf(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
>>>>>>> Stashed changes
        newPosition += moveDirection * currentSpeed;
        playAnimation();
    }
    else {
<<<<<<< Updated upstream
        character->stopAllActions();
        animationPlaying = false;
=======
        _character->stopAllActions();
        _animationPlaying = false;
>>>>>>> Stashed changes
    }

    // �߽���
    const auto visibleSize = Director::getInstance()->getVisibleSize();
<<<<<<< Updated upstream
    const float halfWidth = character->getContentSize().width / 2;
    const float halfHeight = character->getContentSize().height / 2;
=======
    const float halfWidth = _character->getContentSize().width / 2;
    const float halfHeight = _character->getContentSize().height / 2;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    character->setPosition(newPosition);

    return newPosition;
========
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CharacterMove::onKeyPressed(keyCode, event);
}

// �ͷż���ʱ�Ĵ���
void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    CharacterMove::onKeyReleased(keyCode, event);
>>>>>>>> Stashed changes:Classes/Character/Character.cpp
=======
    _character->setPosition(newPosition);

    return newPosition;
>>>>>>> Stashed changes
}