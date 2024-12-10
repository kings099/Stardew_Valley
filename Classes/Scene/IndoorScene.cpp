/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmScene.h
 * File Function: 室内类的创建
 * Author:        胡宝怡
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#include "IndoorScene.h"
#include "cocos2d.h"
#include "Classes/Scene/FarmScene.h"  // 假设农场场景类
#include "Classes/SceneSwitcher/SceneSwitcher.h"
#include "Classes/Maps/IndoorMap.h"
#include "Classes/MenuImage/HoverMenuItemImage.h"
#include "Classes/Layer/UILayer.h"
#include "Classes/Manager/TimeManager.h"
#include "Classes/Layer/TimeManagerUI.h"
USING_NS_CC;

IndoorScene* IndoorScene::create(const std::string& mapFile)
{
    IndoorScene* ret = new IndoorScene();
    if (ret && ret->init(mapFile)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool IndoorScene::init(const std::string& mapFile)
{
    // 调用父类的初始化方法
    if (!Scene::init()) {
        return false;
    }
    //// 获取角色单例
    //auto character = Character::getInstance(".. / Resources / Characters / Bear / BearDownAction1.png");
    //auto characterSprite = character->getCharacterSprite();//获取角色精灵

    //// 如果角色精灵已经有父节点，先移除
    //if (characterSprite->getParent()) {
    //    characterSprite->retain();
    //    characterSprite->removeFromParent();
    //}

    //// 将角色精灵添加到新场景
    //this->addChild(character,1);
    //characterSprite->release();

    // 获取可见区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 设置关闭按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(IndoorScene::menuCloseCallback, this));

    if (closeItem != nullptr) {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 加载室内地图
    indoorMap = IndoorMap::create(mapFile);
    this->addChild(indoorMap, 0);  // 地图位于最底层

    // 创建角色
    character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");  // 假设角色的图片
    this->addChild(character.get(), 1);  // 角色位于地图之上

    // 创建键盘监视事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->character->onKeyPressed(keyCode, event);
        };
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->character->onKeyReleased(keyCode, event);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    // 创建视角控制器
    viewController = new GameViewController(character.get(), indoorMap);  // 初始化视角控制器
    this->addChild(viewController, 2);  // 控制器无需渲染，层级不重要


    // 创建 MapSwitcher，并检查是否成功
    auto mapSwitcher = MapSwitcher::create("farm2", character.get());
    if (!mapSwitcher) {
        CCLOG("Error: Failed to create MapSwitcher.");
        return false;  // MapSwitcher 创建失败，退出或执行其他错误处理
    }
    // 添加到当前场景
    this->addChild(mapSwitcher, 3);

    // 启动定时器来检查角色位置
    this->schedule([this](float deltaTime) {
        // 更新视角控制器
        if (viewController) {
            /*checkCharacterPositionAndSwitchScene();*/
            viewController->update(deltaTime);
        }
        }, "check_position_key");

    return true;
}

// 创建室内地图场景
Scene* IndoorScene::createScene(const std::string& mapFile)
{
    return IndoorScene::create(mapFile);
}

void IndoorScene::menuCloseCallback(Ref* pSender)
{
    // 退出游戏
    Director::getInstance()->end();
}