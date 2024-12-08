#include "HoverMouse.h"

// ����һ���µ� HoverMouse ʵ��
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

// ��ʼ�� HoverMouse ʵ��
bool HoverMouse::init(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button)
{
    if (!Node::init()) {
        return false;
    }

    this->defaultMouseImage = defaultMouseImage;
    this->hoverMouseImage = hoverMouseImage;
    this->activeMouseImage = activeMouseImage;
    this->button = button; // ���水ťָ��

    // �������ͼ����
    mouseSprite = cocos2d::Sprite::create(defaultMouseImage);
    this->addChild(mouseSprite);

    // ����¼�����
    auto listener = cocos2d::EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverMouse::onMouseMove, this);
    listener->onMouseUp = CC_CALLBACK_1(HoverMouse::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// ����ƶ��¼��Ĵ�����
void HoverMouse::onMouseMove(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ���λ��
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // ������꾫���λ��

        // �������Ƿ��ڰ�ť������
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // �������ڰ�ť��Χ�ڣ�������ͣͼ��
            mouseSprite->setTexture(hoverMouseImage);
        }
        else {
            // ���򣬻ָ���Ĭ�����ͼ��
            mouseSprite->setTexture(defaultMouseImage);
        }
    }
}

// ����ͷ��¼��Ĵ�����
void HoverMouse::onMouseUp(cocos2d::Event* event)
{
    const auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ���λ��
        cocos2d::Vec2 mousePos = mouseEvent->getLocation();
        mouseSprite->setPosition(mousePos);  // ������꾫���λ��

        // �������Ƿ��ڰ�ť������
        if (button->getBoundingBox().containsPoint(button->getParent()->convertToNodeSpace(mousePos))) {
            // �������ڰ�ť��Χ�ڣ����ü���ͼ��
            mouseSprite->setTexture(activeMouseImage);
        }
        else {
            // ���򣬻ָ���Ĭ�����ͼ��
            mouseSprite->setTexture(defaultMouseImage);
        }
    }
}
