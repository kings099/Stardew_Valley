/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NPC.h
 * File Function: ��װ���� NPC ��صĻ������ܣ�
                  ����ʾ�Ի������Ӻøжȡ���������������߶����ȡ�
                  NPC �����������һ����������Ի��Լ�����
 * Author:        ��˼�
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
    std::string name;                    // NPC ������
    int affection;                       // �øжȣ���Χ 0 - 100
    bool isMarried;                      // �Ƿ��ѽ��
    std::vector<std::string> dialogues;  // NPC �ĶԻ�����
    cocos2d::Vec2 destination;           // NPC ��Ŀ��λ��
    bool isMoving;                       // NPC �Ƿ������ƶ�
    cocos2d::Sprite* sprite;             // NPC �ľ��飨��ۣ�
    cocos2d::Animate* walkAnimation;     // ���߶���
    std::vector<Task*> tasks;            // NPC ӵ�е�����


    // ���캯������ʼ�� NPC ���ֺ�λ��
    NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames);

   
    // ��ʼ�� NPC �ľ���Ͷ���
    void initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames);

    // NPC ��ʾ�Ի���
    void showDialog();


    // ���Ӻøж�
    void NPC::increaseAffection(int value, bool isRomantic = true);

    void NPC::marryPlayer();

    void NPC::playMarriageAnimation();

    //�Ƿ����ѡ���
    void NPC::showMarriageChoices();

    // �������Ƿ��� NPC ����
    bool isPlayerNear(cocos2d::Vec2 playerPosition);

    // ������
    void NPC::giftItem(GiftItem* gift);

    // ʹ NPC �ƶ���Ŀ��λ��
    void moveTo(cocos2d::Vec2 targetPosition);

    //�������߶���
    void startWalkingAnimation();

    //���ص�ǰNPC������
    std::string getName();
    
    //�رնԻ�
    void closeDialog(cocos2d::Ref* sender);

    // ��ȡ��ǰ�øж�
    int getAffection() const;

    void  showTaskCompletionReward(Task* task);

    void addTask(Task* task);

    void showTaskList();

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    };

#endif // NPC_H
