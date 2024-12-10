/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI����UILayer���ʵ��
 * Author:        ��˼����ϳ�
 * Update Date:   2024/12/9
 * License:       MIT License
 ****************************************************************/
#include "UILayer.h"
#include "Classes/Character/Character.h"

USING_NS_CC;


// ��������
UILayer::~UILayer() {
    delete objectListLayer;
    delete timeLabel1;
    delete timeLabel2;
    delete timeDisplayLayer;
}

// ��ʼ��UI��
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    initializeObjectList();
    initializeTimeDisplay();
    return true;
}

// ��ʼ����Ʒ��
void UILayer::initializeObjectList() {
    // ������Ʒ������
    objectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - objectListLayer->getContentSize().height / 2));
    this->addChild(objectListLayer, 0);

    // ����ɾ����Ʒ��ť
    deleteObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/DefaultGarbageBinButton.png",
        "../Resources/UI/HoverGarbageBinButton.png",
        [this](cocos2d::Ref* sender) { character->deleteCurrentObject(); }
    );
    deleteObjectButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 2));
    this->addChild(deleteObjectButton, 0);  // ��ť����Ʒ������

    // �����ر���Ʒ����ť
    closeObjectListButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        [this](cocos2d::Ref* sender) { character->setObjectListStatus(false); }
    );
    closeObjectListButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height * 3 / 5));
    this->addChild(closeObjectListButton, 0);  // ��ť����Ʒ������
}

void UILayer::updateObjectList() {
    // ��ȡ��ɫ����Ʒ��״̬�ʹ��ڴ�С
    const auto objectListStatus = character->getObjectListStatus();
    if (objectListLayer != nullptr) {
        this->removeChild(objectListLayer);
    }

    // ���ݽ�ɫ����Ʒ��״̬��ʼ����Ʒ������
    if (!objectListStatus) {
        objectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
        objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - objectListLayer->getContentSize().height / 2));
        deleteObjectButton->setVisible(false);
        closeObjectListButton->setVisible(false);
    }
    else {
        objectListLayer = Sprite::create("../Resources/UI/ObjectList.png");
        objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        deleteObjectButton->setVisible(true);
        closeObjectListButton->setVisible(true);
    }
    this->addChild(objectListLayer, 0);
}

// ��ʼ��ʱ����ʾ��
void UILayer::initializeTimeDisplay() {
    character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");

    // ��ȡ�ɼ������С
    visibleSize = Director::getInstance()->getVisibleSize();

    // �������Ͻǵ�λ��
    const Vec2 rightTopPos = Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f);  // ���Ͻǣ����������ʵ�ƫ����

    // ��������ͼƬ
    timeDisplayLayer = Sprite::create("../Resources/UI/timetable.png");

    // ��ȡԭʼͼƬ�ߴ�
    const Size originalTimeDisplaySize = timeDisplayLayer->getContentSize();

    // �������ű�����ʹ��ͼƬ��Ӧ 16x16 ����
    const float scaleX = UI_SCALE / originalTimeDisplaySize.width;  // ���� X ��������ű���
    const float scaleY = UI_SCALE / originalTimeDisplaySize.height; // ���� Y ��������ű���

    // �������ű���
    timeDisplayLayer->setScale(scaleX, scaleY);

    // ���ñ���ͼƬλ��
    timeDisplayLayer->setPosition(rightTopPos);

    // ��ӵ�����
    this->addChild(timeDisplayLayer, 0);  // �����ڵײ�

    // �����ǩ��λ�ã�ʹ������ڱ���λ��
    const Vec2 labelPos1 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y + originalTimeDisplaySize.height * scaleY * 0.35f);  // �ڱ���ͼƬ�Ķ���
    const Vec2 labelPos2 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y - originalTimeDisplaySize.height * scaleY * 0.05f);  // �� labelPos1 ����ƫ�� 30

    // ��������ʼ�� timeLabel1 �� timeLabel2
    timeLabel1 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    timeLabel1->setPosition(labelPos1);  // ���� timeLabel1 ����ڱ���ͼƬ������λ��
    this->addChild(timeLabel1, 1);  // ��ǩ�ڱ�������

    timeLabel2 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    timeLabel2->setPosition(labelPos2);  // ���� timeLabel2 ����� timeLabel1 ��λ��
    this->addChild(timeLabel2, 1);  // ��ǩ�ڱ�������
}

// ����ʱ����ʾ��
void UILayer::updateTimeDisplay() {
    // ��ȡ TimeManager ��ʵ��
    const TimeManager* timeManager = TimeManager::getInstance();

    // ��ȡ������������Ϣ�����ں����ڣ�
    std::string weekDay = timeManager->getWeekDay();
    timeLabel1->setString(weekDay);  // ��ʾ���ڼ� 

    // ��ȡ������ʱ����Ϣ������/���Ϻ͵�ǰʱ�䣩
    const bool isDaytime = timeManager->isDaytime();
    std::string dayOrNight = isDaytime ? "����" : "����";
    std::string timeOfDay = timeManager->getCurrentTime();
}

// ����UI����
void UILayer::update(float deltaTime) {
    // ������Ʒ��
    updateObjectList();
    // ����ʱ����ʾ��
    updateTimeDisplay();
}