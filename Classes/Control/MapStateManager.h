/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapStateManager.cpp
 * File Function: ��ͼ�����������MapStateManager��ʵ��
 * Author:        �����
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef MAP_STATE_MANAGER_H_
#define MAP_STATE_MANAGER_H_

#include <unordered_map>
#include <vector>
#include <string>
#include "proj.win32/Constant.h"
#include "cocos2d.h"


class MapStateManager {
public:
    // ��ȡ����ʵ��
    static MapStateManager& getInstance();

    // ������Ƭ����
    void saveTileChange(const std::string& mapName, const TileConstants::TileChange& change);

    // ��ȡָ����ͼ�����и���
    const std::vector<TileConstants::TileChange>& getTileChanges(const std::string& mapName) const;

    // ���ָ����ͼ�����и���
    void clearTileChanges(const std::string& mapName);

private:
    // ���캯������������˽�л�
    MapStateManager() = default;
    ~MapStateManager() = default;

    // ���ÿ�������͸�ֵ�����
    MapStateManager(const MapStateManager&) = delete;
    MapStateManager& operator=(const MapStateManager&) = delete;

    // �洢ÿ�ŵ�ͼ����Ƭ����
    std::unordered_map<std::string, std::vector<TileConstants::TileChange>> _mapChanges;
};
#endif // MAP_STATE_MANAGER_H_
