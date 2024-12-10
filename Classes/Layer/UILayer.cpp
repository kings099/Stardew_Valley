/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI界面UILayer类的实现
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/9
 * License:       MIT License
 ****************************************************************/
#include "UILayer.h"
#include "Classes/Character/Character.h"

USING_NS_CC;


// 析构函数
UILayer::~UILayer() {
    delete objectListLayer;
    delete timeLabel1;
    delete timeLabel2;
    delete timeDisplayLayer;
}

// 初始化UI层
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    initializeObjectList();
    initializeTimeDisplay();
    return true;
}

// 初始化物品栏
void UILayer::initializeObjectList() {
    // 创建物品栏背景
    objectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - objectListLayer->getContentSize().height / 2));
    this->addChild(objectListLayer, 0);

    // 创建删除物品按钮
    deleteObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/DefaultGarbageBinButton.png",
        "../Resources/UI/HoverGarbageBinButton.png",
        [this](cocos2d::Ref* sender) { character->deleteCurrentObject(); }
    );
    deleteObjectButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 2));
    this->addChild(deleteObjectButton, 0);  // 按钮在物品栏下面

    // 创建关闭物品栏按钮
    closeObjectListButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        [this](cocos2d::Ref* sender) { character->setObjectListStatus(false); }
    );
    closeObjectListButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height * 3 / 5));
    this->addChild(closeObjectListButton, 0);  // 按钮在物品栏下面
}

void UILayer::updateObjectList() {
    // 获取角色的物品栏状态和窗口大小
    const auto objectListStatus = character->getObjectListStatus();
    if (objectListLayer != nullptr) {
        this->removeChild(objectListLayer);
    }

    // 根据角色的物品栏状态初始化物品栏背景
    if (!objectListStatus) {
        objectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
        objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - objectListLayer->getContentSize().height / 2));
        deleteObjectButton->setVisible(false);
        closeObjectListButton->setVisible(false);
    }
    else {
        objectListLayer = Sprite::create("../Resources/UI/ObjectList.png");
        objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        deleteObjectButton->setVisible(true);
        closeObjectListButton->setVisible(true);
    }
    this->addChild(objectListLayer, 0);
}

// 初始化时间显示器
void UILayer::initializeTimeDisplay() {
    character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");

    // 获取可见区域大小
    visibleSize = Director::getInstance()->getVisibleSize();

    // 计算右上角的位置
    const Vec2 rightTopPos = Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f);  // 右上角，调整到合适的偏移量

    // 创建背景图片
    timeDisplayLayer = Sprite::create("../Resources/UI/timetable.png");

    // 获取原始图片尺寸
    const Size originalTimeDisplaySize = timeDisplayLayer->getContentSize();

    // 计算缩放比例，使得图片适应 16x16 像素
    const float scaleX = UI_SCALE / originalTimeDisplaySize.width;  // 计算 X 方向的缩放比例
    const float scaleY = UI_SCALE / originalTimeDisplaySize.height; // 计算 Y 方向的缩放比例

    // 设置缩放比例
    timeDisplayLayer->setScale(scaleX, scaleY);

    // 设置背景图片位置
    timeDisplayLayer->setPosition(rightTopPos);

    // 添加到场景
    this->addChild(timeDisplayLayer, 0);  // 背景在底层

    // 计算标签的位置，使其相对于背景位置
    const Vec2 labelPos1 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y + originalTimeDisplaySize.height * scaleY * 0.35f);  // 在背景图片的顶部
    const Vec2 labelPos2 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y - originalTimeDisplaySize.height * scaleY * 0.05f);  // 在 labelPos1 下面偏移 30

    // 创建并初始化 timeLabel1 和 timeLabel2
    timeLabel1 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    timeLabel1->setPosition(labelPos1);  // 设置 timeLabel1 相对于背景图片顶部的位置
    this->addChild(timeLabel1, 1);  // 标签在背景上面

    timeLabel2 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    timeLabel2->setPosition(labelPos2);  // 设置 timeLabel2 相对于 timeLabel1 的位置
    this->addChild(timeLabel2, 1);  // 标签在背景上面
}

// 更新时间显示器
void UILayer::updateTimeDisplay() {
    // 获取 TimeManager 的实例
    const TimeManager* timeManager = TimeManager::getInstance();

    // 获取并更新日期信息（星期和日期）
    std::string weekDay = timeManager->getWeekDay();
    timeLabel1->setString(weekDay);  // 显示星期几 

    // 获取并更新时间信息（白天/晚上和当前时间）
    const bool isDaytime = timeManager->isDaytime();
    std::string dayOrNight = isDaytime ? "白天" : "晚上";
    std::string timeOfDay = timeManager->getCurrentTime();
}

// 更新UI界面
void UILayer::update(float deltaTime) {
    // 更新物品栏
    updateObjectList();
    // 更新时间显示器
    updateTimeDisplay();
}