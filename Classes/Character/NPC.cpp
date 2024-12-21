/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     NPC.cpp
 * File Function: 封装了与 NPC 相关的基本功能，
                  显示对话框、增加好感度、接受礼物、播放行走动画等。
                  NPC 对象可以与玩家互动，包括对话以及送礼。
 * Author:        达思睿
 * Update Date:   2024/12/13
 * License:       MIT License
 ****************************************************************/

#include "NPC.h"

USING_NS_CC;

 // NPC 初始化
NPC::NPC(std::string name, cocos2d::Vec2 position, const std::string& idleImage, const std::vector<std::string>& walkFrames)
    : name(name), affection(0), isMarried(false), isMoving(false) {
    setPosition(position);                    // 初始化 NPC 位置
    initializeSprite(idleImage, walkFrames);  // 初始化精灵和动画

    // 注册键盘监听事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(NPC::onKeyPressed, this);  // 绑定按键事件
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 初始化精灵和动画
void NPC::initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames) {
    sprite = cocos2d::Sprite::create(idleImage);
    if (sprite == nullptr) {
        CCLOG("Failed to load sprite: %s", idleImage.c_str());
    }
    sprite->setPosition(getPosition());
    addChild(sprite);

    // 设置精灵缩放比例,让精灵的大小固定
    sprite->setScaleX(NPC_WIDTH / sprite->getContentSize().width);  
    sprite->setScaleY(NPC_HEIGHT / sprite->getContentSize().height); 

    CCLOG("NPC Width: %f, Height: %f", sprite->getContentSize().width, sprite->getContentSize().height);
    // 设置行走动画
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 64, 64)));
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    walkAnimation = cocos2d::Animate::create(walkAnim);
}

void NPC::showDialog() {
    int dialogueIndex = affection / 25;
    dialogueIndex = std::min(dialogueIndex, (int)dialogues.size() - 1);
    std::string username = CharacterInfo::getInstance()->getUsername();  // 获取用户名
    std::string dialogue = dialogues[dialogueIndex] + "," + username;

    // 创建并显示 ChatLayer
    ChatLayer* chatLayer = ChatLayer::create(dialogue);  // 创建 ChatLayer 实例并传入对话内容

    // 设置对话框位置相对于 NPC
    Vec2 npcPosition = getPosition();  // 获取 NPC 当前的位置
    chatLayer->setPosition(npcPosition.x +250, npcPosition.y+60);  // 将对话框位置设置为 NPC 的位置

    // 将 ChatLayer 添加为 NPC 的子节点
    this->addChild(chatLayer, 1);  // 将 ChatLayer 添加为 NPC 的子节点，优先级设置为 1000
}

// 增加好感度
void NPC::increaseAffection(int value, bool isRomantic) {
    affection = std::min(100, affection + value);
}

// 显示询问用户是否求婚的UI
void NPC::showMarriageChoices() {
    if (affection >= 0 && !isMarried) {
        const auto visibleSize = Director::getInstance()->getVisibleSize();
        const auto origin = Director::getInstance()->getVisibleOrigin();

        // 创建一个自定义的对话框
        auto dialog = ui::Layout::create();
        dialog->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        dialog->setBackGroundColor(Color3B(0, 0, 0));  // 设置背景为黑色
        dialog->setBackGroundColorOpacity(128);  // 设置透明度为128（半透明）

        // 设置对话框的锚点为左下角 (0, 0)
        dialog->setAnchorPoint(Vec2(0, 0));

        // 设置对话框大小
        float dialogWidth = 500.0f;
        float dialogHeight = 120.f;
        dialog->setContentSize(Size(dialogWidth, dialogHeight));  // 设置对话框的内容大小

        // 设置对话框的位置为 (50, 0)
        dialog->setPosition(Vec2(50, 0));
        this->addChild(dialog, 10);  // 添加到 NPC 层，设置优先级为 10 确保显示在最上层

        // 创建询问文本信息
        auto text = Label::createWithSystemFont("Would you like to propose?\nAffection is sufficient now!", "Arial", 24);
        text->setPosition(Vec2(dialog->getContentSize().width / 2, dialog->getContentSize().height / 2));
        dialog->addChild(text);

        // "Yes" 按钮，玩家同意结婚，字体大小设为24
        auto yesButton = ui::Button::create();
        yesButton->setTitleText("Yes");
        yesButton->setTitleFontSize(24);  // 设置按钮字体大小为24
        yesButton->setPosition(Vec2(dialog->getContentSize().width * 0.3f, -dialog->getContentSize().height * 0.3f));
        yesButton->addClickEventListener([this, dialog](Ref* sender) {
            marryPlayer();  // 玩家同意结婚
            dialog->removeFromParent();  // 移除对话框
            });
        dialog->addChild(yesButton);

        // "No" 按钮，玩家拒绝结婚，字体大小设为24
        auto noButton = ui::Button::create();
        noButton->setTitleText("No");
        noButton->setTitleFontSize(24);  // 设置按钮字体大小为24
        noButton->setPosition(Vec2(dialog->getContentSize().width * 0.7f, -dialog->getContentSize().height * 0.3f));
        noButton->addClickEventListener([this, dialog](Ref* sender) {
            dialog->removeFromParent();  // 移除对话框
            });
        dialog->addChild(noButton);
    }
}


