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
//构造函数
ChatLayer::ChatLayer(const std::string& message) {
    // 直接调用 showMessage 来显示消息
    showMessage(message);
}

//创建并显示对话框
void ChatLayer::showMessage(const std::string& message) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // 创建对话框背景
    _dialogBg = Sprite::create("../Resources/UI/chatBox.png");
   

    // 设置对话框大小
    float dialogWidth = DIALOG_WIDTH;
    float dialogHeight = DIALOG_HEIGHT;
    _dialogBg->setPosition(0, 0);
    _dialogBg->setScaleX(dialogWidth / _dialogBg->getContentSize().width);
    _dialogBg->setScaleY(dialogHeight / _dialogBg->getContentSize().height);
    this->addChild(_dialogBg);  

    // 创建并设置显示消息的标签
    _dialogLabel = Label::createWithSystemFont(message, FONT_TYPE, 20);
    _dialogLabel->setDimensions(dialogWidth - 20, dialogHeight - 20);
    _dialogLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    _dialogLabel->setVerticalAlignment(TextVAlignment::CENTER);
    _dialogLabel->setPosition(_dialogBg->getPosition());
    this->addChild(_dialogLabel);

    // 创建关闭按钮
    MenuItemImage* closeButton = MenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        CC_CALLBACK_1(ChatLayer::closeDialog, this)
    );
    closeButton->setPosition(_dialogBg->getPositionX(), _dialogBg->getPositionY() - dialogHeight / 2 + closeButton->getContentSize().height);
 
    // 添加按钮到菜单
    Menu* menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);  
}

//关闭对话框 
void ChatLayer::closeDialog(Ref* sender) {
    this->removeFromParentAndCleanup(true);  // 移除自己
}

//获取实例
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

//增加下方喜爱度显示文本，在送礼逻辑的时候才会显示
void ChatLayer::addAffectionText(const std::string& affectionInfo) {
    // 获取对话框的尺寸
    Size dialogSize = _dialogBg->getContentSize();

    // 创建显示亲密度信息的标签
    Label* affectionLabel = Label::createWithSystemFont(affectionInfo, FONT_TYPE, FONT_SIZE);

    // 设置标签的宽度和高度相对于对话框的比例
    float labelWidth = dialogSize.width * 1.2;  // 例如宽度占对话框的80%
    float labelHeight = dialogSize.height * 0.2f; // 高度占对话框的20%

    affectionLabel->setDimensions(labelWidth, labelHeight);  // 限制标签的宽度和高度
    affectionLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    affectionLabel->setVerticalAlignment(TextVAlignment::BOTTOM);  // 放置在底部

    // 设置标签的位置，相对于对话框底部对齐
    Vec2 position = _dialogBg->getPosition() + Vec2(0,-labelHeight);  // 适当的偏移
    affectionLabel->setPosition(position);

    // 将标签添加到对话框的层中
    this->addChild(affectionLabel);
}
