/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameViewController.cpp
 * File Function: 游戏视角控制类GameViewController的实现
 * Author:        金恒宇
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#include "GameViewController.h"

USING_NS_CC;

GameViewController::GameViewController(Character* character,FarmMap* farmmap)
    : _character(character),_farmmap(farmmap) {}

void GameViewController::update(float deltaTime) {
    
    // 获取角色的位置
    Vec2 characterPosition = _character->updatePosition(deltaTime);

    Vec2 mapPosition = _farmmap->getPosition();
    Size mapSize = _farmmap->getMapSize();

    // 获取屏幕可视区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize(); 

    // 计算摄像机应该的位置：确保角色始终处于屏幕中央且限制摄像机位置确保不超出地图的边界
    Vec2 targetCameraPosition;
    targetCameraPosition.x = std::max(characterPosition.x - mapPosition.x  , visibleSize.width / 2);
    targetCameraPosition.y = std::max(characterPosition.y - mapPosition.y, visibleSize.height / 2);
    targetCameraPosition.x = std::min(targetCameraPosition.x, mapSize.width - visibleSize.width / 2);
    targetCameraPosition.y = std::min(targetCameraPosition.y, mapSize.height - visibleSize.height / 2);

  // 获取默认的摄像机并平滑地更新它的位置
 auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
 Vec2 currentCameraPosition = camera->getPosition();

 // 以较慢的速度平滑过渡摄像机位置
 float lerpSpeed = 0.1f; // 调整此值以改变过渡的平滑度
 Vec2 newCameraPosition = currentCameraPosition.lerp(targetCameraPosition, lerpSpeed);
 camera->setPosition(newCameraPosition);
