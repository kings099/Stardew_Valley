#include "UILayer.h"

USING_NS_CC;


// 析构函数
UILayer::~UILayer() {
    delete objectListBackground;
}

// 初始化UI层
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// 初始化物品栏
void UILayer::initializeObjectList() {

    // 获取角色的物品栏状态和窗口大小
    const auto objectListStatus = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png")->checkObjectListStatus();
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (objectListBackground != nullptr) {
        this->removeChild(objectListBackground);
    }

    // 根据角色的物品栏状态初始化物品栏背景
    if (!objectListStatus) {
        objectListBackground = Sprite::create("../Resources/UI/ObjectListRow.png");
    }
    else {
        objectListBackground = Sprite::create("../Resources/UI/ObjectList.png");
    }

    // 设置位置并添加到层中
    if (objectListBackground != nullptr) {
        objectListBackground->setPosition(Vec2(0, 0));
        this->addChild(objectListBackground);
        objectListBackground->setScale(2.0f);
    }
}

// 更新UI界面
void UILayer::update(float deltaTime) {
    initializeObjectList(); 
}