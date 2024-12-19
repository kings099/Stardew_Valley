/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NPC.h
 * File Function: 封装了与 NPC 相关的基本功能，
                  如显示对话框、增加好感度、接受礼物、播放行走动画等。
                  NPC 对象可以与玩家互动，包括对话以及送礼。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef NPC_H
#define NPC_H
#include "cocos2d.h"
#include "Task.h"
#include "GiftItem.h"
#include "Control/GiftItemManager.h"
#include "ui/CocosGUI.h"
#include "Layer/ChatLayer.h"
#include"CharacterInfo.h"
#include <vector>
#include <string>
#include"Character.h"



class NPC : public cocos2d::Node {
public: 
    std::string name;                    // NPC 的名字
    int affection;                       // 好感度，范围 0 - 100
    bool isMarried;                      // 是否已结婚
    std::vector<std::string> dialogues;  // NPC 的对话内容
    cocos2d::Vec2 destination;           // NPC 的目标位置
    bool isMoving;                       // NPC 是否正在移动
    cocos2d::Sprite* sprite;             // NPC 的精灵（外观）
    cocos2d::Animate* walkAnimation;     // 行走动画
    std::vector<Task*> tasks;            // NPC 拥有的任务


    // 构造函数，初始化 NPC 名字和位置
    NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames);

   
    // 初始化 NPC 的精灵和动画
    void initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames);

    // NPC 显示对话框
    void showDialog();


    // 增加好感度
    void NPC::increaseAffection(int value, bool isRomantic = true);

    void NPC::marryPlayer();

    void NPC::playMarriageAnimation();

    //是否结婚的选择框
    void NPC::showMarriageChoices();

    // 检查玩家是否在 NPC 附近
    bool isPlayerNear(cocos2d::Vec2 playerPosition);

    // 送礼物
    void NPC::giftItem(GiftItem* gift);

    // 使 NPC 移动到目标位置
    void moveTo(cocos2d::Vec2 targetPosition);

    //启动行走动画
    void startWalkingAnimation();

    //返回当前NPC的姓名
    std::string getName();
    
    //关闭对话
    void closeDialog(cocos2d::Ref* sender);

    // 获取当前好感度
    int getAffection() const;

    void  showTaskCompletionReward(Task* task);

    void addTask(Task* task);

    void showTaskList();

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    };

#endif // NPC_H
