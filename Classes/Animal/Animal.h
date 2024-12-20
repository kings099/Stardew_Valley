/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animal.h
 * File Function: С�����࣬ʵ��С����ĸ��ֻ�������
 * Author:        ������
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/
#ifndef ANIMAL_H
#define ANIMAL_H

#include "cocos2d.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "proj.win32/Constant.h"

USING_NS_CC;

class Animal : public Node {
    
protected:
    Sprite* angryIcon; // ŭ��ͼ��
    std::string type;   // �������� (�磺chicken��cow��sheep)
    float affection;    // ����ĺøж�
    bool isFed;         // �Ƿ�ι��
    float lastFedTime;  // ���ι��ʱ��
    float affectionDecayRate; // �øж�˥������
    float maxAffection;    // ���øж�

    Sprite* sprite;   // ����ľ���
    Action* currentAnimation; // ��ǰ���ŵĶ���
    
    Vec2 position;     // ����ĵ�ǰ����
    Vec2 origin;       // ����С����ʱָ����ԭ�� (�����ε����½�)
    float areaSize;    // ����������Ĵ�С (20x20)

    // �������Դӳ��
    static std::unordered_map<std::string, std::vector<std::string>> resourceMap;
    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> animationMap;

public:
    Vec2 direction;
    Animal();
    ~Animal();

  

    // ��ʼ����Դ
    static void initializeResourceMap();
    static void initializeAnimationMap();

    // ��������ʵ��
    static Animal* create(const std::string& type, const Vec2& startPosition);
    //��ʼ��������Ϣ
    bool init(const std::string& type, const Vec2& startPosition);

    // ι������
    void feed();

    // ���ºøж�
    void updateAffection(float deltaTime);

    // �ж϶����Ƿ񷢿�
    bool isAngry() const;

    // ���﷢��ʱ�Ĵ���
    void handleAngry();

    // ��ȡ���ﵱǰ�øж�
    float getAffection() const;

    // ��ȡ��������
    const std::string& getType() const;

    // ���ö��������ƶ�
    void setRandomMovement(float deltaTime);

    // ���ŷ��򶯻�
    void playDirectionAnimation(const std::string& direction, int repeatCount);
};

#endif // ANIMAL_H
