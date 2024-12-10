/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SceneSwitcher.cpp
 * File Function: 场景转换
 * Author:        胡宝怡
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#include "SceneSwitcher.h"
#include "cocos2d.h"
#include "Classes/Scene/HelloWorldScene.h"  // 假设你要切换到的目标场景
#include "Classes/Scene/IndoorScene.h"  // 假设你要切换到的目标场景
#include "Classes/Scene/FarmScene.h"  // 假设你要切换到的目标场景
USING_NS_CC;

MapSwitcher::MapSwitcher() : targetMapName(""), character(nullptr) {}

MapSwitcher::~MapSwitcher() {}

MapSwitcher* MapSwitcher::create(const std::string& targetMapName, Character* character)
{
    MapSwitcher* ret = new MapSwitcher();
    if (ret && ret->init(targetMapName, character)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MapSwitcher::init(const std::string& targetMapName, Character* character)
{
    if (!Node::init()) {
        return false;
    }

    this->targetMapName = targetMapName;
    this->character = character;

    // 你可以设置一个调度器来周期性检查人物是否到达切换区域
    schedule([this](float deltaTime) {
        this->checkCharacterPositionAndSwitchScene(deltaTime);
        }, 0.1f, "check_position_key");

    return true;
}

void MapSwitcher::checkCharacterPositionAndSwitchScene(float deltaTime)
{
    // 确保人物有效
    if (!character) {
        CCLOG("Error: character is null");
        return;
    }
    
    // 使用更新后的位置
    Vec2 characterPosition = character->updatePosition(deltaTime);
    /* CCLOG("Updated pos: (%f, %f)", characterPosition.x, characterPosition.y);*/


     // 检查人物是否在切换区域内

    if (targetMapName == "house") {
        // 添加错误处理
        if (checkIfInSwitchArea_farm(characterPosition)) {
            try {
                auto scene = IndoorScene::createScene("../Resources/Maps/Farm/house.tmx"); // 修改路径，
                if (scene) {

                    auto transition = TransitionFade::create(1.0f, scene);
                    if (transition) {
                        Director::getInstance()->replaceScene(transition);
                    }
                    else {
                        CCLOG("Error: Failed to create transition");
                    }
                }
                else {
                    CCLOG("Error: Failed to create scene");
                }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during scene switch: %s", e.what());
            }
        }
    }
    else if (targetMapName == "farm2") {
        if (checkIfInSwitchArea_house(characterPosition)) {
            // 添加错误处理
            try {

                // 先清理当前角色实例
               // character->destroyInstance();
                auto scene = FarmScene::createScene(); 
                if (scene) {
                    auto transition = TransitionFade::create(1.0f, scene);
                    if (transition) {
                        Director::getInstance()->replaceScene(transition);
                    }
                    else {
                        CCLOG("Error: Failed to create transition");
                    }
                }
                else {
                    CCLOG("Error: Failed to create scene");
                }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during scene switch: %s", e.what());
            }
        }
    }

}

bool MapSwitcher::checkIfInSwitchArea_farm(const Vec2& position)
{
    //// 打印传入的坐标
    CCLOG("Received Position: (%f, %f)", position.x, position.y);
    // 假设目标切换区域是地图上的某个点
    Rect switchArea(0, 0, 100, 100);  // 假设目标区域是一个矩形（可以自定义位置和大小）

    return switchArea.containsPoint(position);
}

bool MapSwitcher::checkIfInSwitchArea_house(const Vec2& position)
{
    //// 打印传入的坐标
   /* CCLOG("Received Position: (%f, %f)", position.x, position.y);*/
    // 假设目标切换区域是地图上的某个点
    Rect switchArea(245, 55, 85, 55);  // 假设目标区域是一个矩形（可以自定义位置和大小）
  
    return switchArea.containsPoint(position);
}