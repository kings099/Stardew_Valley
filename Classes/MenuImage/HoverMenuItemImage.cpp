/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     HoverAnimatedMenuItemImage.cpp
 * File Function: 悬停菜单按钮HoverMenuItemImage类的实现
 * Author:        尹诚成
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/

#include "HoverMenuItemImage.h"
#include"../proj.win32/Constant.h"

 // 构造函数
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

// 初始化
 bool HoverMenuItemImage::init()  {
    // 注册鼠标事件
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(HoverMenuItemImage::onMouseMove, this);
    listener->onMouseDown = CC_CALLBACK_1(HoverMenuItemImage::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

 // 鼠标移动事件
 void HoverMenuItemImage::onMouseMove(EventMouse* event) {
     // 检查鼠标位置是否在按钮范围内
     Vec2 location = Vec2(event->getCursorX(), event->getCursorY());
     if (this->getBoundingBox().containsPoint(location)) {
         scaleAnimation(ENLARGEMENT_RATIO);  // 鼠标悬停时放大
     }
     else {
         scaleAnimation(1.0f);  // 鼠标离开时还原
     }
 }

 // 鼠标点击事件
 void HoverMenuItemImage::onMouseDown(EventMouse* event) {
     Vec2 location = Vec2(event->getCursorX(), event->getCursorY());
     if (this->getBoundingBox().containsPoint(location)) {
         _callback(this); // 按钮被点击
     }
 }

 // 缩放动画函数
 void HoverMenuItemImage::scaleAnimation(float targetScale) {
     // 只当目标缩放与当前不同时才运行动画
     if (this->getScale() != targetScale) {
         auto scaleAction = ScaleTo::create(ENLARGEMENT_TIME, targetScale); // 动画持续时间
         this->runAction(scaleAction);
     }
 }