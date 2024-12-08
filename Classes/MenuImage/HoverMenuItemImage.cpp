/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     HoverAnimatedMenuItemImage.cpp
 * File Function: ��ͣ�˵���ťHoverMenuItemImage���ʵ��
 * Author:        ���ϳ�
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/

#include "HoverMenuItemImage.h"
#include"../proj.win32/Constant.h"

 // ���캯��
HoverMenuItemImage *HoverMenuItemImage::create(const std::string& normalImage, const std::string& selectedImage, const std::function<void(Ref*)>& callback) {
    HoverMenuItemImage* item = new HoverMenuItemImage();
    if (item && item->initWithNormalImage(normalImage, selectedImage, "", callback)) {
        item->autorelease();
        item->init();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

// ��ʼ��
 bool HoverMenuItemImage::init()  {
    // ע������¼�
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverMenuItemImage::onMouseMove, this);
    listener->onMouseDown = CC_CALLBACK_1(HoverMenuItemImage::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

 // ����ƶ��¼�
 void HoverMenuItemImage::onMouseMove(EventMouse* event) {
     // ������λ���Ƿ��ڰ�ť��Χ��
     Vec2 location = Vec2(event->getCursorX(), event->getCursorY());
     if (this->getBoundingBox().containsPoint(location)) {
         scaleAnimation(ENLARGEMENT_RATIO);  // �����ͣʱ�Ŵ�
     }
     else {
         scaleAnimation(1.0f);  // ����뿪ʱ��ԭ
     }
 }

 // ������¼�
 void HoverMenuItemImage::onMouseDown(EventMouse* event) {
     Vec2 location = Vec2(event->getCursorX(), event->getCursorY());
     if (this->getBoundingBox().containsPoint(location)) {
         _callback(this); // ��ť�����
     }
 }

 // ���Ŷ�������
 void HoverMenuItemImage::scaleAnimation(float targetScale) {
     // ֻ��Ŀ�������뵱ǰ��ͬʱ�����ж���
     if (this->getScale() != targetScale) {
         auto scaleAction = ScaleTo::create(ENLARGEMENT_TIME, targetScale); // ��������ʱ��
         this->runAction(scaleAction);
     }
 }