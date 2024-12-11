/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     TimeManagerUI.cpp
 * File Function: ��ʾʱ����Ϣ��UI��������ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/7
 * License:       MIT License
 ****************************************************************/
#include "TimeManagerUI.h"
#include "Manager/TimeManager.h"
#include"../proj.win32/Constant.h"
USING_NS_CC;

TimeManagerUI* TimeManagerUI::create()
{
    TimeManagerUI* ret = new TimeManagerUI();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool TimeManagerUI::init()
{
    if (!Layer::init())
    {
        return false;
    }
    // ��ȡ�ɼ������С
    visibleSize = Director::getInstance()->getVisibleSize();

    // �������Ͻǵ�λ��
    Vec2 rightTopPos = Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f);  // ���Ͻǣ����������ʵ�ƫ����

    // ��������ͼƬ
    backgroundSprite = Sprite::create("../Resources/UI/timetable.png");  // ����ͼƬ·��
    // ��ȡԭʼͼƬ�ߴ�
    Size originalSize = backgroundSprite->getContentSize();

    // �������ű�����ʹ��ͼƬ��Ӧ 16x16 ����
    float scaleX = UI_SCALE / originalSize.width;  // ���� X ��������ű���
    float scaleY = UI_SCALE / originalSize.height; // ���� Y ��������ű���

    // �������ű���
    backgroundSprite->setScale(scaleX, scaleY);

    // ���ñ���ͼƬλ��
    backgroundSprite->setPosition(rightTopPos);

    // ��ӵ�����
    this->addChild(backgroundSprite, 0);  // �����ڵײ�

    // �����ǩ��λ�ã�ʹ������ڱ���λ��
    Vec2 labelPos1 = Vec2(visibleSize.width*0.5, visibleSize.height * 0.5);  // �ڱ���ͼƬ�Ķ���
    Vec2 labelPos2 = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5-30); ;  // �� labelPos1 ����ƫ�� 30

    // ��������ʼ�� timeLabel1 �� timeLabel2
    timeLabel1 = Label::createWithSystemFont("111111111111111111111", "Arial", FONT_SIZE);
    timeLabel1->setPosition(labelPos1);  // ���� timeLabel1 ����ڱ���ͼƬ������λ��
    this->addChild(timeLabel1, 1);  // ��ǩ�ڱ�������

    timeLabel2 = Label::createWithSystemFont("1111111111111111111111", "Arial", FONT_SIZE);
    timeLabel2->setPosition(labelPos2);  // ���� timeLabel2 ����� timeLabel1 ��λ��
    this->addChild(timeLabel2, 1);  // ��ǩ�ڱ�������

    // ��ʼ��ʱ��ʾʱ��
    updateTimeDisplay();

    // ÿ�����һ��
    schedule([this](float deltaTime) {
        updateTimeDisplay();
        }, 1.0f, "updateTimeDisplayKey");

    return true;
}

void TimeManagerUI::updateTimeDisplay()
{
    // ��ȡ TimeManager ��ʵ��
    TimeManager* timeManager = TimeManager::getInstance();

    // ��ȡ������������Ϣ�����ں����ڣ�
    std::string weekDay = timeManager->getWeekDay();  // ���� TimeManager ���� getWeekDay() ����
    timeLabel1->setString(weekDay);  // ��ʾ���ڼ�  �Ĵ��벿��

    // ��ȡ������ʱ����Ϣ������/���Ϻ͵�ǰʱ�䣩
    bool isDaytime = timeManager->isDaytime();
    std::string dayOrNight = isDaytime ? "����" : "����";  // �ж��Ƿ��ǰ��������
    std::string timeOfDay = timeManager->getCurrentTime();  // ���� TimeManager ���� getCurrentTime() ����
    timeLabel2->setString(dayOrNight + " " + timeOfDay);  // ��ʾ����/���Ϻ͵�ǰʱ��  �Ĵ��벿��
}
