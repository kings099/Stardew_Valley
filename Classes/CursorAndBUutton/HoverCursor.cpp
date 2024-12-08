#include "HoverCursor.h"

// 创建一个新的 HoverCursor 实例
HoverCursor* HoverCursor::create(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button)
{
    HoverCursor* cursor = new(std::nothrow) HoverCursor();
    if (cursor && cursor->init(defaultMouseImage, hoverMouseImage, activeMouseImage, button)) {
        cursor->autorelease();
        return cursor;
    }
    CC_SAFE_DELETE(cursor);
    return nullptr;
}

// 初始化 HoverCursor 实例
bool HoverCursor::init(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button)
{
    if (!Node::init()) {
        return false;
    }

    this->defaultCursorImage = defaultCursorImage;
    this->hoverCursorImage = hoverCursorImage;
    this->activeCursorImage = activeCursorImage;
    this->button = button; // 保存按钮指针

    // 创建鼠标图像精灵
    mouseSprite = cocos2d::Sprite::create(defaultMouseImage);
    this->addChild(mouseSprite);

    // 鼠标事件监听
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverCursor::onMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(HoverCursor::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 鼠标移动事件的处理函数
void HoverCursor::onMouseMove(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标位置
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // 更新鼠标精灵的位置

        // 检查鼠标是否在按钮区域内
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // 如果鼠标在按钮范围内，设置悬停图像
            mouseSprite->setTexture(hoverCursorImage);
        }
        else {
            // 否则，恢复到默认鼠标图像
            mouseSprite->setTexture(defaultCursorImage);
        }
    }
}

// 鼠标释放事件的处理函数
void HoverCursor::onMouseUp(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标位置
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // 更新鼠标精灵的位置

        // 检查鼠标是否在按钮区域内
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // 如果鼠标在按钮范围内，设置激活图像
            mouseSprite->setTexture(activeCursorImage);
        }
        else {
            // 否则，恢复到默认鼠标图像
            mouseSprite->setTexture(defaultCursorImage);
        }
    }
}
