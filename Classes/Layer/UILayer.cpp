/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.cpp
 * File Function: UI界面UILayer类的实现
 * Author:        达思睿，尹诚成
 * Update Date:   2024/12/18
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
    _weekDayLabel(nullptr),
    _timeHourLabel(nullptr),
    _timeDisplayLayer(nullptr),
    _closedObjectListLayer(nullptr),
    _openedObjectListLayer(nullptr),
    _boxObjectListLayer(nullptr),
    _skillLevelBoardLayer(nullptr),
    _shopLayer(nullptr),
    _synthesisTableLayer(nullptr),
    _nearestPlacementMarker(nullptr),
    _selectedObjectImage({nullptr,nullptr}),
    _deleteObjectButton(nullptr),
    _closeObjectListButton(nullptr),
    _sellObjectButton(nullptr),
    _exitButton(nullptr),
    _placementMarkerLayer(nullptr),
    _objectListStatus(false),
    _lastObjectListStatus(false),
    _boxObjectListStatus(false),
    _storeStatus(false),
    _synthesisTableStatus(false),
    _lastSelectedObjectIndex(0),
    _startLocation({OpenedObjectList,-1})
{
    _character = Character::getInstance();
    _store = Store::getInstance();
    _store->refreshStock();
    _visibleSize = Director::getInstance()->getVisibleSize();
    _lastWeekDay = "Monday";
    std::fill_n(_selectObjectSpriteMarker, OBJECT_LIST_COLS, nullptr);
    std::fill_n(_skillLevelLayer, SKILL_KIND_NUM * SKILL_LEVEL_NUM, nullptr);
    std::fill_n(_synthesisObjectSpriteImage, SYNTHESIS_TABLE_COLS * SYNTHESIS_TABLE_ROWS, nullptr);
    std::fill_n(_closedObjectSpriteImage, OBJECT_LIST_COLS, ObjectImageInfo());
    std::fill_n(_openedObjectSpriteImage, OBJECT_LIST_COLS * OBJECT_LIST_ROWS, ObjectImageInfo());
    std::fill_n(_boxObjectSpriteImage, OBJECT_LIST_COLS, ObjectImageInfo());
    std::fill_n(_storeObjectInfo, PRODUCE_KIND_NUM_EACH_DAY, StoreObjectInfo());
    // 鼠标事件监听器
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(UILayer::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(UILayer::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(UILayer::onMouseUp, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    // 设置回调
    _character->_callback = [this](bool success) {
        if (success) {
            updateObjectList();
            showObjectImage();
        }
        };
    _store->_sellProductCallback = [this](bool success) {
        if (success) {
            updateObjectList();
            showObjectImage();
        }
    };
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
    initializeShop();
    initializeSynthesisTable();
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
    _boxObjectListLayer->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height * 3 / 5));
    this->addChild(_boxObjectListLayer, UI_LAYER_GRADE);
    _boxObjectListLayer->setVisible(false);

    // 创建物品栏选中框
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        _selectObjectSpriteMarker[i] = Sprite::create("../Resources/UI/SelectionMarker.png");
        _selectObjectSpriteMarker[i]->setPosition(LocationMap::getInstance().getLocationMap().at({ ClosedObjectList,i }));
        this->addChild(_selectObjectSpriteMarker[i], OBJECT_LAYER_GRADE);
        _selectObjectSpriteMarker[i]->setVisible(false);
    }
    _selectObjectSpriteMarker[0]->setVisible(true);

    // 创建删除物品按钮
    _deleteObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/DefaultGarbageBinButton.png",
        "../Resources/UI/HoverGarbageBinButton.png",
        [this](cocos2d::Ref* sender) {}
    );//character->deleteCurrentObject();
    _deleteObjectButton->setPosition(Vec2(_visibleSize.width * 2 / 3, _visibleSize.height / 2));
    this->addChild(_deleteObjectButton, UI_LAYER_GRADE);
    _deleteObjectButton->setVisible(false);

    // 创建关闭物品栏按钮
    _closeObjectListButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultCloseMenuButton.png",
        "../Resources/UI/defaultCloseMenuButton.png",
        [this](cocos2d::Ref* sender) {  _character->resetKeyEnabled(); }
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
    _skillLevelBoardLayer = Sprite::create("../Resources/UI/SkillBoard.png");
    _skillLevelBoardLayer->setPosition(Vec2(_visibleSize.width / 4, _visibleSize.height / 2));
    this->addChild(_skillLevelBoardLayer, UI_LAYER_GRADE);
    _skillLevelBoardLayer->setVisible(false);

    // 创建技能等级显示图片
    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        for (int j = 0; j < SKILL_LEVEL_NUM; j++) {
            _skillLevelLayer[i * SKILL_LEVEL_NUM + j] = Sprite::create("../Resources/UI/SkillStar.png");
            _skillLevelLayer[i * SKILL_LEVEL_NUM + j]->setPosition(LocationMap::getInstance().getSkillLevelLocationMap().at(i * SKILL_LEVEL_NUM + j));
            this->addChild(_skillLevelLayer[i * SKILL_LEVEL_NUM + j], OBJECT_LAYER_GRADE);
            _skillLevelLayer[i * SKILL_LEVEL_NUM + j]->setVisible(false);
        }
    }
}

