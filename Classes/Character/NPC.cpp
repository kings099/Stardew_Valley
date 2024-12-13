#include "NPC.h"
#include "GiftItem.h"  // �����������ͷ�ļ�

NPC::NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames)
    : name(name), affection(0), isMarried(false), isMoving(false) {
    setPosition(position);  // ��ʼ�� NPC λ��
    initializeSprite(idleImage, walkFrames);  // ��ʼ������Ͷ���
}

// ��ʼ�� NPC �ľ���Ͷ��������κ�����
void NPC::initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames) {
    // ���þ�����ۣ�����ʹ�ò�ͬ������ͼƬ��Ϊ��ͬ�ľ���
    sprite = cocos2d::Sprite::create(idleImage);  // ʹ�ô���ľ�ֹͼ��
    sprite->setPosition(getPosition());  // ���þ����ʼλ��
    addChild(sprite);  // ��������ӵ� NPC �ڵ�

    // ���� NPC �����߶���
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 32, 32)));  // ʹ�ô��������֡
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    walkAnimation = cocos2d::Animate::create(walkAnim);
}

// NPC �ĶԻ�
void NPC::showDialog() {
    int dialogueIndex = affection / 25;  // ���ݺøж�ѡ��ͬ�ĶԻ�
    dialogueIndex = std::min(dialogueIndex, (int)dialogues.size() - 1);
    std::string dialogue = dialogues[dialogueIndex];
    showMessage(dialogue);
}

void NPC::showMessage(const std::string& message) {
    // �����Ի��򱳾�����
    cocos2d::Sprite* dialogBg = cocos2d::Sprite::create("dialog_background.png");
    dialogBg->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2,
        cocos2d::Director::getInstance()->getVisibleSize().height / 2));
    this->addChild(dialogBg);  // ���Ի��򱳾���ӵ�������

    // ����һ����ǩ����ʾ��Ϣ����
    cocos2d::Label* dialogLabel = cocos2d::Label::createWithSystemFont(message, "Arial", 24);
    dialogLabel->setDimensions(400, 200);  // ���ñ�ǩ��С
    dialogLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    dialogLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    dialogLabel->setPosition(dialogBg->getPosition());
    dialogBg->addChild(dialogLabel);  // ����ǩ��ӵ��Ի�����

    // ����һ���رհ�ť
    cocos2d::MenuItemImage* closeButton = cocos2d::MenuItemImage::create(
        "close_button_normal.png",  // ����״̬�µİ�ťͼ��
        "close_button_pressed.png", // ����״̬�µİ�ťͼ��
        CC_CALLBACK_1(NPC::closeDialog, this));  // �󶨰�ť����¼�
    closeButton->setPosition(cocos2d::Vec2(dialogBg->getContentSize().width / 2 + 100,
        dialogBg->getContentSize().height / 2 - 100));

    // ����һ���˵�������رհ�ť
    cocos2d::Menu* menu = cocos2d::Menu::create(closeButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    dialogBg->addChild(menu);  // ���˵���ӵ��Ի�����
}

// �رնԻ���Ļص�����
void NPC::closeDialog(cocos2d::Ref* sender) {
    // ɾ���Ի���Ͱ�ť
    this->removeChildByName("dialog_background.png");
}
// ���Ӻøж�
void NPC::increaseAffection(int value) {
    affection = std::min(100, affection + value);
}

// NPC �Ƿ��������ͬһ��λ��
bool NPC::isPlayerNear(cocos2d::Vec2 playerPosition) {
    return playerPosition.distance(getPosition()) < 50.0f;  // �ж��Ƿ���ͬһ���Ӹ���
}

// ������
void NPC::giftItem(GiftItem* gift) {
    increaseAffection(gift->affectionValue);  // ���Ӻøж�
    showMessage("Thank you for the gift, " + gift->name);
}

// ʹ NPC �ƶ���Ŀ��λ��
void NPC::moveTo(cocos2d::Vec2 targetPosition) {
    if (isMoving) return;  // ��ֹ NPC ���ƶ�ʱ�ظ��ƶ�
    isMoving = true;
    destination = targetPosition;

    // �л������߶���
    sprite->runAction(walkAnimation);

    // ʹ�� Cocos2d �������ֵ������ NPC �ƶ�
    cocos2d::MoveTo* moveAction = cocos2d::MoveTo::create(2.0f, destination);
    runAction(cocos2d::Sequence::create(moveAction, cocos2d::CallFunc::create([this]() {
        isMoving = false;
        sprite->stopAllActions();  // ֹͣ���߶���
        sprite->setTexture("npc_idle.png");  // �ָ�Ϊ��ֹ״̬
        }), nullptr));
}