//处理求婚逻辑，包括播放动画，修改关系，消息提示用户已经结婚
void NPC::marryPlayer() {
    // 播放求婚动画，并在动画完成后显示结婚消息
    playMarriageAnimation();

    // 设置婚姻状态
    isMarried = true;

    // 创建结婚消息的回调函数
    auto showWeddingMessage = [this]() {
        // 显示结婚消息
        std::string weddingMessage = "You and " + name + " are now married!";
        ChatLayer* chatLayer = ChatLayer::create(weddingMessage);
        // 设置对话框位置相对于 NPC

        Vec2 npcPosition = getPosition();  // 获取 NPC 当前的位置
        chatLayer->setPosition(npcPosition.x + 250, npcPosition.y + 60);  // 将对话框位置设置为 NPC 的位置

        this->addChild(chatLayer, 1);
        };

    // 创建一个延时动作，在动画结束后调用 showWeddingMessage 函数
    auto delayAction = Sequence::create(DelayTime::create(3.0f), CallFunc::create(showWeddingMessage), nullptr);

    // 在结婚动画结束时执行结婚消息显示
    this->runAction(delayAction);
}

void NPC::playMarriageAnimation() {
    // 创建一个闪烁的心形精灵
    auto heartSprite = Sprite::create("../Resources/Characters/NPC/happy.png");
    // 设置开心表情的位置，偏移位置稍微往上
    Vec2 npcPosition = getPosition();
    heartSprite->setPosition(npcPosition.x, npcPosition.y + sprite->getContentSize().height / 2);  // 头顶位置

    // 将开心表情添加为 NPC 的子节点，这样它的坐标就会随 NPC 移动
    this->addChild(heartSprite, 2);
    heartSprite->setOpacity(0);  // 初始透明度为0，不可见

    // 放大效果
    auto scaleUp = ScaleTo::create(3.0f, 1.5f);  // 放大效果
    auto scaleDown = ScaleTo::create(0.3f, 1.0f);  // 恢复到正常大小

    // 闪烁效果，快速地透明化和出现
    auto fadeIn = FadeIn::create(0.2f);  // 渐显效果
    auto fadeOut = FadeOut::create(0.2f);  // 渐隐效果

    // 颜色变化效果
    auto colorChange = TintTo::create(0.2f, 255, 0, 0);  // 直接设置为红色
    auto revertColor = TintTo::create(0.2f, 255, 255, 255); // 恢复为原来的颜色（白色）

    // 让心形精灵闪烁的动作序列
    auto blinkSequence = Sequence::create(fadeIn, scaleUp, colorChange, fadeOut, scaleDown, revertColor, nullptr);

    // 创建一个重复的闪烁效果
    auto repeat = RepeatForever::create(blinkSequence);

    // 播放动画
    heartSprite->runAction(repeat);

    // 如果要展示完成后销毁心形精灵，可以在动画结束时移除它
    heartSprite->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([heartSprite]() {
        heartSprite->removeFromParent();
        }), nullptr));
}

