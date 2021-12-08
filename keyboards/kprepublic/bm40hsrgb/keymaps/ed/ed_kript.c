#include QMK_KEYBOARD_H

#include "ed_kript.h"
#include "ed_tools.h"
#include "../../../../../../pinfo.h"

#include "aes/aes.h"

#include <string.h>

uint8_t g_kript_mode = KRIPT_STANDBY;
uint8_t g_kript_count = 0;
uint8_t g_selected_cypher = 0;
char g_kript_password[KRIPT_MAX_PASSWORD_SIZE] = { 0 };

uint8_t code_iv[16] = CODE_IV;

const uint8_t PROGMEM g_kript_cypher[][KRIPT_MAX_CYPHER_SIZE] = {
    [KRIPT_CYPHER_01] = CODE_CYPHER_01,
};

void kript_start(void) {
    default_layer_set(1U << 1);
    g_kript_mode = KRIPT_SELECT_CYPHER;
}

void kript_reset(void) {
    memset(g_kript_password, 0, KRIPT_MAX_PASSWORD_SIZE);
    g_kript_mode = KRIPT_STANDBY;
    g_kript_count = 0;
    default_layer_set(1U << 0);
}

void kript_key_init(uint8_t *key) {
#ifndef ED_KRIPT_SHA256
  uint8_t j = 0, r = 1;
  for (int i = 0; i < KRIPT_KEY_SIZE; ++i){
    r = (g_kript_password[j] * 2 + 4 * r) & 0xFF;
    key[i] = r;
    j = (j + 1) % g_kript_count;}
#else
    sha256_hash_t sha;
    sha256(&sha, key, 8);
#endif
}

bool kript_process(uint16_t keycode, keyrecord_t *record) {

    if(g_kript_mode == KRIPT_STANDBY) return true;
    if(keycode < 0x5000) {
        if (record->event.pressed) {
            switch(g_kript_mode) {
                case KRIPT_SELECT_CYPHER:
                    switch(keycode) {
                        case KC_Q:
                        {
                            g_selected_cypher = KRIPT_CYPHER_01;
                            g_kript_mode = KRIPT_ENTER_CODE;
                            return false;
                        }
                        case KC_W:
                        {
                            g_selected_cypher = KRIPT_CYPHER_02;
                            g_kript_mode = KRIPT_ENTER_CODE;
                            return false;
                        }
                        case KC_E:
                        {
                            g_selected_cypher = KRIPT_CYPHER_03;
                            g_kript_mode = KRIPT_ENTER_CODE;
                            return false;
                        }
                        case KC_R:
                        {
                            g_selected_cypher = KRIPT_CYPHER_04;
                            g_kript_mode = KRIPT_ENTER_CODE;
                            return false;
                        }
                        case KC_ESC:
                            kript_reset();
                            return false;
                    }
                case KRIPT_ENTER_CODE:
                {
                    uint8_t key = (keycode & 0xFF);
                    if(key >= KC_A && key <= KC_0) {
                        g_kript_password[g_kript_count] = keycode_to_ascii(keycode);
                        g_kript_count++;
                    }
                    else if(keycode == KC_ENT) {
                        struct AES_ctx ctx;
                        uint8_t cText[KRIPT_MAX_CYPHER_SIZE];
                        uint8_t g_kript_key[KRIPT_KEY_SIZE];

                        memset(cText, 0, KRIPT_MAX_CYPHER_SIZE);
                        for(uint8_t i = 0; i < KRIPT_MAX_CYPHER_SIZE; i++) {
                            cText[i] = pgm_read_byte_near(g_kript_cypher[g_selected_cypher] + i);
                        }

                        kript_key_init(g_kript_key);
                        AES_init_ctx_iv(&ctx, g_kript_key, code_iv);
                        AES_CBC_decrypt_buffer(&ctx, cText, KRIPT_MAX_CYPHER_SIZE);
                        send_string((const char *)&cText);

                        memset(g_kript_key, 0, KRIPT_KEY_SIZE);
                        memset(cText, 0, KRIPT_MAX_CYPHER_SIZE);
                        kript_reset();
                    }
                    else if(keycode == KC_ESC) {
                        kript_reset();
                    }
                    return false;
                }
            }
        }
    }
    return true;
}

