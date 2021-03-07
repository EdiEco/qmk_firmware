#pragma once
#include "keyboard.h"
#include "personal.h"

#define KRIPT_AES_128

#define KRIPT_SIZE              16
#define KRIPT_KEY_SIZE          16
#define KRIPT_BLOCK_SIZE        16
#define KRIPT_MAX_CYPHER_SIZE   16

#define KRIPT_MAX_PASSWORD_SIZE 16


enum kript_mode {
    KRIPT_STANDBY = 0,
    KRIPT_SELECT_CYPHER,
    KRIPT_ENTER_CODE,
    KRIPT_SELECT_KEYCODE,
    KRIPT_TYPE_PASSWORD
};

enum kript_cypher{
    KRIPT_CYPHER_01,
    KRIPT_CYPHER_02,
    KRIPT_CYPHER_03,
    KRIPT_CYPHER_04
};


// Kript
void kript_start(void);
void kript_reset(void);
void kript_key_init(uint8_t* key);
bool kript_process(uint16_t keycode, keyrecord_t *record);

extern uint8_t g_kript_mode;
extern char g_kript_password[KRIPT_MAX_PASSWORD_SIZE];
extern uint8_t g_kript_key[KRIPT_KEY_SIZE];
extern uint8_t g_kript_count;
extern uint8_t code_iv[16];
extern uint8_t g_kript_mode;
extern uint8_t g_selected_cypher;
extern const uint8_t g_kript_cypher[][KRIPT_MAX_CYPHER_SIZE];
