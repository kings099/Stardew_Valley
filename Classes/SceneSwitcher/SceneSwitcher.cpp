/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     SceneSwitcher.cpp
 * File Function: ����ת��
 * Author:        ������
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#include "SceneSwitcher.h"
#include "cocos2d.h"
#include "Classes/Scene/HelloWorldScene.h"  // ������Ҫ�л�����Ŀ�곡��
#include "Classes/Scene/IndoorScene.h"  // ������Ҫ�л�����Ŀ�곡��
#include "Classes/Scene/FarmScene.h"  // ������Ҫ�л�����Ŀ�곡��
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

    // ���������һ���������������Լ�������Ƿ񵽴��л�����
    schedule([this](float deltaTime) {
        this->checkCharacterPositionAndSwitchScene(deltaTime);
        }, 0.1f, "check_position_key");

    return true;
}

void MapSwitcher::checkCharacterPositionAndSwitchScene(float deltaTime)
{
    // ȷ��������Ч
    if (!character) {
        CCLOG("Error: character is null");
        return;
    }
    
    // ʹ�ø��º��λ��
    Vec2 characterPosition = character->updatePosition(deltaTime);
    /* CCLOG("Updated pos: (%f, %f)", characterPosition.x, characterPosition.y);*/


     // ��������Ƿ����л�������

    if (targetMapName == "house") {
        // ��Ӵ�����
        if (checkIfInSwitchArea_farm(characterPosition)) {
            try {
                auto scene = IndoorScene::createScene("../Resources/Maps/Farm/house.tmx"); // �޸�·����
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
            // ��Ӵ�����
            try {

                // ������ǰ��ɫʵ��
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
    //// ��ӡ���������
    CCLOG("Received Position: (%f, %f)", position.x, position.y);
    // ����Ŀ���л������ǵ�ͼ�ϵ�ĳ����
    Rect switchArea(0, 0, 100, 100);  // ����Ŀ��������һ�����Σ������Զ���λ�úʹ�С��

    return switchArea.containsPoint(position);
}

bool MapSwitcher::checkIfInSwitchArea_house(const Vec2& position)
{
    //// ��ӡ���������
   /* CCLOG("Received Position: (%f, %f)", position.x, position.y);*/
    // ����Ŀ���л������ǵ�ͼ�ϵ�ĳ����
    Rect switchArea(245, 55, 85, 55);  // ����Ŀ��������һ�����Σ������Զ���λ�úʹ�С��
  
    return switchArea.containsPoint(position);
}