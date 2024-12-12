/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.h
 * File Function: CharacterAction��Ķ���
 * Author:        ���ϳ�
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
	// ��������¼���������
	void onMouseDown(cocos2d::Event* event);


protected:
	int _farmExperience;		// ���ּ��ܾ���ֵ
	int _collectExperience;		// �ɼ����ܾ���ֵ
	int _mineExperience;		// �ɿ��ܾ���ֵ
	int _fishExperience;		// ���㼼�ܾ���ֵ


private:
	// ��ȡ��ɫ����ִ�еĶ���
	GameCharacterAction getAction();

	// �жϽ�ɫ�Ƿ����ִ�ж���
	bool checkActionIsValid();

	// ִ�ж���
	void doAction();
};

#endif // !_CHARACTER_ACTION_H_