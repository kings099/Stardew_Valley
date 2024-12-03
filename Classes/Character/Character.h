/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.h
 * File Function: Character��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/02
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

class Character : public cocos2d::Node {
public:
    //��������
    static Character* create(const std::string& filename);

    //��ʼ��
    bool init(const std::string& filename);

    // ���¼���ʱ�Ĵ���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �ͷż���ʱ�Ĵ���
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ���Ŷ���
    void playAnimation();

    // ���½�ɫλ��
    void Character::updatePosition(float deltaTime);

    // ���¼���״̬��ʾ
    void updateKeyStatus();

private:
    cocos2d::Sprite* character;                         //��ɫ����
    cocos2d::Label* keyStatusLabel;                     //��ʾ����״̬�ı�ǩ
    cocos2d::EventKeyboard::KeyCode lastKeyCode;        //���һ�ΰ��µļ�
    float width;                                        //��ɫ���
    float height;                                       //��ɫ�߶�
    float moveSpeed;                                    //��ɫ�ٶ�
    bool moveUp;                                        //�Ƿ�����
    bool moveDown;                                      //�Ƿ�����
    bool moveLeft;                                      //�Ƿ�����
    bool moveRight;                                     //�Ƿ�����
    bool animationPlaying;                              //�Ƿ����ڲ��Ŷ���
};

#endif // __CHARACTER_H__
