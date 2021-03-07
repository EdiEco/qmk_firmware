/* Copyright 2020 tominabox1
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
#include "color.h"
#include "rgb_matrix.h"
#include "keyboard.h"
#include "personal.h"
#include "ed_tap_dance.h"
#include "ed_kript.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record);

enum layers {
  _QWEED1,
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _NAV,          // Navegation layer
  _LOWER,
  _RAISE,
  _ENG,          // Engineering layer
  _ADJUST
};

// Macros declaratiOns
enum custom_keycodes {
    GO_QWERTY = SAFE_RANGE,
    GO_COLEMAK,
    GO_DVORAK,
    GO_QWEED1,
    CPP_PNT,
    KRIPT
};


// Tap Dance
#define ESC_PRI TD(TD_ESC_PNT)
#define SFT_CAP TD(TD_SFT_CAP)
#define LCTL_ENT_EX TD(TD_LCTL_ENT_EXTRA)
#define RCTL_ENT_EX TD(TD_RCTL_ENT_EXTRA)
#define LSFT_EXTRA TD(TD_LSFT_EXTRA)
#define RSFT_EXTRA TD(TD_RSFT_EXTRA)
#define LFT_EXTRA TD(TD_DWN_EXTRA)
#define CIRC_EXTRA TD(TD_CIRC_EXTRA)
#define TILD_EXTRA TD(TD_TILD_EXTRA)

// Mod-Tap
#define CTL_ENT MT(MOD_LCTL,KC_ENT)
#define ALT_BSP MT(MOD_LALT, KC_BSPC)
#define SFT_ENT MT(MOD_RSFT,KC_ENT)
#define CTL_F16 MT(MOD_RCTL,KC_F16)
#define ALT_DWN MT(MOD_LALT, KC_DOWN)
#define GUI_BSP MT(MOD_LGUI, KC_BSPC)

// Layer
#define LOW_BSP LT(_LOWER, KC_BSPC)
#define LOW_DWN LT(_LOWER, KC_DOWN)
#define RAI_UP LT(_RAISE, KC_UP)
#define NAV_SPC LT(_NAV, KC_SPC)
#define NAV_RGH  LT(_NAV, KC_RGHT)
#define ENG_DOW LT(_ENG, KC_DOWN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_mit(
    KC_ESC,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_BSPC,
    KC_TAB,      KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,
    KC_LSFT,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,     KC_ENT ,
    KC_LCTL,     RGB_TOG,     KC_LALT,     KC_LGUI,     MO(_LOWER),  KC_SPC,                   MO(_RAISE),  KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT
),

[_QWEED1] = LAYOUT_planck_mit(
    ESC_PRI,     KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_BSPC,
    KC_TAB,      KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,
    LSFT_EXTRA,  KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,     RSFT_EXTRA,
    LCTL_ENT_EX, GUI_BSP,     ALT_BSP,     LFT_EXTRA,   LOW_DWN,     KC_SPC,                   RAI_UP,      NAV_RGH,     _______,     KC_LEAD,     RCTL_ENT_EX
),

[_COLEMAK] = LAYOUT_planck_mit(
    ESC_PRI,     KC_Q,        KC_W,        KC_F,        KC_P,        KC_G,       KC_J,         KC_L,        KC_U,        KC_Y,        KC_SCLN,     KC_BSPC,
    KC_TAB,      KC_A,        KC_R,        KC_S,        KC_T,        KC_D,       KC_H,         KC_N,        KC_E,        KC_I,        KC_O,        KC_QUOT,
    SFT_CAP,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,       KC_K,         KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,     KC_ENT ,
    LCTL_ENT_EX, KC_LEAD,     ALT_DWN,     TT(_ENG),    LOW_BSP,     KC_SPC,                   MO(_RAISE),  KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT
),

[_DVORAK] = LAYOUT_planck_mit(
    ESC_PRI,     KC_QUOT,     KC_COMM,     KC_DOT,      KC_P,        KC_Y,       KC_F,         KC_G,        KC_C,        KC_R,        KC_L,        KC_BSPC,
    KC_TAB,      KC_A,        KC_O,        KC_E,        KC_U,        KC_I,       KC_D,         KC_H,        KC_T,        KC_N,        KC_S,        KC_SLSH,
    SFT_CAP,     KC_SCLN,     KC_Q,        KC_J,        KC_K,        KC_X,       KC_B,         KC_M,        KC_W,        KC_V,        KC_Z,        KC_ENT ,
    LCTL_ENT_EX, KC_LEAD,     ALT_DWN,     TT(_ENG),    LOW_BSP,     KC_SPC,                   MO(_RAISE),  KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT
),

[_LOWER] = LAYOUT_planck_mit(
    KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_BSPC,
    KC_DEL,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_MINS,     KC_EQL,      KC_LBRC,     KC_RBRC,     KC_BSLS,
    _______,     KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_INS,      _______,     _______,     _______,     _______,
    _______,     _______,     _______,     _______,     _______,     _______,                  _______,     KC_HOME,     KC_PGDN,     KC_PGUP,     KC_END
),

[_RAISE] = LAYOUT_planck_mit(
    TILD_EXTRA,  KC_EXLM,     KC_AT,       KC_HASH,     KC_DLR,      KC_PERC,     CIRC_EXTRA,  KC_AMPR,     KC_ASTR,     KC_LPRN,     KC_RPRN,     KC_BSPC,
    KC_DEL,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_UNDS,     KC_PLUS,     KC_LBRC,     KC_RBRC,     KC_BSLS,
    _______,     KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      CPP_PNT,     _______,     _______,     _______,     _______,
    _______,     _______,     _______,     _______,     _______,     _______,                  _______,     KC_F13,      KC_F14,      KC_F15,      CTL_F16
),

[_ENG] = LAYOUT_planck_mit(
    _______,     KC_WH_U,     KC_BTN1,     KC_MS_U,     KC_BTN2,     KC_HOME,     KC_END,      KC_BSPC,     KC_P7,       KC_P8,       KC_P9,       KC_PPLS,
    KC_VOLU,     KC_WH_D,     KC_MS_L,     KC_MS_D,     KC_MS_R,     KC_BTN3,     KC_PGUP,     KC_TAB,      KC_P4,       KC_P5,       KC_P6,       KC_PMNS,
    KC_VOLD,     KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT,     _______,     KC_PGDN,     KC_NLCK,     KC_P1,       KC_P2,       KC_P3,       KC_PENT,
    _______,     _______,     _______,     _______,     _______,     _______,                  _______,     KC_P0,       KC_PDOT,     KC_PAST,     KC_PSLS
),

[_NAV] = LAYOUT_planck_mit(
    _______,     KC_MS_L,     KC_MS_D,     KC_MS_U,     KC_MS_R,     KC_BTN1,     KC_WH_U,     KC_MS_L,     KC_MS_D,     KC_MS_U,     KC_MS_R,     _______,
    _______,     KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT,     KC_BTN2,     KC_WH_D,     KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT,     _______,
    _______,     KC_HOME,     KC_PGDN,     KC_PGUP,     KC_END,      KC_BTN3,     _______,     KC_HOME,     KC_PGDN,     KC_PGUP,     KC_END,      _______,
    _______,     _______,     _______,     _______,     _______,     _______,                  _______,     _______,     _______,     _______,     _______
),


[_ADJUST] = LAYOUT_planck_mit(
    RESET,       _______,     _______,     KC_PSCR,     RGB_MOD,     RGB_HUI,     RGB_HUD,     KC_VOLU,     KC_VOLD,     KRIPT,       GO_QWEED1,   GO_QWERTY,
    DEBUG,       _______,     _______,     KC_CAPS,     RGB_TOG,     RGB_SAI,     RGB_SAD,     KC_MPLY,     KC_MSTP,     _______,     _______,     GO_COLEMAK,
    _______,     _______,     _______,     KC_SLCK,     _______,     RGB_VAI,     RGB_VAD,     KC_MPRV,     KC_MNXT,     _______,     _______,     GO_DVORAK,
    _______,     _______,     _______,     _______,     _______,     _______,                  _______,     _______,     _______,     _______,     _______
)

/* RGB Grid
 * ,-----------------------------------------------------------------------------------.
 * |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  12  |  13  |  14  |  15  |  16  |  17  |  18  |  19  |  20  |  21  |  22  |  23  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  24  |  25  |  26  |  27  |  28  |  29  |  30  |  31  |  32  |  33  |  34  |  35  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  36  |  37  |  38  |  39  |  40  |     41      |  42  |  43  |  44  |  45  |  46  |
 * `-----------------------------------------------------------------------------------'
 */

};

