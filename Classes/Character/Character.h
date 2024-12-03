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

class Character : public CharacterMove {
public:
    // 创建Character对象
    static Character* create(const std::string& filename);

    // 初始化Character对象
    bool init(const std::string& filename);

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:

};

#endif // __CHARACTER_H__