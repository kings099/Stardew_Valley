/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI界面UILayer类的实现
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#include <algorithm>
#include "UILayer.h"
#include "Classes/Character/Character.h"
#include "Classes/LocationMap/LocationMap.h"
#include "Classes/Scene/GameMainScene.h"

USING_NS_CC;

// 构造函数
UILayer::UILayer() :
    _timeLabel1(nullptr),
    _timeLabel2(nullptr),
    _timeDisplayLayer(nullptr),
    _closedObjectListLayer(nullptr),
    _openedObjectListLayer(nullptr),
    _selectedObjectSprite(nullptr),
    _skillLevelBoard(nullptr),
    _nearestPlacementMarker(nullptr),
    _deleteObjectButton(nullptr),
    _closeObjectListButton(nullptr),
    _exitButton(nullptr),
    _placementMarkerLayer(nullptr),
    _currentObjectQuantityLabel(nullptr),
    _objectListStatus(false),
    _lastObjectListStatus(false),
    _boxObjectListStatus(false),
    _lastSelectedObjectIndex(0),
    _startLocation(-1)
{
    _character = Character::getInstance("../Resources/Characters/Bear/BearDownAction1.png");
    _visibleSize = Director::getInstance()->getVisibleSize();
    std::fill_n(_selectObjectSpriteMarker, OBJECT_LIST_COLS, nullptr);
    std::fill_n(_closedObjectSpriteImage, OBJECT_LIST_COLS, nullptr);
    std::fill_n(_openedObjectSpriteImage, OBJECT_LIST_COLS * OBJECT_LIST_ROWS, nullptr);
    std::fill_n(_skillLevelStar, SKILL_KIND_NUM * SKILL_LEVEL_NUM, nullptr);
    std::fill_n(_closedObjectQuantityLabels, OBJECT_LIST_COLS, nullptr);
    std::fill_n(_openedObjectQuantityLabels, OBJECT_LIST_COLS * OBJECT_LIST_ROWS, nullptr);
    std::fill_n(_boxObjectQuantityLabels, OBJECT_LIST_COLS, nullptr);

    // 鼠标事件监听器
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(UILayer::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(UILayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(UILayer::onMouseUp, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

}

// 析构函数
UILayer::~UILayer() {
    //delete _character;
    //delete _objectListLayer;
    //delete _timeLabel1;
    //delete _timeLabel2;
    //delete _timeDisplayLayer;
    //delete _deleteObjectButton;
    //delete _closeObjectListButton;
}

// 初始化UI层
bool UILayer::init() {
    if (!Layer::init()) {
        return false;
    }
    initializeObjectList();
    showObjectImage();
    initializeSkillBoard();
    initializeTimeDisplay();
    return true;
}

// 初始化物品栏
void UILayer::initializeObjectList() {
    // 创建物品栏背景
    _closedObjectListLayer = Sprite::create("../Resources/UI/ObjectListRow.png");
    _closedObjectListLayer->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height - _closedObjectListLayer->getContentSize().height / 2));
    this->addChild(_closedObjectListLayer, UI_LAYER_GRADE);

    _openedObjectListLayer = Sprite::create("../Resources/UI/ObjectList.png");
    _openedObjectListLayer->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
    this->addChild(_openedObjectListLayer, UI_LAYER_GRADE);
    _openedObjectListLayer->setVisible(false);

    _boxObjectListLayer = Sprite::create("../Resources/UI/BoxList.png");
    _boxObjectListLayer->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height*3/5));
    this->addChild(_boxObjectListLayer, UI_LAYER_GRADE);
    _boxObjectListLayer->setVisible(false);

    // 创建物品栏选中框
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        _selectObjectSpriteMarker[i] = Sprite::create("../Resources/UI/SelectionMarker.png");
        _selectObjectSpriteMarker[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
        this->addChild(_selectObjectSpriteMarker[i], OBJECT_LAYER_GRADE);
        _selectObjectSpriteMarker[i]->setVisible(false);
    }
    _selectObjectSpriteMarker[0]->setVisible(true);

    // 创建删除物品按钮
    _deleteObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/DefaultGarbageBinButton.png",
        "../Resources/UI/HoverGarbageBinButton.png",
        [this](cocos2d::Ref* sender) { _character->setObjectListStatus(false);  }
    );//character->deleteCurrentObject();
    _deleteObjectButton->setPosition(Vec2(_visibleSize.width * 2 / 3, _visibleSize.height / 2));
    this->addChild(_deleteObjectButton, UI_LAYER_GRADE);
    _deleteObjectButton->setVisible(false);

    // 创建关闭物品栏按钮
    _closeObjectListButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        [this](cocos2d::Ref* sender) { _character->setObjectListStatus(false); }
    );
    _closeObjectListButton->setPosition(Vec2(_visibleSize.width * 2 / 3, _visibleSize.height * 3 / 5));
    this->addChild(_closeObjectListButton, UI_LAYER_GRADE);
    _closeObjectListButton->setVisible(false);

    // 创建退出程序按钮
    _exitButton = HoverMenuItemImage::create(
        "../Resources/UI/ExitButton.png",
        "../Resources/UI/ExitButton.png",
        [this](cocos2d::Ref* sender) { this->menuCloseCallback(sender); }
    );
    _exitButton->setPosition(Vec2(_visibleSize.width - _exitButton->getContentSize().width / 2, _exitButton->getContentSize().height / 2));
    this->addChild(_exitButton, UI_LAYER_GRADE);
    _exitButton->setVisible(true);
}

