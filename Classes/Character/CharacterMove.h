﻿/****************************************************************
 * Project Name:  Stardew Valley
<<<<<<< Updated upstream
 * File Name:     Character.h
 * File Function: Character��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/03
=======
 * File Name:     CharacterMove.h
 * File Function: CharacterMove类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/04
>>>>>>> Stashed changes
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_MOVE_H__
#define __CHARACTER_MOVE_H__

#include "cocos2d.h"
<<<<<<< Updated upstream
#include <unordered_map>
=======

>>>>>>> Stashed changes

class CharacterMove : virtual public cocos2d::Node {
public:
    //构造函数
    CharacterMove();

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 播放动画
    void playAnimation();

protected:
    cocos2d::Sprite* _character;                         // 角色对象

    // 更新角色位置
    cocos2d::Vec2 updatePosition(float deltaTime);
private:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    cocos2d::Sprite* character;                         // ��ɫ����
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;      // ��ɫ����֡
    float width;                                        // ��ɫ���
    float height;                                       // ��ɫ�߶�
    float moveSpeed;                                    // ��ɫ�ٶ�
    bool moveUp;                                        // �Ƿ�����
    bool moveDown;                                      // �Ƿ�����
    bool moveLeft;                                      // �Ƿ�����
    bool moveRight;                                     // �Ƿ�����
    bool animationPlaying;                              // �Ƿ����ڲ��Ŷ���
    std::string currentDirection;                       // ��ǰ��������
    std::string lastDirection;                          // ��һ�ζ�������
=======
    cocos2d::Sprite* _character;                         // ��ɫ����
    cocos2d::Vector<cocos2d::SpriteFrame*> _frames;      // ��ɫ����֡
    float _width;                                        // ��ɫ���
    float _height;                                       // ��ɫ�߶�
    float _moveSpeed;                                    // ��ɫ�ٶ�
    bool _moveUp;                                        // �Ƿ�����
    bool _moveDown;                                      // �Ƿ�����
    bool _moveLeft;                                      // �Ƿ�����
    bool _moveRight;                                     // �Ƿ�����
    bool _animationPlaying;                              // �Ƿ����ڲ��Ŷ���
    std::string _currentDirection;                       // ��ǰ��������
    std::string _lastDirection;                          // ��һ�ζ�������
>>>>>>> Stashed changes
=======
    cocos2d::Vector<cocos2d::SpriteFrame*> _frames;      // 角色动画帧
    float _width;                                        // 角色宽度
    float _height;                                       // 角色高度
    float _moveSpeed;                                    // 角色速度
    bool _moveUp;                                        // 是否上移
    bool _moveDown;                                      // 是否下移
    bool _moveLeft;                                      // 是否左移
    bool _moveRight;                                     // 是否右移
    bool _animationPlaying;                              // 是否正在播放动画
    std::string _currentDirection;                       // 当前动画方向
    std::string _lastDirection;                          // 上一次动画方向


>>>>>>> Stashed changes
};

#endif // __CHARACTER_H__
