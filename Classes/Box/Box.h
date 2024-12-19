/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Box.h
 * File Function: ����Box��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/

#pragma once
# ifndef BOX_H
# define BOX_H

# include <vector>
# include "cocos2d.h"
#include "Classes/Character/Character.h"
#include "../proj.win32/Constant.h"

class Box : public cocos2d::Node {
public:
	// ��ȡ����
	static Box& getInstance();
	
	// ��ȡ����
	BoxNode& getBoxList();

	// ��ȡ��������
	int getBoxCount();

	// ��ӵ�������
	bool addBox(const BoxNode& boxNode);

	// �Ƴ���������
	void removeBox();

	// ��������λ��ƥ������
	int matchBoxPosition(cocos2d::Vec2 worldPosition);
	
	// ������Ʒ
	bool storeObject(int objectListIndex, int boxIndex);

	// ������Ʒ
	void swapObject(int startIndex, int targetIndex);

	// ȡ����Ʒ
	void getSelectedObject(int boxIndex,int objectListIndex);

	// ����ָ��λ���Ƿ�����Ʒ
	ObjectListNode findObjectAtPosition(int objectIndex);

	// ��������
	bool saveData(const std::string& fileName);

	// ��������
	bool loadData(const std::string& fileName);
private:
	Character* _character;					// ��ɫָ��
	std::vector<BoxNode> _boxObjectList;	// ���������Ʒ�б�
	int _maxObjectKindCount;				// ���������������
	
	// ���캯��
	Box();
	Box(cocos2d::Vec2 worldPosition, cocos2d::Vec2 tilePosition);

	// �����������Ƿ���ָ����Ʒ
	int findObject( GameCommonObject targetObject);

	// ��������Ƿ�����
	bool checkObjectListFull();
};

#endif // !BOX_H