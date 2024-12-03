/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: 游戏视角控制类GameViewController的实现
 * Author:        金恒宇
 * Update Date:   2024/12/3
 * License:       MIT License
 ****************************************************************/

#include "GameViewController.h"

USING_NS_CC;

GameViewController::GameViewController(Character* character)
    : _character(character) {}

void GameViewController::update(float deltaTime) {
    
    // 获取角色的位置
    Vec2 characterPosition = _character->updatePosition(deltaTime);

    // 获取屏幕可视区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize(); 

    // 计算摄像机应该的位置：确保角色始终处于屏幕中央
    Vec2 targetCameraPosition = Vec2(characterPosition.x + visibleSize.width / 4,
        characterPosition.y + visibleSize.height / 4);

    CCLOG(" % f, % f", characterPosition.x, characterPosition.y);
    // 获取默认的摄像机并平滑地更新它的位置
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    Vec2 currentCameraPosition = camera->getPosition();

    // 以较慢的速度平滑过渡摄像机位置
    float lerpSpeed = 0.1f; // 调整此值以改变过渡的平滑度
    Vec2 newCameraPosition = currentCameraPosition.lerp(targetCameraPosition, lerpSpeed);
    camera->setPosition(newCameraPosition);
}
