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
	CharacterAction();

	// ��������¼���������
	bool onMouseDown(cocos2d::Event* event,GameCharacterAction &gameCharacterAction,cocos2d::Vec2 & targetTilePos, InteractionManager* interactionManager);

	// �����Ʒ
	void getObject(GameCharacterAction action,InteractionManager* interactionManager);

	// ʹ����Ʒ
	void useObject(GameCharacterAction action, InteractionManager* interactionManager);

	// ��ȡ���ܵȼ�
	int getSkillLevel(GameObjectSkillType skillType);

    // ��ȡ��ɫ��Ǯ
	int getMoney();

	// �޸Ľ�ɫ��Ǯ
	void setMoney(int money);

	// ��������
	bool saveData(const std::string& fileName);

	// ��������
	bool loadData(const std::string& fileName);

private:

	int _skillExprience[SKILL_KIND_NUM];	// ���ܾ���ֵ����
	int _skillLevel[SKILL_KIND_NUM];		// ���ܵȼ�����
	int _money;                             // ��ɫ��Ǯ
	TileInfo _targetTileNode;				// Ŀ����Ƭ�ڵ���Ϣ
	// ��ȡ��ɫ����ִ�еĶ���(������)
	GameCharacterAction getLeftButtonAction();

	// ��ȡ��ɫ����ִ�еĶ���(����Ҽ�)
	GameCharacterAction getRightButtonAction();

	// �жϽ�ɫ�Ƿ����ִ�ж���
	bool checkActionIsValid(GameCharacterAction action,cocos2d::Vec2& targetTilePos, InteractionManager* interactionManager);

	// ��ȡ��ɫ�����������Ƭ��Ϣ
	TileInfo getTileInfo( InteractionManager* interactionManager, GameCharacterAction action = NoneAction);

	// ���¼��ܵȼ�
	void updateSkillLevel();

	// ���¼��ܾ���ֵ
	void updateSkillExprience(GameCharacterAction gameCharacterAction);


	// ʹ����Ʒ
	void useObject();
};

#endif // !_CHARACTER_ACTION_H_