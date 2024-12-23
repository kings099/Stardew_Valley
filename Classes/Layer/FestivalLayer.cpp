 /****************************************************************
  * Project Name:  Stardew_Valley
  * File Name:     FestivalLayer.cpp
  * File Function: 节日活动UI层的实现
  * Author:        达思睿
  * Update Date:   2024/12/16
  * License:       MIT License
  ****************************************************************/

#include "FestivalLayer.h"


USING_NS_CC;
// 构造函数
FestivalLayer::FestivalLayer() : _festivalButton(nullptr) {
  
}

// 析构函数
FestivalLayer::~FestivalLayer() {

}

// 初始化函数
bool FestivalLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // 获取屏幕的尺寸
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建节日活动按钮，默认设置为不可见
    _festivalButton = ui::Button::create("../Resources/UI/SkillStar.png", "../Resources/UI/SkillStar.png");
    _festivalButton->setPosition(Vec2(visibleSize.width - _festivalButton->getContentSize().width * 2,
        visibleSize.height - _festivalButton->getContentSize().height * 4));
    _festivalButton->setVisible(false); 

    // 创建社区活动按钮，默认设置为不可见
    _communityButton = ui::Button::create("../Resources/UI/SkillStar.png", "../Resources/UI/SkillStar.png");
    _communityButton->setPosition(Vec2(visibleSize.width - _communityButton->getContentSize().width * 2,
        visibleSize.height - _communityButton->getContentSize().height * 6));
    _communityButton->setVisible(false);  // 默认按钮不可见

    // 添加点击事件监听
    _festivalButton->addClickEventListener(CC_CALLBACK_1(FestivalLayer::onButtonClicked, this, "Crazy ThursDay Festival Today!\nV u 50\n you can buy things with 50% discount"));
    _communityButton->addClickEventListener(CC_CALLBACK_1(FestivalLayer::onButtonClicked, this, "Abigail's favorite day. Go talk to her!"));

    // 将按钮添加到当前层
    this->addChild(_festivalButton);
    this->addChild(_communityButton);

    // 定期更新按钮的可见性
    schedule([this](float dt) {
        updateFestivalButtonVisibility();
        updateCommunityButtonVisibility();
        }, FESTIVAL_UPDATE, "updateFestivalButtonKey");

    return true;
}

//点击按钮执行的回调函数
void FestivalLayer::onButtonClicked(Ref* pSender, const std::string& message) {
    // 创建并显示对话框
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    ChatLayer* chatLayer = ChatLayer::create(message);
    chatLayer->setPosition(Vec2(DIALOG_X_OFFSET, DIALOG_Y_OFFSET));

    this->addChild(chatLayer);
}


//更新节日按钮是否可见
void FestivalLayer::updateFestivalButtonVisibility() {
    // 获取当前日期
    TimeManager* timeManager = TimeManager::getInstance();
    std::string currentWeekDay = timeManager->getWeekDay();

    // 判断当前是否是星期四
    if (currentWeekDay == "Thursday") {
        _festivalButton->setVisible(true);  // 显示节日按钮
    }
    else {
        _festivalButton->setVisible(false);  // 隐藏节日按钮
    }
}

//更新社区按钮是否可见
void FestivalLayer::updateCommunityButtonVisibility() {
    // 获取当前日期
    TimeManager* timeManager = TimeManager::getInstance();
    std::string currentWeekDay = timeManager->getWeekDay();

    // 判断当前是否是星期一
    if (currentWeekDay == "Monday") {
        _communityButton->setVisible(true);  // 显示社区活动按钮
    }
    else {
        _communityButton->setVisible(false);  // 隐藏社区活动按钮
    }
}

// 创建并返回一个FestivalLayer实例
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