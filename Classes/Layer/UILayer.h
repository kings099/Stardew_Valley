/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI����UILayer��Ķ���
 * Author:        ��˼����ϳ�
 * Update Date:   2024/12/17
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

	// ��ʾ��Ʒ������ǩ
	void showObjectCountLabel(cocos2d::Sprite* objectSprite,int index ,int count);

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
	cocos2d::Sprite* _closedObjectSpriteImage[OBJECT_LIST_COLS];					// ��Ʒ���ر�ʱ��ʾ����ƷͼƬָ��
	cocos2d::Sprite* _openedObjectSpriteImage[OBJECT_LIST_COLS * OBJECT_LIST_ROWS];	// ��Ʒ����ʱ��ʾ����ƷͼƬָ��
	cocos2d::Sprite* _boxObjectSpriteImage[OBJECT_LIST_COLS];						// ������ƷͼƬָ��
	cocos2d::Sprite* _selectObjectSpriteMarker[OBJECT_LIST_COLS];					// ѡ����Ʒ�ı��ָ��(��Ʒ����
	cocos2d::Sprite* _selectBoxObjectSpriteMarker[OBJECT_LIST_COLS];				// ѡ����Ʒ�ı��ָ��(������Ʒ����
	cocos2d::Sprite* _nearestPlacementMarker;										// ������ñ��ָ��
	cocos2d::Sprite* _selectedObjectSprite;											// ��ǰѡ�еĶ���
	cocos2d::Sprite* _skillLevelBoard;												// ���ܰ�ָ��
	cocos2d::Sprite* _skillLevelStar[SKILL_KIND_NUM * SKILL_LEVEL_NUM];				// ���ܵȼ�ָ��
	HoverMenuItemImage* _deleteObjectButton;										// ɾ����Ʒ��ť
	HoverMenuItemImage* _closeObjectListButton;										// �ر���Ʒ����ť
	HoverMenuItemImage* _exitButton;												// �˳���ť
	PlacementMarkerLayer* _placementMarkerLayer;									// ���ñ�ǲ���ָ��
	cocos2d::Label* _closedObjectQuantityLabels[OBJECT_LIST_COLS];					// ��Ʒ���ر�ʱ����Ʒ������ǩ
	cocos2d::Label* _openedObjectQuantityLabels[OBJECT_LIST_COLS * OBJECT_LIST_ROWS];// ��Ʒ����ʱ����Ʒ������ǩ
	cocos2d::Label* _boxObjectQuantityLabels[OBJECT_LIST_COLS];						// ������Ʒ������Ʒ������ǩ
	cocos2d::Label* _currentObjectQuantityLabel;									// ��ǰѡ����Ʒ��������ǩ
	bool _objectListStatus;															// ��Ʒ��״̬
	bool _lastObjectListStatus;														// ��һ����Ʒ��״̬
	bool _boxObjectListStatus;														// �Ƿ������
	int _lastSelectedObjectIndex;													// ��һ����Ʒ������
	int _startLocation;																// ��ʼλ��
	std::vector<Box> _boxList;														// �����б�
	// Ѱ������ɷ�������
	cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* objectSprite);

	// ����ѡ����Ʒ��ǿ����ʾ״̬
	void setSelectObjectSpriteMarker(int index, bool show);

	// ���ü��ܵȼ�����ʾ״̬
	void setSkillLevel(bool show);

	// �رջص�
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif // !_UILAYER_H_


