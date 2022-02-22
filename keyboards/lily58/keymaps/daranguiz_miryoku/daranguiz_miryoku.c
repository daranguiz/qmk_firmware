// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku
// generated -*- buffer-read-only: t -*-

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "daranguiz_miryoku.h"
#include "config.h"
#include <stdio.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_miryoku_with_grv(
#if defined DARIO_THUMB_SHIFT
    KC_Q,              KC_W,              KC_F,              KC_P,              KC_G,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT, TG(GAME),
    LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_D,              KC_H,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
    LT(BUTTON, KC_Z),  LT(FUN, KC_X),     KC_C,              KC_V,              KC_B,              KC_K,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(BUTTON, KC_SLSH),
    U_NP,              U_NP,              LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LSFT_T(KC_ENT),    LT(NUM, KC_BSPC),  LT(SYM, KC_DEL),   U_NP,              U_NP
#else /* default */
    KC_Q,              KC_W,              KC_F,              KC_P,              KC_G,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT, TG(GAME),
    LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_D,              KC_H,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),
    LT(BUTTON, KC_Z),  ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_K,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(BUTTON, KC_SLSH),
    U_NP,              U_NP,              LT(MEDIA, KC_ESC), LT(NAV, KC_SPC),   LT(MOUSE, KC_TAB), LT(SYM, KC_ENT),   LT(NUM, KC_BSPC),  LT(FUN, KC_DEL),   U_NP,              U_NP
#endif
  ),
  [NAV] = LAYOUT_miryoku(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    U_NP,    U_NP,    U_NA,    U_NA,    U_NA,    KC_ENT,  KC_BSPC, KC_DEL,  U_NP,    U_NP
  ),
  [MOUSE] = LAYOUT_miryoku(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    U_NU,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
    U_NP,    U_NP,    U_NA,    U_NA,    U_NA,    KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP
  ),
  [MEDIA] = LAYOUT_miryoku(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    U_NU,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
    U_NP,    U_NP,    U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE, U_NP,    U_NP
  ),
  [NUM] = LAYOUT_miryoku(
    KC_LBRC, KC_4,    KC_5,    KC_6,    KC_RBRC, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_SCLN, KC_1,    KC_2,    KC_3,    KC_EQL,  U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_GRV,  KC_7,    KC_8,    KC_9,    KC_BSLS, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    U_NP,    U_NP,    KC_DOT,  KC_0,    KC_MINS, U_NA,    U_NA,    U_NA,    U_NP,    U_NP
  ),
  [SYM] = LAYOUT_miryoku(
    KC_LCBR, KC_DLR,  KC_PERC, KC_CIRC, KC_RCBR, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_COLN, KC_EXLM, KC_AT,   KC_HASH, KC_PLUS, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, KC_PIPE, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    U_NP,    U_NP,    KC_LPRN, KC_RPRN, KC_UNDS, U_NA,    U_NA,    U_NA,    U_NP,    U_NP
  ),
  [FUN] = LAYOUT_miryoku(
    KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
    U_NP,    U_NP,    KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA,    U_NP,    U_NP
  ),
  [BUTTON] = LAYOUT_miryoku(
    U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    U_NP,    U_NP,    KC_BTN2, KC_BTN3, KC_BTN1, KC_BTN1, KC_BTN3, KC_BTN2, U_NP,    U_NP
  ),
  [GAME] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG(GAME),
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                               KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_ENT, U_NP, KC_BSPC, KC_RGUI
  )
};

/*
 * Per key tapping term settings
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_R:
        case HOME_I:
        case HOME_A:
        case HOME_O:
        case HOME_S:
        case HOME_E:
        case HOME_T:
        case HOME_N:
            // Leaving this split out separately. With permissive hold on, this is generally not needed.
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}

// Quick-tap for layers, to register keys on the tapping downstroke
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#if defined DARIO_THUMB_SHIFT
        // Specifically for shift rolling
        case LSFT_T(KC_ENT):
            return true;
#endif
        // Everything else has permissive hold off by default.
        default:
            return false;
    }
}

// Quick-tap for modifier keys, to register keys on the tapping upstroke
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Shift mods, always permissive hold!
        case HOME_T:
        case HOME_N:
#if defined DARIO_THUMB_SHIFT
                return true;
#else
                return true;
#endif

        // Other modifiers, no bueno. 
        // L hand
        case HOME_A:
        case HOME_R:
        case HOME_S:
        // R hand
        case HOME_E:
        case HOME_I:
        case HOME_O:
            return false;

        // This would be nice to put on GET_HOLD_ON_OTHER_KEY_PRESS,
        // but space is rolled too often for that. Put it on a standard
        // permissive hold instead.
        case LT(NAV, KC_SPC):
            return true;

        // I think these are sometimes rolled too.
        case LT(NUM, KC_BSPC):
#if defined DARIO_THUMB_SHIFT
        case LT(SYM, KC_DEL): // for thumb shift layout
#else
        case LT(SYM, KC_ENT): // for standard layout
#endif        
            return true;

        default:
            return false;
    }
}

// Runs whenever there is a layer state change.
// In the gaming layer, I want auto-shift disabled.
layer_state_t layer_state_set_user(layer_state_t  state) {
    enum layers cur_layer = get_highest_layer(state);

    switch (cur_layer)
    {
    case GAME:
        autoshift_disable();
        break;

    default:
        autoshift_enable();
        break;
    }

    // Don't delete! This is what updates layers!
    return state;
}
