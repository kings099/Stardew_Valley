/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     FarmMap.cpp
 * File Function: ��Ϸ�ӽǿ�����GameViewController��ʵ��
 * Author:        �����
 * Update Date:   2024/12/3
 * License:       MIT License
 ****************************************************************/

#include "GameViewController.h"

USING_NS_CC;

GameViewController::GameViewController(Character* character)
    : _character(character) {}

void GameViewController::update(float deltaTime) {
    
    // ��ȡ��ɫ��λ��
    Vec2 characterPosition = _character->updatePosition(deltaTime);

    // ��ȡ��Ļ���������С
    auto visibleSize = Director::getInstance()->getVisibleSize(); 

    // ���������Ӧ�õ�λ�ã�ȷ����ɫʼ�մ�����Ļ����
    Vec2 targetCameraPosition = Vec2(characterPosition.x + visibleSize.width / 4,
        characterPosition.y + visibleSize.height / 4);

    CCLOG(" % f, % f", characterPosition.x, characterPosition.y);
    // ��ȡĬ�ϵ��������ƽ���ظ�������λ��
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    Vec2 currentCameraPosition = camera->getPosition();

    // �Խ������ٶ�ƽ�����������λ��
    float lerpSpeed = 0.1f; // ������ֵ�Ըı���ɵ�ƽ����
    Vec2 newCameraPosition = currentCameraPosition.lerp(targetCameraPosition, lerpSpeed);
    camera->setPosition(newCameraPosition);
}
