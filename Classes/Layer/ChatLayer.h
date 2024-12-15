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
    /**
     * @brief ���캯��
     *
     * @param message ��ʾ����Ϣ�ı�
     */
    ChatLayer(const std::string& message);

    /**
     * @brief ��������ʾ�Ի���
     *
     * @param message �Ի�������ʾ���ı�����
     */
    void showMessage(const std::string& message);

    /**
     * @brief �رնԻ���
     *
     * @param sender �����ر��¼��Ķ���
     */
    void closeDialog(cocos2d::Ref* sender);

    /**
     * @brief ��ȡ ChatLayer ʵ��
     *
     * @param message �Ի�������ʾ���ı�����
     * @return ChatLayer* ChatLayer ʵ��
     */
    static ChatLayer* create(const std::string& message);

private:
    cocos2d::LayerColor* chatLayer;  ///< ��͸����ɫ������
    cocos2d::Sprite* dialogBg;       ///< �Ի��򱳾�����
    cocos2d::Label* dialogLabel;     ///< ��ʾ��Ϣ�ı�ǩ
};

#endif // CHATLAYER_H
