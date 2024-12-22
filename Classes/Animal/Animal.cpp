/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animal.cpp
 * File Function: С�����࣬ʵ��С����ĸ��ֻ�������
 * Author:        ������
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#include "Animal.h"

USING_NS_CC;

// ��ʼ����̬����
std::unordered_map<std::string, std::vector<std::string>> Animal::_resourceMap;
std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> Animal::_animationMap;

Animal::Animal()
    : _type("chicken"), _affection(100.0f), _isFed(false), _lastFedTime(0.0f),
    _affectionDecayRate(1.0f), _maxAffection(100.0f), _sprite(nullptr), _currentAnimation(nullptr),
    _areaSize(40.0f), _angryIcon(nullptr) {  // ��ʼ��ŭ��ͼ��Ϊ nullptr
}

Animal::~Animal() {
    // ������Դ
    if (_sprite) {
        _sprite->removeFromParent();
        _sprite = nullptr;
    }
}

void Animal::initializeResourceMap() {
    if (!_resourceMap.empty()) return;  // �����Դ�Ѿ���ʼ��������

    // ��ʼ��С������Դ
    _resourceMap["chicken"] = {
        "../Resources/Animals/Chicken/Chicken_0.png",
    };
    _resourceMap["cow"] = {
        "../Resources/Animals/Cow/CowFrontAnimation_0.png",
    };

    _resourceMap["sheep"] = {
        "../Resources/Animals/Sheep/SheepFrontAnimation_0.png",
    };
}

void Animal::initializeAnimationMap() {
    if (!_animationMap.empty()) return;

    // ��ʼ��������Դ
    _animationMap["chicken"] = {
        {"up", {"../Resources/Animals/Chicken/ChickenBackAction_1.png",
            "../Resources/Animals/Chicken/ChickenBackAction_2.png",
            "../Resources/Animals/Chicken/ChickenBackAction_3.png",
            "../Resources/Animals/Chicken/ChickenBackAction_4.png"}},

        {"down", {"../Resources/Animals/Chicken/ChickenFrontAction_1.png",
        "../Resources/Animals/Chicken/ChickenFrontAction_2.png",
        "../Resources/Animals/Chicken/ChickenFrontAction_3.png",
        "../Resources/Animals/Chicken/ChickenFrontAction_4.png"}},

        {"left", {"../Resources/Animals/Chicken/ChickenLeftAction_1.png",
        "../Resources/Animals/Chicken/ChickenLeftAction_2.png",
        "../Resources/Animals/Chicken/ChickenLeftAction_3.png",
        "../Resources/Animals/Chicken/ChickenLeftAction_4.png"}},

        {"right", {"../Resources/Animals/Chicken/ChickenRightAction_1.png",
       "../Resources/Animals/Chicken/ChickenRightAction_2.png",
        "../Resources/Animals/Chicken/ChickenRightAction_3.png",
       "../Resources/Animals/Chicken/ChickenRightAction_4.png"}}
    };
    
    _animationMap["sheep"] = {
        {"up", {"../Resources/Animals/Sheep/SheepBackAnimation_0.png",
            "../Resources/Animals/Sheep/SheepBackAnimation_1.png",
            "../Resources/Animals/Sheep/SheepBackAnimation_2.png",
            "../Resources/Animals/Sheep/SheepBackAnimation_3.png" }},

         {"down", {"../Resources/Animals/Sheep/SheepFrontAnimation_0.png",
        "../Resources/Animals/Sheep/SheepFrontAnimation_1.png",
        "../Resources/Animals/Sheep/SheepFrontAnimation_2.png",
        "../Resources/Animals/Sheep/SheepFrontAnimation_3.png"}},

        {"left", {"../Resources/Animals/Sheep/SheepLeftAnimation_0.png",
        "../Resources/Animals/Sheep/SheepLeftAnimation_1.png",
        "../Resources/Animals/Sheep/SheepLeftAnimation_2.png",
        "../Resources/Animals/Sheep/SheepLeftAnimation_3.png"}},

        {"right", {"../Resources/Animals/Sheep/SheepRightAnimation_0.png",
        "../Resources/Animals/Sheep/SheepRightAnimation_1.png",
        "../Resources/Animals/Sheep/SheepRightAnimation_2.png",
        "../Resources/Animals/Sheep/SheepRightAnimation_3.png"}}
    };
    
    _animationMap["cow"] = {
        {"up",  {"../Resources/Animals/Cow/CowBackAnimation_0.png",
        "../Resources/Animals/Cow/CowBackAnimation_1.png",
        "../Resources/Animals/Cow/CowBackAnimation_2.png",
        "../Resources/Animals/Cow/CowBackAnimation_3.png"}},

        {"down", {"../Resources/Animals/Cow/CowFrontAnimation_0.png",
            "../Resources/Animals/Cow/CowFrontAnimation_1.png",
            "../Resources/Animals/Cow/CowFrontAnimation_2.png",
            "../Resources/Animals/Cow/CowFrontAnimation_3.png"}},

        {"left", {"../Resources/Animals/Cow/CowLeftAnimation_0.png",
        "../Resources/Animals/Cow/CowLeftAnimation_1.png",
        "../Resources/Animals/Cow/CowLeftAnimation_2.png",
        "../Resources/Animals/Cow/CowLeftAnimation_3.png"}},

        {"right", {"../Resources/Animals/Cow/CowRightAnimation_0.png",
        "../Resources/Animals/Cow/CowRightAnimation_1.png",
        "../Resources/Animals/Cow/CowRightAnimation_2.png",
        "../Resources/Animals/Cow/CowRightAnimation_3.png"}}
    };
   
    // Ϊ��������������Ƶ���Դ
}

