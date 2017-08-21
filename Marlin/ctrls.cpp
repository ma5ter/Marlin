/*
	Controllers header file.
	
	Version 0.1

	Copyright (C) 2017 ma5ter [https://github.com/ma5ter/Marlin]

    Based on Marlin 3D Printer Firmware
    Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]

    Based on Sprinter and grbl.
    Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	
	---

	Purpose of this file is to reorganize all that spaghetty define-based 
	code trash which is used to select proper controller method used in the
	Marlin-firmware project

*/

#include "Marlin.h"
#include "ctrls.h" // After "Marlin.h" etc.

// Only when any type of controller is enabled
#if ENABLED(CTRL_TYPE)

#if (CTRL_TYPE == CTRL_ADC_KEYPAD) 
	volatile keymask_t keypad_button_mask;
	uint32_t encoderPosition;
#endif

// Some keys are using analog pin to read its states
#if (CTRL_TYPE == CTRL_ADC_KEYPAD) 

	#include "temperature.h"
	#include "ultralcd.h"

	typedef struct {
		uint8_t  key_mask;
		uint16_t nominal_reading;
	} ctrl_adc_keypad_ref_t;

	static const ctrl_adc_keypad_ref_t ctrl_adc_keypad_ref[] PROGMEM = CTRL_ADC_KEYPAD_REF;

	// Returns active key code
	keymask_t ctrl_get_keys(void)
	{
		if (thermalManager.adc_key_piece_count >= 16) {
			const uint16_t average_adc_value = thermalManager.adc_key_hoarder >> 2;
			#if ENABLED(CTRL_ADC_KEYPAD_DEBUG)
				SERIAL_PROTOCOLLN(average_adc_value);
			#endif
			thermalManager.adc_key_hoarder = 0;
			thermalManager.adc_key_piece_count = 0;
			if (average_adc_value < CTRL_ADC_KEYPAD_INACTIVE) {
				for (uint8_t i = 0; i < (sizeof(ctrl_adc_keypad_ref) / sizeof(ctrl_adc_keypad_ref_t)); i++) {
					const uint16_t 
						lo = pgm_read_word(&ctrl_adc_keypad_ref[i].nominal_reading) * (1 - CTRL_ADC_KEYPAD_TOLERANCE),
						hi = pgm_read_word(&ctrl_adc_keypad_ref[i].nominal_reading) * (1 + CTRL_ADC_KEYPAD_TOLERANCE);
					if (WITHIN(average_adc_value, lo, hi)) {
						keypad_button_mask |= (1 << pgm_read_byte(&ctrl_adc_keypad_ref[i].key_mask));
					}
				}
			}
		}
		return keypad_button_mask;
	}

	// Key press handler
	inline bool handle_adc_keypad()
	{
		static uint8_t adc_steps = 0;
		if (keypad_button_mask) {
			if (adc_steps < 20) {
				++adc_steps;
			}
			lcd_quick_feedback();
			lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
			const int8_t step = adc_steps > 19 ? 100 : adc_steps > 10 ? 10 : 1;
			#if ENABLED(HAS_KEY_DOWN)
			if (KEYCHECK(keypad_button_mask, KEY_DOWN)) {
				encoderPosition += ENCODER_PULSES_PER_STEP * step;
			}
			#endif
			#if ENABLED(HAS_KEY_UP)
			else if (KEYCHECK(keypad_button_mask, KEY_UP)) {
				encoderPosition -= ENCODER_PULSES_PER_STEP * step;
			}
			#endif
			#if ENABLED(HAS_KEY_ESCAPE)
			else if (KEYCHECK(keypad_button_mask, KEY_ESCAPE)) {
				menu_action_back();
			}
			#endif
			#if ENABLED(HAS_KEY_HOME)
			else if (KEYCHECK(keypad_button_mask, KEY_HOME)) {
				encoderPosition = 0;
			}
			#endif
			#if ENABLED(CTRL_ADC_KEYPAD_DEBUG)
			SERIAL_PROTOCOLLNPAIR("keypad_button_mask = ", (uint32_t)keypad_button_mask);
			SERIAL_PROTOCOLLNPAIR("encoderPosition = ", (uint32_t)encoderPosition);
			#endif
			return true;
		}
		else if (!thermalManager.adc_key_hoarder) {
			adc_steps = 0;    // reset stepping acceleration
		}

		return false;
	}


#endif

#endif