#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Classes/Character/CharacterInfo.h"
#include "FarmScene.h"
#include "Manager/TimeManager.h"  // ���� TimeManager ��ͷ�ļ�

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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ��ȡȫ�ֳߴ��С
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ���ر���ͼƬ
    this->initBackground();
 

    // ���ز�������Ϸ����ͼƬ
    titleSprite = Sprite::create("../Resources/Helloworld/gameTitle.png");  // ��ı���ͼƬ�ļ�
    if (titleSprite == nullptr) {
        problemLoading("'gameTitle.png'");
    }
    else {
        // ���ñ���ͼƬ��λ��
        titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
        this->addChild(titleSprite, 1);  // ��������ӵ�������
    }
    this->createMenuWithImage();
    return true;
}

void HelloWorld::createMenuWithImage()
{
    // ��ȡ��ǰ�ɼ����򣨴��ڣ�����Ļ����Ĵ�С����Ⱥ͸߶ȣ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ���� "��ʼ" ��ť��ͼ��
    startItem = MenuItemImage::create(
        "../Resources/Helloworld/start.png",   // ��ͨ״̬�µ�ͼƬ
        "../Resources/Helloworld/start_.png",  // ��ͣ״̬�µ�ͼƬ
        CC_CALLBACK_1(HelloWorld::startGameCallback, this)  // ���ʱ���õĻص�����
    );
    startItem->setPosition(Vec2(origin.x + visibleSize.width * 0.33, origin.y + visibleSize.height * 0.2f)); // ���� "��ʼ" ��ť��λ��

    // ���� "����" ��ť��ͼ��
    exitItem = MenuItemImage::create(
        "../Resources/Helloworld/end.png",    // ��ͨ״̬�µ�ͼƬ
        "../Resources/Helloworld/end_.png", // ��ͣ״̬�µ�ͼƬ
        CC_CALLBACK_1(HelloWorld::exitGameCallback, this)  // ���ʱ���õĻص�����
    );
    exitItem->setPosition(Vec2(origin.x + visibleSize.width * 0.67, origin.y + visibleSize.height * 0.2f)); // ���� "����" ��ť��λ��

    // �����˵����� "��ʼ" �� "����" ��ť��ӵ��˵���
    auto menu = Menu::create(startItem, exitItem, nullptr);
    menu->setPosition(Vec2::ZERO);  // ���ò˵���ԭ��λ��
    this->addChild(menu, 2);  // ���˵���ӵ�������
}

