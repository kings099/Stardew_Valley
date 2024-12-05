/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmScene.h
 * File Function: 农场场景类FamrScene的实现
 * Author:        金恒宇
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#include "FarmScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* FarmScene::createScene()
{
    return FarmScene::create();
}

bool FarmScene::init()
{
    // 调用父类初始化
    if (!Scene::init()) {
        return false;
    }

    // 获取可见区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 设置关闭按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(FarmScene::menuCloseCallback, this));

    if (closeItem != nullptr) {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 加载农场地图
    farmMap = FarmMap::create("../Resources/Maps/Farm/farm2.tmx");
    this->addChild(farmMap, 0); // 地图置于最底层

    // 加载角色
    character = Character::create("../Resources/Characters/Bear/BearDownAction1.png");
    this->addChild(character, 1); // 角色位于地图之上
    CCLOG("Character Anchor Point: (%.2f, %.2f)", character->getAnchorPoint().x, character->getAnchorPoint().y);

    // 创建视角控制器
    viewController = new GameViewController(character, farmMap);
    this->addChild(viewController, 2); // 控制器无需渲染，层级不重要

    // 设置更新回调
    this->schedule([this](float deltaTime) {
        if (viewController) {
            viewController->update(deltaTime);
        }
        }, "ViewControllerUpdate");

    return true;
}

void FarmScene::menuCloseCallback(Ref* pSender)
{
    // 退出游戏
    Director::getInstance()->end();
}