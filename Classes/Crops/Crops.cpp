/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: 农作物类，实现农作物的生长浇水等动画
 * Author:        胡宝怡
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "Crops.h"

USING_NS_CC;

// 定义静态资源映射表
std::unordered_map<std::string, std::vector<std::string>> Crop::resourceMap;

void Crop::initializeResourceMap() {
    // 如果资源表已经初始化，则跳过
    if (!resourceMap.empty()) return;

    // 为每种农作物类型添加对应的图片资源路径
    //小树
    resourceMap["little_tree"] = {
        "../Resources/Crops/little_tree_0.png",
        "../Resources/Crops/little_tree_1.png",
        "../Resources/Crops/little_tree_2.png",
        "../Resources/Crops/little_tree_3.png"
    };
    //苔雨树
    resourceMap["tree"] = {
       "../Resources/Crops/tree1_0.png",
       "../Resources/Crops/tree1_1.png",
       "../Resources/Crops/tree1_2.png",
       "../Resources/Crops/tree1_3.png",
       "../Resources/Crops/tree1_4.png"
    };

    //普通草
    resourceMap["grass"] = {
        "../Resources/Crops/grass.png"
    };

    for (const auto& entry : resourceMap) {
        CCLOG("Type: %s", entry.first.c_str());
        for (const auto& texture : entry.second) {
            CCLOG(" - Texture: %s", texture.c_str());
        }
    }
  /*  resourceMap["wheat"] = {
        "wheat_stage_0.png",
        "wheat_stage_1.png",
        "wheat_stage_2.png",
        "wheat_stage_3.png"
    };*/
}

Crop* Crop::create(const std::string& type, int maxGrowthStage) {
    CCLOG("Creating Crop instance...");
    Crop* ret = new Crop();
    if (ret && ret->init(type, maxGrowthStage)) {
        ret->autorelease();
        CCLOG("Crop instance created successfully");
        return ret;
    }
    CC_SAFE_DELETE(ret);
    CCLOG("Crop instance creation failed");
    return nullptr;
}

bool Crop::init(const std::string& type, int maxGrowthStage) {
    CCLOG("Initializing Crop...");
    if (!Node::init()) {
        CCLOG("Error: Node::init failed");
        return false;
    }

    // 初始化资源表（仅首次调用时会执行）
    initializeResourceMap();

    this->type = type;
    this->growthStage = 0;
    this->maxGrowthStage = maxGrowthStage;
    this->growthTimer = 0.0f;
    this->isWatered = false;

    // 初始化农作物的精灵
    sprite = Sprite::create(resourceMap[type][0]);
    if (sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }
    sprite->setScale(2.0f);

    this->addChild(sprite);
    CCLOG("Crop initialized successfully");
    return true;
}

void Crop::updateGrowth(float deltaTime) {
    //if (isWatered) {  // 检查是否已浇水
        growthTimer += deltaTime;

        // 检查是否达到下一个生长阶段
        if (growthTimer >= 5.0f) { // 每阶段需要10秒
            growthTimer = 0.0f;
            growthStage = std::min(growthStage + 1, maxGrowthStage);

            // 从静态资源映射表中获取对应的贴图
            if (resourceMap.find(type) != resourceMap.end()) {
                const auto& textures = resourceMap[type];
                if (growthStage >= 0 && growthStage < textures.size()) {
                    sprite->setTexture(textures[growthStage]);
                }
                else {
                    CCLOG("Warning: Growth stage %d out of range for type %s", growthStage, type.c_str());
                }
            }
            else {
                CCLOG("Error: No resources found for crop type: %s", type.c_str());
            }
        }
    /*}*/

    // 每天重置浇水状态（可以根据游戏的时间系统实现）
    /*isWatered = false;*/
}


void Crop::waterCrop() {
    isWatered = true;

    //// 显示浇水动画
    //auto waterEffect = Sprite::create("water_effect.png");
    //waterEffect->setPosition(sprite->getPosition());
    //this->addChild(waterEffect);

    //auto fadeOut = FadeOut::create(1.0f);
    //auto removeEffect = CallFunc::create([waterEffect]() {
    //    waterEffect->removeFromParent();
    //    });

    //auto sequence = Sequence::create(fadeOut, removeEffect, nullptr);
    //waterEffect->runAction(sequence);
}

bool Crop::isReadyToHarvest() const {
    return growthStage >= maxGrowthStage;
}

