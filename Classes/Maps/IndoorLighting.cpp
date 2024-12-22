/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorLighting.cpp
 * File Function: 模拟室内灯光变化
 * Author:        金恒宇
 * Update Date:   2024/12/21
 * License:       MIT License
 ****************************************************************/

#include "IndoorLighting.h"

IndoorLighting::IndoorLighting(cocos2d::Node* parentNode)
    : _lightingLayer(nullptr), _parentNode(parentNode) {
    // 确保父节点有效
    if (_parentNode) {
        // 创建一个半透明黑色蒙版
        _lightingLayer = cocos2d::LayerColor::create(HLAFBLACK);
        if (_lightingLayer) {
            _parentNode->addChild(_lightingLayer, ANIMATION_LAYER_GRADE); // 添加到父节点
            CCLOG("IndoorLighting applied.");
        }
    }
    else {
        CCLOG("IndoorLighting not applied due to null parentNode.");
    }
}

IndoorLighting::~IndoorLighting() {
    if (_lightingLayer) {
        if (_lightingLayer->getParent()) {
            _lightingLayer->removeFromParentAndCleanup(true); // 从父节点移除
        }
        _lightingLayer = nullptr; // 重置指针
    }
}