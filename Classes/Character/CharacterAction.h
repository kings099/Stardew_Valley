/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.h
 * File Function: CharacterAction类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/11
 * License:       MIT License
 ****************************************************************/
#pragma once

#include "CharacterObjectList.h"
#include "CharacterMove.h"

#ifndef _CHARACTER_ACTION_H_
#define _CHARACTER_ACTION_H_

class CharacterAction : public CharacterObjectList, public CharacterMove {
public:
	// 按下鼠标事件触发函数
	void onMouseDown(cocos2d::Event* event);


protected:
	int _farmExperience;		// 耕种技能经验值
	int _collectExperience;		// 采集技能经验值
	int _mineExperience;		// 采矿技能经验值
	int _fishExperience;		// 钓鱼技能经验值


private:
	// 获取角色打算执行的动作
	GameCharacterAction getAction();

	// 判断角色是否可以执行动作
	bool checkActionIsValid();

	// 执行动作
	void doAction();
};

#endif // !_CHARACTER_ACTION_H_