/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.h
 * File Function: CharacterAction类的定义
 * Author:        尹诚成
 * Update Date:   2023/12/17
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
	void onMouseDown(cocos2d::Event* event,GameCharacterAction &gameCharacterAction,cocos2d::Vec2 & targetTilePos, InteractionManager* interactionManager);

	// 保存数据
	bool saveData(const std::string& fileName);

	// 加载数据
	bool loadData(const std::string& fileName);

	// 获取技能等级
	int getSkillLevel(int index);
private:
	int _skillExprience[SKILL_KIND_NUM];	//技能经验值数组
	int _skillLevel[SKILL_KIND_NUM];		//技能等级数组

	// 获取角色打算执行的动作(鼠标左键)
	GameCharacterAction getLeftButtonAction();

	// 获取角色打算执行的动作(鼠标右键)
	GameCharacterAction getRightButtonAction();

	// 判断角色是否可以执行动作
	bool checkActionIsValid(GameCharacterAction action,cocos2d::Vec2& targetTilePos, InteractionManager* interactionManager);

	// 获取角色动作对象的瓦片信息
	TileInfo getTileInfo(GameCharacterAction action, InteractionManager* interactionManager);

	// 更新技能等级
	void updateSkillLevel();

	// 更新技能经验值
	void updateSkillExprience(GameCharacterAction gameCharacterAction);

	// 获取物品
	void getObject();
};

#endif // !_CHARACTER_ACTION_H_