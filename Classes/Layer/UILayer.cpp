#include "UILayer.h"

USING_NS_CC;


// ��������
UILayer::~UILayer() {
    delete objectListBackground;
}

// ��ʼ��UI��
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

// ��ʼ����Ʒ��
void UILayer::initializeObjectList() {

    // ��ȡ��ɫ����Ʒ��״̬�ʹ��ڴ�С
    const auto objectListStatus = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png")->checkObjectListStatus();
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (objectListBackground != nullptr) {
        this->removeChild(objectListBackground);
    }

    // ���ݽ�ɫ����Ʒ��״̬��ʼ����Ʒ������
    if (!objectListStatus) {
        objectListBackground = Sprite::create("../Resources/UI/ObjectListRow.png");
    }
    else {
        objectListBackground = Sprite::create("../Resources/UI/ObjectList.png");
    }

    // ����λ�ò���ӵ�����
    if (objectListBackground != nullptr) {
        objectListBackground->setPosition(Vec2(0, 0));
        this->addChild(objectListBackground);
        objectListBackground->setScale(2.0f);
    }
}

// ����UI����
void UILayer::update(float deltaTime) {
    initializeObjectList(); 
}