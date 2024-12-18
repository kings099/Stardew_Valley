/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: 农作物类，实现农作物的各种基本操作
 * Author:        胡宝怡
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "Crops.h"


USING_NS_CC;
// 初始化静态变量
Season Crops::currentSeason = Season::Winter;
int Crops::playerLevel = 1; // 初始人物等级为1

// 定义静态资源映射表
std::unordered_map<std::string, std::vector<std::string>> Crops::resourceMap;

void Crops::initializeResourceMap() {
    // 如果资源表已经初始化，则跳过
    if (!resourceMap.empty()) return;

    // 为每种农作物类型添加对应的图片资源路径
    //花椰菜
    resourceMap["cauliflower"] = {
        "../Resources/Crops/Cauliflower/cauliflower_0.png",
        "../Resources/Crops/Cauliflower/cauliflower_1.png",
        "../Resources/Crops/Cauliflower/cauliflower_2.png",
        "../Resources/Crops/Cauliflower/cauliflower_3.png",
         "../Resources/Crops/Cauliflower/cauliflower_4.png"
    };

    //甘蓝菜
    resourceMap["kale"] = {
       "../Resources/Crops/Kale/kale_0.png",
       "../Resources/Crops/Kale/kale_1.png",
       "../Resources/Crops/Kale/kale_2.png",
       "../Resources/Crops/Kale/kale_3.png",
       "../Resources/Crops/Kale/kale_4.png"
    };

    //南瓜
     resourceMap["pumpkin"] = {
    "../Resources/Crops/Pumpkin/pumpkin_0.png",
     "../Resources/Crops/Pumpkin/pumpkin_1.png",
     "../Resources/Crops/Pumpkin/pumpkin_2.png",
     "../Resources/Crops/Pumpkin/pumpkin_3.png",
     "../Resources/Crops/Pumpkin/pumpkin_4.png",
     "../Resources/Crops/Pumpkin/pumpkin_5.png"
    };
    //橡树
     resourceMap["oak"] = {
    "../Resources/Crops/Oak/oak_0.png",
     "../Resources/Crops/Oak/oak_1.png",
     "../Resources/Crops/Oak/oak_2.png",
     "../Resources/Crops/Oak/oak_3.png"
     };

    //枫树
     resourceMap["maple"] = {
    "../Resources/Crops/Maple/maple_0.png",
     "../Resources/Crops/Maple/maple_1.png",
     "../Resources/Crops/Maple/maple_2.png",
     "../Resources/Crops/Maple/maple_3.png"
     };

    //松树
     resourceMap["pine"] = {
    "../Resources/Crops/Pine/pine_0.png",
     "../Resources/Crops/Pine/pine_1.png",
     "../Resources/Crops/Pine/pine_2.png",
     "../Resources/Crops/Pine/pine_3.png"
     };

    //普通草
    resourceMap["grass"] = {
        "../Resources/Crops/grass.png"
    };

    //石头
    resourceMap["stone"] = {
        "../Resources/Crops/stone.png"
    };
    //草2
    resourceMap["grass_2"] = {
        "../Resources/Crops/grass_2.png"
    };

    //枯萎
    resourceMap["wilt"] = {
       "../Resources/Crops/wilt/wilt_0.png"
    };
    for (const auto& entry : resourceMap) {
        CCLOG("Type: %s", entry.first.c_str());
        for (const auto& texture : entry.second) {
            CCLOG(" - Texture: %s", texture.c_str());
        }
    }
    
}

