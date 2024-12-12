#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <memory>
#include <map>
#include "cocos2d.h"
#include "ObjectConstant.h"

// Ó¦ÓÃ³ÌÐòÉèÖÃ
constexpr int DESIGN_RESOLUTION_WIDTH = 1920;                               // Éè¼Æ·Ö±æÂÊ¿í¶È
constexpr int DESIGN_RESOLUTION_HEIGHT = 1080;                              // Éè¼Æ·Ö±æÂÊ¸ß¶È
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                 // Ð¡·Ö±æÂÊ¿í¶È
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                // Ð¡·Ö±æÂÊ¸ß¶È
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                               // ÖÐ·Ö±æÂÊ¿í¶È
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                               // ÖÐ·Ö±æÂÊ¸ß¶È
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                // ´ó·Ö±æÂÊ¿í¶È
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                               // ´ó·Ö±æÂÊ¸ß¶È
constexpr float FRAME_RATE = 60.0f;                                         // Ó¦ÓÃ³ÌÐòÖ¡ÂÊ
const std::string APPLICATION_TITLE = u8"ÐÇÂ¶¹È Stardew Valley";				// Ó¦ÓÃ³ÌÐò±êÌâ


//½ÇÉ«²âÊÔÓÃ³£±äÁ¿
constexpr float MOVE_SPEED = 3.5f;											// ÒÆ¶¯ËÙ¶È
constexpr float MOVE_RATE = FRAME_RATE;										// ÒÆ¶¯Ö¡ÂÊ
constexpr auto INVIAID_KEY = cocos2d::EventKeyboard::KeyCode::KEY_NONE;		// ÎÞÐ§°´¼ü
constexpr float ACTION_RATE = 5.0f;											// ¶¯×÷¼ä¸ôÖ¡ÂÊ
constexpr int INVAVID_NUM = -1;												// ÎÞÐ§Êý×Ö

// ½ÇÉ«ÊôÐÔ
constexpr int CHARACTER_WIDTH = 32;											// ½ÇÉ«¿í¶È
constexpr int CHARACTER_HEIGHT = 32;										// ½ÇÉ«¸ß¶È
constexpr float CHARACTER_MOVE_SPEED = 5.0f;								// ÒÆ¶¯ËÙ¶È

<<<<<<< Updated upstream
// µØÍ¼ÉèÖÃ
constexpr float LERP_SPEED = 0.1f;											// ÊÓ½Ç¹ý¶ÉµÄÆ½»¬¶È
constexpr float SCENE_TRANSITION_TIME = 1.0f;								// ³¡¾°¹ý¶ÉÊ±¼ä
constexpr float FARM_MAP_SCALE = 2.0f;										// µØÍ¼Ëõ·Å´óÐ¡


// ÎïÆ·À¸ÉèÖÃ
constexpr int OBJECT_LIST_ROWS = 3;											// ÎïÆ·À¸ÐÐÊý
constexpr int OBJECT_LIST_COLS = 12;										// ÎïÆ·À¸ÁÐÊý
=======
// ç‰©å“è®¾ç½®
constexpr int OBJECT_LIST_ROWS = 3;											// ç‰©å“åˆ—è¡¨è¡Œæ•°
constexpr int OBJECT_LIST_COLS = 12;										// ç‰©å“åˆ—è¡¨åˆ—æ•°

// UI ç›¸å…³è®¾ç½®
constexpr int UI_SCALE = 190.0f;                                            // UIç•Œé¢ç¼©æ”¾
constexpr int FONT_SIZE = 20;                                               // å­—ä½“å¤§å°
constexpr int MAP_LAYER_GRADE = 0;                                          // åœ°å›¾å±‚çº§
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // è§’è‰²å±‚çº§
constexpr int UI_LAYER_GRADE = 2;                                           // UIå±‚çº§
constexpr int OBJECT_LAYER_GRADE = 3;                                       // ç‰©å“å±‚çº§
constexpr float BUTTON_SIZE_RATIO = 2.0f;                                   // æŒ‰é’®å¤§å°å˜åŒ–æ¯”ä¾‹
constexpr float ENLARGEMENT_RATIO = 1.2f;									// æŒ‰é’®åŠ¨ç”»ç¼©æ”¾æ¯”ä¾‹
constexpr float ENLARGEMENT_TIME = 0.15f;									// æŒ‰é’®åŠ¨ç”»ç¼©æ”¾æ—¶é—´
constexpr int CLOSE_OBJECT_LIST_START_X = 729;								// ç‰©å“æ (å…³é—­çŠ¶æ€)èµ·å§‹ä½ç½®çš„Xåæ ‡
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// ç‰©å“æ (å…³é—­çŠ¶æ€)èµ·å§‹ä½ç½®çš„Yåæ ‡
constexpr int OPEN_OBJECT_LIST_START_X = 729;								// ç‰©å“æ (å¼€å¯çŠ¶æ€)èµ·å§‹ä½ç½®çš„Xåæ ‡
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// ç‰©å“æ (å¼€å¯çŠ¶æ€)èµ·å§‹ä½ç½®çš„Yåæ ‡
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// ç‰©å“æ ç‰©å“æ ¼å­æ°´å¹³é—´è·
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// ç‰©å“æ ç‰©å“æ ¼å­åž‚ç›´é—´è·
constexpr float OBJECT_NODE_SCALE = 2.0f;									// ç‰©å“ç¼©æ”¾æ¯”ä¾‹
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// ç‰©å“æ åˆ é™¤æŒ‰é’®å·¦è¾¹ç•Œ
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// ç‰©å“æ åˆ é™¤æŒ‰é’®å³è¾¹ç•Œ
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// ç‰©å“æ åˆ é™¤æŒ‰é’®ä¸Šè¾¹ç•Œ
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// ç‰©å“æ åˆ é™¤æŒ‰é’®ä¸‹è¾¹ç•Œ
>>>>>>> Stashed changes



