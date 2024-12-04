/****************************************************************
 * Project Name:  Stardew Valley
 * File Name:     CharacterObjectList.h
 * File Function: CharacterObjectList��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2023/12/05
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_OBJECT_LIST_H__
#define __CHARACTER_OBJECT_LIST_H__

#include <vector>
#include "cocos2d.h"
#include "../proj.win32/Constant.h"

// ��Ʒ����Ʒ״̬����
typedef enum {
	Unselected,						// δ��ѡ��
	Selected,						// ��ѡ��
}ObjectStatus;

// ��Ʒ��������Ʒ��Ϣ����
typedef struct {
	int id;							// ��Ʒ������
	GameCommonObject object;		// ��Ʒ����
	int count;						// ��Ʒ����
	ObjectStatus status;			// ��Ʒ״̬
}ObjectListNode;



class CharacterObjectList : public cocos2d::Node {
public:
	// ���캯��
	CharacterObjectList();

	// ��������
	~CharacterObjectList();

	// ���¼���ʱ�Ĵ���
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// �������ʱ�Ĵ���
	void onMouseDown(cocos2d::Event* event);

	// ������Ʒ
	bool pickUpObject(GameCommonObject object);	

	// �ƶ���Ʒ
	void moveObject(ObjectListNode object);

private:
	std::vector<ObjectListNode*> _objectList;   // ��Ʒ�б�
	ObjectListNode _currentObject;				// ��ǰ��Ʒ
	int _maxObjectCount;						// �����Ʒ����
	int _currentObjectCount;					// ��ǰ��Ʒ����
	int _currentObjectIndex;					// ��ǰ��Ʒ����

	// ���õ�ǰ��Ʒ
	void setCurrentObject(int index);			

	// ������ǰ��Ʒ
	ObjectListNode discardCurrentObject();
};

#endif // !__CHARACTER_OBJECT_LIST_H__