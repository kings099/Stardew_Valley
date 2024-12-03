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

    // 播放动画
    void playAnimation();

    // 更新角色位置
    void Character::updatePosition(float deltaTime);

    // 更新键盘状态显示
    void updateKeyStatus();

private:
    cocos2d::Sprite* character;                         //角色对象
    cocos2d::Label* keyStatusLabel;                     //显示按键状态的标签
    cocos2d::EventKeyboard::KeyCode lastKeyCode;        //最后一次按下的键
    float width;                                        //角色宽度
    float height;                                       //角色高度
    float moveSpeed;                                    //角色速度
    bool moveUp;                                        //是否上移
    bool moveDown;                                      //是否下移
    bool moveLeft;                                      //是否左移
    bool moveRight;                                     //是否右移
    bool animationPlaying;                              //是否正在播放动画
};

#endif // __CHARACTER_H__
