/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmScene.h
 * File Function: ũ��������FamrScene��ʵ��
 * Author:        �����
 * Update Date:   2024/12/5
 * License:       MIT License
 ****************************************************************/
#include "FarmScene.h"
#include "SimpleAudioEngine.h"
#include "Manager/TimeManager.h"  // ���� TimeManager ��ͷ�ļ�
USING_NS_CC;

Scene* FarmScene::createScene()
{
    return FarmScene::create();
}

bool FarmScene::init()
{
    // ���ø����ʼ��
    if (!Scene::init()) {
        return false;
    }
   
    // ��ȡ�ɼ������С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

   /*����ʱ����ʾ��ǩ
    auto timeLabel = Label::createWithSystemFont("", "Arial", 24);
    timeLabel->setPosition(Vec2(visibleSize.width * 0.8f, visibleSize.height * 0.9f));
    this->addChild(timeLabel, 10);

    // ����ʱ����ʾ��ǩ�� TimeManager
    TimeManager* timeManager = TimeManager::getInstance();
    timeManager->setTimeLabel(timeLabel);  // ����ʱ���ǩ

    // ����ʱ�����
    timeManager->startUpdating();*/


    // ���ùرհ�ť
    auto closeItem = MenuItemImage::create(
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

    // ����ũ����ͼ
    farmMap = FarmMap::create("../Resources/Maps/Farm/farm2.tmx");
    this->addChild(farmMap, 0); // ��ͼ������ײ�

    // ���ؽ�ɫ
    character = Character::create("../Resources/Characters/Bear/BearDownAction1.png");
    this->addChild(character, 1); // ��ɫλ�ڵ�ͼ֮��

    // �����ӽǿ�����
    viewController = new GameViewController(character, farmMap);
    this->addChild(viewController, 2); // ������������Ⱦ���㼶����Ҫ

    

    // ���ø��»ص�
    this->schedule([this](float deltaTime) {
        if (viewController) {
            viewController->update(deltaTime);
        }
        }, "ViewControllerUpdate");

    return true;
}

void FarmScene::menuCloseCallback(Ref* pSender)
{
    // �˳���Ϸ
    Director::getInstance()->end();
}


