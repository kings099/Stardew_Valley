/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AudioControlLayer.h
 * File Function: 音频播放UI层的实现
 * Author:        达思睿
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/

#include "AudioControlLayer.h"
#include "audio/include/AudioEngine.h" // 引入音频引擎

USING_NS_CC;

AudioControlLayer::AudioControlLayer() : _isAudioPlaying(true), _audioButton(nullptr) {
    // 构造函数
}

AudioControlLayer::~AudioControlLayer() {
    // 析构函数
}

bool AudioControlLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // 获取屏幕的尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建音频控制按钮（默认图标为关闭音频）
    _audioButton = ui::Button::create("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");
    _audioButton->setPosition(Vec2(visibleSize.width - _audioButton->getContentSize().width*2,
        visibleSize.height - _audioButton->getContentSize().height*2));

    // 添加点击事件监听
    _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::stopAudioCallback, this));

    // 将按钮添加到当前层
    this->addChild(_audioButton);

    return true;
}

void AudioControlLayer::stopAudioCallback(Ref* pSender) {
    if (_isAudioPlaying) {
        // 停止所有音频播放
        cocos2d::experimental::AudioEngine::stopAll();
        CCLOG("Audio has been stopped.");

        // 更新音频状态
        _isAudioPlaying = false;

        // 改变按钮图标
        _audioButton->loadTextures("../Resources/UI/openMusic.png", "../Resources/UI/openMusic.png");

        // 更新按钮回调函数为开始音频
        _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::startAudioCallback, this));
    }
    else {
        // 播放音频（此处可以替换为你实际的音频文件）
        cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true); // 播放音频

        // 更新音频状态
        _isAudioPlaying = true;

        // 改变按钮图标为停止
        _audioButton->loadTextures("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");

        // 更新按钮回调函数为停止音频
        _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::stopAudioCallback, this));
    }
}

void AudioControlLayer::startAudioCallback(Ref* pSender) {
    // 播放音频
    cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true);
    CCLOG("Audio has been started.");

    // 更新音频状态
    _isAudioPlaying = true;

    // 改变按钮图标
    _audioButton->loadTextures("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");

    // 更新按钮回调函数为停止音频
    _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::stopAudioCallback, this));
}

AudioControlLayer* AudioControlLayer::create() {
    AudioControlLayer* ret = new AudioControlLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
