/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.h
 * File Function: 放置标记层类PlacementMarkerLayer的定义
 * Author:        尹诚成
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PLACEMENT_MARKER_LAYER_H_
#define _PLACEMENT_MARKER_LAYER_H_

#include "cocos2d.h"
#include "Character/Character.h"
#include "proj.win32/Constant.h"
#include "proj.win32/ObjectConstant.h"


class PlacementMarkerLayer : public cocos2d::Layer {
public:
    // 初始化放置标记层
    virtual bool init();

    // 显示放置标记
    void showPlacementMarker();

    // 实现 PlacementMarkerLayer 类的 create 方法
    CREATE_FUNC(PlacementMarkerLayer);

private:
    // 创建放置标记
<<<<<<< Updated upstream
    void createPlacementMarker(const int &index);
=======
    void createPlacementMarker(const int& index);
>>>>>>> Stashed changes
    Character* _character; // 角色对象
};

#endif // !_PLACEMENT_MARKER_LAYER_H_