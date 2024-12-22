/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AudioControlLayer.h
 * File Function: ��Ƶ����UI���ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/

#include "AudioControlLayer.h"
#include "audio/include/AudioEngine.h" // ������Ƶ����

USING_NS_CC;

AudioControlLayer::AudioControlLayer() : _isAudioPlaying(true), _audioButton(nullptr) {
    // ���캯��
}

AudioControlLayer::~AudioControlLayer() {
    // ��������
}

bool AudioControlLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ȡ��Ļ�ĳߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������Ƶ���ư�ť��Ĭ��ͼ��Ϊ�ر���Ƶ��
    _audioButton = ui::Button::create("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");
    _audioButton->setPosition(Vec2(visibleSize.width - _audioButton->getContentSize().width*2,
        visibleSize.height - _audioButton->getContentSize().height*2));

    // ��ӵ���¼�����
    _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::stopAudioCallback, this));

    // ����ť��ӵ���ǰ��
    this->addChild(_audioButton);

    return true;
}

void AudioControlLayer::stopAudioCallback(Ref* pSender) {
    if (_isAudioPlaying) {
        // ֹͣ������Ƶ����
        cocos2d::experimental::AudioEngine::stopAll();
        CCLOG("Audio has been stopped.");

        // ������Ƶ״̬
        _isAudioPlaying = false;

        // �ı䰴ťͼ��
        _audioButton->loadTextures("../Resources/UI/openMusic.png", "../Resources/UI/openMusic.png");

        // ���°�ť�ص�����Ϊ��ʼ��Ƶ
        _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::startAudioCallback, this));
    }
    else {
        // ������Ƶ���˴������滻Ϊ��ʵ�ʵ���Ƶ�ļ���
        cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true); // ������Ƶ

        // ������Ƶ״̬
        _isAudioPlaying = true;

        // �ı䰴ťͼ��Ϊֹͣ
        _audioButton->loadTextures("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");

        // ���°�ť�ص�����Ϊֹͣ��Ƶ
        _audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlLayer::stopAudioCallback, this));
    }
}

void AudioControlLayer::startAudioCallback(Ref* pSender) {
    // ������Ƶ
    cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true);
    CCLOG("Audio has been started.");

    // ������Ƶ״̬
    _isAudioPlaying = true;

    // �ı䰴ťͼ��
    _audioButton->loadTextures("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");

    // ���°�ť�ص�����Ϊֹͣ��Ƶ
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
