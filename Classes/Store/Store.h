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

class Store {
public:
	// ���캯��
	Store();

	// �µ�һ��ˢ���̵����
	void refreshStock();

	// ���ݼ��ڸ��¼۸�
	void updatePrices();

private:
	int productKindCount;						// �̵�ÿ�������Ļ�������
	std::vector<SeedProductNode>_seedProduct;		// ������Ʒ����,����
	std::vector<BaseProductNode> _baseProduct;		// ������Ʒ����,����
};

#endif // !__STORE_H__