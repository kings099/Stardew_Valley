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
<<<<<<< Updated upstream
	int id;							// ��Ʒ������
	GameCommonObject object;		// ��Ʒ����
=======
	GameCommonObject objectNode;	// ��Ʒ����
>>>>>>> Stashed changes
	int count;						// ��Ʒ����
	ObjectStatus status;			// ��Ʒ״̬
}ObjectListNode;


<<<<<<< Updated upstream

class CharacterObjectList : public cocos2d::Node {
=======
class CharacterObjectList : virtual public cocos2d::Node {
>>>>>>> Stashed changes
public:
	// ���캯��
	CharacterObjectList();

<<<<<<< Updated upstream
	// ��������
	~CharacterObjectList();

	// ���¼���ʱ�Ĵ���
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// �������ʱ�Ĵ���
	void onMouseDown(cocos2d::Event* event);

	// ������Ʒ
	bool pickUpObject(GameCommonObject object);	
=======
	// ���¼���ʱ�Ĵ���
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// ������Ʒ
	bool pickUpObject(GameCommonObject targetObject, int objectCount);
>>>>>>> Stashed changes

	// �ƶ���Ʒ
	void moveObject(ObjectListNode object);

<<<<<<< Updated upstream
private:
	std::vector<ObjectListNode*> _objectList;   // ��Ʒ�б�
	ObjectListNode _currentObject;				// ��ǰ��Ʒ
	int _maxObjectCount;						// �����Ʒ����
	int _currentObjectCount;					// ��ǰ��Ʒ����
	int _currentObjectIndex;					// ��ǰ��Ʒ����
=======
	// ��ȡ��ǰ��Ʒ����������Ʒ
	ObjectListNode getCurrentObject();

	// �����Ʒ���Ƿ�����
	bool checkObjectListFull();
protected:
	bool openObjectList;						// �Ƿ����Ʒ��

private:
	std::vector<ObjectListNode> _objectList;	// ��Ʒ�б�
	int _maxObjectCount;						// �����Ʒ����
	int _currentObjectKindCount;				// ��ǰ��Ʒ��������
	int _currentObjectIndex;					// ��ǰ��Ʒ������
	// ��ʼ����Ʒ������
	void initObjectList();
>>>>>>> Stashed changes

	// ���õ�ǰ��Ʒ
	void setCurrentObject(int index);			

	// ������ǰ��Ʒ
	ObjectListNode discardCurrentObject();
<<<<<<< Updated upstream
=======

	// ����ָ����Ʒ
	int findObject(GameCommonObject targetObject);
>>>>>>> Stashed changes
};

#endif // !__CHARACTER_OBJECT_LIST_H__