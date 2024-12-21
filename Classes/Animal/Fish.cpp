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

std::unordered_map<Season, std::vector<std::string>> Fishs::_seasonFishMap;  // 静态成员变量定义

Fishs::Fishs()
    : _name("defaultFish"), _season("spring"), _activityRange(50.0f), _sprite(nullptr),
    _currentAnimation(nullptr), _moveDirection(1) {  // 1表示向右，-1表示向左
}

Fishs::~Fishs() {
    if (_sprite) {
        _sprite->removeFromParent();
        _sprite = nullptr;
    }
}

//初始化每个季节的鱼的类型
void Fishs::initializeSeasonFishMap() {
    if (!_seasonFishMap.empty()) return;
    _seasonFishMap[Spring] = { "Bigeye", "LargemouthBass", "Salmon"};// 春季：大眼鱼，大嘴鲈鱼，鲑鱼
    _seasonFishMap[Summer] = { "Squid", "Sardines", "Herring" };// 夏季：鱿鱼，沙丁鱼，鲱鱼
    _seasonFishMap[Fall] =   { "RedMullet", "Carps", "Octopuses"};// 秋季：红鲻鱼，鲤鱼，章鱼
    _seasonFishMap[Winter] = { "RedSnapper", "SmallmouthBass", "TunaFish"};// 冬季：红鲷鱼，小嘴鲈鱼，金枪鱼
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

    this->_name = name;
    this->_season = season;
    this->_position = position;
    this->_initialPosition = position;  // 保存初始位置

    // 加载鱼的初始精灵
    string fishImagePath = "../Resources/Objects/Base/" + name + ".png";
    _sprite = Sprite::create(fishImagePath);
    if (!_sprite) {
        CCLOG("Error: Failed to load fish sprite for %s", name.c_str());
        return false;
    }
    _sprite->setPosition(position);
    _sprite->setScale(FISH_RATIO);
    this->addChild(_sprite);

    // 启动随机移动和动画更新
    schedule([this](float deltaTime) {
        moveRandomly(deltaTime);
        }, 0.8f, "move_key");

    return true;
}

//设置每种鱼的活动范围
void Fishs::setActivityRange(float range) {
    this->_activityRange = range;
}

//获取当前这种鱼的图片的资源路径
std::string Fishs::getFishImagePath() const {
    return "../Resources/Objects/Base/" + _name + ".png";
}

//随机决定现在鱼的移动方向
void Fishs::moveRandomly(float deltaTime) {
    // 随机决定鱼的移动方向，向左（-1）或向右（1）
    if (rand() % 100 < 5) {  // 5% 概率改变方向
        _moveDirection = (_moveDirection == 1) ? -1 : 1;
    }

    // 随机生成横向位移
    float dx = _moveDirection * (rand() % 10 + 5) * deltaTime;  // 随机的横向位移
    float newX = _position.x + dx;

    // 随机生成纵向位移
    float dy = (rand() % 3 - 1) * (rand() % 10 + 5) * deltaTime;  // 随机的纵向位移 (-1, 0, 1)
    float newY = _position.y + dy;

    // 限制新的位置在初始位置的 40*40 矩形范围内
    if (newX < _initialPosition.x - 20) newX = _initialPosition.x - 20;
    if (newX > _initialPosition.x + 20) newX = _initialPosition.x + 20;
    if (newY < _initialPosition.y - 20) newY = _initialPosition.y - 20;
    if (newY > _initialPosition.y + 20) newY = _initialPosition.y + 20;

    // 更新位置
    _position.x = newX;
    _position.y = newY;
    _sprite->setPosition(_position);

    // 更新动画
    updateAnimation();
}

//鱼往左或往右的动画
void Fishs::updateAnimation() {
    if (!_sprite) {
        CCLOG("Error: Sprite is nullptr, cannot update animation.");
        return;
    }

    // 清除旧的动画动作
    _sprite->stopAllActions();

    // 动画帧路径
    std::vector<std::string> framePaths;
    if (_moveDirection == 1) {  // 向右游动
        framePaths = {
            "../Resources/Animals/Fish/" + _name + "_Right.png",
            "../Resources/Objects/Base/" + _name + ".png"
        };
    }
    else {  // 向左游动
        framePaths = {
            "../Resources/Animals/Fish/" + _name + "_Left_0.png",
            "../Resources/Animals/Fish/" + _name + "_Left_1.png"
        };
    }

    // 加载帧
    Vector<SpriteFrame*> frames = loadFrames(framePaths, Rect(0, 0, 16, 16));  // 假设帧尺寸为 64x64
    if (frames.empty()) {
        CCLOG("Error: No frames loaded for fish animation.");
        return;
    }

    auto animation = Animation::createWithSpriteFrames(frames, 0.97f);
    auto animate = Animate::create(animation);

    _sprite->runAction(RepeatForever::create(animate));
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
std::string Fishs::catchFish(const Season season) {
    srand(static_cast<unsigned int>(time(0)));
    // 初始化季节性鱼类信息
    initializeSeasonFishMap();

    if (_seasonFishMap.find(season) == _seasonFishMap.end()) {
        CCLOG("Error: Invalid season %d", season);
        return "";
    }

    // 获取当前季节的鱼类列表
    const std::vector<std::string>& fishList = _seasonFishMap[season];

    // 小概率不返回鱼
    if (rand() % 100 < FAIL_TO_GET_FISH) {  // 10%的概率不返回鱼
        CCLOG("No fish caught in this season.");
        return "";
    }

    // 随机选择一种鱼
    int randomIndex = rand() % fishList.size();
    std::string fishName = fishList[randomIndex];

    //// 创建并返回一个新的鱼对象
    //Fish* fish = Fish::create(fishName, season, Vec2(rand() % 100, rand() % 100));
    return fishName;
}