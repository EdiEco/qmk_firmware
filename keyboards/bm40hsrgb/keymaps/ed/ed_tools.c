#include "ed_tools.h"
#include "quantum.h"

//const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};
//const char shifted_keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 0, 0, 0, '\t', ' ', '_', '+', '{', '}', '|', 0, ':', '\'', '~', '<', '>', '?'};

char keycode_to_ascii(uint16_t keycode) {
    char cha = 0x00;
    uint8_t key = (keycode & 0xFF);
    uint8_t mod = (keycode >> 8) & 0xFF;

    bool shift = ((keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) != 0 || (mod & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) != 0);
/*
    if (shift) {
        cha = pgm_read_byte_near(shifted_keycode_to_ascii_lut + key);
    } else if (get_mods() == 0) {
        cha = pgm_read_byte_near(keycode_to_ascii_lut + key);
    }
*/

    if(key >= KC_A && key <= KC_Z)
        cha = (shift) ? key + 0x3D : key + 0x5D;
    else if((key >= KC_1 && key <= KC_0) && shift)
    {
        switch(key)
        {
            case KC_1: cha = 0x21; break;
            case KC_2: cha = 0x40; break;
            case KC_3: cha = 0x23; break;
            case KC_4: cha = 0x24; break;
            case KC_5: cha = 0x25; break;
            case KC_6: cha = 0x5E; break;
            case KC_7: cha = 0x26; break;
            case KC_8: cha = 0x2A; break;
            case KC_9: cha = 0x28; break;
            case KC_0: cha = 0x29; break;
        }
    }
    else if(key >= KC_1 && key <= KC_9)
    {
        cha = key + 0x13;
    }
    else if(key == KC_0) cha = 0x30;

    return cha;
}

void keycode2hex16(uint16_t keycode) {
    char buffer[10];
    sprintf(buffer,"%04X", keycode);
    buffer[4] = '\0';
    send_string(buffer);
    SEND_STRING(" ");
    tap_code16(keycode);
    SEND_STRING("\n");
}

void keycode2hex(uint8_t keycode) {
    char buffer[10];
    sprintf(buffer,"%02X", keycode);
    buffer[2] = '\0';
    send_string(buffer);
    SEND_STRING(" ");
    tap_code16(keycode);
    SEND_STRING("\n");
}
