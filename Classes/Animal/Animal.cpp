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
std::unordered_map<std::string, std::vector<std::string>> Animal::resourceMap;
std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> Animal::animationMap;

Animal::Animal()
    : type("chicken"), affection(100.0f), isFed(false), lastFedTime(0.0f),
    affectionDecayRate(1.0f), maxAffection(100.0f), sprite(nullptr), currentAnimation(nullptr),
    areaSize(40.0f), angryIcon(nullptr) {  // 初始化怒气图标为 nullptr
}

Animal::~Animal() {
    // 清理资源
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
}

void Animal::initializeResourceMap() {
    if (!resourceMap.empty()) return;  // 如果资源已经初始化，跳过

    // 初始化小动物资源
    resourceMap["chicken"] = {
        "../Resources/Animals/Chicken/Chicken_0.png",
    };
    resourceMap["cow"] = {
        "../Resources/Animals/Cow/CowFrontAnimation_0.png",
    };

    resourceMap["sheep"] = {
        "../Resources/Animals/Sheep/SheepFrontAnimation_0.png",
    };
}

void Animal::initializeAnimationMap() {
    if (!animationMap.empty()) return;

    // 初始化动画资源
    animationMap["chicken"] = {
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
    
    animationMap["sheep"] = {
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
    
    animationMap["cow"] = {
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

bool Animal::init(const std::string& type, const Vec2& startPosition) {
    if (!Node::init()) {
        return false;
    }

    // 初始化资源
    initializeResourceMap();
    initializeAnimationMap();

    this->type = type;
    this->affection = maxAffection;
    this->isFed = false;
    this->lastFedTime = 0.0f;

    this->origin = startPosition;
    this->position = origin;  // 初始位置设置为传入的原点位置

    // 加载动物的精灵
    if (resourceMap.find(type) == resourceMap.end()) {
        CCLOG("Error: Animal type not found: %s", type.c_str());
        return false;
    }

    sprite = Sprite::create(resourceMap[type][0]);
    if (sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }

    sprite->setPosition(position);
    sprite->setScale(1.0f);
    addChild(sprite);

    // 开始定时更新小动物的位置
    if (this->type == "chicken") {
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

void Animal::feed() {
    isFed = true;
    affection = maxAffection;  // 喂养后好感度恢复到最大值
    lastFedTime = 0.0f;  // 重置喂养时间
    CCLOG("%s is fed!", type.c_str());
}

void Animal::updateAffection(float deltaTime) {
    if (!isFed) {
        lastFedTime += deltaTime;
        affection -= affectionDecayRate * deltaTime;  // 根据时间衰减好感度
        if (affection < 0) affection = 0;

        // 如果好感度降为零，触发发怒函数
        if (isAngry()) {
            handleAngry();
        }
    }
}

bool Animal::isAngry() const {
    return affection == 0;  // 好感度为0则动物发狂
}

void Animal::handleAngry() {
    if (isAngry()) {
        CCLOG("%s is angry!", type.c_str());

        // 如果已经有怒气图标，则不再重复添加
        if (!angryIcon) {
            // 创建怒气图标
            angryIcon = Sprite::create("../Resources/Animals/emotes.png");
            if (angryIcon) {
                // 设置图标位置：相对于动物精灵的头顶
                angryIcon->setPosition(Vec2(sprite->getContentSize().width / 2,
                    sprite->getContentSize().height + 5));
                angryIcon->setScale(0.8f); // 缩小图标尺寸（根据需要调整）

                // 将图标添加为动物精灵的子节点
                sprite->addChild(angryIcon, 1); // z-index = 1，确保在动物精灵上方显示
            }
            else {
                CCLOG("Failed to load angry icon!");
            }
        }
    }
}


float Animal::getAffection() const {
    return affection;
}

const std::string& Animal::getType() const {
    return type;
}

void Animal::playDirectionAnimation(const std::string& direction, int step) {
    // 确保指定方向存在于动画映射表中
    if (animationMap[type].find(direction) != animationMap[type].end()) {
        // 获取当前步数对应的图片路径
        const std::string& framePath = animationMap[type][direction][step];

        // 根据动物类型设置帧大小
        Rect frameRect = (this->type == "chicken") ? Rect(0, 0, 16, 16) : Rect(0, 0, 32, 32);

        // 更新精灵的纹理
        sprite->setTexture(framePath);
        sprite->setTextureRect(frameRect);
    }
}

void Animal::setRandomMovement(float deltaTime) {
    // 随机选择一个方向
    int a;
    if (this->type == "chicken") {
         a = 8;
    }
    else if (this->type == "cow") {
        a = 7;
    }
    else {
        a = 3;
    }
    static int direction = (rand()+a) % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
    static int steps = 0;  // 记录走的步数
    float stepSize = 2.0f;  // 每步移动的距离

    // 时间控制变量
    static float elapsedTime = 0.0f;  // 记录累计时间
    elapsedTime += deltaTime;

    if (elapsedTime >= 0.0f) {  // 每 0.08 秒更新一次帧和移动
        Vec2 newPosition = position;  // 新位置

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
        newPosition.x = std::min(std::max(newPosition.x, origin.x), origin.x + areaSize);
        newPosition.y = std::min(std::max(newPosition.y, origin.y), origin.y + areaSize);

        // 如果位置有改变，更新精灵的位置
        if (newPosition != position) {
            position = newPosition;
            sprite->setPosition(position);
        }

        elapsedTime = 0.0f;  // 重置时间
    }
}

