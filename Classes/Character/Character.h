/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     Character.h
 * File Function: Character类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/02
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

class Character : public cocos2d::Node {
public:
    //创建对象
    static Character* create(const std::string& filename);

    //初始化
    bool init(const std::string& filename);

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 更新角色位置
    void Character::updatePosition(float deltaTime);

private:
    cocos2d::Sprite* character;     //角色对象
    float moveSpeed;                //速度
    bool moveUp;                    //是否上移
    bool moveDown;                  //是否下移
    bool moveLeft;                  //是否左移
    bool moveRight;                 //是否右移
};

#endif // __CHARACTER_H__