// 初始化商店
void UILayer::initializeShop() {
    // 创建商店背景板
    _shopLayer = Sprite::create("../Resources/UI/StoreList.png");
    _shopLayer->setPosition(Vec2(_visibleSize.width * 4 / 5, _visibleSize.height / 2));
    this->addChild(_shopLayer, UI_LAYER_GRADE);
    _shopLayer->setVisible(false);

    // 创建出售物品按钮
    _sellObjectButton = HoverMenuItemImage::create(
        "../Resources/UI/defaultSellButton.png",
        "../Resources/UI/defaultSellButton.png",
        [this](cocos2d::Ref* sender) { _store->sellProduct(_character->getCurrentObject().objectNode, _character->getCurrentObject().count); }
    );
    _sellObjectButton->setPosition(Vec2(_visibleSize.width * 4 / 5, _visibleSize.height * 1 / 3));
    this->addChild(_sellObjectButton, UI_LAYER_GRADE);
    _sellObjectButton->setVisible(false);

}

// 初始化合成表
void UILayer::initializeSynthesisTable() {
    // 创建合成表背景板
    _synthesisTableLayer = Sprite::create("../Resources/UI/SynthesisTable.png");
    _synthesisTableLayer->setPosition(Vec2(_visibleSize.width * 4 / 5, _visibleSize.height / 2));
    this->addChild(_synthesisTableLayer, UI_LAYER_GRADE);
    _synthesisTableLayer->setVisible(false);

    // 创建可合成物品图片
    int index = 0;
    for (const auto& object : GAME_BASE_OBJECTS_ATTRS) {
        if (object._synthesis == true) {
            _synthesisObjectSpriteImage[index] = HoverMenuItemImage::create(object._fileName, object._fileName, [this, object](cocos2d::Ref* sender) {_character->synthesizeObject(object);}, OBJECT_NODE_SCALE);
            _synthesisObjectSpriteImage[index]->setPosition(LocationMap::getInstance().getSysthesisTableLocationMap().at(index));
            _synthesisObjectSpriteImage[index]->setScale(OBJECT_NODE_SCALE);
            this->addChild(_synthesisObjectSpriteImage[index], OBJECT_LAYER_GRADE);
            _synthesisObjectSpriteImage[index]->setVisible(false);
            index++;
        }
    }
}

