/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManagerUI.h
 * File Function: ��ʾʱ����Ϣ��UI��������
 * Author:        ��˼�
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#pragma once
#include "cocos2d.h"


class TimeManagerUI : public cocos2d::Layer
{
public:
    static TimeManagerUI* create();  // ���� TimeManagerUI ����
    virtual bool init() override;  // ��ʼ��

    void updateTimeDisplay();  // ����ʱ����ʾ


private:
    cocos2d::Label* timeLabel1;  // ��ʾ���ں����ڵı�ǩ
    cocos2d::Label* timeLabel2;  // ��ʾ����/���Ϻ�Сʱ�ı�ǩ
    cocos2d::Sprite* backgroundSprite;  // ������ΪUI������ͼƬ

    cocos2d::Size visibleSize;   // �ɼ�����Ĵ�С
};
