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
#include "../Classes/MenuImage/HoverMenuItemImage.h"
#include "../Classes/Layer/UILayer.h"
#include "../Classes/Manager/TimeManager.h"
#include "../Classes/Layer/TimeManagerUI.h"
#include "Control/MapSwitchManager.h"

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
    auto closeItem = HoverMenuItemImage::create(
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
    farmMap = FarmMap::create("../Resources/Maps/Farm/Farm_Combat.tmx");
    this->addChild(farmMap, 0); // 地图置于最底层

    // 加载角色
    character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
    this->addChild(character, 1); // 角色位于地图之上
   

    // 创建视角控制器
    viewController = new GameViewController(character, farmMap);
    this->addChild(viewController, 2); // 控制器无需渲染，层级不重要

    // 创建交互管理器
    auto interaction = InteractionManager::create(farmMap);
    this->addChild(interaction);

    //创建场景转换器
    // 创建 MapSwitcher，并检查是否成功
    auto mapSwitchManager = MapSwitchManager::create(character, farmMap, viewController, interaction);
    this->addChild(mapSwitchManager);
    this->schedule([this, mapSwitchManager, interaction](float deltaTime) {
        Vec2 characterWorldPos = character->getPosition();
        std::string targetMapFile;
        interaction->updateSurroundingTiles(characterWorldPos);
        // 检测传送点
        if (interaction->checkTeleport(characterWorldPos, targetMapFile)) {
            CCLOG("Teleport triggered to map: %s", targetMapFile.c_str());
            mapSwitchManager->switchMap(targetMapFile, 0);
        }
        character->updateTileInfo(interaction);
        }, "CheckTeleportUpdate");
    // 启动时间管理器的计时
    TimeManager::getInstance()->startUpdating();

    // 创建 UI 容器
    Node* uiContainer = Node::create();
    uiContainer->setPosition(Vec2(0, 0));  // 设置为屏幕的原点
    this->addChild(uiContainer, 100);  // 添加到最上层


    uiLayer = UILayer::create();
    uiContainer->addChild(uiLayer);

    // 创建键盘监视事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->character->onKeyPressed(keyCode, event);
        this->uiLayer->onKeyPressed(keyCode, event);
        };
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->character->onKeyReleased(keyCode, event);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 设置更新回调
    this->schedule([this, uiContainer](float deltaTime) {
        if (viewController) {
            viewController->update(deltaTime);
        }
        // 获取摄像机的位移
        const auto cameraPosition = Camera::getDefaultCamera()->getPosition();
        const auto visibleSize = Director::getInstance()->getVisibleSize();
        // 将摄像机的偏移量应用到UI容器
        Vec2 cameraOffset = cameraPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);
        uiContainer->setPosition(cameraOffset);  // 更新UI容器的位置，使UI随摄像机移动

        if (uiLayer) {
            uiLayer->update(deltaTime);
        }

        }, "ViewControllerUpdate");
  
    return true;
}


void FarmScene::menuCloseCallback(Ref* pSender)
{
    // 退出游戏
    character->saveData();
    Director::getInstance()->end();
}