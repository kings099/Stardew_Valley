/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LoginLayer.h
 * File Function: 用户登录UI层的实现
 * Author:        达思睿
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#include "LoginLayer.h"
#include "Character/CharacterInfo.h"
#include "Scene/GameMainScene.h"


 // 构造函数
LoginLayer::LoginLayer() : _usernameInput(nullptr), _farmNameInput(nullptr), _favoriteInput(nullptr), _submitButton(nullptr), _loginLayer(nullptr)
{
}


//析构函数
LoginLayer::~LoginLayer()
{
}

// 创建函数
LoginLayer* LoginLayer::create()
{
    LoginLayer* ret = new LoginLayer();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

// 初始化函数
bool LoginLayer::init()
{
    // 获取可见区域尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建登录层
    _loginLayer = LayerColor::create(Color4B(0, 0, 0, 150)); // 半透明黑色背景层
    if (_loginLayer)
    {
        this->addChild(_loginLayer); // 将登录层添加到当前场景
    }
    else
    {
        CCLOG("loginLayer creation failed");
        return false;
    }

    // 创建用户名输入框背景图
    auto usernameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    usernameInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    usernameInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET));
    _loginLayer->addChild(usernameInputBackground);

    // 创建用户名输入框
    _usernameInput = cocos2d::ui::TextField::create("Enter your username", FONT_TYPE, FONT_SIZE);
    _usernameInput->setMaxLength(20);
    _usernameInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET));
    _usernameInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    _usernameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _usernameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    _loginLayer->addChild(_usernameInput);

    // 创建用户名标签
    auto usernameLabel = Label::createWithTTF("Username", FONT_TYPE, FONT_SIZE);
    usernameLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(usernameLabel);

    // 创建农场名输入框背景图
    auto farmNameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    farmNameInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    farmNameInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(farmNameInputBackground);

    // 创建农场名输入框
    _farmNameInput = cocos2d::ui::TextField::create("Enter your farm name", FONT_TYPE, FONT_SIZE);
    _farmNameInput->setMaxLength(20);
    _farmNameInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height));
    _farmNameInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    _farmNameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _farmNameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    _loginLayer->addChild(_farmNameInput);

    // 创建农场名标签
    auto farmNameLabel = Label::createWithTTF("Farm Name", FONT_TYPE, FONT_SIZE);
    farmNameLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(farmNameLabel);

    // 创建最喜欢的东西输入框背景图
    auto favoriteInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    favoriteInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    favoriteInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2));
    _loginLayer->addChild(favoriteInputBackground);

    // 创建最喜欢的东西输入框
    _favoriteInput = cocos2d::ui::TextField::create("Enter your favorite thing", FONT_TYPE, FONT_SIZE);
    _favoriteInput->setMaxLength(20);
    _favoriteInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2));
    _favoriteInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    _favoriteInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _favoriteInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    _loginLayer->addChild(_favoriteInput);

    // 创建最喜欢的东西标签
    auto favoriteLabel = Label::createWithTTF("Favorite Thing", FONT_TYPE, FONT_SIZE);
    favoriteLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2 + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(favoriteLabel);

    // 创建提交按钮
    _submitButton = cocos2d::ui::Button::create("../Resources/Helloworld/start.png", "../Resources/Helloworld/start_.png");
    _submitButton->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 3));
    _submitButton->addClickEventListener(CC_CALLBACK_1(LoginLayer::onSubmitClicked, this));
    _loginLayer->addChild(_submitButton);

    return true;
}

// 提交按钮回调
void LoginLayer::onSubmitClicked(Ref* sender)
{
    // 获取输入的内容
    std::string username = _usernameInput->getString();
    std::string farmName = _farmNameInput->getString();
    std::string favoriteThing = _favoriteInput->getString();

    // 获取 CharacterInfo 的实例并保存数据
    CharacterInfo* characterInfo = CharacterInfo::getInstance();
    characterInfo->setCharacterInfo(username, farmName, favoriteThing);

    // 隐藏登录界面
    _loginLayer->setVisible(false);

    // 创建并切换到游戏主场景
    auto farmScene = GameMainScene::createScene();
    auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, farmScene);
    Director::getInstance()->replaceScene(transition);
}
