#include "HoverCursor.h"

// ����һ���µ� HoverCursor ʵ��
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

// ��ʼ�� HoverCursor ʵ��
bool HoverCursor::init(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button)
{
    if (!Node::init()) {
        return false;
    }

    this->defaultCursorImage = defaultCursorImage;
    this->hoverCursorImage = hoverCursorImage;
    this->activeCursorImage = activeCursorImage;
    this->button = button; // ���水ťָ��

    // �������ͼ����
    mouseSprite = cocos2d::Sprite::create(defaultMouseImage);
    this->addChild(mouseSprite);

    // ����¼�����
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverCursor::onMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(HoverCursor::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// ����ƶ��¼��Ĵ�����
void HoverCursor::onMouseMove(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ���λ��
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // ������꾫���λ��

        // �������Ƿ��ڰ�ť������
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // �������ڰ�ť��Χ�ڣ�������ͣͼ��
            mouseSprite->setTexture(hoverCursorImage);
        }
        else {
            // ���򣬻ָ���Ĭ�����ͼ��
            mouseSprite->setTexture(defaultCursorImage);
        }
    }
}

// ����ͷ��¼��Ĵ�����
void HoverCursor::onMouseUp(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ���λ��
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // ������꾫���λ��

        // �������Ƿ��ڰ�ť������
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // �������ڰ�ť��Χ�ڣ����ü���ͼ��
            mouseSprite->setTexture(activeCursorImage);
        }
        else {
            // ���򣬻ָ���Ĭ�����ͼ��
            mouseSprite->setTexture(defaultCursorImage);
        }
    }
}
