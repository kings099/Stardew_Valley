/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: 农作物类，实现农作物的各种基本操作
 * Author:        胡宝怡
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#include "Crops.h"
#include "Classes/Control/TimeManager.h"

USING_NS_CC;
// 初始化静态变量
Season Crops::_currentSeason = Season::Spring;
int Crops::_playerLevel = 1; // 初始人物等级为1

// 定义静态资源映射表
std::unordered_map<std::string, std::vector<std::string>> Crops::_resourceMap;

void Crops::initializeResourceMap() {
    // 如果资源表已经初始化，则跳过
    if (!_resourceMap.empty()) return;

    // 为每种农作物类型添加对应的图片资源路径
    //花椰菜
    _resourceMap["cauliflower"] = {
        "../Resources/Crops/Cauliflower/cauliflower_0.png",
        "../Resources/Crops/Cauliflower/cauliflower_1.png",
        "../Resources/Crops/Cauliflower/cauliflower_2.png",
        "../Resources/Crops/Cauliflower/cauliflower_3.png",
         "../Resources/Crops/Cauliflower/cauliflower_4.png"
    };

    //甘蓝菜
    _resourceMap["kale"] = {
       "../Resources/Crops/Kale/kale_0.png",
       "../Resources/Crops/Kale/kale_1.png",
       "../Resources/Crops/Kale/kale_2.png",
       "../Resources/Crops/Kale/kale_3.png",
       "../Resources/Crops/Kale/kale_4.png"
    };

    //南瓜
    _resourceMap["pumpkin"] = {
   "../Resources/Crops/Pumpkin/pumpkin_0.png",
    "../Resources/Crops/Pumpkin/pumpkin_1.png",
    "../Resources/Crops/Pumpkin/pumpkin_2.png",
    "../Resources/Crops/Pumpkin/pumpkin_3.png",
    "../Resources/Crops/Pumpkin/pumpkin_4.png",
    "../Resources/Crops/Pumpkin/pumpkin_5.png"
    };
    //橡树
    _resourceMap["oak"] = {
   "../Resources/Crops/Oak/oak_0.png",
    "../Resources/Crops/Oak/oak_1.png",
    "../Resources/Crops/Oak/oak_2.png",
    "../Resources/Crops/Oak/oak_3.png"
    };

    //枫树
    _resourceMap["maple"] = {
   "../Resources/Crops/Maple/maple_0.png",
    "../Resources/Crops/Maple/maple_1.png",
    "../Resources/Crops/Maple/maple_2.png",
    "../Resources/Crops/Maple/maple_3.png"
    };

    //松树
    _resourceMap["pine"] = {
   "../Resources/Crops/Pine/pine_0.png",
    "../Resources/Crops/Pine/pine_1.png",
    "../Resources/Crops/Pine/pine_2.png",
    "../Resources/Crops/Pine/pine_3.png"
    };

    //普通草
    _resourceMap["grass"] = {
        "../Resources/Crops/grass.png"
    };

    //石头
    _resourceMap["stone"] = {
        "../Resources/Crops/stone.png"
    };
    //草2
    _resourceMap["grass_2"] = {
        "../Resources/Crops/grass_2.png"
    };

    //枯萎
    _resourceMap["wilt"] = {
       "../Resources/Crops/wilt/wilt_0.png"
    };
    for (const auto& entry : _resourceMap) {
        CCLOG("Type: %s", entry.first.c_str());
        for (const auto& texture : entry.second) {
            CCLOG(" - Texture: %s", texture.c_str());
        }
    }

}

