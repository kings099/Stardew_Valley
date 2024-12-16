/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NPC.cpp
 * File Function: ��װ���� NPC ��صĻ������ܣ�
                  ����ʾ�Ի������Ӻøжȡ���������������߶����ȡ�
                  NPC �����������һ����������Ի��Լ�����
 * Author:        ��˼�
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/

#include "NPC.h"
#include "GiftItem.h"
#include "ui/CocosGUI.h"
#include "Layer/ChatLayer.h"
#include"CharacterInfo.h"

 // NPC ��ʼ��
NPC::NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames)
    : name(name), affection(0), isMarried(false), isMoving(false) {
    setPosition(position);                    // ��ʼ�� NPC λ��
    initializeSprite(idleImage, walkFrames);  // ��ʼ������Ͷ���
}

// ��ʼ������Ͷ���
void NPC::initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames) {
    sprite = cocos2d::Sprite::create(idleImage);
    if (sprite == nullptr) {
        CCLOG("Failed to load sprite: %s", idleImage.c_str());
    }
    sprite->setPosition(getPosition());
    addChild(sprite);

    // ���þ������ű���
    sprite->setScaleX(32.0f / sprite->getContentSize().width);  
    sprite->setScaleY(64.0f / sprite->getContentSize().height); 

    // �������߶���
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 64, 64)));
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    walkAnimation = cocos2d::Animate::create(walkAnim);
}

// ��ʾ�Ի���
void NPC::showDialog() {
    int dialogueIndex = affection / 25;
    dialogueIndex = std::min(dialogueIndex, (int)dialogues.size() - 1);
    std::string username = CharacterInfo::getInstance()->getUsername();  // ��ȡ�û���
    std::string dialogue = dialogues[dialogueIndex]+","+username;

    // ��������ʾ ChatLayer
    ChatLayer* chatLayer = ChatLayer::create(dialogue);  // ���� ChatLayer ʵ��������Ի�����
    cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (runningScene != nullptr) {
        runningScene->addChild(chatLayer, 10);  // �� ChatLayer ��ӵ���ǰ����
    }
}

// ���Ӻøж�
void NPC::increaseAffection(int value) {
    affection = std::min(100, affection + value);
}

// �ж�����Ƿ�ӽ�
bool NPC::isPlayerNear(cocos2d::Vec2 playerPosition) {
    return playerPosition.distance(getPosition()) < 50.0f;
}

// ������
void NPC::giftItem(GiftItem* gift) {
    int affectionIncrease = gift->getAffectionForNPC(name);
    increaseAffection(affectionIncrease);
    // ��������ʾ ChatLayer
    ChatLayer* chatLayer = ChatLayer::create("Thank you for the gift, " + gift->name);  // ���� ChatLayer ʵ��������Ի�����
    cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (runningScene != nullptr) {
        runningScene->addChild(chatLayer, 10);  // �� ChatLayer ��ӵ���ǰ����
    }
}

// ��ʼ���߶���
void NPC::startWalkingAnimation() {
    if (sprite && walkAnimation) {
        sprite->runAction(cocos2d::RepeatForever::create(walkAnimation));
    }
}

std::string NPC::getName() {
    return name;
}
