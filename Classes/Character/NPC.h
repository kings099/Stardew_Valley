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
    std::string _name;                    // NPC ������
    int _affection;                       // �øжȣ���Χ 0 - 100
    bool _isMarried;                      // �Ƿ��ѽ��
    std::vector<std::string> _dialogues;  // NPC �ĶԻ�����
    cocos2d::Vec2 _destination;           // NPC ��Ŀ��λ��
    bool _isMoving;                       // NPC �Ƿ������ƶ�
    cocos2d::Sprite* _sprite;             // NPC �ľ��飨��ۣ�
    cocos2d::Animate* _walkAnimation;     // ���߶���
    std::vector<Task*> _tasks;            // NPC ӵ�е�����
    bool _isProcessing;                  // �����ж��Ƿ����ڴ�������

    // ���캯������ʼ�� NPC ���ֺ�λ��
    NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames);

   
    // ��ʼ�� NPC �ľ���Ͷ���
    void initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames);

    // NPC ��ʾ�Ի���
    void showDialog();

    void showDialogue(const std::string& dialogueText);

    // ���Ӻøж�
    void NPC::increaseAffection(int value);

    //ִ������߼�
    void NPC::marryPlayer();
    
    //������鶯��
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
 
    //����NPC����
    void addTask(Task* task);

    //չʾ�����б�
    void showTaskList();

    //���̽���
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    //�޸�������״̬
    void setIsProcessing(bool isProcessing);

    };

#endif // NPC_H
