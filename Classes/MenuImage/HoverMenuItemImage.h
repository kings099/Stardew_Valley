/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     HoverAnimatedMenuItemImage.h
 * File Function: 悬停菜单按钮HoverMenuItemImage类的定义
 * Author:        尹诚成
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/

#include "cocos2d.h"

#ifndef _HOVER_MENU_ITEM_IMAGE_H_
#define _HOVER_MENU_ITEM_IMAGE_H_

USING_NS_CC;

class HoverMenuItemImage : public MenuItemImage {
public:
    // 构造函数
    static HoverMenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::function<void(Ref*)>& callback);

    // 初始化
    bool init();
private:
    // 鼠标移动事件
    void onMouseMove(EventMouse* event);

    // 缩放动画函数
    void scaleAnimation(float targetScale);
};

#endif !_HOVER_MENU_ITEM_IMAGE_H_