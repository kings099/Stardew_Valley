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
#include "Classes/Control/InteractionManager.h"
#include "../proj.win32/Constant.h"


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

    // 更新角色周围瓦片地图信息
    void updateTileInfo(InteractionManager* interactionManager);
protected:
    cocos2d::Sprite* _character;                         // 角色对象   
    std::vector<TileInfo> _surroundingTilesInfo;         // 角色周围瓦片地图信息
    Direction _currentDirection;                         // 当前动画方向
    
    // 更新角色位置
    cocos2d::Vec2 updatePosition(float deltaTime);

    // 保存数据
    bool saveData(const std::string& fileName);

    // 加载数据
    bool loadData(const std::string& fileName);

    // 检查文件是否存在
    bool fileExists(const std::string& fileName);
private:
    cocos2d::Vector<cocos2d::SpriteFrame*> _frames;      // 角色动画帧
    cocos2d::Vec2 _position;                             // 角色位置
    float _width;                                        // 角色宽度
    float _height;                                       // 角色高度
    float _moveSpeed;                                    // 角色速度
    bool _moveDirection[4];                              // 角色移动方向
    Direction _lastDirection;                            // 上一次动画方向
};

#endif // __CHARACTER_H__

