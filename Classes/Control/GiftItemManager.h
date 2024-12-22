#pragma once
#include "Character/GiftItem.h"
#include <vector>
#include <string>

class GiftItemManager {
public:
    // 获取 GiftItemManager 的单例实例
    static GiftItemManager* getInstance();

    void initializeGifts();  // 初始化礼物
    GiftItem* getGiftByName(const std::string& name);  // 根据名称获取礼物

private:
    GiftItemManager();  // 私有构造函数
    std::vector<GiftItem> _gifts;  // 礼物列表
};