// 初始化技能板
void UILayer::initializeSkillBoard() {
    // 创建技能背景板
    _skillLevelBoard = Sprite::create("../Resources/UI/SkillBoard.png");
    _skillLevelBoard->setPosition(Vec2(_visibleSize.width / 4, _visibleSize.height / 2));
    this->addChild(_skillLevelBoard, UI_LAYER_GRADE);
    _skillLevelBoard->setVisible(false);

    // 创建技能等级显示图片
    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        for (int j = 0; j < SKILL_LEVEL_NUM; j++) {
            _skillLevelStar[i * SKILL_LEVEL_NUM + j] = Sprite::create("../Resources/UI/SkillStar.png");
            _skillLevelStar[i * SKILL_LEVEL_NUM + j]->setPosition(LocationMap::getInstance().getSkillLevelLocationMap().at(i * SKILL_LEVEL_NUM + j));
            this->addChild(_skillLevelStar[i * SKILL_LEVEL_NUM + j], UI_LAYER_GRADE + 1);
            _skillLevelStar[i * SKILL_LEVEL_NUM + j]->setVisible(false);
        }
    }
}

// 更新物品栏
void UILayer::updateObjectList() {
    // 获取角色的物品栏状态和窗口大小
    _objectListStatus = _character->getObjectListStatus();
    _boxObjectListStatus = _character->getBoxStatus();
    const int index = _character->getCurrentObjectIndex();
    // 根据角色的物品栏状态初始化物品栏背景
    if (!_objectListStatus) {
        _closedObjectListLayer->setVisible(true);
        _openedObjectListLayer->setVisible(false);
        _boxObjectListLayer->setVisible(false);
        _deleteObjectButton->setVisible(false);
        _closeObjectListButton->setVisible(false);
        setSelectObjectSpriteMarker(index, true);
        _skillLevelBoard->setVisible(false);
        setSkillLevel(false);
    }
    else {
        _closedObjectListLayer->setVisible(false);
        _openedObjectListLayer->setVisible(true);
        if (_boxObjectListStatus) {
            _boxObjectListLayer->setVisible(true);
        }
        _deleteObjectButton->setVisible(true);
        _closeObjectListButton->setVisible(true);
        setSelectObjectSpriteMarker(index, false);
        _skillLevelBoard->setVisible(true);
        setSkillLevel(true);
 
    }
    _lastObjectListStatus = _objectListStatus;
}

