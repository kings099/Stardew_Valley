/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI����UILayer��Ķ���
 * Author:        ��˼����ϳ�
 * Update Date:   2024/12/11
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
	Character* character;															// ��ɫָ
	cocos2d::Size visibleSize;														// �ɼ�����Ĵ�С
	cocos2d::Label* timeLabel1;														// ��ʾ���ں����ڵı�ǩָ��
	cocos2d::Label* timeLabel2;														// ��ʾ����/���Ϻ�Сʱ�ı�ǩָ��
	cocos2d::Sprite* timeDisplayLayer;												// ����Ϊʱ����ʾ��������ͼƬָ��
	cocos2d::Sprite* closedobjectListLayer;											// ��Ʒ���ر�״̬ͼƬָ��
	cocos2d::Sprite* openedobjectListLayer;											// ��Ʒ����״̬ͼƬָ��
	cocos2d::Sprite* closedObjectSpriteImage[OBJECT_LIST_COLS];						// ��Ʒ���ر�ʱ��ʾ����ƷͼƬָ��
	cocos2d::Sprite* openedObjectSpriteImage[OBJECT_LIST_COLS * OBJECT_LIST_ROWS];	// ��Ʒ����ʱ��ʾ����ƷͼƬָ��
	cocos2d::Sprite* selectObjectSpriteMarker[OBJECT_LIST_COLS];					// ѡ����Ʒ�ı��ָ��
	cocos2d::Sprite* nearestPlacementMarker;										// ������ñ��ָ��
	cocos2d::Sprite* selectedObjectSprite;											// ��ǰѡ�еĶ���
	HoverMenuItemImage *deleteObjectButton;											// ɾ����Ʒ��ť
	HoverMenuItemImage *closeObjectListButton;										// �ر���Ʒ����ť
	PlacementMarkerLayer* placementMarkerLayer;										// ���ñ�ǲ���ָ��
	bool objectListStatus;															// ��Ʒ��״̬
	bool lastObjectListStatus;														// ��һ����Ʒ��״̬
	int lastSelectedObjectIndex;													// ��һ����Ʒ������
	int startLocation;																// ��ʼλ��
	// Ѱ������ɷ�������
	cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* objectSprite);

	// ����ѡ����Ʒ��ǿ����ʾ״̬
	void setSelectObjectSpriteMarker(int index, bool show);
};

#endif // !_UILAYER_H_


