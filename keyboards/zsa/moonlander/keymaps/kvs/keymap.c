/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"

enum layers {
    BASE,
    LEFT,
    RIGHT,
};

enum custom_keycodes {
    VRSN = SAFE_RANGE, // writes 'zsa/moonlander/kvs @ a8e4b7-dirty'
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
		KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   KC_F14,
		KC_DEL,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     _______,  _______, KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
		KC_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_HYPR,  KC_MEH,   KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
		KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,                         KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
		KC_GRV,   _______,  _______,  _______,  _______,                      _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,
                                                          LT(LEFT, KC_TAB), SFT_T(KC_SPACE),  KC_LGUI,           KC_ENT, CTL_T(KC_BACKSPACE), LT(RIGHT, KC_ESC)
    ),

    [LEFT] = LAYOUT(
		_______,            _______,         _______,         _______,         _______,         _______,         _______,       _______,       _______,         _______,         _______,         _______,         _______,        _______,
		KC_GRV,       KC_EXLM,       KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,       _______,       _______,       KC_PERC,       KC_AMPR,       KC_ASTR,       KC_LPRN,       KC_RPRN,       KC_F12,
		_______,       KC_GRAVE,      KC_DLR,        KC_LCBR,       KC_RCBR,       KC_GRV,        _______,       _______,       KC_DOWN,       KC_4,          KC_5,          KC_6,          KC_PLUS,       _______,
		_______,       KC_PERC,       KC_CIRC,       KC_LBRC,       KC_RBRC,                                     KC_TILD,       KC_AMPR,       KC_1,          KC_2,          KC_3,          KC_BSLS,       _______,
		EE_CLR,        _______,       _______,       _______,       _______,                                     RM_VALU,       RM_TOGG,       _______,       KC_DOT,        KC_0,          KC_EQL,        _______,
                                            RM_HUED, RM_VALD, RM_HUEU, TOGGLE_LAYER_COLOR,_______, _______
    ),

    [RIGHT] = LAYOUT(
		LED_LEVEL, _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   QK_BOOT,
		_______,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      _______,   _______,   KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      _______,
		_______,   _______,   KC_MS_L,   KC_MS_D,   KC_MS_R,   _______,   _______,   _______,   _______,   KC_MINUS,  KC_EQUAL,  _______,   _______,   KC_MPLY,
		_______,   _______,   _______,   _______,   _______,                         _______,   _______,   _______,   KC_MPRV,   KC_MNXT,   _______,   _______,
		_______,   _______,   _______,   KC_BTN1,   KC_BTN2,                         _______,   _______,   KC_VOLU,   KC_VOLD,   KC_MUTE,   _______,   _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}
