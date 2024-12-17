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
    affectionDecayRate(1.0f), maxAffection(100.0f), sprite(nullptr), currentAnimation(nullptr), areaSize(20.0f) {
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
   /* resourceMap["cow"] = {
        "../Resources/Animals/Cow/cow_0.png",
        "../Resources/Animals/Cow/cow_1.png"
    };

    resourceMap["sheep"] = {
        "../Resources/Animals/Sheep/sheep_0.png",
        "../Resources/Animals/Sheep/sheep_1.png"
    };*/
}

void Animal::initializeAnimationMap() {
    if (!animationMap.empty()) return;

    // 初始化动画资源
    animationMap["chicken"] = {
        {"up", {"../Resources/Animals/Chicken/ChickenFrontAction_1.png", 
        "../Resources/Animals/Chicken/ChickenFrontAction_2.png",
        "../Resources/Animals/Chicken/ChickenFrontAction_3.png",
        "../Resources/Animals/Chicken/ChickenFrontAction_4.png"}},

        {"down", {"../Resources/Animals/Chicken/ChickenBackAction_1.png", 
        "../Resources/Animals/Chicken/ChickenBackAction_2.png",
        "../Resources/Animals/Chicken/ChickenBackAction_3.png",
        "../Resources/Animals/Chicken/ChickenBackAction_4.png"}},

        {"left", {"../Resources/Animals/Chicken/ChickenLeftAction_1.png",
        "../Resources/Animals/Chicken/ChickenLeftAction_2.png",
        "../Resources/Animals/Chicken/ChickenLeftAction_3.png",
        "../Resources/Animals/Chicken/ChickenLeftAction_4.png"}},

        {"right", {"../Resources/Animals/Chicken/ChickenRightAction_1.png",
       "../Resources/Animals/Chicken/ChickenRightAction_2.png",
        "../Resources/Animals/Chicken/ChickenRightAction_3.png",
       "../Resources/Animals/Chicken/ChickenRightAction_4.png"}}
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
    schedule([this](float deltaTime) {
        setRandomMovement(deltaTime);  // 更新位置
        }, 1.0f, "move_key");  // 每秒更新一次

    return true;
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
    }
}

bool Animal::isAngry() const {
    return affection == 0;  // 好感度为0则动物发狂
}

void Animal::handleAngry() {
    if (isAngry()) {
        CCLOG("%s is angry!", type.c_str());
        // 这里可以添加动物发狂的动画或其他表现
    }
}

float Animal::getAffection() const {
    return affection;
}

const std::string& Animal::getType() const {
    return type;
}

