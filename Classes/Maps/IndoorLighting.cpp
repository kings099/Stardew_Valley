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
        _lightingLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
        if (_lightingLayer) {
            _parentNode->addChild(_lightingLayer, 10); // 添加到父节点
            CCLOG("IndoorLighting applied.");
        }
    }
    else {
        CCLOG("IndoorLighting not applied due to null parentNode.");
    }
}

IndoorLighting::~IndoorLighting() {
    if (_lightingLayer && _lightingLayer->getParent()) {
        CCLOG("Removing lighting layer from parent.");
        _lightingLayer->removeFromParentAndCleanup(true); // 从父节点移除
    }
    _lightingLayer = nullptr; // 重置指针
}