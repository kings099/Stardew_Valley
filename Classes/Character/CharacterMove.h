/****************************************************************
 * Project Name:  Stardew Valley
<<<<<<< Updated upstream
 * File Name:     Character.h
 * File Function: Character类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/03
=======
 * File Name:     CharacterMove.h
 * File Function: CharacterMove类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/04
>>>>>>> Stashed changes
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTERMOVE_H__
#define __CHARACTERMOVE_H__

#include "cocos2d.h"
<<<<<<< Updated upstream
#include <unordered_map>
=======

>>>>>>> Stashed changes

class CharacterMove : public cocos2d::Node {
public:
    //创建对象
    static CharacterMove* create(const std::string& filename);

    //初始化
    bool init(const std::string& filename);

    // 按下键盘时的处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 释放键盘时的处理
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 播放动画
    void playAnimation();

    // 更新角色位置
    cocos2d::Vec2 updatePosition(float deltaTime);

private:
<<<<<<< Updated upstream
    cocos2d::Sprite* character;                         // 角色对象
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;      // 角色动画帧
    float width;                                        // 角色宽度
    float height;                                       // 角色高度
    float moveSpeed;                                    // 角色速度
    bool moveUp;                                        // 是否上移
    bool moveDown;                                      // 是否下移
    bool moveLeft;                                      // 是否左移
    bool moveRight;                                     // 是否右移
    bool animationPlaying;                              // 是否正在播放动画
    std::string currentDirection;                       // 当前动画方向
    std::string lastDirection;                          // 上一次动画方向
=======
    cocos2d::Sprite* _character;                         // 角色对象
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
>>>>>>> Stashed changes
};

#endif // __CHARACTER_H__
