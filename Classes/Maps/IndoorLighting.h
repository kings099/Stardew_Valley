/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorLighting.h
 * File Function: ģ�����ڵƹ�仯�ĸ�����
 * Author:        �����
 * Update Date:   2024/12/21
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef INDOOR_LIGHTING_H
#define INDOOR_LIGHTING_H
#include "cocos2d.h"
#include "proj.win32/Constant.h"

// ʹ��RAII�������ڵƹ�
class IndoorLighting {
public:

    // ���캯������ʼ������ӵƹ��
    explicit IndoorLighting(cocos2d::Node* parentNode);

    // �����������Ƴ��ƹ��
    ~IndoorLighting();

private:
    // �ƹ��
    cocos2d::LayerColor* _lightingLayer;

    // ���ڵ�
    cocos2d::Node* _parentNode;         
};
#endif // __INDOOR_LIGHTING_H_
