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
    affectionDecayRate(1.0f), maxAffection(100.0f), sprite(nullptr), currentAnimation(nullptr),
    areaSize(40.0f), angryIcon(nullptr) {  // ��ʼ��ŭ��ͼ��Ϊ nullptr
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
    resourceMap["cow"] = {
        "../Resources/Animals/Cow/CowFrontAnimation_0.png",
    };

    resourceMap["sheep"] = {
        "../Resources/Animals/Sheep/SheepFrontAnimation_0.png",
    };
}

void Animal::initializeAnimationMap() {
    if (!animationMap.empty()) return;

    // ��ʼ��������Դ
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
    if (this->type == "chicken") {
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

        // ����øжȽ�Ϊ�㣬������ŭ����
        if (isAngry()) {
            handleAngry();
        }
    }
}

bool Animal::isAngry() const {
    return affection == 0;  // �øж�Ϊ0���﷢��
}

void Animal::handleAngry() {
    if (isAngry()) {
        CCLOG("%s is angry!", type.c_str());

        // ����Ѿ���ŭ��ͼ�꣬�����ظ����
        if (!angryIcon) {
            // ����ŭ��ͼ��
            angryIcon = Sprite::create("../Resources/Animals/emotes.png");
            if (angryIcon) {
                // ����ͼ��λ�ã�����ڶ��ﾫ���ͷ��
                angryIcon->setPosition(Vec2(sprite->getContentSize().width / 2,
                    sprite->getContentSize().height + 5));
                angryIcon->setScale(0.8f); // ��Сͼ��ߴ磨������Ҫ������

                // ��ͼ�����Ϊ���ﾫ����ӽڵ�
                sprite->addChild(angryIcon, 1); // z-index = 1��ȷ���ڶ��ﾫ���Ϸ���ʾ
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
    // ȷ��ָ����������ڶ���ӳ�����
    if (animationMap[type].find(direction) != animationMap[type].end()) {
        // ��ȡ��ǰ������Ӧ��ͼƬ·��
        const std::string& framePath = animationMap[type][direction][step];

        // ���ݶ�����������֡��С
        Rect frameRect = (this->type == "chicken") ? Rect(0, 0, 16, 16) : Rect(0, 0, 32, 32);

        // ���¾��������
        sprite->setTexture(framePath);
        sprite->setTextureRect(frameRect);
    }
}

void Animal::setRandomMovement(float deltaTime) {
    // ���ѡ��һ������
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
    static int steps = 0;  // ��¼�ߵĲ���
    float stepSize = 2.0f;  // ÿ���ƶ��ľ���

    // ʱ����Ʊ���
    static float elapsedTime = 0.0f;  // ��¼�ۼ�ʱ��
    elapsedTime += deltaTime;

    if (elapsedTime >= 0.0f) {  // ÿ 0.08 �����һ��֡���ƶ�
        Vec2 newPosition = position;  // ��λ��

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
        newPosition.x = std::min(std::max(newPosition.x, origin.x), origin.x + areaSize);
        newPosition.y = std::min(std::max(newPosition.y, origin.y), origin.y + areaSize);

        // ���λ���иı䣬���¾����λ��
        if (newPosition != position) {
            position = newPosition;
            sprite->setPosition(position);
        }

        elapsedTime = 0.0f;  // ����ʱ��
    }
}

