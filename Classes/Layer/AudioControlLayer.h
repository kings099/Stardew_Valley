/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AudioControlLayer.h
 * File Function: 音频播放UI组件的定义
 * Author:        达思睿
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

    // 初始化
    bool init();

    // 创建实例
    static AudioControlLayer* create();

    // 停止音频回调函数
    void stopAudioCallback(cocos2d::Ref* pSender);

    // 播放音频回调函数
    void startAudioCallback(cocos2d::Ref* pSender);

private:
    bool isAudioPlaying;  // 音频播放状态
    cocos2d::ui::Button* audioButton; // 音频控制按钮
};

#endif // __AUDIO_CONTROL_LAYER_H__
