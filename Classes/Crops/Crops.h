/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: ũ�������ͷ�ļ�
 * Author:        ������
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"

class Crop : public cocos2d::Node {
public:
    static Crop* create(const std::string& type, int maxGrowthStage);

    // ��ʼ��ũ����
    bool init(const std::string& type, int maxGrowthStage);

    // ���������߼�
    void updateGrowth(float deltaTime);

    // ��ˮ�߼�
    void waterCrop();

    // �ж��Ƿ�����ջ�
    bool isReadyToHarvest() const;

    // ���������׶�
    void setGrowthStage(int stage);

    // ��ȡũ��������
    std::string getType() const { return type; }

    // ��ȡ��ǰ�����׶�
    int getGrowthStage() const { return growthStage; }

    //���ݶ���cocos2d::
    void playWeedingAnimation(const cocos2d::Vec2& position, cocos2d::TMXTiledMap* farmMap);
    //��ʯ����
    void playStoneBreakingAnimationAt(const cocos2d::Vec2& position, cocos2d::TMXTiledMap* farmMap);
    // ������ʩ�ʺ���
    void fertilize();

private:
    bool isFertilized;         //�Ƿ�ʩ��
    std::string type;          // ũ��������
    int growthStage;           // ��ǰ�����׶�
    int maxGrowthStage;        // ��������׶�
    float growthTimer;         // ������ʱ��
    bool isWatered;            // �Ƿ񱻽�ˮ
    int daysWithoutWater;       //û�б���ˮ������
    // ��̬��Դӳ���
    static std::unordered_map<std::string, std::vector<std::string>> resourceMap;

    // ������Դ��
    static void initializeResourceMap();
    cocos2d::Sprite* sprite;   // ũ�������ʾ����
};

#endif // __CROP_H__

