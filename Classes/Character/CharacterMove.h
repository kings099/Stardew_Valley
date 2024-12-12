/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterMove.h
 * File Function: 角色移动CharacterMove类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/07
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTERMOVE_H__
#define __CHARACTERMOVE_H__

#include "cocos2d.h"


class CharacterMove :virtual public cocos2d::Node {
public:
    //构造函数
    CharacterMove();

    // 按下键盘事件触发函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘事件触发函数
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 播放动画
    void playAnimation();

    // 获取角色当前位置
    cocos2d::Vec2 getPosition();

    // 设置角色位置
    void setPosition(const cocos2d::Vec2& position);

    // 强制停止角色移动
    void stopMove();
protected:
    cocos2d::Sprite* _character;                         // 角色对象
   
    // 更新角色位置
    cocos2d::Vec2 updatePosition(float deltaTime);
private:
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
};

#endif // __CHARACTER_H__