// 农作物的生长周期表（不同季节不同周期）
std::unordered_map<std::string, std::unordered_map<Season, float>> Crops::growthCycles = {
    {"cauliflower", {{Season::Spring, 50.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter,72.0f}}},
    {"kale", {{Season::Spring, 30.0f}, {Season::Summer, 30.0f}, {Season::Fall, 40.0f}, {Season::Winter, 50.0f}}},
    {"pumpkin", {{Season::Spring, 2.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter, 72.0f}}},
    {"oak", {{Season::Spring,2.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"maple", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"pine", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}}
  
};

// 树成熟阶段图片（不同季节的贴图）
std::unordered_map<std::string, std::unordered_map<Season, std::string>> Crops::matureTextures = {
    {"oak", {{Season::Spring, "../Resources/Crops/Oak/oak_spring.png"},
                     {Season::Summer, "../Resources/Crops/Oak/oak_summer.png"},
                     {Season::Fall, "../Resources/Crops/Oak/oak_fall.png"},
                     {Season::Winter, "../Resources/Crops/Oak/oak_winter.png"}}
    },
    {"maple", {{Season::Spring, "../Resources/Crops/Maple/maple_spring.png"},
              {Season::Summer, "../Resources/Crops/Maple/maple_summer.png"},
              {Season::Fall, "../Resources/Crops/Maple/maple_fall.png"},
              {Season::Winter, "../Resources/Crops/Maple/maple_winter.png"}}
    },
    {"pine", {{Season::Spring, "../Resources/Crops/Pine/pine_spring.png"},
                 {Season::Summer, "../Resources/Crops/Pine/pine_spring.png"},
                 {Season::Fall, "../Resources/Crops/Pine/pine_fall.png"},
                 {Season::Winter, "../Resources/Crops/Pine/pine_winter.png"}}
    },
    {"cauliflower", {{Season::Spring, "../Resources/Crops/Cauliflower/cauliflower_4.png"},
                 {Season::Summer, "../Resources/Crops/Cauliflower/cauliflower_4.png"},
                 {Season::Fall, "../Resources/Crops/Cauliflower/cauliflower_4.png"},
                 {Season::Winter, "../Resources/Crops/Cauliflower/cauliflower_4.png"}}
    },
    {"kale", {{Season::Spring, "../Resources/Crops/Kale/kale_4.png"},
                 {Season::Summer, "../Resources/Crops/Kale/kale_4.png"},
                 {Season::Fall, "../Resources/Crops/Kale/kale_4.png"},
                 {Season::Winter, "../Resources/Crops/Kale/kale_4.png"}} 
    },

     {"pumpkin", {{Season::Spring, "../Resources/Crops/Pumpkin/pumpkin_5.png"},
           {Season::Summer, "../Resources/Crops/Pumpkin/pumpkin_5.png"},
           {Season::Fall, "../Resources/Crops/Pumpkin/pumpkin_5.png"},
           {Season::Winter, "../Resources/Crops/Pumpkin/pumpkin_5.png"}}
     }
};

void Crops::setPlayerLevel(int level) {
    playerLevel = level;
    CCLOG("Player level set to: %d", playerLevel);
}

bool Crops::canBePlanted() const {
    if (type == "pumpkin" && playerLevel < 3) {
        CCLOG("Error: Player level too low to plant pumpkin! Required level: 3");
        return false;
    }
    return true;
}


Crops* Crops::create(const std::string& type, int maxGrowthStage) {
    CCLOG("Creating Crop instance...");
    Crops* ret = new Crops();
    if (ret && ret->init(type, maxGrowthStage)) {
        ret->autorelease();
        CCLOG("Crop instance created successfully");
        return ret;
    }
    CC_SAFE_DELETE(ret);
    CCLOG("Crop instance creation failed");
    return nullptr;
}

// 施肥函数：改变isFertilized为true，提升生长速度
void Crops::fertilize() {
    isFertilized = true;
}

bool Crops::init(const std::string& type, int maxGrowthStage) {
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
    this->daysWithoutWater = 0;
    this->isFertilized = 0;
    this->hasPests = false;    // 初始无病虫害
    this->pestProbability = 0.05f; // 感染概率 10%
    // 初始化农作物的精灵
    sprite = Sprite::create(resourceMap[type][0]);
    if (sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }
    
    sprite->setScale(1.5f);
    // 设置锚点（例如设置到底部中心点）
    sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    

    this->addChild(sprite);
    CCLOG("Crop initialized successfully");
    return true;
}

void Crops::updateGrowth(float deltaTime) {
    // 获取当前季节的生长周期
    float growthSpeed = 5.0f;
    if (growthCycles.find(type) != growthCycles.end()) {
        if (growthCycles[type].find(currentSeason) != growthCycles[type].end()) {
            growthSpeed = growthCycles[type][currentSeason];
        }
    }

    // 如果施肥，加速生长
    if (isFertilized) {
        growthSpeed *= 0.8f; // 生长周期缩短 20%
    }

    // 累积时间，进入下一个生长阶段
    growthTimer += deltaTime;
    if (growthTimer >= growthSpeed && !hasPests) {
        growthTimer = 0.0f;
        growthStage = std::min(growthStage + 1, maxGrowthStage);

        // 如果达到成熟阶段，加载季节对应的成熟图片
        if (growthStage == maxGrowthStage) {
            if (matureTextures.find(type) != matureTextures.end()) {
                auto seasonTexture = matureTextures[type][currentSeason];
                sprite->setTexture(seasonTexture);
                if (this->type == "maple" || this->type == "oak" || this->type == "pine") {
                    sprite->setScale(1.0f);
                }
                CCLOG("Crop %s matured with texture: %s", type.c_str(), seasonTexture.c_str());
            }
        }
        else {
            // 继续生长阶段的贴图更新
            if (resourceMap.find(type) != resourceMap.end()) {
                const auto& textures = resourceMap[type];
                if (growthStage >= 0 && growthStage < textures.size()) {
                    sprite->setTexture(textures[growthStage]);
                }
            }
        }
    }
    // 检查是否枯萎
    if (!isWatered) {
        daysWithoutWater++;
        if (daysWithoutWater >= 3) {
            if (resourceMap.find("wilt") != resourceMap.end()) {
                const auto& textures = resourceMap["wilt"];
                if (!textures.empty()) {
                    sprite->setTexture(textures[0]);
                }
            }
        }
    }
    else {
        daysWithoutWater = 0;
    }
    checkPests(); // 每次更新时检查病虫害
    isWatered = false; // 每次更新后重置浇水状态
}

void Crops::setSeason(Season season) {
    if (currentSeason != season) { // 避免重复触发
        currentSeason = season;
        CCLOG("Season changed to %d", static_cast<int>(season));
    }
}
Season Crops::getSeason() {
    return currentSeason;
}

void Crops::checkPests() {
    if (!hasPests && CCRANDOM_0_1() < pestProbability) { // 随机概率感染病虫害
        hasPests = true;
        CCLOG("Crop infected with pests!");

        // 更改贴图显示病虫害状态（假设有特定图片）
        sprite->setTexture("../Resources/Crops/pests.png");
       
    }
}
void Crops::treatPests() {
    if (hasPests) {
        hasPests = false;
        CCLOG("Pests removed from crop!");

        // 判断是否处于成熟阶段（最后一个生长阶段）
        if (growthStage == maxGrowthStage) {
            // 从成熟贴图映射中获取当前季节的贴图
            if (matureTextures.find(type) != matureTextures.end()) {
                auto seasonTexture = matureTextures[type][currentSeason];
                if (this->type == "maple" || this->type == "oak" || this->type == "pine") {
                    sprite->setScale(1.0f);
                }
                sprite->setTexture(seasonTexture);               
                CCLOG("Restored crop to mature state with texture: %s", seasonTexture.c_str());
            }
        }
        else {
            // 如果未成熟，恢复到对应生长阶段的正常贴图
            if (resourceMap.find(type) != resourceMap.end()) {
                const auto& textures = resourceMap[type];
                if (growthStage >= 0 && growthStage < textures.size()) {
                    sprite->setTexture(textures[growthStage]);
                  
                }
            }
        }
    }
}


void Crops::waterCrop() {
    isWatered = true;
    daysWithoutWater = 0; // 浇水后重置未浇水天数
    // 创建一个动画，由五帧图片组成
    Vector<SpriteFrame*> frames;

    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_1.png", Rect(0, 0, 70, 70)));  // 假设每张图片的大小是 100x100
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_2.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_3.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_4.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_5.png", Rect(0, 0, 70, 70)));

    // 创建动画
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.7f);  // 每帧持续0.2秒
    Animate* animate = Animate::create(animation);

    // 显示浇水动画
    auto waterEffect = Sprite::create("../Resources/Animations/water/water_1.png");
    double x=sprite->getPosition().x;
    double y = sprite->getPosition().y;
    waterEffect->setPosition(Vec2(x, y-8));
    waterEffect->setScale(0.8f);
    this->addChild(waterEffect,-1);

    // 执行动画
    waterEffect->runAction(animate);

    // 动画结束后移除效果
    auto fadeOut = FadeOut::create(1.0f);
    auto removeEffect = CallFunc::create([waterEffect]() {
        waterEffect->removeFromParent();
        });

    auto sequence = Sequence::create(animate, fadeOut, removeEffect, nullptr);
    waterEffect->runAction(sequence);
}


