/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MapStateManager.cpp
 * File Function: 地图保存管理单例类MapStateManager的实现
 * Author:        金恒宇
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#include "MapStateManager.h"

USING_NS_CC;

// 获取单例实例
MapStateManager& MapStateManager::getInstance() {
    static MapStateManager instance;
    return instance;
}

// 保存瓦片更改
void MapStateManager::saveTileChange(const std::string& mapName, const TileConstants::TileChange& change) {
    _mapChanges[mapName].push_back(change);
    CCLOG("Saved tile change: Map='%s', Layer='%s', Tile=(%f, %f), GID=%d",
        mapName.c_str(), change.layerName.c_str(), change.tileCoord.x, change.tileCoord.y, change.newGID);
}

// 获取指定地图的所有更改
const std::vector<TileConstants::TileChange>& MapStateManager::getTileChanges(const std::string& mapName) const {
    static const std::vector<TileConstants::TileChange> emptyChanges;
    auto it = _mapChanges.find(mapName);
    if (it != _mapChanges.end()) {
        return it->second;
    }
    return emptyChanges;
}

// 清除指定地图的所有更改
void MapStateManager::clearTileChanges(const std::string& mapName) {
    _mapChanges.erase(mapName);
    CCLOG("Cleared tile changes for map: '%s'", mapName.c_str());
}


// 保存地图更改到文件
void MapStateManager::saveChangesToFile(const std::string& fileName) const {
    // 打开文件进行二进制写入
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        CCLOG("Error opening file for writing: %s", fileName.c_str()); // 文件打开失败
        return;
    }

    // 写入地图数量
    size_t mapCount = _mapChanges.size();
    outFile.write(reinterpret_cast<const char*>(&mapCount), sizeof(mapCount));

    // 遍历每个地图的更改
    for (const auto& mapPair : _mapChanges) {
        const std::string& mapName = mapPair.first; // 地图名称
        const auto& changes = mapPair.second;      // 地图更改列表

        // 写入地图名称长度和名称
        size_t nameSize = mapName.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(mapName.data(), nameSize);

        // 写入地图更改数量
        size_t changeCount = changes.size();
        outFile.write(reinterpret_cast<const char*>(&changeCount), sizeof(changeCount));

        // 写入每个更改
        for (const auto& change : changes) {
            // 写入图层名称长度和名称
            size_t layerNameSize = change.layerName.size();
            outFile.write(reinterpret_cast<const char*>(&layerNameSize), sizeof(layerNameSize));
            outFile.write(change.layerName.data(), layerNameSize);

            // 写入瓦片坐标和新 GID
            outFile.write(reinterpret_cast<const char*>(&change.tileCoord), sizeof(change.tileCoord));
            outFile.write(reinterpret_cast<const char*>(&change.newGID), sizeof(change.newGID));
        }
    }

    outFile.close(); // 关闭文件
    CCLOG("Map changes saved to file: %s", fileName.c_str()); // 打印保存成功日志
}

// 从文件加载地图更改
void MapStateManager::loadChangesFromFile(const std::string& fileName) {
    // 打开文件进行二进制读取
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        CCLOG("Error opening file for reading: %s", fileName.c_str()); // 文件打开失败
        return;
    }

    _mapChanges.clear(); // 清空现有更改

    // 读取地图数量
    size_t mapCount;
    inFile.read(reinterpret_cast<char*>(&mapCount), sizeof(mapCount));

    // 遍历每个地图
    for (size_t i = 0; i < mapCount; ++i) {
        // 读取地图名称长度和名称
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        std::string mapName(nameSize, '\0');
        inFile.read(&mapName[0], nameSize);

        // 读取地图更改数量
        size_t changeCount;
        inFile.read(reinterpret_cast<char*>(&changeCount), sizeof(changeCount));
        std::vector<TileConstants::TileChange> changes(changeCount);

        // 读取每个更改
        for (size_t j = 0; j < changeCount; ++j) {
            // 读取图层名称长度和名称
            size_t layerNameSize;
            inFile.read(reinterpret_cast<char*>(&layerNameSize), sizeof(layerNameSize));
            std::string layerName(layerNameSize, '\0');
            inFile.read(&layerName[0], layerNameSize);

            TileConstants::TileChange change;
            change.layerName = std::move(layerName); // 使用 std::move 优化赋值

            // 读取瓦片坐标和新 GID
            inFile.read(reinterpret_cast<char*>(&change.tileCoord), sizeof(change.tileCoord));
            inFile.read(reinterpret_cast<char*>(&change.newGID), sizeof(change.newGID));

            changes[j] = std::move(change); // 使用 std::move 优化赋值
        }

        _mapChanges[mapName] = std::move(changes); // 将更改保存到 _mapChanges
    }

    inFile.close(); // 关闭文件
    CCLOG("Map changes loaded from file: %s", fileName.c_str()); // 打印加载成功日志
}