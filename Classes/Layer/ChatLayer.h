#pragma once
#pragma once
#ifndef CHATLAYER_H
#define CHATLAYER_H

#include "cocos2d.h"

/**
 * @class ChatLayer
 * @brief 用于管理游戏中的聊天界面，显示对话框和其他聊天 UI 组件。
 */
class ChatLayer : public cocos2d::Layer {
public:
    /**
     * @brief 构造函数
     *
     * @param message 显示的消息文本
     */
    ChatLayer(const std::string& message);

    /**
     * @brief 创建并显示对话框
     *
     * @param message 对话框中显示的文本内容
     */
    void showMessage(const std::string& message);

    /**
     * @brief 关闭对话框
     *
     * @param sender 触发关闭事件的对象
     */
    void closeDialog(cocos2d::Ref* sender);

    /**
     * @brief 获取 ChatLayer 实例
     *
     * @param message 对话框中显示的文本内容
     * @return ChatLayer* ChatLayer 实例
     */
    static ChatLayer* create(const std::string& message);

private:
    cocos2d::LayerColor* chatLayer;  ///< 半透明黑色背景层
    cocos2d::Sprite* dialogBg;       ///< 对话框背景精灵
    cocos2d::Label* dialogLabel;     ///< 显示消息的标签
};

#endif // CHATLAYER_H
