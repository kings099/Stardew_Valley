/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     cropData.h
 * File Function: 管理农作物数据的结构体
 * Author:        胡宝怡
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
//方便在切换场景之后迅速恢复之前的农作物状态或保存当下的农作物状态
#pragma once
#ifndef __CROP_DATA_H__
#define __CROP_DATA_H__

#include "cocos2d.h"

struct CropData {
    std::string _type;  // 农作物类型
    bool _isHarvest;   // 是否可以收获
    std::string Harvest;    // 收获的东西
};

#endif // __CROP_DATA_H__

