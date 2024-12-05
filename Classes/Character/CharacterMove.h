/****************************************************************
 * Project Name:  Stardew Valley
<<<<<<< Updated upstream
 * File Name:     Character.h
 * File Function: CharacterÀàµÄ¶¨Òå
 * Author:        Òü³Ï³É
 * Update Date:   2023/12/03
=======
 * File Name:     CharacterMove.h
 * File Function: CharacterMoveç±»çš„å®šä¹‰
 * Author:        å°¹è¯šæˆ
 * Update Date:   2023/12/04
>>>>>>> Stashed changes
 * License:       MIT License
 ****************************************************************/

#ifndef __CHARACTER_MOVE_H__
#define __CHARACTER_MOVE_H__

#include "cocos2d.h"
<<<<<<< Updated upstream
#include <unordered_map>
=======

>>>>>>> Stashed changes

class CharacterMove : virtual public cocos2d::Node {
public:
    //æ„é€ å‡½æ•°
    CharacterMove();

    // æŒ‰ä¸‹é”®ç›˜æ—¶çš„å¤„ç†
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // é‡Šæ”¾é”®ç›˜æ—¶çš„å¤„ç†
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // æ’­æ”¾åŠ¨ç”»
    void playAnimation();

protected:
    cocos2d::Sprite* _character;                         // è§’è‰²å¯¹è±¡

    // æ›´æ–°è§’è‰²ä½ç½®
    cocos2d::Vec2 updatePosition(float deltaTime);
private:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    cocos2d::Sprite* character;                         // ½ÇÉ«¶ÔÏó
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;      // ½ÇÉ«¶¯»­Ö¡
    float width;                                        // ½ÇÉ«¿í¶È
    float height;                                       // ½ÇÉ«¸ß¶È
    float moveSpeed;                                    // ½ÇÉ«ËÙ¶È
    bool moveUp;                                        // ÊÇ·ñÉÏÒÆ
    bool moveDown;                                      // ÊÇ·ñÏÂÒÆ
    bool moveLeft;                                      // ÊÇ·ñ×óÒÆ
    bool moveRight;                                     // ÊÇ·ñÓÒÒÆ
    bool animationPlaying;                              // ÊÇ·ñÕıÔÚ²¥·Å¶¯»­
    std::string currentDirection;                       // µ±Ç°¶¯»­·½Ïò
    std::string lastDirection;                          // ÉÏÒ»´Î¶¯»­·½Ïò
=======
    cocos2d::Sprite* _character;                         // ½ÇÉ«¶ÔÏó
    cocos2d::Vector<cocos2d::SpriteFrame*> _frames;      // ½ÇÉ«¶¯»­Ö¡
    float _width;                                        // ½ÇÉ«¿í¶È
    float _height;                                       // ½ÇÉ«¸ß¶È
    float _moveSpeed;                                    // ½ÇÉ«ËÙ¶È
    bool _moveUp;                                        // ÊÇ·ñÉÏÒÆ
    bool _moveDown;                                      // ÊÇ·ñÏÂÒÆ
    bool _moveLeft;                                      // ÊÇ·ñ×óÒÆ
    bool _moveRight;                                     // ÊÇ·ñÓÒÒÆ
    bool _animationPlaying;                              // ÊÇ·ñÕıÔÚ²¥·Å¶¯»­
    std::string _currentDirection;                       // µ±Ç°¶¯»­·½Ïò
    std::string _lastDirection;                          // ÉÏÒ»´Î¶¯»­·½Ïò
>>>>>>> Stashed changes
=======
    cocos2d::Vector<cocos2d::SpriteFrame*> _frames;      // è§’è‰²åŠ¨ç”»å¸§
    float _width;                                        // è§’è‰²å®½åº¦
    float _height;                                       // è§’è‰²é«˜åº¦
    float _moveSpeed;                                    // è§’è‰²é€Ÿåº¦
    bool _moveUp;                                        // æ˜¯å¦ä¸Šç§»
    bool _moveDown;                                      // æ˜¯å¦ä¸‹ç§»
    bool _moveLeft;                                      // æ˜¯å¦å·¦ç§»
    bool _moveRight;                                     // æ˜¯å¦å³ç§»
    bool _animationPlaying;                              // æ˜¯å¦æ­£åœ¨æ’­æ”¾åŠ¨ç”»
    std::string _currentDirection;                       // å½“å‰åŠ¨ç”»æ–¹å‘
    std::string _lastDirection;                          // ä¸Šä¸€æ¬¡åŠ¨ç”»æ–¹å‘


>>>>>>> Stashed changes
};

#endif // __CHARACTER_H__
