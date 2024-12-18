#include "AudioControlUI.h"
#include "audio/include/AudioEngine.h" // 引入音频引擎

USING_NS_CC;

AudioControlUI::AudioControlUI() : isAudioPlaying(true), audioButton(nullptr) {
    // 构造函数
}

AudioControlUI::~AudioControlUI() {
    // 析构函数
}

bool AudioControlUI::init() {
    if (!Node::init()) {
        return false;
    }

    // 获取屏幕的尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建音频控制按钮（默认图标为关闭音频）
    audioButton = ui::Button::create("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");
    audioButton->setPosition(Vec2(visibleSize.width - audioButton->getContentSize().width / 2 - 20,
        visibleSize.height - audioButton->getContentSize().height / 2 - 20));

    // 添加点击事件监听
    audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));

    // 将按钮添加到当前场景
    this->addChild(audioButton);

    return true;
}

void AudioControlUI::stopAudioCallback(Ref* pSender) {
    if (isAudioPlaying) {
        // 停止所有音频播放
        cocos2d::experimental::AudioEngine::stopAll();
        CCLOG("Audio has been stopped.");

        // 更新音频状态
        isAudioPlaying = false;

        // 改变按钮图标为播放
        audioButton->loadTextures("../Resources/UI/openMusic.png", "../Resources/UI/openMusic.png");

        // 更新按钮回调函数为开始音频
        audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::startAudioCallback, this));
    }
    else {
        // 播放音频（此处可以替换为你实际的音频文件）
        cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true); // 播放音频

        // 更新音频状态
        isAudioPlaying = true;

        // 改变按钮图标为停止
        audioButton->loadTextures("../Resources/UI/openMusic.png", "../Resources/UI/openMusic.png");

        // 更新按钮回调函数为停止音频
        audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));
    }
}

void AudioControlUI::startAudioCallback(Ref* pSender) {
    // 播放音频
    cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true);
    CCLOG("Audio has been started.");

    // 更新音频状态
    isAudioPlaying = true;

    // 改变按钮图标为停止
    audioButton->loadTextures("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");

    // 更新按钮回调函数为停止音频
    audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));
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
