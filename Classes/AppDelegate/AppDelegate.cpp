#include "AppDelegate.h"
#include "../Classes/Scene/GameStartScene.h"
#include "proj.win32/Constant.h"
#include "Classes/Scene/GameMainScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif


#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
static cocos2d::Size smallResolutionSize = cocos2d::Size(SMALL_RESOLUTION_WIDTH, SMALL_RESOLUTION_HEIGHT);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(MEDIUM_RESOLUTION_WIDTH, MEDIUM_RESOLUTION_HEIGHT);
static cocos2d::Size largeResolutionSize = cocos2d::Size(LARGE_RESOLUTION_WIDTH, LARGE_RESOLUTION_HEIGHT);



AppDelegate::~AppDelegate() 
{

    AudioEngine::end();

}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // ��ȡ��Ϸ����ĵ���ʵ��
    auto director = Director::getInstance();
    // ��ȡ OpenGL ��ͼ
    auto glview = director->getOpenGLView();

    // ��� OpenGL ��ͼ�����ڣ�����ƽ̨����
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // �� Windows��Mac��Linux ƽ̨�ϴ��� OpenGL ��ͼ
        glview = GLViewImpl::createWithRect(APPLICATION_TITLE, cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        // ������ƽ̨�ϴ��� OpenGL ��ͼ
        glview = GLViewImpl::create(APPLICATION_TITLE);
#endif
        // ���� OpenGL ��ͼ
        director->setOpenGLView(glview);
    }

    //�Ƿ�������ͳ����Ϣ
    director->setDisplayStats(false);

    // ������Ϸ��֡�ʣ��˴�Ϊ60֡
    director->setAnimationInterval(1.0f / FRAME_RATE);

    // ���÷ֱ���
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    // ��ȡ���ڵ�֡��С
    const auto frameSize = glview->getFrameSize();
   
    //���ݴ��ڵĴ�С����������������
    if (frameSize.height > mediumResolutionSize.height){        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height){        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    else{        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // ��������������
    auto scene = GameStartScene::createScene();

    // ������������
    director->runWithScene(scene);

    AudioEngine::preload("../Resources/Music/HelloMusic.mp3", [](bool success) {
        if (success) {
            CCLOG("Audio loaded successfully");
            AudioEngine::play2d("../Resources/Music/HelloMusic.mp3", true);
        }
        else {
            CCLOG("Audio failed to load");
        }
        });

    return true;
}

// ��Ӧ�ó�������̨ʱ���ô˺���
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();


    AudioEngine::pauseAll();

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    AudioEngine::resumeAll();

}
