/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.h
 * File Function: ����Box��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2024/12/17
 * License:       MIT License
 ****************************************************************/

#pragma once
# ifndef BOX_H
# define BOX_H

# include <vector>
# include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "../proj.win32/Constant.h"

struct BoxNode {
	std::vector<ObjectListNode> _boxObjectList;	// ���������Ʒ�б�
	int _maxObjectKindCount;						// �����������
	cocos2d::Vec2 _worldPosition;					// ��������
	cocos2d::Vec2 _tilePosition;					// ������Ƭ���ꡢ

	// ���캯��
	BoxNode() :
		_maxObjectKindCount(OBJECT_LIST_COLS)
	{
		_boxObjectList.resize(_maxObjectKindCount);
	}

	BoxNode(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition) :
		_maxObjectKindCount(OBJECT_LIST_COLS),
		_worldPosition(worldPosition),
		_tilePosition(tilePosition)
	{
		_boxObjectList.resize(_maxObjectKindCount);
	}
};

class Box : public cocos2d::Node {
public:
	// ��ȡ����
	static Box& getInstace();
	
	// ��ȡ���������б�
	std::vector<BoxNode>& getBoxList();

	// ��ӵ�������
	void addBox(const BoxNode& boxNode);

	// ��������λ��ƥ������
	int matchBoxPosition(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition);
	
	// ������Ʒ
	bool storeObject(int boxListIndex,GameToolObject targetObject, int objectCount, int targetIndex);

	// ������Ʒ
	bool storeObject(int boxListIndex, GameSeedObject targetObject, int objectCount, int targetIndex);

	// ������Ʒ
	bool storeObject(int boxListIndex, GameBaseObject targetObject, int objectCount, int targetIndex);

	// ������Ʒ
	void swapObject(int boxListIndex, int startIndex, int targetIndex);

	// ȡ����ǰѡ�е���Ʒ
	void getSelectedObject(int boxListIndex,int boxIndex,int objectListIndex);

	// ����ָ��λ���Ƿ�����Ʒ
	ObjectListNode findObjectAtPosition(int boxListIndex,int objectIndex);

	
private:
	Character* _character;					// ��ɫָ��
	std::vector<BoxNode> _boxObjectList;	// ���������Ʒ�б�
	int _maxObjectKindCount;				// ���������������
	
	// ���캯��
	Box();
	Box(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition);

	// �����������Ƿ���ָ����Ʒ
	int findObject(int boxListIndex, GameCommonObject targetObject);

	// ������Ʒ
	bool storeObject(int boxListIndex, GameCommonObject targetObject, int objectCount,int targetIndex);

	// ��������Ƿ�����
	bool checkObjectListFull(int boxListIndex);
};

#endif // !BOX_H