// 显示物品图片
void UILayer::showObjectImage() {
    _objectListStatus = _character->getObjectListStatus();
    _boxObjectListStatus = _character->getBoxStatus();
    // 清空之前的数量标签
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        if (_closedObjectSpriteImage[i] != nullptr) {
            if (_closedObjectQuantityLabels[i] != nullptr) {
                _closedObjectQuantityLabels[i]->removeFromParent();
                _closedObjectQuantityLabels[i] = nullptr;
            }
        }
    }
    for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
        for (int j = 0; j < OBJECT_LIST_COLS; j++) {
            if (_openedObjectQuantityLabels[i * OBJECT_LIST_COLS + j] != nullptr) {
                _openedObjectQuantityLabels[i * OBJECT_LIST_COLS + j]->removeFromParent();
                _openedObjectQuantityLabels[i * OBJECT_LIST_COLS + j] = nullptr;
            }
        }
    }
    // 显示物品图片
    if (!_objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            const auto objectInfo = _character->findObjectAtPosition(i);
            if (objectInfo.count != 0) {
                const auto objectSprite = objectInfo.objectNode.object->_fileName;
                _closedObjectSpriteImage[i] = Sprite::create(objectSprite);
                _closedObjectSpriteImage[i]->setPosition(LocationMap::getInstance().getLocationMap().at(i));
                _closedObjectSpriteImage[i]->setScale(OBJECT_NODE_SCALE);
                this->addChild(_closedObjectSpriteImage[i], OBJECT_LAYER_GRADE);
                showObjectCountLabel(_closedObjectSpriteImage[i], i, objectInfo.count);
            }
        }
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                if (_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j] != nullptr)
                    _openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setVisible(false);
            }
        }
    }
    else {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                const auto objectInfo = _character->findObjectAtPosition(i * OBJECT_LIST_COLS + j);
                if (objectInfo.count != 0) {
                    const auto objectSprite = objectInfo.objectNode.object->_fileName;
                    _openedObjectSpriteImage[i * OBJECT_LIST_COLS + j] = Sprite::create(objectSprite);
                    _openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setPosition(LocationMap::getInstance().getLocationMap().at(i * OBJECT_LIST_COLS + j));
                    _openedObjectSpriteImage[i * OBJECT_LIST_COLS + j]->setScale(OBJECT_NODE_SCALE);
                    this->addChild(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], OBJECT_LAYER_GRADE);

                    showObjectCountLabel(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], i * OBJECT_LIST_COLS + j, objectInfo.count);
                }
            }
        }
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if (_closedObjectSpriteImage[i] != nullptr)
                _closedObjectSpriteImage[i]->setVisible(false);
        }
    }

    // 显示箱子图片
    // todo:利用坐标位置查找箱子
   // for (int i = 0; i < _boxList.size(); i++) {

    //}
 /*   int index = 0;
    if (_boxObjectListStatus) {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            const auto boxObjectInfo = _boxList[index].findObjectAtPosition(i);
            if (boxObjectInfo.count != 0) {
                const auto objectSprite = boxObjectInfo.objectNode.object->_fileName;
                _closedObjectSpriteImage[i] = Sprite::create(objectSprite);
                _closedObjectSpriteImage[i]->setPosition(LocationMap::getInstance().getBoxLocationMap().at(i));
                _closedObjectSpriteImage[i]->setScale(OBJECT_NODE_SCALE);
                this->addChild(_closedObjectSpriteImage[i], OBJECT_LAYER_GRADE);

                showObjectCountLabel(_closedObjectSpriteImage[i], i, boxObjectInfo.count);
            }
        }
    }
    else {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if (_closedObjectSpriteImage[i] != nullptr)
                _closedObjectSpriteImage[i]->setVisible(false);
        }
    }*/
}

