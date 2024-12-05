#pragma once
#include <string>
#include "cocos2d.h"  // ���� cocos2d �����ͷ�ļ���������ʾʱ���ǩ��

class TimeManager {
public:
    static TimeManager* getInstance();  // ��ȡ TimeManager �ĵ���
    void update(int deltaT); // deltaT: ʱ����������λ��
    std::string getTimeString() const; // ��ȡ��ǰʱ����ַ�����ʽ��Сʱ:���ӣ�
    bool isDaytime() const; // �ж��Ƿ��ǰ���

    void setTimeLabel(cocos2d::Label* label); // ����ʱ���ǩ���ⲿ���룩

    void startUpdating(); // ����ʱ�����
    void stopUpdating();  // ֹͣʱ�����

private:
    TimeManager();  // ˽�й��캯���������ⲿʵ����
    ~TimeManager();  // ��������

    static TimeManager* instance;  // ����ָ��
    int timeInSeconds; // ��ǰʱ�䣬����Ϊ��λ
   

    int day, hour, minute, season; // ��ǰ��������Сʱ�����ӡ�����
    bool isDay;  // ��ǰ�ǰ��컹��ҹ��

    cocos2d::Label* timeLabel;  // ������ʾʱ��ı�ǩָ��

    void updateDayNightCycle(); // ������ҹ�仯
    void updateSeason(); // ���¼��ڱ仯
    void updateTime(); // ����ʱ�䣨Сʱ�����ӣ�

    void updateLabel(); // ����ʱ����ʾ��ǩ
};
