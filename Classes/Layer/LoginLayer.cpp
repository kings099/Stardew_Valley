/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     LoginLayer.h
 * File Function: �û���¼UI���ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#include "LoginLayer.h"
#include "Character/CharacterInfo.h"
#include "Scene/GameMainScene.h"


 // ���캯��
LoginLayer::LoginLayer() : _usernameInput(nullptr), _farmNameInput(nullptr), _favoriteInput(nullptr), _submitButton(nullptr), _loginLayer(nullptr)
{
}


//��������
LoginLayer::~LoginLayer()
{
}

// ��������
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

// ��ʼ������
bool LoginLayer::init()
{
    // ��ȡ�ɼ�����ߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������¼��
    _loginLayer = LayerColor::create(Color4B(0, 0, 0, 150)); // ��͸����ɫ������
    if (_loginLayer)
    {
        this->addChild(_loginLayer); // ����¼����ӵ���ǰ����
    }
    else
    {
        CCLOG("loginLayer creation failed");
        return false;
    }

    // �����û�������򱳾�ͼ
    auto usernameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    usernameInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    usernameInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET));
    _loginLayer->addChild(usernameInputBackground);

    // �����û��������
    _usernameInput = cocos2d::ui::TextField::create("Enter your username", FONT_TYPE, FONT_SIZE);
    _usernameInput->setMaxLength(20);
    _usernameInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET));
    _usernameInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    _usernameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _usernameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    _loginLayer->addChild(_usernameInput);

    // �����û�����ǩ
    auto usernameLabel = Label::createWithTTF("Username", FONT_TYPE, FONT_SIZE);
    usernameLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(usernameLabel);

    // ����ũ��������򱳾�ͼ
    auto farmNameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    farmNameInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    farmNameInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(farmNameInputBackground);

    // ����ũ���������
    _farmNameInput = cocos2d::ui::TextField::create("Enter your farm name", FONT_TYPE, FONT_SIZE);
    _farmNameInput->setMaxLength(20);
    _farmNameInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height));
    _farmNameInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    _farmNameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _farmNameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    _loginLayer->addChild(_farmNameInput);

    // ����ũ������ǩ
    auto farmNameLabel = Label::createWithTTF("Farm Name", FONT_TYPE, FONT_SIZE);
    farmNameLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(farmNameLabel);

    // ������ϲ���Ķ�������򱳾�ͼ
    auto favoriteInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    favoriteInputBackground->setContentSize(Size(300, INPUT_BOX_HEIGHT_RATIO * visibleSize.height));
    favoriteInputBackground->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2));
    _loginLayer->addChild(favoriteInputBackground);

    // ������ϲ���Ķ��������
    _favoriteInput = cocos2d::ui::TextField::create("Enter your favorite thing", FONT_TYPE, FONT_SIZE);
    _favoriteInput->setMaxLength(20);
    _favoriteInput->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2));
    _favoriteInput->setAnchorPoint(Vec2(0.5f, 0.5f));
    _favoriteInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _favoriteInput->setTextVerticalAlignment(TextVAlignment::CENTER);
    _loginLayer->addChild(_favoriteInput);

    // ������ϲ���Ķ�����ǩ
    auto favoriteLabel = Label::createWithTTF("Favorite Thing", FONT_TYPE, FONT_SIZE);
    favoriteLabel->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 2 + INPUT_BOX_HEIGHT_RATIO * visibleSize.height * HALF_FACTOR + VERTICAL_SPACING_RATIO * visibleSize.height));
    _loginLayer->addChild(favoriteLabel);

    // �����ύ��ť
    _submitButton = cocos2d::ui::Button::create("../Resources/Helloworld/start.png", "../Resources/Helloworld/start_.png");
    _submitButton->setPosition(Vec2(visibleSize.width * HALF_FACTOR, visibleSize.height * LABEL_Y_OFFSET - INPUT_BOX_SPACING_RATIO * visibleSize.height * 3));
    _submitButton->addClickEventListener(CC_CALLBACK_1(LoginLayer::onSubmitClicked, this));
    _loginLayer->addChild(_submitButton);

    return true;
}

// �ύ��ť�ص�
void LoginLayer::onSubmitClicked(Ref* sender)
{
    // ��ȡ���������
    std::string username = _usernameInput->getString();
    std::string farmName = _farmNameInput->getString();
    std::string favoriteThing = _favoriteInput->getString();

    // ��ȡ CharacterInfo ��ʵ������������
    CharacterInfo* characterInfo = CharacterInfo::getInstance();
    characterInfo->setCharacterInfo(username, farmName, favoriteThing);

    // ���ص�¼����
    _loginLayer->setVisible(false);

    // �������л�����Ϸ������
    auto farmScene = GameMainScene::createScene();
    auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, farmScene);
    Director::getInstance()->replaceScene(transition);
}
