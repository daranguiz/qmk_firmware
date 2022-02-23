// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku
// generated -*- buffer-read-only: t -*-

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "keymap_config.h"
#include "config.h"
#include "oled.h"
#include "features/caps_word.h"
#include <stdio.h>

// Our combo
const uint16_t PROGMEM caps_combo[] = { HOME_T, HOME_N, COMBO_END };

// Boilerplate, required for QMK
uint16_t COMBO_LEN = COMBO_LENGTH;
combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO_ACTION(caps_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CAPS_COMBO:
            if (pressed) {
                caps_word_set(true);
            }
            break;
        default:
            break;
    }
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // in oled.c, for luna
    process_record_user_oled(keycode, record);

    // in features/caps_word.c
    if (!process_caps_word(keycode, record)) {
        return false;
    }

    // AKA, continue processing the key (it wasn't absorbed).
    return true;
}
