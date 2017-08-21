/*
	Configuration translation file. 
	
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
	Marlin-firmware project.

	Use this to translate legacy Marlin Config.h to current macro definitions.

*/

#ifndef _OLDCONFIG_H_
#define _OLDCONFIG_H_

// Old configuration files should be supported, use this to translate old values to new ones
#include "Configuration.h"

#include "ctrl_type.h"
#include "macros.h"

#ifdef ADC_KEYPAD
#define CTRL_TYPE CTRL_ADC_KEYPAD
#endif
#ifdef ADC_KEYPAD_PIN
#define CTRL_ADC_KEYPAD_PIN ADC_KEYPAD_PIN
#endif
#ifdef ADC_KEY_NUM
#undef ADC_KEY_NUM
#endif
#ifdef ADC_KEYPAD_DEBUG
#undef ADC_KEYPAD_DEBUG
#define CTRL_ADC_KEYPAD_DEBUG
#endif

#endif