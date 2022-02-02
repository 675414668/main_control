#ifndef __TASK_LCD_H
#define __TASK_LCD_H

#include "hal_lcd.h"

void task_lcd_init(void);
void task_lcd_display(void);
uint8_t lcd_get_display_state(void);
void lcd_set_display_state(uint8_t state);
#endif 
