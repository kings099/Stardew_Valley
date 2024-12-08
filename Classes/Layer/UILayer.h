
#pragma once
#ifndef _UILAYER_H_
#define _UILAYER_H_

#include "cocos2d.h"
#include "Classes/Character/Character.h"

class UILayer : public cocos2d::Layer {
public:
	//析构函数
	~UILayer();

	// 初始化UI层
	virtual bool init();

	// 初始化物品栏
	void initializeObjectList();

	// 更新UI界面
	void update(float deltaTime);

	// 实现 UILayer 类的 create 方法
	CREATE_FUNC(UILayer);

private:
	cocos2d::Sprite* objectListBackground = nullptr; // 保存当前物品栏背景的指针
};

#endif // ！_UILAYER_H_