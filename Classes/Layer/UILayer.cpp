/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI界面UILayer类的实现
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/9
 * License:       MIT License
 ****************************************************************/
#include "UILayer.h"
#include "Classes/Character/Character.h"
#include "Classes/LocationMap/LocationMap.h"

USING_NS_CC;


// 析构函数
UILayer::~UILayer() {
    delete character;
    delete objectListLayer;
    delete timeLabel1;
    delete timeLabel2;
    delete timeDisplayLayer;
}

// 初始化UI层
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

// 按下键盘事件触发函数
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

// 初始化物品栏
void UILayer::initializeObjectList() {
    // 创建物品栏背景
    objectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    objectListLayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - objectListLayer->getContentSize().height / 2));
    this->addChild(objectListLayer, UI_LAYER_GRADE);

    // 创建物品栏选中框
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        selectObjectSpriteMarker[i] = Sprite::create("../Resources/UI/SelectionMarker.png");
        selectObjectSpriteMarker[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
        this->addChild(selectObjectSpriteMarker[i], OBJECT_LAYER_GRADE);
        selectObjectSpriteMarker[i]->setVisible(false);
    }
    selectObjectSpriteMarker[0]->setVisible(true);
    lastSelectedObjectIndex = 0;

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

void UILayer::updateObjectList() {
    // 获取角色的物品栏状态和窗口大小
    const auto objectListStatus = character->getObjectListStatus();
    if (objectListLayer != nullptr) {
        this->removeChild(objectListLayer);
    }

    // 根据角色的物品栏状态初始化物品栏背景
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

// 显示物品图片
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
                this->addChild(closedObjectSpriteImage[i], OBJECT_LAYER_GRADE);  // 物品图片在物品栏上面
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
                    this->addChild(openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], OBJECT_LAYER_GRADE);  // 物品图片在物品栏上面
                }
            }
        }
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if(closedObjectSpriteImage[i]!= nullptr)
          this->removeChild(closedObjectSpriteImage[i]);
        }
    }
}

// 显示当前选中的物品
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
    std::string dayOrNight = isDaytime ? "白天" : "晚上";  
    std::string timeOfDay = timeManager->getCurrentTime();  
}

// 更新UI界面
void UILayer::update(float deltaTime) {
    // 更新物品栏
    const auto objectListStatus = character->getObjectListStatus();
    //CCLOG("objectListStatus = %d, lastObjectListStatus = %d", objectListStatus, lastObjectListStatus);
    if (objectListStatus != lastObjectListStatus) {
        updateObjectList();
        showObjectImage();
    }
    // 更新时间显示器
    updateTimeDisplay();
}

// 寻找最近可放置坐标
Vec2 UILayer::findNearestPoint(cocos2d::Sprite* objectSprite) {
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