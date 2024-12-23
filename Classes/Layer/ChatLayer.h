/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     ChatLayer.h
 * File Function: NPC对话弹窗UI层的定义
 * Author:        达思睿
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef CHATLAYER_H
#define CHATLAYER_H

#include "cocos2d.h"
#include"proj.win32/constant.h"
#include "Character/NPC.h"
class ChatLayer : public cocos2d::Layer {
public:
    //构造函数
    ChatLayer(const std::string& message);

   //创建并显示对话框
    void showMessage(const std::string& message);

    //关闭对话框 
    void closeDialog(cocos2d::Ref* sender);

    //获取实例
    static ChatLayer* create(const std::string& message);
    
    //增加下方喜爱度显示文本，在送礼逻辑的时候才会显示
    void ChatLayer::addAffectionText(const std::string& affectionInfo);

private:
    cocos2d::LayerColor* _chatLayer;  ///< 半透明黑色背景层
    cocos2d::Sprite* _dialogBg;       ///< 对话框背景精灵
    cocos2d::Label* _dialogLabel;     ///< 显示消息的标签
};

#endif 
