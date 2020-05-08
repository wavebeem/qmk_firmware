#include QMK_KEYBOARD_H
#include "bootloader.h"

#ifdef PROTOCOL_LUFA
    #include "lufa.h"
    #include "split_util.h"
#endif

#ifdef AUDIO_ENABLE
    #include "audio.h"
#endif

#ifdef OLED_DRIVER_ENABLE
    #include "oled_driver.h"
#endif

#ifdef RGBLIGHT_ENABLE
    extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

static uint16_t frame_time = 300;
static uint16_t typing_timeout = 300 * 4;
static uint16_t oled_timeout = 300 * 16;
static uint16_t last_keypress = 0;
static uint16_t last_image_swap = 0;
static bool is_typing = false;
static bool image_swap = false;

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};

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
     MO(4)   , KC_LCTL , KC_LALT , KC_LGUI , MO(2)   , KC_RSFT , KC_SPC  , TG(3)   , KC_SPC  , MO(1)   , KC_RGUI , KC_RALT , KC_RCTL , KC_RSFT
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## NUMBERS & SYMBOLS LAYER ##########################################################################################################
[1] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                     KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     _______ , KC_GRV  , _______ , _______ , _______ , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## ARROWS & F1-F12 LAYER ############################################################################################################
[2] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_TAB  , KC_HOME , KC_UP   , KC_END  , KC_ENT  ,                     KC_F13  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_LEFT , KC_DOWN , KC_RGHT , KC_ENT  ,                     KC_F14  , KC_F5   , KC_F6   , KC_F7   , KC_F8  , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_SPC  , KC_PGUP , KC_PGDN , KC_ENT  ,                     KC_F15  , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ , KC_CAPS , RESET   , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## GAMES LAYER ######################################################################################################################
[3] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     KC_F1   , KC_HOME , KC_UP   , KC_END  , KC_F4   , KC_BSPC ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     KC_F2   , KC_LEFT , KC_DOWN , KC_RGHT , KC_F5   , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     KC_F3   , KC_PGDN , KC_PGUP , KC_ENT  , KC_F6   , KC_ENT ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     KC_LALT , KC_LGUI , KC_LALT , KC_LCTL , KC_SPC  , KC_SPC  , KC_SPC  , _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## LED & MEDIA KEYS LAYER ###########################################################################################################
[4] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_HUD , RGB_HUI , RGB_TOG , XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_MUTE , KC_VOLD , KC_VOLU , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_VAD , RGB_VAI , RGB_MOD , XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_MPRV , KC_MNXT , KC_MPLY , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_SAD , RGB_SAI , RGB_RMOD, XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_LSFT , RGBRST  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_on();
        last_keypress = timer_read();
        is_typing = true;
    }
    switch (keycode) {
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                    RGB_current_mode = rgblight_config.mode;
                }
            #endif
            break;
    }
    return true;
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

// https://javl.github.io/image2cpp/
const char PROGMEM logo1[] = {
// const char logo1[] = {
// 'helix-screen1', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x30, 0x30,
0x0c, 0x0c, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x0c, 0x0c, 0xf0, 0xf0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x30, 0x30, 0x30, 0x30, 0x0c, 0x0c, 0x03, 0x03, 0x00, 0x00,
0x0c, 0x0c, 0x33, 0x33, 0x0c, 0x0c, 0x00, 0x00, 0x03, 0x03, 0xfc, 0xfc, 0x00, 0x00, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x0c, 0x0c, 0xf0, 0xf0, 0x00, 0x00,
0x0c, 0x0c, 0x33, 0x33, 0x0c, 0x0c, 0x00, 0x00, 0x30, 0x30, 0x0f, 0x0f, 0xc0, 0xc0, 0x3f, 0x3f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,
0x0c, 0x0c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0c, 0x0c, 0x03, 0x03, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char PROGMEM logo2[] = {
// const char logo2[] = {
// 'helix-screen2', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x30, 0x30, 0x0c, 0x0c,
0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x30, 0x30, 0xc0, 0xc0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xc0, 0xc0, 0x30, 0x30, 0x30, 0x30, 0x0c, 0x0c, 0x03, 0x03, 0x00, 0x00, 0x0c, 0x0c,
0x33, 0x33, 0x0c, 0x0c, 0x00, 0x00, 0x03, 0x03, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x0c, 0x0c, 0xf0, 0xf0, 0x00, 0x00, 0x0c, 0x0c,
0x33, 0x33, 0x0c, 0x0c, 0x00, 0x00, 0x30, 0x30, 0x0f, 0x0f, 0x00, 0x00, 0xc0, 0xc0, 0x3f, 0x3f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x0c, 0x0c,
0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char PROGMEM name[] = {
// 'screen-b', 128x32px
0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff,
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff
};

static void render_logo1(void) {
    oled_write_raw_P(logo1, sizeof logo1);
}

static void render_logo2(void) {
    oled_write_raw_P(logo2, sizeof logo2);
}

static void render_logo(void) {
    if (!image_swap) {
        render_logo1();
    } else {
        render_logo2();
    }
}

static void render_status(void) {
    oled_write_raw_P(name, sizeof name);
}


void oled_task_user(void) {
    #if DEBUG_TO_SCREEN
        if (debug_enable) {
            return;
        }
    #endif
    if (timer_elapsed(last_keypress) > typing_timeout) {
        is_typing = false;
    }
    if (timer_elapsed(last_keypress) > oled_timeout) {
        oled_off();
    }
    if (
        (is_typing || image_swap) &&
        timer_elapsed(last_image_swap) > frame_time
    ) {
        last_image_swap = timer_read();
        image_swap = !image_swap;
    }
    if (!is_master) {
        render_logo();
    } else {
        render_status();
    }
}

#endif
