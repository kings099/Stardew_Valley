/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.h
 * File Function: Character类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/04
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "CharacterMove.h"
#include "CharacterObjectList.h"

class Character : public CharacterMove, public CharacterObjectList {
public:
    // 构造函数
    Character(const std::string& filename);

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 更新角色位置
    cocos2d::Vec2 updatePosition(float deltaTime);
private:
    //cocos2d::Sprite* _character;                         // 角色对象
};

#endif // __CHARACTER_H__