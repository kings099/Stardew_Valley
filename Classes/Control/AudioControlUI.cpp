#include "AudioControlUI.h"
#include "audio/include/AudioEngine.h" // 引入音频引擎

USING_NS_CC;

AudioControlUI::AudioControlUI() {
    // 构造函数
}

AudioControlUI::~AudioControlUI() {
    // 析构函数
}

bool AudioControlUI::init() {
    // 获取屏幕的尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建关闭音频的按钮
    auto stopAudioButton = ui::Button::create("../Resources/stopAudioNormal.png", "../Resources/stopAudioPressed.png");
    stopAudioButton->setPosition(Vec2(visibleSize.width - stopAudioButton->getContentSize().width / 2 - 20, visibleSize.height - stopAudioButton->getContentSize().height / 2 - 20));
    stopAudioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));

    // 将按钮添加到当前场景
    this->addChild(stopAudioButton);

    return true;
}

void AudioControlUI::stopAudioCallback(Ref* pSender) {
    // 停止所有音频播放
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

