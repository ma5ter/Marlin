/**
    Marlin 3D Printer Firmware
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

*/

#ifndef ULTRALCD_H
#define ULTRALCD_H

#include "Marlin.h"

#include "ctrls.h"

#if ENABLED(LCDKIND_CHARACTER)

#define BUTTON_EXISTS(BN) (defined(BTN_## BN) && BTN_## BN >= 0)
#define BUTTON_PRESSED(BN) !READ(BTN_## BN)

extern int16_t lcd_preheat_hotend_temp[2], lcd_preheat_bed_temp[2], lcd_preheat_fan_speed[2];

int16_t lcd_strlen(const char *s);
int16_t lcd_strlen_P(const char *s);
void lcd_update();
void lcd_init();
bool lcd_hasstatus();
void lcd_setstatus(const char *message, const bool persist = false);
void lcd_setstatusPGM(const char *message, const int8_t level = 0);
void lcd_setalertstatusPGM(const char *message);
void lcd_status_printf_P(const uint8_t level, const char *const fmt, ...);
void lcd_reset_alert_level();
void lcd_kill_screen();
void kill_screen(const char *lcd_msg);
bool lcd_detected(void);

extern uint8_t lcdDrawUpdate;
inline void lcd_refresh()
{
	lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW;
}

#if HAS_BUZZER
	void lcd_buzz(long duration, uint16_t freq);
#endif

#if ENABLED(LCD_PROGRESS_BAR) && PROGRESS_MSG_EXPIRE > 0
	void dontExpireStatus();
#endif

#if ENABLED(LCDKIND_GRAPHIC)
	extern uint16_t lcd_contrast;
	void set_lcd_contrast(const uint16_t value);
#endif

#if ENABLED(SHOW_BOOTSCREEN)
	void lcd_bootscreen();
#endif

#define LCD_UPDATE_INTERVAL 100

#if ENABLED(USE_CONTROLLER)

#define BLEN_A 0
#define BLEN_B 1
// Encoder click is directly connected
#if BUTTON_EXISTS(ENC)
	#define BLEN_C 2
#endif
#define EN_A (_BV(BLEN_A))
#define EN_B (_BV(BLEN_B))
#define EN_C (_BV(BLEN_C))

extern volatile uint8_t buttons;  // The last-checked buttons in a bit array.
void lcd_buttons_update();
void lcd_quick_feedback();        // Audible feedback for a button click - could also be visual
void lcd_completion_feedback(const bool good = true);

#if ENABLED(ADVANCED_PAUSE_FEATURE)
	void lcd_advanced_pause_show_message(const AdvancedPauseMessage message);
#endif // ADVANCED_PAUSE_FEATURE

#else

inline void lcd_buttons_update() {}

#endif

#if ENABLED(FILAMENT_LCD_DISPLAY) && ENABLED(SDSUPPORT)
	extern millis_t previous_lcd_status_ms;
#endif

bool lcd_blink();

#if ENABLED(REPRAPWORLD_KEYPAD) || ENABLED(ADC_KEYPAD) || ENABLED(NEWPANEL) // is also USE_CONTROLLER and NEWPANEL

#define KEYPAD_MOVE_MENU KEYCHECK(keypad_button_mask, keypad_button_mask & KEY_MENU)

#if BUTTON_EXISTS(ENC)
	#define LCD_CLICKED ((buttons & EN_C) || REPRAPWORLD_KEYPAD_MOVE_MENU)
#else
	#define LCD_CLICKED KEYPAD_MOVE_MENU
#endif

#define REPRAPWORLD_KEYPAD_PRESSED \
	(keypad_button_mask & ( \
		EN_KEYPAD_F3 | \
		EN_KEYPAD_F2 | \
		EN_KEYPAD_F1 | \
		EN_KEYPAD_DOWN | \
		EN_KEYPAD_RIGHT | \
		EN_KEYPAD_MIDDLE | \
		EN_KEYPAD_UP | \
		EN_KEYPAD_LEFT) \
	)

#elif ENABLED(NEWPANEL)
#define LCD_CLICKED (buttons & EN_C)
#else
#define LCD_CLICKED false
#endif

#else // no LCD

inline void lcd_update() {}
inline void lcd_init() {}
inline bool lcd_hasstatus()
{
	return false;
}
inline void lcd_setstatus(const char *const message, const bool persist = false)
{
	UNUSED(message);
	UNUSED(persist);
}
inline void lcd_setstatusPGM(const char *const message, const int8_t level = 0)
{
	UNUSED(message);
	UNUSED(level);
}
inline void lcd_setalertstatusPGM(const char *message)
{
	UNUSED(message);
}
inline void lcd_status_printf_P(const uint8_t level, const char *const fmt, ...)
{
	UNUSED(level);
	UNUSED(fmt);
}
inline void lcd_buttons_update() {}
inline void lcd_reset_alert_level() {}
inline bool lcd_detected()
{
	return true;
}
inline void lcd_refresh() {}

#endif // LCDKIND_CHARACTER

#define LCD_MESSAGEPGM(x)      lcd_setstatusPGM(PSTR(x))
#define LCD_ALERTMESSAGEPGM(x) lcd_setalertstatusPGM(PSTR(x))

void lcd_reset_status();

#if ENABLED(AUTO_BED_LEVELING_UBL)
	extern bool ubl_lcd_map_control;
	void lcd_mesh_edit_setup(float initial);
	float lcd_mesh_edit();
	void lcd_z_offset_edit_setup(float);
	float lcd_z_offset_edit();
#endif

#if ENABLED(DELTA_CALIBRATION_MENU)
	float lcd_probe_pt(const float &lx, const float &ly);
#endif


#if ENABLED(CTRL_TYPE)
	// Function pointer to menu functions.
	typedef void (*screenFunc_t)();

	#define menu_action_back(dummy) _menu_action_back()
	void _menu_action_back();
	void menu_action_submenu(screenFunc_t data);
	void menu_action_gcode(const char *pgcode);
	void menu_action_function(screenFunc_t data);
#endif


#endif // ULTRALCD_H
