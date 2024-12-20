/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Animation.cpp
 * File Function: 动画类，包含各类动画函数
 * Author:        胡宝怡
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#include "Animation.h"

// 通用加载帧方法
Vector<SpriteFrame*> AnimationHelper::loadFrames(const std::string& basePath, int frameCount, const Rect& frameRect) {
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= frameCount; ++i) {
        std::string frameName = StringUtils::format("%s%d.png", basePath.c_str(), i);
        auto frame = SpriteFrame::create(frameName, frameRect);
        if (frame == nullptr) {
            CCLOG("Error: Failed to load frame: %s", frameName.c_str());
            continue;
        }
        frames.pushBack(frame);
    }
    return frames;
}

// 播放砍木桩动画
void AnimationHelper::playWoodCuttingAnimation(const Vec2& position, TMXTiledMap* farmMap) {
    CCLOG("Playing wood cutting animation at position (%f, %f)...", position.x, position.y);

    // 创建临时精灵
    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for wood cutting animation.");
        return;
    }
    tempSprite->setPosition(position);
    tempSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    farmMap->addChild(tempSprite, ANIMATION_LAYER_GRADE);
    tempSprite->setScale(WOOD_CUT_RATIO);

    // 加载砍木桩的帧
    auto frames = loadFrames("../Resources/Animations/tree_root/tree_root_", 5, Rect(0, 0, 128, 134));
    if (frames.empty()) {
        CCLOG("Error: No frames loaded for wood cutting animation");
        tempSprite->removeFromParent();
        return;
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
    auto animate = Animate::create(animation);

    // 播放完动画后删除精灵
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}
// 播放除草动画
void AnimationHelper::playWeedingAnimation(const Vec2& position, TMXTiledMap* farmMap) {
    CCLOG("Playing weeding animation at position (%f, %f)...", position.x, position.y);

    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for weeding animation.");
        return;
    }
    tempSprite->setPosition(position);
    farmMap->addChild(tempSprite, ANIMATION_LAYER_GRADE);
    tempSprite->setScale(WEEDING_RATIO);

    auto frames = loadFrames("../Resources/Animations/Weeding/weeding_", 7, Rect(0, 0, 64, 72));
    if (frames.empty()) {
        CCLOG("Error: No frames loaded for weeding animation");
        tempSprite->removeFromParent();
        return;
    }

    auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
    auto animate = Animate::create(animation);
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}

// 播放碎石动画
void AnimationHelper::playStoneBreakingAnimation(const Vec2& position, TMXTiledMap* farmMap) {
    CCLOG("Playing stone breaking animation at position (%f, %f)...", position.x, position.y);

    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for stone breaking animation.");
        return;
    }
    tempSprite->setPosition(position);
    tempSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    farmMap->addChild(tempSprite, ANIMATION_LAYER_GRADE);
    tempSprite->setScale(STONE_BREAK_RATIO);

    auto frames = loadFrames("../Resources/Animations/stone_break/stone_break_", 5, Rect(0, 0, 133, 136));
    if (frames.empty()) {
        CCLOG("Error: No frames loaded for stone breaking animation");
        tempSprite->removeFromParent();
        return;
    }

    auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
    auto animate = Animate::create(animation);
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}
