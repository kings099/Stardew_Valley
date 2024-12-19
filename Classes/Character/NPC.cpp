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

    // 设置行走动画
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 64, 64)));
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    walkAnimation = cocos2d::Animate::create(walkAnim);
}

// 显示对话框
void NPC::showDialog() {
    int dialogueIndex = affection / 25;
    dialogueIndex = std::min(dialogueIndex, (int)dialogues.size() - 1);
    std::string username = CharacterInfo::getInstance()->getUsername();  // 获取用户名
    std::string dialogue = dialogues[dialogueIndex]+","+username;

    // 创建并显示 ChatLayer
    ChatLayer* chatLayer = ChatLayer::create(dialogue);  // 创建 ChatLayer 实例并传入对话内容
    cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (runningScene != nullptr) {
        runningScene->addChild(chatLayer, 10);  // 将 ChatLayer 添加到当前场景
    }
}

// 增加好感度
void NPC::increaseAffection(int value, bool isRomantic) {
    affection = std::min(100, affection + value);
}

// 显示询问用户是否求婚的UI
void NPC::showMarriageChoices() {
    if (affection >= 0 && !isMarried) {
        // 获取当前场景
        auto runningScene = cocos2d::Director::getInstance()->getRunningScene();
        if (!runningScene) {
            return;
        }

        const auto visibleSize = Director::getInstance()->getVisibleSize();
        const auto origin = Director::getInstance()->getVisibleOrigin();

      

        // 创建一个自定义的对话框
        auto dialog = ui::Layout::create();
        dialog->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        dialog->setBackGroundColor(Color3B(0, 0, 0));
        dialog->setOpacity(200);
        dialog->setContentSize(Size(visibleSize.width * DIALOG_WIDTH_RATIO, visibleSize.height * DIALOG_HEIGHT_RATIO));
        dialog->setPosition(Vec2(origin.x + visibleSize.width * 0.25f, origin.y + visibleSize.height * 0.375f));
        runningScene->addChild(dialog, 10);

        // 创建询问文本信息，字体大小设为30
        auto text = Label::createWithSystemFont("Would you like to propose?", "Arial", 30);
        text->setPosition(Vec2(dialog->getContentSize().width / 2, dialog->getContentSize().height - dialog->getContentSize().height * 0.3f));
        dialog->addChild(text);

        // 创建额外的文本信息，字体大小设为30
        auto text1 = Label::createWithSystemFont("Affection is sufficient now!", "Arial", 30);
        text1->setPosition(Vec2(dialog->getContentSize().width / 2, dialog->getContentSize().height - dialog->getContentSize().height * 0.5f));
        dialog->addChild(text1);

        // "Yes" 按钮，玩家同意结婚，字体大小设为30
        auto yesButton = ui::Button::create();
        yesButton->setTitleText("Yes");
        yesButton->setTitleFontSize(30);  // 设置按钮字体大小为30
        yesButton->setPosition(Vec2(dialog->getContentSize().width / 2 - dialog->getContentSize().width * BUTTON_OFFSET_RATIO, dialog->getContentSize().height * BUTTON_SIZE_RATIO));
        yesButton->addClickEventListener([this, dialog](Ref* sender) {
            marryPlayer();  // 玩家同意结婚
            dialog->removeFromParent();  // 移除对话框
            });
        dialog->addChild(yesButton);

        // "No" 按钮，玩家拒绝结婚，字体大小设为30
        auto noButton = ui::Button::create();
        noButton->setTitleText("No");
        noButton->setTitleFontSize(30);  // 设置按钮字体大小为30
        noButton->setPosition(Vec2(dialog->getContentSize().width / 2 + dialog->getContentSize().width * BUTTON_OFFSET_RATIO, dialog->getContentSize().height * BUTTON_SIZE_RATIO));
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
        cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
        if (runningScene != nullptr) {
            runningScene->addChild(chatLayer, 10);
        }
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
    heartSprite->setPosition(npcPosition.x, npcPosition.y + (sprite->getContentSize().height / 2) * 1.2);  // 头顶位置

    // 将开心表情添加为 NPC 的子节点，这样它的坐标就会随 NPC 移动
    this->addChild(heartSprite, 1);
    heartSprite->setOpacity(0);  // 初始透明度为0，不可见

    // 放大效果
    auto scaleUp = ScaleTo::create(0.3f, 1.5f);  // 放大效果
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
        taskButton1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 40));
        taskButton1->setTitleFontSize(30); // 设置字体大小
        taskButton1->addClickEventListener([this, task1, runningScene](Ref* sender) {
            if (!task1->checkCompletion()) {
                // 如果任务没有完成，执行任务
                // 执行任务1的逻辑
            }
            else {

            }
            });
        runningScene->addChild(taskButton1, 10);

        // 创建任务2按钮
        auto taskButton2 = ui::Button::create();
        taskButton2->setTitleText(task2Info);
        taskButton2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));
        taskButton2->setTitleFontSize(30); // 设置字体大小
        taskButton2->addClickEventListener([this, task2, runningScene](Ref* sender) {
            if (!task2->checkCompletion()) {
                // 如果任务没有完成，执行任务
                // 执行任务2的逻辑
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


// 送礼物
void NPC::giftItem(GiftItem* gift) {
    int affectionIncrease = gift->getAffectionForNPC(name);  // 获取好感度增益
    increaseAffection(affectionIncrease);  // 更新 NPC 的亲密度

    // 获取当前场景
    cocos2d::Scene* runningScene = cocos2d::Director::getInstance()->getRunningScene();
    if (!runningScene) {
        return;
    }

    // 在 NPC 头顶显示开心表情 2 秒
    Sprite* happyFace = Sprite::create("../Resources/Characters/NPC/happy.png");

    
   // 获取 NPC 的当前位置
    Vec2 npcPosition = getPosition();

    // 设置开心表情的位置，偏移位置稍微往上
    happyFace->setPosition(npcPosition.x, npcPosition.y + (sprite->getContentSize().height / 2)*1.2 );  // 头顶位置


    // 将开心表情添加为 NPC 的子节点，这样它的坐标就会随 NPC 移动
    this->addChild(happyFace, 1); 

    // 延迟 2 秒后移除开心表情并弹出 ChatLayer
    auto delay = DelayTime::create(2.0f);
    auto showChatLayer = CallFunc::create([this, affectionIncrease, runningScene, gift]() {
        // 创建并显示 ChatLayer
        ChatLayer* chatLayer = ChatLayer::create("Thank you for the gift:" + gift->name + "  :)"); // 创建对话框

        // 在底部添加亲密度信息
        std::string affectionInfo = "Affection added: " + std::to_string(affectionIncrease) +
            ", Current Affection: " + std::to_string(getAffection());
        chatLayer->addAffectionText(affectionInfo);  // 显示亲密度信息

        // 将 ChatLayer 添加到当前场景
        runningScene->addChild(chatLayer, 10);
        });

    // 创建一个移除开心表情并显示 ChatLayer的动作序列
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
    if (keyCode == EventKeyboard::KeyCode::KEY_T) {
        // 触发 NPC 显示任务列表
        showTaskList();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_G) {
        // 触发 NPC 送礼物
        if (auto gift = GiftItemManager::getInstance()->getGiftByName("Rose")) { // 例如送“Rose”花
            giftItem(gift);
        }
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // 显示婚姻选择
        showMarriageChoices();
    }
}
