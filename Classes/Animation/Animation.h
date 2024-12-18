/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animation.h
 * File Function: ������ͷ�ļ�
 * Author:        ������
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#ifndef ANIMATION_HELPER_H
#define ANIMATION_HELPER_H

#include "cocos2d.h"
USING_NS_CC;

class AnimationHelper {
public:
    // ���ų��ݶ���
    static void playWeedingAnimation(const Vec2& position, TMXTiledMap* farmMap);

    // ������ʯ����
    static void playStoneBreakingAnimation(const Vec2& position, TMXTiledMap* farmMap);
    //��ľ׮����
    static void playWoodCuttingAnimation(const Vec2& position, TMXTiledMap* farmMap);

private:
    // ����֡������ͨ�÷���
    static Vector<SpriteFrame*> loadFrames(const std::string& basePath, int frameCount, const Rect& frameRect);
};

#endif // ANIMATION_HELPER_H
