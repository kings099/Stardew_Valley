#include "ChatLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

ChatLayer::ChatLayer(const std::string& message) {
    showMessage(message);
}

void ChatLayer::showMessage(const std::string& message) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // ������ɫ��͸��������
    chatLayer = LayerColor::create(Color4B(0, 0, 0, 150));  // ��͸������
    this->addChild(chatLayer, 3);

    // �����Ի��򱳾�
    dialogBg = Sprite::create("../Resources/UI/chatBox.png");
    if (!dialogBg) {
        CCLOG("Failed to load dialog background image.");
        return;
    }

    // ���öԻ����С
    float dialogWidth = visibleSize.width * 0.6f;
    float dialogHeight = visibleSize.height * 0.25f;
    dialogBg->setPosition(visibleSize.width / 2, visibleSize.height / 4);
    dialogBg->setScaleX(dialogWidth / dialogBg->getContentSize().width);
    dialogBg->setScaleY(dialogHeight / dialogBg->getContentSize().height);
    chatLayer->addChild(dialogBg, 0);

    // ������������ʾ��Ϣ�ı�ǩ
    dialogLabel = Label::createWithSystemFont(message, "Arial", 50);
    dialogLabel->setDimensions(dialogWidth - 20, dialogHeight - 20);
    dialogLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    dialogLabel->setVerticalAlignment(TextVAlignment::CENTER);
    dialogLabel->setPosition(dialogBg->getPosition());
    chatLayer->addChild(dialogLabel, 1);

    // �����رհ�ť
    MenuItemImage* closeButton = MenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        CC_CALLBACK_1(ChatLayer::closeDialog, this)
    );
    closeButton->setPosition(dialogBg->getPositionX(), dialogBg->getPositionY() - dialogHeight / 3 + closeButton->getContentSize().height);
    closeButton->setScale(1.5f);

    // ��Ӱ�ť���˵�
    Menu* menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    chatLayer->addChild(menu, 2);
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
    Size dialogSize = dialogBg->getContentSize();

    // ������ʾ���ܶ���Ϣ�ı�ǩ
    Label* affectionLabel = Label::createWithSystemFont(affectionInfo, "Arial", 30);

    // ���ñ�ǩ�Ŀ�Ⱥ͸߶�����ڶԻ���ı���
    float labelWidth = dialogSize.width*1.2;  // ������ռ�Ի����80%
    float labelHeight = dialogSize.height * 0.2f; // �߶�ռ�Ի����20%

    affectionLabel->setDimensions(labelWidth, labelHeight);  // ���Ʊ�ǩ�Ŀ�Ⱥ͸߶�
    affectionLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    affectionLabel->setVerticalAlignment(TextVAlignment::BOTTOM);  // �����ڵײ�

    // ���ñ�ǩ��λ�ã�����ڶԻ���ײ�����
    Vec2 position = dialogBg->getPosition() + Vec2(0, ( - dialogSize.height / 2 + labelHeight / 2)*1.4);  // �ʵ���ƫ��
    affectionLabel->setPosition(position);

    // ����ǩ��ӵ��Ի���Ĳ���
    chatLayer->addChild(affectionLabel, 1);
}