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
  TD_CB 
};
#define KC_BSM1 LT(1, KC_BSPC)
#define KC_SPM1 LT(1, KC_SPC)
#define SH_CAP MT(MOD_LSFT, KC_CAPS)

//------------------------------------------------------------------------------------------
/* BASE
,_______ ______ ______ ______ ______ ______ ______ ______ ______ ______ _______ _________
| TAB   | Q    | W    | E    |  R   | T    | Y    | U    | I    | O    | P     | BCKSPC  |
|       |      |      |      |      |      |      |      |      |      |       |         |
|_______|______|______|______|______|______|______|______|______|______|_______|_________|
| CTRL    | A    | S    | D    | F    | G    | H    | J    | K    | L    | :    | ENTER  |
| TD>L1   |      |      |      |      |      |      |      |      |      | ;    |        |
|_________|______|______|______|______|______|______|______|______|______|______|________|
| SHFT | ?    | Z    | X    | C    | V    | B    | N    | M    | <    | >    | SHIFT     |
| CAPS | /    |      |      |      |      |      |      |      | ,    | .    |           |
|______|______|______|______|______|______|______|______|______|______|______|___________|
|      |      |       | SPACE       | FN   | SPACE              | ALT   |       | CTRL   |
| ALT  |      | GUI   | LT1         | TT2  |                    |       |       |        |
|______|      |_______|_____________|______|____________________|_______|       |________|
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all( /* Base */
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, 
    TD(TD_C1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, 
    SH_CAP,    KC_SLSH, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT, 
    KC_LALT,   XXXXXXX, KC_RGUI,          KC_SPM1,          TT(2),            KC_SPM1, KC_RALT, XXXXXXX, KC_RCTL
  ),

//------------------------------------------------------------------------------------------
/* 1
,_______ ______ ______ ______ ______ ______ ______ ______ ______ ______ _______ _________
| GRV   | 1    | 2    | 3    |  4   | 5    | 6    | 7    | 8    | 9    | 0     | DEL     |
|       |      |      |      |      |      |      |      |      |      |       |         |
|_______|______|______|______|______|______|______|______|______|______|_______|_________|
| CTRL    |      |      |      |      |      | LEFT | DOWN | UP   | RIGHT| "    | |      |
| TD>L0   |      |      |      |      |      |      |      |      |      | '    | \      |
|_________|______|______|______|______|______|______|______|______|______|______|________|
| SHFT | |    |      |      |      |      |      |      |      | {    | }    |           |
| CAPS | \    |      |      |      |      |      |      |      | [    | ]    |           |
|______|______|______|______|______|______|______|______|______|______|______|___________|
|      |      |        |             |      |                   |       |       |        |
|      |      |        |             |      |                   |       |       |        |
|______|      |________|_____________|______|___________________|_______|       |________|
*/

  [1] = LAYOUT_all( /* Num and extra Keys */
    KC_GESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, 
    TD(TD_CB), _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, KC_BSLS, 
    SH_CAP,    KC_BSLS, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, 
    _______,   XXXXXXX, _______,          _______,          _______,          _______, _______, _______, _______
  ),

//------------------------------------------------------------------------------------------
/* 2
,_______ ______ ______ ______ ______ ______ ______ ______ ______ ______ _______ _________
| PSCRN |      |      |      |      |      |      |      |      | _    | +     | DEL     |
|       |      |      |      |      |      |      |      |      | -    | =     |         |
|_______|______|______|______|______|______|______|______|______|______|_______|_________|
| CTRL    | VolU | VolD | Mute | Play/|      | Home | PgDN | PgUP | End  | "    | |      |
| TD>L0   |      |      |      | Pause|      |      |      |      |      | '    | \      |
|_________|______|______|______|______|______|______|______|______|______|______|________|
| F1   | F2   | F3   | F4   | F5   | F6   | F7   | F8   | F9   | F10  | F11  | F12       |
|      |      |      |      |      |      |      |      |      |      |      |           |
|______|______|______|______|______|______|______|______|______|______|______|___________|
|      |      | MO3    |  BCKSPC     |      |                   |       |       |        |
|      |      |        |             |      |                   |       |       |        |
|______|      |________|_____________|______|___________________|_______|       |________|
*/

  [2] = LAYOUT_all( /* FN media */
    KC_PSCR,   _______, _______, _______,  _______, _______, _______, _______, _______, KC_MINS, KC_EQL, KC_DEL, 
    TD(TD_CB), KC_VOLU, KC_VOLD, KC_MUTE,  KC_MPLY, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_QUOT, KC_BSLS, 
    KC_F1,     KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,
    _______,   XXXXXXX, MO(3),             KC_BSPC,          _______,          _______, _______, XXXXXXX, _______
  ), 

//------------------------------------------------------------------------------------------
/* 3
,_______ ______ ______ ______ ______ ______ ______ ______ ______ ______ _______ _________
|       |      |      |      |      |      |      |      |      |      |       | RESET   |
|       |      |      |      |      |      |      |      |      |      |       | RESET   |
|_______|______|______|______|______|______|______|______|______|______|_______|_________|
|  CTRL   |      |      |      |      |      |      |      |      |      |      |        |
|  TD>L0  |      |      |      |      |      |      |      |      |      |      |        |
|_________|______|______|______|______|______|______|______|______|______|______|________|
|      |      |      |      |      |      |      |      |      |      |      |           |
|      |      |      |      |      |      |      |      |      |      |      |           |
|______|______|______|______|______|______|______|______|______|______|______|___________|
|      |      |        |             |      |                   |       |       |        |
|      |      |        |             |      |                   |       |       |        |
|______|      |________|_____________|______|___________________|_______|       |________|
*/

  [3] = LAYOUT_all( /* RESET */
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET, 
    TD(TD_CB), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______,   XXXXXXX, _______,          _______,          _______,          _______, _______, _______, _______
  )
};

 qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_C1] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LCTRL, 1),
  [TD_CB] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LCTRL, 0),
}; 

