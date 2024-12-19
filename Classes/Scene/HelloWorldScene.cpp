/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     HelloScene.cpp
 * File Function: 游戏启动场景类的实现
 * Author:        达思睿
 * Update Date:   2024/12/3
 * License:       MIT License
 ****************************************************************/
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Layer/LoginLayer.h"
#include "ui/CocosGUI.h"
#include "../Classes/Maps/FarmMap.h"
#include "../Classes/Character/CharacterInfo.h"
#include "../Classes/MenuImage/HoverMenuItemImage.h"
#include "GameMainScene.h"
#include "Control/NpcManager.h"             
#include "Control/NpcInteractionManager.h"  
#include "Layer/AudioControlLayer.h"

using namespace cocos2d::experimental;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }
 
    // 初始化 NPC 和管理器
    NpcManager::getInstance()->initializeNPCs();  // 初始化 NPC
    CCLOG("NPC initialization completed.");
    // 获取 Abigail NPC
    NPC* abigail = NpcManager::getInstance()->getNPCByName("Abigail");
    // 初始化单例对象
    NpcManager::getInstance();  // 初始化 NPC 管理器
    TimeManager::getInstance();  // 初始化时间管理器
    GiftItemManager::getInstance();  // 初始化礼物物品管理器

    // 如果 Abigail 存在，则将其添加到场景中
    if (abigail) {
        this->addChild(abigail, 4);  // 将整个 NPC 对象添加到场景中
        abigail->startWalkingAnimation();  // 启动动画
        CCLOG("Abigail added to scene.");
    }
    else {
        CCLOG("Abigail NPC not found!");  // 如果没有找到 Abigail NPC，则打印错误日志
    }
    CCLOG("NPC initialization completed.");
    // 获取全局尺寸大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载背景图片,层级为0
    this->initBackground();
  
   
    // 加载并设置游戏标题图片,层级为1
    titleSprite = Sprite::create("../Resources/Helloworld/gameTitle.png");  
    if (titleSprite == nullptr) {
        problemLoading("'gameTitle.png'");
    }
    else {
        // 设置标题图片的位置
        titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
        this->addChild(titleSprite, 1);  // 将标题添加到场景中
    }
   
    //创建开始结束菜单项，层级为2
    this->createMenuWithImage();
  
    // 创建音频控制层并添加到场景,层级为2
    auto audioControlLayer = AudioControlLayer::create();
    this->addChild(audioControlLayer);

    return true;
}

void HelloWorld::createMenuWithImage()
{
    // 获取当前可见区域（窗口）或屏幕区域的大小（宽度和高度）
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建 "开始" 按钮的图像
    startItem = HoverMenuItemImage::create(
        "../Resources/Helloworld/start.png",   // 普通状态下的图片
        "../Resources/Helloworld/start_.png",  // 悬停状态下的图片
        CC_CALLBACK_1(HelloWorld::startGameCallback, this)  // 点击时调用的回调函数
    );
    startItem->setPosition(Vec2(origin.x + visibleSize.width * 0.33, origin.y + visibleSize.height * 0.2f)); // 设置 "开始" 按钮的位置

    // 创建 "结束" 按钮的图像
    exitItem = HoverMenuItemImage::create(
        "../Resources/Helloworld/end.png",    // 普通状态下的图片
        "../Resources/Helloworld/end_.png",   // 悬停状态下的图片
        CC_CALLBACK_1(HelloWorld::exitGameCallback, this)  // 点击时调用的回调函数
    );
    exitItem->setPosition(Vec2(origin.x + visibleSize.width * 0.67, origin.y + visibleSize.height * 0.2f)); // 设置 "结束" 按钮的位置

    // 创建菜单，将 "开始" 和 "结束" 按钮添加到菜单中
    auto menu = Menu::create(startItem, exitItem, nullptr);
    menu->setPosition(Vec2::ZERO);  // 设置菜单的原点位置
    this->addChild(menu, 2);  // 将菜单添加到场景中
   
}

void HelloWorld::initBackground() {
    // 获取屏幕的尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建两个背景图
    auto background1 = Sprite::create("../Resources/Helloworld/Cloud.png");
    auto background2 = Sprite::create("../Resources/Helloworld/Cloud.png");

    // 设置背景图片的缩放使其填满屏幕
    float scaleX = visibleSize.width / background1->getContentSize().width;
    float scaleY = visibleSize.height / background1->getContentSize().height;
    background1->setScale(scaleX, scaleY);
    background2->setScale(scaleX, scaleY);

    // 设置背景图片的初始位置
    background1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background2->setPosition(Vec2(visibleSize.width * 1.5 + origin.x, visibleSize.height / 2 + origin.y));

    // 将背景图片添加到场景中
    this->addChild(background1, 0);
    this->addChild(background2, 0);

    // 启动定时器进行背景的移动
    schedule([=](float dt) {
        // 每帧移动背景图片
        background1->setPositionX(background1->getPositionX() - 2);  // 移动速度可以根据需要调整
        background2->setPositionX(background2->getPositionX() - 2);  //获取背景当前的 X 坐标，减去 2 意味着每帧将背景向左移动 2 个单位。

        // 当第一个背景移出屏幕时，将其移到第二个背景的后面
        if (background1->getPositionX() <= -visibleSize.width / 2) {
            background1->setPositionX(background2->getPositionX() + visibleSize.width);
        }

        // 当第二个背景移出屏幕时，将其移到第一个背景的后面
        if (background2->getPositionX() <= -visibleSize.width / 2) {
            background2->setPositionX(background1->getPositionX() + visibleSize.width);
        }
        }, 0.016f, "backgroundMoveKey");
}

void HelloWorld::startGameCallback(Ref* pSender)
{
    CCLOG("Start Game!");
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 按钮右移并隐藏
    startItem->runAction(MoveBy::create(1.0f, Vec2(visibleSize.width, 0)));  // 平滑地右移到屏幕外
    exitItem->runAction(MoveBy::create(1.0f, Vec2(visibleSize.width, 0)));   // 平滑地右移到屏幕外
    titleSprite->runAction(MoveBy::create(1.0f, Vec2(visibleSize.width, 0))); // 平滑地右移到屏幕外
    
    auto loginLayer = LoginLayer::create();
    this->addChild(loginLayer);

}

// exitGameCallback: 当点击“结束”按钮时，调用此函数
void HelloWorld::exitGameCallback(Ref* pSender)
{
    CCLOG("Exit Game!");  // 打印日志信息（用于调试）
    // 退出游戏：退出应用
    Director::getInstance()->end();  // 结束应用
}

