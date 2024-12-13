#pragma once
#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include "cocos2d.h"

class TimeManager {
public:
    // ��ȡ TimeManager �ĵ���
    static TimeManager* getInstance();

    // ������Ϸʱ��
    void update(int deltaT);

    // ��ȡ��ǰʱ����ַ�����ʾ�����ڡ��ա�ʱ�֣�
    std::string getTimeString() const;

    // ��ȡ��ǰ���ڼ����磺����һ�����ڶ���
    std::string getWeekDay() const;

    // ��ȡ��ǰʱ�䣨Сʱ:���ӣ���ʽ���ַ���
    std::string getCurrentTime() const;

    // �ж��Ƿ��ǰ���
    bool isDaytime() const;

    // ����ʱ�����
    void startUpdating();

    // ֹͣʱ�����
    void stopUpdating();

private:
    TimeManager();  // ���캯��
    ~TimeManager(); // ��������

    // ����ʱ�䣨Сʱ�����ӡ�������
    void updateTime();

    // ������ҹ����
    void updateDayNightCycle();

    // ���¼���
    void updateSeason();

    static TimeManager* instance;  // ����ָ��

    int timeInSeconds; // ��Ϸ��ʱ�䣨�룩
    int day;            // ��ǰ��Ϸ��
    int hour;           // ��ǰСʱ
    int minute;         // ��ǰ����
    int season;         // ��ǰ����
    bool isDay;         // �Ƿ�Ϊ����
};

#endif // __TIMEMANAGER_H__

