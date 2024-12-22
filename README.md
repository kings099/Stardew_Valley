# Stardew_Valley

星露谷物语[Sprit-Sheet-Resource](https://www.spriters-resource.com/pc_computer/stardewvalley/)

## 项目名称

Stardew_Valley

## 项目简介

A project of Stardew Valley based on [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual).

基于 [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual) 开发的星露谷游戏项目。

> * Programing Paradigm 2024 (2024年同济大学程序设计范式)

该项目是一个基于 [Cocos2d-x 3.17.2](https://docs.cocos.com/cocos2d-x/manual) 开发的星露谷游戏，灵感来自于《星露谷》《我的世界》等游戏，玩家将管理⾃⼰的农场，种植作物，养殖动物，与镇上的居⺠互动，参与节⽇活动，并探索周围的⾃然环境。

---
## 成员分工

| 姓名 | 学号 | 分工 |
| :---: | :---: | :---: |
| 尹诚成 (组长) | 2351279 |**项目后端与UI设计** <br>代码审查 <br>`Character`类 <br>`CharacterAction`类 <br>`CharacterObjectList`类 <br>`CharacterMove`类 <br>`Box`类 <br>`PlacementMarkerLayer`类 <br>`UILayer`类 <br>`LoactionMap`类 <br>`HoverMenuItemImage`类 |
| 金恒宇 | 2352280 |**项目后端与前端对接** <br>地图类统筹 <br>`GameViewControlle`类 <br>`InteractionManager`类 <br>`MapStateManager`类 <br>`MapSwitchManager`类 <br>`GameMap`类 <br>`FarmMap`类 <br>`TownMap`类 <br>`MineMap`类 <br>`IndoorLighting`类<br> `GameMainScene`类 <br> 农场地图绘制 小镇地图绘制|
| 达思睿 | 2352288 |**UI设计与NPC交互**  <br> `CharacterInfo` 类<br> `HelloWorldScene` 类 <br> `UILayer` 类<br> `TimeManager` 类 <br> `NPC` 类 <br> `NPCManager` 类 <br> `GiftItem` 类 <br> `GiftItemManager` 类  <br> `Task` 类<br> `LoginLayer` 类<br> `FestivalLayer` 类<br> `ChatLayer` 类<br> `AudioControlLayer` 类 <br> 图标按钮绘制 <br> 启动场景绘制 <br> 音频引擎  |
| 胡宝怡 | 2353409 | |

## 成员贡献

| 姓名 | 学号 | 总提交行数 |.h和.cpp文件提交行数 | 工作量 |
| :---: | :---: | :---: | :---: | :---: |
| 尹诚成 (组长) | 2351279 |  |  |  |
| 金恒宇 | 2352280 |  |  |  |
| 达思睿 | 2352288 |  |  |  |
| 胡宝怡 | 2353409 |  |  |  |

## 项目组成

* `/Classes`
类定义与类实现

* `/Resources`
资源文件

* `/GameData`
游戏数据

* `/cocos2d`
依赖文件

* `/proj.win32`
游戏程序

## 项目实现功能与项目技术细节

### 基础功能

* [X] 有初始界面
* [X] 支持背景音效
* [X] 支持耕种、种植、收获农作物等操作
* [X] 支持养殖动物并获取相关畜产品
* [X] 支持对游戏内物品资源的存储
* [X] 支持与小镇上的NPC居民建立关系
* [X] 支持接受居民委托的相关任务
* [X] 支持挖掘矿物，钓鱼和收集稀有物品
* [X] 支持技能升级以及随技能提升解锁新的物品

### 拓展功能
* [X] 支持存档功能
* [X] 支持合成物品

### 项目开发日志

#### 2024.11.22
- Cocos2d-x 3.17.2及相关环境配置  
- Markdown 基本语言掌握

#### 2024.11.23
- git 工具学习
- GitHub Desktop 工具学习

#### 2024.11.24
- 明确项目代码规范
- 明确git提交规范
- 创建项目托管GitHub仓库
- Cocos2d-x学习

#### 2024.11.25-11.29
- git 和 GitHub 补漏
- Cocos2d-x学习

#### 2024.12.01
- 明确项目仓库组成
- 讨论确定具体实现功能内容
- 初步确定成员分工

#### 2024.12.03
- 初步实现 `CharacterMove` 类
- 初步完成瓦片地图文件搭建
- 初步实现 `FarmMap` 类

#### 2024.12.04
- 初步实现 `GameViewController` 类
- 调整 `CharacterMove` 类

#### 2024.12.05
- 初步实现 `TimeManager` 类
- 初步实现 `FarmScene` 类
- 初步实现 `CharacterInfo` 类
- 调整 `GameViewController` 类
- 实现 `StartUpScene` 类

#### 2024.12.06
- 初步实现 `CharacterObjectList` 类
- 实现物品数据设计
- 调整 `Character` 类

#### 2024.12.07
- 初步实现 `HoverMenuItemImage` 类
- 基本实现 `InteractionManager` 类
- 调整 `CharacterMove` 类
- 调整物品数据设计

#### 2024.12.07
- 基本实现 `GameMap` 类
- 调整 `FarmMap` 类
- 调整 `GameViewController` 类

#### 2024.12.09
- 初步实现 `UILayer` 类
- 实现 `TimeManager` 类
- 实现 `TimeManagerUI` 类
- 将 `TimeManagerUI` 类合并到 `UILayer` 类中
- 调整 `Character` 类
- 调整 `HoverMenuItemImage` 类

#### 2024.12.11
- 实现 `IndoorMap` 类
- 实现 `IndoorScene` 类
- 初步实现 `SceneSwitcher` 类
- 工作对接

#### 2024.12.12
- 调整 `InteractionManager` 类
- 实现 `MapSwitchManager` 类
- 初步实现 `Crop` 类
- 初步实现 `NPC` 类

#### 2024.12.13
- 弃用 `SceneSwitcher` 类
- 弃用 `IndoorScene` 类
- 基本实现 `UILayer` 类
- 调整 `Character` 及其基类
- 实现 `PlacementMarkerLayer` 类
- 实现 `LocationMap` 类
- 初步实现 `CharacterAction` 类
- 调整地图文件
- 实现人物移动碰撞检测

#### 2024.12.14
- 调整 `characterAction` 类
- 调整 `InteractionManager` 类
- 初步实现存储和读取角色信息功能

#### 2024.12.15
- 基本实现存储和读取角色信息功能
- 进一步实现 `Crop` 类
- 调整 `FarmMap` 类
- 调整 `GameMap` 类

#### 2024.12.16
- 弃用 `FarmMapScene` 类
- 初步实现 `Animation` 类
- 实现  `GameMainScene` 类 
- 完善 `UILayer` 类
- 调整 `LocationMap` 类
- 调整 `Character` 类及其基类
- 调整 `InteractionManager` 类

#### 2024.12.17
- 初步实现 `AudioControlUI` 类
- 初步实现 `AudioControlLayer` 类
- 初步实现 `ChatLayer` 类
- 初步实现 `Animal` 类
- 进一步实现 `NPC` 类
- 基本实现 `Crop` 类

#### 2024.12.18
- 初步实现 `Task` 类
- 初步实现 `Box` 类
- 基本实现 `NPC` 类
- 调整 `UILayer` 类

#### 2024.12.19
- 基本实现 `Fish` 类
- 基本实现 `Box` 类
- 实现 `TownMap` 类
- 调整 `GameViewController` 类
- 调整 `Character` 类及其基类
- 调整 `UILayer` 类

#### 2024.12.20
- 基本实现 `Store` 类
- 实现 `Fish` 类
- 实现 `Animal` 类
- 实现 `MapStateManager` 类
- 实现 `MineMap` 类
- 完善 `FarmMap` 类

#### 2024.12.21
- 调整 `Fish` 类
- 调整 `Character` 及其基类
- 完善 `UILayer` 类
- 调整UI与用户交互细节
- 基本实现市场经济系统


---
#### 文档更新日期：2024年12月22日
