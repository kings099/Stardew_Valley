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
    std::string _type;  // ũ��������
    bool _isHarvest;   // �Ƿ�����ջ�
    std::string _Harvest;    // �ջ�Ķ���
    int _growthStage;
    bool _isWatered;
    int _daysWithoutWater;      // ȱˮ������
    bool _hasPests;             // �Ƿ��к���
    bool _isFertilized;         // �Ƿ�ʩ��
};

#endif // __CROP_DATA_H__

