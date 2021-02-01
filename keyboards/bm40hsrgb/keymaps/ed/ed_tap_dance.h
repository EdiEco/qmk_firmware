#pragma once
#include "keyboard.h"

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
