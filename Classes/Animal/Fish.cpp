/****************************************************************
 * Project Name:  FishWorld
 * File Name:     Fish.cpp
 * File Function: ���࣬����������ɡ����Χ�ͼ����Ե���
 * Author:        ������
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

std::unordered_map<Season, std::vector<std::string>> Fishs::_seasonFishMap;  // ��̬��Ա��������

Fishs::Fishs()
    : _name("defaultFish"), _season("spring"), _activityRange(50.0f), _sprite(nullptr),
    _currentAnimation(nullptr), _moveDirection(1) {  // 1��ʾ���ң�-1��ʾ����
}

Fishs::~Fishs() {
    if (_sprite) {
        _sprite->removeFromParent();
        _sprite = nullptr;
    }
}

std::unordered_map<std::string, Fishs::FishData> Fishs::fishLevelMap = {
    {"Bigeye", {"Bigeye", 1}},
    {"LargemouthBass", {"LargemouthBass", 2}},
    {"Salmon", {"Salmon", 3}},
    {"Squid", {"Squid", 2}},
    {"Sardines", {"Sardines", 1}},
    {"Herring", {"Herring", 2}},
    {"RedMullet", {"RedMullet", 3}},
    {"Carps", {"Carps", 4}},
    {"Octopuses", {"Octopuses", 5}},
    {"RedSnapper", {"RedSnapper", 3}},
    {"SmallmouthBass", {"SmallmouthBass", 2}},
    {"TunaFish", {"TunaFish", 5}},
};

//��ʼ��ÿ�����ڵ��������
void Fishs::initializeSeasonFishMap() {
    if (!_seasonFishMap.empty()) return;
    _seasonFishMap[Spring] = { "Bigeye", "LargemouthBass", "Salmon"};// �����������㣬�������㣬����
    _seasonFishMap[Summer] = { "Squid", "Sardines", "Herring" };// �ļ������㣬ɳ���㣬����
    _seasonFishMap[Fall] =   { "RedMullet", "Carps", "Octopuses"};// �＾�������㣬���㣬����
    _seasonFishMap[Winter] = { "RedSnapper", "SmallmouthBass", "TunaFish"};// �����������㣬С�����㣬��ǹ��
}

//����������һ���µ� Fishs ����
Fishs* Fishs::create(const std::string& name, const std::string& season, const Vec2& position) {
    Fishs* ret = new Fishs();
    if (ret && ret->init(name, season, position)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//��ʼ����ĸ�����Ϣ
bool Fishs::init(const std::string& name, const std::string& season, const Vec2& position) {
    if (!Node::init()) {
        return false;
    }

    this->_name = name;
    this->_season = season;
    this->_position = position;
    this->_initialPosition = position;  // �����ʼλ��

    // ������ĵȼ�
    if (fishLevelMap.find(name) != fishLevelMap.end()) {
        _level = fishLevelMap[name].level;
    }
    else {
        _level = 0;  // Ĭ�ϵȼ�
    }
    // ������ĳ�ʼ����
    string fishImagePath = "../Resources/Objects/Base/" + name + ".png";
    _sprite = Sprite::create(fishImagePath);
    if (!_sprite) {
        CCLOG("Error: Failed to load fish sprite for %s", name.c_str());
        return false;
    }
    _sprite->setPosition(position);
    _sprite->setScale(FISH_RATIO);
    this->addChild(_sprite);

    // ��������ƶ��Ͷ�������
    schedule([this](float deltaTime) {
        moveRandomly(deltaTime);
        }, 0.8f, "move_key");

    return true;
}

//����ÿ����Ļ��Χ
void Fishs::setActivityRange(float range) {
    this->_activityRange = range;
}

//��ȡ��ǰ�������ͼƬ����Դ·��
std::string Fishs::getFishImagePath() const {
    return "../Resources/Objects/Base/" + _name + ".png";
}

//���������������ƶ�����
void Fishs::moveRandomly(float deltaTime) {
    // �����������ƶ���������-1�������ң�1��
    if (rand() % 100 < 5) {  // 5% ���ʸı䷽��
        _moveDirection = (_moveDirection == 1) ? -1 : 1;
    }

    // ������ɺ���λ��
    float dx = _moveDirection * (rand() % 10 + 5) * deltaTime;  // ����ĺ���λ��
    float newX = _position.x + dx;

    // �����������λ��
    float dy = (rand() % 3 - 1) * (rand() % 10 + 5) * deltaTime;  // ���������λ�� (-1, 0, 1)
    float newY = _position.y + dy;

    // �����µ�λ���ڳ�ʼλ�õ� 40*40 ���η�Χ��
    if (newX < _initialPosition.x - 20) newX = _initialPosition.x - 20;
    if (newX > _initialPosition.x + 20) newX = _initialPosition.x + 20;
    if (newY < _initialPosition.y - 20) newY = _initialPosition.y - 20;
    if (newY > _initialPosition.y + 20) newY = _initialPosition.y + 20;

    // ����λ��
    _position.x = newX;
    _position.y = newY;
    _sprite->setPosition(_position);

    // ���¶���
    updateAnimation();
}

//����������ҵĶ���
void Fishs::updateAnimation() {
    if (!_sprite) {
        CCLOG("Error: Sprite is nullptr, cannot update animation.");
        return;
    }

    // ����ɵĶ�������
    _sprite->stopAllActions();

    // ����֡·��
    std::vector<std::string> framePaths;
    if (_moveDirection == 1) {  // �����ζ�
        framePaths = {
            "../Resources/Animals/Fish/" + _name + "_Right.png",
            "../Resources/Objects/Base/" + _name + ".png"
        };
    }
    else {  // �����ζ�
        framePaths = {
            "../Resources/Animals/Fish/" + _name + "_Left_0.png",
            "../Resources/Animals/Fish/" + _name + "_Left_1.png"
        };
    }

    // ����֡
    Vector<SpriteFrame*> frames = loadFrames(framePaths, Rect(0, 0, 16, 16));  // ����֡�ߴ�Ϊ 64x64
    if (frames.empty()) {
        CCLOG("Error: No frames loaded for fish animation.");
        return;
    }

    auto animation = Animation::createWithSpriteFrames(frames, 0.97f);
    auto animate = Animate::create(animation);

    _sprite->runAction(RepeatForever::create(animate));
}

//�ú������ݸ�����֡·����֡�������򣬴�ÿ��·������������������Ӧ�ľ���֡�����Ὣ�ɹ����صľ���֡��ӵ�һ�� `Vector<SpriteFrame*>` �����в����ء�
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

//���㺯�������ص�ǰ�����������
std::string Fishs::catchFish(const Season season,int playerLevel) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(0)));
        seeded = true;
    }
    // ��ʼ��������������Ϣ
    initializeSeasonFishMap();

    if (_seasonFishMap.find(season) == _seasonFishMap.end()) {
        CCLOG("Error: Invalid season %d", season);
        return "";
    }

    // ��ȡ��ǰ���ڵ������б�
    const std::vector<std::string>& fishList = _seasonFishMap[season];
    //// ���Դ�ӡ�����б�
    //CCLOG("Fish list for season %d:", season);
    //for (const auto& fish : fishList) {
    //    CCLOG(" - %s", fish.c_str());
    //}
    
    // ����һ����ѡ�������б�ɸѡ����ҵȼ�����Ҫ�������
    std::vector<std::string> eligibleFishList;
    for (const auto& fishName : fishList) {
        if (fishLevelMap.find(fishName) != fishLevelMap.end()) {
            int fishUnlockLevel = fishLevelMap[fishName].level;  // ��ȡ����Ľ����ȼ�
            if (fishUnlockLevel <= playerLevel) {
                eligibleFishList.push_back(fishName);  // ��ҵȼ����㣬�����ѡ�б�
            }
        }
    }
    // ���û�з�������������
    if (eligibleFishList.empty()) {
        CCLOG("Player level %d is not high enough to catch any fish in this season.", playerLevel);
        return "";
    }

   
    // С���ʲ�������
    if (rand() % 100 < FAIL_TO_GET_FISH) {  // 10%�ĸ��ʲ�������
        CCLOG("No fish caught in this season.");
        return "";
    }

    // ���ѡ��һ��������������
    int randomIndex = rand() % eligibleFishList.size();
    std::string fishName_end = eligibleFishList[randomIndex];

    //// ����������һ���µ������
    //Fish* fish = Fish::create(fishName, season, Vec2(rand() % 100, rand() % 100));
    return fishName_end;
}