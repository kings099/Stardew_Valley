/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animal.cpp
 * File Function: 小动物类，实现小动物的各种基本操作
 * Author:        胡宝怡
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#include "Animal.h"

USING_NS_CC;

// 初始化静态变量
std::unordered_map<std::string, std::vector<std::string>> Animal::_resourceMap;
std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> Animal::_animationMap;

Animal::Animal()
    : _type("chicken"), _affection(100.0f), _isFed(false), _lastFedTime(0.0f),
    _affectionDecayRate(1.0f), _maxAffection(100.0f), _sprite(nullptr), _currentAnimation(nullptr),
    _areaSize(40.0f), _angryIcon(nullptr) {  // 初始化怒气图标为 nullptr
}

Animal::~Animal() {
    // 清理资源
    if (_sprite) {
        _sprite->removeFromParent();
        _sprite = nullptr;
    }
}

void Animal::initializeResourceMap() {
    if (!_resourceMap.empty()) return;  // 如果资源已经初始化，跳过

    // 初始化小动物资源
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

    // 初始化动画资源
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
   
    // 为其他动物添加类似的资源
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

//初始化小动物信息
bool Animal::init(const std::string& type, const Vec2& startPosition) {
    if (!Node::init()) {
        return false;
    }

    // 初始化资源
    initializeResourceMap();
    initializeAnimationMap();

    this->_type = type;
    this->_affection = _maxAffection;
    this->_isFed = false;
    this->_lastFedTime = 0.0f;

    this->_origin = startPosition;
    this->_position = _origin;  // 初始位置设置为传入的原点位置

    // 加载动物的精灵
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

    // 开始定时更新小动物的位置
    if (this->_type == "chicken") {
        schedule([this](float deltaTime) {
            setRandomMovement(deltaTime);  // 更新位置
            }, 0.4f, "move_key");  // 每0.3秒更新一次

    }
    else {
        schedule([this](float deltaTime) {
            setRandomMovement(deltaTime);  // 更新位置
            }, 0.7f, "move_key");  // 每0.3秒更新一次

    }

    schedule([this](float deltaTime) {
        updateAffection(deltaTime);  // 更新好感度
        }, 1.0f, "affection_key");  // 每1秒更新一次好感度

}

//喂养后调用喂养函数
void Animal::feed() {
    _isFed = true;
    _affection = _maxAffection;  // 喂养后好感度恢复到最大值
    _lastFedTime = 0.0f;  // 重置喂养时间
    CCLOG("%s is fed!", _type.c_str());
}

//更新动物好感度
void Animal::updateAffection(float deltaTime) {
    if (!_isFed) {
        _lastFedTime += deltaTime;
        _affection -= _affectionDecayRate * deltaTime;  // 根据时间衰减好感度
        if (_affection < 0) _affection = 0;

        // 如果好感度降为零，触发发怒函数
        if (isAngry()) {
            handleAngry();
        }
    }
}

//返回动物是否发怒的判断
bool Animal::isAngry() const {
    return _affection == 0;  // 好感度为0则动物发狂
}

//显示动物发怒图标（!）
void Animal::handleAngry() {
    if (isAngry()) {
        CCLOG("%s is angry!", _type.c_str());

        // 如果已经有怒气图标，则不再重复添加
        if (!_angryIcon) {
            // 创建怒气图标
            _angryIcon = Sprite::create("../Resources/Animals/emotes.png");
            if (_angryIcon) {
                // 设置图标位置：相对于动物精灵的头顶
                _angryIcon->setPosition(Vec2(_sprite->getContentSize().width / 2,
                    _sprite->getContentSize().height + 5));
                _angryIcon->setScale(ANGRY_ICON_RATIO); // 缩小图标尺寸（根据需要调整）

                // 将图标添加为动物精灵的子节点
                _sprite->addChild(_angryIcon, 1); // z-index = 1，确保在动物精灵上方显示
            }
            else {
                CCLOG("Failed to load angry icon!");
            }
        }
    }
}

//获取当前动物的好感度
float Animal::getAffection() const {
    return _affection;
}

//获取当前动物的类型
const std::string& Animal::getType() const {
    return _type;
}

//播放动物行走动画
void Animal::playDirectionAnimation(const std::string& direction, int step) {
    // 确保指定方向存在于动画映射表中
    if (_animationMap[_type].find(direction) != _animationMap[_type].end()) {
        // 获取当前步数对应的图片路径
        const std::string& framePath = _animationMap[_type][direction][step];

        // 根据动物类型设置帧大小
        Rect frameRect = (this->_type == "chicken") ? Rect(0, 0, 16, 16) : Rect(0, 0, 32, 32);

        // 更新精灵的纹理
        _sprite->setTexture(framePath);
        _sprite->setTextureRect(frameRect);
    }
}

//设置当前动物随机移动的方向
void Animal::setRandomMovement(float deltaTime) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(0)));
        seeded = true;
    }
    static int direction = (rand()) % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
    static int steps = 0;  // 记录走的步数
    float stepSize = 2.0f;  // 每步移动的距离

    // 时间控制变量
    static float elapsedTime = 0.0f;  // 记录累计时间
    elapsedTime += deltaTime;

    if (elapsedTime >= 0.0f) {  // 每 0.08 秒更新一次帧和移动
        Vec2 newPosition = _position;  // 新位置

        // 根据方向更新位置和精灵图片
        switch (direction) {
        case 0:  // 向上
            newPosition.y += stepSize;
            playDirectionAnimation("up", steps % 4);  // 更新当前帧图片
            break;
        case 1:  // 向下
            newPosition.y -= stepSize;
            playDirectionAnimation("down", steps % 4);
            break;
        case 2:  // 向左
            newPosition.x -= stepSize;
            playDirectionAnimation("left", steps % 4);
            break;
        case 3:  // 向右
            newPosition.x += stepSize;
            playDirectionAnimation("right", steps % 4);
            break;
        }

        // 更新步数和方向
        steps++;
        if (steps >= 8) {  // 走满4步后重新选择方向
            steps = 0;
            direction = rand() % 4;  // 随机选择新方向
        }

        // 保证小动物在 20x20 正方形区域内
        newPosition.x = std::min(std::max(newPosition.x, _origin.x), _origin.x + _areaSize);
        newPosition.y = std::min(std::max(newPosition.y, _origin.y), _origin.y + _areaSize);

        // 如果位置有改变，更新精灵的位置
        if (newPosition != _position) {
            _position = newPosition;
            _sprite->setPosition(_position);
        }

        elapsedTime = 0.0f;  // 重置时间
    }
}

