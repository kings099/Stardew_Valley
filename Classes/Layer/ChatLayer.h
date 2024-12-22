/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     ChatLayer.h
 * File Function: NPC�Ի�����UI��Ķ���
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef CHATLAYER_H
#define CHATLAYER_H

#include "cocos2d.h"
#include"proj.win32/constant.h"
#include "Character/NPC.h"
class ChatLayer : public cocos2d::Layer {
public:
    //���캯��
    ChatLayer(const std::string& message);

   //��������ʾ�Ի���
    void showMessage(const std::string& message);

    //�رնԻ��� 
    void closeDialog(cocos2d::Ref* sender);

    //��ȡʵ��
    static ChatLayer* create(const std::string& message);
    
    //�����·�ϲ������ʾ�ı����������߼���ʱ��Ż���ʾ
    void ChatLayer::addAffectionText(const std::string& affectionInfo);

private:
    cocos2d::LayerColor* chatLayer;  ///< ��͸����ɫ������
    cocos2d::Sprite* dialogBg;       ///< �Ի��򱳾�����
    cocos2d::Label* dialogLabel;     ///< ��ʾ��Ϣ�ı�ǩ
};

#endif 
