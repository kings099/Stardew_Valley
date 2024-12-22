/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     Task.h
 * File Function: NPC������Ķ����ʵ��
 * Author:        ��˼�
 * Update Date:   2024/12/18
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    // ���캯��
    Task(std::string description, std::string requiredItemName, int requiredItemCount, int affectionReward)
        : _description(description), _requiredItemName(requiredItemName), _requiredItemCount(requiredItemCount),
          _currentItemCount(0), _isCompleted(false), _affectionReward(affectionReward) {}

    // ���������Ʒʱ�����������
    void addItem(std::string itemId, int count) {
        if (itemId == _requiredItemName) {
           _currentItemCount += count;
            if (_currentItemCount >= _requiredItemCount) {
                _isCompleted = true;
            }
        }
    }

    // ��������Ƿ����
    bool checkCompletion() const {
        return _isCompleted;
    }

    // ��ȡ��������
    const std::string& getDescription() const {
        return _description;
    }

    // ��ȡ���������øжȣ�
    int getAffectionReward() const {
        return _affectionReward;
    }
    // ��ȡ��Ҫ����Ʒ����
    int getRequiredItemCount() const {
        return _requiredItemCount;
    }

    // �����������״̬
    void setCompletion(bool completed) {
        _isCompleted = completed;
    }

    std::string getRequiredItemName() const{
        return  _requiredItemName;
    }
private:
    std::string _description;  // ��������
    std::string _requiredItemName;       // ��Ҫ����Ʒ��
    int _requiredItemCount;    // ��Ҫ����Ʒ����
    int _currentItemCount;     // ��ǰ��Ʒ����
    bool _isCompleted;         // �����Ƿ����
    int _affectionReward;      // �����������ӵĺøж�
};

#endif // TASK_H
