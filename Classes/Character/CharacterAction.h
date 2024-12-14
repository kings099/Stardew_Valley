/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.h
 * File Function: CharacterAction类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/07
 * License:       MIT License
 ****************************************************************/
#pragma once

#include "CharacterObjectList.h"
#include "CharacterMove.h"

#ifndef _CHARACTER_ACTION_H_
#define _CHARACTER_ACTION_H_

class CharacterAction : public CharacterObjectList, virtual public CharacterMove {
public:
	// 构造函数
	CharacterAction(const std::string& filename);

	// 按下鼠标事件触发函数
	void onMouseDown(cocos2d::Event* event,GameCharacterAction &gameCharacterAction,cocos2d::Vec2 & targetTilePos);

	// 更新技能经验值和等级
	void updateSkillExprienceAndLevel(GameCharacterAction gameCharacterAction);


	int _sikllLevel[SKILL_KIND_NUM];		//技能等级数组
protected:



private:
	int _sikllExprience[SKILL_KIND_NUM];	//技能经验值数组

	// 获取角色打算执行的动作
	GameCharacterAction getAction();

	// 判断角色是否可以执行动作
	GameCharacterAction checkActionIsValid( cocos2d::Vec2& targetTilePos);
};

#endif // !_CHARACTER_ACTION_H_