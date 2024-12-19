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

LoginLayer::LoginLayer() : usernameInput(nullptr), farmNameInput(nullptr), favoriteInput(nullptr), submitButton(nullptr), loginLayer(nullptr)
{
}

LoginLayer::~LoginLayer()
{
}

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

bool LoginLayer::init()
{
    // 获取可见区域尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建登录层
    loginLayer = LayerColor::create(Color4B(0, 0, 0, 150)); // 半透明黑色背景层
    if (loginLayer)
    {
        this->addChild(loginLayer); // 将登录层添加到当前场景
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
    loginLayer->addChild(usernameInputBackground);

    // 创建用户名输入框
    usernameInput = cocos2d::ui::TextField::create("Enter your username", "fonts/arial.ttf", FONT_SIZE);
    usernameInput->setMaxLength(20);
    usernameInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET));
    usernameInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    usernameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    usernameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    loginLayer->addChild(usernameInput);

    // 创建用户名标签
    auto usernameLabel = Label::createWithTTF("Username", "fonts/arial.ttf", FONT_SIZE);
    usernameLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    loginLayer->addChild(usernameLabel);

    // 创建农场名输入框背景图
    auto farmNameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    farmNameInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    farmNameInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height));
    loginLayer->addChild(farmNameInputBackground);

    // 创建农场名输入框
    farmNameInput = cocos2d::ui::TextField::create("Enter your farm name", "fonts/arial.ttf", FONT_SIZE);
    farmNameInput->setMaxLength(20);
    farmNameInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height));
    farmNameInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    farmNameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    farmNameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    loginLayer->addChild(farmNameInput);

    // 创建农场名标签
    auto farmNameLabel = Label::createWithTTF("Farm Name", "fonts/arial.ttf", FONT_SIZE);
    farmNameLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    loginLayer->addChild(farmNameLabel);

    // 创建最喜欢的东西输入框背景图
    auto favoriteInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    favoriteInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    favoriteInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2));
    loginLayer->addChild(favoriteInputBackground);

    // 创建最喜欢的东西输入框
    favoriteInput = cocos2d::ui::TextField::create("Enter your favorite thing", "fonts/arial.ttf", FONT_SIZE);
    favoriteInput->setMaxLength(20);
    favoriteInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2));
    favoriteInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    favoriteInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    favoriteInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    loginLayer->addChild(favoriteInput);

    // 创建最喜欢的东西标签
    auto favoriteLabel = Label::createWithTTF("Favorite Thing", "fonts/arial.ttf", FONT_SIZE);
    favoriteLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2 + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    loginLayer->addChild(favoriteLabel);

    // 创建提交按钮
    submitButton = cocos2d::ui::Button::create("../Resources/Helloworld/start.png", "../Resources/Helloworld/start_.png");
    submitButton->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 3));
    submitButton->addClickEventListener(CC_CALLBACK_1(LoginLayer::onSubmitClicked, this));
    loginLayer->addChild(submitButton);

    return true;
}

void LoginLayer::onSubmitClicked(Ref* sender)
{
    // 获取输入的内容
    std::string username = usernameInput->getString();
    std::string farmName = farmNameInput->getString();
    std::string favoriteThing = favoriteInput->getString();

    // 打印输入内容
    CCLOG("Username: %s, Farm Name: %s, Favorite Thing: %s", username.c_str(), farmName.c_str(), favoriteThing.c_str());

    // 获取 CharacterInfo 的实例并保存数据
    CharacterInfo* characterInfo = CharacterInfo::getInstance();
    characterInfo->setCharacterInfo(username, farmName, favoriteThing);

    // 打印保存后的信息
    CCLOG("CharacterInfo after saving:");
    CCLOG("Username: %s", characterInfo->getUsername().c_str());
    CCLOG("Farm Name: %s", characterInfo->getFarmName().c_str());
    CCLOG("Favorite Thing: %s", characterInfo->getFavoriteThing().c_str());

    // 隐藏登录界面
    loginLayer->setVisible(false);

    // 创建并切换到游戏主场景
    auto farmScene = GameMainScene::createScene();
    auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, farmScene);
    Director::getInstance()->replaceScene(transition);
}
