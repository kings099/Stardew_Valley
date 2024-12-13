/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI����UILayer���ʵ��
 * Author:        ��˼����ϳ�
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "UILayer.h"
#include "Classes/Character/Character.h"
#include "Classes/LocationMap/LocationMap.h"

USING_NS_CC;

// ���캯��
UILayer::UILayer() :
    timeLabel1(nullptr),
    timeLabel2(nullptr),
    timeDisplayLayer(nullptr),
    deleteObjectButton(nullptr),
    closeObjectListButton(nullptr),
    selectedObjectSprite(nullptr),
    lastSelectedObjectIndex(0),
    objectListStatus(false),
    lastObjectListStatus(false),
    startLocation(-1),
    placementMarkerLayer(nullptr),
    nearestPlacementMarker(nullptr)
{
    character = Character::getInstance(".. / Resources / Characters / Elimy / ElimyDown1.png");
    visibleSize = Director::getInstance()->getVisibleSize();
    std::fill_n(selectObjectSpriteMarker, OBJECT_LIST_COLS, nullptr);
    std::fill_n(closedObjectSpriteImage, OBJECT_LIST_COLS, nullptr);
    std::fill_n(openedObjectSpriteImage, OBJECT_LIST_COLS * OBJECT_LIST_ROWS, nullptr);

    // ����¼�������
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(UILayer::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(UILayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(UILayer::onMouseUp, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

// ��������
UILayer::~UILayer() {
    //delete character;
    //delete objectListLayer;
    //delete timeLabel1;
    //delete timeLabel2;
    //delete timeDisplayLayer;
    //delete deleteObjectButton;
    //delete closeObjectListButton;
}

// ��ʼ��UI��
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    initializeObjectList();
    showObjectImage();
    initializeTimeDisplay();
    return true;
}

// ��ʼ����Ʒ��
void UILayer::initializeObjectList() {
    // ������Ʒ������
    closedobjectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    closedobjectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - closedobjectListLayer->getContentSize().height / 2));
    this->addChild(closedobjectListLayer, UI_LAYER_GRADE);

    openedobjectListLayer = Sprite::create("../Resources/UI/ObjectList.png");
    openedobjectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(openedobjectListLayer, UI_LAYER_GRADE);
    openedobjectListLayer->setVisible(false);

    // ������Ʒ��ѡ�п�
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        selectObjectSpriteMarker[i] = Sprite::create("../Resources/UI/SelectionMarker.png");
        selectObjectSpriteMarker[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
        this->addChild(selectObjectSpriteMarker[i], OBJECT_LAYER_GRADE);
        selectObjectSpriteMarker[i]->setVisible(false);
    }
    selectObjectSpriteMarker[0]->setVisible(true);

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

// ������Ʒ��
void UILayer::updateObjectList() {
    // ��ȡ��ɫ����Ʒ��״̬�ʹ��ڴ�С
    const auto objectListStatus = character->getObjectListStatus();
    const int index = character->getCurrentObjectIndex();
    // ���ݽ�ɫ����Ʒ��״̬��ʼ����Ʒ������
    if (!objectListStatus) {
        closedobjectListLayer->setVisible(true);
        openedobjectListLayer->setVisible(false);
        deleteObjectButton->setVisible(false);
        closeObjectListButton->setVisible(false);

        setSelectObjectSpriteMarker(index, true);
    }
    else {
        closedobjectListLayer->setVisible(false);
        openedobjectListLayer->setVisible(true);
        deleteObjectButton->setVisible(true);
        closeObjectListButton->setVisible(true);
        setSelectObjectSpriteMarker(index, false);
    }
    lastObjectListStatus = objectListStatus;
}


// ��ʾ��ƷͼƬ
void UILayer::showObjectImage() {
    objectListStatus = character->getObjectListStatus();
    if (!objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            const auto objectInfo = character->findObjectAtPosition(i);
            if (objectInfo.count != 0) {
                const auto objectSprite = objectInfo.objectNode.object->_fileName;
                closedObjectSpriteImage[i] = Sprite::create(objectSprite);
                closedObjectSpriteImage[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
                closedObjectSpriteImage[i]->setScale(OBJECT_NODE_SCALE);
                this->addChild(closedObjectSpriteImage[i], OBJECT_LAYER_GRADE);
            }
        }
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                if (openedObjectSpriteImage[i * OBJECT_LIST_COLS + j] != nullptr)
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setVisible(false);
            }
        }
    }
    else {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {

                const auto objectInfo = character->findObjectAtPosition(i * OBJECT_LIST_COLS + j);

                if (objectInfo.count != 0) {
                    const auto objectSprite = objectInfo.objectNode.object->_fileName;
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j] = Sprite::create(objectSprite);
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setPosition(LocationMap::getInstance().getLocationMap().at(i * OBJECT_LIST_COLS + j));
                    openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setScale(OBJECT_NODE_SCALE);
                    this->addChild(openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], OBJECT_LAYER_GRADE);

                }
            }
        }
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if (closedObjectSpriteImage[i] != nullptr)
                closedObjectSpriteImage[i]->setVisible(false);
        }
    }
}



