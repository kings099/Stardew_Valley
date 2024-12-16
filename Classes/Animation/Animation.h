/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animation.h
 * File Function: 动画类头文件
 * Author:        胡宝怡
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#ifndef ANIMATION_HELPER_H
#define ANIMATION_HELPER_H

#include "cocos2d.h"
USING_NS_CC;

class AnimationHelper {
public:
    // 播放除草动画
    static void playWeedingAnimation(const Vec2& position, TMXTiledMap* farmMap);

    // 播放碎石动画
    static void playStoneBreakingAnimation(const Vec2& position, TMXTiledMap* farmMap);
    //砍木桩动画
    static void playWoodCuttingAnimation(const Vec2& position, TMXTiledMap* farmMap);

private:
    // 创建帧动画的通用方法
    static Vector<SpriteFrame*> loadFrames(const std::string& basePath, int frameCount, const Rect& frameRect);
};

#endif // ANIMATION_HELPER_H