Animal* Animal::create(const std::string& type, const Vec2& startPosition) {
    Animal* ret = new Animal();
    if (ret && ret->init(type, startPosition)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//��ʼ��С������Ϣ
bool Animal::init(const std::string& type, const Vec2& startPosition) {
    if (!Node::init()) {
        return false;
    }

    // ��ʼ����Դ
    initializeResourceMap();
    initializeAnimationMap();

    this->_type = type;
    this->_affection = _maxAffection;
    this->_isFed = false;
    this->_lastFedTime = 0.0f;

    this->_origin = startPosition;
    this->_position = _origin;  // ��ʼλ������Ϊ�����ԭ��λ��

    // ���ض���ľ���
    if (_resourceMap.find(type) == _resourceMap.end()) {
        CCLOG("Error: Animal type not found: %s", type.c_str());
        return false;
    }

    _sprite = Sprite::create(_resourceMap[type][0]);
    if (_sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }

    _sprite->setPosition(_position);
    _sprite->setScale(ANIMAL_RATIO);
    addChild(_sprite);

    // ��ʼ��ʱ����С�����λ��
    if (this->_type == "chicken") {
        schedule([this](float deltaTime) {
            setRandomMovement(deltaTime);  // ����λ��
            }, 0.4f, "move_key");  // ÿ0.3�����һ��

    }
    else {
        schedule([this](float deltaTime) {
            setRandomMovement(deltaTime);  // ����λ��
            }, 0.7f, "move_key");  // ÿ0.3�����һ��

    }

    schedule([this](float deltaTime) {
        updateAffection(deltaTime);  // ���ºøж�
        }, 1.0f, "affection_key");  // ÿ1�����һ�κøж�

}

//ι�������ι������
void Animal::feed() {
    _isFed = true;
    _affection = _maxAffection;  // ι����øжȻָ������ֵ
    _lastFedTime = 0.0f;  // ����ι��ʱ��
    CCLOG("%s is fed!", _type.c_str());
}

//���¶���øж�
void Animal::updateAffection(float deltaTime) {
    if (!_isFed) {
        _lastFedTime += deltaTime;
        _affection -= _affectionDecayRate * deltaTime;  // ����ʱ��˥���øж�
        if (_affection < 0) _affection = 0;

        // ����øжȽ�Ϊ�㣬������ŭ����
        if (isAngry()) {
            handleAngry();
        }
    }
}

//���ض����Ƿ�ŭ���ж�
bool Animal::isAngry() const {
    return _affection == 0;  // �øж�Ϊ0���﷢��
}

//��ʾ���﷢ŭͼ�꣨!��
void Animal::handleAngry() {
    if (isAngry()) {
        CCLOG("%s is angry!", _type.c_str());

        // ����Ѿ���ŭ��ͼ�꣬�����ظ����
        if (!_angryIcon) {
            // ����ŭ��ͼ��
            _angryIcon = Sprite::create("../Resources/Animals/emotes.png");
            if (_angryIcon) {
                // ����ͼ��λ�ã�����ڶ��ﾫ���ͷ��
                _angryIcon->setPosition(Vec2(_sprite->getContentSize().width / 2,
                    _sprite->getContentSize().height + 5));
                _angryIcon->setScale(ANGRY_ICON_RATIO); // ��Сͼ��ߴ磨������Ҫ������

                // ��ͼ�����Ϊ���ﾫ����ӽڵ�
                _sprite->addChild(_angryIcon, 1); // z-index = 1��ȷ���ڶ��ﾫ���Ϸ���ʾ
            }
            else {
                CCLOG("Failed to load angry icon!");
            }
        }
    }
}

//��ȡ��ǰ����ĺøж�
float Animal::getAffection() const {
    return _affection;
}

//��ȡ��ǰ���������
const std::string& Animal::getType() const {
    return _type;
}

//���Ŷ������߶���
void Animal::playDirectionAnimation(const std::string& direction, int step) {
    // ȷ��ָ����������ڶ���ӳ�����
    if (_animationMap[_type].find(direction) != _animationMap[_type].end()) {
        // ��ȡ��ǰ������Ӧ��ͼƬ·��
        const std::string& framePath = _animationMap[_type][direction][step];

        // ���ݶ�����������֡��С
        Rect frameRect = (this->_type == "chicken") ? Rect(0, 0, 16, 16) : Rect(0, 0, 32, 32);

        // ���¾��������
        _sprite->setTexture(framePath);
        _sprite->setTextureRect(frameRect);
    }
}

//���õ�ǰ��������ƶ��ķ���
void Animal::setRandomMovement(float deltaTime) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(0)));
        seeded = true;
    }
    static int direction = (rand()) % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
    static int steps = 0;  // ��¼�ߵĲ���
    float stepSize = 2.0f;  // ÿ���ƶ��ľ���

    // ʱ����Ʊ���
    static float elapsedTime = 0.0f;  // ��¼�ۼ�ʱ��
    elapsedTime += deltaTime;

    if (elapsedTime >= 0.0f) {  // ÿ 0.08 �����һ��֡���ƶ�
        Vec2 newPosition = _position;  // ��λ��

        // ���ݷ������λ�ú;���ͼƬ
        switch (direction) {
        case 0:  // ����
            newPosition.y += stepSize;
            playDirectionAnimation("up", steps % 4);  // ���µ�ǰ֡ͼƬ
            break;
        case 1:  // ����
            newPosition.y -= stepSize;
            playDirectionAnimation("down", steps % 4);
            break;
        case 2:  // ����
            newPosition.x -= stepSize;
            playDirectionAnimation("left", steps % 4);
            break;
        case 3:  // ����
            newPosition.x += stepSize;
            playDirectionAnimation("right", steps % 4);
            break;
        }

        // ���²����ͷ���
        steps++;
        if (steps >= 8) {  // ����4��������ѡ����
            steps = 0;
            direction = rand() % 4;  // ���ѡ���·���
        }

        // ��֤С������ 20x20 ������������
        newPosition.x = std::min(std::max(newPosition.x, _origin.x), _origin.x + _areaSize);
        newPosition.y = std::min(std::max(newPosition.y, _origin.y), _origin.y + _areaSize);

        // ���λ���иı䣬���¾����λ��
        if (newPosition != _position) {
            _position = newPosition;
            _sprite->setPosition(_position);
        }

        elapsedTime = 0.0f;  // ����ʱ��
    }
}