// 更新物品栏
void UILayer::updateObjectList() {
    const int index = _character->getCurrentObjectIndex();
    // 根据角色的物品栏状态初始化物品栏背景
    if (!_objectListStatus) {
        _closedObjectListLayer->setVisible(true);
        _openedObjectListLayer->setVisible(false);
        _boxObjectListLayer->setVisible(false);
        _boxObjectListLayer->setVisible(false);
        _shopLayer->setVisible(false);
        _sellObjectButton->setVisible(false);
        _deleteObjectButton->setVisible(false);
        _closeObjectListButton->setVisible(false);
        setSelectObjectSpriteMarker(index, true);
        setSkillLevelVisible(false);
        setSynthesisTableVisible(false);
    }
    else {
        _closedObjectListLayer->setVisible(false);
        _openedObjectListLayer->setVisible(true);
        if (_boxObjectListStatus && Box::getInstance().getBoxCount() != 0) {
            _boxObjectListLayer->setVisible(true);
            _shopLayer->setVisible(false);
            _sellObjectButton->setVisible(false);
            setSynthesisTableVisible(false);
        }
        else if (_storeStatus) {
            _boxObjectListLayer->setVisible(false);
            _shopLayer->setVisible(true);
            _sellObjectButton->setVisible(true);
            setSynthesisTableVisible(false);
        }
        else if (_synthesisTableStatus) {
            _boxObjectListLayer->setVisible(false);
            _shopLayer->setVisible(false);
            _sellObjectButton->setVisible(false);
            setSynthesisTableVisible(true);
        }
        _deleteObjectButton->setVisible(true);
        _closeObjectListButton->setVisible(true);
        setSelectObjectSpriteMarker(index, false);
        setSkillLevelVisible(true);
 
    }
    _lastObjectListStatus = _objectListStatus;
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

    // 创建并初始化 _weekDayLabel 和 _timeHourLabel
    _weekDayLabel = Label::createWithSystemFont("", FONT_TYPE, FONT_SIZE);
    _weekDayLabel->setPosition(labelPos1);
    _weekDayLabel->setTextColor(Color4B::ORANGE);
    this->addChild(_weekDayLabel, UI_LAYER_GRADE);

    _timeHourLabel = Label::createWithSystemFont("", FONT_TYPE, FONT_SIZE);
    _timeHourLabel->setPosition(labelPos2);
    _timeHourLabel->setTextColor(Color4B::ORANGE);
    this->addChild(_timeHourLabel, UI_LAYER_GRADE);

    _weatherLabel = Label::createWithSystemFont("", FONT_TYPE, FONT_SIZE);
    _weatherLabel->setPosition(_visibleSize.width * 0.9f, _visibleSize.height * 0.8f);
    _weatherLabel->setTextColor(Color4B::ORANGE);
    this->addChild(_weatherLabel, UI_LAYER_GRADE);
}

