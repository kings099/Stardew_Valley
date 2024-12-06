#pragma once
#ifndef _HOVER_MOUSE_H_
#define _HOVER_MOUSE_H_

#include <string>
#include "cocos2d.h"

class HoverCursor : public cocos2d::Node {
public:
    // ����һ���µ� HoverCursor ʵ��
    static HoverCursor* create(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button);

    // ��ʼ�� HoverCursor ʵ��
    bool init(const std::string& defaultMouseImage, const std::string& hoverMouseImage, const std::string& activeMouseImage, cocos2d::Node* button);

private:
    std::string defaultCursorImage;  // Ĭ�Ϲ��ͼƬ·��
    std::string hoverCursorImage;    // ��ͣ���ͼƬ·��
    std::string activeCursorImage;   // ������ͼƬ·��
    cocos2d::Sprite* mouseSprite;   // ������ʾ���ͼ��
    cocos2d::Node* button;          // ָ����Ҫ���İ�ť

    // ����ƶ��¼��Ĵ�����
    void onMouseMove(cocos2d::Event* event);

    // ����ͷ��¼��Ĵ�����
    void onMouseUp(cocos2d::Event* event);
};

#endif // !_HOVER_MOUSE_H_
