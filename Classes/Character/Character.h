/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Character.h
 * File Function: Character类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/07
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "CharacterMove.h"
#include "CharacterAction.h"
#include <memory>

class Character : public CharacterAction {
public:
    // 获取单例，返回智能指针
    static std::unique_ptr<Character> getInstance(const std::string& filename);
    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 更新位置
    cocos2d::Vec2 updatePosition(float deltaTime);

    // 获取角色精灵节点
    cocos2d::Sprite* getCharacterSprite() const;

    // 构造函数私有化
    Character(const std::string& filename);
private:
    // 禁止拷贝和赋值
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;



    int _money;                                 // 角色金钱
    int _currentEnergy;                         // 角色能量
    int _maxEnergy;                             // 角色最大能量
};

#endif // __CHARACTER_H__