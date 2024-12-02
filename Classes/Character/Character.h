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

    // ���½�ɫλ��
    void Character::updatePosition(float deltaTime);

private:
    cocos2d::Sprite* character;     //��ɫ����
    float moveSpeed;                //�ٶ�
    bool moveUp;                    //�Ƿ�����
    bool moveDown;                  //�Ƿ�����
    bool moveLeft;                  //�Ƿ�����
    bool moveRight;                 //�Ƿ�����
};

#endif // __CHARACTER_H__
