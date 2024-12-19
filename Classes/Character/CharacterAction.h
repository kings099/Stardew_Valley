/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     CharacterAction.h
 * File Function: CharacterAction��Ķ���
 * Author:        ���ϳ�
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
	// ���캯��
	CharacterAction(const std::string& filename);

	// ��������¼���������
	void onMouseDown(cocos2d::Event* event,GameCharacterAction &gameCharacterAction,cocos2d::Vec2 & targetTilePos, InteractionManager* interactionManager);

	// ��������
	bool saveData(const std::string& fileName);

	// ��������
	bool loadData(const std::string& fileName);

	// ��ȡ���ܵȼ�
	int getSkillLevel(int index);
private:
	int _skillExprience[SKILL_KIND_NUM];	//���ܾ���ֵ����
	int _skillLevel[SKILL_KIND_NUM];		//���ܵȼ�����

	// ��ȡ��ɫ����ִ�еĶ���(������)
	GameCharacterAction getLeftButtonAction();

	// ��ȡ��ɫ����ִ�еĶ���(����Ҽ�)
	GameCharacterAction getRightButtonAction();

	// �жϽ�ɫ�Ƿ����ִ�ж���
	bool checkActionIsValid(GameCharacterAction action,cocos2d::Vec2& targetTilePos, InteractionManager* interactionManager);

	// ��ȡ��ɫ�����������Ƭ��Ϣ
	TileInfo getTileInfo(GameCharacterAction action, InteractionManager* interactionManager);

	// ���¼��ܵȼ�
	void updateSkillLevel();

	// ���¼��ܾ���ֵ
	void updateSkillExprience(GameCharacterAction gameCharacterAction);

	// ��ȡ��Ʒ
	void getObject();
};

#endif // !_CHARACTER_ACTION_H_