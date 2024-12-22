/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Task.h
 * File Function: NPC任务类的定义和实现
 * Author:        达思睿
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    // 构造函数
    Task(std::string description, std::string requiredItemName, int requiredItemCount, int affectionReward)
        : _description(description), _requiredItemName(requiredItemName), _requiredItemCount(requiredItemCount),
          _currentItemCount(0), _isCompleted(false), _affectionReward(affectionReward) {}

    // 玩家赠送物品时更新任务进度
    void addItem(std::string itemId, int count) {
        if (itemId == _requiredItemName) {
           _currentItemCount += count;
            if (_currentItemCount >= _requiredItemCount) {
                _isCompleted = true;
            }
        }
    }

    // 检查任务是否完成
    bool checkCompletion() const {
        return _isCompleted;
    }

    // 获取任务描述
    const std::string& getDescription() const {
        return _description;
    }

    // 获取任务奖励（好感度）
    int getAffectionReward() const {
        return _affectionReward;
    }
    // 获取需要的物品数量
    int getRequiredItemCount() const {
        return _requiredItemCount;
    }

    // 设置任务完成状态
    void setCompletion(bool completed) {
        _isCompleted = completed;
    }

    std::string getRequiredItemName() const{
        return  _requiredItemName;
    }
private:
    std::string _description;  // 任务描述
    std::string _requiredItemName;       // 需要的物品名
    int _requiredItemCount;    // 需要的物品数量
    int _currentItemCount;     // 当前物品数量
    bool _isCompleted;         // 任务是否完成
    int _affectionReward;      // 任务奖励：增加的好感度
};

#endif // TASK_H
