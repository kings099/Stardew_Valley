#include "AudioControlUI.h"
#include "audio/include/AudioEngine.h" // ������Ƶ����

USING_NS_CC;

AudioControlUI::AudioControlUI() {
    // ���캯��
}

AudioControlUI::~AudioControlUI() {
    // ��������
}

bool AudioControlUI::init() {
    // ��ȡ��Ļ�ĳߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����ر���Ƶ�İ�ť
    auto stopAudioButton = ui::Button::create("../Resources/stopAudioNormal.png", "../Resources/stopAudioPressed.png");
    stopAudioButton->setPosition(Vec2(visibleSize.width - stopAudioButton->getContentSize().width / 2 - 20, visibleSize.height - stopAudioButton->getContentSize().height / 2 - 20));
    stopAudioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));

    // ����ť��ӵ���ǰ����
    this->addChild(stopAudioButton);

    return true;
}

void AudioControlUI::stopAudioCallback(Ref* pSender) {
    // ֹͣ������Ƶ����
    cocos2d::experimental::AudioEngine::stopAll();
    CCLOG("Audio has been stopped.");
}

AudioControlUI* AudioControlUI::create() {
    AudioControlUI* ret = new AudioControlUI();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

