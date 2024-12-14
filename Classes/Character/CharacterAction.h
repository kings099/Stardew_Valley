/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.h
 * File Function: CharacterAction��Ķ���
 * Author:        ���ϳ�
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
	// ���캯��
	CharacterAction(const std::string& filename);

	// ��������¼���������
	void onMouseDown(cocos2d::Event* event,GameCharacterAction &gameCharacterAction,cocos2d::Vec2 & targetTilePos);

	// ���¼��ܾ���ֵ�͵ȼ�
	void updateSkillExprienceAndLevel(GameCharacterAction gameCharacterAction);


	int _sikllLevel[SKILL_KIND_NUM];		//���ܵȼ�����
protected:



private:
	int _sikllExprience[SKILL_KIND_NUM];	//���ܾ���ֵ����

	// ��ȡ��ɫ����ִ�еĶ���
	GameCharacterAction getAction();

	// �жϽ�ɫ�Ƿ����ִ�ж���
	GameCharacterAction checkActionIsValid( cocos2d::Vec2& targetTilePos);
};

#endif // !_CHARACTER_ACTION_H_