// 按下鼠标事件触发函数
void UILayer::onMouseDown(cocos2d::Event* event) {
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Vec2 location = mouseEvent->getLocationInView();
    _selectedObjectImage = { nullptr,nullptr };

    // 当物品栏被打开时才会检测
    if (_objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_ROWS * OBJECT_LIST_COLS; i++) {
            const auto sprite = _openedObjectSpriteImage[i].sprite;
            if (sprite != nullptr) {
                const Vec2 spritePos = sprite->getPosition();
                const Size spriteSize = sprite->getContentSize();
                if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT &&
                    location.x >= (spritePos.x - spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.x <= (spritePos.x + spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.y >= (spritePos.y - spriteSize.height * OBJECT_NODE_SCALE / 2) &&
                    location.y <= (spritePos.y + spriteSize.height * OBJECT_NODE_SCALE / 2)) {
                    _selectedObjectImage.sprite = _openedObjectSpriteImage[i].sprite;
                    _selectedObjectImage.label = _openedObjectSpriteImage[i].label;
                    break;
                }
            }
        }

        if (_boxObjectListStatus && Box::getInstance().getBoxCount() != 0) {
            for (int i = 0; i < OBJECT_LIST_COLS; i++) {
                const auto sprite = _boxObjectSpriteImage[i].sprite;
                if (sprite != nullptr) {
                    const Vec2 spritePos = sprite->getPosition();
                    const Size spriteSize = sprite->getContentSize();
                    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT &&
                        location.x >= (spritePos.x - spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                        location.x <= (spritePos.x + spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                        location.y >= (spritePos.y - spriteSize.height * OBJECT_NODE_SCALE / 2) &&
                        location.y <= (spritePos.y + spriteSize.height * OBJECT_NODE_SCALE / 2)) {
                        _selectedObjectImage.sprite = _boxObjectSpriteImage[i].sprite;
                        _selectedObjectImage.label = _boxObjectSpriteImage[i].label;
                        break;
                    }
                }
            }
        }
    }

    // 当商店被打开时才会检测
    if (_storeStatus) {
        for (const auto& storeProdctPos : LocationMap::getInstance().getStoreLocationMap()) {
            const auto sprite = _storeObjectInfo[storeProdctPos.first].sprite;
            if (sprite != nullptr) {
                const Vec2 spritePos = sprite->getPosition();
                const Size spriteSize = sprite->getContentSize();
                if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT &&
                    location.x >= (spritePos.x - spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.x <= (spritePos.x + spriteSize.width * OBJECT_NODE_SCALE / 2) &&
                    location.y >= (spritePos.y - spriteSize.height * OBJECT_NODE_SCALE / 2) &&
                    location.y <= (spritePos.y + spriteSize.height * OBJECT_NODE_SCALE / 2) &&
                    _store->buyProduct(storeProdctPos.first)) {
                        setStoreObjectInfoVisible(_storeObjectInfo[storeProdctPos.first], false);
                        this->removeChild(_storeObjectInfo[storeProdctPos.first].sprite);
                        this->removeChild(_storeObjectInfo[storeProdctPos.first].namelabel);
                        this->removeChild(_storeObjectInfo[storeProdctPos.first].pricelabel);
                        _storeObjectInfo[storeProdctPos.first] = { nullptr,nullptr,nullptr }; // 重新初始化
                }
            }
        }
    }
    
    if (_selectedObjectImage.sprite) {
        // 标记选中状态
        if (_objectListStatus) {
            _selectedObjectImage.sprite->setUserData(reinterpret_cast<void*>(1));
            _selectedObjectImage.label->setUserData(reinterpret_cast<void*>(1));
            _nearestPlacementMarker = Sprite::create("../Resources/UI/NearestPlacementMarker.png");
            _nearestPlacementMarker->setVisible(false);
            this->addChild(_nearestPlacementMarker, OBJECT_LAYER_GRADE + 1);

            for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                if (pair.second.equals(_selectedObjectImage.sprite->getPosition())) {
                    _startLocation = pair.first;
                    break;
                }
            }
            _character->setCurrentObject(_startLocation.position);

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
        if (_selectedObjectImage.sprite != nullptr) {
            if (_nearestPlacementMarker != nullptr) {
                _nearestPlacementMarker->setPosition(findNearestPoint(_selectedObjectImage.sprite));
                _nearestPlacementMarker->setVisible(true);
            }

            // 移动物品
            EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
            Vec2 location = mouseEvent->getLocationInView();
            setObjectImagePosition(_selectedObjectImage, location);
        }
    }
}

// 释放鼠标事件触发函数
void UILayer::onMouseUp(cocos2d::Event* event) {
    if (_objectListStatus) {
        if (_selectedObjectImage.sprite != nullptr) {
            // 取消选中状态
            _selectedObjectImage.sprite->setUserData(nullptr);
            _selectedObjectImage.label->setUserData(nullptr);
            _nearestPlacementMarker->removeFromParent();
            _nearestPlacementMarker = nullptr;

            // 删除/出售当前物品
            bool isDelete = false;
            bool isSell = false;
            const Vec2 currentPos = _selectedObjectImage.sprite->getPosition();
            if (currentPos.x >= OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY &&
                currentPos.x <= OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY &&
                currentPos.y >= OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY &&
                currentPos.y <= OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY) {
                isDelete = true;
            }
            else if (currentPos.x >= OPEN_OBJIEC_LIST_SELL_BUTTON_LEFT_BOUDARY
                && currentPos.x <= OPEN_OBJIEC_LIST_SELL_BUTTON_RIGHT_BOUDARY
                && currentPos.y >= OPEN_OBJIEC_LIST_SELL_BUTTON_TOP_BOUDARY
                && currentPos.y <= OPEN_OBJIEC_LIST_SELL_BUTTON_BOTTOM_BOUDARY
                && _character->getCurrentObject().objectNode.type != Tool) {
                isSell = true;
            }

            if (!isDelete && !isSell) {
                // 遍历所有可放置位置
                Vec2 nearestPoint = findNearestPoint(_selectedObjectImage.sprite);

                // 确定物品移动目标位置属性
                Location targetLocation = { OpenedObjectList, -1 };
                for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                    if (pair.second.equals(nearestPoint)) {
                        targetLocation = pair.first;
                        break;
                    }
                }

                // 更新物品栏图片
                ObjectImageInfo currentObjectImage;
                if (_startLocation.status == OpenedObjectList) {
                    currentObjectImage = _openedObjectSpriteImage[_startLocation.position];
                    _openedObjectSpriteImage[_startLocation.position] = { nullptr,nullptr };

                }
                else if (_startLocation.status == OpenedBoxList && _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0) {
                    currentObjectImage = _boxObjectSpriteImage[_startLocation.position];
                    _boxObjectSpriteImage[_startLocation.position] = { nullptr,nullptr };
                }
                if (targetLocation.status == OpenedObjectList) {
                    _openedObjectSpriteImage[targetLocation.position] = currentObjectImage;
                }
                else if(targetLocation.status == OpenedBoxList && _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0){
                    _boxObjectSpriteImage[targetLocation.position] = currentObjectImage;
                }

                // 更新物品栏
                if (_startLocation.status == OpenedObjectList && targetLocation.status == OpenedObjectList) {// 背包->背包
                    _character->swapObject(_startLocation.position, targetLocation.position);
                }
                else if (_startLocation.status == OpenedBoxList && targetLocation.status == OpenedBoxList && _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0) { // 箱子->箱子
                    Box::getInstance().swapObject(_startLocation.position, targetLocation.position);
                }
                else if (_startLocation.status == OpenedObjectList && targetLocation.status == OpenedBoxList && _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0) { // 背包->箱子
                    Box::getInstance().storeObject(_startLocation.position, targetLocation.position);
                }
                else if (_startLocation.status == OpenedBoxList && targetLocation.status == OpenedObjectList && _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0) { // 箱子->背包
                    Box::getInstance().getSelectedObject(_startLocation.position, targetLocation.position);
                }

                // 移动物品图片
                setObjectImagePosition(_selectedObjectImage, nearestPoint);
            }
            else if(isDelete){
                setObjectImageVisible(_selectedObjectImage, false);
                _character->deleteCurrentObject();
            }
            else if (isSell) {
                const auto targetObject = _character->getCurrentObject();
                if (_store->sellProduct(targetObject.objectNode, targetObject.count)) {
                   // setObjectImageVisible(_selectedObjectImage, false);
                }
            }
            // 关闭放置标记层
            this->removeChild(_placementMarkerLayer);
            _placementMarkerLayer = nullptr;
            _selectedObjectImage = { nullptr,nullptr };
        }
    }
}

