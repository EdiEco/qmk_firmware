#include QMK_KEYBOARD_H
#include "ed_tap_dance.h"
#include "keyboard.h"

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
        case SINGLE_TAP: register_code(KC_ENT); break;
        case SINGLE_HOLD: register_code(keycode); break;
        case DOUBLE_TAP: tap_code(KC_DOT); register_code(KC_ENT); break;
        case DOUBLE_HOLD: register_code(KC_LSFT); tap_code(KC_SLSH); unregister_code(KC_LSFT); register_code(KC_ENT); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_ENT); register_code(KC_ENT); break;
    }
}

void td_ctl_ent_reset(qk_tap_dance_state_t *state, void *user_data)
{
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;
    uint16_t keycode = pair->kc1;

    switch (etap_state.state) {
        case SINGLE_TAP: unregister_code(KC_ENT); break;
        case SINGLE_HOLD: unregister_code(keycode); break;
        case DOUBLE_TAP:  unregister_code(KC_ENT); break;
        case DOUBLE_HOLD: unregister_code(KC_ENT); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_ENT); break;
    }
    etap_state.state = 0;
}

// Left Shift
static tap ls_tap_state = {
    .is_press_action = true,
    .state = 0
};

void td_ls_finished(qk_tap_dance_state_t *state, void *user_data)
{
    ls_tap_state.state = cur_dance(state);
    switch (ls_tap_state.state) {
        case SINGLE_TAP: register_code(KC_LSFT); tap_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LSFT); break;
        case DOUBLE_TAP: tap_code(KC_LBRC); break;
        case DOUBLE_HOLD: register_code(KC_LSFT); tap_code(KC_LBRC); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_LSFT); tap_code(KC_9); tap_code(KC_9); break;
        case TRIPLE_TAP: register_code(KC_LSFT); tap_code(KC_LBRC); break;
    }
}

void td_ls_reset(qk_tap_dance_state_t *state, void *user_data)
{
    switch (ls_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LSFT); break;
        case SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case DOUBLE_TAP:  break;
        case DOUBLE_HOLD: unregister_code(KC_LSFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_LSFT); break;
        case TRIPLE_TAP: unregister_code(KC_LSFT); break;
    }
    ls_tap_state.state = 0;
}

// Right Shift
static tap rs_tap_state = {
    .is_press_action = true,
    .state = 0
};

void td_rs_finished(qk_tap_dance_state_t *state, void *user_data)
{
    rs_tap_state.state = cur_dance(state);
    switch (rs_tap_state.state) {
        case SINGLE_TAP: register_code(KC_RSFT); tap_code(KC_0); break;
        case SINGLE_HOLD: register_code(KC_RSFT); break;
        case DOUBLE_TAP: tap_code(KC_RBRC); break;
        case DOUBLE_HOLD: register_code(KC_RSFT); tap_code(KC_RBRC); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_RSFT); tap_code(KC_0); tap_code(KC_0); break;
        case TRIPLE_TAP: register_code(KC_RSFT); tap_code(KC_RBRC); break;
    }
}

void td_rs_reset(qk_tap_dance_state_t *state, void *user_data)
{
    switch (rs_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_RSFT); break;
        case SINGLE_HOLD: unregister_code(KC_RSFT); break;
        case DOUBLE_TAP:  break;
        case DOUBLE_HOLD: unregister_code(KC_RSFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_RSFT); break;
        case TRIPLE_TAP: unregister_code(KC_RSFT); break;
    }
    rs_tap_state.state = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_PNT] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_PSCR),
    [TD_SFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_LSFT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_ls_finished, td_ls_reset, 200),
    [TD_RSFT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, td_rs_finished, td_rs_reset, 200),
    [TD_LCTL_ENT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TIME(NULL, td_ctl_ent_finished, td_ctl_ent_reset, 100, KC_LCTL),
    [TD_RCTL_ENT_EXTRA] = ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TIME(NULL, td_ctl_ent_finished, td_ctl_ent_reset, 200, KC_RCTL),
};
