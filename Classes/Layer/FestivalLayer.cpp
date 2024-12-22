
 /****************************************************************
  * Project Name:  Stardew_Valley
  * File Name:     FestivalLayer.cpp
  * File Function: ���ջUI���ʵ��
  * Author:        ��˼�
  * Update Date:   2024/12/16
  * License:       MIT License
  ****************************************************************/

#include "FestivalLayer.h"


USING_NS_CC;

FestivalLayer::FestivalLayer() : _festivalButton(nullptr) {
    // ���캯��
}

FestivalLayer::~FestivalLayer() {
    // ��������
}

bool FestivalLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ȡ��Ļ�ĳߴ�
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �������ջ��ť��Ĭ������Ϊ���ɼ�
    _festivalButton = ui::Button::create("../Resources/UI/festival.png", "../Resources/UI/festival.png");
    _festivalButton->setPosition(Vec2(visibleSize.width - _festivalButton->getContentSize().width * 2,
        visibleSize.height - _festivalButton->getContentSize().height * 4));
    _festivalButton->setVisible(false); 

    // �����������ť��Ĭ������Ϊ���ɼ�
    _communityButton = ui::Button::create("../Resources/UI/community.png", "../Resources/UI/community.png");
    _communityButton->setPosition(Vec2(visibleSize.width - _communityButton->getContentSize().width * 2,
        visibleSize.height - _communityButton->getContentSize().height * 6));
    _communityButton->setVisible(false);  // Ĭ�ϰ�ť���ɼ�

    // ��ӵ���¼�����
    _festivalButton->addClickEventListener(CC_CALLBACK_1(FestivalLayer::onButtonClicked, this, "Crazy ThursDay Festival Today!\nV u 50\n you can buy things with 50% discount"));
    _communityButton->addClickEventListener(CC_CALLBACK_1(FestivalLayer::onButtonClicked, this, "Abigail's favorite day. Go talk to her!"));

    // ����ť��ӵ���ǰ��
    this->addChild(_festivalButton);
    this->addChild(_communityButton);

    // ���ڸ��°�ť�Ŀɼ���
    schedule([this](float dt) {
        updateFestivalButtonVisibility();
        updateCommunityButtonVisibility();
        }, FESTIVAL_UPDATE, "updateFestivalButtonKey");

    return true;
}

// �ϲ���Ļص������������ַ�����Ϣ
void FestivalLayer::onButtonClicked(Ref* pSender, const std::string& message) {
    // ��������ʾ�Ի���
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    ChatLayer* chatLayer = ChatLayer::create(message);
    chatLayer->setPosition(Vec2(DIALOG_X_OFFSET, DIALOG_Y_OFFSET));

    this->addChild(chatLayer);
}

void FestivalLayer::updateFestivalButtonVisibility() {
    // ��ȡ��ǰ����
    TimeManager* timeManager = TimeManager::getInstance();
    std::string currentWeekDay = timeManager->getWeekDay();

    // �жϵ�ǰ�Ƿ���������
    if (currentWeekDay == "Thursday") {
        _festivalButton->setVisible(true);  // ��ʾ���հ�ť
    }
    else {
        _festivalButton->setVisible(false);  // ���ؽ��հ�ť
    }
}

void FestivalLayer::updateCommunityButtonVisibility() {
    // ��ȡ��ǰ����
    TimeManager* timeManager = TimeManager::getInstance();
    std::string currentWeekDay = timeManager->getWeekDay();

    // �жϵ�ǰ�Ƿ�������һ
    if (currentWeekDay == "Monday") {
        _communityButton->setVisible(true);  // ��ʾ�������ť
    }
    else {
        _communityButton->setVisible(false);  // �����������ť
    }
}

FestivalLayer* FestivalLayer::create() {
    FestivalLayer* ret = new FestivalLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}