//void Animal::playDirectionAnimation(const std::string& direction, int repeatCount) {
//    if (animationMap[type].find(direction) != animationMap[type].end()) {
//        // 加载对应方向的帧动画
//        Vector<SpriteFrame*> frames;
//        for (const auto& framePath : animationMap[type][direction]) {
//            frames.pushBack(SpriteFrame::create(framePath, Rect(0, 0, 16, 16)));  // 动画帧大小
//        }
//
//        // 创建动画
//        Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);  // 每帧0.1秒
//
//        if (currentAnimation) {
//            sprite->stopAction(currentAnimation);  // 停止旧的动画
//        }
//
//        // 使用RepeatForever确保动画不断重复播放（让动物边走边播放动画）
//        currentAnimation = RepeatForever::create(Animate::create(animation));
//        sprite->runAction(currentAnimation);  // 运行动画
//    }
//}
//
//void Animal::setRandomMovement(float deltaTime) {
//    // 随机选择一个方向
//    int direction = rand() % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
//    float step = 4.0f;  // 增大每次移动的步长，使得移动更明显
//    int repeatCount = 1;  // 每次播放的动画重复次数（这可以根据需要调整）
//
//    // 创建动画的回调函数
//    auto moveCallback = [this, direction, step, repeatCount](float dt) {
//        Vec2 newPosition = position;  // 新的位置
//
//        // 根据方向更新位置
//        switch (direction) {
//        case 0:  // 向上
//            newPosition.y += step;  // 每步向上移动一定距离
//            playDirectionAnimation("up", repeatCount);  // 播放向上走的动画
//            break;
//        case 1:  // 向下
//            newPosition.y -= step;  // 每步向下移动一定距离
//            playDirectionAnimation("down", repeatCount);  // 播放向下走的动画
//            break;
//        case 2:  // 向左
//            newPosition.x -= step;  // 每步向左移动一定距离
//            playDirectionAnimation("left", repeatCount);  // 播放向左走的动画
//            break;
//        case 3:  // 向右
//            newPosition.x += step;  // 每步向右移动一定距离
//            playDirectionAnimation("right", repeatCount);  // 播放向右走的动画
//            break;
//        }
//
//        // 保证小动物在20x20正方形区域内
//        newPosition.x = std::min(std::max(newPosition.x, origin.x), origin.x + areaSize);
//        newPosition.y = std::min(std::max(newPosition.y, origin.y), origin.y + areaSize);
//
//        // 如果位置有改变，才更新位置和精灵
//        if (newPosition != position) {
//            position = newPosition;  // 更新位置
//            sprite->setPosition(position);  // 更新精灵的位置
//        }
//        };
//
//    // 每次调用 setRandomMovement 时直接调用 Lambda
//    moveCallback(deltaTime);  // 每次调用 setRandomMovement 时直接调用 Lambda
//}
void Animal::playDirectionAnimation(const std::string& direction, int step) {
    if (animationMap[type].find(direction) != animationMap[type].end()) {
        // 加载对应方向的帧动画
        Vector<SpriteFrame*> frames;
        for (const auto& framePath : animationMap[type][direction]) {
            frames.pushBack(SpriteFrame::create(framePath, Rect(0, 0, 16, 16)));  // 动画帧大小
        }

        // 创建动画，设置每帧时间为0.15秒
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);

        if (currentAnimation) {
            sprite->stopAction(currentAnimation);  // 停止旧的动画
        }

        // 每次播放新的动画，确保动画不断重复播放
        currentAnimation = RepeatForever::create(Animate::create(animation));
        sprite->runAction(currentAnimation);  // 运行动画
    }
}

void Animal::setRandomMovement(float deltaTime) {
    // 随机选择一个方向
    int direction = rand() % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
    float step = 4.0f;  // 每次移动的步长
    int repeatCount = 1;  // 每次播放的动画重复次数（这可以根据需要调整）

    // 定义一个步数计数器，每次走四步
    int steps = 0;

    // 创建动画的回调函数
    auto moveCallback = [this, &direction, step, repeatCount, &steps](float dt) {
        Vec2 newPosition = position;  // 新的位置

        // 根据方向更新位置并切换动画
        switch (direction) {
        case 0:  // 向上
            newPosition.y += step;  // 每步向上移动一定距离
            playDirectionAnimation("up", steps % 4);  // 播放向上走的动画，步数不同播放不同帧
            break;
        case 1:  // 向下
            newPosition.y -= step;  // 每步向下移动一定距离
            playDirectionAnimation("down", steps % 4);  // 播放向下走的动画
            break;
        case 2:  // 向左
            newPosition.x -= step;  // 每步向左移动一定距离
            playDirectionAnimation("left", steps % 4);  // 播放向左走的动画
            break;
        case 3:  // 向右
            newPosition.x += step;  // 每步向右移动一定距离
            playDirectionAnimation("right", steps % 4);  // 播放向右走的动画
            break;
        }

        // 更新步数
        steps++;

        // 如果走了四步，停止动画并选一个新的方向
        if (steps >= 4) {
            steps = 0;  // 步数重置为0
            direction = rand() % 4;  // 重新随机选择一个方向
        }

        // 保证小动物在20x20正方形区域内
        newPosition.x = std::min(std::max(newPosition.x, origin.x), origin.x + areaSize);
        newPosition.y = std::min(std::max(newPosition.y, origin.y), origin.y + areaSize);

        // 如果位置有改变，才更新位置和精灵
        if (newPosition != position) {
            position = newPosition;  // 更新位置
            sprite->setPosition(position);  // 更新精灵的位置
        }
        };

    // 每次调用 setRandomMovement 时直接调用 Lambda
    moveCallback(deltaTime);  // 每次调用 setRandomMovement 时直接调用 Lambda
}


