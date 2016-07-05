#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define LFTY 2 // lefty

#define ON_PRESS 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 1: Basic layer */
    [BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,        KC_5,   TO(LFTY, ON_PRESS),
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,        KC_T,   KC_TRNS,
        KC_LCTL,        KC_A,         KC_S,   KC_D,   KC_F,        KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,        KC_B,   KC_JLBR,
        KC_LGUI,        KC_TRNS,      KC_LALT,        KC_LGUI,     KC_LCTRL,
                                                  KC_TRNS,         KC_TRNS,
                                                                   KC_TRNS,
                                               KC_SPC,KC_BSPC,    LALT(KC_SPC),
        // right hand
        KC_6,        KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,          KC_JGRV,
        KC_TRNS,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_JAT,
                     KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,          KC_JCLN,
        KC_JRBR,     KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_F13,
                             KC_LALT,KC_RGUI,KC_TRNS,KC_RCTL,          KC_F18,
        // KC_F13 and KC_F18 are intended to be remapped to KC_JYEN and KC_RO
        // respectively.
        // Since some special keys (KC_F20, 21, ..., KC_INT1, 2, ..., etc.) are
        // not recognized by or have special meaning (KC_F14 = Brightness Down)
        // to Mac with JIS keyboard layout, I deliberately chosen two unused
        // keys.
        KC_HOME,        KC_END,
        KC_PGUP,
        KC_PGDN,KC_BSPC, LT(SYMB, KC_ENT)
    ),
    /* Keymap 1: Symbol Layer */
    [SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /* Keymap 2: Lefty Layer */
    [LFTY] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(BASE, ON_PRESS),
       KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
