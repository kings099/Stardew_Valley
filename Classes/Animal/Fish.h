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
#include "proj.win32/Constant.h"

USING_NS_CC;

class Fishs : public Node {
public:
    Fishs();
    virtual ~Fishs();
    //��ʼ��ÿ�ּ��ڶ�Ӧ��������͵Ĺ�������
    static void initializeSeasonFishMap();

    //����������һ���µ� Fishs ����
    static Fishs* create(const std::string& name, const std::string& season, const Vec2& position);

    //��ʼ��ÿ�������Ϣ
    bool init(const std::string& name, const std::string& season, const Vec2& position);

    //����ÿ����������ƶ���Χ
    void setActivityRange(float range);
    //��ȡ��ǰ�����������
    std::string getFishImagePath() const;

    // ����ƶ�
    void moveRandomly(float deltaTime);

    // ���¶���
    void updateAnimation();

    // ������
    static std::string catchFish(const Season season, int playerLevel);

private:
    std::string _name;                    // �������
    std::string _season;                  // ��ǰ����
    Vec2 _position;                       // ��ǰ���λ��
    float _activityRange;                 // ��Ļ��Χ
    Sprite* _sprite;                      // ��ľ���
    Animate* _currentAnimation;           // ��ǰ����
    int _moveDirection;                   // ����ƶ����� (1: ����, -1: ����)
    Vec2 _initialPosition;                // ������ĳ�ʼλ��
    // ����������ӳ��
    static std::unordered_map<Season, std::vector<std::string>> _seasonFishMap;

    // ���ض���֡�ĸ�������
    Vector<SpriteFrame*> loadFrames(const std::vector<std::string>& framePaths, const Rect& frameRect);
};

#endif // __FISH_H__
