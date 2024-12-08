#pragma once
#ifndef _HOVER_MOUSE_H_
#define _HOVER_MOUSE_H_

#include <string>
#include "cocos2d.h"

class HoverCursor : public cocos2d::Node {
public:
    // 创建一个新的 HoverCursor 实例
    static HoverCursor* create(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button);

    // 初始化 HoverCursor 实例
    bool init(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button);

private:
    std::string defaultCursorImage;  // 默认光标图片路径
    std::string hoverCursorImage;    // 悬停光标图片路径
    std::string activeCursorImage;   // 激活光标图片路径
    cocos2d::Sprite* mouseSprite;   // 用于显示鼠标图像
    cocos2d::Node* button;          // 指向需要检测的按钮

    // 鼠标移动事件的处理函数
    void onMouseMove(cocos2d::Event* event);

    // 鼠标释放事件的处理函数
    void onMouseUp(cocos2d::Event* event);
};

#endif // !_HOVER_MOUSE_H_
