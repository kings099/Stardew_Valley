/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapStateManager.cpp
 * File Function: ��ͼ�����������MapStateManager��ʵ��
 * Author:        �����
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#include "MapStateManager.h"

USING_NS_CC;

// ��ȡ����ʵ��
MapStateManager& MapStateManager::getInstance() {
    static MapStateManager instance;
    return instance;
}

// ������Ƭ����
void MapStateManager::saveTileChange(const std::string& mapName, const TileConstants::TileChange& change) {
    _mapChanges[mapName].push_back(change);
    CCLOG("Saved tile change: Map='%s', Layer='%s', Tile=(%f, %f), GID=%d",
        mapName.c_str(), change.layerName.c_str(), change.tileCoord.x, change.tileCoord.y, change.newGID);
}

// ��ȡָ����ͼ�����и���
const std::vector<TileConstants::TileChange>& MapStateManager::getTileChanges(const std::string& mapName) const {
    static const std::vector<TileConstants::TileChange> emptyChanges;
    auto it = _mapChanges.find(mapName);
    if (it != _mapChanges.end()) {
        return it->second;
    }
    return emptyChanges;
}

// ���ָ����ͼ�����и���
void MapStateManager::clearTileChanges(const std::string& mapName) {
    _mapChanges.erase(mapName);
    CCLOG("Cleared tile changes for map: '%s'", mapName.c_str());
}
