/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AudioControlLayer.h
 * File Function: ��Ƶ����UI����Ķ���
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#ifndef __AUDIO_CONTROL_LAYER_H__
#define __AUDIO_CONTROL_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class AudioControlLayer : public cocos2d::Layer {
public:
    AudioControlLayer();
    ~AudioControlLayer();

    // ��ʼ��
    bool init();

    // ����ʵ��
    static AudioControlLayer* create();

    // ֹͣ��Ƶ�ص�����
    void stopAudioCallback(cocos2d::Ref* pSender);

    // ������Ƶ�ص�����
    void startAudioCallback(cocos2d::Ref* pSender);

private:
    bool isAudioPlaying;  // ��Ƶ����״̬
    cocos2d::ui::Button* audioButton; // ��Ƶ���ư�ť
};

#endif // __AUDIO_CONTROL_LAYER_H__
