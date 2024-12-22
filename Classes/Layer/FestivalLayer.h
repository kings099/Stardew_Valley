/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FestivalLayer.h
 * File Function: ���ջUI�������
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef FESTIVALLAYER_H
#define FESTIVALLAYER_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"  // ����Cocos2d UI���
#include "ChatLayer.h"    // ����ChatLayer��
#include "Control/TimeManager.h"  // ����TimeManager��

class FestivalLayer : public cocos2d::Layer {
public:
    FestivalLayer();  // ���캯��
    ~FestivalLayer();  // ��������

    // ��ʼ������
    bool init();

    // ����������һ��FestivalLayerʵ��
    static FestivalLayer* create();

    // ���°�ť����ʾ״̬
    void updateFestivalButtonVisibility();
    void  updateCommunityButtonVisibility();
    void onButtonClicked(Ref* pSender, const std::string& message);



private:
    // ���հ�ť
    cocos2d::ui::Button* _festivalButton;
    cocos2d::ui::Button* _communityButton;
    // ��ť����ص�����ʾ�Ի���
    void onFestivalButtonClicked(cocos2d::Ref* pSender);
};

#endif // FESTIVALLAYER_H
