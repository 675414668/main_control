#ifndef __TASK_LCD_H
#define __TASK_LCD_H

#include "hal_lcd.h"
#include "hal_lcd_api.h"
#include "hal_lcd_font.h"

void task_lcd_init(void);
void task_key_scan(void);
void task_lcd_display(void);
#endif 
