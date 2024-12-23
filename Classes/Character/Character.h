/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Character.h
 * File Function: Character类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/19
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "CharacterMove.h"
#include "CharacterAction.h"

class Character :  public CharacterAction {
public:
    // 获取单例
    static Character* getInstance();

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 按下鼠标时的处理
    bool onMouseDown(cocos2d::Event* event, GameCharacterAction& gameCharacterAction, cocos2d::Vec2& targetTilePos, InteractionManager* interactionManager);

    // 更新位置
    cocos2d::Vec2 updatePosition(float deltaTime);

    // 获取角色精灵节点
    cocos2d::Sprite* getCharacterSprite();

    // 保存数据
    bool saveData();

    // 加载数据
    bool loadData(const std::string& fileName);
private:
    // 禁止拷贝和赋值
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    // 构造函数私有化
    Character();

    int _currentEnergy;                         // 角色能量
    int _maxEnergy;                             // 角色最大能量
};

#endif // __CHARACTER_H__