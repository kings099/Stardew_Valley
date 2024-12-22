/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorLighting.h
 * File Function: 模拟室内灯光变化的辅助类
 * Author:        金恒宇
 * Update Date:   2024/12/21
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef INDOOR_LIGHTING_H
#define INDOOR_LIGHTING_H
#include "cocos2d.h"

// 使用RAII管理室内灯光
class IndoorLighting {
public:
    // 构造函数：初始化并添加灯光层
    explicit IndoorLighting(cocos2d::Node* parentNode);

    // 析构函数：移除灯光层
    ~IndoorLighting();

private:
    cocos2d::LayerColor* _lightingLayer; // 灯光层
    cocos2d::Node* _parentNode;          // 父节点
};
#endif // __INDOOR_LIGHTING_H_
