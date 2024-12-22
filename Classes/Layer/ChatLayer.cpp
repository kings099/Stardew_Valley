/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     ChatLayer.cpp
 * File Function: NPC�Ի�����UI���ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/16
 * License:       MIT License
 ****************************************************************/
#include "ChatLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

ChatLayer::ChatLayer(const std::string& message) {
    // ֱ�ӵ��� showMessage ����ʾ��Ϣ
    showMessage(message);
}

void ChatLayer::showMessage(const std::string& message) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // �����Ի��򱳾�
    _dialogBg = Sprite::create("../Resources/UI/chatBox.png");
   

    // ���öԻ����С
    float dialogWidth = 500.0f;
    float dialogHeight = 120.f;
    _dialogBg->setPosition(0, 0);
    _dialogBg->setScaleX(dialogWidth / _dialogBg->getContentSize().width);
    _dialogBg->setScaleY(dialogHeight / _dialogBg->getContentSize().height);
    this->addChild(_dialogBg);  

    // ������������ʾ��Ϣ�ı�ǩ
    _dialogLabel = Label::createWithSystemFont(message, FONT_TYPE, 20);
    _dialogLabel->setDimensions(dialogWidth - 20, dialogHeight - 20);
    _dialogLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    _dialogLabel->setVerticalAlignment(TextVAlignment::CENTER);
    _dialogLabel->setPosition(_dialogBg->getPosition());
    this->addChild(_dialogLabel);

    // �����رհ�ť
    MenuItemImage* closeButton = MenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        CC_CALLBACK_1(ChatLayer::closeDialog, this)
    );
    closeButton->setPosition(_dialogBg->getPositionX(), _dialogBg->getPositionY() - dialogHeight / 2 + closeButton->getContentSize().height);
 
    // ��Ӱ�ť���˵�
    Menu* menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);  
}

void ChatLayer::closeDialog(Ref* sender) {
    this->removeFromParentAndCleanup(true);  // �Ƴ��Լ�
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
    // ��ȡ�Ի���ĳߴ�
    Size dialogSize = _dialogBg->getContentSize();

    // ������ʾ���ܶ���Ϣ�ı�ǩ
    Label* affectionLabel = Label::createWithSystemFont(affectionInfo, "Arial", 20);

    // ���ñ�ǩ�Ŀ�Ⱥ͸߶�����ڶԻ���ı���
    float labelWidth = dialogSize.width * 1.2;  // ������ռ�Ի����80%
    float labelHeight = dialogSize.height * 0.2f; // �߶�ռ�Ի����20%

    affectionLabel->setDimensions(labelWidth, labelHeight);  // ���Ʊ�ǩ�Ŀ�Ⱥ͸߶�
    affectionLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    affectionLabel->setVerticalAlignment(TextVAlignment::BOTTOM);  // �����ڵײ�

    // ���ñ�ǩ��λ�ã�����ڶԻ���ײ�����
    Vec2 position = _dialogBg->getPosition() + Vec2(0,-labelHeight);  // �ʵ���ƫ��
    affectionLabel->setPosition(position);

    // ����ǩ��ӵ��Ի���Ĳ���
    this->addChild(affectionLabel);
}
