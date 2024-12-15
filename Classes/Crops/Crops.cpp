/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: ũ�����࣬ʵ��ũ�����������ˮ�ȶ���
 * Author:        ������
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "Crops.h"


USING_NS_CC;
// ��ʼ����̬����
Season Crops::currentSeason = Season::Winter;

// ���徲̬��Դӳ���
std::unordered_map<std::string, std::vector<std::string>> Crops::resourceMap;

void Crops::initializeResourceMap() {
    // �����Դ���Ѿ���ʼ����������
    if (!resourceMap.empty()) return;

    // Ϊÿ��ũ�����������Ӷ�Ӧ��ͼƬ��Դ·��
    //��Ҭ��
    resourceMap["cauliflower"] = {
        "../Resources/Crops/Cauliflower/cauliflower_0.png",
        "../Resources/Crops/Cauliflower/cauliflower_1.png",
        "../Resources/Crops/Cauliflower/cauliflower_2.png",
        "../Resources/Crops/Cauliflower/cauliflower_3.png",
         "../Resources/Crops/Cauliflower/cauliflower_4.png"
    };

    //������
    resourceMap["kale"] = {
       "../Resources/Crops/Kale/kale_0.png",
       "../Resources/Crops/Kale/kale_1.png",
       "../Resources/Crops/Kale/kale_2.png",
       "../Resources/Crops/Kale/kale_3.png",
       "../Resources/Crops/Kale/kale_4.png"
    };

    //�Ϲ�
     resourceMap["pumpkin"] = {
    "../Resources/Crops/Pumpkin/pumpkin_0.png",
     "../Resources/Crops/Pumpkin/pumpkin_1.png",
     "../Resources/Crops/Pumpkin/pumpkin_2.png",
     "../Resources/Crops/Pumpkin/pumpkin_3.png",
     "../Resources/Crops/Pumpkin/pumpkin_4.png",
     "../Resources/Crops/Pumpkin/pumpkin_5.png"
    };
    //����
     resourceMap["oak"] = {
    "../Resources/Crops/Oak/oak_0.png",
     "../Resources/Crops/Oak/oak_1.png",
     "../Resources/Crops/Oak/oak_2.png",
     "../Resources/Crops/Oak/oak_3.png"
     };

    //����
     resourceMap["maple"] = {
    "../Resources/Crops/Maple/maple_0.png",
     "../Resources/Crops/Maple/maple_1.png",
     "../Resources/Crops/Maple/maple_2.png",
     "../Resources/Crops/Maple/maple_3.png"
     };

    //����
     resourceMap["pine"] = {
    "../Resources/Crops/Pine/pine_0.png",
     "../Resources/Crops/Pine/pine_1.png",
     "../Resources/Crops/Pine/pine_2.png",
     "../Resources/Crops/Pine/pine_3.png"
     };

    //��ͨ��
    resourceMap["grass"] = {
        "../Resources/Crops/grass.png"
    };

    //ʯͷ
    resourceMap["stone"] = {
        "../Resources/Crops/stone.png"
    };
    //��2
    resourceMap["grass_2"] = {
        "../Resources/Crops/grass_2.png"
    };

    //��ή
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

// ũ������������ڱ�����ͬ���ڲ�ͬ���ڣ�
std::unordered_map<std::string, std::unordered_map<Season, float>> Crops::growthCycles = {
    {"cauliflower", {{Season::Spring, 50.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter,72.0f}}},
    {"kale", {{Season::Spring, 30.0f}, {Season::Summer, 30.0f}, {Season::Fall, 40.0f}, {Season::Winter, 50.0f}}},
    {"pumpkin", {{Season::Spring, 50.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter, 72.0f}}},
    {"oak", {{Season::Spring,2.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"maple", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"pine", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}}
  
};

// ������׶�ͼƬ����ͬ���ڵ���ͼ��
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

// ʩ�ʺ������ı�isFertilizedΪtrue�����������ٶ�
void Crops::fertilize() {
    isFertilized = true;
}

bool Crops::init(const std::string& type, int maxGrowthStage) {
    CCLOG("Initializing Crop...");
    if (!Node::init()) {
        CCLOG("Error: Node::init failed");
        return false;
    }

    // ��ʼ����Դ�������״ε���ʱ��ִ�У�
    initializeResourceMap();

    this->type = type;
    this->growthStage = 0;
    this->maxGrowthStage = maxGrowthStage;
    this->growthTimer = 0.0f;
    this->isWatered = false;
    this->daysWithoutWater = 0;
    this->isFertilized = 0;
    this->hasPests = false;    // ��ʼ�޲��溦
    this->pestProbability = 0.05f; // ��Ⱦ���� 10%
    // ��ʼ��ũ����ľ���
    sprite = Sprite::create(resourceMap[type][0]);
    if (sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }
    
    sprite->setScale(1.5f);
    // ����ê�㣨�������õ��ײ����ĵ㣩
    sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    

    this->addChild(sprite);
    CCLOG("Crop initialized successfully");
    return true;
}

void Crops::updateGrowth(float deltaTime) {
    // ��ȡ��ǰ���ڵ���������
    float growthSpeed = 5.0f;
    if (growthCycles.find(type) != growthCycles.end()) {
        if (growthCycles[type].find(currentSeason) != growthCycles[type].end()) {
            growthSpeed = growthCycles[type][currentSeason];
        }
    }

    // ���ʩ�ʣ���������
    if (isFertilized) {
        growthSpeed *= 0.8f; // ������������ 20%
    }

    // �ۻ�ʱ�䣬������һ�������׶�
    growthTimer += deltaTime;
    if (growthTimer >= growthSpeed && !hasPests) {
        growthTimer = 0.0f;
        growthStage = std::min(growthStage + 1, maxGrowthStage);

        // ����ﵽ����׶Σ����ؼ��ڶ�Ӧ�ĳ���ͼƬ
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
            // ���������׶ε���ͼ����
            if (resourceMap.find(type) != resourceMap.end()) {
                const auto& textures = resourceMap[type];
                if (growthStage >= 0 && growthStage < textures.size()) {
                    sprite->setTexture(textures[growthStage]);
                }
            }
        }
    }
    // ����Ƿ��ή
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
    checkPests(); // ÿ�θ���ʱ��鲡�溦
    isWatered = false; // ÿ�θ��º����ý�ˮ״̬
}

void Crops::setSeason(Season season) {
    if (currentSeason != season) { // �����ظ�����
        currentSeason = season;
        CCLOG("Season changed to %d", static_cast<int>(season));
    }
}
Season Crops::getSeason() {
    return currentSeason;
}

void Crops::checkPests() {
    if (!hasPests && CCRANDOM_0_1() < pestProbability) { // ������ʸ�Ⱦ���溦
        hasPests = true;
        CCLOG("Crop infected with pests!");

        // ������ͼ��ʾ���溦״̬���������ض�ͼƬ��
        sprite->setTexture("../Resources/Crops/pests.png");
       
    }
}
void Crops::treatPests() {
    if (hasPests) {
        hasPests = false;
        CCLOG("Pests removed from crop!");

        // �ж��Ƿ��ڳ���׶Σ����һ�������׶Σ�
        if (growthStage == maxGrowthStage) {
            // �ӳ�����ͼӳ���л�ȡ��ǰ���ڵ���ͼ
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
            // ���δ���죬�ָ�����Ӧ�����׶ε�������ͼ
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
    daysWithoutWater = 0; // ��ˮ������δ��ˮ����
    // ����һ������������֡ͼƬ���
    Vector<SpriteFrame*> frames;

    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_1.png", Rect(0, 0, 70, 70)));  // ����ÿ��ͼƬ�Ĵ�С�� 100x100
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_2.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_3.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_4.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_5.png", Rect(0, 0, 70, 70)));

    // ��������
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.7f);  // ÿ֡����0.2��
    Animate* animate = Animate::create(animation);

    // ��ʾ��ˮ����
    auto waterEffect = Sprite::create("../Resources/Animations/water/water_1.png");
    double x=sprite->getPosition().x;
    double y = sprite->getPosition().y;
    waterEffect->setPosition(Vec2(x, y-8));
    waterEffect->setScale(0.8f);
    this->addChild(waterEffect,-1);

    // ִ�ж���
    waterEffect->runAction(animate);

    // �����������Ƴ�Ч��
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
    growthStage = std::min(stage, maxGrowthStage); // ȷ���׶β��������ֵ
    // �����Դӳ������Ƿ��е�ǰũ�������͵���Դ
    if (growthStage == maxGrowthStage) {
        // ����ǳ���׶Σ����س���׶ζ�Ӧ�ļ�����ͼ
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

void Crops::playWeedingAnimation(const Vec2& position, TMXTiledMap* farmMap) {
    CCLOG("Playing weeding animation at position (%f, %f)...", position.x, position.y);

    // ����һ���µľ�������ʾ����
    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for weeding animation.");
        return;
    }

    // ���þ���ĳ�ʼλ��
    tempSprite->setPosition(position);

    // ���ӵ���ǰ�ڵ�򳡾�
    farmMap->addChild(tempSprite);
    tempSprite->setScale(0.5f);
    // ������ݶ�����֡����
    Vector<SpriteFrame*> frames;
    for (int i = 1; i < 6; ++i) { // ���趯���� 5 ֡
        std::string frameName = StringUtils::format("../Resources/Animations/Weeding/grass_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 36, 38)); // ����ÿ֡Ϊ 64x64
        if (frame == nullptr) {
            CCLOG("Error: Failed to load frame: %s", frameName.c_str());
            continue;
        }
        frames.pushBack(frame);
    }

    if (frames.empty()) {
        CCLOG("Error: No frames loaded for weeding animation");
        tempSprite->removeFromParent(); // ȷ����ʧ��ʱ�Ƴ��ڵ�
        return;
    }

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.4f); // ÿ֡����ʱ��Ϊ 0.2 ��
    auto animate = Animate::create(animation);

    // ���Ŷ������Ƴ�����
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}


void Crops::playStoneBreakingAnimationAt(const Vec2& position, TMXTiledMap* farmMap) {
    CCLOG("Playing stone breaking animation at position (%f, %f)...", position.x, position.y);

    // ����һ���µ���ʱ��������ʾ����
    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for stone breaking animation.");
        return;
    }

    // ���þ���ĳ�ʼλ��
    tempSprite->setPosition(position);
    tempSprite->setScale(0.2f);
    // ���ӵ���ǰ�ڵ�򳡾�
    farmMap->addChild(tempSprite);

    // ������ʯ������֡����
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; ++i) { // ���趯���� 5 ֡
        std::string frameName = StringUtils::format("../Resources/Animations/stone_break/stone_break_%d.png", i);
        auto frame = SpriteFrame::create(frameName, Rect(0, 0, 133, 136)); // ����ÿ֡Ϊ 64x64
        if (frame == nullptr) {
            CCLOG("Error: Failed to load frame: %s", frameName.c_str());
            continue;
        }
        frames.pushBack(frame);
    }

    if (frames.empty()) {
        CCLOG("Error: No frames loaded for stone breaking animation");
        tempSprite->removeFromParent(); // ����δ�ɹ����ض����Ľڵ�
        return;
    }

    // ��������
    auto animation = Animation::createWithSpriteFrames(frames, 0.5f); // ÿ֡����ʱ��Ϊ 0.2 ��
    auto animate = Animate::create(animation);

    // ������ɺ��Ƴ�����
    auto removeSelf = CallFunc::create([tempSprite]() {
        tempSprite->removeFromParent();
        });

    auto sequence = Sequence::create(animate, removeSelf, nullptr);
    tempSprite->runAction(sequence);
}
