/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NPC.cpp
 * File Function: 封装了与 NPC 相关的基本功能，
                  如显示对话框、增加好感度、接受礼物、播放行走动画等。
                  NPC 对象可以与玩家互动，包括对话以及送礼。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/

#include "NPC.h"
#include "GiftItem.h"
#include "ui/CocosGUI.h"
#include "Layer/ChatLayer.h"
#include"CharacterInfo.h"

 // NPC 初始化
NPC::NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames)
    : name(name), affection(0), isMarried(false), isMoving(false) {
    setPosition(position);                    // 初始化 NPC 位置
    initializeSprite(idleImage, walkFrames);  // 初始化精灵和动画
}

// 初始化精灵和动画
void NPC::initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames) {
    sprite = cocos2d::Sprite::create(idleImage);
    if (sprite == nullptr) {
        CCLOG("Failed to load sprite: %s", idleImage.c_str());
    }
    sprite->setPosition(getPosition());
    addChild(sprite);

    // 设置精灵缩放比例
    sprite->setScaleX(32.0f / sprite->getContentSize().width);  
    sprite->setScaleY(64.0f / sprite->getContentSize().height); 

    // 设置行走动画
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 64, 64)));
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    walkAnimation = cocos2d::Animate::create(walkAnim);
}

// 显示对话框
void NPC::showDialog() {
    int dialogueIndex = affection / 25;
    dialogueIndex = std::min(dialogueIndex, (int)dialogues.size() - 1);
    std::string username = CharacterInfo::getInstance()->getUsername();  // 获取用户名
    std::string dialogue = dialogues[dialogueIndex]+","+username;

    // 创建并显示 ChatLayer
    ChatLayer* chatLayer = ChatLayer::create(dialogue);  // 创建 ChatLayer 实例并传入对话内容
    cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (runningScene != nullptr) {
        runningScene->addChild(chatLayer, 10);  // 将 ChatLayer 添加到当前场景
    }
}

// 增加好感度
void NPC::increaseAffection(int value) {
    affection = std::min(100, affection + value);
}

// 判断玩家是否接近
bool NPC::isPlayerNear(cocos2d::Vec2 playerPosition) {
    return playerPosition.distance(getPosition()) < 50.0f;
}

// 送礼物
void NPC::giftItem(GiftItem* gift) {
    int affectionIncrease = gift->getAffectionForNPC(name);
    increaseAffection(affectionIncrease);
    // 创建并显示 ChatLayer
    ChatLayer* chatLayer = ChatLayer::create("Thank you for the gift, " + gift->name);  // 创建 ChatLayer 实例并传入对话内容
    cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (runningScene != nullptr) {
        runningScene->addChild(chatLayer, 10);  // 将 ChatLayer 添加到当前场景
    }
}

// 开始行走动画
void NPC::startWalkingAnimation() {
    if (sprite && walkAnimation) {
        sprite->runAction(cocos2d::RepeatForever::create(walkAnimation));
    }
}

std::string NPC::getName() {
    return name;
}
