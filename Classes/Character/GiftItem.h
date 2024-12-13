#pragma once
#ifndef GIFITEM_H
#define GIFITEM_H

#include <string>

class GiftItem {
public:
    std::string name;       // ��������
    int affectionValue;     // �������ӵĺøж�ֵ

    GiftItem(std::string name, int affectionValue)
        : name(name), affectionValue(affectionValue) {}
};

#endif // GIFITEM_H
