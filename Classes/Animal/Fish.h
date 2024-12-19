#pragma once
/****************************************************************
 * Project Name:  FishWorld
 * File Name:     Fish.h
 * File Function: ���࣬����������ɡ����Χ�ͼ����Ե���
 * Author:        ������
 * Update Date:   2024/12/19
 * License:       MIT License
 ****************************************************************/

#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <unordered_map>
#include <vector>
#include <string>

USING_NS_CC;

class Fishs : public Node {
public:
    Fishs();
    virtual ~Fishs();

    static void initializeSeasonFishMap();
    static Fishs* create(const std::string& name, const std::string& season, const Vec2& position);

    bool init(const std::string& name, const std::string& season, const Vec2& position);
    void setActivityRange(float range);
    std::string getFishImagePath() const;

    // ����ƶ�
    void moveRandomly(float deltaTime);

    // ���¶���
    void updateAnimation();

    // ������
    static std::string catchFish(const std::string& season);

private:
    std::string name;                    // �������
    std::string season;                  // ��ǰ����
    Vec2 position;                       // ��ǰ���λ��
    float activityRange;                 // ��Ļ��Χ
    Sprite* sprite;                      // ��ľ���
    Animate* currentAnimation;           // ��ǰ����
    int moveDirection;                   // ����ƶ����� (1: ����, -1: ����)
    Vec2 initialPosition;                // ������ĳ�ʼλ��
    // ����������ӳ��
    static std::unordered_map<std::string, std::vector<std::string>> seasonFishMap;

    // ���ض���֡�ĸ�������
    Vector<SpriteFrame*> loadFrames(const std::vector<std::string>& framePaths, const Rect& frameRect);
};

#endif // __FISH_H__
