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
    std::string _name;                    // NPC 的名字
    int _affection;                       // 好感度，范围 0 - 100
    bool _isMarried;                      // 是否已结婚
    std::vector<std::string> _dialogues;  // NPC 的对话内容
    cocos2d::Vec2 _destination;           // NPC 的目标位置
    bool _isMoving;                       // NPC 是否正在移动
    cocos2d::Sprite* _sprite;             // NPC 的精灵（外观）
    cocos2d::Animate* _walkAnimation;     // 行走动画
    std::vector<Task*> _tasks;            // NPC 拥有的任务
    bool _isProcessing;                  // 用于判断是否正在处理任务

    // 构造函数，初始化 NPC 名字和位置
    NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames);

   
    // 初始化 NPC 的精灵和动画
    void initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames);

    // NPC 显示对话框
    void showDialog();

    void showDialogue(const std::string& dialogueText);

    // 增加好感度
    void NPC::increaseAffection(int value);

    //执行求婚逻辑
    void NPC::marryPlayer();
    
    //播放求婚动画
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
 
    //增加NPC任务
    void addTask(Task* task);

    //展示任务列表
    void showTaskList();

    //键盘交互
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    //修改任务处理状态
    void setIsProcessing(bool isProcessing);

    };

#endif // NPC_H
