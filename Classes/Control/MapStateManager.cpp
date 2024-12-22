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


// �����ͼ���ĵ��ļ�
void MapStateManager::saveChangesToFile(const std::string& fileName) const {
    // ���ļ����ж�����д��
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        CCLOG("Error opening file for writing: %s", fileName.c_str()); // �ļ���ʧ��
        return;
    }

    // д���ͼ����
    size_t mapCount = _mapChanges.size();
    outFile.write(reinterpret_cast<const char*>(&mapCount), sizeof(mapCount));

    // ����ÿ����ͼ�ĸ���
    for (const auto& mapPair : _mapChanges) {
        const std::string& mapName = mapPair.first; // ��ͼ����
        const auto& changes = mapPair.second;      // ��ͼ�����б�

        // д���ͼ���Ƴ��Ⱥ�����
        size_t nameSize = mapName.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(mapName.data(), nameSize);

        // д���ͼ��������
        size_t changeCount = changes.size();
        outFile.write(reinterpret_cast<const char*>(&changeCount), sizeof(changeCount));

        // д��ÿ������
        for (const auto& change : changes) {
            // д��ͼ�����Ƴ��Ⱥ�����
            size_t layerNameSize = change.layerName.size();
            outFile.write(reinterpret_cast<const char*>(&layerNameSize), sizeof(layerNameSize));
            outFile.write(change.layerName.data(), layerNameSize);

            // д����Ƭ������� GID
            outFile.write(reinterpret_cast<const char*>(&change.tileCoord), sizeof(change.tileCoord));
            outFile.write(reinterpret_cast<const char*>(&change.newGID), sizeof(change.newGID));
        }
    }

    outFile.close(); // �ر��ļ�
    CCLOG("Map changes saved to file: %s", fileName.c_str()); // ��ӡ����ɹ���־
}

// ���ļ����ص�ͼ����
void MapStateManager::loadChangesFromFile(const std::string& fileName) {
    // ���ļ����ж����ƶ�ȡ
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        CCLOG("Error opening file for reading: %s", fileName.c_str()); // �ļ���ʧ��
        return;
    }

    _mapChanges.clear(); // ������и���

    // ��ȡ��ͼ����
    size_t mapCount;
    inFile.read(reinterpret_cast<char*>(&mapCount), sizeof(mapCount));

    // ����ÿ����ͼ
    for (size_t i = 0; i < mapCount; ++i) {
        // ��ȡ��ͼ���Ƴ��Ⱥ�����
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        std::string mapName(nameSize, '\0');
        inFile.read(&mapName[0], nameSize);

        // ��ȡ��ͼ��������
        size_t changeCount;
        inFile.read(reinterpret_cast<char*>(&changeCount), sizeof(changeCount));
        std::vector<TileConstants::TileChange> changes(changeCount);

        // ��ȡÿ������
        for (size_t j = 0; j < changeCount; ++j) {
            // ��ȡͼ�����Ƴ��Ⱥ�����
            size_t layerNameSize;
            inFile.read(reinterpret_cast<char*>(&layerNameSize), sizeof(layerNameSize));
            std::string layerName(layerNameSize, '\0');
            inFile.read(&layerName[0], layerNameSize);

            TileConstants::TileChange change;
            change.layerName = std::move(layerName); // ʹ�� std::move �Ż���ֵ

            // ��ȡ��Ƭ������� GID
            inFile.read(reinterpret_cast<char*>(&change.tileCoord), sizeof(change.tileCoord));
            inFile.read(reinterpret_cast<char*>(&change.newGID), sizeof(change.newGID));

            changes[j] = std::move(change); // ʹ�� std::move �Ż���ֵ
        }

        _mapChanges[mapName] = std::move(changes); // �����ı��浽 _mapChanges
    }

    inFile.close(); // �ر��ļ�
    CCLOG("Map changes loaded from file: %s", fileName.c_str()); // ��ӡ���سɹ���־
}