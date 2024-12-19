/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI����UILayer��Ķ���
 * Author:        ��˼����ϳ�
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Control/TimeManager.h"
#include "Classes/MenuImage/HoverMenuItemImage.h"
#include "Classes/Layer/PlacementMarkerLayer.h"
#include "Classes/Box/Box.h"
#include "../proj.win32/Constant.h"

class UILayer : public cocos2d::Layer {
public:
	// ���캯��
	UILayer();

	// ��������
	~UILayer();

	// ��ʼ��UI��
	virtual bool init();

	// ��������¼���������
	void onMouseDown(cocos2d::Event* event);

	// �ƶ�����¼���������
	void onMouseMove(cocos2d::Event* event);

	// �ͷ�����¼���������
	void onMouseUp(cocos2d::Event* event);

	// ���¼����¼���������
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// ��ʼ����Ʒ��
	void initializeObjectList();

	// ��ʼ�����ܰ�
	void initializeSkillBoard();

	// ������Ʒ��
	void updateObjectList();

	// ��ʾ��ƷͼƬ
	void showObjectImage();

	// ��ʼ��ʱ����ʾ��
	void initializeTimeDisplay();

	// ����ʱ����ʾ��
	void updateTimeDisplay();

	// ����UI����
	void update(float deltaTime);

	// UILayer��create����
	CREATE_FUNC(UILayer);

private:
	Character* _character;															// ��ɫָ��
	cocos2d::Size _visibleSize;														// �ɼ�����Ĵ�С
	cocos2d::Label* _timeLabel1;													// ��ʾ���ں����ڵı�ǩָ��
	cocos2d::Label* _timeLabel2;													// ��ʾ����/���Ϻ�Сʱ�ı�ǩָ��
	cocos2d::Sprite* _timeDisplayLayer;												// ����Ϊʱ����ʾ��������ͼƬָ��
	cocos2d::Sprite* _closedObjectListLayer;										// ��Ʒ���ر�״̬ͼƬָ��
	cocos2d::Sprite* _openedObjectListLayer;										// ��Ʒ����״̬ͼƬָ��
	cocos2d::Sprite* _boxObjectListLayer;											// ������Ʒ��ͼƬָ��
	cocos2d::Sprite* _skillLevelBoardLayer;											// ���ܰ�ָ��
	ObjectImageInfo _closedObjectSpriteImage[OBJECT_LIST_COLS];						// ��Ʒ���ر�ʱ��ʾ����ƷͼƬָ��
	ObjectImageInfo _openedObjectSpriteImage[OBJECT_LIST_COLS * OBJECT_LIST_ROWS];	// ��Ʒ����ʱ��ʾ����ƷͼƬָ��
	ObjectImageInfo _boxObjectSpriteImage[OBJECT_LIST_COLS];						// ������ƷͼƬָ��
	cocos2d::Sprite* _selectObjectSpriteMarker[OBJECT_LIST_COLS];					// ѡ����Ʒ�ı��ָ��(�ر�״̬����Ʒ����
	cocos2d::Sprite* _skillLevelLayer[SKILL_KIND_NUM * SKILL_LEVEL_NUM];			// ���ܵȼ�ָ��
	cocos2d::Sprite* _nearestPlacementMarker;										// ������ñ��ָ��
	ObjectImageInfo _selectedObjectImage;											// ��ǰѡ�е���ƷͼƬ����
	HoverMenuItemImage* _deleteObjectButton;										// ɾ����Ʒ��ť
	HoverMenuItemImage* _closeObjectListButton;										// �ر���Ʒ����ť
	HoverMenuItemImage* _exitButton;												// �˳���ť
	PlacementMarkerLayer* _placementMarkerLayer;									// ���ñ�ǲ���ָ��
	bool _objectListStatus;															// ��Ʒ��״̬
	bool _lastObjectListStatus;														// ��һ����Ʒ��״̬
	bool _boxObjectListStatus;														// �Ƿ������
	int _lastSelectedObjectIndex;													// ��һ����Ʒ������
	Location _startLocation;														// ��Ʒ�ƶ���ʼλ������
	// ������ƷͼƬ 
	void createObjectImage(ObjectImageInfo& objectImageInfo,const std::string spriteFileName,const int count);

	// ������ƷͼƬλ��
	void setObjectImagePosition(const ObjectImageInfo& objectImageInfo, const cocos2d::Vec2& position);

	// ������ƷͼƬ�Ƿ�ɼ�
	void setObjectImageVisible(ObjectImageInfo& objectImageInfo, bool visible);

	// Ѱ������ɷ�������
	cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* objectSprite);

	// ����ѡ����Ʒ��ǿ����ʾ״̬
	void setSelectObjectSpriteMarker(int index, bool show);

	// ���ü��ܵȼ�����ʾ״̬
	void setSkillLevel(bool show);

	// �������Ƿ���ĳ������������
	bool isMouseOverSprite(EventMouse* mouseEvent, const Vec2& mousePosition, cocos2d::Sprite* sprite);

	// �رջص�
	void menuCloseCallback(cocos2d::Ref* pSender);


};

#endif // !_UILAYER_H_


