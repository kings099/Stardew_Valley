#pragma once
#ifndef __AUDIO_CONTROL_UI_H__
#define __AUDIO_CONTROL_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class AudioControlUI : public cocos2d::Layer
{
public:
    AudioControlUI();
    ~AudioControlUI();

    // ����UI
    bool init();

    // �ر���Ƶ�Ļص�����
    void stopAudioCallback(cocos2d::Ref* pSender);

    // ���س���
    static AudioControlUI* create();
};

#endif // __AUDIO_CONTROL_UI_H__
