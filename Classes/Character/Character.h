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

class Character : public CharacterMove {
public:
    // ����Character����
    static Character* create(const std::string& filename);

    // ��ʼ��Character����
    bool init(const std::string& filename);

    // ���¼���ʱ�Ĵ���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // �ͷż���ʱ�Ĵ���
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:

};

#endif // __CHARACTER_H__