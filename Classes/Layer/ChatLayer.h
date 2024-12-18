#pragma once
#pragma once
#ifndef CHATLAYER_H
#define CHATLAYER_H

#include "cocos2d.h"

/**
 * @class ChatLayer
 * @brief ���ڹ�����Ϸ�е�������棬��ʾ�Ի������������ UI �����
 */
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

#endif // CHATLAYER_H
