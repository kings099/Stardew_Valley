/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Store.h
 * File Function: �̵�Store��Ķ���
 * Author:        ���ϳ�
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef __STORE_H__
#define __STORE_H__

#include <string>
#include <vector>
#include <map>
#include "Character/Character.h"
#include "Control/TimeManager.h"

class Store {
public:
	// ��ȡ����
	static Store* getInstance();

	// �µ�һ��ˢ���̵����
	void refreshStock();

	// ������Ʒ
	bool buyProduct(int index);

	// ������Ʒ
	bool sellProduct(const GameSeedObject targetObject,int objectCount);

	// ������Ʒ
	bool sellProduct(const GameBaseObject targetObject, int objectCount);

	// ������Ʒ
	bool sellProduct(const GameCommonObject targetObject, int totalPrice);

	// ����ָ��λ�õ���Ʒ��Ϣ
	ProductNode findObjectAtPosition(int index);

	// �ص�����
	void setSellProductCallback(std::function<void(bool)> callback);

	std::function<void(bool)> _sellProductCallback;  // ���ڱ���ص�
private:
	Character *_character;					// ��ҽ�ɫ
	TimeManager* _timeManager;				// ʱ�������
	int productKindCount;					// �̵�ÿ�������Ļ�������
	std::vector<ProductNode>_product;		// ��Ʒ����,����

	// ���캯��
	Store();

	// �ж���Ʒ�Ƿ������ӵ��ջ���
	bool canHarvestFromAnySeed(const GameBaseObject& baseObject, GameSeedObject* seedObject);

	// ���ݼ��ڸ��¼۸�
	void updatePrices();

	// TODO�����ݺøжȸ��¼۸�
	// void updatePricesByLove();
};

#endif // !__STORE_H__