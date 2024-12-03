/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     CharacterMove.h
 * File Function: CharacterMove��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTERMOVE_H__
#define __CHARACTERMOVE_H__

#include "cocos2d.h"


class CharacterMove : public cocos2d::Node {
public:
    //��������
    static CharacterMove* create(const std::string& filename);

    //��ʼ��
    bool init(const std::string& filename);

    // ���¼���ʱ�Ĵ���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �ͷż���ʱ�Ĵ���
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ���Ŷ���
    void playAnimation();

    // ���½�ɫλ��
    cocos2d::Vec2 updatePosition(float deltaTime);

private:
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
};

#endif // __CHARACTER_H__
