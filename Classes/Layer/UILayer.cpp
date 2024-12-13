/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI界面UILayer类的实现
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/11
 * License:       MIT License
 ****************************************************************/
#include "UILayer.h"
#include "Classes/Character/Character.h"
#include "Classes/LocationMap/LocationMap.h"

USING_NS_CC;

// 构造函数
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

    // 鼠标事件监听器
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(UILayer::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(UILayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(UILayer::onMouseUp, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

// 析构函数
UILayer::~UILayer() {
    //delete character;
    //delete objectListLayer;
    //delete timeLabel1;
    //delete timeLabel2;
    //delete timeDisplayLayer;
    //delete deleteObjectButton;
    //delete closeObjectListButton;
}

// 初始化UI层
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    initializeObjectList();
    showObjectImage();
    initializeTimeDisplay();
    return true;
}

// 初始化物品栏
void UILayer::initializeObjectList() {
    // 创建物品栏背景
    closedobjectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    closedobjectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - closedobjectListLayer->getContentSize().height / 2));
    this->addChild(closedobjectListLayer, UI_LAYER_GRADE);

    openedobjectListLayer = Sprite::create("../Resources/UI/ObjectList.png");
    openedobjectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(openedobjectListLayer, UI_LAYER_GRADE);
    openedobjectListLayer->setVisible(false);

    // 创建物品栏选中框
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        selectObjectSpriteMarker[i] = Sprite::create("../Resources/UI/SelectionMarker.png");
        selectObjectSpriteMarker[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
        this->addChild(selectObjectSpriteMarker[i], OBJECT_LAYER_GRADE);
        selectObjectSpriteMarker[i]->setVisible(false);
    }
    selectObjectSpriteMarker[0]->setVisible(true);

    // 创建删除物品按钮
    deleteObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/DefaultGarbageBinButton.png",
        "../Resources/UI/HoverGarbageBinButton.png",
        [this](cocos2d::Ref* sender) { character->setObjectListStatus(false);  }
    );//character->deleteCurrentObject();
    deleteObjectButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 2));
    this->addChild(deleteObjectButton, UI_LAYER_GRADE);
    deleteObjectButton->setVisible(false);

    // 创建关闭物品栏按钮
    closeObjectListButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        [this](cocos2d::Ref* sender) { character->setObjectListStatus(false); }
    );
    closeObjectListButton->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height * 3 / 5));
    this->addChild(closeObjectListButton, UI_LAYER_GRADE);
    closeObjectListButton->setVisible(false);
}

