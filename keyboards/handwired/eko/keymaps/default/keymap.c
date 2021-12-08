/* Copyright 2020 GhostSeven <work@ghost7.com>
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
#include "print.h"
#include <stdio.h>

enum encoder_names {
  _ENCODER
};

enum layers {
  _DEFAULT,
  _MENU,
  _PHOTOSHOP,
  _PHOTOSHOP_01,
  _PHOTOSHOP_02,
  _LIGHTROOM,
  _LIGHTROOM_01,
  _BLENDER,
  _ADJUST
};

// Macros declaratiOns
enum custom_keycodes {
    GO_DEFAULT = SAFE_RANGE,
    GO_MENU,
    GO_PHOTOSHOP,
    GO_LIGHTROOM,
    GO_BLENDER
};

int8_t brush_opacity = 100;
int8_t brush_flow = 100;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        |                   |      | Knob 1: Vol Dn/Up  |
        | Hold: Layer 2     | Up   | Press: Mute        |
        | Left              | Down | Right              |
     */
    [_DEFAULT] = LAYOUT(
        KC_MPLY, KC_UP, MO(_MENU),
        KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    /*
        | Held: Layer 2  | Home | RESET      |}}]][[[]]]
        | Media Previous | End  | Media Next |
     */
    [_MENU] = LAYOUT(
        TO(_PHOTOSHOP), TO(_LIGHTROOM), _______,
        TO(_BLENDER), KC_END , RESET
    ),

    [_PHOTOSHOP] = LAYOUT(
        KC_B, KC_V, TG(_PHOTOSHOP),
        KC_SPC, KC_Z , TO(_PHOTOSHOP_01)
    ),

    [_PHOTOSHOP_01] = LAYOUT(
        KC_X, KC_D, TO(_PHOTOSHOP),
        KC_SPC, KC_LSFT , TO(_PHOTOSHOP_02)
    ),

    [_PHOTOSHOP_02] = LAYOUT(
        KC_LCTRL, KC_LALT, TO(_PHOTOSHOP_01),
        KC_SPC, KC_LSFT , TO(_PHOTOSHOP)
    ),

    [_LIGHTROOM] = LAYOUT(
        KC_1, KC_2, TG(_LIGHTROOM),
        KC_3, KC_4 , TO(_LIGHTROOM_01)
    ),

    [_LIGHTROOM_01] = LAYOUT(
        KC_B, KC_V, TO(_LIGHTROOM),
        KC_SPC, KC_Z , TO(_LIGHTROOM)
    ),

    [_BLENDER] = LAYOUT(
        KC_B, KC_V, TG(_BLENDER),
        KC_SPC, KC_Z , TO(_BLENDER)
    ),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    // uprintf("%s\n", buffer);
    if (index == _ENCODER) {
        if(layer_state_is(_PHOTOSHOP)) {
            if (clockwise) {
                tap_code(KC_RBRC);
            } else {
                tap_code(KC_LBRC);
            }
            return true;
        }
        if(layer_state_is(_PHOTOSHOP_01)) {
            if (clockwise) {
                tap_code16(S(KC_RBRC));
            } else {
                tap_code16(S(KC_LBRC));
            }
            return true;
        }
        if(layer_state_is(_PHOTOSHOP_02)) {
            if (clockwise) {
                brush_flow += 5;
                if(brush_flow > 100) brush_flow = 100;
            } else {
                brush_flow-= 5;
                if(brush_flow < 0) brush_flow = 0;
            }
            char buffer[4];
            sprintf(buffer,"%d", brush_flow);
            send_string(buffer);
            return true;
        }
        if(layer_state_is(_LIGHTROOM)) {
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }
            return true;
        }

        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

// Macro
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case GO_DEFAULT:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DEFAULT);
            }
            return false;
        case GO_MENU:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MENU);
            }
            return false;
        case GO_PHOTOSHOP:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_PHOTOSHOP);
            }
            return false;
        case GO_LIGHTROOM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_LIGHTROOM);
            }
            return false;
        case GO_BLENDER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BLENDER);
            }
            return false;
    }
    return true;
};

#ifdef OLED_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _MENU:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _PHOTOSHOP:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
