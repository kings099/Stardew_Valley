/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Crops.h
 * File Function: ũ�������ͷ�ļ�
 * Author:        ������
 * Update Date:   2024/12/22
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "CropData.h"

class Crops : public cocos2d::Node {
public:
   

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
    std::string getType() const { return _type; }

    // ��ȡ��ǰ�����׶�
    int getGrowthStage() const { return _growthStage; }

    // ������ʩ�ʺ���
    void fertilize();


    //�����������溦
    void checkPests();     // ��鲡�溦
    void treatPests();     // ���Ʋ��溦
    //ͨ������������ˮ
    void manageDrought(Weather currentWeather);
    // ������Ա�����ͱ���
    static void setPlayerLevel(int level); // ��������ȼ�

    // �ж��Ƿ�����ֲ��ǰũ����
    static bool canBePlanted(const std::string& cropType);

    // ����ũ����ʱ����Ƿ������ֲ
    static Crops* create(const std::string& type, int maxGrowthStage);

    //������������
    void chopTree();                     

    //ũ�����ջ�ʱ���ú�����ɾ����ǰũ���ﾫ��
    void harvestCrop();

    // ���ü���
    static void setSeason(Season season);

    // ��ȡ��ǰ����
    static Season getSeason();        

    // �Ƴ�ũ����
    bool _isRemoved = false;

    // ��ҵȼ�
    static int _playerLevel;
    // ���� CropData
    CropData getCropData();

private:
    bool _isFertilized;         // �Ƿ�ʩ��
    std::string _type;          // ũ��������
    int _growthStage;           // ��ǰ�����׶�
    int _maxGrowthStage;        // ��������׶�
    float _growthTimer;         // ������ʱ��
    bool _isWatered;            // �Ƿ񱻽�ˮ
    int _daysWithoutWater;      // û�б���ˮ������
    bool _hasPests;             // ����Ƿ��в��溦
    float _pestProbability;     // ��Ⱦ���溦�ĸ���
    cocos2d::Sprite* _sprite;   // ũ�������ʾ����

    CropData _cropData;         //ũ����Ļ�����Ϣ
    // ��̬��Ա�����ں��������ڱ�
    static Season _currentSeason;
    static std::unordered_map<std::string, std::unordered_map<Season, float>> _growthCycles;

    // ���ڴ洢��ͬ������ũ�������׶ε�ͼƬ
    static std::unordered_map<std::string, std::unordered_map<Season, std::string>> _matureTextures;

    // ��̬��Դӳ���
    static std::unordered_map<std::string, std::vector<std::string>> _resourceMap;

    // ������Դ��
    static void initializeResourceMap();
   
};

#endif // __CROP_H__

