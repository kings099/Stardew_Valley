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
    : _name(name), _affection(0), _isMarried(false), _isMoving(false),_isProcessing(false) {
    setPosition(position);                    // 初始化 NPC 位置
    initializeSprite(idleImage, walkFrames);  // 初始化精灵和动画

    // 注册键盘监听事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(NPC::onKeyPressed, this);  // 绑定按键事件
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 初始化精灵和动画
void NPC::initializeSprite(const std::string& idleImage, const std::vector<std::string>& walkFrames) {
    _sprite = cocos2d::Sprite::create(idleImage);
    _sprite->setPosition(getPosition());
    addChild(_sprite);

    // 设置精灵缩放比例,让精灵的大小固定
    _sprite->setScaleX(NPC_WIDTH / _sprite->getContentSize().width);  
    _sprite->setScaleY(NPC_HEIGHT / _sprite->getContentSize().height); 

    
    // 设置行走动画
    cocos2d::Vector<cocos2d::SpriteFrame*> walkSpriteFrames;
    for (const auto& frame : walkFrames) {
        walkSpriteFrames.pushBack(cocos2d::SpriteFrame::create(frame, cocos2d::Rect(0, 0, 64, 64)));
    }
    cocos2d::Animation* walkAnim = cocos2d::Animation::createWithSpriteFrames(walkSpriteFrames, 0.2f);
    _walkAnimation = cocos2d::Animate::create(walkAnim);
}

//展示NPC对话框，好感程度不同触发不同的内容
void NPC::showDialog() {
    int dialogueIndex = _affection / AFFECTION_INDEX;
    dialogueIndex = std::min(dialogueIndex, (int)_dialogues.size() - 1);
    std::string username = CharacterInfo::getInstance()->getUsername();  // 获取用户名
    std::string dialogue = _dialogues[dialogueIndex] + "," + username;
    showDialogue(dialogue);
}

//根据传入的字符串展示对话框
void NPC::showDialogue(const std::string& dialogueText) {
    // 创建 ChatLayer 实例并传入对话内容
    ChatLayer* chatLayer = ChatLayer::create(dialogueText);

    // 获取 NPC 当前的位置
    Vec2 npcPosition = getPosition();

    // 设置对话框位置相对于 NPC
    chatLayer->setPosition(npcPosition.x + DIALOG_X_OFFSET, npcPosition.y + DIALOG_Y_OFFSET);

    // 将 ChatLayer 添加为 NPC 的子节点
    this->addChild(chatLayer); 
}

// 增加好感度
void NPC::increaseAffection(int value) {
   _affection = std::min(MAX_AFFECTION, _affection + value);
}

// 显示询问用户是否求婚的UI
void NPC::showMarriageChoices() {
    if (_affection >= MARRIAGE_AFFECTION && !_isMarried) {
        // 获取 NPC 当前的位置
        Vec2 npcPosition = getPosition();

        // 创建一个自定义的对话框
        auto dialog = ui::Layout::create();
        dialog->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        dialog->setBackGroundColor(Color3B(0, 0, 0));  // 设置背景为黑色
        dialog->setBackGroundColorOpacity(128);  // 设置透明度为128（半透明）

        // 设置对话框大小
        float dialogWidth = DIALOG_WIDTH;
        float dialogHeight = DIALOG_HEIGHT;
        dialog->setContentSize(Size(dialogWidth, dialogHeight));  // 设置对话框的内容大小

        // 设置对话框的位置
        dialog->setPosition(Vec2(DIALOG_X_OFFSET/2, DIALOG_Y_OFFSET/2));
        this->addChild(dialog);  

        // 创建询问文本信息
        auto text = Label::createWithSystemFont("Would you like to propose?\nAffection is sufficient now!", FONT_TYPE, FONT_SIZE);
        text->setPosition(Vec2(dialog->getContentSize().width / 2, dialog->getContentSize().height / 2));
        dialog->addChild(text);

        // "Yes" 按钮，玩家同意结婚
        auto yesButton = ui::Button::create();
        yesButton->setTitleText("Yes");
        yesButton->setTitleFontSize(FONT_SIZE);  
        yesButton->setPosition(Vec2(dialog->getContentSize().width * 0.3f, -dialog->getContentSize().height * 0.3f));
        yesButton->addClickEventListener([this, dialog](Ref* sender) {
            marryPlayer(); 
            dialog->removeFromParent();  // 移除对话框
            _isProcessing = false;
            });
        dialog->addChild(yesButton);

        // "No" 按钮，玩家拒绝结婚，字体大小设为24
        auto noButton = ui::Button::create();
        noButton->setTitleText("No");
        noButton->setTitleFontSize(FONT_SIZE);  
        noButton->setPosition(Vec2(dialog->getContentSize().width * 0.7f, -dialog->getContentSize().height * 0.3f));
        noButton->addClickEventListener([this, dialog](Ref* sender) {
            dialog->removeFromParent();  // 移除对话框
            _isProcessing = false;
            });
        dialog->addChild(noButton);
    }
    else {
        std::string dialogue = "You can not propose!";
        showDialogue(dialogue);
        _isProcessing = false;
    }
}

//处理求婚逻辑，包括播放动画，修改关系，消息提示用户已经结婚
void NPC::marryPlayer() {
    // 播放求婚动画，并在动画完成后显示结婚消息
    playMarriageAnimation();

    // 设置婚姻状态
    _isMarried = true;

    // 创建结婚消息的回调函数
    auto showWeddingMessage = [this]() {
        // 显示结婚消息
        std::string weddingMessage = "You and " + _name + " are now married!";
        ChatLayer* chatLayer = ChatLayer::create(weddingMessage);
        // 设置对话框位置相对于 NPC

        Vec2 npcPosition = getPosition();  // 获取 NPC 当前的位置
        chatLayer->setPosition(npcPosition.x + DIALOG_X_OFFSET, npcPosition.y + DIALOG_Y_OFFSET);  // 将对话框位置设置为 NPC 的位置

        this->addChild(chatLayer);
        };

    // 创建一个延时动作，在动画结束后调用 showWeddingMessage 函数
    auto delayAction = Sequence::create(DelayTime::create(3.0f), CallFunc::create(showWeddingMessage), nullptr);

    // 在结婚动画结束时执行结婚消息显示
    this->runAction(delayAction);
}

//播放求婚动画
void NPC::playMarriageAnimation() {
    // 创建一个闪烁的心形精灵
    auto heartSprite = Sprite::create("../Resources/Characters/NPC/happy.png");
    // 设置开心表情的位置，偏移位置稍微往上
    Vec2 npcPosition = getPosition();
    heartSprite->setPosition(npcPosition.x, npcPosition.y + _sprite->getContentSize().height / 2);  // 头顶位置

    // 将开心表情添加为 NPC 的子节点，这样它的坐标就会随 NPC 移动
    this->addChild(heartSprite);
    heartSprite->setOpacity(0);  // 初始透明度为0，不可见

    // 放大效果
    auto scaleUp = ScaleTo::create(3.0f, 1.5f);  // 放大效果
    auto scaleDown = ScaleTo::create(0.3f, 1.0f);  // 恢复到正常大小

    // 闪烁效果，快速地透明化和出现
    auto fadeIn = FadeIn::create(0.2f);  // 渐显效果
    auto fadeOut = FadeOut::create(0.2f);  // 渐隐效果

    // 颜色变化效果
    auto colorChange = TintTo::create(0.2f, 255, 0, 0);      // 直接设置为红色
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

//展示任务列表并处理任务逻辑
void NPC::showTaskList() {
    std::string taskInfo = "Available Tasks:\n";
    // 生成两个任务按钮
    if (_tasks.size() >= 2) {
        // 获取任务1
        Task* task1 = _tasks[0];
        // 获取任务2
        Task* task2 = _tasks[1];

        // 创建任务1按钮
        auto taskButton1 = ui::Button::create();
        taskButton1->setTitleText(task1->getDescription() + (task1->checkCompletion() ? " (Completed)" : " (In Progress)"));
        taskButton1->setPosition(Vec2(250,200));
        taskButton1->setTitleFontSize(24);

        // 创建任务2按钮
        auto taskButton2 = ui::Button::create();
        taskButton2->setTitleText(task2->getDescription() + (task2->checkCompletion() ? " (Completed)" : " (In Progress)"));
        taskButton2->setPosition(Vec2(250, 230));
        taskButton2->setTitleFontSize(24); 

        // 创建任务1按钮点击事件
        taskButton1->addClickEventListener([this, task1,taskButton1, taskButton2](Ref* sender) {
            this->removeChild(taskButton1);
            this->removeChild(taskButton2);
            if (!task1->checkCompletion()) {
                // 任务1的逻辑：检查玩家是否有Ring
                Character* _character = Character::getInstance(); // 获取 Character 的单例对象
                int targetObjectIndex = _character->findObjectByObjectList(task1->getRequiredItemName()); // 判断数量
                if (targetObjectIndex != -1 && _character->findObjectAtPosition(targetObjectIndex).count > task1->getRequiredItemCount()) {
                    GiftItem* gift = GiftItemManager::getInstance()->getGiftByName(task1->getRequiredItemName());
                    _character->deleteObject(targetObjectIndex, task1->getRequiredItemCount());
                    this->giftItem(gift);
                    this->increaseAffection(task1->getAffectionReward());
                    task1->setCompletion(true);
                }
                else {
                    std::string dialogue = "Oh no,task can not be finished";
                    showDialogue(dialogue);
                }
            }
            else {
                std::string dialogue = "Already be finished!";
                showDialogue(dialogue);
            }
            _isProcessing = false;
            });
       this->addChild(taskButton1);

       
       // 创建任务2按钮点击事件
        taskButton2->addClickEventListener([this, task2, taskButton1, taskButton2](Ref* sender) {
            this->removeChild(taskButton1);
            this->removeChild(taskButton2);
            if (!task2->checkCompletion()) {
                // 任务2的逻辑：检查玩家是否有5个木材
                Character* _character = Character::getInstance(); // 获取 Character 的单例对象
                int targetObjectIndex = _character->findObjectByObjectList(task2->getRequiredItemName()); // 判断数量
                if (targetObjectIndex != -1 && _character->findObjectAtPosition(targetObjectIndex).count > task2->getRequiredItemCount()) {
                    // 数量大于5，删除5个木材
                    _character->deleteObject(targetObjectIndex, task2->getRequiredItemCount());
                    //增加任务对应的好感度
                    this->increaseAffection(task2->getAffectionReward());
                    std::string dialogue= "Task be finished!\n";
                    std::string affectionInfo = "Affection added: " + std::to_string(task2->getAffectionReward()) +
                        ", Current Affection: " + std::to_string(getAffection());
                    showDialogue(dialogue+affectionInfo);
                    task2->setCompletion(true);
                }
                else {
                    std::string dialogue = "Oh no,materials isn't enough";
                    showDialogue(dialogue);
                }
            }
            else {
                std::string dialogue = "Already be finished!";
                showDialogue(dialogue);
            }
            _isProcessing = false;
            });
        this->addChild(taskButton2);
    }

 

}

//增加任务
void NPC::addTask(Task* task) {
    _tasks.push_back(task);
}

// 判断玩家是否接近
bool NPC::isPlayerNear(cocos2d::Vec2 playerPosition) {
    return playerPosition.distance(getPosition()) < INTERACTION_DISTANCE;
}

//执行送礼逻辑
void NPC::giftItem(GiftItem* gift) {
    int affectionIncrease = gift->getAffectionForNPC(_name);  // 获取好感度增益
    increaseAffection(affectionIncrease);  // 更新 NPC 的亲密度

    // 在 NPC 头顶显示开心表情 2 秒
    Sprite* happyFace = Sprite::create("../Resources/Characters/NPC/happy.png");

    // 获取 NPC 的当前位置
    Vec2 npcPosition = getPosition();

    // 设置开心表情的位置，偏移位置稍微往上
    happyFace->setPosition(npcPosition.x, npcPosition.y + _sprite->getContentSize().height/2);  // 头顶位置

    // 将开心表情添加为 NPC 的子节点，这样它的坐标就会随 NPC 移动
    this->addChild(happyFace, 1);

    // 延迟 2 秒后移除开心表情并弹出 ChatLayer
    auto delay = DelayTime::create(2.0f);
    auto showChatLayer = CallFunc::create([this, affectionIncrease, gift]() {
        // 创建并显示 ChatLayer
        ChatLayer* chatLayer = ChatLayer::create("Thank you for the gift:" + gift->_name + "  :)"); 

        // 设置 ChatLayer 的位置，相对于 NPC 的位置
        Vec2 npcPosition = getPosition(); 
        chatLayer->setPosition(npcPosition.x + DIALOG_X_OFFSET, npcPosition.y + DIALOG_Y_OFFSET);  

        // 在底部添加亲密度信息
        std::string affectionInfo = "Affection added: " + std::to_string(affectionIncrease) +
            ", Current Affection: " + std::to_string(getAffection());
        chatLayer->addAffectionText(affectionInfo); 

        // 将 ChatLayer 作为 NPC 的子节点
        this->addChild(chatLayer); 
        });

    // 创建一个移除开心表情并显示 ChatLayer 的动作序列
    auto removeAction = RemoveSelf::create();
    happyFace->runAction(Sequence::create(delay, removeAction, showChatLayer, nullptr));
}

// 开始行走动画
void NPC::startWalkingAnimation() {
    if (_sprite && _walkAnimation) {
        _sprite->runAction(cocos2d::RepeatForever::create(_walkAnimation));
    }
}

//获得NPC姓名
std::string NPC::getName() {
    return _name;
}

// 获取当前好感度
int NPC::getAffection() const {
    return _affection;  // 返回当前好感度
}

// 键盘按下事件处理
void NPC::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    // 如果正在处理任务，直接返回

    if (_isProcessing) {
        return;
    }

    // 标记为正在处理任务
    _isProcessing = true;
 
    // 检查按下的是否是 K 键
    if (keyCode == EventKeyboard::KeyCode::KEY_K) {
        // 触发 NPC 显示对话框
        showDialog();
        _isProcessing = false;
    }
    // 检查按下的是否是 G 键
    else if (keyCode == EventKeyboard::KeyCode::KEY_G) {
        // 触发 NPC 显示任务列表
        showTaskList();
      
    }
    // 检查按下的是否是 M 键
    else if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // 显示婚姻选择
        showMarriageChoices();
   
    }
}

//设置任务处理状态
void NPC::setIsProcessing(bool isProcessing) {
    _isProcessing = isProcessing;
}