void Crop::setGrowthStage(int stage) {
    growthStage = std::min(stage, maxGrowthStage); // 确保阶段不超过最大值

    // 检查资源映射表中是否有当前农作物类型的资源
    if (resourceMap.find(type) != resourceMap.end()) {
        const auto& textures = resourceMap[type];

        // 检查当前阶段是否在资源范围内
        if (growthStage >= 0 && growthStage < textures.size()) {
            sprite->setTexture(textures[growthStage]); // 设置贴图为对应阶段的资源
        }
        else {
            CCLOG("Warning: Growth stage %d out of range for type %s", growthStage, type.c_str());
        }
    }
    else {
        CCLOG("Error: No resources found for crop type: %s", type.c_str());
    }
}

void Crop::playWeedingAnimation(const Vec2& position) {
    CCLOG("Playing weeding animation at position (%f, %f)...", position.x, position.y);

    // 创建一个新的精灵来显示动画
    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for weeding animation.");
        return;
    }

    // 设置精灵的初始位置
    tempSprite->setPosition(position);

    // 添加到当前节点或场景
    this->addChild(tempSprite);

    // 定义除草动画的帧序列
    Vector<SpriteFrame*> frames;
    for (int i = 1; i < 6; ++i) { // 假设动画有 5 帧
        std::string frameName = StringUtils::format("../Resources/Animations/weeding/grass_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 64)); // 假设每帧为 64x64
        if (frame == nullptr) {
            CCLOG("Error: Failed to load frame: %s", frameName.c_str());
            continue;
        }
        frames.pushBack(frame);
    }

    if (frames.empty()) {
        CCLOG("Error: No frames loaded for weeding animation");
        tempSprite->removeFromParent(); // 确保在失败时移除节点
        return;
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.2f); // 每帧持续时间为 0.2 秒
    auto animate = Animate::create(animation);

    // 播放动画并移除精灵
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}


void Crop::playStoneBreakingAnimationAt(const Vec2& position) {
    CCLOG("Playing stone breaking animation at position (%f, %f)...", position.x, position.y);

    // 创建一个新的临时精灵来显示动画
    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for stone breaking animation.");
        return;
    }

    // 设置精灵的初始位置
    tempSprite->setPosition(position);

    // 添加到当前节点或场景
    this->addChild(tempSprite);

    // 定义碎石动画的帧序列
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; ++i) { // 假设动画有 5 帧
        std::string frameName = StringUtils::format("../Resources/Animations/stone_break/stone_break_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 64)); // 假设每帧为 64x64
        if (frame == nullptr) {
            CCLOG("Error: Failed to load frame: %s", frameName.c_str());
            continue;
        }
        frames.pushBack(frame);
    }

    if (frames.empty()) {
        CCLOG("Error: No frames loaded for stone breaking animation");
        tempSprite->removeFromParent(); // 清理未成功加载动画的节点
        return;
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.2f); // 每帧持续时间为 0.2 秒
    auto animate = Animate::create(animation);

    // 动画完成后移除精灵
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}

//void Crop::playWeedingAnimation(TMXTiledMap* _tile_map) {
//    CCLOG("Playing weeding animation...");
//
//    // 如果已有 sprite，不再使用，直接创建新精灵
//    auto animationSprite = Sprite::create();
//    if (animationSprite == nullptr) {
//        CCLOG("Error: Failed to create sprite for animation.");
//        return;
//    }
//
//    // 将新精灵添加到场景或父节点中
//    _tile_map->addChild(animationSprite);
//
//    // 缩小动画效果（调整缩放比例）
//    animationSprite->setScale(0.3f);
//
//    // 定义一组图片和对应的位置
//    struct FrameData {
//        std::string imagePath;
//        Vec2 position;
//    };
//    std::vector<FrameData> frameData = {
//        {"../Resources/Animations/weeding/grass_animation.png", Vec2(200, 200)},
//        {"../Resources/Animations/weeding/grass_animation.png", Vec2(200, 195)},
//        {"../Resources/Animations/weeding/grass_animation.png", Vec2(200, 190)},
//        {"../Resources/Animations/weeding/weeding_4.png", Vec2(200, 200)}
//       
//    };
//
//    // 动画持续时间
//    const float frameDuration = 0.3f;
//
//    // 创建动作序列
//    Vector<FiniteTimeAction*> actions;
//    for (const auto& frame : frameData) {
//        auto changeImage = CallFunc::create([=]() {
//            animationSprite->setTexture(frame.imagePath); // 更换图片
//            animationSprite->setPosition(frame.position); // 更新位置
//            });
//        auto delay = DelayTime::create(frameDuration); // 延迟一段时间
//        actions.pushBack(changeImage);
//        actions.pushBack(delay);
//    }
//
//    // 动画完成后移除节点
//    auto removeSelf = CallFunc::create([animationSprite]() {
//        animationSprite->removeFromParent();
//        });
//
//    // 将所有动作依次执行
//    actions.pushBack(removeSelf);
//    auto sequence = Sequence::create(actions);
//
//    // 执行动作
//    animationSprite->runAction(sequence);
//}
