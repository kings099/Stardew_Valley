/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.h
 * File Function: Character��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "CharacterMove.h"
#include "CharacterObjectList.h"

class Character : public CharacterMove, public CharacterObjectList {
public:
    // ���캯��
    Character(const std::string& filename);

    // ���¼���ʱ�Ĵ���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �ͷż���ʱ�Ĵ���
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ���½�ɫλ��
    cocos2d::Vec2 updatePosition(float deltaTime);
private:
    //cocos2d::Sprite* _character;                         // ��ɫ����
};

#endif // __CHARACTER_H__