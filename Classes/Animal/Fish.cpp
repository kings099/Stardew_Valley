/****************************************************************
 * Project Name:  FishWorld
 * File Name:     Fish.cpp
 * File Function: 鱼类，处理鱼的生成、活动范围和季节性钓鱼
 * Author:        胡宝怡
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/

#include "Fish.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

USING_NS_CC;

std::unordered_map<std::string, std::vector<std::string>> Fishs::seasonFishMap;  // 静态成员变量定义

Fishs::Fishs()
    : name("defaultFish"), season("spring"), activityRange(50.0f), sprite(nullptr),
    currentAnimation(nullptr), moveDirection(1) {  // 1表示向右，-1表示向左
}

Fishs::~Fishs() {
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
}

//初始化每个季节的鱼的类型
void Fishs::initializeSeasonFishMap() {
    if (!seasonFishMap.empty()) return;

    seasonFishMap["spring"] = { "fishSpring_0", "fishSpring_1", "fishSpring_2", "fishSpring_3" };
    seasonFishMap["summer"] = { "fishSummer_0", "fishSummer_1", "fishSpring_0", "fishSpring_1" };
    seasonFishMap["fall"] = { "fishFall_0", "fishFall_1", "fishSpring_2", "fishSpring_3" };
    seasonFishMap["winter"] = { "fishWinter_0", "fishWinter_1", "fishSpring_1", "fishSpring_2" };
}

//创建并返回一个新的 Fishs 对象。
Fishs* Fishs::create(const std::string& name, const std::string& season, const Vec2& position) {
    Fishs* ret = new Fishs();
    if (ret && ret->init(name, season, position)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//初始化鱼的各种信息
bool Fishs::init(const std::string& name, const std::string& season, const Vec2& position) {
    if (!Node::init()) {
        return false;
    }

    this->name = name;
    this->season = season;
    this->position = position;
    this->initialPosition = position;  // 保存初始位置

    // 加载鱼的初始精灵
    string fishImagePath = "../Resources/Animals/Fish/" + name + ".png";
    sprite = Sprite::create(fishImagePath);
    if (!sprite) {
        CCLOG("Error: Failed to load fish sprite for %s", name.c_str());
        return false;
    }
    sprite->setPosition(position);
    sprite->setScale(1.0f);
    this->addChild(sprite);

    // 启动随机移动和动画更新
    schedule([this](float deltaTime) {
        moveRandomly(deltaTime);
        }, 0.8f, "move_key");

    return true;
}

//设置每种鱼的活动范围
void Fishs::setActivityRange(float range) {
    this->activityRange = range;
}

//获取当前这种鱼的图片的资源路径
std::string Fishs::getFishImagePath() const {
    return "../Resources/Animals/Fish/" + name + ".png";
}

//随机决定现在鱼的移动方向
void Fishs::moveRandomly(float deltaTime) {
    // 随机决定鱼的移动方向，向左（-1）或向右（1）
    if (rand() % 100 < 5) {  // 5% 概率改变方向
        moveDirection = (moveDirection == 1) ? -1 : 1;
    }

    // 随机生成横向位移
    float dx = moveDirection * (rand() % 10 + 5) * deltaTime;  // 随机的横向位移
    float newX = position.x + dx;

    // 随机生成纵向位移
    float dy = (rand() % 3 - 1) * (rand() % 10 + 5) * deltaTime;  // 随机的纵向位移 (-1, 0, 1)
    float newY = position.y + dy;

    // 限制新的位置在初始位置的 40*40 矩形范围内
    if (newX < initialPosition.x - 20) newX = initialPosition.x - 20;
    if (newX > initialPosition.x + 20) newX = initialPosition.x + 20;
    if (newY < initialPosition.y - 20) newY = initialPosition.y - 20;
    if (newY > initialPosition.y + 20) newY = initialPosition.y + 20;

    // 更新位置
    position.x = newX;
    position.y = newY;
    sprite->setPosition(position);

    // 更新动画
    updateAnimation();
}

//鱼往左或往右的动画
void Fishs::updateAnimation() {
    if (!sprite) {
        CCLOG("Error: Sprite is nullptr, cannot update animation.");
        return;
    }

    // 清除旧的动画动作
    sprite->stopAllActions();

    // 动画帧路径
    std::vector<std::string> framePaths;
    if (moveDirection == 1) {  // 向右游动
        framePaths = {
            "../Resources/Animals/Fish/" + name + ".png",
            "../Resources/Animals/Fish/" + name + "_Right_1.png"
        };
    }
    else {  // 向左游动
        framePaths = {
            "../Resources/Animals/Fish/" + name + "_Left_0.png",
            "../Resources/Animals/Fish/" + name + "_Left_1.png"
        };
    }

    // 加载帧
    Vector<SpriteFrame*> frames = loadFrames(framePaths, Rect(0, 0, 64, 64));  // 假设帧尺寸为 64x64
    if (frames.empty()) {
        CCLOG("Error: No frames loaded for fish animation.");
        return;
    }

    auto animation = Animation::createWithSpriteFrames(frames, 0.97f);
    auto animate = Animate::create(animation);

    sprite->runAction(RepeatForever::create(animate));
}

//该函数根据给定的帧路径和帧矩形区域，从每个路径加载纹理，并创建相应的精灵帧。它会将成功加载的精灵帧添加到一个 `Vector<SpriteFrame*>` 容器中并返回。
Vector<SpriteFrame*> Fishs::loadFrames(const std::vector<std::string>& framePaths, const Rect& frameRect) {
    Vector<SpriteFrame*> frames;

    for (const auto& path : framePaths) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(path);
        if (!texture) {
            CCLOG("Error: Failed to load texture from path %s", path.c_str());
            continue;
        }

        auto frame = SpriteFrame::createWithTexture(texture, frameRect);
        if (!frame) {
            CCLOG("Error: Failed to create SpriteFrame from texture %s", path.c_str());
            continue;
        }

        frames.pushBack(frame);
    }

    return frames;
}

//钓鱼函数，返回当前钓的鱼的类型
std::string Fishs::catchFish(const std::string& season) {
    initializeSeasonFishMap();

    if (seasonFishMap.find(season) == seasonFishMap.end()) {
        CCLOG("Error: Invalid season %s", season.c_str());
        return "";
    }

    const std::vector<std::string>& fishList = seasonFishMap[season];
    if (rand() % 100 < 10) {
        CCLOG("No fish caught in this season.");
        return "";
    }

    int randomIndex = rand() % fishList.size();
    return fishList[randomIndex];
}