bool Crops::isReadyToHarvest() const {
    return growthStage >= maxGrowthStage;
}

void Crops::setGrowthStage(int stage) {
    growthStage = std::min(stage, maxGrowthStage); // 确保阶段不超过最大值
    // 检查资源映射表中是否有当前农作物类型的资源
    if (growthStage == maxGrowthStage) {
        // 如果是成熟阶段，加载成熟阶段对应的季节贴图
        if (matureTextures.find(type) != matureTextures.end()) {
            auto it = matureTextures[type].find(currentSeason);
            if (it != matureTextures[type].end()) {
                if (this->type == "maple" || this->type == "oak" || this->type == "pine") {
                    sprite->setScale(1.0f);
                }
                sprite->setTexture(it->second);
                CCLOG("Set crop '%s' to mature state with texture: %s", type.c_str(), it->second.c_str());
            }
        }
    }
    else if (resourceMap.find(type) != resourceMap.end()) {
        const auto& textures = resourceMap[type];
        if (growthStage >= 0 && growthStage < textures.size()) {
            sprite->setTexture(textures[growthStage]);
        }
    }
}


void Crops::harvestCrop() {
    if (!canBePlanted()) { // 如果不满足条件（主要是等级检查）
        CCLOG("Crop '%s' cannot be planted due to level restriction.", type.c_str());
        return;
    }

    if (isReadyToHarvest()) {
        CCLOG("Crop '%s' harvested successfully!", type.c_str());

        // 安全移除父节点
        if (this->getParent()) {
            this->removeFromParent();
        }
    }
    else {
        CCLOG("Crop '%s' is not ready for harvest!", type.c_str());
    }
}