// 显示物品数量标签
void UILayer::showObjectCountLabel(cocos2d::Sprite* objectSprite, int index, int count) {
    _objectListStatus = _character->getObjectListStatus();
    _boxObjectListStatus = _character->getBoxStatus();
    auto quantityLabel = Label::createWithTTF(std::to_string(count), "../Resources/Fonts/arial.ttf", FONT_SIZE * 2 / 3);
    quantityLabel->setTextColor(Color4B::BLACK);
    quantityLabel->setPosition(
        objectSprite->getPosition().x + objectSprite->getContentSize().width * OBJECT_NODE_SCALE / 2 - quantityLabel->getContentSize().width / 2,
        objectSprite->getPosition().y - objectSprite->getContentSize().height * OBJECT_NODE_SCALE / 2 + quantityLabel->getContentSize().height / 2
    );
    this->addChild(quantityLabel, OBJECT_LAYER_GRADE + 1); // 将标签放在物品图片上方

    // 保存数量标签
    if (!_objectListStatus) {
        _closedObjectQuantityLabels[index] = quantityLabel;
    }
    else if(_objectListStatus){
        _openedObjectQuantityLabels[index] = quantityLabel;
    }
}

// 按下鼠标事件触发函数
void UILayer::onMouseDown(cocos2d::Event* event) {
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Vec2 location = mouseEvent->getLocationInView();
    _objectListStatus = _character->getObjectListStatus();
    _selectedObjectSprite = nullptr;
    _currentObjectQuantityLabel = nullptr;

    // 当物品栏被打开时才会检测
    if (_objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS * OBJECT_LIST_COLS; i++) {
            const auto sprite = _openedObjectSpriteImage[i];
            if (sprite != nullptr) {
                const Vec2 spritePos = sprite->getPosition();
                const Size spriteSize = sprite->getContentSize();
                if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT &&
                    location.x >= (spritePos.x - spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.x <= (spritePos.x + spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.y >= (spritePos.y - spriteSize.height * OBJECT_NODE_SCALE / 2) &&
                    location.y <= (spritePos.y + spriteSize.height * OBJECT_NODE_SCALE / 2)) {
                    _selectedObjectSprite = sprite;
                    break;
                }
            }
        }
    }

    if (_selectedObjectSprite) {
        // 标记选中状态
        if (_objectListStatus) {
            _selectedObjectSprite->setUserData(reinterpret_cast<void*>(1));
            _nearestPlacementMarker = Sprite::create("../Resources/UI/NearestPlacementMarker.png");
            _nearestPlacementMarker->setVisible(false);
            this->addChild(_nearestPlacementMarker, OBJECT_LAYER_GRADE + 1);

            for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                if (pair.second.equals(_selectedObjectSprite->getPosition())) {
                    _startLocation = pair.first;
                    break;
                }
            }
            _currentObjectQuantityLabel = _openedObjectQuantityLabels[_startLocation];
            _character->setCurrentObject(_startLocation);

            // 创建放置标记层
            _placementMarkerLayer = PlacementMarkerLayer::create();
            _placementMarkerLayer->showPlacementMarker();
            this->addChild(_placementMarkerLayer, OBJECT_LAYER_GRADE);
        }
    }
}

// 移动鼠标事件触发函数
void UILayer::onMouseMove(cocos2d::Event* event) {
    _objectListStatus = _character->getObjectListStatus();
    if (_objectListStatus) {
        if (_selectedObjectSprite != nullptr) {
            if (_nearestPlacementMarker != nullptr) {
                _nearestPlacementMarker->setPosition(findNearestPoint(_selectedObjectSprite));
                _nearestPlacementMarker->setVisible(true);
            }

            // 移动物品
            EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
            Vec2 location = mouseEvent->getLocationInView();
            _selectedObjectSprite->setPosition(location);

            // 更新数量标签位置
            if (_currentObjectQuantityLabel != nullptr) {
                _currentObjectQuantityLabel->setPosition(
                    _selectedObjectSprite->getPosition().x + _selectedObjectSprite->getContentSize().width * OBJECT_NODE_SCALE / 2 - _currentObjectQuantityLabel->getContentSize().width / 2,
                    _selectedObjectSprite->getPosition().y - _selectedObjectSprite->getContentSize().height * OBJECT_NODE_SCALE / 2 + _currentObjectQuantityLabel->getContentSize().height / 2
                );
            }
        }
    }
}

