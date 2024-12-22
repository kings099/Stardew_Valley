/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameStartScene.cpp
 * File Function: 游戏启动场景类的实现
 * Author:        达思睿
 * Update Date:   2024/12/3
 * License:       MIT License
 ****************************************************************/

#include "GameStartScene.h"


using namespace cocos2d::experimental;
USING_NS_CC;


// 创建并返回 游戏启动场景
Scene* GameStartScene::createScene()
{
    return GameStartScene::create();
}

// 初始化 游戏启动场景
bool GameStartScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 获取全局尺寸大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载背景图片
    this->initBackground();

    // 加载并设置游戏标题
    _titleSprite = Sprite::create("../Resources/Helloworld/gameTitle.png");
    _titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
    this->addChild(_titleSprite);

    //加载开始结束菜单项
    this->createMenuWithImage();

    //加载音频控制层
    auto audioControlLayer = AudioControlLayer::create();
    this->addChild(audioControlLayer);

    return true;
}

//加载开始结束菜单项
void GameStartScene::createMenuWithImage()
{
    // 获取当前可见区域（窗口）或屏幕区域的大小（宽度和高度）
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建 "开始" 按钮的图像
    _startItem = HoverMenuItemImage::create(
        "../Resources/Helloworld/start.png",   // 普通状态下的图片
        "../Resources/Helloworld/start_.png",  // 悬停状态下的图片
        CC_CALLBACK_1(GameStartScene::startGameCallback, this)  // 点击时调用的回调函数
    );
    _startItem->setPosition(Vec2(origin.x + visibleSize.width * 0.33, origin.y + visibleSize.height * 0.2f)); // 设置 "开始" 按钮的位置

    // 创建 "结束" 按钮的图像
    _exitItem = HoverMenuItemImage::create(
        "../Resources/Helloworld/end.png",    // 普通状态下的图片
        "../Resources/Helloworld/end_.png",   // 悬停状态下的图片
        CC_CALLBACK_1(GameStartScene::exitGameCallback, this)  // 点击时调用的回调函数
    );
    _exitItem->setPosition(Vec2(origin.x + visibleSize.width * 0.67, origin.y + visibleSize.height * 0.2f)); // 设置 "结束" 按钮的位置

    // 创建菜单，将 "开始" 和 "结束" 按钮添加到菜单中
    auto menu = Menu::create(_startItem, _exitItem, nullptr);
    menu->setPosition(Vec2::ZERO);  // 设置菜单的原点位置
    this->addChild(menu, 2);  // 将菜单添加到场景中

}

// 加载背景图片
void GameStartScene::initBackground() {
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
        background1->setPositionX(background1->getPositionX() - BG_MOVE_SPEED);  // 移动速度可以根据需要调整
        background2->setPositionX(background2->getPositionX() - BG_MOVE_SPEED);  // 获取背景当前的 X 坐标，减去 2 意味着每帧将背景向左移动 2 个单位。

        // 当第一个背景移出屏幕时，将其移到第二个背景的后面
        if (background1->getPositionX() <= -visibleSize.width / 2) {
            background1->setPositionX(background2->getPositionX() + visibleSize.width);
        }

        // 当第二个背景移出屏幕时，将其移到第一个背景的后面
        if (background2->getPositionX() <= -visibleSize.width / 2) {
            background2->setPositionX(background1->getPositionX() + visibleSize.width);
        }
        }, BG_UPDATE_RATIO, "backgroundMoveKey");
}

//点击开始按钮执行的回调函数
void GameStartScene::startGameCallback(Ref* pSender)
{
    CCLOG("Start Game!");
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 按钮右移并隐藏
    _startItem->runAction(MoveBy::create(UPDATE_RATIO, Vec2(visibleSize.width, 0)));  // 平滑地右移到屏幕外
    _exitItem->runAction(MoveBy::create(UPDATE_RATIO, Vec2(visibleSize.width, 0)));   // 平滑地右移到屏幕外
    _titleSprite->runAction(MoveBy::create(UPDATE_RATIO, Vec2(visibleSize.width, 0))); // 平滑地右移到屏幕外

    auto loginLayer = LoginLayer::create();
    this->addChild(loginLayer);

}

//点击结束按钮执行的回调函数
void GameStartScene::exitGameCallback(Ref* pSender)
{
    Director::getInstance()->end();  // 结束应用
}