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
#include "Classes/LocationMap/LocationMap.h"

USING_NS_CC;


// ��������
UILayer::~UILayer() {
    delete character;
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
    character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");

    //selectObjectSpriteMarker = Sprite::create("../Resources/UI/SelectionMarker.png");
    visibleSize = Director::getInstance()->getVisibleSize();
    initializeObjectList();
    showObjectImage();
  
    initializeTimeDisplay();
    return true;
}

// ���¼����¼���������
void UILayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    const auto seletedObjectInfo = character->getCurrentObject();
    const int index = seletedObjectInfo.index;
    const auto objectListStatus = character->getObjectListStatus();
    if (!objectListStatus) {
        selectObjectSpriteMarker[index]->setVisible(true);
    }
    else {
        selectObjectSpriteMarker[index]->setVisible(false);
    }
    selectObjectSpriteMarker[lastSelectedObjectIndex]->setVisible(false);
    lastSelectedObjectIndex = index;
}

// ��ʼ����Ʒ��
void UILayer::initializeObjectList() {
    // ������Ʒ������
    objectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - objectListLayer->getContentSize().height / 2));
    this->addChild(objectListLayer, UI_LAYER_GRADE);

    // ������Ʒ��ѡ�п�
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        selectObjectSpriteMarker[i] = Sprite::create("../Resources/UI/SelectionMarker.png");
        selectObjectSpriteMarker[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
        this->addChild(selectObjectSpriteMarker[i], OBJECT_LAYER_GRADE);
        selectObjectSpriteMarker[i]->setVisible(false);
    }
    selectObjectSpriteMarker[0]->setVisible(true);
    lastSelectedObjectIndex = 0;

    // ����ɾ����Ʒ��ť
    deleteObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/DefaultGarbageBinButton.png",
        "../Resources/UI/HoverGarbageBinButton.png",
        [this](cocos2d::Ref* sender) { character->setObjectListStatus(false);  }
    );//character->deleteCurrentObject();
    deleteObjectButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 2));
    this->addChild(deleteObjectButton, UI_LAYER_GRADE); 
    deleteObjectButton->setVisible(false);

    // �����ر���Ʒ����ť
    closeObjectListButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        [this](cocos2d::Ref* sender) { character->setObjectListStatus(false); }
    );
    closeObjectListButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height * 3 / 5));
    this->addChild(closeObjectListButton, UI_LAYER_GRADE); 
    closeObjectListButton->setVisible(false);
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
    this->addChild(objectListLayer, UI_LAYER_GRADE);
    lastObjectListStatus = objectListStatus;
}

// ��ʾ��ƷͼƬ
void UILayer::showObjectImage() {
    const auto objectListStatus = character->getObjectListStatus();
    if (!objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            const auto objectInfo = character->findObjectAtPosition(i);
            if (objectInfo.count != 0) {
                const auto objectSprite = objectInfo.objectNode.object->_fileName;
                closedObjectSpriteImage[i] = Sprite::create(objectSprite);
                closedObjectSpriteImage[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
                closedObjectSpriteImage[i]->setScale(OBJECT_NODE_SCALE);
                this->addChild(closedObjectSpriteImage[i], OBJECT_LAYER_GRADE);  // ��ƷͼƬ����Ʒ������
            }
        }
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                if(openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]!= nullptr)
                    this->removeChild(openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]);
            }
        }
    }
    else {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                const auto objectInfo = character->findObjectAtPosition(i* OBJECT_LIST_COLS + j);
                if (objectInfo.count != 0) {
                    const auto objectSprite = objectInfo.objectNode.object->_fileName;
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j] = Sprite::create(objectSprite);
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setPosition(LocationMap::getInstance().getLocationMap().at(i* OBJECT_LIST_COLS + j));
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setScale(OBJECT_NODE_SCALE);
                    this->addChild(openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], OBJECT_LAYER_GRADE);  // ��ƷͼƬ����Ʒ������
                }
            }
        }
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if(closedObjectSpriteImage[i]!= nullptr)
          this->removeChild(closedObjectSpriteImage[i]);
        }
    }
}

// ��ʾ��ǰѡ�е���Ʒ
//void UILayer::showSelectedObject(Vec2 position) {
//    const auto objectListStatus = character->getObjectListStatus();
//    if (selectObjectSpriteMarker != nullptr ) {
//        this->removeChild(selectObjectSpriteMarker);
//    }
//
//    if (!objectListStatus) {
//        selectObjectSpriteMarker = Sprite::create("../Resources/UI/SelectionMarker.png");
//        const auto seletedObjectInfo = character->getCurrentObject();
//        selectObjectSpriteMarker->setPosition(position);
//        this->addChild(selectObjectSpriteMarker, OBJECT_LAYER_GRADE);  
//    }
//}

// ��ʼ��ʱ����ʾ��
void UILayer::initializeTimeDisplay() {
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
    this->addChild(timeDisplayLayer, UI_LAYER_GRADE);  

    // �����ǩ��λ�ã�ʹ������ڱ���λ��
    const Vec2 labelPos1 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y + originalTimeDisplaySize.height * scaleY * 0.35f);  // �ڱ���ͼƬ�Ķ���
    const Vec2 labelPos2 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y - originalTimeDisplaySize.height * scaleY * 0.05f);  // �� labelPos1 ����ƫ�� 30

    // ��������ʼ�� timeLabel1 �� timeLabel2
    timeLabel1 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    timeLabel1->setPosition(labelPos1);  
    this->addChild(timeLabel1, UI_LAYER_GRADE);  

    timeLabel2 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    timeLabel2->setPosition(labelPos2); 
    this->addChild(timeLabel2, UI_LAYER_GRADE);  
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
    const auto objectListStatus = character->getObjectListStatus();
    //CCLOG("objectListStatus = %d, lastObjectListStatus = %d", objectListStatus, lastObjectListStatus);
    if (objectListStatus != lastObjectListStatus) {
        updateObjectList();
        showObjectImage();
    }
    // ����ʱ����ʾ��
    updateTimeDisplay();
}

// Ѱ������ɷ�������
Vec2 UILayer::findNearestPoint(cocos2d::Sprite* objectSprite) {
    float minDistance = FLT_MAX;
    Vec2 nearestPoint;

    const Vec2 currentPos = objectSprite->getPosition();
    const auto objectListStatus = character->getObjectListStatus();
  
    if (!objectListStatus) {// ��Ʒ���ر�

    }
    else {  // ��Ʒ����
        for (const auto& point : LocationMap::getInstance().getLocationMap()) {
            const int currentLocation = point.first;
            bool isEmpty = true;
            for (int i = 0; i < OBJECT_LIST_COLS; i++) {
                for (int j = 0; j < OBJECT_LIST_ROWS; j++) {
                    const auto objectInfo = character->findObjectAtPosition(i * OBJECT_LIST_ROWS + j);
                    if (objectInfo.count != 0) {
                        isEmpty = false;
                    }
                }
            }
            if (isEmpty) {
                const Vec2& emptyPoint = point.second;
                const float distance = currentPos.distance(emptyPoint);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPoint = emptyPoint;
                }
            }
        }
    }
    return nearestPoint;
}