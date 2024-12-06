/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     GameViewController.cpp
 * File Function: ��Ϸ�ӽǿ�����GameViewController��ʵ��
 * Author:        �����
 * Update Date:   2024/12/4
 * License:       MIT License
 ****************************************************************/

#include "GameViewController.h"

USING_NS_CC;

GameViewController::GameViewController(Character* character,FarmMap* farmmap)
    : _character(character),_farmmap(farmmap){
}


void GameViewController::update(float deltaTime) {
    
    // ��ȡ��ɫ��λ��
    Vec2 characterPosition = _character->updatePosition(deltaTime);

    Vec2 mapPosition = _farmmap->getPosition();
    Size mapSize = _farmmap->getMapSize();

    // ��ȡ�����
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    // ��ȡ��ǰ���ű���
    float scale = _character->getScale();

    // ��ȡ��Ļ���������С
    auto visibleSize = Director::getInstance()->getVisibleSize(); 

    // ���������Ӧ�õ�λ�ã�ȷ����ɫʼ�մ�����Ļ���������������λ��ȷ����������ͼ�ı߽�
    Vec2 targetCameraPosition;
    targetCameraPosition.x = std::max(characterPosition.x - mapPosition.x  , visibleSize.width / 2);
    targetCameraPosition.y = std::max(characterPosition.y - mapPosition.y, visibleSize.height / 2);
    targetCameraPosition.x = std::min(targetCameraPosition.x, mapSize.width - visibleSize.width / 2);
    targetCameraPosition.y = std::min(targetCameraPosition.y, mapSize.height - visibleSize.height / 2);


    // ������Ӱ��λ��
    Vec2 currentCameraPosition = camera->getPosition();

    // �Խ������ٶ�ƽ�����������λ��
    float lerpSpeed = 0.1f; // ������ֵ�Ըı���ɵ�ƽ����
    Vec2 newCameraPosition = currentCameraPosition.lerp(targetCameraPosition, lerpSpeed);
    camera->setPosition(newCameraPosition);
}
