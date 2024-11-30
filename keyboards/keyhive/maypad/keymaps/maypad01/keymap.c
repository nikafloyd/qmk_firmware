/* Copyright 2019 codybender
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

enum layer_names {
	_NM,
	_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_NM] = LAYOUT_numpad_5x4(
		MO(_FN), KC_PSLS, KC_PAST, KC_PMNS, 
    	KC_P7,            KC_P8,   KC_P9,            
    	KC_P4,            KC_P5,   KC_P6,   KC_PPLS, 
    	KC_P1,            KC_P2,   KC_P3,            
    	         KC_P0,            KC_PDOT, KC_PENT  
	),
	[_FN] = LAYOUT_numpad_5x4(
		_______, _______, _______, KC_CALC, 
    	KC_NLCK, _______, _______,            
    	_______, _______, _______, KC_DEL, 
    	_______, _______, _______,            
    	         _______, _______, KC_BSPC  
	),
};

// Initializes LEDs as outputs
// Turns off red LEDs initially (High = off)
// Turn on NUM LOCK if off
void matrix_init_kb(void) {
	// Left LED
	setPinOutput(B0);
	// Right LED
	setPinOutput(D5);
	// Turn off LEDs
	writePinHigh(B0);
	writePinHigh(D5);

// Turn on NUM LOCK if off
if (!host_keyboard_led_state().num_lock) {
	tap_code_delay(KC_NLCK, 80);
};

}

void matrix_init_user(void) {
	
};

void matrix_scan_user(void) {
// If on function layer, turn on LED
uint8_t layer = biton32(layer_state);
	switch (layer) {
		case 0:
		writePinHigh(D5);
		break;
		case 1:
		writePinLow(D5);
		break;
	};

// If Num Lock is OFF, turn on LED
led_t led_state = host_keyboard_led_state();
	if (!led_state.num_lock) {
		writePinLow(B0);
	} else {
		writePinHigh(B0);
	}
}

void led_set_user(uint8_t usb_led) {

}
