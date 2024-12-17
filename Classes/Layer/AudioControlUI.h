#ifndef __AUDIO_CONTROL_UI_H__
#define __AUDIO_CONTROL_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class AudioControlUI : public cocos2d::Node {
public:
    AudioControlUI();
    ~AudioControlUI();

    // 初始化
    bool init();

    // 创建实例
    static AudioControlUI* create();

    // 停止音频回调函数
    void stopAudioCallback(cocos2d::Ref* pSender);

    // 播放音频回调函数
    void startAudioCallback(cocos2d::Ref* pSender);

private:
    bool isAudioPlaying;  // 音频播放状态
    cocos2d::ui::Button* audioButton; // 音频控制按钮
};

#endif // __AUDIO_CONTROL_UI_H__
