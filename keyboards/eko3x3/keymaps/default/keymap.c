#include "kb.h"

#define EKO_MENU 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = KEYMAP(
		KC_P7, KC_P8, KC_P9, 
		LT(2, KC_P4), KC_P5, KC_P6, 
		LT(1, KC_P1), KC_P2, KC_P3),

	[1] = KEYMAP(
		KC_TRNS, KC_TRNS, TO(3), 
		KC_TRNS, KC_BSPC, KC_COMM, 
		KC_TRNS, KC_P0, KC_PDOT),

	[2] = KEYMAP(
		KC_NLCK, KC_PAST, KC_PSLS, 
		KC_TRNS, KC_PPLS, KC_PMNS, 
		KC_PENT, KC_PEQL, KC_PENT),

	[3] = KEYMAP(
		RESET, KC_UP, KC_TRNS, 
		KC_LEFT, KC_DOWN, KC_RGHT, 
		TO(0), KC_TRNS, KC_TRNS),


};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	//keyevent_t event = record->event;

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}