/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     ChatLayer.cpp
 * File Function: NPC对话弹窗UI层的实现
 * Author:        达思睿
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#include "ChatLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

ChatLayer::ChatLayer(const std::string& message) {
    showMessage(message);
}

void ChatLayer::showMessage(const std::string& message) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // 创建黑色半透明背景层
    chatLayer = LayerColor::create(Color4B(0, 0, 0, 150));  // 半透明背景
    this->addChild(chatLayer, 3);

    // 创建对话框背景
    dialogBg = Sprite::create("../Resources/UI/chatBox.png");
    if (!dialogBg) {
        CCLOG("Failed to load dialog background image.");
        return;
    }

    // 设置对话框大小
    float dialogWidth = visibleSize.width * 0.6f;
    float dialogHeight = visibleSize.height * 0.25f;
    dialogBg->setPosition(visibleSize.width / 2, visibleSize.height / 4);
    dialogBg->setScaleX(dialogWidth / dialogBg->getContentSize().width);
    dialogBg->setScaleY(dialogHeight / dialogBg->getContentSize().height);
    chatLayer->addChild(dialogBg, 0);

    // 创建并设置显示消息的标签
    dialogLabel = Label::createWithSystemFont(message, "Arial", 30);
    dialogLabel->setDimensions(dialogWidth - 20, dialogHeight - 20);
    dialogLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    dialogLabel->setVerticalAlignment(TextVAlignment::CENTER);
    dialogLabel->setPosition(dialogBg->getPosition());
    chatLayer->addChild(dialogLabel, 1);

    // 创建关闭按钮
    MenuItemImage* closeButton = MenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        CC_CALLBACK_1(ChatLayer::closeDialog, this)
    );
    closeButton->setPosition(dialogBg->getPositionX(), dialogBg->getPositionY() - dialogHeight / 3 + closeButton->getContentSize().height);
    closeButton->setScale(1.5f);

    // 添加按钮到菜单
    Menu* menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    chatLayer->addChild(menu, 2);
}

void ChatLayer::closeDialog(Ref* sender) {
    this->removeFromParentAndCleanup(true);  // 移除自己
  
}

ChatLayer* ChatLayer::create(const std::string& message) {
    ChatLayer* layer = new ChatLayer(message);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

void ChatLayer::addAffectionText(const std::string& affectionInfo) {
    // 获取对话框的尺寸
    Size dialogSize = dialogBg->getContentSize();

    // 创建显示亲密度信息的标签
    Label* affectionLabel = Label::createWithSystemFont(affectionInfo, "Arial", 30);

    // 设置标签的宽度和高度相对于对话框的比例
    float labelWidth = dialogSize.width*1.2;  // 例如宽度占对话框的80%
    float labelHeight = dialogSize.height * 0.2f; // 高度占对话框的20%

    affectionLabel->setDimensions(labelWidth, labelHeight);  // 限制标签的宽度和高度
    affectionLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    affectionLabel->setVerticalAlignment(TextVAlignment::BOTTOM);  // 放置在底部

    // 设置标签的位置，相对于对话框底部对齐
    Vec2 position = dialogBg->getPosition() + Vec2(0, ( - dialogSize.height / 2 + labelHeight / 2)*1.4);  // 适当的偏移
    affectionLabel->setPosition(position);

    // 将标签添加到对话框的层中
    chatLayer->addChild(affectionLabel, 1);
}