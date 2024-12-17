#ifndef __AUDIO_CONTROL_UI_H__
#define __AUDIO_CONTROL_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class AudioControlUI : public cocos2d::Node {
public:
    AudioControlUI();
    ~AudioControlUI();

    // ��ʼ��
    bool init();

    // ����ʵ��
    static AudioControlUI* create();

    // ֹͣ��Ƶ�ص�����
    void stopAudioCallback(cocos2d::Ref* pSender);

    // ������Ƶ�ص�����
    void startAudioCallback(cocos2d::Ref* pSender);

private:
    bool isAudioPlaying;  // ��Ƶ����״̬
    cocos2d::ui::Button* audioButton; // ��Ƶ���ư�ť
};

#endif // __AUDIO_CONTROL_UI_H__
