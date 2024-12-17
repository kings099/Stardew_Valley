#pragma once
#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <vector>
#include <string>

class GiftItem;  // 前向声明 GiftItem

class NPC : public cocos2d::Node {
public:
    std::string name;            // NPC 的名字
    int affection;               // 好感度，范围 0 - 100
    bool isMarried;              // 是否已结婚
    std::vector<std::string> dialogues;  // NPC 的对话内容
    cocos2d::Vec2 destination;   // NPC 的目标位置
    bool isMoving;               // NPC 是否正在移动
    cocos2d::Sprite* sprite;     // NPC 的精灵（外观）
    cocos2d::Animate* walkAnimation; // 行走动画
    
    // 构造函数，初始化 NPC 名字和位置
    NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames);

   
    // 初始化 NPC 的精灵和动画
    void initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames);

    // NPC 显示对话框
    void showDialog();

   

    // 增加好感度
    void increaseAffection(int value);

    // 检查玩家是否在 NPC 附近
    bool isPlayerNear(cocos2d::Vec2 playerPosition);

    // 送礼物
    void giftItem(GiftItem* gift);

    // 使 NPC 移动到目标位置
    void moveTo(cocos2d::Vec2 targetPosition);

    //启动行走动画
    void startWalkingAnimation();

    std::string getName();

    void closeDialog(cocos2d::Ref* sender);
};

#endif // NPC_H
