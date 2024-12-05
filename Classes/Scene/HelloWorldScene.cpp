#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Classes/Character/CharacterInfo.h"
#include "FarmScene.h"
#include "Manager/TimeManager.h"  // 包含 TimeManager 类头文件

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
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 获取全局尺寸大小
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载背景图片
    this->initBackground();
 

    // 加载并设置游戏标题图片
    titleSprite = Sprite::create("../Resources/Helloworld/gameTitle.png");  // 你的标题图片文件
    if (titleSprite == nullptr) {
        problemLoading("'gameTitle.png'");
    }
    else {
        // 设置标题图片的位置
        titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
        this->addChild(titleSprite, 1);  // 将标题添加到场景中
    }
    this->createMenuWithImage();
    return true;
}

void HelloWorld::createMenuWithImage()
{
    // 获取当前可见区域（窗口）或屏幕区域的大小（宽度和高度）
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建 "开始" 按钮的图像
    startItem = MenuItemImage::create(
        "../Resources/Helloworld/start.png",   // 普通状态下的图片
        "../Resources/Helloworld/start_.png",  // 悬停状态下的图片
        CC_CALLBACK_1(HelloWorld::startGameCallback, this)  // 点击时调用的回调函数
    );
    startItem->setPosition(Vec2(origin.x + visibleSize.width * 0.33, origin.y + visibleSize.height * 0.2f)); // 设置 "开始" 按钮的位置

    // 创建 "结束" 按钮的图像
    exitItem = MenuItemImage::create(
        "../Resources/Helloworld/end.png",    // 普通状态下的图片
        "../Resources/Helloworld/end_.png", // 悬停状态下的图片
        CC_CALLBACK_1(HelloWorld::exitGameCallback, this)  // 点击时调用的回调函数
    );
    exitItem->setPosition(Vec2(origin.x + visibleSize.width * 0.67, origin.y + visibleSize.height * 0.2f)); // 设置 "结束" 按钮的位置

    // 创建菜单，将 "开始" 和 "结束" 按钮添加到菜单中
    auto menu = Menu::create(startItem, exitItem, nullptr);
    menu->setPosition(Vec2::ZERO);  // 设置菜单的原点位置
    this->addChild(menu, 2);  // 将菜单添加到场景中
}

