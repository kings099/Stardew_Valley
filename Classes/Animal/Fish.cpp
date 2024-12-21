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

std::unordered_map<Season, std::vector<std::string>> Fishs::seasonFishMap;  // ��̬��Ա��������

Fishs::Fishs()
    : name("defaultFish"), season("spring"), activityRange(50.0f), sprite(nullptr),
    currentAnimation(nullptr), moveDirection(1) {  // 1��ʾ���ң�-1��ʾ����
}

Fishs::~Fishs() {
    if (sprite) {
        sprite->removeFromParent();
        sprite = nullptr;
    }
}

//��ʼ��ÿ�����ڵ��������
void Fishs::initializeSeasonFishMap() {
    if (!seasonFishMap.empty()) return;
    seasonFishMap[Spring] = { "Bigeye", "LargemouthBass", "Salmon"};// �����������㣬�������㣬����
    seasonFishMap[Summer] = { "Squid", "Sardines", "Herring" };// �ļ������㣬ɳ���㣬����
    seasonFishMap[Fall] =   { "RedMullet", "Carps", "Octopuses"};// �＾�������㣬���㣬����
    seasonFishMap[Winter] = { "RedSnapper", "SmallmouthBass", "TunaFish"};// �����������㣬С�����㣬��ǹ��
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

    this->name = name;
    this->season = season;
    this->position = position;
    this->initialPosition = position;  // �����ʼλ��

    // ������ĳ�ʼ����
    string fishImagePath = "../Resources/Objects/Base/" + name + ".png";
    sprite = Sprite::create(fishImagePath);
    if (!sprite) {
        CCLOG("Error: Failed to load fish sprite for %s", name.c_str());
        return false;
    }
    sprite->setPosition(position);
    sprite->setScale(FISH_RATIO);
    this->addChild(sprite);

    // ��������ƶ��Ͷ�������
    schedule([this](float deltaTime) {
        moveRandomly(deltaTime);
        }, 0.8f, "move_key");

    return true;
}

//����ÿ����Ļ��Χ
void Fishs::setActivityRange(float range) {
    this->activityRange = range;
}

//��ȡ��ǰ�������ͼƬ����Դ·��
std::string Fishs::getFishImagePath() const {
    return "../Resources/Objects/Base/" + name + ".png";
}

//���������������ƶ�����
void Fishs::moveRandomly(float deltaTime) {
    // �����������ƶ���������-1�������ң�1��
    if (rand() % 100 < 5) {  // 5% ���ʸı䷽��
        moveDirection = (moveDirection == 1) ? -1 : 1;
    }

    // ������ɺ���λ��
    float dx = moveDirection * (rand() % 10 + 5) * deltaTime;  // ����ĺ���λ��
    float newX = position.x + dx;

    // �����������λ��
    float dy = (rand() % 3 - 1) * (rand() % 10 + 5) * deltaTime;  // ���������λ�� (-1, 0, 1)
    float newY = position.y + dy;

    // �����µ�λ���ڳ�ʼλ�õ� 40*40 ���η�Χ��
    if (newX < initialPosition.x - 20) newX = initialPosition.x - 20;
    if (newX > initialPosition.x + 20) newX = initialPosition.x + 20;
    if (newY < initialPosition.y - 20) newY = initialPosition.y - 20;
    if (newY > initialPosition.y + 20) newY = initialPosition.y + 20;

    // ����λ��
    position.x = newX;
    position.y = newY;
    sprite->setPosition(position);

    // ���¶���
    updateAnimation();
}

//����������ҵĶ���
void Fishs::updateAnimation() {
    if (!sprite) {
        CCLOG("Error: Sprite is nullptr, cannot update animation.");
        return;
    }

    // ����ɵĶ�������
    sprite->stopAllActions();

    // ����֡·��
    std::vector<std::string> framePaths;
    if (moveDirection == 1) {  // �����ζ�
        framePaths = {
            "../Resources/Animals/Fish/" + name + "_Right.png",
            "../Resources/Objects/Base/" + name + ".png"
        };
    }
    else {  // �����ζ�
        framePaths = {
            "../Resources/Animals/Fish/" + name + "_Left_0.png",
            "../Resources/Animals/Fish/" + name + "_Left_1.png"
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

    sprite->runAction(RepeatForever::create(animate));
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
std::string Fishs::catchFish(const Season season) {
    srand(static_cast<unsigned int>(time(0)));
    // ��ʼ��������������Ϣ
    initializeSeasonFishMap();

    if (seasonFishMap.find(season) == seasonFishMap.end()) {
        CCLOG("Error: Invalid season %d", season);
        return "";
    }

    // ��ȡ��ǰ���ڵ������б�
    const std::vector<std::string>& fishList = seasonFishMap[season];

    // С���ʲ�������
    if (rand() % 100 < FAIL_TO_GET_FISH) {  // 10%�ĸ��ʲ�������
        CCLOG("No fish caught in this season.");
        return "";
    }

    // ���ѡ��һ����
    int randomIndex = rand() % fishList.size();
    std::string fishName = fishList[randomIndex];

    //// ����������һ���µ������
    //Fish* fish = Fish::create(fishName, season, Vec2(rand() % 100, rand() % 100));
    return fishName;
}