void Crops::chopTree() {
    CCLOG("Tree '%s' is swaying...", type.c_str());

    // 检查是否为树类型
    if (type != "oak" && type != "maple" && type != "pine") {
        CCLOG("Error: Crop '%s' is not a tree and cannot swing.", type.c_str());
        return;
    }

    // 定义树摇摆的幅度和速度
    float moveDistance = 3.0f; // 水平移动的距离（像素）
    float swingAngle = 3.0f;    // 摇摆的角度（度）
    float duration = 0.5f;      // 单次摇摆所需时间（秒）
    int repeatCount = 3;        // 摇摆次数

    // 创建向左摇摆的动作
    auto moveLeft = MoveBy::create(duration, Vec2(-moveDistance, 0)); // 左移
    auto rotateLeft = RotateBy::create(duration, -swingAngle);        // 左旋转

    // 创建向右摇摆的动作
    auto moveRight = MoveBy::create(duration, Vec2(moveDistance, 0)); // 右移
    auto rotateRight = RotateBy::create(duration, swingAngle);        // 右旋转

    // 合成摇摆动作
    auto swingLeft = Spawn::create(moveLeft, rotateLeft, nullptr);
    auto swingRight = Spawn::create(moveRight, rotateRight, nullptr);
    auto swingSequence = Sequence::create(swingLeft, swingRight, nullptr);

    // 摇摆动作重复指定次数
    auto repeatSwing = Repeat::create(swingSequence, repeatCount);

    // 添加最后的旋转 90 度动作
    auto rotateFinal = RotateBy::create(0.5f, -90.0f); // 0.5 秒向左旋转 90 度

    // 添加淡出消失动作
    auto fadeOut = FadeOut::create(1.0f); // 1 秒淡出

    // 移除节点的回调
    auto removeTree = CallFunc::create([this]() {
        CCLOG("Tree '%s' has disappeared after swaying and rotating.", type.c_str());
        this->removeFromParentAndCleanup(true);
        });

    // 组合所有动作：摇摆 -> 旋转 -> 淡出 -> 移除
    auto fullSequence = Sequence::create(repeatSwing, rotateFinal, fadeOut, removeTree, nullptr);

    // 执行动作
    this->sprite->runAction(fullSequence);
}
