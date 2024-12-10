/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmScene.h
 * File Function: ������Ĵ���
 * Author:        ������
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#include "IndoorScene.h"
#include "cocos2d.h"
#include "Classes/Scene/FarmScene.h"  // ����ũ��������
#include "Classes/SceneSwitcher/SceneSwitcher.h"
#include "Classes/Maps/IndoorMap.h"
#include "Classes/MenuImage/HoverMenuItemImage.h"
#include "Classes/Layer/UILayer.h"
#include "Classes/Manager/TimeManager.h"
#include "Classes/Layer/TimeManagerUI.h"
USING_NS_CC;

IndoorScene* IndoorScene::create(const std::string& mapFile)
{
    IndoorScene* ret = new IndoorScene();
    if (ret && ret->init(mapFile)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool IndoorScene::init(const std::string& mapFile)
{
    // ���ø���ĳ�ʼ������
    if (!Scene::init()) {
        return false;
    }
    //// ��ȡ��ɫ����
    //auto character = Character::getInstance(".. / Resources / Characters / Bear / BearDownAction1.png");
    //auto characterSprite = character->getCharacterSprite();//��ȡ��ɫ����

    //// �����ɫ�����Ѿ��и��ڵ㣬���Ƴ�
    //if (characterSprite->getParent()) {
    //    characterSprite->retain();
    //    characterSprite->removeFromParent();
    //}

    //// ����ɫ������ӵ��³���
    //this->addChild(character,1);
    //characterSprite->release();

    // ��ȡ�ɼ������С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // ���ùرհ�ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(IndoorScene::menuCloseCallback, this));

    if (closeItem != nullptr) {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // �������ڵ�ͼ
    indoorMap = IndoorMap::create(mapFile);
    this->addChild(indoorMap, 0);  // ��ͼλ����ײ�

    // ������ɫ
    character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");  // �����ɫ��ͼƬ
    this->addChild(character.get(), 1);  // ��ɫλ�ڵ�ͼ֮��

    // �������̼����¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->character->onKeyPressed(keyCode, event);
        };
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
        this->character->onKeyReleased(keyCode, event);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    // �����ӽǿ�����
    viewController = new GameViewController(character.get(), indoorMap);  // ��ʼ���ӽǿ�����
    this->addChild(viewController, 2);  // ������������Ⱦ���㼶����Ҫ


    // ���� MapSwitcher��������Ƿ�ɹ�
    auto mapSwitcher = MapSwitcher::create("farm2", character.get());
    if (!mapSwitcher) {
        CCLOG("Error: Failed to create MapSwitcher.");
        return false;  // MapSwitcher ����ʧ�ܣ��˳���ִ������������
    }
    // ��ӵ���ǰ����
    this->addChild(mapSwitcher, 3);

    // ������ʱ��������ɫλ��
    this->schedule([this](float deltaTime) {
        // �����ӽǿ�����
        if (viewController) {
            /*checkCharacterPositionAndSwitchScene();*/
            viewController->update(deltaTime);
        }
        }, "check_position_key");

    return true;
}

// �������ڵ�ͼ����
Scene* IndoorScene::createScene(const std::string& mapFile)
{
    return IndoorScene::create(mapFile);
}

void IndoorScene::menuCloseCallback(Ref* pSender)
{
    // �˳���Ϸ
    Director::getInstance()->end();
}