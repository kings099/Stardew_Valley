#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "../Classes/Character/Character.h"
#include"Classes/Maps/FarmMap.h"

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
    if ( !Scene::init() ){
        return false;
    }

    // 加载背景
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //设置关闭按钮
    auto closeItem = MenuItemImage::create("CloseNormal.png",  "CloseSelected.png",  CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else {
        const float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        const float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //设置文字
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    //添加地图
    auto farm_map = FarmMap::create("../Resources/Maps/Farm/farm1/Farm.tmx");
    this->addChild(farm_map);
    //添加角色
    auto character = Character::create("../Resources/Characters/Bear/BearDownAction1.png");
    this->addChild(character);

    this->schedule([farm_map, character](float deltaTime) {
        character->updatePosition(deltaTime);
        }, "CharacterAndMapUpdate");


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
