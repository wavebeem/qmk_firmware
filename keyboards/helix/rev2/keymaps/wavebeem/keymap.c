#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ########## BASE LAYER #######################################################################################################################
[0] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                     KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                     KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                     KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_ENT  ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     MO(3)   , KC_LCTL , KC_LALT , KC_LGUI , MO(2)   , KC_RSFT , KC_SPC  , KC_RSFT , KC_SPC  , MO(1)   , KC_RGUI , KC_RALT , KC_RCTL , TG(3)
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## NUMBERS & SYMBOLS LAYER ##########################################################################################################
[1] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                     KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , XXXXXXX , KC_MUTE , KC_VOLD , KC_VOLU , XXXXXXX ,                     XXXXXXX , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , XXXXXXX , KC_MPRV , KC_MNXT , KC_MPLY , XXXXXXX ,                     XXXXXXX , KC_GRV  , _______ , _______ , _______ , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## ARROWS & MEDIA KEYS LAYER ########################################################################################################
[2] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_HOME , KC_UP   , KC_END  , XXXXXXX ,                     KC_F13  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX ,                     KC_F14  , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_SPC  , KC_PGUP , KC_PGDN , XXXXXXX ,                     KC_F15  , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ , KC_CAPS , RESET   , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## GAMES LAYER ######################################################################################################################
[3] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     XXXXXXX , KC_HOME , KC_UP   , KC_END  , XXXXXXX , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , KC_DEL  , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     XXXXXXX , KC_PGDN , KC_PGUP , KC_ENT  , XXXXXXX , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , KC_SPC  , KC_SPC  , KC_SPC  , _______ , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),
};
