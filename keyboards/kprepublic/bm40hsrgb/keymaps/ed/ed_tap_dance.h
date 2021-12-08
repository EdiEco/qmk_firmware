#pragma once
#include "keyboard.h"
//x
typedef struct {
    uint16_t kc1;
    uint16_t kc2;
    uint16_t kc3;
} qk_tap_dance_trio_t;

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

#define ACTION_TAP_DANCE_FN_ADVANCED_KEYCODE_TRIPLE_TIME(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, tap_specific_tapping_term, kc1, kc2, kc3) {  \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, \
    .user_data = (void *)&((qk_tap_dance_trio_t) { kc1, kc2, kc3}), \
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
    TD_DWN_EXTRA,
    TD_CIRC_EXTRA,
    TD_TILD_EXTRA,
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

void td_ctl_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void td_ctl_ent_reset(qk_tap_dance_state_t *state, void *user_data);

void td_ls_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void td_ls_ent_reset(qk_tap_dance_state_t *state, void *user_data);

void td_rs_ent_finished(qk_tap_dance_state_t *state, void *user_data);
void td_rs_ent_reset(qk_tap_dance_state_t *state, void *user_data);

void td_lt_tt_finished(qk_tap_dance_state_t *state, void *user_data);
void td_lt_tt_reset(qk_tap_dance_state_t *state, void *user_data);

void td_double_finished(qk_tap_dance_state_t *state, void *user_data);
void td_double_reset(qk_tap_dance_state_t *state, void *user_data);



