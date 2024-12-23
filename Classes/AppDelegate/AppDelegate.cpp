/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     AppDelegate.cpp
 * File Function: Main function of the game.
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#include "AppDelegate.h"
#include "../Classes/Scene/GameStartScene.h"
#include "proj.win32/Constant.h"
#include "Classes/Scene/GameMainScene.h"
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

// 初始化 OpenGL 上下文属性
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
    // 获取游戏引擎的导演实例
    auto director = Director::getInstance();

    // 获取 OpenGL 视图
    auto glview = director->getOpenGLView();

    // 如果 OpenGL 视图不存在，根据平台创建
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // 在 Windows、Mac、Linux 平台上创建 OpenGL 视图
        glview = GLViewImpl::createWithRect(APPLICATION_TITLE, cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        // 在其他平台上创建 OpenGL 视图
        glview = GLViewImpl::create(APPLICATION_TITLE);
#endif
        // 设置 OpenGL 视图
        director->setOpenGLView(glview);
    }

    //是否开启性能统计信息
    director->setDisplayStats(false);

    // 设置游戏的帧率，此处为60帧
    director->setAnimationInterval(1.0f / FRAME_RATE);

    // 设置分辨率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    // 获取窗口的帧大小
    const auto frameSize = glview->getFrameSize();
   
    //根据窗口的大小设置内容缩放因子
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

    // 创建启动场景类
    auto scene = GameStartScene::createScene();

    // 运行启动场景
    director->runWithScene(scene);

    // 预加载音乐
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

// 当应用程序进入后台时调用此函数
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    AudioEngine::resumeAll();
}