void keyboard_post_init_user(void) {

}


// Auto layer
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

// Set colors when layer is activate

void rgb_matrix_indicators_user(void) {
    //uint8_t layer = biton32(layer_state);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:

        break;
        case _ADJUST:
            //rgb_matrix_set_color(0, 200, 0, 0);
            //rgb_matrix_set_color(11, 200, 0, 200);
            //rgb_matrix_set_color(23, 200, 0, 200);
            //rgb_matrix_set_color(35, 200, 0, 200);
            rgb_matrix_set_color(10, 0, 200, 200);
        break;
        default:
            if(g_kript_mode == KRIPT_ENTER_CODE) rgb_matrix_set_color_all(200, 0, 0);
            else if(g_kript_mode == KRIPT_SELECT_CYPHER) rgb_matrix_set_color_all(0, 200, 0);
        break;
    }
}



// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case CPP_PNT:
            if (record->event.pressed) SEND_STRING("->"); break;
        case GO_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case GO_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case GO_QWEED1:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWEED1);
            }
            return false;
        case KRIPT:
            if (record->event.pressed) {
                kript_start();
            }
            return false;
        default:
            if(g_kript_mode != KRIPT_STANDBY)
                return kript_process(keycode, record);
    }
    return true;
};

// Leae2020der Keys
LEADER_EXTERNS();
void matrix_scan_user(void) {

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_F) {
      SEND_STRING("FALSE");
    }
    SEQ_TWO_KEYS(KC_F, KC_F) {
      SEND_STRING("TRUE");
    }
    SEQ_THREE_KEYS(KC_F, KC_F, KC_F) {
      SEND_STRING("NULL");
    }
    SEQ_THREE_KEYS(KC_R, KC_R, KC_R) {
      reset_keyboard();
    }
    // Personal information, must include "personal.h"
