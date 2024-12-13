#include "NPC.h"
#include "GiftItem.h"  // 引入礼物类的头文件

NPC::NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames)
    : name(name), affection(0), isMarried(false), isMoving(false) {
    setPosition(position);  // 初始化 NPC 位置
    initializeSprite(idleImage, walkFrames);  // 初始化精灵和动画
}

// 初始化 NPC 的精灵和动画（含参函数）
void NPC::initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames) {
    // 设置精灵外观，可以使用不同的纹理图片作为不同的精灵
    sprite = cocos2d::Sprite::create(idleImage);  // 使用传入的静止图像
    sprite->setPosition(getPosition());  // 设置精灵初始位置
    addChild(sprite);  // 将精灵添加到 NPC 节点

    // 设置 NPC 的行走动画
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 32, 32)));  // 使用传入的行走帧
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    walkAnimation = cocos2d::Animate::create(walkAnim);
}

// NPC 的对话
void NPC::showDialog() {
    int dialogueIndex = affection / 25;  // 根据好感度选择不同的对话
    dialogueIndex = std::min(dialogueIndex, (int)dialogues.size() - 1);
    std::string dialogue = dialogues[dialogueIndex];
    showMessage(dialogue);
}

void NPC::showMessage(const std::string& message) {
    // 创建对话框背景精灵
    cocos2d::Sprite* dialogBg = cocos2d::Sprite::create("dialog_background.png");
    dialogBg->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2,
        cocos2d::Director::getInstance()->getVisibleSize().height / 2));
    this->addChild(dialogBg);  // 将对话框背景添加到场景中

    // 创建一个标签来显示消息内容
    cocos2d::Label* dialogLabel = cocos2d::Label::createWithSystemFont(message, "Arial", 24);
    dialogLabel->setDimensions(400, 200);  // 设置标签大小
    dialogLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    dialogLabel->setVerticalAlignment(cocos2d::TextVAlignment::CENTER);
    dialogLabel->setPosition(dialogBg->getPosition());
    dialogBg->addChild(dialogLabel);  // 将标签添加到对话框中

    // 创建一个关闭按钮
    cocos2d::MenuItemImage* closeButton = cocos2d::MenuItemImage::create(
        "close_button_normal.png",  // 正常状态下的按钮图像
        "close_button_pressed.png", // 按下状态下的按钮图像
        CC_CALLBACK_1(NPC::closeDialog, this));  // 绑定按钮点击事件
    closeButton->setPosition(cocos2d::Vec2(dialogBg->getContentSize().width / 2 + 100,
        dialogBg->getContentSize().height / 2 - 100));

    // 创建一个菜单来管理关闭按钮
    cocos2d::Menu* menu = cocos2d::Menu::create(closeButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    dialogBg->addChild(menu);  // 将菜单添加到对话框中
}

// 关闭对话框的回调函数
void NPC::closeDialog(cocos2d::Ref* sender) {
    // 删除对话框和按钮
    this->removeChildByName("dialog_background.png");
}
// 增加好感度
void NPC::increaseAffection(int value) {
    affection = std::min(100, affection + value);
}

// NPC 是否与玩家在同一个位置
bool NPC::isPlayerNear(cocos2d::Vec2 playerPosition) {
    return playerPosition.distance(getPosition()) < 50.0f;  // 判断是否在同一格子附近
}

// 送礼物
void NPC::giftItem(GiftItem* gift) {
    increaseAffection(gift->affectionValue);  // 增加好感度
    showMessage("Thank you for the gift, " + gift->name);
}

// 使 NPC 移动到目标位置
void NPC::moveTo(cocos2d::Vec2 targetPosition) {
    if (isMoving) return;  // 防止 NPC 在移动时重复移动
    isMoving = true;
    destination = targetPosition;

    // 切换到行走动画
    sprite->runAction(walkAnimation);

    // 使用 Cocos2d 动画或插值方法让 NPC 移动
    cocos2d::MoveTo* moveAction = cocos2d::MoveTo::create(2.0f, destination);
    runAction(cocos2d::Sequence::create(moveAction, cocos2d::CallFunc::create([this]() {
        isMoving = false;
        sprite->stopAllActions();  // 停止行走动画
        sprite->setTexture("npc_idle.png");  // 恢复为静止状态
        }), nullptr));
}
