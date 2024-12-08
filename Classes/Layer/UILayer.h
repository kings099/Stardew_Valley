#pragma once
#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Classes/Character/Character.h"

class UILayer : public cocos2d::Layer {
public:
	//��������
	~UILayer();

	// ��ʼ��UI��
	virtual bool init();

	// ��ʼ����Ʒ��
	void initializeObjectList();

	// ����UI����
	void update(float deltaTime);

	// ʵ�� UILayer ��� create ����
	CREATE_FUNC(UILayer);

private:
	cocos2d::Sprite* objectListBackground = nullptr; // ���浱ǰ��Ʒ��������ָ��
};

#endif // ��_UILAYER_H_


