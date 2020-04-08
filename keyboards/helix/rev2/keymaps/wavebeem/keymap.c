#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

static uint16_t typing_timeout = 1200;
static uint16_t frame_time = 300;
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
    #ifdef SSD1306OLED
        iota_gfx_init(true);
    #endif
}


#ifdef SSD1306OLED

void matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_update(
    struct CharacterMatrix *dest,
    const struct CharacterMatrix *source
) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

static void render_logo(struct CharacterMatrix *matrix) {
    matrix_write_P(matrix, PSTR(
        "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\n"
        "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\n"
        "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\n"
        "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef"
    ));
}

static void render_logo2(struct CharacterMatrix *matrix) {
    matrix_write_P(matrix, PSTR(
        "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\n"
        "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\n"
        "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\n"
        "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff"
    ));
}

static void render_status(struct CharacterMatrix *matrix) {
    matrix_write_P(matrix, PSTR(
        "\x1a QMK Helix\n"
        "\x1a @wavebeem\n"
        "\x1a pdxkbc.com\n"
        "\x1a mockbrian.com"
    ));
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    #if DEBUG_TO_SCREEN
        if (debug_enable) {
            return;
        }
    #endif
    if (timer_elapsed(last_keypress) > typing_timeout) {
        last_keypress = timer_read();
        is_typing = false;
    }
    if (
        (is_typing || image_swap) &&
        timer_elapsed(last_image_swap) > frame_time
    ) {
        last_image_swap = timer_read();
        image_swap = !image_swap;
    }
    matrix_clear(&matrix);
    if (is_master && !image_swap) {
        render_logo(&matrix);
    } else if (is_master) {
        render_logo2(&matrix);
    } else {
        render_status(&matrix);
    }
    matrix_update(&display, &matrix);
}

#endif
