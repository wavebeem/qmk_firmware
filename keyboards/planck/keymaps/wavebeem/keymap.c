#include "planck.h"

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_planck_grid(
    KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R   , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P     , KC_BSPC ,
    KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F   , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN  , KC_QUOT ,
    KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V   , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH  , KC_ENT  ,
    MO(4)   , KC_LCTL , KC_LALT , KC_LGUI , MO(1)  , KC_SPC  , KC_SPC  , MO(2)   , MO(3)   , KC_RGUI , KC_RALT  , KC_RCTL
  ),

  [1] = LAYOUT_planck_grid(
    _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ ,
    _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_UNDS , KC_PLUS , KC_LCBR , KC_RCBR , KC_PIPE ,
    _______ , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_TILD , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [2] = LAYOUT_planck_grid(
    _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
    _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS ,
    _______ , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_GRV  , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [3] = LAYOUT_planck_grid(
    _______ , KC_7    , KC_8    , KC_9    , KC_0    , _______ , _______ , _______ , KC_HOME , KC_UP   , KC_END  , KC_BSPC ,
    _______ , KC_4    , KC_5    , KC_6    , KC_0    , _______ , _______ , KC_TAB  , KC_LEFT , KC_DOWN , KC_RGHT , KC_DEL  ,
    _______ , KC_1    , KC_2    , KC_3    , KC_0    , _______ , _______ , _______ , KC_PGDN , KC_PGUP , KC_TAB  , KC_ENT  ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [4] = LAYOUT_planck_grid(
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_SLSH , KC_7    , KC_8    , KC_9    , KC_ASTR ,
    _______ , KC_MUTE , KC_VOLD , KC_VOLU , _______ , _______ , _______ , KC_MINS , KC_4    , KC_5    , KC_6    , KC_PLUS ,
    KC_CAPS , KC_MPLY , KC_MPRV , KC_MNXT , _______ , _______ , _______ , KC_TAB  , KC_1    , KC_2    , KC_3    , KC_ENT  ,
    _______ , _______ , _______ , _______ , _______ , RESET   , RESET   , _______ , KC_COMM , KC_0    , KC_DOT  , KC_BSPC
  )

};