// 农作物的生长周期表（不同季节不同周期）
std::unordered_map<std::string, std::unordered_map<Season, float>> Crops::_growthCycles = {
    {"cauliflower", {{Season::Spring, 50.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter,72.0f}}},
    {"kale", {{Season::Spring, 30.0f}, {Season::Summer, 30.0f}, {Season::Fall, 40.0f}, {Season::Winter, 50.0f}}},
    {"pumpkin", {{Season::Spring, 2.0f}, {Season::Summer, 50.0f}, {Season::Fall, 60.0f}, {Season::Winter, 72.0f}}},
    {"oak", {{Season::Spring,2.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"maple", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}},
    {"pine", {{Season::Spring, 72.0f}, {Season::Summer, 72.0f}, {Season::Fall, 96.0f}, {Season::Winter, 120.0f}}}

};

// 树成熟阶段图片（不同季节的贴图）
std::unordered_map<std::string, std::unordered_map<Season, std::string>> Crops::_matureTextures = {
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

CropData Crops::getCropData() {
    _cropData.Harvest = _type;
    _cropData.type = _type;
    if (this->isReadyToHarvest()==true) {
        _cropData.isHarvest=true;
    }
    else {
        _cropData.isHarvest = false;
    }
    _cropData.isWatered = _isWatered;
    _cropData.daysWithoutWater = _daysWithoutWater;
    _cropData.growthStage = _growthStage;
    _cropData.hasPests = _hasPests;
    _cropData.isFertilized = _isFertilized;
    return _cropData;
}

//设置当前的人物等级
void Crops::setPlayerLevel(int level) {
    _playerLevel = level;
    CCLOG("Player level set to: %d", _playerLevel);
}

//由人物等级判断是否能种植当下农作物
bool Crops::canBePlanted(const std::string& cropType){
    if (cropType == "pumpkin" && _playerLevel < 3) {
        CCLOG("Error: Player level too low to plant pumpkin! Required level: 3");
        return false;
    }
    return true;
}


Crops* Crops::create(const std::string& type, int maxGrowthStage) {

    // 在创建之前先检查能否种植
    if (!canBePlanted(type)) {
        CCLOG("Cannot plant this crop due to insufficient player level.");
        return nullptr;
    }
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
    _isFertilized = true;
}

//初始化农作物信息
bool Crops::init(const std::string& type, int maxGrowthStage) {
    CCLOG("Initializing Crop...");
    if (!Node::init()) {
        CCLOG("Error: Node::init failed");
        return false;
    }

    // 初始化资源表（仅首次调用时会执行）
    initializeResourceMap();

    this->_type = type;
    this->_growthStage = 0;
    this->_maxGrowthStage = maxGrowthStage;
    this->_growthTimer = 0.0f;
    this->_isWatered = false;
    this->_daysWithoutWater = 0;
    this->_isFertilized = 0;
    this->_hasPests = false;    // 初始无病虫害
    this->_pestProbability = 0.05f; // 感染概率 10%
    // 初始化农作物的精灵
    _sprite = Sprite::create(_resourceMap[type][0]);
    if (_sprite == nullptr) {
        CCLOG("Error: Failed to load sprite for type: %s", type.c_str());
        return false;
    }

    _sprite->setScale(CROP_START_RATIO);
    // 设置锚点（例如设置到底部中心点）
    if (_type == "maple" || _type == "pine" || _type == "oak") {
        _sprite->setAnchorPoint(Vec2(CROP_HORIZONTAL_ANCHORPOINT, TREE_VERTICAL_ANCHORPOINT));
    }
    else {
        _sprite->setAnchorPoint(Vec2(CROP_HORIZONTAL_ANCHORPOINT, CROP_VERTICAL_ANCHORPOINT));
    }

    this->addChild(_sprite);
    CCLOG("Crop initialized successfully");
    this->schedule([this](float dt) {
        this->updateGrowth(dt);
        }, 24.0f, "crop_update");
    return true;
}

// 根据天气管理干旱情况，判断是否需要浇水
void Crops::manageDrought(Weather currentWeather) {
    // 检查是否枯萎
    if (!_isWatered) {
        _daysWithoutWater++;
        // 只处理干旱和晴天，雨天不需要浇水
        if (currentWeather == Weather::Dry) {
            // 干旱天气，每两天浇一次水
            if (_daysWithoutWater >= 2) {
                if (_resourceMap.find("wilt") != _resourceMap.end()) {
                    const auto& textures = _resourceMap["wilt"];
                    if (!textures.empty()) {
                        _sprite->setTexture(textures[0]);
                    }
                }
            }
        }
        else if (currentWeather == Weather::Sunny) {
            if (_daysWithoutWater >= 3) {
                if (_resourceMap.find("wilt") != _resourceMap.end()) {
                    const auto& textures = _resourceMap["wilt"];
                    if (!textures.empty()) {
                        _sprite->setTexture(textures[0]);
                    }
                }
            }
        }
        else if (currentWeather == Weather::Rainy) {
            _daysWithoutWater = 0;
        }
        // 如果是雨天，不做任何操作
    }
    else {
        _daysWithoutWater = 0;
    }
}



//更新植物的生长状态
void Crops::updateGrowth(float deltaTime) {

    const TimeManager* timeManager = TimeManager::getInstance();
    Season currentSeason = timeManager->getCurrentSeason();
    Crops::setSeason(currentSeason); // 设置当前季节

    // 检查是否被采摘
    if (_isRemoved == true) {
        return;
    }
    // 获取当前季节的生长周期
    float growthSpeed = 5.0f;
    if (_growthCycles.find(_type) != _growthCycles.end()) {
        if (_growthCycles[_type].find(_currentSeason) != _growthCycles[_type].end()) {
            growthSpeed = _growthCycles[_type][_currentSeason];
        }
    }

    // 如果施肥，加速生长
    if (_isFertilized) {
        growthSpeed *= 0.8f; // 生长周期缩短 20%
    }

    // 累积时间，进入下一个生长阶段
    _growthTimer += deltaTime;
    if (_growthTimer >= growthSpeed && !_hasPests) {
        _growthTimer = 0.0f;
        _growthStage = std::min(_growthStage + 1, _maxGrowthStage);

        // 如果达到成熟阶段，加载季节对应的成熟图片
        if (_growthStage == _maxGrowthStage) {
            if (_matureTextures.find(_type) != _matureTextures.end()) {
                auto seasonTexture = _matureTextures[_type][_currentSeason];
                _sprite->setTexture(seasonTexture);
                if (this->_type == "maple" || this->_type == "oak" || this->_type == "pine") {
                    _sprite->setScale(CROP_MATURE_RATIO);
                }
                CCLOG("Crop %s matured with texture: %s", _type.c_str(), seasonTexture.c_str());
                this->unschedule("crop_update");
            }
        }
        else {
            // 继续生长阶段的贴图更新
            if (_resourceMap.find(_type) != _resourceMap.end()) {
                const auto& textures = _resourceMap[_type];
                if (_growthStage >= 0 && _growthStage < textures.size()) {
                    _sprite->setTexture(textures[_growthStage]);
                }
            }
        }
    }
    if (_type != "oak" && _type != "maple" && _type != "pine") {
        Weather currentWeather = Weather::Dry;
        this->manageDrought(currentWeather);
        checkPests(); // 每次更新时检查病虫害
        _isWatered = false; // 每次更新后重置浇水状态
    }
}

//更新当前的季节
void Crops::setSeason(Season season) {
    if (_currentSeason != season) { // 避免重复触发
        _currentSeason = season;
        CCLOG("Season changed to %d", static_cast<int>(season));
    }
}

//获取当前的季节
Season Crops::getSeason() {
    return _currentSeason;
}

//检查植物是否患有病虫害
void Crops::checkPests() {
    if (_isRemoved == true) {
        return;
    }
    if (!_hasPests && CCRANDOM_0_1() < _pestProbability) { // 随机概率感染病虫害
        _hasPests = true;
        CCLOG("Crop infected with pests!");

        // 更改贴图显示病虫害状态（假设有特定图片）
        _sprite->setTexture("../Resources/Crops/pests.png");
       
    }
}

//处理病虫害函数，使植物恢复正常
void Crops::treatPests() {
    // 检查当前指针是否为空指针，防止调用已释放的对象
    if (_isRemoved == true) {
        return;
    }

    // 检查 sprite 是否为空指针
    if (_sprite == nullptr) {
        CCLOG("Error: Attempt to update crop with null sprite.");
        return;
    }
    if (_hasPests) {
        _hasPests = false;
        CCLOG("Pests removed from crop!");

        // 判断是否处于成熟阶段（最后一个生长阶段）
        if (_growthStage == _maxGrowthStage) {
            // 从成熟贴图映射中获取当前季节的贴图
            if (_matureTextures.find(_type) != _matureTextures.end()) {
                auto seasonTexture = _matureTextures[_type][_currentSeason];
                if (this->_type == "maple" || this->_type == "oak" || this->_type == "pine") {
                    _sprite->setScale(CROP_MATURE_RATIO);
                }
                _sprite->setTexture(seasonTexture);
                CCLOG("Restored crop to mature state with texture: %s", seasonTexture.c_str());
            }
        }
        else {
            // 如果未成熟，恢复到对应生长阶段的正常贴图
            if (_resourceMap.find(_type) != _resourceMap.end()) {
                const auto& textures = _resourceMap[_type];
                if (_growthStage >= 0 && _growthStage < textures.size()) {
                    _sprite->setTexture(textures[_growthStage]);

                }
            }
        }
    }
}

//浇水动画以及植物浇水状态的更新
void Crops::waterCrop() {
    _isWatered = true;
    _daysWithoutWater = 0; // 浇水后重置未浇水天数
    // 创建一个动画，由五帧图片组成
    Vector<SpriteFrame*> frames;

    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_1.png", Rect(0, 0, 70, 70)));  // 假设每张图片的大小是 100x100
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_2.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_3.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_4.png", Rect(0, 0, 70, 70)));
    frames.pushBack(SpriteFrame::create("../Resources/Animations/water/water_5.png", Rect(0, 0, 70, 70)));

    // 创建动画
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.2f);  // 每帧持续0.2秒
    Animate* animate = Animate::create(animation);

    // 显示浇水动画
    auto waterEffect = Sprite::create("../Resources/Animations/water/water_1.png");
    double x = _sprite->getPosition().x;
    double y = _sprite->getPosition().y;
    waterEffect->setPosition(Vec2(x, y - 8));
    waterEffect->setScale(WATER_RATIO);
    this->addChild(waterEffect, -1);

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

//判断农作物是否已经成熟
bool Crops::isReadyToHarvest() const {
    // 检查农作物是否已经被采摘
    if (_isRemoved == true) {
        return false;
    }

    // 检查 sprite 是否为空指针
    if (_sprite == nullptr) {
        CCLOG("Error: Attempt to update crop with null sprite.");
        return 0;
    }
    return _growthStage >= _maxGrowthStage;
}

//设置农作物当前的成长阶段
void Crops::setGrowthStage(int stage) {
    // 检查当前指针是否为空指针，防止调用已释放的对象
    if (_isRemoved == true) {
        return;
    }

    // 检查 sprite 是否为空指针
    if (_sprite == nullptr) {
        CCLOG("Error: Attempt to update crop with null sprite.");
        return;
    }
    _growthStage = std::min(stage, _maxGrowthStage); // 确保阶段不超过最大值
    // 检查资源映射表中是否有当前农作物类型的资源
    if (_growthStage == _maxGrowthStage) {
        // 如果是成熟阶段，加载成熟阶段对应的季节贴图
        if (_matureTextures.find(_type) != _matureTextures.end()) {
            auto it = _matureTextures[_type].find(_currentSeason);
            if (it != _matureTextures[_type].end()) {
                if (this->_type == "maple" || this->_type == "oak" || this->_type == "pine") {
                    _sprite->setScale(CROP_MATURE_RATIO);
                }
                _sprite->setTexture(it->second);
                CCLOG("Set crop '%s' to mature state with texture: %s", _type.c_str(), it->second.c_str());
            }
        }
    }
    else if (_resourceMap.find(_type) != _resourceMap.end()) {
        const auto& textures = _resourceMap[_type];
        if (_growthStage >= 0 && _growthStage < textures.size()) {
            _sprite->setTexture(textures[_growthStage]);
        }
    }
}

//农作物收获时调用函数，删除当前农作物精灵
void Crops::harvestCrop() {
    // 检查当前指针是否为空指针，防止调用已释放的对象
    if (this == nullptr) {
        CCLOG("Error: Attempt to update a null crop pointer.");
        return;
    }
    if (_isRemoved == true) {//已经被采摘了的不能重复采摘
        return;
    }
    //if (!canBePlanted()) { // 如果不满足条件（主要是等级检查）
    //    CCLOG("Crop '%s' cannot be planted due to level restriction.", _type.c_str());
    //    return;
    //}

    if (isReadyToHarvest()) {
        CCLOG("Crop '%s' harvested successfully!", _type.c_str());
        this->unschedule("crop_update");
        // 安全移除父节点
        if (this->getParent()) {
            this->removeFromParent();
            _isRemoved = true;
            /*if (this != nullptr) {
                CCLOG("Crop EXIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", type.c_str());
            }*/

        }
    }
    else {
        CCLOG("Crop '%s' is not ready for harvest!", _type.c_str());
    }
}

//砍树动画函数
void Crops::chopTree() {
    CCLOG("Tree '%s' is swaying...", _type.c_str());

    // 检查是否为树类型
    if (_type != "oak" && _type != "maple" && _type != "pine") {
        CCLOG("Error: Crop '%s' is not a tree and cannot swing.", _type.c_str());
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
        CCLOG("Tree '%s' has disappeared after swaying and rotating.", _type.c_str());
        this->removeFromParentAndCleanup(true);
        });

    // 组合所有动作：摇摆 -> 旋转 -> 淡出 -> 移除
    auto fullSequence = Sequence::create(repeatSwing, rotateFinal, fadeOut, removeTree, nullptr);

    // 执行动作
    this->_sprite->runAction(fullSequence);
}


