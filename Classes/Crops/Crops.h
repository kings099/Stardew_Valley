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
#include "proj.win32/Constant.h"

class Crops : public cocos2d::Node {
public:
    static Crops* create(const std::string& type, int maxGrowthStage);

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

    // ������ʩ�ʺ���
    void fertilize();

    //���������溦
    void checkPests();     // ��鲡�溦
    void treatPests();     // ���Ʋ��溦

    void harvestCrop();

    static void setSeason(Season season); // ���ü���
    static Season getSeason();           // ��ȡ��ǰ����
    
private:
    bool isFertilized;         //�Ƿ�ʩ��
    std::string type;          // ũ��������
    int growthStage;           // ��ǰ�����׶�
    int maxGrowthStage;        // ��������׶�
    float growthTimer;         // ������ʱ��
    bool isWatered;            // �Ƿ񱻽�ˮ
    int daysWithoutWater;       //û�б���ˮ������
    bool hasPests;         // ����Ƿ��в��溦
    float pestProbability; // ��Ⱦ���溦�ĸ���
    // ��̬��Ա�����ں��������ڱ�
    static Season currentSeason;
    static std::unordered_map<std::string, std::unordered_map<Season, float>> growthCycles;

    // ���ڴ洢��ͬ������ũ�������׶ε�ͼƬ
    static std::unordered_map<std::string, std::unordered_map<Season, std::string>> matureTextures;

    // ��̬��Դӳ���
    static std::unordered_map<std::string, std::vector<std::string>> resourceMap;
    
    // ������Դ��
    static void initializeResourceMap();
    cocos2d::Sprite* sprite;   // ũ�������ʾ����
};

#endif // __CROP_H__

