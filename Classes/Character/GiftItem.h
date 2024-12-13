#pragma once
#ifndef GIFITEM_H
#define GIFITEM_H

#include <string>

class GiftItem {
public:
    std::string name;       // 礼物名称
    int affectionValue;     // 礼物增加的好感度值

    GiftItem(std::string name, int affectionValue)
        : name(name), affectionValue(affectionValue) {}
};

#endif // GIFITEM_H
