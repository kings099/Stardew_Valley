/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     UILayer.h
 * File Function: UI����UILayer��Ķ���
 * Author:        ��˼����ϳ�
 * Update Date:   2024/12/9
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "Classes/Manager/TimeManager.h"
#include "Classes/MenuImage/HoverMenuItemImage.h"
#include "../proj.win32/ObjectConstant.h"

class UILayer : public cocos2d::Layer {
public:
	// ��������
	~UILayer();

	// ��ʼ��UI��
	virtual bool init();

	// ��������¼���������
	void onMouseDown(cocos2d::Event* event, cocos2d::Sprite* championSprite);

	// �ƶ�����¼���������
	void onMouseMove(cocos2d::Event* event, cocos2d::Sprite* championSprite);

	// �ͷ�����¼���������
	void onMouseUp(cocos2d::Event* event, cocos2d::Sprite* championSprite);

	// ���¼����¼���������
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// ��ʼ����Ʒ��
	void initializeObjectList();

	// ������Ʒ��
	void updateObjectList();

	// ��ʾ��ƷͼƬ
	void showObjectImage();

	// ��ʾ��ǰѡ�е���Ʒ
	void showSelectedObject(cocos2d::Vec2 position);

	// ��ʼ��ʱ����ʾ��
	void initializeTimeDisplay();

	// ����ʱ����ʾ��
	void updateTimeDisplay();

	// ����UI����
	void update(float deltaTime);

	// UILayer��create����
	CREATE_FUNC(UILayer);

private:
	Character* character;															// ��ɫ��
	cocos2d::Size visibleSize;														// �ɼ�����Ĵ�С
	cocos2d::Label* timeLabel1;														// ��ʾ���ں����ڵı�ǩ
	cocos2d::Label* timeLabel2;														// ��ʾ����/���Ϻ�Сʱ�ı�ǩ
	cocos2d::Sprite* timeDisplayLayer;												// ����ΪUI������ͼƬ
	cocos2d::Sprite* objectListLayer = nullptr;										// ��Ʒ��״̬
	cocos2d::Sprite* closedObjectSpriteImage[OBJECT_LIST_COLS];						// ��Ʒ���ر�ʱ��ʾ����ƷͼƬ
	cocos2d::Sprite* openedObjectSpriteImage[OBJECT_LIST_COLS* OBJECT_LIST_ROWS];	// ��Ʒ����ʱ��ʾ����ƷͼƬ
	cocos2d::Sprite* selectObjectSpriteMarker[OBJECT_LIST_COLS];							// ѡ����Ʒ�ı��
	HoverMenuItemImage *deleteObjectButton = nullptr;								// ɾ����Ʒ��ť
	HoverMenuItemImage *closeObjectListButton = nullptr;							// �ر���Ʒ����ť
	bool lastObjectListStatus;														// ��һ����Ʒ��״̬
	int lastSelectedObjectIndex;
	// Ѱ������ɷ�������
	cocos2d::Vec2 findNearestPoint(cocos2d::Sprite* objectSprite);
};

#endif // !_UILAYER_H_