void HelloWorld::initBackground() {
    // ��ȡ��Ļ�ĳߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������������ͼ
    auto background1 = Sprite::create("../Resources/Helloworld/Cloud.png");
    auto background2 = Sprite::create("../Resources/Helloworld/Cloud.png");

    // ���ñ���ͼƬ������ʹ��������Ļ
    float scaleX = visibleSize.width / background1->getContentSize().width;
    float scaleY = visibleSize.height / background1->getContentSize().height;
    background1->setScale(scaleX, scaleY);
    background2->setScale(scaleX, scaleY);

    // ���ñ���ͼƬ�ĳ�ʼλ��
    background1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background2->setPosition(Vec2(visibleSize.width * 1.5 + origin.x, visibleSize.height / 2 + origin.y));

    // ������ͼƬ��ӵ�������
    this->addChild(background1, 0);
    this->addChild(background2, 0);

    // ������ʱ�����б������ƶ�
    schedule([=](float dt) {
        // ÿ֡�ƶ�����ͼƬ
        background1->setPositionX(background1->getPositionX() - 2);  // �ƶ��ٶȿ��Ը�����Ҫ����
        background2->setPositionX(background2->getPositionX() - 2);

        // ����һ�������Ƴ���Ļʱ�������Ƶ��ڶ��������ĺ���
        if (background1->getPositionX() <= -visibleSize.width / 2) {
            background1->setPositionX(background2->getPositionX() + visibleSize.width);
        }

        // ���ڶ��������Ƴ���Ļʱ�������Ƶ���һ�������ĺ���
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


    // ��ť���Ʋ�����
    startItem->runAction(MoveBy::create(0.5f, Vec2(visibleSize.width, 0)));  // ƽ�������Ƶ���Ļ��
    exitItem->runAction(MoveBy::create(0.5f, Vec2(visibleSize.width, 0)));   // ƽ�������Ƶ���Ļ��
    titleSprite->runAction(MoveBy::create(0.5f, Vec2(visibleSize.width, 0))); // ƽ�������Ƶ���Ļ��

    // ������¼����
    loginLayer = LayerColor::create(Color4B(0, 0, 0, 150)); // ��͸����ɫ������
    if (loginLayer != nullptr) {
        this->addChild(loginLayer);  // ��ӵ�������
    }
    else {
        CCLOG("loginLayer creation failed");
    }

    // �����ĸ߶�
    const float inputBoxHeight = visibleSize.height * 0.07f;

    // ������Ļ�߶ȶ�̬������
    const float verticalSpacing = visibleSize.height * 0.02f;  // ��ʾ��������֮��Ĵ�ֱ��࣬����������
    const float inputBoxSpacing = visibleSize.height * 0.14f;  // �����������֮��ļ�࣬����������

    // �����û�������򱳾�ͼ
    auto usernameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    usernameInputBackground->setContentSize(Size(300, inputBoxHeight));  // ���ñ������С
    usernameInputBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f));  // ���ñ���ͼλ��
    loginLayer->addChild(usernameInputBackground);

    // �����û��������
    auto usernameInput = cocos2d::ui::TextField::create("Enter your username", "fonts/arial.ttf", 24);
    usernameInput->setMaxLength(20);  // ����������볤��
    usernameInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f));  // ����λ��
    usernameInput->setAnchorPoint(Vec2(0.5f, 0.5f));  // ����ê��Ϊ����
    usernameInput->setTextHorizontalAlignment(TextHAlignment::CENTER); // ˮƽ������ʾ
    usernameInput->setTextVerticalAlignment(TextVAlignment::CENTER); // ��ֱ������ʾ

    loginLayer->addChild(usernameInput);  // ���������ӵ���������

    // �����û�����ǩ����ʾ�ı���
    auto usernameLabel = Label::createWithTTF("Username", "fonts/arial.ttf", 24);
    usernameLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f + inputBoxHeight / 2 + verticalSpacing));  // ���ñ�ǩλ��
    loginLayer->addChild(usernameLabel);

    // ����ũ��������򱳾�ͼ
    auto farmNameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    farmNameInputBackground->setContentSize(Size(300, inputBoxHeight));  // ���ñ������С
    farmNameInputBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing));  // ���ñ���ͼλ��
    loginLayer->addChild(farmNameInputBackground);

    // ����ũ���������
    auto farmNameInput = cocos2d::ui::TextField::create("Enter your farm name", "fonts/arial.ttf", 24);
    farmNameInput->setMaxLength(20);  // ����������볤��
    farmNameInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing));  // ����λ��
    farmNameInput->setAnchorPoint(Vec2(0.5f, 0.5f));  // ����ê��Ϊ����
    farmNameInput->setTextHorizontalAlignment(TextHAlignment::CENTER); // ˮƽ������ʾ
    farmNameInput->setTextVerticalAlignment(TextVAlignment::CENTER); // ��ֱ������ʾ

    loginLayer->addChild(farmNameInput);  // ���������ӵ���������

    // ����ũ������ǩ����ʾ�ı���
    auto farmNameLabel = Label::createWithTTF("Farm Name", "fonts/arial.ttf", 24);
    farmNameLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing + inputBoxHeight / 2 + verticalSpacing));  // ���ñ�ǩλ��
    loginLayer->addChild(farmNameLabel);

    // ������ϲ���Ķ�������򱳾�ͼ
    auto favoriteInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    favoriteInputBackground->setContentSize(Size(300, inputBoxHeight));  // ���ñ������С
    favoriteInputBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing * 2));  // ���ñ���ͼλ��
    loginLayer->addChild(favoriteInputBackground);

    // ������ϲ���Ķ��������
    auto favoriteInput = cocos2d::ui::TextField::create("Enter your favorite thing", "fonts/arial.ttf", 24);
    favoriteInput->setMaxLength(20);  // ����������볤��
    favoriteInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing * 2));  // ����λ��
    favoriteInput->setAnchorPoint(Vec2(0.5f, 0.5f));  // ����ê��Ϊ����
    favoriteInput->setTextHorizontalAlignment(TextHAlignment::CENTER); // ˮƽ������ʾ
    favoriteInput->setTextVerticalAlignment(TextVAlignment::CENTER); // ��ֱ������ʾ

    loginLayer->addChild(favoriteInput);  // ���������ӵ���������

    // ������ϲ���Ķ�����ǩ����ʾ�ı���
    auto favoriteLabel = Label::createWithTTF("Favorite Thing", "fonts/arial.ttf", 24);
    favoriteLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing * 2 + inputBoxHeight / 2 + verticalSpacing));  // ���ñ�ǩλ��
    loginLayer->addChild(favoriteLabel);

    // �����ύ��ť����ѡ��
    auto submitButton = cocos2d::ui::Button::create("../Resources/Helloworld/start.png", "../Resources/Helloworld/start_.png");
    submitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4f - inputBoxSpacing * 2));
    submitButton->addClickEventListener([=](Ref* sender) {
        // ��ȡ���������
        std::string username = usernameInput->getString();
        std::string farmName = farmNameInput->getString();
        std::string favoriteThing = favoriteInput->getString();

        // �ڿ���̨��ӡ��������ݣ�����Ը�����Ҫ������Щ��Ϣ��
        CCLOG("Username: %s, Farm Name: %s, Favorite Thing: %s", username.c_str(), farmName.c_str(), favoriteThing.c_str());
       
        // ��ȡ CharacterInfo ��ʵ��
        CharacterInfo* characterInfo = CharacterInfo::getInstance();

        // ����������ݱ��浽 CharacterInfo ʵ��
        characterInfo->setCharacterInfo(username, farmName, favoriteThing);

        // ���������֤����ȡ��������ݲ���ӡ������̨
        CCLOG("CharacterInfo after saving:");
        CCLOG("Username: %s", characterInfo->getUsername().c_str());
        CCLOG("Farm Name: %s", characterInfo->getFarmName().c_str());
        CCLOG("Favorite Thing: %s", characterInfo->getFavoriteThing().c_str());

        // ���ص�¼����
        loginLayer->setVisible(false);

        // ���� farmScene
        auto farmScene = FarmScene::createScene();  // ���� farmScene �Ѿ�����

        // ʹ�� TransitionFade ���г�������
        auto transition = TransitionFade::create(1.0f, farmScene);  // 1���ӵĹ���ʱ��
        Director::getInstance()->replaceScene(transition);  // �л��� farmScene

        // ���ص�¼����
        loginLayer->setVisible(false);
        });
    loginLayer->addChild(submitButton);

   

}

// exitGameCallback: ���������������ťʱ�����ô˺���
void HelloWorld::exitGameCallback(Ref* pSender)
{
    CCLOG("Exit Game!");  // ��ӡ��־��Ϣ�����ڵ��ԣ�
    // �˳���Ϸ���˳�Ӧ��
    Director::getInstance()->end();  // ����Ӧ��
}
