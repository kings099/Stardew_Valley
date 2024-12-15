/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     cropData.h
 * File Function: ����ũ�������ݵĽṹ��
 * Author:        ������
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
//�������л�����֮��Ѹ�ٻָ�֮ǰ��ũ����״̬�򱣴浱�µ�ũ����״̬
#pragma once
#ifndef __CROP_DATA_H__
#define __CROP_DATA_H__

#include "cocos2d.h"

struct CropData {
    std::string type;  // ũ��������
    cocos2d::Vec2 position; // λ��
    int growthStage;   // ��ǰ�����׶�
    bool isWatered;    // �Ƿ��ѱ���ˮ
};

#endif // __CROP_DATA_H__

