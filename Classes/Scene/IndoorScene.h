/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorScene.h
 * File Function: ������Ĵ�����ͷ�ļ�
 * Author:        ������
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
#pragma once
#ifndef __INDOOR_SCENE_H__
#define __INDOOR_SCENE_H__

#include "cocos2d.h"
#include "Classes/Scene/FarmScene.h"
#include "Classes/Control/GameViewController.h"  // ����ӽǿ�����ͷ�ļ�
#include "Classes/Maps/IndoorMap.h"
#include "Classes/Layer/UILayer.h"
#include "Classes/Control/InteractionManager.h"

USING_NS_CC;

class IndoorScene : public cocos2d::Scene
{
public:
    // ��������ʼ�����ڵ�ͼ
    static IndoorScene* create(const std::string& mapFile);

    // ��ʼ����ͼ
    bool init(const std::string& mapFile);

    // ��������������
    static cocos2d::Scene* createScene(const std::string& mapFile);


    // �رջص�
    void menuCloseCallback(cocos2d::Ref* pSender);

    //// ���update��������
    //virtual void update(float deltaTime) override;

    //// ���������������
    //virtual ~IndoorScene();
private:
    IndoorMap* indoorMap;         // ��Ƭ��ͼ
    std::unique_ptr<Character> character;           // ��ɫ
    GameViewController* viewController; // �ӽǿ�����
};

#endif  // __INDOOR_SCENE_H__
/****************************************************************
 * Project Name:  Stardew_Valley
 * File Name:     IndoorScene.h
 * File Function: ������Ĵ�����ͷ�ļ�
 * Author:        ������
 * Update Date:   2024/12/6
 * License:       MIT License
 ****************************************************************/
 //#ifndef __INDOOR_MAP_H__
 //#define __INDOOR_MAP_H__
 //
 //#include "cocos2d.h"
 //#include "Classes/Scene/FarmScene.h"
 //#include "Classes/Control/GameViewController.h"  // ����ӽǿ�����ͷ�ļ�
 //#include "Classes/Maps/IndoorMap.h"
 //
 //USING_NS_CC;
 //
 //class IndoorScene : public cocos2d::Scene
 //{
 //public:
 //    // ��������ʼ�����ڵ�ͼ
 //    static IndoorScene* create(const std::string& mapFile);
 //
 //    // ��ʼ����ͼ
 //    bool init(const std::string& mapFile);
 //
 //    // ��������������
 //    static cocos2d::Scene* createScene(const std::string& mapFile);
 //
 //    // ����ɫλ�ò��л�����
 //    void checkCharacterPositionAndSwitchScene();
 //
 //    // �رջص�
 //    void menuCloseCallback(cocos2d::Ref* pSender);
 //
 //private:
 //    IndoorMap* indoorMap;         // ��Ƭ��ͼ
 //    Character* character;             // ��ɫ
 //    GameViewController* viewController; // �ӽǿ�����
 //};
 //
 //#endif  // __INDOOR_MAP_H__
 //#include "cocos2d.h"
 //#include "Classes/Maps/IndoorMap.h"
 //#include "Classes/Character/Character.h"
 //#include "Classes/Control/GameViewController.h"
 //#include "Classes/Layer/UILayer.h"
 //#include "Classes/Control/InteractionManager.h"
 //
 //
 //class IndoorScene : public cocos2d::Scene
 //{
 //public:
 //    // ��������
 //    static cocos2d::Scene* createScene();
 //
 //    // ��ʼ��
 //    virtual bool init();
 //
 //    // �رջص�
 //    void menuCloseCallback(cocos2d::Ref* pSender);
 //
 //    // ʵ�� create() ����
 //    CREATE_FUNC(IndoorScene);
 //
 //private:
 //    // ũ����ͼ
 //    IndoorMap* indoorMap;
 //
 //    // ��ɫ
 //    Character* character;
 //
 //    // �ӽǿ�����
 //    GameViewController* viewController;
 //
 //    // UI��
 //    UILayer* uiLayer;
 //};
 //#include "cocos2d.h"
 //#include "Classes/Scene/FarmScene.h"
 //#include "Classes/Control/GameViewController.h"  // ����ӽǿ�����ͷ�ļ�
 //#include "Classes/Maps/IndoorMap.h"
 //USING_NS_CC;
 //class IndoorScene : public cocos2d::Scene
 //{
 //public:
 //    // ��������ʼ�����ڵ�ͼ
 //    static IndoorScene* create(const std::string& mapFile);
 //    // ��ʼ����ͼ
 //    bool init(const std::string& mapFile);
 //    // ��������������
 //    static cocos2d::Scene* createScene(const std::string& mapFile);
 //    // ����ɫλ�ò��л�����
 //    void checkCharacterPositionAndSwitchScene();
 //    // �رջص�
 //    void menuCloseCallback(cocos2d::Ref* pSender);
 //private:
 //    IndoorMap* indoorMap;         // ��Ƭ��ͼ
 //    Character* character;             // ��ɫ
 //    GameViewController* viewController; // �ӽǿ�����
 //};
 //#endif // __INDOOR_SCENE_H__