#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _FN2 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_FN1 MO(_FN1)
#define KC_FN2 MO(_FN2)
#define KC_SPFN1 LT(_FN1, KC_SPACE)
#define KC_BSFN2 LT(_FN2, KC_BSPC)
#define KC_SRCTL LCTL_T(KC_SPACE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,          KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,             KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_FN2,  KC_LALT, KC_LGUI, KC_FN1,  KC_LCTL,          KC_SPC,                    KC_FN1,  KC_RGUI, KC_RALT, KC_FN2
  ),

  [_FN1] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PLUS, KC_EQL,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,          KC_PLUS,
    _______, _______, _______, _______, KC_LCBR, KC_LBRC, KC_RBRC,          KC_RCBR, _______, KC_COLN, KC_SCLN, _______,
    _______, _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
  ),

  [_FN2] = LAYOUT(
    KC_MPLY, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, RESET,
    KC_VOLU, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,          _______,
    KC_VOLD, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,          _______,                   _______, _______, _______, _______
  )

};