// 释放鼠标事件触发函数
void UILayer::onMouseUp(cocos2d::Event* event) {
    _objectListStatus = _character->getObjectListStatus();
    if (_objectListStatus) {
        if (_selectedObjectSprite != nullptr) {
            // 取消选中状态
            _selectedObjectSprite->setUserData(nullptr);
            _nearestPlacementMarker->removeFromParent();
            _nearestPlacementMarker = nullptr;

            // 删除当前物品
            bool isDelete = false;
            const Vec2 currentPos = _selectedObjectSprite->getPosition();
            if (currentPos.x >= OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY &&
                currentPos.x <= OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY &&
                currentPos.y >= OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY &&
                currentPos.y <= OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY) {
                isDelete = true;
            }

            if (!isDelete) {
                // 遍历所有可放置位置
                Vec2 nearestPoint = findNearestPoint(_selectedObjectSprite);

                // 确定物品移动目标位置属性
                int targetLocation = -1;
                for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                    if (pair.second.equals(nearestPoint)) {
                        targetLocation = pair.first;
                        break;
                    }
                }

                // 更新物品栏
                cocos2d::Sprite* currentObjectSprite;
                currentObjectSprite = _openedObjectSpriteImage[_startLocation];
                _openedObjectSpriteImage[_startLocation] = nullptr;
                this->removeChild(_openedObjectSpriteImage[_startLocation]);
                _openedObjectSpriteImage[targetLocation] = currentObjectSprite;

                // 更新数量标签的位置
                if (_currentObjectQuantityLabel != nullptr) {
                    _currentObjectQuantityLabel->setPosition(
                        nearestPoint.x + _selectedObjectSprite->getContentSize().width * OBJECT_NODE_SCALE / 2 - _currentObjectQuantityLabel->getContentSize().width / 2,
                        nearestPoint.y - _selectedObjectSprite->getContentSize().height * OBJECT_NODE_SCALE / 2 + _currentObjectQuantityLabel->getContentSize().height / 2
                    );
                }

                _selectedObjectSprite->setPosition(nearestPoint);
                _character->swapObject(_startLocation, targetLocation);
                std::swap(_openedObjectQuantityLabels[_startLocation], _openedObjectQuantityLabels[targetLocation]);
            }
            else {
                _selectedObjectSprite->setVisible(false);
                _character->deleteCurrentObject();
            }
            // 关闭放置标记层
            this->removeChild(_placementMarkerLayer);
            _placementMarkerLayer = nullptr;
            _selectedObjectSprite = nullptr;
            _currentObjectQuantityLabel = nullptr;
        }
    }
}

// 按下键盘事件触发函数
void UILayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    const int index = _character->getCurrentObjectIndex();
    _objectListStatus = _character->getObjectListStatus();
    setSelectObjectSpriteMarker(_lastSelectedObjectIndex, false);
    if (!_objectListStatus) {
        setSelectObjectSpriteMarker(index, true);
        // 有物品丢弃，需要更新物品栏
        if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
            if (_closedObjectSpriteImage[index] != nullptr) {
                _closedObjectSpriteImage[index]->setVisible(false);
                this->removeChild(_closedObjectSpriteImage[index]);
                _closedObjectSpriteImage[index] = nullptr;
            }
        }
    }
    else {
        setSelectObjectSpriteMarker(index, false);
    }
    _lastSelectedObjectIndex = index;
}

