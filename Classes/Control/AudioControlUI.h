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

    // 创建UI
    bool init();

    // 关闭音频的回调函数
    void stopAudioCallback(cocos2d::Ref* pSender);

    // 返回场景
    static AudioControlUI* create();
};

#endif // __AUDIO_CONTROL_UI_H__