// UI ½çÃæÉèÖÃ
constexpr int UI_SCALE = 160.0f;                                            // UI???????
constexpr int FONT_SIZE = 24;                                               // ×ÖÌå´óÐ¡
constexpr int MAP_LAYER_GRADE = 0;                                          // µØÍ¼²ã¼¶
constexpr int CHARACTER_LAYER_GRADE = 1;                                    // ½ÇÉ«²ã¼¶
constexpr int UI_LAYER_GRADE = 2;                                           // UI²ã¼¶
constexpr int OBJECT_LAYER_GRADE = 3;                                       // ÎïÆ·²ã¼¶
constexpr float ENLARGEMENT_RATIO = 1.2f;									// °´Å¥¶¯»­Ëõ·Å±ÈÀý
constexpr float ENLARGEMENT_TIME = 0.15f;									// °´Å¥¶¯»­Ëõ·ÅÊ±¼ä
constexpr int CLOSE_OBJECT_LIST_START_X = 729;								// ÎïÆ·À¸(¹Ø±Õ×´Ì¬)ÆðÊ¼Î»ÖÃµÄX×ø±ê
constexpr int CLOSE_OBJECT_LIST_START_Y = 1056;								// ÎïÆ·À¸(¹Ø±Õ×´Ì¬)ÆðÊ¼Î»ÖÃµÄY×ø±ê
constexpr int OPEN_OBJECT_LIST_START_X = 729;								// ÎïÆ·À¸(¿ªÆô×´Ì¬)ÆðÊ¼Î»ÖÃµÄX×ø±ê
constexpr int OPEN_OBJECT_LIST_START_Y = 582;								// ÎïÆ·À¸(¿ªÆô×´Ì¬)ÆðÊ¼Î»ÖÃµÄY×ø±ê
constexpr int OBJECT_LIST_NODE_HORIZONTAL_INTERVAL = 42;					// ÎïÆ·À¸ÎïÆ·¸ñ×ÓË®Æ½¼ä¾à
constexpr int OBJECT_LIST_NODE_VERTICAL_INTERVAL = 42;						// ÎïÆ·À¸ÎïÆ·¸ñ×Ó´¹Ö±¼ä¾à
constexpr float OBJECT_NODE_SCALE = 2.0f;									// ÎïÆ·Ëõ·Å±ÈÀý

constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_LEFT_BOUDARY = 1272;			// ÎïÆ·À¸É¾³ý°´Å¥×ó±ß½ç
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_RIGHT_BOUDARY = 1298;			// ÎïÆ·À¸É¾³ý°´Å¥ÓÒ±ß½ç
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_TOP_BOUDARY = 512;				// ÎïÆ·À¸É¾³ý°´Å¥ÉÏ±ß½ç
constexpr int OPEN_OBJIEC_LIST_DELETE_BUTTON_BOTTOM_BOUDARY = 568;			// ÎïÆ·À¸É¾³ý°´Å¥ÏÂ±ß½ç


constexpr int SECONDS_IN_A_DAY = 86400;                                         // Ò»ÌìµÄÃëÊý
constexpr float TIME_SCALE = 3600.0f;                                           // ÓÎÏ·Ê±¼äËõ·Å±ÈÀý£¬ÏÖÊµ1Ãë=ÓÎÏ·1·ÖÖÓ
constexpr int HOURS_IN_A_DAY = 24;                                              // Ò»Ìì24Ð¡Ê±
constexpr int SECONDS_IN_A_HOUR = 3600;                                         // Ã¿Ð¡Ê±60·ÖÖÓ
constexpr int SEASONS_CHANGE_PERIOD = 30;                                       // Ã¿30ÌìÒ»¸ö¼¾½Ú±ä»¯
constexpr int SECONDS_IN_A_MIN = 60;
#endif // !_CONSTANT_H_