// 更新物品栏
void UILayer::updateObjectList() {
    // 获取角色的物品栏状态和窗口大小
    const auto objectListStatus = character->getObjectListStatus();
    const int index = character->getCurrentObjectIndex();
    // 根据角色的物品栏状态初始化物品栏背景
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


    // 显示物品图片
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

    // 按下鼠标事件触发函数
    void UILayer::onMouseDown(cocos2d::Event * event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 location = mouseEvent->getLocationInView();
        objectListStatus = character->getObjectListStatus();
        selectedObjectSprite = nullptr;

        // 当物品栏被打开时才会检测
        if (objectListStatus) {
            for (int i = 0; i < OBJECT_LIST_ROWS * OBJECT_LIST_COLS; i++) {
                const auto sprite = openedObjectSpriteImage[i];
                //TODO:空指针
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
            // 标记选中状态
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

                // 创建放置标记层
                placementMarkerLayer = PlacementMarkerLayer::create();
                placementMarkerLayer->showPlacementMarker();
                this->addChild(placementMarkerLayer, OBJECT_LAYER_GRADE);
            }
        }
    }

    // 移动鼠标事件触发函数
    void UILayer::onMouseMove(cocos2d::Event * event) {
        objectListStatus = character->getObjectListStatus();
        if (objectListStatus) {
            if (selectedObjectSprite != nullptr) {
                if (nearestPlacementMarker != nullptr) {
                    nearestPlacementMarker->setPosition(findNearestPoint(selectedObjectSprite));
                    nearestPlacementMarker->setVisible(true);
                }


    

                // 移动物品
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


    // 释放鼠标事件触发函数
    void UILayer::onMouseUp(cocos2d::Event * event) {
        objectListStatus = character->getObjectListStatus();
        if (objectListStatus) {
            if (selectedObjectSprite != nullptr) {
                // 取消选中状态
                selectedObjectSprite->setUserData(nullptr);
                nearestPlacementMarker->removeFromParent();
                nearestPlacementMarker = nullptr;

                // 删除当前物品
                bool isDelete = false;
                const Vec2 currentPos = selectedObjectSprite->getPosition();
                if (currentPos.x >= OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY &&
                    currentPos.x <= OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY &&
                    currentPos.y >= OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY &&
                    currentPos.y <= OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY) {
                    isDelete = true;
                }

                if (!isDelete) {
                    // 遍历所有可放置位置
                    Vec2 nearestPoint = findNearestPoint(selectedObjectSprite);

                    // 确定物品移动目标位置属性
                    int targetLocation = -1;
                    for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                        if (pair.second.equals(nearestPoint)) {
                            targetLocation = pair.first;
                            break;
                        }
                    }

                    // 更新物品栏
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
                // 关闭放置标记层
                this->removeChild(placementMarkerLayer);
                placementMarkerLayer = nullptr;
                selectedObjectSprite = nullptr;
            }
        }
    }

    // 按下键盘事件触发函数
    void UILayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {


        const int index = character->getCurrentObjectIndex();

        objectListStatus = character->getObjectListStatus();
        setSelectObjectSpriteMarker(lastSelectedObjectIndex, false);
        if (!objectListStatus) {
            setSelectObjectSpriteMarker(index, true);
            // 有物品丢弃，需要更新物品栏
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

    // 初始化时间显示器
    void UILayer::initializeTimeDisplay() {
        // 获取可见区域大小
        visibleSize = Director::getInstance()->getVisibleSize();

        // 计算右上角的位置
        const Vec2 rightTopPos = Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f);  // 右上角，调整到合适的偏移量

        // 创建背景图片
        timeDisplayLayer = Sprite::create("../Resources/UI/timetable.png");

        // 获取原始图片尺寸
        const Size originalTimeDisplaySize = timeDisplayLayer->getContentSize();

        // 计算缩放比例，使得图片适应 16x16 像素
        const float scaleX = UI_SCALE / originalTimeDisplaySize.width;  // 计算 X 方向的缩放比例
        const float scaleY = UI_SCALE / originalTimeDisplaySize.height; // 计算 Y 方向的缩放比例

        // 设置缩放比例
        timeDisplayLayer->setScale(scaleX, scaleY);

        // 设置背景图片位置
        timeDisplayLayer->setPosition(rightTopPos);

        // 添加到场景

        this->addChild(timeDisplayLayer, UI_LAYER_GRADE);


        // 计算标签的位置，使其相对于背景位置
        const Vec2 labelPos1 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y + originalTimeDisplaySize.height * scaleY * 0.35f);  // 在背景图片的顶部
        const Vec2 labelPos2 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.05, rightTopPos.y - originalTimeDisplaySize.height * scaleY * 0.05f);  // 在 labelPos1 下面偏移 30

        // 创建并初始化 timeLabel1 和 timeLabel2
        timeLabel1 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
        timeLabel1->setPosition(labelPos1);
        this->addChild(timeLabel1, UI_LAYER_GRADE);

        timeLabel2 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
        timeLabel2->setPosition(labelPos2);
        this->addChild(timeLabel2, UI_LAYER_GRADE);
    }

    // 更新时间显示器
    void UILayer::updateTimeDisplay() {
        // 获取 TimeManager 的实例
        const TimeManager* timeManager = TimeManager::getInstance();

        // 获取并更新日期信息（星期和日期）
        std::string weekDay = timeManager->getWeekDay();
        timeLabel1->setString(weekDay);  // 显示星期几 

        // 获取并更新时间信息（白天/晚上和当前时间）
        const bool isDaytime = timeManager->isDaytime();

        std::string dayOrNight = isDaytime ? "Day" : "Night";
        std::string timeOfDay = timeManager->getCurrentTime();
        timeLabel2->setString(dayOrNight + " " + timeOfDay);  // 显示白天/晚上和当前时间  的代码部分

    }

    // 更新UI界面
    void UILayer::update(float deltaTime) {
        // 更新物品栏
        objectListStatus = character->getObjectListStatus();
        if (objectListStatus != lastObjectListStatus) {
            updateObjectList();
            showObjectImage();
        }
        // 更新时间显示器
        updateTimeDisplay();
    }


    // 寻找最近可放置坐标
    Vec2 UILayer::findNearestPoint(cocos2d::Sprite * objectSprite) {
        float minDistance = FLT_MAX;
        Vec2 nearestPoint;

        const Vec2 currentPos = objectSprite->getPosition();
        const auto objectListStatus = character->getObjectListStatus();

        if (!objectListStatus) {// 物品栏关闭

        }
        else {  // 物品栏打开
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

    // 设置选中物品标记框的显示状态
    void UILayer::setSelectObjectSpriteMarker(int index, bool show) {
        if (index >= OBJECT_LIST_COLS)

            selectObjectSpriteMarker[0]->setVisible(show);
        else
            selectObjectSpriteMarker[index]->setVisible(show);
    }