void NPC::showTaskList() {
    std::string taskInfo = "Available Tasks:\n";

    // 生成两个任务按钮
    if (tasks.size() >= 2) {
        // 获取任务1
        Task* task1 = tasks[0];
        std::string task1Info = task1->getDescription() + (task1->checkCompletion() ? " (Completed)" : " (In Progress)");

        // 获取任务2
        Task* task2 = tasks[1];
        std::string task2Info = task2->getDescription() + (task2->checkCompletion() ? " (Completed)" : " (In Progress)");

        // 获取当前场景
        auto runningScene = cocos2d::Director::getInstance()->getRunningScene();
        if (!runningScene) {
            return;
        }

        // 获取屏幕的宽度和高度，计算按钮的位置
        const auto visibleSize = Director::getInstance()->getVisibleSize();

        // 创建任务1按钮
        auto taskButton1 = ui::Button::create();
        taskButton1->setTitleText(task1Info);
        taskButton1->setPosition(Vec2(250,180));
        taskButton1->setTitleFontSize(24); // 设置字体大小
        taskButton1->addClickEventListener([this, task1, runningScene](Ref* sender) {
            if (!task1->checkCompletion()) {
               
            }
            else {

            }
            });
       this->addChild(taskButton1, 10);

        // 创建任务2按钮
        auto taskButton2 = ui::Button::create();
        taskButton2->setTitleText(task2Info);
        taskButton2->setPosition(Vec2(250, 170));
        taskButton2->setTitleFontSize(24); // 设置字体大小
        taskButton2->addClickEventListener([this, task2, runningScene](Ref* sender) {
            if (!task2->checkCompletion()) {
                // 任务2的逻辑：检查玩家是否有5个木材
              
            }
            else {

            }
            });
        runningScene->addChild(taskButton2, 10);
    }
}


void NPC::addTask(Task* task) {
    tasks.push_back(task);
}


// 判断玩家是否接近
bool NPC::isPlayerNear(cocos2d::Vec2 playerPosition) {
    return playerPosition.distance(getPosition()) < 50.0f;
}


void NPC::giftItem(GiftItem* gift) {
    int affectionIncrease = gift->getAffectionForNPC(name);  // 获取好感度增益
    increaseAffection(affectionIncrease);  // 更新 NPC 的亲密度

    // 在 NPC 头顶显示开心表情 2 秒
    Sprite* happyFace = Sprite::create("../Resources/Characters/NPC/happy.png");

    // 获取 NPC 的当前位置
    Vec2 npcPosition = getPosition();

    // 设置开心表情的位置，偏移位置稍微往上
    happyFace->setPosition(npcPosition.x, npcPosition.y + sprite->getContentSize().height/2);  // 头顶位置

    // 将开心表情添加为 NPC 的子节点，这样它的坐标就会随 NPC 移动
    this->addChild(happyFace, 1);

    // 延迟 2 秒后移除开心表情并弹出 ChatLayer
    auto delay = DelayTime::create(2.0f);
    auto showChatLayer = CallFunc::create([this, affectionIncrease, gift]() {
        // 创建并显示 ChatLayer
        ChatLayer* chatLayer = ChatLayer::create("Thank you for the gift:" + gift->name + "  :)"); // 创建对话框


        // 设置 ChatLayer 的位置，相对于 NPC 的位置
        Vec2 npcPosition = getPosition();  // 获取 NPC 的位置
        chatLayer->setPosition(npcPosition.x + 250, npcPosition.y + 60);  // 让对话框出现在 NPC 头顶

        // 在底部添加亲密度信息
        std::string affectionInfo = "Affection added: " + std::to_string(affectionIncrease) +
            ", Current Affection: " + std::to_string(getAffection());
        chatLayer->addAffectionText(affectionInfo);  // 显示亲密度信息

        // 将 ChatLayer 作为 NPC 的子节点
        this->addChild(chatLayer, 1);  // 添加 ChatLayer 为 NPC 的子节点，并设置层级优先级为 1000
        });

    // 创建一个移除开心表情并显示 ChatLayer 的动作序列
    auto removeAction = RemoveSelf::create();
    happyFace->runAction(Sequence::create(delay, removeAction, showChatLayer, nullptr));
}


// 开始行走动画
void NPC::startWalkingAnimation() {
    if (sprite && walkAnimation) {
        sprite->runAction(cocos2d::RepeatForever::create(walkAnimation));
    }
}

std::string NPC::getName() {
    return name;
}

// 获取当前好感度
int NPC::getAffection() const {
    return affection;  // 返回当前好感度
}

// 键盘按下事件处理
void NPC::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    // 检查按下的是否是 T 键
    if (keyCode == EventKeyboard::KeyCode::KEY_K) {
        // 触发 NPC 显示任务列表
        showDialog();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_G) {
        // 触发 NPC 送礼物
        showTaskList();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // 显示婚姻选择
        showMarriageChoices();
    }
}
