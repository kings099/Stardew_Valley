/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PlacementMarkerLayer.h
 * File Function: ���ñ�ǲ���PlacementMarkerLayer�Ķ���
 * Author:        ���ϳ�
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
    // ��ʼ�����ñ�ǲ�
    virtual bool init();

    // ��ʾ���ñ��
    void showPlacementMarker();

    // ʵ�� PlacementMarkerLayer ��� create ����
    CREATE_FUNC(PlacementMarkerLayer);

private:
    // �������ñ��
<<<<<<< Updated upstream
    void createPlacementMarker(const int &index);
=======
    void createPlacementMarker(const int& index);
>>>>>>> Stashed changes
    Character* _character; // ��ɫ����
};

#endif // !_PLACEMENT_MARKER_LAYER_H_