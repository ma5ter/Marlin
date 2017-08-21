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

#ifndef _CTRLS_H_
#define _CTRLS_H_

// This needs nothing except the config file
// but ensure that controller types and ENABLED/DISABLED macros are already exists
#include "ctrl_type.h"
#include "macros.h"
// Old configuration files should be supported, use this to translate old values to new ones
#include "oldconfig.h" // '#include "Configuration.h"' is inside

#if !defined(CTRL_TYPE)
#error This build does not have any CTRL_TYPE selected, if you don't need any type of controller just set CTRL_TYPE to NONE
#endif

// Type specific blocks

#if CTRL_TYPE == CTRL_ADC_KEYPAD
	#define CTRL_HAS_KEYS
	#ifndef CTRL_ADC_KEYPAD_TOLERANCE
		#define CTRL_ADC_KEYPAD_TOLERANCE 0.1
	#endif
	#ifndef CTRL_ADC_KEYPAD_INACTIVE 
		#define CTRL_ADC_KEYPAD_INACTIVE 4000
	#endif
#endif


// Common block for all types

#if ENABLED(CTRL_HAS_KEYS)

	// when using bit-mapped register to store pressed keys
	// use this translation to map codes to bytes
	#define KEY_NONE 0 
	typedef enum {
		#if ENABLED(HAS_KEY_F3)
			KEY_F3,
		#endif
		#if ENABLED(HAS_KEY_F2)
			KEY_F2,
		#endif
		#if ENABLED(HAS_KEY_F1)
			KEY_F1,
		#endif
		#if ENABLED(HAS_KEY_DOWN)
			KEY_DOWN,
		#endif
		#if ENABLED(HAS_KEY_RIGHT)
			KEY_RIGHT,
		#endif
		#if ENABLED(HAS_KEY_MIDDLE)
			KEY_MIDDLE,
		#endif
		#if ENABLED(HAS_KEY_UP)
			KEY_UP,
		#endif
		#if ENABLED(HAS_KEY_LEFT)
			KEY_LEFT,
		#endif
		// Add more keys here using same syntax 

		// Automatic key counter, should be the last
		KEYS_MAX
	} KEYS;

	#ifndef KEY_MENU
		#if ENABLED(HAS_KEY_F1)
			#define KEY_MENU KEY_F1
		#elif ENABLED(HAS_KEY_MIDDLE)
			#define KEY_MENU KEY_MIDDLE
		#endif
	#endif

	#ifndef KEY_HOME
		#if ENABLED(HAS_KEY_LEFT)
			#define KEY_HOME KEY_LEFT
		#endif
	#endif

	#ifndef KEY_END
		#if ENABLED(HAS_KEY_RIGHT)
			#define KEY_END KEY_RIGHT
		#endif
	#endif

	// Select the appropriate storage for key masks
	#if KEYS_MAX <= 8
		typedef uint8_t keymask_t;
	#elif KEYS_MAX <= 16
		typedef uint8_t keymask_t;
	#elif KEYS_MAX <= 32
		typedef uint32_t keymask_t;
	#else
		#error Too many keys, maxumum supported is 32
	#endif

	// Gets the key code from the key mask
	#define KEYCODE(key_mask) (key_mask + 1)

	// Gets the key mask from the key code
	#define KEYMASK(key_code) (key_code - 1)

	// Checks the key is whatever active
	#define KEYCHECK(storage, key_mask) (storage & key_mask)

	// Common function to get active key code
	keymask_t ctrl_get_keys();

#endif


#endif
