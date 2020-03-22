/* Copyright 2019 Ryota Goto
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
/*
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
    K300, K301, K302,     K304,       K306,       K308,   K309, K310, K311  \
*/

enum {
  TD_C1 = 0,
  TD_CB = 2 
};
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for layer shift to weather
  [TD_C1] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LCTRL, _1),
  [TD_CB] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LCTRL, _BASE),
// Other declarations would go here, separated by commas, if you have them
};

// tapdance keycodes
enum td_keycodes {
  SHIFT_CAP, //  `LSFT` when tapped or held, `CAPS` when  double tapped. Add additional keycodes for each tapdance.
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// declare your tapdance functions:

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void shiftcap_finished (qk_tap_dance_state_t *state, void *user_data);
void shiftcap_reset (qk_tap_dance_state_t *state, void *user_data);


#define KC_BSM1 LT(1, KC_BSPC)
#define KC_SPM1 LT(1, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all( /* Base */
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, 
    TD(TD_C1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, 
    SHIFT_CAP, KC_SLSH, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, 
    KC_LALT, XXXXXXX, KC_RGUI,          KC_SPM1,          TT(2),            KC_SPM1, KC_RALT, XXXXXXX, KC_RCTL
  ),
  [1] = LAYOUT_all( /* Num and extra Keys */
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, 
    TD(TD_CB), _______, _______, _______, _______, _______,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_QUOT, _______, 
    _______, KC_BSLS, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, 
    _______, XXXXXXX, _______,          KC_BSPC,          _______,          _______, _______, _______, _______
  ),
  [2] = LAYOUT_all( /* FN media */
    KC_GRV,  _______, _______, _______,  _______, _______, _______, _______, _______, KC_MINS, KC_EQL, KC_DEL, 
    _______, KC_VOLU, KC_VOLD, KC_MUTE,  KC_MPLY, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_QUOT, _______, 
    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12
    _______, XXXXXXX,   MO(3),          KC_BSPC,          _______,          _______, _______, XXXXXXX, _______
  ),
  [3] = LAYOUT_all( /* RESET */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______, XXXXXXX, _______,          _______,          _______,          _______, _______, _______, _______
  )
};






// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}

// handle the possible states for each tapdance keycode you define:

void shiftcap_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LSFT);
      break;
    case SINGLE_HOLD:
      register_code16(KC_LSFT); // for a layer-tap key, use `layer_on(_MY_LAYER)` here
      break;
    case DOUBLE_TAP: 
      register_code16(KC_CAPS);
  }
}

void shiftcap_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
   case SINGLE_TAP:
      register_code16(KC_LSFT);
      break;
    case SINGLE_HOLD:
      register_code16(KC_LSFT); // for a layer-tap key, use `layer_on(_MY_LAYER)` here
      break;
    case DOUBLE_TAP: 
      register_code16(KC_CAPS);
  }
}

// define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [SHIFT_CAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftcap_finished, shiftcap_reset)
};
