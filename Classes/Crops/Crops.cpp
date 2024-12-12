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

void Crop::playWeedingAnimation() {
    CCLOG("Playing weeding animation...");
    if (sprite == nullptr) {
        CCLOG("Error: Sprite is null, cannot play animation.");
        return;
    }
    // 缩小动画效果（调整缩放比例）
    sprite->setScale(0.3f); // 将动画缩小到原来的 50%
    // 定义除草动画的帧序列
    Vector<SpriteFrame*> frames;
    for (int i = 1; i < 6; ++i) { // 假设动画有 8 帧
        std::string frameName = StringUtils::format("../Resources/Animations/weeding/weeding_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 64)); // 假设每帧为 64x64
        if (frame == nullptr) {
            CCLOG("Error: Failed to load frame: %s", frameName.c_str());
            continue;
        }
        frames.pushBack(frame);
    }

    if (frames.empty()) {
        CCLOG("Error: No frames loaded for weeding animation");
        return;
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.3f); // 每帧持续时间为 0.1 秒
    auto animate = Animate::create(animation);

    // 播放动画并移除节点（假设除草动画完成后农作物被移除）
    auto removeSelf = CallFunc::create([this]() {
        this->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    sprite->runAction(sequence);
}
