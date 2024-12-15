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

// ���徲̬��Դӳ���
std::unordered_map<std::string, std::vector<std::string>> Crop::resourceMap;

void Crop::initializeResourceMap() {
    // �����Դ���Ѿ���ʼ����������
    if (!resourceMap.empty()) return;

    // Ϊÿ��ũ����������Ӷ�Ӧ��ͼƬ��Դ·��
    //С��
    resourceMap["little_tree"] = {
        "../Resources/Crops/little_tree_0.png",
        "../Resources/Crops/little_tree_1.png",
        "../Resources/Crops/little_tree_2.png",
        "../Resources/Crops/little_tree_3.png"
    };
    //̦����
    resourceMap["tree"] = {
       "../Resources/Crops/tree1_0.png",
       "../Resources/Crops/tree1_1.png",
       "../Resources/Crops/tree1_2.png",
       "../Resources/Crops/tree1_3.png",
       "../Resources/Crops/tree1_4.png"
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
    for (const auto& entry : resourceMap) {
        CCLOG("Type: %s", entry.first.c_str());
        for (const auto& texture : entry.second) {
            CCLOG(" - Texture: %s", texture.c_str());
        }
    }
    //��ή
    resourceMap["wilt"] = {
       "../Resources/Crops/wilt/wilt_0.png"
    };

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

// ʩ�ʺ������ı�isFertilizedΪtrue�����������ٶ�
void Crop::fertilize() {
    isFertilized = true;
}

bool Crop::init(const std::string& type, int maxGrowthStage) {
    CCLOG("Initializing Crop...");
    if (!Node::init()) {
        CCLOG("Error: Node::init failed");
        return false;
    }

    // ��ʼ����Դ�����״ε���ʱ��ִ�У�
    initializeResourceMap();

    this->type = type;
    this->growthStage = 0;
    this->maxGrowthStage = maxGrowthStage;
    this->growthTimer = 0.0f;
    this->isWatered = false;
    this->daysWithoutWater = 0;
    this->isFertilized = 0;
    // ��ʼ��ũ����ľ���
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
    float growthSpeed = 5.0f;  // Ĭ��ÿ�׶�5��
    if (isFertilized) {
        growthSpeed = 3.0f;  // ʩ�ʺ�ÿ�׶�3��
    }

    // ����Ƿ�ﵽ��һ�������׶�
    if (growthTimer >= growthSpeed) {
        growthTimer = 0.0f;
        growthStage = std::min(growthStage + 1, maxGrowthStage);

        // �Ӿ�̬��Դӳ����л�ȡ��Ӧ����ͼ
        if (resourceMap.find(type) != resourceMap.end()) {
            const auto& textures = resourceMap[type];
            if (growthStage >= 0 && growthStage < textures.size()) {
                sprite->setTexture(textures[growthStage]);
            }
        }
    }

    // ���ֲ���Ƿ���������û�н�ˮ�����ǣ����ή
    if (!isWatered) {
        daysWithoutWater++;
        if (daysWithoutWater >= 2) {
            if (resourceMap.find(type) != resourceMap.end()) {
                const auto& textures = resourceMap["wilt"];
                if (!textures.empty()) {
                    sprite->setTexture(textures[0]); // ��Ϊ��ή״̬��ͼƬ
                }
            }
        }
    }
    else {
        daysWithoutWater = 0; // ������콽ˮ�ˣ���������
    }

    isWatered = false; // ÿ�θ��º����ý�ˮ״̬
}


void Crop::waterCrop() {
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


bool Crop::isReadyToHarvest() const {
    return growthStage >= maxGrowthStage;
}

void Crop::setGrowthStage(int stage) {
    growthStage = std::min(stage, maxGrowthStage); // ȷ���׶β��������ֵ

    // �����Դӳ������Ƿ��е�ǰũ�������͵���Դ
    if (resourceMap.find(type) != resourceMap.end()) {
        const auto& textures = resourceMap[type];

        // ��鵱ǰ�׶��Ƿ�����Դ��Χ��
        if (growthStage >= 0 && growthStage < textures.size()) {
            sprite->setTexture(textures[growthStage]); // ������ͼΪ��Ӧ�׶ε���Դ
        }
        else {
            CCLOG("Warning: Growth stage %d out of range for type %s", growthStage, type.c_str());
        }
    }
    else {
        CCLOG("Error: No resources found for crop type: %s", type.c_str());
    }
}

void Crop::playWeedingAnimation(const Vec2& position, TMXTiledMap* farmMap) {
    CCLOG("Playing weeding animation at position (%f, %f)...", position.x, position.y);

    // ����һ���µľ�������ʾ����
    auto tempSprite = Sprite::create();
    if (tempSprite == nullptr) {
        CCLOG("Error: Failed to create sprite for weeding animation.");
        return;
    }

    // ���þ���ĳ�ʼλ��
    tempSprite->setPosition(position);

    // ��ӵ���ǰ�ڵ�򳡾�
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


void Crop::playStoneBreakingAnimationAt(const Vec2& position, TMXTiledMap* farmMap) {
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
    // ��ӵ���ǰ�ڵ�򳡾�
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

