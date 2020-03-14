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
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// static uint16_t last_anim = 0;
static bool anim = false;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

// Customizations from @wavebeem
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
     MO(4)   , KC_LCTL , KC_LALT , KC_LGUI , MO(2)   , KC_RSFT , KC_SPC  , KC_RSFT , KC_SPC  , MO(1)   , KC_RGUI , KC_RALT , KC_RCTL , TG(3)
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
     _______ , _______ , _______ , _______ , _______ , _______ ,                     XXXXXXX , KC_HOME , KC_UP   , KC_END  , XXXXXXX , _______ ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , KC_DEL  , KC_DEL  ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     _______ , _______ , _______ , _______ , _______ , _______ ,                     XXXXXXX , KC_PGDN , KC_PGUP , KC_ENT  , XXXXXXX , _______ ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     KC_LALT , KC_LGUI , KC_LALT , KC_LCTL , KC_SPC  , KC_SPC  , KC_SPC  , _______ , _______ , _______ , _______ , _______ , _______ , _______
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),

// ########## LED LAYER ########################################################################################################################
[4] = LAYOUT(
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_HUD , RGB_HUI , RGB_TOG , XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_VAD , RGB_VAI , RGB_MOD , XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,                   ,---------,---------,---------,---------,---------,---------,
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                     XXXXXXX , RGB_SAD , RGB_SAI , RGB_RMOD, XXXXXXX , XXXXXXX ,
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
     XXXXXXX , KC_LSFT , RGBRST  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
// ,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,---------,
),
};

#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  anim = !anim;
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
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
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        // iota_gfx_init(!has_usb());   // turns on the display
        // iota_gfx_init(true);   // turns on the display
        iota_gfx_init(false);   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {
  static const char *logo =
    "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\n"
    "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\n"
    "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\n"
    "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef";
//   static char logo[] = {
//     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,'\n',
//     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,'\n',
//     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,'\n',
//     0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,'\0',
//   };
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_logo2(struct CharacterMatrix *matrix) {
  static char logo[] = {
    0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,'\n',
    0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,'\n',
    0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,'\n',
    0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,'\0'
  };
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

void render_sprite(struct CharacterMatrix *matrix, uint8_t sprite_index) {
  matrix->dirty = true;
//   uint8_t sprite_width = 4;
//   uint8_t sprite_height = 16;
//   uint8_t char_offset = 16;
//   uint8_t i = char_offset + sprite_index * sprite_width * sprite_height;
  uint8_t i = 0x10;
  for (int col = 0; col < MatrixCols; col++) {
    for (int row = 0; row < MatrixRows; row++) {
    //   matrix->display[row][col] = col % 2 == 0 || row % 2 == 0 ? 0x10 : 0x11;
      matrix->display[row][col] = i++;
    }
  }
}

// static uint8_t sprite_index = 0;

// void render_status(struct CharacterMatrix *matrix) {
//     if (anim) {
//         matrix_write_P(matrix, PSTR("+++"));
//     } else {
//         matrix_write_P(matrix, PSTR("---"));
//     }
// }

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

//   if (timer_elapsed(last_anim) > 300) {
//       last_anim = timer_read();
//       anim = !anim;
//   }
  matrix_clear(&matrix);
//   if(is_master){
  if(anim){
    // render_status(&matrix);
    render_logo2(&matrix);
    // render_logo(&matrix);
    // sprite_index++;
    // sprite_index %= 2;
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
