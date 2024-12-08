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

	// ��ʼ����Ʒ��
	void initializeObjectList();

	// ������Ʒ��
	void updateObjectList();

	// ��ʼ��ʱ����ʾ��
	void initializeTimeDisplay();

	// ����ʱ����ʾ��
	void updateTimeDisplay();

	// ����UI����
	void update(float deltaTime);

	// UILayer��create����
	CREATE_FUNC(UILayer);

private:
	Character* character;							// ��ɫ��
	cocos2d::Size visibleSize;						// �ɼ�����Ĵ�С

	cocos2d::Label* timeLabel1;						// ��ʾ���ں����ڵı�ǩ
	cocos2d::Label* timeLabel2;						// ��ʾ����/���Ϻ�Сʱ�ı�ǩ
	cocos2d::Sprite* timeDisplayLayer;				// ����ΪUI������ͼƬ

	cocos2d::Sprite* objectListLayer = nullptr;			// ��Ʒ��״̬
	HoverMenuItemImage *deleteObjectButton = nullptr;	// ɾ����Ʒ��ť
	HoverMenuItemImage *closeObjectListButton = nullptr;	// �ر���Ʒ����ť
};

#endif // !_UILAYER_H_


