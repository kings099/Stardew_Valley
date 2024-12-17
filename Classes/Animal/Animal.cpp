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
std::unordered_map<std::string, std::vector<std::string>> Animal::resourceMap;
std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> Animal::animationMap;

Animal::Animal()
    : type("chicken"), affection(100.0f), isFed(false), lastFedTime(0.0f),
    affectionDecayRate(1.0f), maxAffection(100.0f), sprite(nullptr), currentAnimation(nullptr), areaSize(20.0f) {
}

Animal::~Animal() {
    // ������Դ
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
}

void Animal::initializeResourceMap() {
    if (!resourceMap.empty()) return;  // �����Դ�Ѿ���ʼ��������

    // ��ʼ��С������Դ
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

    // ��ʼ��������Դ
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

bool Animal::init(const std::string& type, const Vec2& startPosition) {
    if (!Node::init()) {
        return false;
    }

    // ��ʼ����Դ
    initializeResourceMap();
    initializeAnimationMap();

    this->type = type;
    this->affection = maxAffection;
    this->isFed = false;
    this->lastFedTime = 0.0f;

    this->origin = startPosition;
    this->position = origin;  // ��ʼλ������Ϊ�����ԭ��λ��

    // ���ض���ľ���
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

    // ��ʼ��ʱ����С�����λ��
    schedule([this](float deltaTime) {
        setRandomMovement(deltaTime);  // ����λ��
        }, 1.0f, "move_key");  // ÿ�����һ��

    return true;
}

void Animal::feed() {
    isFed = true;
    affection = maxAffection;  // ι����øжȻָ������ֵ
    lastFedTime = 0.0f;  // ����ι��ʱ��
    CCLOG("%s is fed!", type.c_str());
}

void Animal::updateAffection(float deltaTime) {
    if (!isFed) {
        lastFedTime += deltaTime;
        affection -= affectionDecayRate * deltaTime;  // ����ʱ��˥���øж�
        if (affection < 0) affection = 0;
    }
}

bool Animal::isAngry() const {
    return affection == 0;  // �øж�Ϊ0���﷢��
}

void Animal::handleAngry() {
    if (isAngry()) {
        CCLOG("%s is angry!", type.c_str());
        // ���������Ӷ��﷢��Ķ�������������
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
//        // ���ض�Ӧ�����֡����
//        Vector<SpriteFrame*> frames;
//        for (const auto& framePath : animationMap[type][direction]) {
//            frames.pushBack(SpriteFrame::create(framePath, Rect(0, 0, 16, 16)));  // ����֡��С
//        }
//
//        // ��������
//        Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);  // ÿ֡0.1��
//
//        if (currentAnimation) {
//            sprite->stopAction(currentAnimation);  // ֹͣ�ɵĶ���
//        }
//
//        // ʹ��RepeatForeverȷ�����������ظ����ţ��ö�����߲߱��Ŷ�����
//        currentAnimation = RepeatForever::create(Animate::create(animation));
//        sprite->runAction(currentAnimation);  // ���ж���
//    }
//}
//
//void Animal::setRandomMovement(float deltaTime) {
//    // ���ѡ��һ������
//    int direction = rand() % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
//    float step = 4.0f;  // ����ÿ���ƶ��Ĳ�����ʹ���ƶ�������
//    int repeatCount = 1;  // ÿ�β��ŵĶ����ظ�����������Ը�����Ҫ������
//
//    // ���������Ļص�����
//    auto moveCallback = [this, direction, step, repeatCount](float dt) {
//        Vec2 newPosition = position;  // �µ�λ��
//
//        // ���ݷ������λ��
//        switch (direction) {
//        case 0:  // ����
//            newPosition.y += step;  // ÿ�������ƶ�һ������
//            playDirectionAnimation("up", repeatCount);  // ���������ߵĶ���
//            break;
//        case 1:  // ����
//            newPosition.y -= step;  // ÿ�������ƶ�һ������
//            playDirectionAnimation("down", repeatCount);  // ���������ߵĶ���
//            break;
//        case 2:  // ����
//            newPosition.x -= step;  // ÿ�������ƶ�һ������
//            playDirectionAnimation("left", repeatCount);  // ���������ߵĶ���
//            break;
//        case 3:  // ����
//            newPosition.x += step;  // ÿ�������ƶ�һ������
//            playDirectionAnimation("right", repeatCount);  // ���������ߵĶ���
//            break;
//        }
//
//        // ��֤С������20x20������������
//        newPosition.x = std::min(std::max(newPosition.x, origin.x), origin.x + areaSize);
//        newPosition.y = std::min(std::max(newPosition.y, origin.y), origin.y + areaSize);
//
//        // ���λ���иı䣬�Ÿ���λ�ú;���
//        if (newPosition != position) {
//            position = newPosition;  // ����λ��
//            sprite->setPosition(position);  // ���¾����λ��
//        }
//        };
//
//    // ÿ�ε��� setRandomMovement ʱֱ�ӵ��� Lambda
//    moveCallback(deltaTime);  // ÿ�ε��� setRandomMovement ʱֱ�ӵ��� Lambda
//}
void Animal::playDirectionAnimation(const std::string& direction, int step) {
    if (animationMap[type].find(direction) != animationMap[type].end()) {
        // ���ض�Ӧ�����֡����
        Vector<SpriteFrame*> frames;
        for (const auto& framePath : animationMap[type][direction]) {
            frames.pushBack(SpriteFrame::create(framePath, Rect(0, 0, 16, 16)));  // ����֡��С
        }

        // ��������������ÿ֡ʱ��Ϊ0.15��
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);

        if (currentAnimation) {
            sprite->stopAction(currentAnimation);  // ֹͣ�ɵĶ���
        }

        // ÿ�β����µĶ�����ȷ�����������ظ�����
        currentAnimation = RepeatForever::create(Animate::create(animation));
        sprite->runAction(currentAnimation);  // ���ж���
    }
}

void Animal::setRandomMovement(float deltaTime) {
    // ���ѡ��һ������
    int direction = rand() % 4;  // 0 = up, 1 = down, 2 = left, 3 = right
    float step = 4.0f;  // ÿ���ƶ��Ĳ���
    int repeatCount = 1;  // ÿ�β��ŵĶ����ظ�����������Ը�����Ҫ������

    // ����һ��������������ÿ�����Ĳ�
    int steps = 0;

    // ���������Ļص�����
    auto moveCallback = [this, &direction, step, repeatCount, &steps](float dt) {
        Vec2 newPosition = position;  // �µ�λ��

        // ���ݷ������λ�ò��л�����
        switch (direction) {
        case 0:  // ����
            newPosition.y += step;  // ÿ�������ƶ�һ������
            playDirectionAnimation("up", steps % 4);  // ���������ߵĶ�����������ͬ���Ų�ͬ֡
            break;
        case 1:  // ����
            newPosition.y -= step;  // ÿ�������ƶ�һ������
            playDirectionAnimation("down", steps % 4);  // ���������ߵĶ���
            break;
        case 2:  // ����
            newPosition.x -= step;  // ÿ�������ƶ�һ������
            playDirectionAnimation("left", steps % 4);  // ���������ߵĶ���
            break;
        case 3:  // ����
            newPosition.x += step;  // ÿ�������ƶ�һ������
            playDirectionAnimation("right", steps % 4);  // ���������ߵĶ���
            break;
        }

        // ���²���
        steps++;

        // ��������Ĳ���ֹͣ������ѡһ���µķ���
        if (steps >= 4) {
            steps = 0;  // ��������Ϊ0
            direction = rand() % 4;  // �������ѡ��һ������
        }

        // ��֤С������20x20������������
        newPosition.x = std::min(std::max(newPosition.x, origin.x), origin.x + areaSize);
        newPosition.y = std::min(std::max(newPosition.y, origin.y), origin.y + areaSize);

        // ���λ���иı䣬�Ÿ���λ�ú;���
        if (newPosition != position) {
            position = newPosition;  // ����λ��
            sprite->setPosition(position);  // ���¾����λ��
        }
        };

    // ÿ�ε��� setRandomMovement ʱֱ�ӵ��� Lambda
    moveCallback(deltaTime);  // ÿ�ε��� setRandomMovement ʱֱ�ӵ��� Lambda
}


