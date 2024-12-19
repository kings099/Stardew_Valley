/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameMainScene.h
 * File Function: 游戏主场景类GameMainSecen类的定义
 * Author:        金恒宇
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/

#include "GameMainScene.h"

USING_NS_CC;

Scene* GameMainScene::createScene()
{
    return GameMainScene::create();
}


bool GameMainScene::init()
{
    // 调用父类初始化
    if (!Scene::init()) {
        return false;
    }



    // 获取可见区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 创建树木层
    auto treeLayer = Node::create();
    this->addChild(treeLayer, TREE_LAYER_GRADE); // 树木层级比角色高
    treeLayer->setName("treeLayer");

    auto Maplayer = Node::create();
    this->addChild(Maplayer, MAP_LAYER_GRADE); // 地图层级
    Maplayer->setName("Maplayer");
    // 加载农场地图
    _farmMap = FarmMap::create("../Resources/Maps/Farm/Farm_Combat.tmx", treeLayer);
    Maplayer->addChild(_farmMap, MAP_LAYER_GRADE);

    // 加载角色
    _character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
    this->addChild(_character, CHARACTER_LAYER_GRADE);
   
    // 初始化视角控制器
    _viewController = GameViewController::create(_character, _farmMap);
    this->addChild(_viewController);

    // 初始化交互管理器
    _interaction = InteractionManager::create(_farmMap);
    this->addChild(_interaction);

    // 创建 UI 容器
    Node* uiContainer = Node::create();
    uiContainer->setPosition(Vec2::ZERO);  // 设置为屏幕的原点
    this->addChild(uiContainer, UI_LAYER_GRADE);  // 添加到最上层

    //初始化UI层
    _uiLayer = UILayer::create();
    uiContainer->addChild(_uiLayer);
    
    // 创建音频控制层并添加到场景,层级为2
    auto audioControlLayer = AudioControlLayer::create();
    uiContainer->addChild(audioControlLayer);

    // 启动时间管理器的计时
    TimeManager::getInstance()->startUpdating();

    //创建地图转换器
    auto mapSwitchManager = MapSwitchManager::create(_character, _farmMap, _viewController, _interaction);
    this->addChild(mapSwitchManager);

    // 创建键盘事件监视器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->_character->onKeyPressed(keyCode, event);
        this->_uiLayer->onKeyPressed(keyCode, event);
        };
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->_character->onKeyReleased(keyCode, event);
        };
    // 注册键盘监听器 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 创建鼠标事件监视器
    auto mouselistener = EventListenerMouse::create();
    mouselistener->onMouseDown = [this](Event* event) {
        Vec2 actionTilePos;
        GameCharacterAction action;
        this->_character->onMouseDown(event, action, actionTilePos);
        _interaction->ActionAnimation(action, actionTilePos);
        CCLOG("target tile: (%f, %f), action: %d",
            actionTilePos.x, actionTilePos.y, action);
        };
    // 注册鼠标监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, this);

    // 设置更新回调，定时调用检查地图切换逻辑是否触发
    this->schedule([this, mapSwitchManager,treeLayer,Maplayer](float deltaTime) {
        Vec2 characterWorldPos = _character->getPosition();
        Vec2 TargetPos;
        std::string targetMapFile;
        _interaction->updateSurroundingTiles(characterWorldPos);
        // 检测传送点
        if (_interaction->checkTeleport(characterWorldPos, targetMapFile)) {
            CCLOG("Teleport triggered to map: %s", targetMapFile.c_str());
            mapSwitchManager->switchMap(targetMapFile, TargetPos, treeLayer, Maplayer);
            CCLOG("TargetPosition :%f ,%f ", TargetPos.x, TargetPos.y);
            _character->setPosition(TargetPos);
        }
        _character->updateTileInfo(_interaction);
        }, "CheckTeleportUpdate");

    // 设置更新回调，更新角色位置，视角跟随和ui位移
    this->schedule([this, uiContainer](float deltaTime) {
        if (_viewController) { _viewController->update(deltaTime); }
        // 获取摄像机的位移
        const auto cameraPosition = Camera::getDefaultCamera()->getPosition();
        const auto visibleSize = Director::getInstance()->getVisibleSize();
        // 将摄像机的偏移量应用到UI容器
        Vec2 cameraOffset = cameraPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);
        uiContainer->setPosition(cameraOffset);  // 更新UI容器的位置，使UI随摄像机移动
        if (_uiLayer) { _uiLayer->update(deltaTime); }
        }, "ViewControllerUpdate");
  
    

    return true;
}


void GameMainScene::menuCloseCallback(Ref* pSender)
{
    // 退出游戏
    _character->saveData();
    Director::getInstance()->end();
}