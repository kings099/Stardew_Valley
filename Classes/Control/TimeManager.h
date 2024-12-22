#pragma once
#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include "cocos2d.h"
#include "../proj.win32/Constant.h"

class TimeManager {
public:
    // ��ȡ TimeManager �ĵ���
    static TimeManager* getInstance();

    // ������Ϸʱ��
    void update(int deltaT);

    // ��ȡ��ǰ���ڼ����磺����һ�����ڶ���
    std::string getWeekDay() const;

    // ��ȡ��ǰʱ�䣨Сʱ:���ӣ���ʽ���ַ���
    std::string getCurrentTime() const;

    // ��ȡ��ǰ����
    Season getCurrentSeason() const;

    // ��ȡ��ǰ����
    std::string getCurrentSeason_() const;

    // ��ȡ��ǰ��Ϸ��
    int getCurrentDay() const;

    // �ж��Ƿ��ǰ���
    bool isDaytime() const;

    // ����ʱ�����
    void startUpdating();

    // ֹͣʱ�����
    void stopUpdating();

private:
    // ���캯��
    TimeManager();

    // ��������
    ~TimeManager(); 

    // ����ʱ�䣨Сʱ�����ӡ�������
    void updateTime();

    // ������ҹ����
    void updateDayNightCycle();

    // ���¼���
    void updateSeason();

    static TimeManager* instance;  // ����ָ��

    int _timeInSeconds;  // ��Ϸ��ʱ�䣨�룩
    int _day;            // ��ǰ��Ϸ��
    int _hour;           // ��ǰСʱ
    int _minute;         // ��ǰ����
    Season _season;         // ��ǰ����
    bool _isDay;         // �Ƿ�Ϊ����
};

#endif // ! __TIMEMANAGER_H__