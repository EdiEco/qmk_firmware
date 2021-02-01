#pragma once
#include "keyboard.h"

#define ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TIME(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, tap_specific_tapping_term, kc1) {  \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, 0 }), \
    .custom_tapping_term = tap_specific_tapping_term \
}

#define ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_DOUBLE_TIME(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, tap_specific_tapping_term, kc1, kc2) {  \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2}), \
    .custom_tapping_term = tap_specific_tapping_term \
}

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Declarations
enum {
    TD_ESC_PNT,
    TD_SFT_CAP,
    TD_LCTL_ENT_EXTRA,
    TD_RCTL_ENT_EXTRA,
    TD_LSFT_EXTRA,
    TD_RSFT_EXTRA,
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

void td_ctl_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void td_ctl_ent_reset(qk_tap_dance_state_t *state, void *user_data);

void td_ls_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void td_ls_ent_reset(qk_tap_dance_state_t *state, void *user_data);

void td_rs_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void td_rs_ent_reset(qk_tap_dance_state_t *state, void *user_data);
