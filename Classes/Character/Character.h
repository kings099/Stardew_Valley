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

class Character :  public CharacterAction {
public:
    // 获取单例
    static Character* getInstance(const std::string& filename);

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 更新位置
    cocos2d::Vec2 updatePosition(float deltaTime);

    // 判断角色是否打开物品栏
    const bool checkObjectListStatus();
private:
    //cocos2d::Sprite* _character;                        // 角色精灵


    // 构造函数
    Character(const std::string& filename);
};

#endif // __CHARACTER_H__