// ��������¼���������
void UILayer::onMouseDown(cocos2d::Event* event) {
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Vec2 location = mouseEvent->getLocationInView();
    objectListStatus = character->getObjectListStatus();
    selectedObjectSprite = nullptr;

    // ����Ʒ������ʱ�Ż���
    if (objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS * OBJECT_LIST_COLS; i++) {
            const auto sprite = openedObjectSpriteImage[i];
            //TODO:��ָ��
            if (sprite != nullptr) {
                const Vec2 spritePos = sprite->getPosition();
                const Size spriteSize = sprite->getContentSize();
                if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT &&
                    location.x >= (spritePos.x - spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.x <= (spritePos.x + spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.y >= (spritePos.y - spriteSize.height * OBJECT_NODE_SCALE / 2) &&
                    location.y <= (spritePos.y + spriteSize.height * OBJECT_NODE_SCALE / 2)) {
                    selectedObjectSprite = sprite;
                    break;
                }
            }
        }
    }

    if (selectedObjectSprite) {
        // ���ѡ��״̬
        if (objectListStatus) {
            selectedObjectSprite->setUserData(reinterpret_cast<void*>(1));
            nearestPlacementMarker = Sprite::create("../Resources/UI/NearestPlacementMarker.png");
            nearestPlacementMarker->setVisible(false);
            this->addChild(nearestPlacementMarker, OBJECT_LAYER_GRADE + 1);

            for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                if (pair.second.equals(selectedObjectSprite->getPosition())) {
                    startLocation = pair.first;
                    break;
                }
            }
            character->setCurrentObject(startLocation);

            // �������ñ�ǲ�
            placementMarkerLayer = PlacementMarkerLayer::create();
            placementMarkerLayer->showPlacementMarker();
            this->addChild(placementMarkerLayer, OBJECT_LAYER_GRADE);
        }
    }
}

// �ƶ�����¼���������
void UILayer::onMouseMove(cocos2d::Event* event) {
    objectListStatus = character->getObjectListStatus();
    if (objectListStatus) {
        if (selectedObjectSprite != nullptr) {
            if (nearestPlacementMarker != nullptr) {
                nearestPlacementMarker->setPosition(findNearestPoint(selectedObjectSprite));
                nearestPlacementMarker->setVisible(true);
            }

            // �ƶ���Ʒ
            EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
            Vec2 location = mouseEvent->getLocationInView();
            if (location.x >= OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY &&
                location.x <= OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY &&
                location.y >= OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY &&
                location.y <= OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY) {
                nearestPlacementMarker->setVisible(false);
            }
            selectedObjectSprite->setPosition(location);
        }
    }
}

// �ͷ�����¼���������
void UILayer::onMouseUp(cocos2d::Event* event) {
    objectListStatus = character->getObjectListStatus();
    if (objectListStatus) {
        if (selectedObjectSprite != nullptr) {
            // ȡ��ѡ��״̬
            selectedObjectSprite->setUserData(nullptr);
            nearestPlacementMarker->removeFromParent();
            nearestPlacementMarker = nullptr;

            // ɾ����ǰ��Ʒ
            bool isDelete = false;
            const Vec2 currentPos = selectedObjectSprite->getPosition();
            if (currentPos.x >= OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY &&
                currentPos.x <= OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY &&
                currentPos.y >= OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY &&
                currentPos.y <= OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY) {
                isDelete = true;
            }

            if (!isDelete) {
                // �������пɷ���λ��
                Vec2 nearestPoint = findNearestPoint(selectedObjectSprite);

                // ȷ����Ʒ�ƶ�Ŀ��λ������
                int targetLocation = -1;
                for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                    if (pair.second.equals(nearestPoint)) {
                        targetLocation = pair.first;
                        break;
                    }
                }

                // ������Ʒ��
                character->swapObject(startLocation, targetLocation);
                cocos2d::Sprite* currentObjectSprite;

                currentObjectSprite = openedObjectSpriteImage[startLocation];
                openedObjectSpriteImage[startLocation] = nullptr;
                this->removeChild(openedObjectSpriteImage[startLocation]);
                openedObjectSpriteImage[targetLocation] = currentObjectSprite;
                selectedObjectSprite->setPosition(nearestPoint);
                //this->addChild(openedObjectSpriteImage[targetLocation], OBJECT_LAYER_GRADE); 
            }
            else {
                selectedObjectSprite->setVisible(false);
                character->deleteCurrentObject();
            }
            // �رշ��ñ�ǲ�
            this->removeChild(placementMarkerLayer);
            placementMarkerLayer = nullptr;
            selectedObjectSprite = nullptr;
        }
    }
}

// ���¼����¼���������
void UILayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    const int index = character->getCurrentObjectIndex();

    objectListStatus = character->getObjectListStatus();
    setSelectObjectSpriteMarker(lastSelectedObjectIndex, false);
    if (!objectListStatus) {
        setSelectObjectSpriteMarker(index, true);
        // ����Ʒ��������Ҫ������Ʒ��
        if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
            if (closedObjectSpriteImage[index] != nullptr) {
                closedObjectSpriteImage[index]->setVisible(false);
                this->removeChild(closedObjectSpriteImage[index]);
                closedObjectSpriteImage[index] = nullptr;
            }
        }
    }
    else {
        setSelectObjectSpriteMarker(index, false);
    }
    lastSelectedObjectIndex = index;
}

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

    std::string dayOrNight = isDaytime ? "Day" : "Night";
    std::string timeOfDay = timeManager->getCurrentTime();
    timeLabel2->setString(dayOrNight + " " + timeOfDay);  // ��ʾ����/���Ϻ͵�ǰʱ��  �Ĵ��벿��

}



// ����UI����
void UILayer::update(float deltaTime) {
    // ������Ʒ��
    objectListStatus = character->getObjectListStatus();
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
            const auto objectInfo = character->findObjectAtPosition(currentLocation);
            if (objectInfo.count != 0) {
                isEmpty = false;
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

// ����ѡ����Ʒ��ǿ����ʾ״̬
void UILayer::setSelectObjectSpriteMarker(int index, bool show) {
    if (index >= OBJECT_LIST_COLS)

        selectObjectSpriteMarker[0]->setVisible(show);
    else
        selectObjectSpriteMarker[index]->setVisible(show);
}