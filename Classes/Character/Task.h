#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    // 构造函数
    Task(std::string description, int requiredItemId, int requiredItemCount, int affectionReward)
        : description(description), requiredItemId(requiredItemId), requiredItemCount(requiredItemCount),
          currentItemCount(0), isCompleted(false), affectionReward(affectionReward) {}

    // 玩家赠送物品时更新任务进度
    void addItem(int itemId, int count) {
        if (itemId == requiredItemId) {
            currentItemCount += count;
            if (currentItemCount >= requiredItemCount) {
                isCompleted = true;
            }
        }
    }

    // 检查任务是否完成
    bool checkCompletion() const {
        return isCompleted;
    }

    // 获取任务描述
    const std::string& getDescription() const {
        return description;
    }

    // 获取任务奖励（好感度）
    int getAffectionReward() const {
        return affectionReward;
    }

    int getRequiredItemId() const {
        return requiredItemId;
    }
    // 设置任务完成状态
    void setCompletion(bool completed) {
        isCompleted = completed;
    }

private:
    std::string description;  // 任务描述
    int requiredItemId;       // 需要的物品 ID
    int requiredItemCount;    // 需要的物品数量
    int currentItemCount;     // 当前物品数量
    bool isCompleted;         // 任务是否完成
    int affectionReward;      // 任务奖励：增加的好感度
};

#endif // TASK_H
