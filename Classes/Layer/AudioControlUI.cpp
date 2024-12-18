#include "AudioControlUI.h"
#include "audio/include/AudioEngine.h" // ������Ƶ����

USING_NS_CC;

AudioControlUI::AudioControlUI() : isAudioPlaying(true), audioButton(nullptr) {
    // ���캯��
}

AudioControlUI::~AudioControlUI() {
    // ��������
}

bool AudioControlUI::init() {
    if (!Node::init()) {
        return false;
    }

    // ��ȡ��Ļ�ĳߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������Ƶ���ư�ť��Ĭ��ͼ��Ϊ�ر���Ƶ��
    audioButton = ui::Button::create("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");
    audioButton->setPosition(Vec2(visibleSize.width - audioButton->getContentSize().width / 2 - 20,
        visibleSize.height - audioButton->getContentSize().height / 2 - 20));

    // ��ӵ���¼�����
    audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));

    // ����ť��ӵ���ǰ����
    this->addChild(audioButton);

    return true;
}

void AudioControlUI::stopAudioCallback(Ref* pSender) {
    if (isAudioPlaying) {
        // ֹͣ������Ƶ����
        cocos2d::experimental::AudioEngine::stopAll();
        CCLOG("Audio has been stopped.");

        // ������Ƶ״̬
        isAudioPlaying = false;

        // �ı䰴ťͼ��Ϊ����
        audioButton->loadTextures("../Resources/UI/openMusic.png", "../Resources/UI/openMusic.png");

        // ���°�ť�ص�����Ϊ��ʼ��Ƶ
        audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::startAudioCallback, this));
    }
    else {
        // ������Ƶ���˴������滻Ϊ��ʵ�ʵ���Ƶ�ļ���
        cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true); // ������Ƶ

        // ������Ƶ״̬
        isAudioPlaying = true;

        // �ı䰴ťͼ��Ϊֹͣ
        audioButton->loadTextures("../Resources/UI/openMusic.png", "../Resources/UI/openMusic.png");

        // ���°�ť�ص�����Ϊֹͣ��Ƶ
        audioButton->addClickEventListener(CC_CALLBACK_1(AudioControlUI::stopAudioCallback, this));
    }
}

void AudioControlUI::startAudioCallback(Ref* pSender) {
    // ������Ƶ
    cocos2d::experimental::AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true);
    CCLOG("Audio has been started.");

    // ������Ƶ״̬
    isAudioPlaying = true;

    // �ı䰴ťͼ��Ϊֹͣ
    audioButton->loadTextures("../Resources/UI/closeMusic.png", "../Resources/UI/closeMusic.png");

    // ���°�ť�ص�����Ϊֹͣ��Ƶ
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
