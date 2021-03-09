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

enum custom_keycodes {
    RGB_RST = SAFE_RANGE,
    OLED_TG
};

enum Layers {
    LAYER_BASE = 0,
    LAYER_NUM,
    LAYER_NAV,
    LAYER_GAMES,
    LAYER_MEDIA
};

#define L_NUM MO(LAYER_NUM)
#define L_NAV MO(LAYER_NAV)
#define L_GAMES TG(LAYER_GAMES)
#define L_MEDIA MO(LAYER_MEDIA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ########## BASE LAYER #######################################################################################################################
[LAYER_BASE] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                     KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                     KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                     KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_ENT  ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     L_MEDIA , KC_LCTL , KC_LALT , KC_LGUI , L_NAV   , KC_RSFT , KC_SPC  , KC_F12  , KC_SPC  , L_NUM   , KC_RGUI , KC_RALT , KC_RCTL , KC_F10
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## NUMBERS & SYMBOLS LAYER ##########################################################################################################
[LAYER_NUM] = LAYOUT(
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
[LAYER_NAV] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_TAB  , KC_HOME , KC_UP   , KC_END  , KC_LSFT ,                     KC_F13  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_LEFT , KC_DOWN , KC_RGHT , KC_ENT  ,                     KC_F14  , KC_F5   , KC_F6   , KC_F7   , KC_F8  , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , KC_LSFT , KC_SPC  , KC_PGUP , KC_PGDN , KC_ENT  ,                     KC_F15  , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## GAMES LAYER ######################################################################################################################
[LAYER_GAMES] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     KC_F13  , KC_HOME , KC_UP   , KC_END  , KC_F16  , KC_BSPC ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     KC_F14  , KC_LEFT , KC_DOWN , KC_RGHT , KC_F17  , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     KC_F15  , KC_PGDN , KC_PGUP , KC_ENT  , KC_F18  , KC_ENT ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     _______ , KC_LGUI , KC_LALT , KC_LCTL , KC_SPC  , KC_SPC  , KC_SPC  , _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## LED & MEDIA KEYS LAYER ###########################################################################################################
[LAYER_MEDIA] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_HUD , RGB_HUI , RGB_TOG , XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_MUTE , KC_VOLD , KC_VOLU , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_VAD , RGB_VAI , RGB_MOD , XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_MPRV , KC_MNXT , KC_MPLY , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_SAD , RGB_SAI , RGB_RMOD, XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_LSFT , RGB_RST , OLED_TG , XXXXXXX , XXXXXXX , RESET   , L_GAMES , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_CAPS
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_RST:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                }
            #endif
            break;
        case OLED_TG:
            // TODO: Actually disable animation so the OLED doesn't turn on
            #ifdef OLED_DRIVER_ENABLE
                if (record->event.pressed) {
                    if (is_oled_on()) {
                        oled_off();
                    } else {
                        oled_on();
                    }
                }
            #endif
            break;
    }
    return true;
}

void matrix_init_user(void) {
    #ifdef OLED_DRIVER_ENABLE
        oled_clear();
    #endif
}

#ifdef OLED_DRIVER_ENABLE

// https://javl.github.io/image2cpp/
// Vertical - 1 bit per pixel
static const char PROGMEM screen_texture[] = {
// 'helix-screen', 128x32px
0xff, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0xff, 
0xff, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0xff, 
0xff, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0xff, 
0xff, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 
0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 
0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 
0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 
0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 
0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 
0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 
0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 
0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xff, 
0xff, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xff, 
0xff, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xff, 
0xff, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xff
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

void oled_task_user(void) {
    #if DEBUG_TO_SCREEN
        if (debug_enable) {
            return;
        }
    #endif
    oled_write_raw_P(screen_texture, sizeof screen_texture);
    oled_scroll_left();
}

// TODO: Only the primary MCU seems to be aware of this function: the secondary
// MCU continues animating throughout USB suspend. Maybe there's a way to sync
// state from the primary MCU to the secondary MCU, to work around this
// limitation.
void suspend_power_down_user(void) {
    oled_off();
}

void suspend_wakeup_init_user(void) {
    oled_on();
}

#endif
