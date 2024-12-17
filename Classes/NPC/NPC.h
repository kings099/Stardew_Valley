#pragma once
#ifndef NPC_H
#define NPC_H

#include "cocos2d.h"
#include <vector>
#include <string>

class GiftItem;  // ǰ������ GiftItem

class NPC : public cocos2d::Node {
public:
    std::string name;            // NPC ������
    int affection;               // �øжȣ���Χ 0 - 100
    bool isMarried;              // �Ƿ��ѽ��
    std::vector<std::string> dialogues;  // NPC �ĶԻ�����
    cocos2d::Vec2 destination;   // NPC ��Ŀ��λ��
    bool isMoving;               // NPC �Ƿ������ƶ�
    cocos2d::Sprite* sprite;     // NPC �ľ��飨��ۣ�
    cocos2d::Animate* walkAnimation; // ���߶���
    
    // ���캯������ʼ�� NPC ���ֺ�λ��
    NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames);

   
    // ��ʼ�� NPC �ľ���Ͷ���
    void initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames);

    // NPC ��ʾ�Ի���
    void showDialog();

   

    // ���Ӻøж�
    void increaseAffection(int value);

    // �������Ƿ��� NPC ����
    bool isPlayerNear(cocos2d::Vec2 playerPosition);

    // ������
    void giftItem(GiftItem* gift);

    // ʹ NPC �ƶ���Ŀ��λ��
    void moveTo(cocos2d::Vec2 targetPosition);

    //�������߶���
    void startWalkingAnimation();

    std::string getName();

    void closeDialog(cocos2d::Ref* sender);
};

#endif // NPC_H