#ifdef PERSONAL_INFORMATION
    // Email
    SEQ_ONE_KEY(KC_E) {
      SEND_STRING(email);
    }
    SEQ_TWO_KEYS(KC_E, KC_C) {
      SEND_STRING(email_com);
    }
    // Name
    SEQ_ONE_KEY(KC_N) {
      SEND_STRING(name);
    }
    SEQ_TWO_KEYS(KC_N, KC_F) {
      SEND_STRING(first_name);
    }
    SEQ_THREE_KEYS(KC_N, KC_F, KC_F) {
      SEND_STRING(last_name);
    }
    SEQ_TWO_KEYS(KC_N, KC_N) {
      SEND_STRING(nickname_a);
    }
    SEQ_THREE_KEYS(KC_N, KC_N, KC_N) {
      SEND_STRING(nickname_b);
    }
    // Adress
    SEQ_TWO_KEYS(KC_P,KC_A) {
      SEND_STRING(address);
    }
    SEQ_THREE_KEYS(KC_P, KC_A, KC_A) {
      SEND_STRING(address_apt);
    }
     SEQ_TWO_KEYS(KC_P, KC_N) {
      SEND_STRING(apt_text);
    }
    SEQ_THREE_KEYS(KC_P, KC_N, KC_N) {
      SEND_STRING(apt);
    }
    // Phone
    SEQ_TWO_KEYS(KC_P, KC_T) {
      SEND_STRING(phonec);
    }
    SEQ_THREE_KEYS(KC_P, KC_T, KC_T) {
      SEND_STRING(phoneb);
    }
    SEQ_FOUR_KEYS(KC_P, KC_T, KC_T, KC_T) {
      SEND_STRING(phonea);
    }
    // Country
    SEQ_THREE_KEYS(KC_P, KC_C, KC_C) {
      SEND_STRING(country);
    }
    // City
    SEQ_TWO_KEYS(KC_P, KC_C) {
      SEND_STRING(country);
    }
    // Province
    SEQ_TWO_KEYS(KC_P, KC_P) {
      SEND_STRING(province);
    }
    SEQ_THREE_KEYS(KC_P, KC_P, KC_P) {
      SEND_STRING(province);
    }
    // Zip
    SEQ_TWO_KEYS(KC_P, KC_Z) {
      SEND_STRING(zip);
    }
#endif
  }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOW_DWN:
            return 120;
        default:
            return TAPPING_TERM;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOW_DWN:
        case RAI_UP:
            return true;
        default:
            return false;
    }
}

// RGB power control
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}



/*
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {11, 0}},
  {{0, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {11, 1}},
  {{0, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {11, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3},  {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3},{11, 3}},
};
SH_T(KC_A)
*/
