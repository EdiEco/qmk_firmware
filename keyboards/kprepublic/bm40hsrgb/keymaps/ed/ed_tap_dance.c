#include QMK_KEYBOARD_H
#include "ed_tap_dance.h"
#include "keyboard.h"
#include "ctype.h"
#include "quantum.h"


uint8_t cur_dance(qk_tap_dance_state_t *state)
{
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8;
}

// Control
static tap etap_state = {
    .is_press_action = true,
    .state = 0
};

void td_ctl_ent_finished(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    etap_state.state = cur_dance(state);
    switch (etap_state.state) {
        case SINGLE_TAP: tap_code(KC_ENT); break;
        case SINGLE_HOLD: register_code(keycode); break;
        case DOUBLE_TAP: tap_code(KC_DOT); tap_code(KC_ENT); break;
        case DOUBLE_HOLD: register_code(KC_LSFT); tap_code(KC_SLSH); unregister_code(KC_LSFT); tap_code(KC_ENT); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_ENT); tap_code(KC_ENT); break;
    }
}

void td_ctl_ent_reset(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    if(etap_state.state == SINGLE_HOLD) unregister_code(pair->kc1);
    etap_state.state = 0;
}

// Right Shift
static tap s_tap_state = {
    .is_press_action = true,
    .state = 0
};

void td_shift_finished(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_trio_t *pair = (qk_tap_dance_trio_t *)user_data;
    s_tap_state.state = cur_dance(state);

    if(s_tap_state.state != DOUBLE_TAP) register_code(pair->kc1);
    switch (s_tap_state.state) {
        case SINGLE_TAP:        tap_code(pair->kc3); break;
        case SINGLE_HOLD:       break;
        case DOUBLE_TAP:        tap_code(pair->kc2); break;
        case DOUBLE_HOLD:       tap_code(pair->kc2); break;
        case DOUBLE_SINGLE_TAP: tap_code(pair->kc3); tap_code(pair->kc3); break;
        case TRIPLE_TAP:        tap_code(pair->kc2); break;
    }
}

void td_shift_reset(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_trio_t *pair = (qk_tap_dance_trio_t *)user_data;
    if(s_tap_state.state != DOUBLE_TAP) unregister_code(pair->kc1);
    s_tap_state.state = 0;
}

// Layer down
static tap dtap_state = {
    .is_press_action = true,
    .state = 0
};

void td_lt_tt_finished(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;
    uint16_t layer = pair->kc2;

    dtap_state.state = cur_dance(state);
    switch (dtap_state.state) {
        case SINGLE_TAP: tap_code(keycode); break;
        case SINGLE_HOLD: layer_on(layer); break;
        case DOUBLE_TAP:
            if (layer_state_is(layer)) {
                // If already set, then switch it off
                layer_off(layer);
            } else {
                // If not already set, then switch the layer on
                layer_on(layer);
            }
            break;
        case DOUBLE_HOLD: register_code(keycode); break;
      //  case DOUBLE_SINGLE_TAP: tap_code(KC_ENT); register_code(KC_ENT); break;
    }
}

void td_lt_tt_reset(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;
    uint16_t layer = pair->kc2;

    switch (dtap_state.state) {
        case SINGLE_TAP:  break;
        case SINGLE_HOLD: layer_off(layer); break;
        //caese DOUBLE_TAP:  unregister_code(KC_ENT); break;
        case DOUBLE_HOLD: unregister_code(keycode); break;
        //case DOUBLE_SINGLE_TAP: unregister_code(KC_ENT); break;
    }
    dtap_state.state = 0;
}

// Layer down
static tap ddtap_state = {
    .is_press_action = true,
    .state = 0
};

void td_double_finished(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    ddtap_state.state = cur_dance(state);
    switch (ddtap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); tap_code(pair->kc1); unregister_code(KC_LSFT); break;
        case SINGLE_HOLD:  break;
        case DOUBLE_TAP: register_code(KC_LSFT); tap_code(pair->kc1); unregister_code(KC_LSFT); tap_code(pair->kc2); break;
        case DOUBLE_HOLD: break;
      //  case DOUBLE_SINGLE_TAP: tap_code(KC_ENT); register_code(KC_ENT); break;
    }
}

void td_double_reset(qk_tap_dance_state_t *state, void *user_data)
{
    ddtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_PNT] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_PSCR),
    [TD_SFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    //[TD_LSFT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_ls_finished, td_ls_reset, 200),
    //[TD_RSFT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_rs_finished, td_rs_reset, 200),
    [TD_LCTL_ENT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TIME(NULL, td_ctl_ent_finished, td_ctl_ent_reset, 100, KC_LCTL),
    //[TD_RCTL_ENT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TIME(NULL, td_ctl_ent_finished, td_ctl_ent_reset, 200, KC_RCTL),
    [TD_DWN_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_DOUBLE_TIME(NULL, td_lt_tt_finished, td_lt_tt_reset, 160, KC_LEFT, 7),
    [TD_CIRC_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_DOUBLE_TIME(NULL, td_double_finished, td_double_reset, 160, KC_CIRC, KC_E),
    [TD_TILD_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_DOUBLE_TIME(NULL, td_double_finished, td_double_reset, 160, KC_TILD, KC_A),

    [TD_LSFT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TRIPLE_TIME(NULL, td_shift_finished, td_shift_reset, 200, KC_LSFT, KC_LBRC, KC_9),
    [TD_RSFT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TRIPLE_TIME(NULL, td_shift_finished, td_shift_reset, 200, KC_RSFT, KC_RBRC, KC_0),
};
