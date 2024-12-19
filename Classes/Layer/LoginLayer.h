/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LoginLayer.h
 * File Function: �û���¼UI��Ķ���
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __LOGIN_LAYER_H__
#define __LOGIN_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

class LoginLayer : public Layer
{
public:
    // ���캯��
    LoginLayer();
    virtual ~LoginLayer();

    // ��������
    static LoginLayer* create();

    // ��ʼ������
    bool init();

    // �ύ��ť�ص�
    void onSubmitClicked(Ref* sender);


private:
    // �����ؼ�
    cocos2d::ui::TextField* usernameInput;
    cocos2d::ui::TextField* farmNameInput;
    cocos2d::ui::TextField* favoriteInput;

    // ��ť�ؼ�
    cocos2d::ui::Button* submitButton;

    // ��¼�����
    LayerColor* loginLayer;
};

#endif // __LOGIN_LAYER_H__
