/*
	Controllers types constants, just list, nothing more.
	
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

	Purpose of this file is to reorganize all that spaghetti define-based 
	code trash which is used to select proper controller method used in the
	Marlin-firmware project

*/

#ifndef _CTRL_TYPES_H_
#define _CTRL_TYPES_H_

// NOTE! Put here nothing (except new controller types and their descriptions).

// Controller is absent and this is not a error, I just don't need it
#define CTRL_TYPE_NONE 0

// This stuff is simple and uses only one pin and number of resistors like this 
// http://www.instructables.com/id/How-to-access-5-buttons-through-1-Arduino-input/
#define CTRL_ADC_KEYPAD 1



#endif