void HelloWorld::initBackground() {
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
        background1->setPositionX(background1->getPositionX() - 2);  // 移动速度可以根据需要调整
        background2->setPositionX(background2->getPositionX() - 2);

        // 当第一个背景移出屏幕时，将其移到第二个背景的后面
        if (background1->getPositionX() <= -visibleSize.width / 2) {
            background1->setPositionX(background2->getPositionX() + visibleSize.width);
        }

        // 当第二个背景移出屏幕时，将其移到第一个背景的后面
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


    // 按钮右移并隐藏
    startItem->runAction(MoveBy::create(0.5f, Vec2(visibleSize.width, 0)));  // 平滑地右移到屏幕外
    exitItem->runAction(MoveBy::create(0.5f, Vec2(visibleSize.width, 0)));   // 平滑地右移到屏幕外
    titleSprite->runAction(MoveBy::create(0.5f, Vec2(visibleSize.width, 0))); // 平滑地右移到屏幕外

    // 创建登录界面
    loginLayer = LayerColor::create(Color4B(0, 0, 0, 150)); // 半透明黑色背景层
    if (loginLayer != nullptr) {
        this->addChild(loginLayer);  // 添加到场景中
    }
    else {
        CCLOG("loginLayer creation failed");
    }

    // 输入框的高度
    const float inputBoxHeight = visibleSize.height * 0.07f;

    // 根据屏幕高度动态计算间距
    const float verticalSpacing = visibleSize.height * 0.02f;  // 提示语和输入框之间的垂直间距，按比例调整
    const float inputBoxSpacing = visibleSize.height * 0.14f;  // 输入框和输入框之间的间距，按比例调整

    // 创建用户名输入框背景图
    auto usernameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    usernameInputBackground->setContentSize(Size(300, inputBoxHeight));  // 设置背景框大小
    usernameInputBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f));  // 设置背景图位置
    loginLayer->addChild(usernameInputBackground);

    // 创建用户名输入框
    auto usernameInput = cocos2d::ui::TextField::create("Enter your username", "fonts/arial.ttf", 24);
    usernameInput->setMaxLength(20);  // 设置最大输入长度
    usernameInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f));  // 设置位置
    usernameInput->setAnchorPoint(Vec2(0.5f, 0.5f));  // 设置锚点为中心
    usernameInput->setTextHorizontalAlignment(TextHAlignment::CENTER); // 水平居中显示
    usernameInput->setTextVerticalAlignment(TextVAlignment::CENTER); // 垂直居中显示

    loginLayer->addChild(usernameInput);  // 将输入框添加到背景层上

    // 创建用户名标签（提示文本）
    auto usernameLabel = Label::createWithTTF("Username", "fonts/arial.ttf", 24);
    usernameLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f + inputBoxHeight / 2 + verticalSpacing));  // 设置标签位置
    loginLayer->addChild(usernameLabel);

    // 创建农场名输入框背景图
    auto farmNameInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    farmNameInputBackground->setContentSize(Size(300, inputBoxHeight));  // 设置背景框大小
    farmNameInputBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing));  // 设置背景图位置
    loginLayer->addChild(farmNameInputBackground);

    // 创建农场名输入框
    auto farmNameInput = cocos2d::ui::TextField::create("Enter your farm name", "fonts/arial.ttf", 24);
    farmNameInput->setMaxLength(20);  // 设置最大输入长度
    farmNameInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing));  // 设置位置
    farmNameInput->setAnchorPoint(Vec2(0.5f, 0.5f));  // 设置锚点为中心
    farmNameInput->setTextHorizontalAlignment(TextHAlignment::CENTER); // 水平居中显示
    farmNameInput->setTextVerticalAlignment(TextVAlignment::CENTER); // 垂直居中显示

    loginLayer->addChild(farmNameInput);  // 将输入框添加到背景层上

    // 创建农场名标签（提示文本）
    auto farmNameLabel = Label::createWithTTF("Farm Name", "fonts/arial.ttf", 24);
    farmNameLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing + inputBoxHeight / 2 + verticalSpacing));  // 设置标签位置
    loginLayer->addChild(farmNameLabel);

    // 创建最喜欢的东西输入框背景图
    auto favoriteInputBackground = cocos2d::ui::Scale9Sprite::create("../Resources/Helloworld/textBox.png");
    favoriteInputBackground->setContentSize(Size(300, inputBoxHeight));  // 设置背景框大小
    favoriteInputBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing * 2));  // 设置背景图位置
    loginLayer->addChild(favoriteInputBackground);

    // 创建最喜欢的东西输入框
    auto favoriteInput = cocos2d::ui::TextField::create("Enter your favorite thing", "fonts/arial.ttf", 24);
    favoriteInput->setMaxLength(20);  // 设置最大输入长度
    favoriteInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing * 2));  // 设置位置
    favoriteInput->setAnchorPoint(Vec2(0.5f, 0.5f));  // 设置锚点为中心
    favoriteInput->setTextHorizontalAlignment(TextHAlignment::CENTER); // 水平居中显示
    favoriteInput->setTextVerticalAlignment(TextVAlignment::CENTER); // 垂直居中显示

    loginLayer->addChild(favoriteInput);  // 将输入框添加到背景层上

    // 创建最喜欢的东西标签（提示文本）
    auto favoriteLabel = Label::createWithTTF("Favorite Thing", "fonts/arial.ttf", 24);
    favoriteLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6f - inputBoxSpacing * 2 + inputBoxHeight / 2 + verticalSpacing));  // 设置标签位置
    loginLayer->addChild(favoriteLabel);

    // 创建提交按钮（可选）
    auto submitButton = cocos2d::ui::Button::create("../Resources/Helloworld/start.png", "../Resources/Helloworld/start_.png");
    submitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4f - inputBoxSpacing * 2));
    submitButton->addClickEventListener([=](Ref* sender) {
        // 获取输入的内容
        std::string username = usernameInput->getString();
        std::string farmName = farmNameInput->getString();
        std::string favoriteThing = favoriteInput->getString();

        // 在控制台打印输入的内容（你可以根据需要处理这些信息）
        CCLOG("Username: %s, Farm Name: %s, Favorite Thing: %s", username.c_str(), farmName.c_str(), favoriteThing.c_str());
       
        // 获取 CharacterInfo 的实例
        CharacterInfo* characterInfo = CharacterInfo::getInstance();

        // 将输入的内容保存到 CharacterInfo 实例
        characterInfo->setCharacterInfo(username, farmName, favoriteThing);

        // 这里加入验证：获取保存的数据并打印到控制台
        CCLOG("CharacterInfo after saving:");
        CCLOG("Username: %s", characterInfo->getUsername().c_str());
        CCLOG("Farm Name: %s", characterInfo->getFarmName().c_str());
        CCLOG("Favorite Thing: %s", characterInfo->getFavoriteThing().c_str());

        // 隐藏登录界面
        loginLayer->setVisible(false);

        // 创建 farmScene
        auto farmScene = FarmScene::createScene();  // 假设 farmScene 已经创建

        // 使用 TransitionFade 进行场景过渡
        auto transition = TransitionFade::create(1.0f, farmScene);  // 1秒钟的过渡时间
        Director::getInstance()->replaceScene(transition);  // 切换到 farmScene

        // 隐藏登录界面
        loginLayer->setVisible(false);
        });
    loginLayer->addChild(submitButton);

   

}

// exitGameCallback: 当点击“结束”按钮时，调用此函数
void HelloWorld::exitGameCallback(Ref* pSender)
{
    CCLOG("Exit Game!");  // 打印日志信息（用于调试）
    // 退出游戏：退出应用
    Director::getInstance()->end();  // 结束应用
}