// 初始化时间显示器
void UILayer::initializeTimeDisplay() {
    // 获取可见区域大小
    _visibleSize = Director::getInstance()->getVisibleSize();

    // 计算右上角的位置
    const Vec2 rightTopPos = Vec2(_visibleSize.width * 0.9f, _visibleSize.height * 0.9f);  // 右上角，调整到合适的偏移量

    // 创建背景图片
    _timeDisplayLayer = Sprite::create("../Resources/UI/timetable.png");

    // 获取原始图片尺寸
    const Size originalTimeDisplaySize = _timeDisplayLayer->getContentSize();

    // 计算缩放比例，使得图片适应 16x16 像素
    const float scaleX = UI_SCALE / originalTimeDisplaySize.width;  // 计算 X 方向的缩放比例
    const float scaleY = UI_SCALE / originalTimeDisplaySize.height; // 计算 Y 方向的缩放比例

    // 设置缩放比例
    _timeDisplayLayer->setScale(scaleX, scaleY);

    // 设置背景图片位置
    _timeDisplayLayer->setPosition(rightTopPos);

    // 添加到场景
    this->addChild(_timeDisplayLayer, UI_LAYER_GRADE);

    // 计算标签的位置，使其相对于背景位置
    const Vec2 labelPos1 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.1, rightTopPos.y + originalTimeDisplaySize.height * scaleY * 0.32f);  // 在背景图片的顶部
    const Vec2 labelPos2 = Vec2(rightTopPos.x + originalTimeDisplaySize.width * 0.1, rightTopPos.y - originalTimeDisplaySize.height * scaleY * 0.05f);  // 在 labelPos1 下面偏移 30

    // 创建并初始化 timeLabel1 和 timeLabel2
    _timeLabel1 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    _timeLabel1->setPosition(labelPos1);
    _timeLabel1->setTextColor(Color4B::ORANGE);
    this->addChild(_timeLabel1, UI_LAYER_GRADE);

    _timeLabel2 = Label::createWithSystemFont("", "Arial", FONT_SIZE);
    _timeLabel2->setPosition(labelPos2);
    _timeLabel2->setTextColor(Color4B::ORANGE);
    this->addChild(_timeLabel2, UI_LAYER_GRADE);
}

// 更新时间显示器
void UILayer::updateTimeDisplay() {
    // 获取 TimeManager 的实例
    const TimeManager* timeManager = TimeManager::getInstance();

    // 获取并更新日期信息（星期和日期）
    std::string weekDay = timeManager->getWeekDay();
    _timeLabel1->setString(weekDay);  // 显示星期几 

    // 获取并更新时间信息（白天/晚上和当前时间）
    const bool isDaytime = timeManager->isDaytime();

    std::string dayOrNight = isDaytime ? "Day" : "Night";
    std::string timeOfDay = timeManager->getCurrentTime();
    _timeLabel2->setString(dayOrNight + " " + timeOfDay);  // 显示白天/晚上和当前时间的代码部分
}

// 更新UI界面
void UILayer::update(float deltaTime) {
    // 更新物品栏
    _objectListStatus = _character->getObjectListStatus();

    if (_objectListStatus != _lastObjectListStatus) {
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
    const auto objectListStatus = _character->getObjectListStatus();

    if (!objectListStatus) { // 物品栏关闭
        // 这里可以添加逻辑
    }
    else {  // 物品栏打开
        for (const auto& point : LocationMap::getInstance().getLocationMap()) {
            const int currentLocation = point.first;

            bool isEmpty = true;
            const auto objectInfo = _character->findObjectAtPosition(currentLocation);
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
        _selectObjectSpriteMarker[0]->setVisible(show);
    else
        _selectObjectSpriteMarker[index]->setVisible(show);
}

// 设置技能等级的显示状态
void UILayer::setSkillLevel(bool show) {
    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        const int skillLevel = _character->getSkillLevel(i);
        if (skillLevel > 0) {
            for (int j = 0; j < skillLevel; j++) {
                _skillLevelStar[i * SKILL_LEVEL_NUM + j]->setVisible(show);
            }
        }
    }
}

// 关闭回调
void UILayer::menuCloseCallback(cocos2d::Ref* pSender) {
    auto scene = Director::getInstance()->getRunningScene();
    if (scene) {
        auto farmScene = dynamic_cast<GameMainScene*>(scene);
        if (farmScene) {
            farmScene->menuCloseCallback(pSender);
        }
    }
}

