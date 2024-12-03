#include "HoverMouse.h"

// 创建一个新的 HoverMouse 实例
HoverMouse* HoverMouse::create(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button)
{
    HoverMouse* mouse = new(std::nothrow) HoverMouse();
    if (mouse && mouse->init(defaultMouseImage, hoverMouseImage, activeMouseImage, button)) {
        mouse->autorelease();
        return mouse;
    }
    CC_SAFE_DELETE(mouse);
    return nullptr;
}

// 初始化 HoverMouse 实例
bool HoverMouse::init(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button)
{
    if (!Node::init()) {
        return false;
    }

    this->defaultMouseImage = defaultMouseImage;
    this->hoverMouseImage = hoverMouseImage;
    this->activeMouseImage = activeMouseImage;
    this->button = button; // 保存按钮指针

    // 创建鼠标图像精灵
    mouseSprite = cocos2d::Sprite::create(defaultMouseImage);
    this->addChild(mouseSprite);

    // 鼠标事件监听
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverMouse::onMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(HoverMouse::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 鼠标移动事件的处理函数
void HoverMouse::onMouseMove(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标位置
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // 更新鼠标精灵的位置

        // 检查鼠标是否在按钮区域内
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // 如果鼠标在按钮范围内，设置悬停图像
            mouseSprite->setTexture(hoverMouseImage);
        }
        else {
            // 否则，恢复到默认鼠标图像
            mouseSprite->setTexture(defaultMouseImage);
        }
    }
}

// 鼠标释放事件的处理函数
void HoverMouse::onMouseUp(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标位置
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // 更新鼠标精灵的位置

        // 检查鼠标是否在按钮区域内
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // 如果鼠标在按钮范围内，设置激活图像
            mouseSprite->setTexture(activeMouseImage);
        }
        else {
            // 否则，恢复到默认鼠标图像
            mouseSprite->setTexture(defaultMouseImage);
        }
    }
}
