/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     MineMap.cpp
 * File Function: ��ʼ���󶴵�ͼ
 * Author:        �������������
 * Update Date:   2024/12/20
 * License:       MIT License
 ****************************************************************/
#include "MineMap.h"

USING_NS_CC;

MineMap::MineMap(const Vec2& mapPosition)
    : GameMap(mapPosition) {}


MineMap::~MineMap()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}

MineMap* MineMap::create(const std::string& mapFile, const Vec2& mapPosition)
{
    MineMap* ret = new MineMap(mapPosition);
    if (ret && ret->init(mapFile, mapPosition)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool MineMap::init(const std::string& mapFile, const Vec2& mapPosition)
{
    // ���ø���ĳ�ʼ������
    if (!GameMap::init(mapFile, mapPosition)) {
        return false;
    }
    _mapName = mapFile;
    _map_position = mapPosition;
    this->setScale(INDOOR_MAP_SCALE);

    return true;
}

// �ɿ��ͼ�ĸ��ĵؿ��߼���д
void MineMap::replaceTileAt(const std::string& layerName, const Vec2& tileCoord, int newGID, bool isUserAction) {
    // ��ȡĿ��ͼ��
    auto layer = _tile_map->getLayer(layerName);
    if (!layer) {
        CCLOG("Layer '%s' not found!", layerName.c_str());
        return;
    }

    // �����Ƭ�����Ƿ��ڵ�ͼ��Χ��
    auto mapSize = _tile_map->getMapSize(); // ��ͼ����Ƭ�ߴ磨�����Ƭ����
    if (tileCoord.x < 0 || tileCoord.y < 0 || tileCoord.x >= mapSize.width || tileCoord.y >= mapSize.height) {
        CCLOG("Tile position (%f, %f) is out of bounds!", tileCoord.x, tileCoord.y);
        return;
    }

    // �����µ���Ƭ GID
    layer->setTileGID(newGID, tileCoord);
    CCLOG("Replaced tile at (%f, %f) on layer '%s' with GID=%d", tileCoord.x, tileCoord.y, layerName.c_str(), newGID);

    // ������û���Ϊ���������߼������û���Ϊ����Ӧ�ñ���ĸ��ģ������棬������ѭ��
    if (isUserAction) {
        // ��ȡ��ǰ��Ƭ�� TileInfo
        TileConstants::TileType tiletype = getTileTypeAt(tileCoord);

        // ���� TileInfo ���ʹ���
        if (tiletype == TileConstants::TileType::Treasure) {
            // �����Ƭ����Ϊ "Treasure"��ֱ�ӱ������
            MapStateManager::getInstance().saveTileChange(
                _mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
            CCLOG("Treasure tile at (%f, %f) saved with new GID=%d", tileCoord.x, tileCoord.y, newGID);
        }
        else if (tiletype == TileConstants::TileType::Mine) {
            // �����Ƭ����Ϊ "Mine"��20% �ĸ��ʱ���ٻ�״̬
            float randomValue = CCRANDOM_0_1(); // ��������� [0, 1]
            if (randomValue <= 0.2f) {
                // �����������ʱ�������
                MapStateManager::getInstance().saveTileChange(
                    _mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
                CCLOG("Mine tile at (%f, %f) recorded for destruction (20%% chance triggered)", tileCoord.x, tileCoord.y);
            }
            else {
                // δ�����������ʱ��������
                CCLOG("Mine tile at (%f, %f) not recorded for destruction (20%% chance not triggered)", tileCoord.x, tileCoord.y);
            }
        }
        else {
            // ������Ƭ����ֱ�ӱ���
            MapStateManager::getInstance().saveTileChange(
                _mapName, TileConstants::TileChange(layerName, tileCoord, newGID));
            CCLOG("Tile at (%f, %f) of type '%d' saved with new GID=%d", tileCoord.x, tileCoord.y, tiletype, newGID);
        }
    }
}

// ��ȡָ����Ƭ������
TileConstants::TileType MineMap::getTileTypeAt(const Vec2& tileCoord) const {
    int layerGID = this->getTileGIDAt("ore", tileCoord); 
    if (layerGID == 0) {
        CCLOG("No tile found at (%f, %f)", tileCoord.x, tileCoord.y);
        return TileConstants::TileType::Other; // ����Ĭ������
    }

    // ��ȡ��Ƭ��������Ϣ
    ValueMap tileProps = this->getTilePropertiesForGID(layerGID);

    // �ж���Ƭ����
    if (tileProps.find("isSteel") != tileProps.end() && tileProps["isSteel"].asBool()) {
        return TileConstants::TileType::Mine; // ��ʯ���ͣ��ֿ�
    }
    else if (tileProps.find("isCopper") != tileProps.end() && tileProps["isCopper"].asBool()) {
        return TileConstants::TileType::Mine; // ��ʯ���ͣ�ͭ��
    }
    else if (tileProps.find("isTreasure") != tileProps.end() && tileProps["isTreasure"].asBool()) {
        return TileConstants::TileType::Treasure; // ��������
    }
    else if (tileProps.find("isRing") != tileProps.end() && tileProps["isRing"].asBool()) {
        return TileConstants::TileType::Treasure; // ��ָ����
    }

    return TileConstants::TileType::Other; // ��������
}