// 按下键盘事件触发函数
void UILayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    const int index = _character->getCurrentObjectIndex();
    _objectListStatus = _character->getObjectListStatus();
    _boxObjectListStatus = _character->getBoxStatus();
    _storeStatus = _character->getStoreStatus();
    _synthesisTableStatus = _character->getSynthesisTableStatus();
    
    setSelectObjectSpriteMarker(_lastSelectedObjectIndex, false);
    if (!_objectListStatus) {
        setSelectObjectSpriteMarker(index, true);
        // 有物品丢弃，需要更新物品栏
        if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
            if (_closedObjectSpriteImage[index].sprite != nullptr) {
                _closedObjectSpriteImage[index].sprite->setVisible(false);
                this->removeChild(_closedObjectSpriteImage[index].sprite);
                _closedObjectSpriteImage[index] = {nullptr,nullptr };
            }
        }
    }
    else {
        setSelectObjectSpriteMarker(index, false);
    }
    _lastSelectedObjectIndex = index;
}

// 更新时间显示器
void UILayer::updateTimeDisplay() {
    // 获取 TimeManager 的实例
    const TimeManager* timeManager = TimeManager::getInstance();

    // 获取并更新日期信息（星期和日期）
    std::string weekDay = timeManager->getWeekDay();
    _weekDayLabel->setString(weekDay);  // 显示星期几 

    // 获取并更新时间信息（白天/晚上,当前时间,天气）
    const bool isDaytime = timeManager->isDaytime();
    std::string season = timeManager->getCurrentSeasonStr();
    std::string dayOrNight = isDaytime ? "D" : "N";
    std::string timeOfDay = timeManager->getCurrentTime();
    _timeHourLabel->setString(season+"-"+dayOrNight + " " + timeOfDay);  // 显示白天/晚上和当前时间的代码部分
    std::string weather = timeManager->getCurrentWeatherStr();
    _weatherLabel->setString(weather);  // 显示天气信息

    if (_lastWeekDay != weekDay) {
        _lastWeekDay = weekDay;

        _store->refreshStock();
        showObjectImage();
    }

}

