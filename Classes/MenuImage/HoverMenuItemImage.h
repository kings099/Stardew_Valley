/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     HoverAnimatedMenuItemImage.h
 * File Function: ��ͣ�˵���ťHoverMenuItemImage��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/

#include "cocos2d.h"

#ifndef _HOVER_MENU_ITEM_IMAGE_H_
#define _HOVER_MENU_ITEM_IMAGE_H_

USING_NS_CC;

class HoverMenuItemImage : public MenuItemImage {
public:
    // ���캯��
    static HoverMenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::function<void(Ref*)>& callback);

    // ��ʼ��
    bool init();
private:
    // ����ƶ��¼�
    void onMouseMove(EventMouse* event);

    // ���Ŷ�������
    void scaleAnimation(float targetScale);
};

#endif !_HOVER_MENU_ITEM_IMAGE_H_