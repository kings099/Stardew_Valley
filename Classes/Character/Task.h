#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    // ���캯��
    Task(std::string description, int requiredItemId, int requiredItemCount, int affectionReward)
        : description(description), requiredItemId(requiredItemId), requiredItemCount(requiredItemCount),
          currentItemCount(0), isCompleted(false), affectionReward(affectionReward) {}

    // ���������Ʒʱ�����������
    void addItem(int itemId, int count) {
        if (itemId == requiredItemId) {
            currentItemCount += count;
            if (currentItemCount >= requiredItemCount) {
                isCompleted = true;
            }
        }
    }

    // ��������Ƿ����
    bool checkCompletion() const {
        return isCompleted;
    }

    // ��ȡ��������
    const std::string& getDescription() const {
        return description;
    }

    // ��ȡ���������øжȣ�
    int getAffectionReward() const {
        return affectionReward;
    }

    int getRequiredItemId() const {
        return requiredItemId;
    }
    // �����������״̬
    void setCompletion(bool completed) {
        isCompleted = completed;
    }

private:
    std::string description;  // ��������
    int requiredItemId;       // ��Ҫ����Ʒ ID
    int requiredItemCount;    // ��Ҫ����Ʒ����
    int currentItemCount;     // ��ǰ��Ʒ����
    bool isCompleted;         // �����Ƿ����
    int affectionReward;      // �����������ӵĺøж�
};

#endif // TASK_H
