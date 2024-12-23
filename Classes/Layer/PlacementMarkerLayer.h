/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.h
 * File Function: 放置标记层类PlacementMarkerLayer的定义
 * Author:        尹诚成
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PLACEMENT_MARKER_LAYER_H_
#define _PLACEMENT_MARKER_LAYER_H_

#include "cocos2d.h"
#include "Character/Character.h"
#include "Box/Box.h"
#include "../proj.win32/Constant.h"



class PlacementMarkerLayer : public cocos2d::Layer {
public:
    // 初始化放置标记层
    virtual bool init();

    // 显示放置标记
    void showPlacementMarker();

    // 实现 PlacementMarkerLayer 类的 create 方法
    CREATE_FUNC(PlacementMarkerLayer);

private:
    Character* _character; // 角色对象

    // 创建放置标记
    void createPlacementMarker(const Location& location);

};

#endif // !_PLACEMENT_MARKER_LAYER_H_