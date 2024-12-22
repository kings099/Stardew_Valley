/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorLighting.cpp
 * File Function: ģ�����ڵƹ�仯
 * Author:        �����
 * Update Date:   2024/12/21
 * License:       MIT License
 ****************************************************************/

#include "IndoorLighting.h"

IndoorLighting::IndoorLighting(cocos2d::Node* parentNode)
    : _lightingLayer(nullptr), _parentNode(parentNode) {
    // ȷ�����ڵ���Ч
    if (_parentNode) {
        // ����һ����͸����ɫ�ɰ�
        _lightingLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
        if (_lightingLayer) {
            _parentNode->addChild(_lightingLayer, 10); // ��ӵ����ڵ�
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
        _lightingLayer->removeFromParentAndCleanup(true); // �Ӹ��ڵ��Ƴ�
    }
    _lightingLayer = nullptr; // ����ָ��
}