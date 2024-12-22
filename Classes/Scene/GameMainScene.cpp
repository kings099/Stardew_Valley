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

// 创建场景
Scene* GameMainScene::createScene(){
    return GameMainScene::create();
}


// 初始化
bool GameMainScene::init(){
    // 调用父类初始化
    if (!Scene::init()) {
        return false;
    }

    // 初始化地图和角色
    initializeMapAndCharacter();

    // 初始化视角控制和交互管理
    initializeViewControllerAndInteraction();

    // 初始化 UI 层
    initializeUI();

    // 注册输入事件
    registerInputListeners();

    // 注册更新回调
    registerUpdateCallbacks();
    return true;
}

// 初始化地图和角色
void GameMainScene::initializeMapAndCharacter() {
    // 创建树木层
    auto treeLayer = Node::create();
    this->addChild(treeLayer, TREE_LAYER_GRADE);
    treeLayer->setName("treeLayer");

    // 创建地图层
    auto mapLayer = Node::create();
    this->addChild(mapLayer, MAP_LAYER_GRADE);
    mapLayer->setName("MapLayer");

    // 加载农场地图
    _farmMap = FarmMap::create("../Resources/Maps/Farm/Farm_Combat.tmx", treeLayer);
    mapLayer->addChild(_farmMap, MAP_LAYER_GRADE);

    // 加载地图存档并应用更改
    MapStateManager::getInstance().loadChangesFromFile("../GameData/MapChanges.dat");
    _farmMap->applySavedChanges();

    // 加载角色
    _character = Character::getInstance();
    this->addChild(_character, CHARACTER_LAYER_GRADE);
}

// 初始化视角控制和交互管理
void GameMainScene::initializeViewControllerAndInteraction() {
    // 初始化视角控制器
    _viewController = GameViewController::create(_character, _farmMap);
    this->addChild(_viewController, VIEW_CONTROLLER_LAYER_GRADE);

    // 初始化交互管理器
    _interaction = InteractionManager::create(_farmMap);
    this->addChild(_interaction);

    // 创建地图切换管理器
    _mapSwitchManager = MapSwitchManager::create(_character, _farmMap, _viewController, _interaction);
    this->addChild(_mapSwitchManager);
}

// 初始化 UI 层
void GameMainScene::initializeUI() {
    // 创建 UI 容器
    _uiContainer = Node::create();
    _uiContainer->setPosition(Vec2::ZERO);
    this->addChild(_uiContainer, UI_LAYER_GRADE);

    // 初始化 UI 层
    _uiLayer = UILayer::create();
    _uiContainer->addChild(_uiLayer);

    // 创建音频控制层并添加到 UI 容器
    auto audioControlLayer = AudioControlLayer::create();
    _uiContainer->addChild(audioControlLayer);

    // 启动时间管理器
    TimeManager::getInstance()->startUpdating();
}

// 注册输入事件监听器
void GameMainScene::registerInputListeners() {
    // 注册键盘监听器
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        _character->onKeyPressed(keyCode, event);
        _uiLayer->onKeyPressed(keyCode, event);
        };
    keyboardListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        _character->onKeyReleased(keyCode, event);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 注册鼠标监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [this](Event* event) {
        Vec2 actionTilePos;
        GameCharacterAction action;
        if (_character->onMouseDown(event, action, actionTilePos, _interaction)) {
            _interaction->updateCurrentObject(_character->getCurrentObject(), _character->getSkillLevel(GameObjectSkillType::Farm));
            _interaction->ActionAnimation(action, actionTilePos);
            _character->useObject(action, _interaction);
        }

        CCLOG("target tile: (%f, %f), action: %d", actionTilePos.x, actionTilePos.y, action);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

// 注册更新回调函数
void GameMainScene::registerUpdateCallbacks() {
    // 地图切换检查
    this->schedule([this](float deltaTime) {
        Vec2 characterWorldPos = _character->getPosition();
        Vec2 targetPos;
        std::string targetMapFile;
        _interaction->updateSurroundingTiles(characterWorldPos);

        if (_interaction->checkTeleport(characterWorldPos, targetMapFile)) {
            CCLOG("Teleport triggered to map: %s", targetMapFile.c_str());
            _mapSwitchManager->switchMap(targetMapFile, targetPos, this->getChildByName("treeLayer"), this->getChildByName("MapLayer"));
            _character->setPosition(targetPos);
        }

        _character->updateTileInfo(_interaction);
        }, "CheckTeleportUpdate");

    // 设置更新回调，更新角色位置，视角跟随和ui位移
    this->schedule([this](float deltaTime) {
        if (_viewController) { _viewController->update(deltaTime); }

        // 获取摄像机的位移
        const auto cameraPosition = Camera::getDefaultCamera()->getPosition();
        const auto visibleSize = Director::getInstance()->getVisibleSize();

        // 将摄像机的偏移量应用到UI容器
        Vec2 cameraOffset = cameraPosition - Vec2(visibleSize.width / 2, visibleSize.height / 2);

        _uiContainer->setPosition(cameraOffset);  // 更新UI容器的位置，使UI随摄像机移动
        if (_uiLayer) { _uiLayer->update(deltaTime); }
        }, "ViewControllerUpdate");
}

// 关闭回调
void GameMainScene::menuCloseCallback(Ref* pSender)
{
    // 退出游戏
    _character->saveData();
    Box::getInstance().saveData("../GameData/BoxObjectListData.dat");
    MapStateManager::getInstance().saveChangesToFile("../GameData/MapChanges.dat");
    Director::getInstance()->end();
}