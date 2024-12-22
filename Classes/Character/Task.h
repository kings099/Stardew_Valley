#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    // ���캯��
    Task(std::string description, std::string requiredItemName, int requiredItemCount, int affectionReward)
        : description(description), requiredItemName(requiredItemName), requiredItemCount(requiredItemCount),
          currentItemCount(0), isCompleted(false), affectionReward(affectionReward) {}

    // ���������Ʒʱ�����������
    void addItem(std::string itemId, int count) {
        if (itemId == requiredItemName) {
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
    // ��ȡ��Ҫ����Ʒ����
    int getRequiredItemCount() const {
        return requiredItemCount;
    }

    // �����������״̬
    void setCompletion(bool completed) {
        isCompleted = completed;
    }

    std::string getRequiredItemName() const{
        return  requiredItemName;
    }
private:
    std::string description;  // ��������
    std::string requiredItemName;       // ��Ҫ����Ʒ��
    int requiredItemCount;    // ��Ҫ����Ʒ����
    int currentItemCount;     // ��ǰ��Ʒ����
    bool isCompleted;         // �����Ƿ����
    int affectionReward;      // �����������ӵĺøж�
};

#endif // TASK_H