// 更新角色金钱显示
void UILayer::updateCharacterMoneyLabel() {
    // 创建角色金钱数量标签
    if (_characterMoneyLabel != nullptr) {
        this->removeChild(_characterMoneyLabel);
        _characterMoneyLabel = nullptr;
    }
    _characterMoneyLabel = Label::create(std::to_string(_character->getMoney()), "../Resources/fonts/arial.ttf", FONT_SIZE);
    _characterMoneyLabel->setPosition(Vec2(_visibleSize.width * 4 / 5 + 271, _visibleSize.height * 4 / 5 + 30));
    _characterMoneyLabel->setAnchorPoint(RIGHT_ALIGNED_ANCHOR);
    _characterMoneyLabel->setTextColor(Color4B::ORANGE);
    this->addChild(_characterMoneyLabel, UI_LAYER_GRADE + 1);
    _characterMoneyLabel->setVisible(true);
}


// 更新UI界面
void UILayer::update(float deltaTime) {
    // 更新物品栏
    // 根据物品栏状态更新物品栏图片
    if (_objectListStatus != _lastObjectListStatus) {
        updateObjectList();
        showObjectImage();
    }

    // TODO:补充合成表逻辑

    // 更新时间显示器
    updateTimeDisplay();

    // 更新金钱标签
    updateCharacterMoneyLabel();
}
// 显示物品图片
void UILayer::showObjectImage() {
    // 清空之前的数量标签
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        if (_closedObjectSpriteImage[i].sprite != nullptr) {
            this->removeChild(_closedObjectSpriteImage[i].sprite);
            this->removeChild(_closedObjectSpriteImage[i].label);
            _closedObjectSpriteImage[i] = { nullptr,nullptr }; // 重新初始化
        }
    }
    for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
        for (int j = 0; j < OBJECT_LIST_COLS; j++) {
            if (_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j].sprite != nullptr) {
                this->removeChild(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j].sprite);
                this->removeChild(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j].label);
                _openedObjectSpriteImage[i * OBJECT_LIST_COLS + j] = { nullptr,nullptr }; // 重新初始化
            }
        }
    }
    for (int i = 0; i < OBJECT_LIST_COLS; i++) {
        if (_boxObjectSpriteImage[i].sprite != nullptr) {
            this->removeChild(_boxObjectSpriteImage[i].sprite);
            this->removeChild(_boxObjectSpriteImage[i].label);
            _boxObjectSpriteImage[i] = { nullptr,nullptr }; // 重新初始化
        }
    }
    for (int i = 0; i < PRODUCE_KIND_NUM_EACH_DAY; i++) {
        if (_storeObjectInfo[i].sprite != nullptr) {
            this->removeChild(_storeObjectInfo[i].sprite);
            this->removeChild(_storeObjectInfo[i].namelabel);
            this->removeChild(_storeObjectInfo[i].pricelabel);
            _storeObjectInfo[i] = { nullptr,nullptr,nullptr }; // 重新初始化

        }
    }
    // 显示物品图片
    if (!_objectListStatus) {
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            const auto objectInfo = _character->findObjectAtPosition(i);
            if (objectInfo.count != 0) {
                const auto objectSpriteFilename = objectInfo.objectNode.object->_fileName;
                const int objectCount = objectInfo.count;
                createObjectImage(_closedObjectSpriteImage[i], objectSpriteFilename, objectCount);
                setObjectImagePosition(_closedObjectSpriteImage[i], LocationMap::getInstance().getLocationMap().at({ ClosedObjectList,i }));
            }
        }
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                if (_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j].sprite != nullptr)
                    setObjectImageVisible(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], false);
            }
        }
    }
    else {
        for (int i = 0; i < OBJECT_LIST_ROWS; i++) {
            for (int j = 0; j < OBJECT_LIST_COLS; j++) {
                const auto objectInfo = _character->findObjectAtPosition(i * OBJECT_LIST_COLS + j);
                if (objectInfo.count != 0) {
                    const auto objectSpriteFilename = objectInfo.objectNode.object->_fileName;
                    const int objectCount = objectInfo.count;
                    createObjectImage(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], objectSpriteFilename, objectCount);
                    setObjectImagePosition(_openedObjectSpriteImage[i * OBJECT_LIST_COLS + j], LocationMap::getInstance().getLocationMap().at({ OpenedObjectList,i * OBJECT_LIST_COLS + j }));
                }
            }
        }
        for (int i = 0; i < OBJECT_LIST_COLS; i++) {
            if (_closedObjectSpriteImage[i].sprite != nullptr)
                setObjectImageVisible(_closedObjectSpriteImage[i], false);
        }

        // 如果打开箱子则显示箱子物品图片
        if (_boxObjectListStatus && Box::getInstance().getBoxCount() != 0) {
            for (int i = 0; i < OBJECT_LIST_COLS; i++) {
                const auto boxObjectInfo = Box::getInstance().findObjectAtPosition(i);
                if (boxObjectInfo.count != 0) {
                    const auto objectSpriteFilename = boxObjectInfo.objectNode.object->_fileName;
                    const int objectCount = boxObjectInfo.count;
                    createObjectImage(_boxObjectSpriteImage[i], objectSpriteFilename, objectCount);
                    setObjectImagePosition(_boxObjectSpriteImage[i], LocationMap::getInstance().getLocationMap().at({ OpenedBoxList,i }));
                }
            }
        }
        else {
            for (int i = 0; i < OBJECT_LIST_COLS; i++) {
                if (_boxObjectSpriteImage[i].sprite != nullptr)
                    setObjectImageVisible(_boxObjectSpriteImage[i], false);
            }
        }

        // 如果打开商店则显示商店物品图片
        if (_storeStatus) {
            for (int i = 0; i < PRODUCE_KIND_NUM_EACH_DAY; i++) {
                const auto storeObjectInfo = _store->findObjectAtPosition(i);
                if (storeObjectInfo.count != 0) {
                    const auto objectSpriteFilename = storeObjectInfo.product.object->_fileName;
                    const auto objectName = storeObjectInfo.product.object->_name;
                    const int objectPrice = storeObjectInfo.totalPrice;
                    createStoreObjectInfo(_storeObjectInfo[i], objectSpriteFilename, objectName, objectPrice);
                    setStoreObjectInfoPosition(_storeObjectInfo[i], LocationMap::getInstance().getStoreLocationMap().at(i));
                }
            }
        }
        else {
            for (int i = 0; i < PRODUCE_KIND_NUM_EACH_DAY; i++) {
                if (_storeObjectInfo[i].sprite != nullptr) {
                    setStoreObjectInfoVisible(_storeObjectInfo[i], false);
                }
            }
        }
    }
}

