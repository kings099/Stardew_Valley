/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameViewController.cpp
 * File Function: 游戏视角控制类GameViewController的实现
 * Author:        金恒宇
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/

#include "GameViewController.h"
#include "InteractionManager.h"
USING_NS_CC;

GameViewController::GameViewController()
    : _character(nullptr), _map(nullptr){}

GameViewController* GameViewController::create(Character* character, GameMap* gamemap) {
    GameViewController* ret = new (std::nothrow) GameViewController();
    if (ret && ret->init(character, gamemap)) {
        ret->autorelease(); // 自动管理内存
        return ret;
    }
    CC_SAFE_DELETE(ret); // 初始化失败时删除对象
    return nullptr;
}

bool GameViewController::init(Character* character, GameMap* gamemap) {
    // 确保父类 Node 初始化成功
    if (!Node::init()) {
        return false;
    }

    // 确保角色和地图对象不为空
    CCASSERT(character != nullptr, "Character must not be null");
    CCASSERT(gamemap != nullptr, "GameMap must not be null");

    _character = character;
    _map = gamemap;
    _darknessMask = nullptr;
    _circleHole = nullptr;

    return true;
}



void GameViewController::update(float deltaTime) {

    // 获取角色的位置
    Vec2 characterPosition = _character->updatePosition(deltaTime);

    // 地图位置
    Vec2 mapPosition = _map->getPosition();

    // 地图大小
    Size mapSize = _map->getMapSize();

    // 更新遮罩位置
    if (_darknessEnabled && _circleHole && _character) {
        // 更新透明圆的位置
        auto characterPosition = _character->getPosition();
        _circleHole->clear();
        _circleHole->drawSolidCircle(characterPosition, 150.0f, 0, 50, cocos2d::Color4F(0, 0, 0, 0));
    }

    // 获取摄像机
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();

    // 获取当前地图缩放比例
    float scale = _map->getScale();


    // 获取屏幕可视区域大小
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 计算摄像机应该的位置：确保角色始终处于屏幕中央且限制摄像机位置确保不超出地图的边界
    Vec2 targetCameraPosition;

    // 地图小于屏幕大小
    if (mapSize.width * scale < visibleSize.width && mapSize.height * scale < visibleSize.height) {
        targetCameraPosition = characterPosition;
    }
    else {
        // 目标位置是角色位置
        float idealX = characterPosition.x;
        // 边界位置判断
        targetCameraPosition.x = clamp(
            idealX,
            mapPosition.x + visibleSize.width / 2.0f,
            mapPosition.x + mapSize.width * scale - visibleSize.width / 2.0f
        );

        float idealY = characterPosition.y;
        // 边界位置判断
        targetCameraPosition.y = clamp(
            idealY,
            mapPosition.y + visibleSize.height / 2.0f,
            mapPosition.y + mapSize.height * scale - visibleSize.height / 2.0f
        );
    }

    Vec2 currentCameraPosition = camera->getPosition();
    // 以较慢的速度平滑过渡摄像机位置
    float lerpSpeed = 0.1f; // 调整此值以改变过渡的平滑度
    Vec2 newCameraPosition = currentCameraPosition.lerp(targetCameraPosition, lerpSpeed);
    camera->setPosition(newCameraPosition);

}

void GameViewController::setMap(GameMap* newMap) {
    if (newMap != nullptr) {
        //设置新地图
        _map = newMap;

        // 地图为矿洞地图添加黑暗效果
        if (_map->getType() == MapType::Mine) {
            enableDarknessEffect();
        }
        else
        {
            disableDarknessEffect();
        }
        CCLOG("GameViewController updated to new map: %p", _map);
    }
}

//辅助函数
float GameViewController::clamp(float value, float minVal, float maxVal)
{
    return std::max(std::min(value, maxVal), minVal);
}

// 模拟黑暗环境
void GameViewController::enableDarknessEffect() {
    if (_darknessMask) {
        return; // 如果已经存在蒙版，不重复添加
    }

    // 创建一个半透明的黑色 LayerColor
    _darknessMask = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
    if (_map) {
        _map->addChild(_darknessMask, _map->getLocalZOrder() + 1); // 添加到地图节点上，层级高于地图内容
    }

    CCLOG("Darkness effect enabled.");
}

// 禁用黑暗环境模拟
void GameViewController::disableDarknessEffect() {
    if (!_darknessEnabled) return;
    _darknessEnabled = false;

    _darknessMask = nullptr;

    CCLOG("Darkness effect disabled.");
}