// 创建物品图片 
void UILayer::createObjectImage(ObjectImageInfo& objectImageInfo, const std::string spriteFileName, const int count) {
    objectImageInfo.sprite = Sprite::create(spriteFileName);
    objectImageInfo.label = Label::createWithTTF(std::to_string(count), FONT_TYPE, FONT_SIZE * 2 / 3);
    objectImageInfo.sprite->setScale(OBJECT_NODE_SCALE);
    objectImageInfo.label->setTextColor(Color4B::BLACK);
    this->addChild(objectImageInfo.sprite, OBJECT_LAYER_GRADE);
    this->addChild(objectImageInfo.label, OBJECT_LAYER_GRADE + 1);
}

// 设置物品图片位置
void UILayer::setObjectImagePosition(const ObjectImageInfo& objectImageInfo, const cocos2d::Vec2& position) {
    objectImageInfo.sprite->setPosition(position);
    objectImageInfo.label->setPosition(
        objectImageInfo.sprite->getPosition().x + objectImageInfo.sprite->getContentSize().width * OBJECT_NODE_SCALE / 2 - objectImageInfo.label->getContentSize().width / 2,
        objectImageInfo.sprite->getPosition().y - objectImageInfo.sprite->getContentSize().height * OBJECT_NODE_SCALE / 2 + objectImageInfo.label->getContentSize().height / 2
    );
}

// 设置物品图片是否可见
void UILayer::setObjectImageVisible(const ObjectImageInfo& objectImageInfo, bool visible) {
    objectImageInfo.sprite->setVisible(visible);
    objectImageInfo.label->setVisible(visible);
}

// 创建商店物品信息
void UILayer::createStoreObjectInfo(StoreObjectInfo& storeObjectInfo, const std::string spriteFileName, const std::string spriteName, const int price) {
    storeObjectInfo.sprite = Sprite::create(spriteFileName);
    storeObjectInfo.namelabel = Label::createWithTTF(spriteName, FONT_TYPE, FONT_SIZE * 2 / 3);
    storeObjectInfo.pricelabel = Label::createWithTTF(std::to_string(price), FONT_TYPE, FONT_SIZE * 2 / 3);

    storeObjectInfo.sprite->setScale(OBJECT_NODE_SCALE);
    storeObjectInfo.namelabel->setTextColor(Color4B::BLACK);
    storeObjectInfo.pricelabel->setTextColor(Color4B::BLACK);
  
    this->addChild(storeObjectInfo.sprite, OBJECT_LAYER_GRADE + 1);
    this->addChild(storeObjectInfo.namelabel, OBJECT_LAYER_GRADE + 1);
    this->addChild(storeObjectInfo.pricelabel, OBJECT_LAYER_GRADE + 1);
}

// 设置商店物品图片位置
void UILayer::setStoreObjectInfoPosition(const StoreObjectInfo& storeObjectInfo, const cocos2d::Vec2& position) {
    storeObjectInfo.sprite->setPosition(position);
    storeObjectInfo.namelabel->setPosition(position.x + OBJECT_STORE_IMAGE_NAME_HORIZONTAL_INTERVAL, position.y);
    storeObjectInfo.pricelabel->setPosition(position.x + OBJECT_STORE_IMAGE_NAME_HORIZONTAL_INTERVAL+OBJECT_STORE_NAME_PRICE_HORIZONTAL_INTERVAL, position.y );
}

// 设置商店物品图片是否可见
void UILayer::setStoreObjectInfoVisible(const StoreObjectInfo& storeObjectInfo, bool visible) {
    storeObjectInfo.sprite->setVisible(visible);
    storeObjectInfo.namelabel->setVisible(visible);
    storeObjectInfo.pricelabel->setVisible(visible);
}

// 设置技能表是否可见
void UILayer::setSkillLevelVisible(bool visible) {
    _skillLevelBoardLayer->setVisible(visible);

    for (int i = 0; i < SKILL_KIND_NUM; i++) {
        const int skillLevel = _character->getSkillLevel(static_cast<GameObjectSkillType>(i));
        if (skillLevel > 0) {
            for (int j = 0; j < skillLevel; j++) {
                _skillLevelLayer[i * SKILL_LEVEL_NUM + j]->setVisible(visible);
            }
        }
    }
}

// 设置合成表是否可见
void UILayer::setSynthesisTableVisible(bool visible) {
    _synthesisTableLayer->setVisible(visible);

    for (int i = 0; i < SYNTHESIS_TABLE_ROWS; i++) {
        for (int j = 0; j < SYNTHESIS_TABLE_COLS; j++) {
            if (_synthesisObjectSpriteImage[i * SYNTHESIS_TABLE_COLS + j] != nullptr) {
                _synthesisObjectSpriteImage[i * SYNTHESIS_TABLE_COLS + j]->setVisible(visible);
            }
        }
    }
}

// 寻找最近可放置坐标
Vec2 UILayer::findNearestPoint(cocos2d::Sprite* objectSprite) {
    float minDistance = FLT_MAX;
    Vec2 nearestPoint;
    const Vec2 currentPos = objectSprite->getPosition();

    if (_objectListStatus)  {  // 物品栏打开
        for (const auto& point : LocationMap::getInstance().getLocationMap()) {
            const Location currentLocation = point.first;

            bool isEmpty = true;
            ObjectListNode objectInfo = { GameCommonObject() ,0 ,Unselected};
            if (currentLocation.status == ClosedObjectList) {
                continue;
            }
            else if (currentLocation.status == OpenedObjectList) {
                 objectInfo = _character->findObjectAtPosition(currentLocation.position);
            }
            else if (currentLocation.status == OpenedBoxList && _boxObjectListStatus == true ) {
                if (Box::getInstance().getBoxCount() != 0) {
                    objectInfo = Box::getInstance().findObjectAtPosition(currentLocation.position);
                }
                else {
                    continue;
                }
            }

            if (currentLocation.status == OpenedObjectList) {
                if (objectInfo.count != 0) {
                    isEmpty = false;
                }
            }
            else if (currentLocation.status == OpenedBoxList&& _boxObjectListStatus == true && Box::getInstance().getBoxCount() != 0) {
                if (objectInfo.count != 0) {
                    isEmpty = false;
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

// 设置选中物品标记框的显示状态
void UILayer::setSelectObjectSpriteMarker(int index, bool show) {
    if (index >= OBJECT_LIST_COLS)
        _selectObjectSpriteMarker[0]->setVisible(show);
    else
        _selectObjectSpriteMarker[index]->setVisible(show);
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

